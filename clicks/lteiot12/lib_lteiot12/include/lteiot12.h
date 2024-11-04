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
 * @file lteiot12.h
 * @brief This file contains API for LTE IoT 12 Click Driver.
 */

#ifndef LTEIOT12_H
#define LTEIOT12_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup lteiot12 LTE IoT 12 Click Driver
 * @brief API for configuring and manipulating LTE IoT 12 Click driver.
 * @{
 */

/**
 * @defgroup lteiot12_cmd LTE IoT 12 Device Settings
 * @brief Settings for registers of LTE IoT 12 Click driver.
 */

/**
 * @addtogroup lteiot12_cmd
 * @{
 */

/**
 * @brief LTE IoT 12 control commands.
 * @details Specified setting for control commands of LTE IoT 12 Click driver.
 */
#define LTEIOT12_CMD_AT                             "AT"
#define LTEIOT12_CMD_GET_MODEL_ID                   "AT+CGMM"
#define LTEIOT12_CMD_GET_SW_VERSION                 "AT+CGMR"
#define LTEIOT12_CMD_GET_SERIAL_NUM                 "AT+CGSN"
#define LTEIOT12_CMD_FACTORY_RESET                  "AT&F"
#define LTEIOT12_CMD_SET_UE_FUNCTIONALITY           "AT+CFUN"
#define LTEIOT12_CMD_NETWORK_REGISTRATION           "AT+CREG"
#define LTEIOT12_CMD_SIGNAL_QUALITY_REPORT          "AT+CSQ"
#define LTEIOT12_CMD_OPERATOR_SELECTION             "AT+COPS"
#define LTEIOT12_CMD_SEND_SMS                       "AT+CMGS"
#define LTEIOT12_CMD_SELECT_SMS_FORMAT              "AT+CMGF"
#define LTEIOT12_CMD_DEFINE_PDP_CONTEXT             "AT+CGDCONT"
#define LTEIOT12_CMD_SHOW_PDP_ADDRESS               "AT+CGPADDR"
#define LTEIOT12_CMD_PSM_SETTING                    "AT+CPSMS"
#define LTEIOT12_CMD_ACTIVATE_PDP_CONTEXT           "AT+QIACT"
#define LTEIOT12_CMD_OPEN_SOCKET                    "AT+QIOPEN"
#define LTEIOT12_CMD_CLOSE_SOCKET                   "AT+QICLOSE"
#define LTEIOT12_CMD_SEND_DATA                      "AT+QISEND"
#define LTEIOT12_CMD_RECEIVE_DATA                   "AT+QIRD"
#define LTEIOT12_CMD_EXTENDED_CONFIG                "AT+QCFG"
#define LTEIOT12_CMD_TURN_ON_GNSS                   "AT+QGPS"
#define LTEIOT12_CMD_ACQUIRE_NMEA_SENTENCES         "AT+QGPSGNMEA"

/**
 * @brief LTE IoT 12 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT12_RSP_OK                             "OK"
#define LTEIOT12_RSP_ERROR                          "ERROR"

/**
 * @brief LTE IoT 12 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTEIOT12_URC_RECEIVED_DATA                  "+QIURC:"
#define LTEIOT12_URC_OPEN_SOCKET                    "+QIOPEN:"

/**
 * @brief LTE IoT 12 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 12 Click driver.
 */
#define LTEIOT12_RSP_START                          "$"
#define LTEIOT12_RSP_DELIMITER                      ","
#define LTEIOT12_RSP_END                            "\r\n"
#define LTEIOT12_RSP_GGA                            "GGA"

/**
 * @brief LTE IoT 12 power state settings.
 * @details Specified power state settings of LTE IoT 12 Click driver.
 */
#define LTEIOT12_POWER_STATE_OFF                    0
#define LTEIOT12_POWER_STATE_ON                     1

/**
 * @brief LTE IoT 12 GGA command elements.
 * @details Specified GGA command elements of LTE IoT 12 Click driver.
 */
#define LTEIOT12_GGA_ELEMENT_SIZE                   15
#define LTEIOT12_GGA_TIME                           1
#define LTEIOT12_GGA_LATITUDE                       2
#define LTEIOT12_GGA_LATITUDE_SIDE                  3
#define LTEIOT12_GGA_LONGITUDE                      4
#define LTEIOT12_GGA_LONGITUDE_SIDE                 5
#define LTEIOT12_GGA_QUALITY_INDICATOR              6
#define LTEIOT12_GGA_NUMBER_OF_SATELLITES           7
#define LTEIOT12_GGA_H_DILUTION_OF_POS              8
#define LTEIOT12_GGA_ALTITUDE                       9
#define LTEIOT12_GGA_ALTITUDE_UNIT                  10
#define LTEIOT12_GGA_GEOIDAL_SEPARATION             11
#define LTEIOT12_GGA_GEOIDAL_SEPARATION_UNIT        12
#define LTEIOT12_GGA_TIME_SINCE_LAST_DGPS           13
#define LTEIOT12_GGA_DGPS_REFERENCE_STATION_ID      14

/**
 * @brief LTE IoT 12 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT12_TX_DRV_BUFFER_SIZE                 256
#define LTEIOT12_RX_DRV_BUFFER_SIZE                 256

/*! @} */ // lteiot12_cmd

/**
 * @defgroup lteiot12_map LTE IoT 12 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 12 Click driver.
 */

/**
 * @addtogroup lteiot12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 12 Click to the selected MikroBUS.
 */
#define LTEIOT12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot12_map
/*! @} */ // lteiot12

/**
 * @brief LTE IoT 12 Click context object.
 * @details Context object definition of LTE IoT 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;      /**< PWRKEY pin (active low). */
    digital_out_t rts;      /**< UART Request to send pin. */

    // Input pins
    digital_in_t sta;       /**< Module operation status pin. */
    digital_in_t ring;      /**< Ring indicator pin. */
    digital_in_t cts;       /**< UART Clear to send pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTEIOT12_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT12_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTEIOT12_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lteiot12_t;

/**
 * @brief LTE IoT 12 Click configuration object.
 * @details Configuration object definition of LTE IoT 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sta;         /**< Module operation status pin. */
    pin_name_t pwr;         /**< PWRKEY pin (active low). */
    pin_name_t rts;         /**< UART Request to send pin. */
    pin_name_t ring;        /**< Ring indicator pin. */
    pin_name_t cts;         /**< UART Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} lteiot12_cfg_t;

/**
 * @brief LTE IoT 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT12_OK = 0,
    LTEIOT12_ERROR = -1,
    LTEIOT12_ERROR_TIMEOUT = -2,
    LTEIOT12_ERROR_CMD = -3,
    LTEIOT12_ERROR_UNKNOWN = -4

} lteiot12_return_value_t;

/*!
 * @addtogroup lteiot12 LTE IoT 12 Click Driver
 * @brief API for configuring and manipulating LTE IoT 12 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot12_cfg_setup ( lteiot12_cfg_t *cfg );

/**
 * @brief LTE IoT 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot12_init ( lteiot12_t *ctx, lteiot12_cfg_t *cfg );

/**
 * @brief LTE IoT 12 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot12_generic_write ( lteiot12_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 12 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot12_generic_read ( lteiot12_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE IoT 12 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot12_set_pwr_pin ( lteiot12_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 12 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot12_set_rts_pin ( lteiot12_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 12 get STA pin function.
 * @details This function returns the module operating status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot12_get_sta_pin ( lteiot12_t *ctx );

/**
 * @brief LTE IoT 12 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot12_get_ring_pin ( lteiot12_t *ctx );

/**
 * @brief LTE IoT 12 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot12_get_cts_pin ( lteiot12_t *ctx );

/**
 * @brief LTE IoT 12 set power state function.
 * @details This function sets a desired power state by toggling PWR pin with a specific time for low state.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON.
 * @return None.
 * @note None.
 */
void lteiot12_set_power_state ( lteiot12_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 12 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot12_cmd_run ( lteiot12_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 12 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lteiot12_cmd_set ( lteiot12_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE IoT 12 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot12_cmd_get ( lteiot12_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 12 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot12_cmd_help ( lteiot12_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 12 set SIM card APN function.
 * @details This function sets APN for SIM card.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return None.
 * @note None.
 */
void lteiot12_set_sim_apn ( lteiot12_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 12 send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return None.
 * @note None.
 */
void lteiot12_send_sms_text ( lteiot12_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 12 send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot12_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot12_send_sms_pdu ( lteiot12_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 12 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot12_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT12_H

/*! @} */ // lteiot12

// ------------------------------------------------------------------------ END
