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
 * \brief This file contains API for Fan 3 Click driver.
 *
 * \addtogroup fan3 Fan 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FAN3_H
#define FAN3_H

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
#define FAN3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FAN3_RETVAL  uint8_t

#define FAN3_OK                    0x00
#define FAN3_INIT_ERROR            0xFF
/** \} */

/**
 * \defgroup speed  Speed
 * \{
 */
#define FAN3_STOPPED               0x00
#define FAN3_SPEED1                0x01
#define FAN3_SPEED2                0x02
#define FAN3_SPEED3                0x03
#define FAN3_SPEED4                0x04
#define FAN3_SPEED5                0x05
#define FAN3_SPEED6                0x06
#define FAN3_SPEED7                0x07
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{   
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} fan3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} fan3_cfg_t;

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
void fan3_cfg_setup ( fan3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FAN3_RETVAL fan3_init ( fan3_t *ctx, fan3_cfg_t *cfg );

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
void fan3_generic_write ( fan3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void fan3_generic_read ( fan3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set speed
 *
 * @param ctx          Click object.
 * @param new_speed    Speed to be set
 *
 * @description Sets the fan speed to a desired value, including 0 - stopped.
 */
void fan3_set_speed ( fan3_t *ctx, uint8_t new_speed );

#ifdef __cplusplus
}
#endif
#endif  // _FAN3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
