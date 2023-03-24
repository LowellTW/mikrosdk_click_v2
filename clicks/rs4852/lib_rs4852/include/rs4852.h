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
 * \brief This file contains API for RS485 2 Click driver.
 *
 * \addtogroup rs4852 RS485 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS4852_H
#define RS4852_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RS4852_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.de      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.re      = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS4852_RETVAL  uint8_t

#define RS4852_OK           0x00
#define RS4852_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup driver_output_enable  Driver Output Enable
 * \{
 */
#define RS4852_ENABLE_DE      0x01
#define RS4852_DISABLE_DE     0x00
/** \} */

/**
 * \defgroup receiver_enable  Receiver Enable
 * \{
 */
#define RS4852_ENABLE_RE      0x00
#define RS4852_DISABLE_RE     0x01
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

    digital_out_t de;
    digital_out_t re;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rs4852_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t de;
    pin_name_t re;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs4852_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rs4852_error_t;

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
void rs4852_cfg_setup ( rs4852_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rs4852 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS4852_RETVAL rs4852_init ( rs4852_t *ctx, rs4852_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param rs4852 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs4852_generic_write ( rs4852_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param rs4852 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t rs4852_generic_read ( rs4852_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set DE ( cs ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs4852_set_de_pin ( rs4852_t *ctx, uint8_t state );

/**
 * @brief Set RE ( reset ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs4852_set_re_pin ( rs4852_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _RS4852_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
