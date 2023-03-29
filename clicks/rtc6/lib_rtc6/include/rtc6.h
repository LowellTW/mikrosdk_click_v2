/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*!
 * \file
 *
 * \brief This file contains API for RTC6 Click driver.
 *
 * \addtogroup rtc6 RTC6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC6_H
#define RTC6_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RTC6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup regs Registers
 * \{
 */
#define RTC6_REG_SECONDS              0x00
#define RTC6_REG_MINUTES              0x01
#define RTC6_REG_HOURS                0x02
#define RTC6_REG_DAY                  0x03
#define RTC6_REG_DATE                 0x04
#define RTC6_REG_MONTH                0x05
#define RTC6_REG_YEARS                0x06
#define RTC6_REG_CONTROL              0x07
#define RTC6_REG_OSC_TRIM             0x08
#define RTC6_REG_EEUNLOCK             0x09
#define RTC6_REG_ALARM0_SECOND        0x0A
#define RTC6_REG_ALARM0_MINUTE        0x0B
#define RTC6_REG_ALARM0_HOUR          0x0C
#define RTC6_REG_ALARM0_DAY           0x0D
#define RTC6_REG_ALARM0_DATE          0x0E
#define RTC6_REG_ALARM0_MONTH         0x0F
#define RTC6_REG_ALARM1_SECOND        0x11
#define RTC6_REG_ALARM1_MINUTE        0x12
#define RTC6_REG_ALARM1_HOUR          0x13
#define RTC6_REG_ALARM1_DAY           0x14
#define RTC6_REG_ALARM1_DATE          0x15
#define RTC6_REG_ALARM1_MONTH         0x16
#define RTC6_REG_POWER_DOWN_MINUTE    0x18
#define RTC6_REG_POWER_DOWN_HOUR      0x19
#define RTC6_REG_POWER_DOWN_DATE      0x1A
#define RTC6_REG_POWER_DOWN_MONTH     0x1B
#define RTC6_REG_POWER_UP_MINUTE      0x1C
#define RTC6_REG_POWER_UP_HOUR        0x1D
#define RTC6_REG_POWER_UP_DATE        0x1E
#define RTC6_REG_POWER_UP_MONTH       0x1F
/** \} */

/**
 * \defgroup oscillator Oscillator
 * \{
 */
#define RTC6_OSCILLATOR_ENABLE     0x80
#define RTC6_OSCILLATOR_DISABLE    0x00
/** \} */

/**
 * \defgroup format Format
 * \{
 */
#define RTC6_FORMAT_12_HOURS    0x40
#define RTC6_FORMAT_24_HOURS    0x00
/** \} */

/**
 * \defgroup swo SWO
 * \{
 */
#define RTC6_SWO_1HZ          0x01
#define RTC6_SWO_4_096KHZ     0x02
#define RTC6_SWO_8_192KHZ     0x03
#define RTC6_SWO_32_768KHZ    0x04
/** \} */

/* Months in Year */
#define RTC6_MONTH_JANUARY      0x00
#define RTC6_MONTH_FEBRUARY     0x01
#define RTC6_MONTH_MARCH        0x02
#define RTC6_MONTH_APRIL        0x03
#define RTC6_MONTH_MAY          0x04
#define RTC6_MONTH_JUNE         0x05
#define RTC6_MONTH_JULY         0x06
#define RTC6_MONTH_AUGUST       0x07
#define RTC6_MONTH_SEPTEMBER    0x08
#define RTC6_MONTH_OCTOBER      0x09
#define RTC6_MONTH_NOVEMBER     0x0A
#define RTC6_MONTH_DECEMBER     0x0B
/** \} */

/**
 * \defgroup days_in_week Days in Week
 * \{
 */
#define RTC6_DAY_MONDAY       0x00
#define RTC6_DAY_TUESDAY      0x01
#define RTC6_DAY_WEDNESDAY    0x02
#define RTC6_DAY_THURSDAY     0x03
#define RTC6_DAY_FRIDAY       0x04
#define RTC6_DAY_SATURDAY     0x05
#define RTC6_DAY_SUNDAY       0x06
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define RTC6_DEVICE_SLAVE_ADDR     0x6F
#define RTC6_SRAM_SLAVE_ADDR       0xDE
#define RTC6_EEPROM_SLAVE_ADDR     0x57
/** \} */

/**
 * \defgroup alarm Alarm
 * \{
 */
#define RTC6_ALARM_0   0x00
#define RTC6_ALARM_1   0x01
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC6_RETVAL  uint8_t

#define RTC6_OK           0x00
#define RTC6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error Error
 * \{
 */
#define SET_ERROR       0x02
#define DEVICE_ERROR    0x01
#define DEVICE_OK       0x00
/** \} */

/**
 * \defgroup bytes Bytes
 * \{
 */
#define RTC6_TIMEDATE_BYTES    0x07
#define RTC6_SECONDS_BYTE      0x00
#define RTC6_MINUTES_BYTE      0x01
#define RTC6_HOUR_BYTE         0x02
#define RTC6_DAY_BYTE          0x03
#define RTC6_DATE_BYTE         0x04
#define RTC6_MONTH_BYTE        0x05
#define RTC6_YEAR_BYTE         0x06
/** \} */

/**
 * \defgroup ram_and_eeprom RAM and EEPROM
 * \{
 */
#define RTC6_RAM_SIZE              64
#define RTC6_RAM_START           0x20
#define RTC6_RAM_END             0x5f
#define RTC6_EEPROM_SIZE         1024
#define RTC6_EEPROM_START           0
#define RTC6_EEPROM_END          1024
#define RTC6_EEPROM_PAGE_SIZE       8
#define RTC6_EEPROM_STATUS       0xFF
/** \} */

/* Seconds  */
/**
 * \defgroup seconds Seconds
 * \{
 */
#define TIME_SEC_IN_MIN             60
#define TIME_SEC_IN_HOUR            3600
#define TIME_SEC_IN_DAY             86400
#define TIME_SEC_IN_MONTH           2629743
#define TIME_SEC_IN_YEAR_365        31536000
#define TIME_SEC_IN_LEAP_YEAR       31622400
#define TIME_SEC_IN_YEAR_365_25     31557600
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click time data object
 */
typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t weekdays;
    uint8_t monthday;
    uint8_t month;
    uint16_t year;

} rtc6_time_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins

    digital_in_t int_pin;

    // Modules

    i2c_master_t i2c;

    // ctx variable

    uint8_t slave_address;

    int8_t time_zone;

} rtc6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t scl;
    pin_name_t sda;

    // Additional gpio pins

    pin_name_t int_pin;

    // static variable

    uint32_t i2c_speed;
    uint8_t i2c_address;

    // Time config value

    int8_t time_zone_cfg;

} rtc6_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rtc6_cfg_setup ( rtc6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC6_RETVAL rtc6_init ( rtc6_t *ctx, rtc6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Rtc6 click.
 */
void rtc6_default_cfg ( rtc6_t *ctx, int8_t time_zone, rtc6_time_t *utc_time, rtc6_time_t *alarm_time );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void rtc6_generic_write ( rtc6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void rtc6_generic_read ( rtc6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

uint8_t rtc6_init_fun ( rtc6_t *ctx, int8_t time_zone );

/**
 * @brief Enable Square Wave Output
 *
 * @param ctx          Click object.
 * @param swo    Frequency of output
 *
 * @description This function enables and sets square wave output.
 * Available options:
 * <pre>
     - RTC6_SWO_1HZ
     - RTC6_SWO_4_096KHZ
     - RTC6_SWO_8_192KHZ
     - RTC6_SWO_32_768KHZ
 * </pre>
 */
void rtc6_enable_swo ( rtc6_t *ctx, uint8_t swo );

/**
 * @brief Disables Square Wave Output
 *
 * @param ctx          Click object.
 *
 * @description This function deisables square wave output.
 */
void rtc6_disable_swo ( rtc6_t *ctx );

/**
 * @brief Enables automatic switch to battery
 *
 * @param ctx          Click object.
 *
 * @description This function enables automatic switch to battery on VCC failure.
 */
void rtc6_battery_enable ( rtc6_t *ctx );

/**
 * @brief Gets the current GMT time set in the RTC
 *
 * @param ctx         Click object.
 * @param gmt_time    A buffer in which GMT time values will be stored
 *
 * @description This function gets current GMT time and sets it in the RTC.
 */
void rtc6_get_gmt_time ( rtc6_t *ctx, rtc6_time_t *gmt_time );

/**
 * @brief Sets the UTC GMT time
 *
 * @param ctx           Click object.
 * @param set_time      GMT time to be set.
 *
 * @description This function sets GMT/UTC time.
 */
void rtc6_set_gmt_time ( rtc6_t *ctx, rtc6_time_t *set_time );

/**
 * @brief Calculates the current local time
 *
 * @param ctx           Click object.
 * @param local_time    A buffer in which local time values will be stored
 *
 * @description This function calculates current local time.
 */
void rtc6_get_local_time ( rtc6_t *ctx, rtc6_time_t *local_time );

/**
 * @brief Calculates the current GMT time in UNIX epoch time
 *
 * @param ctx           Click object.
 *
 * @retval GMT time converted to UNIX epoch time
 *
 * @description This function calculates and returns current GMT time in UNIX epoch time.
 */
uint32_t rtc6_get_gmt_unix_time ( rtc6_t *ctx );

/**
 * @brief Calculates the current local time in UNIX epoch time
 *
 * @param ctx           Click object.
 *
 * @retval local time converted to UNIX epoch time
 *
 * @description This function calculates and returns current local time in UNIX epoch time.
 */
uint32_t rtc6_get_local_unix_time( rtc6_t *ctx );

/**
 * @brief Checks if the current year is a leap one
 *
 * @param ctx           Click object.
 *
 * @retval 0 - on a leap year or 1 - if not a leap year
 *
 * @description This function checks if current year is a leap year and returns an appropriate value.
 */
uint8_t rtc6_is_leap_year ( rtc6_t *ctx );

/**
 * @brief Checks if a power failure has occured
 *
 * @param ctx           Click object.
 *
 * @retval 0 if a power failure detected or 1 if no power failure was detected
 *
 * @description This function checks if power failure has occured and returns an appropriate value.
 */
uint8_t rtc6_is_power_failure ( rtc6_t *ctx );

/**
 * @brief Gets the time of the last power failure
 *
 * @param ctx           Click object.
 * @param last_time     time of the power failure
 *
 * @description This functions gets the of the last power faulure.
 */
void rtc6_get_last_power_failure ( rtc6_t *ctx, rtc6_time_t *last_time );

/**
 * @brief Sets the desired alarm
 *
 * @param ctx           Click object.
 * @param alarm         Desired alarm to be set (alarm 0 or alarm 1)
 * @param trigger       Desired trigger for the alarm
 * @param time          Desired alarm time to be set
 *
 * @description This function sets the desired alarm.
 */
void rtc6_set_alarm ( rtc6_t *ctx, uint8_t alarm, uint8_t trigger, rtc6_time_t *time );

/**
 * @brief Disables the alarm
 *
 * @param ctx           Click object.
 * @param alarm         Desired alarm to be disabled (alarm 0 or alarm 1)
 *
 * @description This function disables the alarm.
 */
void rtc6_disable_alarm ( rtc6_t *ctx, uint8_t alarm );

/**
 * @brief Reads the alarm time
 *
 * @param ctx           Click object.
 * @param alarm         Desired alarm to be read (alarm 0 or alarm 1)
 * @param get_alarm     Struct in which Alarm time values will be stored
 *
 * @description This function reads the alarm time.
 */
void rtc6_read_alarm ( rtc6_t *ctx, uint8_t alarm, rtc6_time_t *get_alarm );

/**
 * @brief Check if the alarm is activated
 *
 * @param ctx           Click object.
 *
 * @retval 0 - if not active alarm or 1 - if active alarm
 *
 * @description This function checks if the alarm is activated by checking the state of the int_pin pin.
 */
uint8_t rtc6_is_active_alarm( rtc6_t *ctx );

/**
 * @brief Repeat Alarm
 *
 * @param ctx           Click object.
 * @param alarm         Desired alarm to be read (alarm 0 or alarm 1)
 * @param sec           Number of seconds for which the alarm will repeat
 *
 * @description This funtion sets up repeats for the alarm.
 */
void rtc6_repeat_alarm ( rtc6_t *ctx, uint8_t alarm, uint32_t sec );

/**
 * @brief Writes data to the SRAM
 *
 * @param ctx           Click object.
 * @param addr          Address of the desired register
 * @param data_in       Data to be written
 *
 * @description This function writes data to the SRAM registers of the RTC
 */
void rtc6_write_sram ( rtc6_t *ctx, uint8_t addr, uint8_t data_in );

/**
 * @brief Reads data from an SRAM
 *
 * @param ctx           Click object.
 * @param addr          Register address
 *
 * @retval read data byte
 *
 * @description This function reads data from an SRAM register
 */
uint8_t rtc6_read_sram ( rtc6_t *ctx, uint8_t addr );

/**
 * @brief Write protect on
 *
 * @param ctx           Click object.
 *
 * @description This function turns EEPROM write protection on.
 */
void rtc6_write_eeprom_protect_on ( rtc6_t *ctx );

/**
 * @brief Write protect off
 *
 * @param ctx           Click object.
 *
 * @description This function turns EEPROM write protection off.
 */
void rtc6_write_eeprom_protect_off ( rtc6_t *ctx );

/**
 * @brief Lock check function
 *
 * @param ctx           Click object.
 *
 * @description This function checks if EEPROM is locked.
 */
uint8_t rtc6_eeprom_is_locked ( rtc6_t *ctx );

/**
 * @brief Writes data to EEPROM
 *
 * @param ctx           Click object.
 * @param addr          Address from where to start writing
 * @param data_in       Data to be written
 * @param data_size     Number of bytes to be written
 *
 * @description This function writes data to EEPROM registers of RTC
 */
void rtc6_write_eeprom ( rtc6_t *ctx, uint8_t addr, uint8_t *data_in, uint8_t data_size );

/**
 * @brief Reads data from EEPROM
 *
 * @param ctx           Click object.
 * @param addr          Address from where to start reading
 * @param data_out      Variable which will hold the read data
 * @param data_size     Number of bytes to be read
 *
 * @description This functiom reads data from EEPROM registers of the RTC
 */
void rtc6_read_eeprom ( rtc6_t *ctx, uint8_t addr, uint8_t *data_out, uint8_t data_size );

/**
 * @brief Reads unique ID
 *
 * @param ctx           Click object.
 *
 * @retval  unique ID (8 bytes)
 *
 * @description This funciton reads unique ID from EEPROM registers of the RTC
 */
void rtc6_read_unique_id ( rtc6_t *ctx, uint8_t *unique_id );

#ifdef __cplusplus
}
#endif
#endif  // _RTC6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------- END
