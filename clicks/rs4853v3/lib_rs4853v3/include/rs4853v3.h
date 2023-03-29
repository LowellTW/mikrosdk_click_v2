/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file rs4853v3.h
 * @brief This file contains API for RS485 3V3 Click Driver.
 */

#ifndef RS4853V3_H
#define RS4853V3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup rs4853v3 RS485 3V3 Click Driver
 * @brief API for configuring and manipulating RS485 3V3 Click driver.
 * @{
 */

/**
 * @defgroup rs4853v3_set RS485 3V3 Device Settings
 * @brief Settings for registers of RS485 3V3 Click driver.
 */

/**
 * @addtogroup rs4853v3_set
 * @{
 */

/**
 * @brief RS485 3V3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // rs4853v3_set

/**
 * @defgroup rs4853v3_map RS485 3V3 MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 3V3 Click driver.
 */

/**
 * @addtogroup rs4853v3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 3V3 Click to the selected MikroBUS.
 */
#define RS4853V3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rw = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // rs4853v3_map
/*! @} */ // rs4853v3

/**
 * @brief RS485 3V3 Click context object.
 * @details Context object definition of RS485 3V3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t rw;  

    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];       
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         

} rs4853v3_t;

/**
 * @brief RS485 3V3 Click configuration object.
 * @details Configuration object definition of RS485 3V3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins

    pin_name_t rw;        

    // Static variable

    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} rs4853v3_cfg_t;

/**
 * @brief RS485 3V3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RS4853V3_OK = 0,
   RS4853V3_ERROR = -1

} rs4853v3_return_value_t;

/*!
 * @addtogroup rs4853v3 RS485 3V3 Click Driver
 * @brief API for configuring and manipulating RS485 3V3 Click driver.
 * @{
 */

/**
 * @brief RS485 3V3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs4853v3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs4853v3_cfg_setup ( rs4853v3_cfg_t *cfg );

/**
 * @brief RS485 3V3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs4853v3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs4853v3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4853v3_init ( rs4853v3_t *ctx, rs4853v3_cfg_t *cfg );

/**
 * @brief RS485 3V3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4853v3_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Nothing.
 * @note None.
 */
void rs4853v3_generic_write ( rs4853v3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief RS485 3V3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4853v3_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4853v3_generic_read ( rs4853v3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command
 * @details This function sends a command by using UART serial interface.
 * @param ctx          Click object.
 * @param command      Command to be sent.
 */
void rs4853v3_send_command ( rs4853v3_t *ctx, char *command );
#ifdef __cplusplus
}
#endif
#endif // RS4853V3_H

/*! @} */ // rs4853v3

// ------------------------------------------------------------------------ END
