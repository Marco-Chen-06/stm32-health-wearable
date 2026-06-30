#ifndef BMI270_HW_H
#define BMI270_HW_H

#define BMI270_CHIP_ID 0x24
#define BMI270_I2C_DEFAULT_ADDR 0x68

// register bases
#define BMI270_REG_CHIP_ID 0x00

#define BMI270_REG_DATA_8 0x0C // acc_x lsb
#define BMI270_REG_DATA_9 0x0D // acc_x msb
#define BMI270_REG_DATA_10 0x0E // acc_y lsb
#define BMI270_REG_DATA_11 0x0F // acc_y msb
#define BMI270_REG_DATA_12 0x10 // acc_z lsb
#define BMI270_REG_DATA_13 0x11 // acc_z msb

#define BMI270_REG_DATA_14 0x12 // gyr_x lsb
#define BMI270_REG_DATA_15 0x13 // gyr_x msb
#define BMI270_REG_DATA_16 0x14 // gyr_x lsb
#define BMI270_REG_DATA_17 0x15 // gyr_x msb
#define BMI270_REG_DATA_18 0x16 // gyr_x lsb
#define BMI270_REG_DATA_19 0x17 // gyr_x msb

#define BMI270_REG_INTERNAL_STATUS 0x21

#define BMI270_REG_FEATURES_GYR_POSTPROC 0x3C

#define BMI270_REG_ACC_CONF 0x40
#define BMI270_REG_GYR_CONF 0x42
#define BMI270_REG_GYR_RANGE 0x43
#define BMI270_REG_INIT_CTRL 0x59

#define BMI270_REG_INIT_ADDR_0 0x5B
#define BMI270_REG_INIT_ADDR_1 0x5C

#define BMI270_REG_INIT_DATA 0x5E
#define BMI270_REG_PWR_CONF 0x7C
#define BMI270_REG_PWR_CTRL 0x7D

#define BMI270_REG_CMD 0x7E
#define BMI270_CMD_SOFTRESET 0xB6

#endif
