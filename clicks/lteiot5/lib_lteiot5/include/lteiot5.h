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
 * @file lteiot5.h
 * @brief This file contains API for LTE IoT 5 Click Driver.
 */

#ifndef LTEIOT5_H
#define LTEIOT5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot5 LTE IoT 5 Click Driver
 * @brief API for configuring and manipulating LTE IoT 5 Click driver.
 * @{
 */

/**
 * @defgroup lteiot5_reg LTE IoT 5 Commands List
 * @brief List of commands of LTE IoT 5 Click driver.
 */

/**
 * @addtogroup lteiot5_reg
 * @{
 */

/**
 * @brief LTE IoT 5 description register.
 * @details Specified register for description of LTE IoT 5 Click driver.
 */
// TODO -- dodati makroe koji definisu adrese registara

/*! @} */ // lteiot5_reg

/**
 * @defgroup lteiot5_set LTE IoT 5 Device Settings
 * @brief Settings for registers of LTE IoT 5 Click driver.
 */

/**
 * @addtogroup lteiot5_set
 * @{
 */

/**
 * @brief LTE IoT 5 description setting.
 * @details Specified setting for description of LTE IoT 5 Click driver.
 */
#define LTEIOT5_CMD_AT          "AT"
#define LTEIOT5_CMD_ATI         "ATI"
#define LTEIOT5_CMD_CGMR        "AT+CGMR"

#define LTEIOT5_CMD_CFUN        "AT+CFUN"
#define LTEIOT5_CMD_CREG        "AT+CREG"
#define LTEIOT5_CMD_CEREG       "AT+CEREG"
#define LTEIOT5_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT5_CMD_CIMI        "AT+CIMI"
#define LTEIOT5_CMD_CGATT       "AT+CGATT"
#define LTEIOT5_CMD_CSQ         "AT+CSQ"
#define LTEIOT5_CMD_CESQ        "AT+CESQ"
#define LTEIOT5_CMD_COPS        "AT+COPS"
#define LTEIOT5_CMD_URAT        "AT+URAT"
#define LTEIOT5_CMD_UBANDMASK   "AT+UBANDMASK"
#define LTEIOT5_CMD_URATCONF    "AT+URATCONF"
#define LTEIOT5_CMD_UAUTHREQ    "AT+UAUTHREQ"
#define LTEIOT5_CMD_UUICC       "AT+UUICC"
#define LTEIOT5_CMD_UCGED       "AT+UCGED"
#define LTEIOT5_CMD_UCELLINFO   "AT+UCELLINFO"
#define LTEIOT5_CMD_UANTR       "AT+UANTR"

// "AT+CGMR"

/**
 * @brief LTE IoT 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE                     500
#define DRV_TX_BUFFER_SIZE                     150

/*! @} */ // lteiot5_set

/**
 * @defgroup lteiot5_map LTE IoT 5 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 5 Click driver.
 */

/**
 * @addtogroup lteiot5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 5 Click to the selected MikroBUS.
 */
#define LTEIOT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot5_map
/*! @} */ // lteiot5

/**
 * @brief LTE IoT 5 Click context object.
 * @details Context object definition of LTE IoT 5 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t pwr;       /**< Description. */
    digital_out_t rst;     /**< Description. */
    digital_out_t rts;       /**< Description. */

    // Input pins

    digital_in_t ri;       /**< Description. */
    digital_in_t cts;       /**< Description. */

    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} lteiot5_t;

/**
 * @brief LTE IoT 5 Click configuration object.
 * @details Configuration object definition of LTE IoT 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins

    pin_name_t pwr;          /**< Description. */
    pin_name_t rst;        /**< Description. */
    pin_name_t rts;          /**< Description. */
    pin_name_t ri;        /**< Description. */
    pin_name_t cts;        /**< Description. */

    // Static variable

    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} lteiot5_cfg_t;

/*!
 * @addtogroup lteiot5 LTE IoT 5 Click Driver
 * @brief API for configuring and manipulating LTE IoT 5 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot5_cfg_setup ( lteiot5_cfg_t *cfg );

/**
 * @brief LTE IoT 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_init ( lteiot5_t *ctx, lteiot5_cfg_t *cfg );

/**
 * @brief LTE IoT 5 default configuration function.
 * @details This function executes a default configuration of LTE IoT 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lteiot5_default_cfg ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_generic_write ( lteiot5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_generic_read ( lteiot5_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief LTE IoT 5 power on.
 * @details This function resets the chip on LTE IoT 5 click.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return Nothing.
 */
void lteiot5_power_on ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 power on.
 * @details This function resets the chip on LTE IoT 5 click.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return Nothing.
 */
void lteiot5_reset ( lteiot5_t *ctx );

/**
 * @brief Sets state of the PWR pin.
 * @details This function sets PWR pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot5_set_pwr ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot5_set_rst ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot5_set_rts ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief RI Pin Get function
 * @details This function allows user to check state of the RI pin.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t lteiot5_get_ri ( lteiot5_t *ctx );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t lteiot5_get_cts ( lteiot5_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void lteiot5_send_cmd ( lteiot5_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void lteiot5_send_cmd_with_parameter ( lteiot5_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void lteiot5_send_cmd_check ( lteiot5_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void lteiot5_send_cmd_parameter_check ( lteiot5_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void lteiot5_set_sim_apn ( lteiot5_t *ctx, char *sim_apn );

/**
 * @brief LTE IoT 5 send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void lteiot5_send_text_message ( lteiot5_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT5_H

/*! @} */ // lteiot5

// ------------------------------------------------------------------------ END
