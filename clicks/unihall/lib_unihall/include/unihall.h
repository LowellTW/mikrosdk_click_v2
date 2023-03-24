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
 * \brief This file contains API for UNI HALL Click driver.
 *
 * \addtogroup unihall UNI HALL Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UNIHALL_H
#define UNIHALL_H

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
#define UNIHALL_MAP_MIKROBUS( cfg, mikrobus )    \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UNIHALL_RETVAL  uint8_t

#define UNIHALL_OK           0x00
#define UNIHALL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup int_state Detecting north pole magnetic fields status
 * \{
 */
#define UNIHALL_RETVAL  uint8_t

#define UNIHALL_NORTH_POLE_DETECTED           0x00
#define UNIHALL_NORTH_POLE_NOT_DETECTED       0x01
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
    // Input pins 

    digital_in_t int_pin;

} unihall_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t int_pin;

} unihall_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void unihall_cfg_setup ( unihall_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param unihall Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UNIHALL_RETVAL unihall_init ( unihall_t *ctx, unihall_cfg_t *cfg );

/**
 * @brief Detecting north pole magnetic fields status function.
 *
 * @param ctx  Click object.
 *
 * @return State of INT pin:
 * <pre> 0 - detected; </pre>
 * <pre> 1 - not detected; </pre>
 *
 * @description This function detecting north pole magnetic fields status
 * and returns the state of the INT pin.
 * INT pin can be configured to show are data registers updated 
 * with the new values or not.
 */
uint8_t unihall_detecting_magnetic_fields ( unihall_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _UNIHALL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
