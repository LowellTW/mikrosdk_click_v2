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
 * @file rs4855v.h
 * @brief This file contains API for RS485 5V Click Driver.
 */

#ifndef RS4855V_H
#define RS4855V_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup rs4855v RS485 5V Click Driver
 * @brief API for configuring and manipulating RS485 5V Click driver.
 * @{
 */

/**
 * @defgroup rs4855v_set RS485 5V Device Settings
 * @brief Settings for registers of RS485 5V Click driver.
 */

/**
 * @addtogroup rs4855v_set
 * @{
 */

/**
 * @brief RS485 5V driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // rs4855v_set

/**
 * @defgroup rs4855v_map RS485 5V MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 5V Click driver.
 */

/**
 * @addtogroup rs4855v_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 5V Click to the selected MikroBUS.
 */
#define RS4855V_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rw = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // rs4855v_map
/*! @} */ // rs4855v

/**
 * @brief RS485 5V Click context object.
 * @details Context object definition of RS485 5V Click driver.
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

} rs4855v_t;

/**
 * @brief RS485 5V Click configuration object.
 * @details Configuration object definition of RS485 5V Click driver.
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

} rs4855v_cfg_t;

/**
 * @brief RS485 5V Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RS4855V_OK = 0,
   RS4855V_ERROR = -1

} rs4855v_return_value_t;

/*!
 * @addtogroup rs4855v RS485 5V Click Driver
 * @brief API for configuring and manipulating RS485 5V Click driver.
 * @{
 */

/**
 * @brief RS485 5V configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs4855v_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs4855v_cfg_setup ( rs4855v_cfg_t *cfg );

/**
 * @brief RS485 5V initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs4855v_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs4855v_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4855v_init ( rs4855v_t *ctx, rs4855v_cfg_t *cfg );

/**
 * @brief RS485 5V data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4855v_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Nothing.
 * @note None.
 */
void rs4855v_generic_write ( rs4855v_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief RS485 5V data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4855v_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4855v_generic_read ( rs4855v_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command
 * @details This function sends a command by using UART serial interface.
 * @param ctx          Click object.
 * @param command      Command to be sent.
 */
void rs4855v_send_command ( rs4855v_t *ctx, char *command );
#ifdef __cplusplus
}
#endif
#endif // RS4855V_H

/*! @} */ // rs4855v

// ------------------------------------------------------------------------ END
