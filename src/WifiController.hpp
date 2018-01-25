#pragma once

#include "esp_log.h"

#include "WiFiC.h"
#include "BaseTask.hpp"
#include "DataProcessor.hpp"

class WifiController : BaseTask {
public:
	WifiController(unsigned int task_priority, DataProcessor &dp);
	friend void run_wifi_task(void *args);
private:
	DataProcessor &DPHandle;
    void *WIFITASK_TIMER_ID = 0;
protected:
	void main_task();
};

