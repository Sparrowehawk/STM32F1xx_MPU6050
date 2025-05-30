# STM32F1xx_MPU6050
A I2C MPU6050 implementation for the STM32F103C6T6 using the HAL library; however this would work with any STM32F1xx chip 

## Parts Used
- STM32F103C6T6
- MPU6050
- Logic Analyzer (used to see the communications)

## For a barebones setup, check my [other repo](https://github.com/Sparrowehawk/STM32_barebones/tree/main/section_9%20-%20I2C)

## Setup

- Use the STM32CubeIde (.ioc file) to select and enable the I2C pins.
  - Go into the .ioc file and select connectivity -> I2C
  - Enable I2C
  - See the two pins that are green on the chip, they are the I2C pins  
   
![image](https://github.com/user-attachments/assets/c63712e6-7caf-49e1-b3df-476d0e02da26)

- Add this line of code in `main.h`
   ```
   /* USER CODE BEGIN Includes */
  #include "mpu6050.h"
  /* USER CODE END Includes */
  ```

- Add `mpu6050.c` into  `/Src` and `mpu6050.h` to `/Inc`
- In `main.c`
  - Create a private variable called hi2c1 (depending on what the IDE creates in MX_I2Cx_Init())
```
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
```
  - After GPIO and I2C initialises, initialise the MPU6050
    - Note: `mpu6050_init()` can be changed to be a void if you don't care about error handling
```
  bool success = mpu6050_init(&hi2c1);
	if(success != true){
		error_led();
	}
	toggle_led();
  accel_data_t accel;
  temp_data_t temp;
```
  - In the `while(1)` loop, read the data with the following functions
    - `mpu6050_read_accel(&hi2c1, &accel)`
    - `mpu6050_read_temp(&hi2c1, &temp)`
    - `mpu6050_read_gyro(&hi2c1, &gyro)`

## What the Data Means

### Accelerometer
- The MPU6050 outputs raw accelerometer values as signed 16-bit integers across three axes: X, Y, and Z
- Individually, they're given as 6 8-bit hex values, they can be combined in pairs to get the X, Y and Z values
- These values can be converted to `g` depending on the sensitivity set during initialisation (found in the register map as well)
  - For ±2g:  
     - `Acceleration (g) = Raw Value / 16384.0f`
    

### Temperature
- The temperature is reported as a signed 16-bit value
- Example: If bytes received are `0xF2` and `0x6D`, combine to get `0xF26D`
- Convert to decimal:
   - `0xF26D` = `-3475`
- Use the formula from the MPU6050 Register Map:
   - `Temperature (°C) = (Raw Value / 340.0) + 36.53`
   - `-3475 / 340 + 36.53 ≈ 26.31°C`

### Gyroscope
- Gyroscope data is also provided as signed 16-bit values for the X, Y, and Z axes
- Individually, they're given as 6 8-bit hex values, they can be combined in pairs to get the X, Y and Z values
- To convert raw values to degrees per second (°/s), use:
  - For ±250°/s:
    - `Gyro (°/s) = Raw Value/131.0f`
    
---

## License
MIT License

---

## Author
[Sparrowehawk](https://github.com/Sparrowehawk)
