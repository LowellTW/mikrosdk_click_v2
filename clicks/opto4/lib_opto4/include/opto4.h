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
 * \brief This file contains API for OPTO 4 Click driver.
 *
 * \addtogroup opto4 OPTO 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTO4_H
#define OPTO4_H

#include "drv_digital_out.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define OPTO4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.cs= MIKROBUS( mikrobus, MIKROBUS_CS ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTO4_RETVAL  uint8_t

#define OPTO4_OK           0x00
#define OPTO4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup status  Status
 * \{
 */
#define OPTO4_OUTPUT_ENABLE   0x01
#define OPTO4_OUTPUT_DISABLE  0x00
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

    digital_out_t cs;

} opto4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t cs;

} opto4_cfg_t;

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
void opto4_cfg_setup ( opto4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param opto4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OPTO4_RETVAL opto4_init ( opto4_t *ctx, opto4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for OPTO 4 click.
 */
void opto4_default_cfg ( opto4_t *ctx );

/**
 * @brief Function for output enable or disable
 *
 * @param ctx      Click object.
 * @param enable   Enable 
 *
 * @description This function sets the status enabled or disabled.
 */
void opto4_output_enable ( opto4_t *ctx, uint8_t enable );

#ifdef __cplusplus
}
#endif
#endif  // _OPTO4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
