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
 * \brief This file contains API for Ir Eclipse Click driver.
 *
 * \addtogroup ireclipse Ir Eclipse Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRECLIPSE_H
#define IRECLIPSE_H

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
#define IRECLIPSE_MAP_MIKROBUS( cfg, mikrobus )    \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRECLIPSE_RETVAL  uint8_t

#define IRECLIPSE_OK           0x00
#define IRECLIPSE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup int_state State of INT pin beam  is ( or not ) eclipsed.
 * \{
 */

#define IRECLIPSE_LOW              0
#define IRECLIPSE_HIGH             1
/** \} */

/**
 * \defgroup start_cnt Start conting value.
 * \{
 */

#define IRECLIPSE_START_CNT_VAL    0
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

} ireclipse_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
  // Additional gpio pins 

  pin_name_t int_pin;

} ireclipse_cfg_t;

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
void ireclipse_cfg_setup ( ireclipse_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ireclipse Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRECLIPSE_RETVAL ireclipse_init ( ireclipse_t *ctx, ireclipse_cfg_t *cfg );

/**
 * @brief Detecting states of IR beam from EE-SX198 photo interrupter sensor
 *
 * @param ctx  Click object.
 *
 * @return State of INT pin:
 * <pre> 0 : beam not eclipsed;</pre>
 * <pre> 1 : beam is eclipsed;</pre>
 *
 * Function states of IR beam from EE-SX198 photo interrupter sensor,
 * ( eclipsed or not eclipsed ) and returns the state of the INT pin.
 */
uint8_t ireclipse_int_status ( ireclipse_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRECLIPSE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
