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
 * @file rs2323.h
 * @brief This file contains API for RS232 3 Click Driver.
 */

#ifndef RS2323_H
#define RS2323_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup rs2323 RS232 3 Click Driver
 * @brief API for configuring and manipulating RS232 3 Click driver.
 * @{
 */

/**
 * @defgroup rs2323_cmd RS232 3 Device Settings
 * @brief Settings of RS232 3 Click driver.
 */

/**
 * @addtogroup rs2323_cmd
 * @{
 */

/**
 * @brief RS232 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // rs2323_cmd

/**
 * @defgroup rs2323_map RS232 3 MikroBUS Map
 * @brief MikroBUS pin mapping of RS232 3 Click driver.
 */

/**
 * @addtogroup rs2323_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS232 3 Click to the selected MikroBUS.
 */
#define RS2323_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rs2323_map
/*! @} */ // rs2323

/**
 * @brief RS232 3 Click context object.
 * @details Context object definition of RS232 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;                          /**< Shutdown pin. */
    digital_out_t en;                           /**< Enable pin. */
    digital_out_t on;                           /**< Online pin. */

    // Input pins
    digital_in_t sta;                           /**< Status pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} rs2323_t;

/**
 * @brief RS232 3 Click configuration object.
 * @details Configuration object definition of RS232 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t shd;                             /**< Shutdown pin. */
    pin_name_t en;                              /**< Enable pin. */
    pin_name_t on;                              /**< Online pin. */
    pin_name_t sta;                             /**< Status pin. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} rs2323_cfg_t;

/**
 * @brief RS232 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS2323_OK = 0,
    RS2323_ERROR = -1

} rs2323_return_value_t;

/*!
 * @addtogroup rs2323 RS232 3 Click Driver
 * @brief API for configuring and manipulating RS232 3 Click driver.
 * @{
 */

/**
 * @brief RS232 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs2323_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs2323_cfg_setup ( rs2323_cfg_t *cfg );

/**
 * @brief RS232 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs2323_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs2323_init ( rs2323_t *ctx, rs2323_cfg_t *cfg );

/**
 * @brief RS232 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs2323_generic_write ( rs2323_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief RS232 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs2323_generic_read ( rs2323_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief RS232 3 set shutdown pin function.
 * @details This function sets the shutdown (SHD) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rs2323_set_shutdown_pin ( rs2323_t *ctx, uint8_t state );

/**
 * @brief RS232 3 set enable pin function.
 * @details This function sets the enable (EN) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rs2323_set_enable_pin ( rs2323_t *ctx, uint8_t state );

/**
 * @brief RS232 3 set online pin function.
 * @details This function sets the online (ON) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rs2323_set_online_pin ( rs2323_t *ctx, uint8_t state );

/**
 * @brief RS232 3 get status pin function.
 * @details This function returns the status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs2323_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rs2323_get_status_pin ( rs2323_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RS2323_H

/*! @} */ // rs2323

// ------------------------------------------------------------------------ END
