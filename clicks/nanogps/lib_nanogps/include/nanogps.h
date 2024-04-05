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
 * \brief This file contains API for Nano GPS Click driver.
 *
 * \addtogroup nanogps Nano GPS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOGPS_H
#define NANOGPS_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

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
#define NANOGPS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NANOGPS_RETVAL  uint8_t

#define NANOGPS_OK           0x00
#define NANOGPS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define NANOGPS_NEMA_GPGGA 1
#define NANOGPS_NEMA_GPGLL 3
#define NANOGPS_NEMA_GPGGA_NUM_ELEMENT 15
#define NANOGPS_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define NANOGPS_GPGGA_TIME                      1 
#define NANOGPS_GPGGA_LATITUDE                  2
#define NANOGPS_GPGGA_LATITUDE_SIDE             3
#define NANOGPS_GPGGA_LONGITUDE                 4
#define NANOGPS_GPGGA_LONGITUDE_SIDE            5
#define NANOGPS_GPGGA_QUALITY_INDICATOR         6
#define NANOGPS_GPGGA_NUMBER_OF_SATELLITES      7
#define NANOGPS_GPGGA_H_DILUTION_OF_POS         8
#define NANOGPS_GPGGA_ALTITUDE                  9
#define NANOGPS_GPGGA_ALTITUDE_UNIT             10
#define NANOGPS_GPGGA_GEOIDAL_SEPARATION        11
#define NANOGPS_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define NANOGPS_GPGGA_TIME_SINCE_LAST_DGPS      13
#define NANOGPS_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define NANOGPS_GPGLL_LATITUDE                  1
#define NANOGPS_GPGLL_LATITUDE_SIDE             2
#define NANOGPS_GPGLL_LONGITUDE                 3
#define NANOGPS_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define NANOGPS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define NANOGPS_ERROR_START_OR_END_COMMAND 0x8F
#define NANOGPS_ERROR_NEXT_ELEMENT         0x4F
#define NANOGPS_ERROR_CURRENT_ELEMENT      0x2F
#define NANOGPS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define NANOGPS_DRV_RX_BUFFER_SIZE 500
#define NANOGPS_DRV_TX_BUFFER_SIZE 100
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

    digital_out_t rst;
    digital_out_t pwr;

    // Input pins 

    digital_in_t wkp;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ NANOGPS_DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ NANOGPS_DRV_TX_BUFFER_SIZE ];

} nanogps_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t wkp;
    pin_name_t rst;
    pin_name_t pwr;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} nanogps_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t nanogps_error_t;

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
void nanogps_cfg_setup ( nanogps_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param nanogps Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NANOGPS_RETVAL nanogps_init ( nanogps_t *ctx, nanogps_cfg_t *cfg );

/**
 * @brief Wake-up module.
 * @param nanogps Click object.
 */
void nanogps_module_wakeup ( nanogps_t *ctx );

/**
 * @brief Set PWR ( powerS ) pin state.
 * @param nanogps Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void nanogps_set_pwr_pin ( nanogps_t *ctx, uint8_t state );

/**
 * @brief Set RST ( reset ) pin state.
 * @param nanogps Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void nanogps_set_rst_pin ( nanogps_t *ctx, uint8_t state );

/**
 * @brief Get WKP pin state.
 * @param nanogps Click object.
 * @return current pin state.
 */
uint8_t nanogps_get_wkp_pin ( nanogps_t *ctx );

/**
 * @brief Generic write function.
 * @param nanogps Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void nanogps_generic_write ( nanogps_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param nanogps Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t nanogps_generic_read ( nanogps_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param nanogps Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
nanogps_error_t nanogps_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _NANOGPS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
