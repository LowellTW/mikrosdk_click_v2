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
 * @file c4glteatt.h
 * @brief This file contains API for 4G LTE-ATT Click Driver.
 */

#ifndef C4GLTEATT_H
#define C4GLTEATT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup c4glteatt 4G LTE-ATT Click Driver
 * @brief API for configuring and manipulating 4G LTE-ATT Click driver.
 * @{
 */

/**
 * @defgroup c4glteatt_set 4G LTE-ATT Device Settings
 * @brief Settings for registers of 4G LTE-ATT Click driver.
 */

/**
 * @addtogroup c4glteatt_set
 * @{
 */

/**
 * @brief 4G LTE-ATT description setting.
 * @details Specified setting for description of 4G LTE-ATT Click driver.
 */
#define C4GLTEATT_CMD_AT          "AT"
#define C4GLTEATT_CMD_ATI         "ATI"
#define C4GLTEATT_CMD_CGMR        "AT+CGMR"
#define C4GLTEATT_CMD_CFUN        "AT+CFUN"
#define C4GLTEATT_CMD_CREG        "AT+CREG"
#define C4GLTEATT_CMD_CGREG       "AT+CGREG"
#define C4GLTEATT_CMD_CGDCONT     "AT+CGDCONT"
#define C4GLTEATT_CMD_CIMI        "AT+CIMI"
#define C4GLTEATT_CMD_CMEE        "AT+CMEE"
#define C4GLTEATT_CMD_CGATT       "AT+CGATT"
#define C4GLTEATT_CMD_CSQ         "AT+CSQ"
#define C4GLTEATT_CMD_COPS        "AT+COPS"
#define C4GLTEATT_CMD_CMGS        "AT+CMGS"
#define C4GLTEATT_CMD_CMGF        "AT+CMGF"
/**
 * @brief 4G LTE-ATT driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE      256
#define DRV_TX_BUFFER_SIZE      256

/*! @} */ // c4glteatt_set

/**
 * @defgroup c4glteatt_map 4G LTE-ATT MikroBUS Map
 * @brief MikroBUS pin mapping of 4G LTE-ATT Click driver.
 */

/**
 * @addtogroup c4glteatt_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4G LTE-ATT Click to the selected MikroBUS.
 */
#define C4GLTEATT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // c4glteatt_map
/*! @} */ // c4glteatt

/**
 * @brief 4G LTE-ATT Click context object.
 * @details Context object definition of 4G LTE-ATT Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwk;     
    digital_out_t rts;     

    // Input pins
    digital_in_t sta;         
    digital_in_t ring;      
    digital_in_t cts;    

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} c4glteatt_t;

/**
 * @brief 4G LTE-ATT Click configuration object.
 * @details Configuration object definition of 4G LTE-ATT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t sta;  
    pin_name_t pwk;      
    pin_name_t rts;    
    pin_name_t ring;     
    pin_name_t cts;       

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} c4glteatt_cfg_t;

/**
 * @brief 4G LTE-ATT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   C4GLTEATT_OK = 0,
   C4GLTEATT_ERROR = -1

} c4glteatt_return_value_t;

/*!
 * @addtogroup c4glteatt 4G LTE-ATT Click Driver
 * @brief API for configuring and manipulating 4G LTE-ATT Click driver.
 * @{
 */

/**
 * @brief 4G LTE-ATT configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c4glteatt_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c4glteatt_cfg_setup ( c4glteatt_cfg_t *cfg );

/**
 * @brief 4G LTE-ATT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c4glteatt_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glteatt_init ( c4glteatt_t *ctx, c4glteatt_cfg_t *cfg );

/**
 * @brief Power ON the module function.
 * @details This function powers ON the module.
 * @param[out] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_module_power_on ( c4glteatt_t *ctx );

/**
 * @brief 4G LTE-ATT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glteatt_generic_write ( c4glteatt_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief 4G LTE-ATT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glteatt_generic_read ( c4glteatt_t *ctx, char *data_buf, uint16_t max_len );


/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void c4glteatt_set_rts_pin ( c4glteatt_t *ctx, uint8_t state );

/**
 * @brief Sets state of the PWK pin.
 * @details This function sets PWK pin state.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void c4glteatt_set_pwk_pin ( c4glteatt_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function.
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 * @note None.
 */
uint8_t c4glteatt_get_cts_pin ( c4glteatt_t *ctx );

/**
 * @brief STA Pin Get function.
 * @details This function allows user to check state of the STA pin.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 * @note None.
 */
uint8_t c4glteatt_get_sta_pin ( c4glteatt_t *ctx );

/**
 * @brief RING Pin Get function.
 * @details This function allows user to check state of the RING pin.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 * @note None.
 */
uint8_t c4glteatt_get_ring_pin ( c4glteatt_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_send_cmd ( c4glteatt_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_send_cmd_with_parameter ( c4glteatt_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_send_cmd_check ( c4glteatt_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_send_cmd_parameter_check ( c4glteatt_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_set_sim_apn ( c4glteatt_t *ctx, char *sim_apn );

/**
 * @brief 4G LTE-ATT send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c4glteatt_send_sms_text ( c4glteatt_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief 4G LTE-ATT send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c4glteatt_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glteatt_send_sms_pdu ( c4glteatt_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // C4GLTEATT_H

/*! @} */ // c4glteatt

// ------------------------------------------------------------------------ END
