#include "Mpu9250Implementation.hpp"


esp_err_t i2c_mpu9250_read_array(unsigned char address, unsigned char* read_data, int size)
{
    int ret;
    uint8_t read_data_l;
    uint8_t read_data_h;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_READ_BIT, ACK_CHECK_EN);
    while(size-- != 0) {
    	i2c_master_read_byte(cmd, read_data++, ACK_VAL);
    }
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_mpu9250_read_short(unsigned char address, unsigned short* read_data)
{
    int ret;
    uint8_t read_data_l;
    uint8_t read_data_h;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &read_data_h, ACK_VAL);
    i2c_master_read_byte(cmd, &read_data_l, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    *read_data = read_data_h;
    *read_data <<= 8;
    *read_data |= read_data_l;

    return ret;
}

esp_err_t i2c_mpu9250_read_byte(unsigned char address, unsigned char* read_data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
//    i2c_master_stop(cmd);
//    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
//    i2c_cmd_link_delete(cmd);
//    if (ret != ESP_OK) {
//        return ret;
//    }
//
//    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, read_data, ACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_mpu9250_write_word(unsigned char address, unsigned short write_data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, (write_data >> 8), ACK_CHECK_EN);
    i2c_master_write_byte(cmd, (write_data & 0xFF), ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_mpu9250_write_byte(unsigned char address, unsigned char write_data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU9250_I2C_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, write_data, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_AK8936_read_byte(unsigned char address, unsigned char* read_data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, AK8936_MAG_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, AK8936_MAG_ADDRESS << 1 | I2C_READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, read_data, ACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_AK8936_write_byte(unsigned char address, unsigned char write_data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, AK8936_MAG_ADDRESS << 1 | I2C_WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, write_data, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

void readAK8963Registers(uint8_t subAddress, uint8_t count, uint8_t* dest){

	i2c_mpu9250_write_byte(I2C_SLV0_ADDR, (AK8936_MAG_ADDRESS | I2C_READ_FLAG));
	i2c_mpu9250_write_byte(I2C_SLV0_REG, subAddress);
	i2c_mpu9250_write_byte(I2C_SLV0_CTRL, (I2C_SLV0_EN | count));
	vTaskDelay(portTICK_PERIOD_MS);
	i2c_mpu9250_read_array(EXT_SENS_DATA_00, dest, count);
}

bool writeAK8963Register(uint8_t subAddress, uint8_t data){
	uint8_t ReadValue;

	i2c_mpu9250_write_byte(I2C_SLV0_ADDR, AK8936_MAG_ADDRESS); // set slave 0 to the AK8963 and set for write
	i2c_mpu9250_write_byte(I2C_SLV0_REG, subAddress); // set the register to the desired AK8963 sub address
	i2c_mpu9250_write_byte(I2C_SLV0_DO, data); // store the data for write
	i2c_mpu9250_write_byte(I2C_SLV0_CTRL, (I2C_SLV0_EN | 1)); // enable I2C and send 1 byte

	// read the register and confirm
	readAK8963Registers(subAddress, 1, &ReadValue);

	if(ReadValue == data) {
  		return true;
  	}
  	else{
  		return false;
  	}
}


Mpu9250Implementation::Mpu9250Implementation() {
	//i2c_mpu9250_write_byte(GYRO_CONFIG_REG, GYROSCALE_500_DPS);
	//i2c_mpu9250_write_byte(ACCEL_CONFIG_REG, ACCELSCALE_4G);

	uint8_t ak8936_id;
	uint8_t mpu9250_id;

	// reset the MPU9250
	//i2c_mpu9250_write_byte(PWR_MGMNT_1, PWR_RESET);

	// wait for MPU-9250 to come back up
	//vTaskDelay(portTICK_PERIOD_MS);

	// reset the AK8963
	//writeAK8963Register(AK8963_CNTL2, AK8963_RESET);

	ESP_ERROR_CHECK(i2c_mpu9250_read_byte(117, &mpu9250_id));

	ESP_ERROR_CHECK(i2c_mpu9250_write_byte(USER_CTRL, I2C_MST_EN));

	ESP_ERROR_CHECK(i2c_mpu9250_write_byte(I2C_MST_CTRL, I2C_MST_CLK));

	readAK8963Registers(0, 1, &ak8936_id);

	if(writeAK8963Register(AK8936_MAG_CNTL, AK8936_CONT_MODE_2) == false) {
		ESP_LOGI("I2C TASK", "Write failed");
	}

	ESP_LOGI("I2C TASK", "MPU9250 ID: %i    AK8936 ID: %i", mpu9250_id, ak8936_id);
}

mpu9250_data Mpu9250Implementation::GetMpu9250Data() {

	mpu9250_data localdata;
	unsigned char localbyte;

	i2c_mpu9250_read_short(ACCEL_X_REG, &localdata.AccelerometerX);
	i2c_mpu9250_read_short(ACCEL_Y_REG, &localdata.AccelerometerY);
	i2c_mpu9250_read_short(ACCEL_Z_REG, &localdata.AccelerometerZ);
	i2c_mpu9250_read_short(GYRO_X_REG, &localdata.GyroscopeX);
	i2c_mpu9250_read_short(GYRO_Y_REG, &localdata.GyroscopeY);
	i2c_mpu9250_read_short(GYRO_Z_REG, &localdata.GyroscopeZ);

	/*i2c_mpu9250_write_byte(MPU9250_BYPASS_REG, MPU9250_BYPASS_BIT);

	i2c_AK8936_read_byte(AK8936_MAG_XOUT_L, &localbyte);
	localdata.MagnetoX = localbyte;
	localdata.MagnetoX <<= 8;
	i2c_AK8936_read_byte(AK8936_MAG_XOUT_H, &localbyte);
	localdata.MagnetoX |= localbyte;
	i2c_AK8936_read_byte(AK8936_MAG_YOUT_L, &localbyte);
	localdata.MagnetoY = localbyte;
	localdata.MagnetoY <<= 8;
	i2c_AK8936_read_byte(AK8936_MAG_YOUT_H, &localbyte);
	localdata.MagnetoY |= localbyte;
	i2c_AK8936_read_byte(AK8936_MAG_ZOUT_L, &localbyte);
	localdata.MagnetoZ = localbyte;
	localdata.MagnetoZ <<= 8;
	i2c_AK8936_read_byte(AK8936_MAG_ZOUT_H, &localbyte);
	localdata.MagnetoZ |= localbyte;

	i2c_mpu9250_write_byte(MPU9250_BYPASS_REG, 0x00);*/

	readAK8963Registers(AK8936_MAG_XOUT_L, 6, (unsigned char*)&localdata.MagnetoX);

	ESP_LOGI("I2C TASK", "Value: \t %i, \t %i, \t %i, \t %i, \t %i, \t %i, \t %d, \t %d, \t %d \t",
		localdata.AccelerometerX/100,
		localdata.AccelerometerY/100,
		localdata.AccelerometerZ/100,
		localdata.GyroscopeX/100,
		localdata.GyroscopeY/100,
		localdata.GyroscopeZ/100,
		localdata.MagnetoX/100,
		localdata.MagnetoY/100,
		localdata.MagnetoZ/100);

	return localdata;
}

Mpu9250Implementation::~Mpu9250Implementation() {

}
