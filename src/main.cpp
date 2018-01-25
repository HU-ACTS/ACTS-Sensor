#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_adc_cal.h"

#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#include "SdWriterController.hpp"
#include "SensorController.hpp"
#include "SystemVariables.hpp"
#include "Systemerrors.hpp"

#include "StandbyController.hpp"
#include "WifiController.hpp"

RTC_DATA_ATTR struct timeval sleep_enter_time;
struct timeval GlobalTimeValNow;
time_t GlobalStartTime;

EventGroupHandle_t GlobalEventGroupHandle;

static gpio_num_t led_used_pin;
static int led_time_on;
static int led_time_off;

static void gpio_init_all() {
	// Enable GPIO_SD_DETECT again since it was assigned to RTC
	rtc_gpio_deinit(GPIO_SD_DETECT);
	// Select gipo
	gpio_pad_select_gpio(GPIO_LED_RED);
	gpio_pad_select_gpio(GPIO_LED_GREEN);
	gpio_pad_select_gpio(GPIO_LED_BLUE);
	// Set the GPIO as a push/pull output
	gpio_set_direction(GPIO_LED_RED, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED_GREEN, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_LED_BLUE, GPIO_MODE_OUTPUT);
	// Set initial state
	gpio_set_level(GPIO_LED_RED, 1);
	gpio_set_level(GPIO_LED_GREEN, 1);
	gpio_set_level(GPIO_LED_BLUE, 1);
}

void blink_set_led(gpio_num_t led, int time_on, int time_off) {
	if(led == GPIO_LED_RED || led == GPIO_LED_GREEN || led == GPIO_LED_BLUE) {
		led_used_pin = led;
		led_time_on = time_on;
		led_time_off = time_off;
	}
}

static void i2c_master_init() {
	// give scl pin some clocks
	gpio_pad_select_gpio(GPIO_SCL);
	gpio_set_direction(GPIO_SCL, GPIO_MODE_OUTPUT);
	for(int i=0;i<100;i++) {
		gpio_set_level(GPIO_SCL, 1);
		vTaskDelay(1);
		gpio_set_level(GPIO_SCL, 0);
		vTaskDelay(1);
	}

	// initialize bus
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_SDA;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_SCL;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_SPEED;

	if(i2c_param_config(I2C_NUM_0, &conf) != ESP_OK)  {
		ESP_LOGE("INIT_ERROR", "Error code:%i , message: i2c param config failed!", ERROR_I2C_PARAM_CONFIG);
	}

	if(i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0) != ESP_OK) {
		ESP_LOGE("INIT_ERROR", "Error code:%i , message: i2c driver install failed!", ERROR_I2C_DRIVER_INSTALL);
	}
}


void error_flash_init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    nvs_handle my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    int32_t error_value = (int32_t) ErrorCode::NO_ERROR; // value will default to 0, if not set yet in NVS
    err = nvs_get_i32(my_handle, "error_value", &error_value);
    bool failed = false;
    switch (err) {
        case ESP_OK:
        	ESP_LOGI("INIT", "Done");
        	ESP_LOGI("INIT", "Restart counter = %d", error_value);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            failed = true;
            break;
        default :
        	ESP_LOGI("INIT", "Error (%d) reading!", err);
    }
    if(failed)  {
        //int32_t error_code = (int32_t) error::errCode; // value will default to 0, if not set yet in NVS
        err = nvs_set_i32(my_handle, "error_value", (int32_t) ErrorCode::NO_ERROR);
        err = nvs_commit(my_handle);
        nvs_close(my_handle);
    }
    else    {
        nvs_close(my_handle);
    }
    if(error_value != (int32_t) ErrorCode::NO_ERROR) {
        ESP_LOGI("INIT", "Last ran ended with error code: %i\n", error_value);
    }
    else    {
        ESP_LOGI("INIT", "NO EXCEPTION FOUND IN LAST RUN");
    }
}

void BuildFileName(char *TimeStringBuffer, int str_len) {
	struct tm timeinfo;
	localtime_r(&GlobalStartTime, &timeinfo);
	strftime(TimeStringBuffer, str_len, "%Y_%m_%d_%H_%M_%S", &timeinfo);
	ESP_LOGI("MAIN", "Central time:  %s  ", TimeStringBuffer);
	strcat(TimeStringBuffer, ".bin");
}

void blink_task(void *pvParameter)
{
    while(1) {
    	gpio_set_level(led_used_pin, 1);
    	vTaskDelay(led_time_off / portTICK_PERIOD_MS);
    	gpio_set_level(led_used_pin, 0);
    	vTaskDelay(led_time_on / portTICK_PERIOD_MS);
    }
}

void sntp_task(void* param) {
    ESP_LOGI("SNTP TASK", "Initializing wifi");
    WiFiInitialize(WIFI_SSID, WIFI_PASSWORD);
	bool enabled = WiFiConnect(WIFI_CONNECT_TIMEOUT);
	ESP_LOGI("SNTP TASK", "Reading time");
	GlobalStartTime = WiFiGetTime(SNTP_READ_TIME_RETRY);
	WiFiDisconnect();

	if(GlobalStartTime == 0) {
		GlobalStartTime = GlobalTimeValNow.tv_sec;
	}
	else {
		GlobalTimeValNow.tv_sec = GlobalStartTime;
	}
	settimeofday(&GlobalTimeValNow, NULL);

	xEventGroupSetBits(GlobalEventGroupHandle, SNTPTaskDoneFlag);

	while(1) {
	   	vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}

extern "C" void app_main(void)
{
    ESP_LOGI("MAIN", "Booting completed");
    GlobalEventGroupHandle = xEventGroupCreate();

    if(nvs_flash_init() != ESP_OK)   {
      	ESP_LOGE("INIT_ERROR", "Error code: %i , message: nvs_flash_init failed!", ERROR_NVS_FLASH_INIT);
    }

    int WakeUpCause = esp_sleep_get_wakeup_cause();
    if(WakeUpCause == ESP_SLEEP_WAKEUP_TIMER) {
    	ESP_LOGI("MAIN", "Woke up from a timer reset");
    }
    else if(WakeUpCause == ESP_SLEEP_WAKEUP_EXT1) {
    	ESP_LOGI("MAIN", "Woke up from a pin change reset");
    }
    else {
    	ESP_LOGI("MAIN", "Woke up from normal reset");
    }

    ESP_LOGI("MAIN", "Creating SNTP task");
    TaskHandle_t sntp_task_handle;
    xTaskCreatePinnedToCore(sntp_task, "sntp_task", SNTPTASK_STACK_SIZE, NULL, SNTPTASK_PRIORITY, &sntp_task_handle, SNTPTASK_CORE_NUM);
    xEventGroupWaitBits(GlobalEventGroupHandle, SNTPTaskDoneFlag, pdTRUE, pdFALSE, portMAX_DELAY);
    vTaskDelete(sntp_task_handle);

    int sleep_time_ms = (GlobalTimeValNow.tv_sec - sleep_enter_time.tv_sec) * 1000 + (GlobalTimeValNow.tv_usec - sleep_enter_time.tv_usec) / 1000;
    ESP_LOGI("MAIN", "Time spent in deep sleep: %d ms", sleep_time_ms);

    error_flash_init();
    i2c_master_init();
    gpio_init_all();

    // Start blink task
    blink_set_led(GPIO_LED_GREEN, 10, 5000);
    xTaskCreatePinnedToCore(&blink_task, "blink_task", BLINKTASK_STACK_SIZE, NULL, BLINKTASK_PRIORITY, NULL, BLINKTASK_CORE_NUM);

    char name[64];
    BuildFileName(name, sizeof(name));
    SDWriter *GlobalSDWriter = new SDWriter;
    GlobalSDWriter->InitSDMMC(SDMMC_INIT_RETRIES);
    GlobalSDWriter->SetFileName(name);

    DataProcessor *GlobalDataHandler = new DataProcessor;
    GlobalDataHandler->SetTimeoutValue(TIMEOUT_TIME_SEC * 1000);
    GlobalDataHandler->SetTrigger(TRIGGER_VALUE_X, TRIGGER_VALUE_Y, TRIGGER_VALUE_Z);

    DoubleBuffer *GlobalDoubleBuffer = new DoubleBuffer(*GlobalSDWriter);

    SensorController *st = new SensorController(SENSORTASK_PRIORITY, *GlobalDoubleBuffer, *GlobalDataHandler);

    SdWriterController *sdw = new SdWriterController(WRITERTASK_PRIORITY, *GlobalDoubleBuffer, *GlobalSDWriter);

    StandbyController *sbc = new StandbyController(STANDBYCONT_PRIORITY);

    WifiController *wt = new WifiController(WIFITASK_PRIORITY, *GlobalDataHandler);

    ESP_LOGI("MAIN", "Init done");
}
