/*
 * Mpu9250Implementation.hpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Sander
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#define WRITE_BIT              		I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT               		I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN           		0x1              /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS          		0x0              /*!< I2C master will not check ack from slave */
#define ACK_VAL                		0x0              /*!< I2C ack value */
#define NACK_VAL               		0x1              /*!< I2C nack value */
#define I2C_MASTER_SCL_IO      		19               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO      		18               /*!< gpio number for I2C master data  */
#define I2C_WRITE_BIT           	0x00
#define I2C_READ_BIT            	0x01

// I2C addresses
#define MPU9250_I2C_ADDRESS     	0x68
#define AK8936_ADDRESS   			0x0C

// MPU9250 registers
#define MPU9250_REG_WHOAMI			0x75
#define MPU9250_REG_GYRO_CONFIG		0x1B
#define MPU9250_REG_GYRO_XL     	0x43
#define MPU9250_REG_GYRO_YL     	0x45
#define MPU9250_REG_GYRO_ZL     	0x47
#define MPU9250_REG_ACCEL_CONFIG	0x1C
#define MPU9250_REG_ACCEL_XL    	0x3B
#define MPU9250_REG_ACCEL_YL    	0x3D
#define MPU9250_REG_ACCEL_ZL    	0x3F
#define MPU9250_REG_BYPASS			0x37
#define MPU9250_REG_PWR_MGMNT_1		0x6B

// MPU9250 settings
#define GYROSCALE_250_DPS       	0x00
#define GYROSCALE_500_DPS       	0x08
#define GYROSCALE_1000_DPS      	0x10
#define GYROSCALE_2000_DPS      	0x18
#define ACCELSCALE_2G           	0x00
#define ACCELSCALE_4G           	0x08
#define ACCELSCALE_8G           	0x10
#define ACCELSCALE_16G          	0x18
#define MPU9250_SET_PWR_RESET		0x80
#define MPU9250_SET_BYPASS			0x02

// AK8936 registers
#define AK8936_REG_WHOAMI			0x00
#define AK8936_REG_STATUS1			0x02
#define AK8936_REG_XOUT_L       	0x03
#define AK8936_REG_CNTL1        	0x0A
#define AK8963_REG_CNTL2			0x0B

// AK8936 settings
#define AK8936_SET_SING_SAMP		0x01
#define AK8936_SET_CONT_MODE_1		0x02
#define AK8936_SET_CONT_MODE_2		0x06
#define AK8936_SET_16BIT			0x10
#define AK8963_SET_RESET			0x01

class mpu9250_data{
public:
   short AccelerometerX;
   short AccelerometerY;
   short AccelerometerZ;
   short GyroscopeX;
   short GyroscopeY;
   short GyroscopeZ;
   short MagnetoX;
   short MagnetoY;
   short MagnetoZ;
};


class Mpu9250Implementation {
public:
	Mpu9250Implementation();
	mpu9250_data GetMpu9250Data();
	~Mpu9250Implementation();
private:
	mpu9250_data LocalMPUData;
	bool MPUIsInitialized;
	bool AKIsInitialized;
protected:
};