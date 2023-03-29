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
 * \brief This file contains API for Charger 13 Click driver.
 *
 * \addtogroup charger13 Charger 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CHARGER13_H
#define CHARGER13_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CHARGER13_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER13_RETVAL  uint8_t

#define CHARGER13_OK           0x00
#define CHARGER13_INIT_ERROR   0xFF
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
    // Output pins 

    digital_out_t en;

    // Input pins 

    digital_in_t int_pin;

} charger13_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

} charger13_cfg_t;

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
void charger13_cfg_setup ( charger13_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param charger13 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CHARGER13_RETVAL charger13_init ( charger13_t *ctx, charger13_cfg_t *cfg );

/**
 * @brief Enabled charging function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable battery charging
 * by cleared to LOW state of the EN ( PWM ) pin
 * of the Charger 13 click board.
 */
void charger13_enable ( charger13_t *ctx );

/**
 * @brief Disabled charging function.
 *
 * @param ctx  Click object.
 *
 * @description This function disable battery charging
 * by sets to HIGH state of the EN ( PWM ) pin
 * of the Charger 13 click board.
 */
void charger13_disable ( charger13_t *ctx );

/**
 * @brief Check battery charging function.
 *
 * @param ctx  Click object.
 *
 * @description This function check if the battery is charging
 * of the Charger 13 click board.
 */
uint8_t charger13_check ( charger13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CHARGER13_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
