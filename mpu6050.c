/*
 * mpu6050.c
 *
 *  Created on: May 24, 2025
 *      Author: Hamid
 */

#include <mpu6050.h>

bool mpu6050_init(I2C_HandleTypeDef *hi2c)
{
	uint8_t data;
	HAL_StatusTypeDef ret;

	data = 0x00;
	ret = HAL_I2C_Mem_Write(hi2c, I2C_RECIEVER_ADDR, MPU6050_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if(ret != HAL_OK){
		return false;
	}
	HAL_Delay(500);

	data = 0x01;
	ret = HAL_I2C_Mem_Write(hi2c, I2C_RECIEVER_ADDR, MPU6050_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if(ret != HAL_OK){
		return false;
	}
	HAL_Delay(500);

	data = 0x09;
	ret = HAL_I2C_Mem_Write(hi2c, I2C_RECIEVER_ADDR, MPU6050_SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if(ret != HAL_OK){
		return false;
	}
	HAL_Delay(500);

	data = 0x00;
	ret = HAL_I2C_Mem_Write(hi2c, I2C_RECIEVER_ADDR, MPU6050_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if(ret != HAL_OK){
		return false;
	}
	HAL_Delay(500);

	data = 0x00;
	ret = HAL_I2C_Mem_Write(hi2c, I2C_RECIEVER_ADDR, MPU6050_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if(ret != HAL_OK){
		return false;
	}
	HAL_Delay(500);

	return true;
}

bool mpu6050_read_accel(I2C_HandleTypeDef *hi2c, accel_data_t* accel)
{
	uint8_t raw_data[6];
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Mem_Read(hi2c, I2C_RECIEVER_ADDR, MPU6050_ACCEL, 1, raw_data, 6, 500);
	if(ret != HAL_OK){
		return false;
	}

    accel->x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    accel->y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    accel->z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    return true;
}

bool mpu6050_read_temp(I2C_HandleTypeDef *hi2c, temp_data_t* temp)
{
	uint8_t raw_data[2];
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Mem_Read(hi2c, I2C_RECIEVER_ADDR, MPU6050_TEMP, 1, raw_data, 2, 500);
	if(ret != HAL_OK){
		return false;
	}

    temp->temperature = (int16_t)((raw_data[0] << 8) | raw_data[1]);

    return true;
}


bool mpu6050_read_gyro(I2C_HandleTypeDef *hi2c, gyro_data_t* gyro)
{
	uint8_t raw_data[6];
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Mem_Read(hi2c, I2C_RECIEVER_ADDR, MPU6050_GYRO, 1, raw_data, 6, 500);
	if(ret != HAL_OK){
		return false;
	}

    gyro->x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    gyro->y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    gyro->z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    return true;
}
