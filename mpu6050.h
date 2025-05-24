/*
 * mpu6050.h
 *
 *  Created on: May 24, 2025
 *      Author: Hamid
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define I2C_RECIEVER_ADDR (0x68 << 1)

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} accel_data_t;

typedef struct {
    int16_t temperature;
} temp_data_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} gyro_data_t;


bool mpu6050_init(I2C_HandleTypeDef *hi2c);

bool mpu6050_read_accel(I2C_HandleTypeDef *hi2c, accel_data_t* accel);
bool mpu6050_read_temp(I2C_HandleTypeDef *hi2c, temp_data_t* temp);
bool mpu6050_read_gyro(I2C_HandleTypeDef *hi2c, gyro_data_t* gyro);

#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_SMPLRT_DIV     0x19
#define MPU6050_CONFIG         0x1A
#define MPU6050_GYRO_CONFIG    0x1B
#define MPU6050_ACCEL_CONFIG   0x1C
#define MPU6050_WHO_AM_I       0x75

#define MPU6050_ACCEL          0x3B
#define MPU6050_TEMP           0x41
#define MPU6050_GYRO           0x43


#endif /* INC_MPU6050_H_ */
