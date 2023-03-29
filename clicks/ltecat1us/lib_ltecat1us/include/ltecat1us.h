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
 * @file ltecat1us.h
 * @brief This file contains API for LTE Cat.1-US Click Driver.
 */

#ifndef LTECAT1US_H
#define LTECAT1US_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup ltecat1us LTE Cat.1-US Click Driver
 * @brief API for configuring and manipulating LTE Cat.1-US Click driver.
 * @{
 */


/**
 * @defgroup ltecat1us_set LTE Cat.1-US Device Settings
 * @brief Settings for registers of LTE Cat.1-US Click driver.
 */

/**
 * @addtogroup ltecat1us_set
 * @{
 */

/**
 * @brief LTE Cat.1-US description setting.
 * @details Specified setting for description of LTE Cat.1-US Click driver.
 */
#define LTECAT1US_CMD_AT          "AT"
#define LTECAT1US_CMD_ATI         "ATI"
#define LTECAT1US_CMD_CGMR        "AT+CGMR"

#define LTECAT1US_CMD_CFUN        "AT+CFUN"
#define LTECAT1US_CMD_CREG        "AT+CREG"
#define LTECAT1US_CMD_CEREG       "AT+CEREG"
#define LTECAT1US_CMD_CGDCONT     "AT+CGDCONT"
#define LTECAT1US_CMD_CIMI        "AT+CIMI"
#define LTECAT1US_CMD_CGATT       "AT+CGATT"
#define LTECAT1US_CMD_CSQ         "AT+CSQ"
#define LTECAT1US_CMD_CESQ        "AT+CESQ"
#define LTECAT1US_CMD_COPS        "AT+COPS"


/**
 * @brief LTE Cat.1-US driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 100

/*! @} */ // ltecat1us_set

/**
 * @defgroup ltecat1us_map LTE Cat.1-US MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1-US Click driver.
 */

/**
 * @addtogroup ltecat1us_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1-US Click to the selected MikroBUS.
 */
#define LTECAT1US_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ltecat1us_map
/*! @} */ // ltecat1us

/**
 * @brief LTE Cat.1-US Click context object.
 * @details Context object definition of LTE Cat.1-US Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;   
    digital_out_t cs;    
    digital_out_t rts;  

    // Input pins
    digital_in_t cts;      

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} ltecat1us_t;

/**
 * @brief LTE Cat.1-US Click configuration object.
 * @details Configuration object definition of LTE Cat.1-US Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
   //pin_name_t an;         
    pin_name_t rst;       
    pin_name_t cts;   
    pin_name_t cs;    
    pin_name_t rts;      
    
    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} ltecat1us_cfg_t;

/**
 * @brief LTE Cat.1-US Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LTECAT1US_OK = 0,
   LTECAT1US_ERROR = -1

} ltecat1us_return_value_t;

/*!
 * @addtogroup ltecat1us LTE Cat.1-US Click Driver
 * @brief API for configuring and manipulating LTE Cat.1-US Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1-US configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat1us_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat1us_cfg_setup ( ltecat1us_cfg_t *cfg );

/**
 * @brief LTE Cat.1-US initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat1us_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat1us_init ( ltecat1us_t *ctx, ltecat1us_cfg_t *cfg );

/**
 * @brief LTE Cat.1-US data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Nothing.
 * 
 * @note None.
 */
void ltecat1us_generic_write ( ltecat1us_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE Cat.1-US data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat1us_generic_read ( ltecat1us_t *ctx, char *data_buf, uint16_t max_len );


/**
 * @brief LTE Cat.1-US module power on.
 * @details This function resets the chip on LTE Cat.1-US click.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @return Nothing.
 */
void ltecat1us_power_on ( ltecat1us_t *ctx );

/**
 * @brief Sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void ltecat1us_set_rst ( ltecat1us_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void ltecat1us_set_rts ( ltecat1us_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t ltecat1us_get_cts ( ltecat1us_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void ltecat1us_send_cmd ( ltecat1us_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void ltecat1us_send_cmd_with_parameter ( ltecat1us_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void ltecat1us_send_cmd_check ( ltecat1us_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void ltecat1us_send_cmd_parameter_check ( ltecat1us_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void ltecat1us_set_sim_apn ( ltecat1us_t *ctx, char *sim_apn );

/**
 * @brief LTE Cat.1-US send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat1us_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void ltecat1us_send_text_message ( ltecat1us_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif // LTECAT1US_H

/*! @} */ // ltecat1us

// ------------------------------------------------------------------------ END
