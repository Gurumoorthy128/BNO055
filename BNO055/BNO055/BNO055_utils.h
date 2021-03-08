/*
 * BNO055.h
 *
 * Created: 12/22/2020 6:36:46 PM
 * Author : Gurumoorthy S 
 */


#ifndef TEST_BNO055_H_
#define TEST_BNO055_H_

//#include "I2C_Master_H_file.h"


//BNO055 TWI Address: Low - 0x28, High - 0x29
#define BNO055_WRITE_ADDRESS 0x50
#define BNO055_READ_ADDRESS 0x51

//Register definitions
/* Page id register definition */
#define BNO055_PAGE_ID_ADDR          0x07
/* PAGE0 REGISTER DEFINITION START*/
#define CHIP_ID_ADDR          0x00
#define ACCEL_REV_ID_ADDR     0x01
#define MAG_REV_ID_ADDR       0x02
#define GYRO_REV_ID_ADDR      0x03
#define SW_REV_ID_LSB_ADDR    0x04
#define SW_REV_ID_MSB_ADDR    0x05
#define BL_REV_ID_ADDR        0x06
/* Calibration status register */
#define CALIB_STAT_ADDR 0x35
/* Self test result register */
#define ST_RESULT_ADDR 0x36
/* Accelerometer data register */
#define ACCEL_DATA_X_LSB_ADDR 0x08
#define ACCEL_DATA_X_MSB_ADDR 0x09
#define ACCEL_DATA_Y_LSB_ADDR 0x0A
#define ACCEL_DATA_Y_MSB_ADDR 0x0B
#define ACCEL_DATA_Z_LSB_ADDR 0x0C
#define ACCEL_DATA_Z_MSB_ADDR 0x0D
/* Magnetometer data register */
#define MAG_DATA_X_LSB_ADDR   0x0E
#define MAG_DATA_X_MSB_ADDR   0x0F
#define MAG_DATA_Y_LSB_ADDR   0x10
#define MAG_DATA_Y_MSB_ADDR   0x11
#define MAG_DATA_Z_LSB_ADDR   0x12
#define MAG_DATA_Z_MSB_ADDR   0x13
/* Gyroscope data registers */
#define GYRO_DATA_X_LSB_ADDR  0x14
#define GYRO_DATA_X_MSB_ADDR  0x15
#define GYRO_DATA_Y_LSB_ADDR  0x16
#define GYRO_DATA_Y_MSB_ADDR  0x17
#define GYRO_DATA_Z_LSB_ADDR  0x18
#define GYRO_DATA_Z_MSB_ADDR  0x19
/* Euler data registers */
#define EULER_H_LSB_ADDR      0x1A
#define EULER_H_MSB_ADDR      0x1B
#define EULER_R_LSB_ADDR      0x1C
#define EULER_R_MSB_ADDR      0x1D
#define EULER_P_LSB_ADDR      0x1E
#define EULER_P_MSB_ADDR      0x1F
/* Quaternion data registers */
#define QUATERNION_DATA_W_LSB_ADDR  0x20
#define QUATERNION_DATA_W_MSB_ADDR  0x21
#define QUATERNION_DATA_X_LSB_ADDR  0x22
#define QUATERNION_DATA_X_MSB_ADDR  0x23
#define QUATERNION_DATA_Y_LSB_ADDR  0x24
#define QUATERNION_DATA_Y_MSB_ADDR  0x25
#define QUATERNION_DATA_Z_LSB_ADDR  0x26
#define QUATERNION_DATA_Z_MSB_ADDR  0x27
/* Linea acceleration data registers */
#define LINEAR_ACCEL_DATA_X_LSB_ADDR 0x28
#define LINEAR_ACCEL_DATA_X_MSB_ADDR 0x29
#define LINEAR_ACCEL_DATA_Y_LSB_ADDR 0x2A
#define LINEAR_ACCEL_DATA_Y_MSB_ADDR 0x2B
#define LINEAR_ACCEL_DATA_Z_LSB_ADDR 0x2C
#define LINEAR_ACCEL_DATA_Z_MSB_ADDR 0x2D
/* Gravity data registers */
#define GRAVITY_DATA_X_LSB_ADDR      0x2E
#define GRAVITY_DATA_X_MSB_ADDR      0x2F
#define GRAVITY_DATA_Y_LSB_ADDR      0x30
#define GRAVITY_DATA_Y_MSB_ADDR      0x31
#define GRAVITY_DATA_Z_LSB_ADDR      0x32
#define GRAVITY_DATA_Z_MSB_ADDR      0x33
/* Temperature data register */
#define TEMP_ADDR                    0x34
/* Status registers */
#define CALIB_STAT_ADDR              0x35
#define SELFTEST_RESULT_ADDR         0x36
#define INTR_STAT_ADDR               0x37
#define SYS_CLK_STAT_ADDR            0x38
#define SYS_STAT_ADDR                0x39
#define SYS_ERR_ADDR                 0x3A
/* Unit selection register */
#define UNIT_SEL_ADDR                0x3B
#define DATA_SELECT_ADDR             0x3C
/* Mode registers */
#define OPR_MODE_ADDR                0x3D
#define PWR_MODE_ADDR                0x3E
#define SYS_TRIGGER_ADDR             0x3F
#define TEMP_SOURCE_ADDR             0x40
/* Axis remap registers */
#define AXIS_MAP_CONFIG_ADDR         0x41
#define AXIS_MAP_SIGN_ADDR           0x42
/* Accelerometer Offset registers */
#define ACCEL_OFFSET_X_LSB_ADDR             0x55
#define ACCEL_OFFSET_X_MSB_ADDR             0x56
#define ACCEL_OFFSET_Y_LSB_ADDR             0x57
#define ACCEL_OFFSET_Y_MSB_ADDR             0x58
#define ACCEL_OFFSET_Z_LSB_ADDR             0x59
#define ACCEL_OFFSET_Z_MSB_ADDR             0x5A
/* Magnetometer Offset registers */
#define MAG_OFFSET_X_LSB_ADDR               0x5B
#define MAG_OFFSET_X_MSB_ADDR               0x5C
#define MAG_OFFSET_Y_LSB_ADDR               0x5D
#define MAG_OFFSET_Y_MSB_ADDR               0x5E
#define MAG_OFFSET_Z_LSB_ADDR               0x5F
#define MAG_OFFSET_Z_MSB_ADDR               0x60
/* Gyroscope Offset registers*/
#define GYRO_OFFSET_X_LSB_ADDR              0x61
#define GYRO_OFFSET_X_MSB_ADDR              0x62
#define GYRO_OFFSET_Y_LSB_ADDR              0x63
#define GYRO_OFFSET_Y_MSB_ADDR              0x64
#define GYRO_OFFSET_Z_LSB_ADDR              0x65
#define GYRO_OFFSET_Z_MSB_ADDR              0x66
/* Radius registers */
#define ACCEL_RADIUS_LSB_ADDR               0x67
#define ACCEL_RADIUS_MSB_ADDR               0x68
#define MAG_RADIUS_LSB_ADDR                 0x69
#define MAG_RADIUS_MSB_ADDR                 0x6A

/* Page 1 registers */
#define BNO055_UNIQUE_ID_ADDR               0x50

//Definitions for unit selection
#define MPERSPERS   0x00
#define MILLIG      0x01
#define DEG_PER_SEC 0x00
#define RAD_PER_SEC 0x02
#define DEGREES     0x00
#define RADIANS     0x04
#define CENTIGRADE  0x00
#define FAHRENHEIT  0x10
#define WINDOWS     0x00
#define ANDROID     0x80

//Definitions for power mode
#define POWER_MODE_NORMAL   0x00
#define POWER_MODE_LOWPOWER 0x01
#define POWER_MODE_SUSPEND  0x02

//Definitions for operating mode
#define OPERATION_MODE_CONFIG        0x00
#define OPERATION_MODE_ACCONLY       0x01
#define OPERATION_MODE_MAGONLY       0x02
#define OPERATION_MODE_GYRONLY       0x03
#define OPERATION_MODE_ACCMAG        0x04
#define OPERATION_MODE_ACCGYRO       0x05
#define OPERATION_MODE_MAGGYRO       0x06
#define OPERATION_MODE_AMG           0x07
#define OPERATION_MODE_IMUPLUS       0x08
#define OPERATION_MODE_COMPASS       0x09
#define OPERATION_MODE_M4G           0x0A
#define OPERATION_MODE_NDOF_FMC_OFF  0x0B
#define OPERATION_MODE_NDOF          0x0C

/* DATA read function */
int CALIB_STAT_ACC();
int CALIB_STAT_GYR();
int CALIB_STAT_MAG();
int CALIB_STAT_SYS();
float GRV_X();
float GRV_Y();
float GRV_Z();
float LIA_X();
float LIA_Y();
float LIA_Z();
float EULER_H();
float EULER_P();
float EULER_R();
float QUAT_X();
float QUAT_Y();
float QUAT_Z();
float QUAT_W();
float ACC_X();
float ACC_Y();
float ACC_Z();
float GYR_X();
float GYR_Y();
float GYR_Z();
float MAG_X();
float MAG_Y();
float MAG_Z();
float TEMP();

/*CONFIGURE functions*/
void UNIT_SEL();
void OFFSET();
void PWR_MODE();
void TEMP_SOURCE();

#define set_opr_as_CONFIG OPR_CONFIG_MODE()
void OPR_CONFIG_MODE();

#define set_opr_as_ACCONLY OPR_MODE_ACCONLY()
void OPR_MODE_ACCONLY();

#define set_opr_as_MAGONLY OPR_MODE_MAGONLY()
void OPR_MODE_MAGONLY();

#define set_opr_as_GYRONLY OPR_MODE_GYRONLY()
void OPR_MODE_GYRONLY();

#define set_opr_as_ACCMAG OPR_MODE_ACCMAG()
void OPR_MODE_ACCMAG();

#define set_opr_as_ACCGYR OPR_MODE_ACCGYR()
void OPR_MODE_ACCGYR();

#define set_opr_as_GYRMAG OPR_MODE_GYRMAG()
void OPR_MODE_GYRMAG();

#define set_opr_as_AMG OPR_MODE_AMG()
void OPR_MODE_AMG();

#define set_opr_as_IMU OPR_MODE_IMU()
void OPR_MODE_IMU();

#define set_opr_as_COMPASS OPR_MODE_COMPASS()
void OPR_MODE_COMPASS();

#define set_opr_as_M4G OPR_MODE_M4G()
void OPR_MODE_M4G();

#define set_opr_as_NDOF_FMC_OFF OPR_MODE_NDOF_FMC_OFF()
void OPR_MODE_NDOF_FMC_OFF();

#define set_opr_as_NDOF OPR_MODE_NDOF()
void OPR_MODE_NDOF();







//Function Prototypes
//void AVR_Init(void);
//void UART_Init(void);
//void UART_Tx(unsigned char data);
//void UART_Put_String(char *s);
//void BNO_Get_ID(void);

//Store TWI data
//uint8_t TWI_data;

#endif /* TEST_BNO055_H_ */