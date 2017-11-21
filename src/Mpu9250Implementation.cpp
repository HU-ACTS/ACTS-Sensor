#include "Mpu9250Implementation.hpp"


esp_err_t i2c_mpu9250_read_array(unsigned char address, unsigned char* read_data, int size)
{
    int ret;
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
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }

    cmd = i2c_cmd_link_create();
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
    i2c_master_read_byte(cmd, read_data, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_AK8936_read_array(unsigned char address, unsigned char count, unsigned char* read_data)
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
    for(int i=0;i<count - 1;i++) {
    	i2c_master_read_byte(cmd, read_data++, ACK_VAL);
    }
    i2c_master_read_byte(cmd, read_data, NACK_VAL);
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

static unsigned short switch_short(unsigned short value) {
	unsigned char upper = value >> 8;
	unsigned char lower = value & 0xFF;
	unsigned short returnvalue = lower;
	returnvalue <<= 8;
	returnvalue |= upper;
	return returnvalue;
}

Mpu9250Implementation::Mpu9250Implementation() {
	uint8_t ak8936_id = 0;
	uint8_t mpu9250_id = 0;

	// reset the MPU9250
	i2c_mpu9250_write_byte(PWR_MGMNT_1, PWR_RESET);
	vTaskDelay(10);

	i2c_mpu9250_read_byte(117, &mpu9250_id);

	i2c_mpu9250_write_byte(MPU9250_BYPASS_REG, MPU9250_BYPASS_BIT);

	// reset the ak8936
	i2c_AK8936_write_byte(AK8963_CNTL2, AK8963_RESET);
	vTaskDelay(10);

	i2c_AK8936_read_byte(0, &ak8936_id);

	i2c_AK8936_write_byte(10, AK8936_16BIT | AK8936_SINGLE_SAMPLE);

	ESP_LOGI("I2C TASK", "MPU9250 ID: %i    AK8936 ID: %i", mpu9250_id, ak8936_id);
}

mpu9250_data Mpu9250Implementation::GetMpu9250Data() {

	mpu9250_data localdata;
	memset(&localdata, 0, sizeof(mpu9250_data));

	i2c_mpu9250_read_short(ACCEL_X_REG, &localdata.AccelerometerX);
	i2c_mpu9250_read_short(ACCEL_Y_REG, &localdata.AccelerometerY);
	i2c_mpu9250_read_short(ACCEL_Z_REG, &localdata.AccelerometerZ);
	i2c_mpu9250_read_short(GYRO_X_REG, &localdata.GyroscopeX);
	i2c_mpu9250_read_short(GYRO_Y_REG, &localdata.GyroscopeY);
	i2c_mpu9250_read_short(GYRO_Z_REG, &localdata.GyroscopeZ);

	unsigned char status_reg_1 = 0;
	i2c_AK8936_read_byte(2, &status_reg_1);
	if(status_reg_1)
	{
		i2c_AK8936_read_array(AK8936_MAG_XOUT_L, 6, (unsigned char*)&localdata.MagnetoX);
		localdata.MagnetoX = switch_short(localdata.MagnetoX);
		localdata.MagnetoY = switch_short(localdata.MagnetoY);
		localdata.MagnetoZ = switch_short(localdata.MagnetoZ);
	}

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

	i2c_AK8936_write_byte(10, AK8936_16BIT | AK8936_SINGLE_SAMPLE);

	return localdata;
}

Mpu9250Implementation::~Mpu9250Implementation() {

}
