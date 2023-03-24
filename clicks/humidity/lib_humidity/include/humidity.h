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
 * @file humidity.h
 * @brief This file contains API for Humidity Click Driver.
 */

#ifndef HUMIDITY_H
#define HUMIDITY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup humidity Humidity Click Driver
 * @brief API for configuring and manipulating Humidity Click driver.
 * @{
 */

/**
 * @defgroup humidity_set Humidity Settings
 * @brief Settings for Humidity Click driver.
 */

/**
 * @addtogroup humidity_set
 * @{
 */

/**
 * @brief Humidity device address setting.
 * @details Specified setting for device slave address selection of
 * Humidity Click driver.
 */
#define HUMIDITY_SET_DEV_ADDR           0x4D

/**
 * @brief Humidity ADC setting.
 * @details Specified settings for ADC of Humidity Click driver.
 */
#define HUMIDITY_ADC_RESOLUTION         0x0FFF
#define HUMIDITY_VREF_3V3               3.3
#define HUMIDITY_VREF_5V                5.0

/**
 * @brief Humidity constants.
 * @details Specified constants for humidity calculation of Humidity Click driver.
 */
#define HUMIDITY_DIVISOR                0.00636
#define HUMIDITY_SUBTRAHEND             0.1515

/*! @} */ // humidity_set

/**
 * @defgroup humidity_map Humidity MikroBUS Map
 * @brief MikroBUS pin mapping of Humidity Click driver.
 */

/**
 * @addtogroup humidity_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Humidity Click to the selected MikroBUS.
 */
#define HUMIDITY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // humidity_map
/*! @} */ // humidity

/**
 * @brief Humidity Click driver selector.
 * @details Selects target driver interface of Humidity Click driver.
 */
typedef enum
{
    HUMIDITY_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    HUMIDITY_DRV_SEL_I2C        /**< I2C driver descriptor. */

} humidity_drv_t;

/**
 * @brief Humidity Click context object.
 * @details Context object definition of Humidity Click driver.
 */
typedef struct
{
    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    humidity_drv_t drv_sel;     /**< Master driver interface selector. */
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    float   vref;               /**< ADC reference voltage. */

} humidity_t;

/**
 * @brief Humidity Click configuration object.
 * @details Configuration object definition of Humidity Click driver.
 */
typedef struct
{
    pin_name_t  an;             /**< Analog pin descriptor. */
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    
    humidity_drv_t          drv_sel;        /**< Master driver interface selector. */
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} humidity_cfg_t;

/**
 * @brief Humidity Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HUMIDITY_OK = 0,
    HUMIDITY_ERROR = -1

} humidity_return_value_t;

/*!
 * @addtogroup humidity Humidity Click Driver
 * @brief API for configuring and manipulating Humidity Click driver.
 * @{
 */

/**
 * @brief Humidity configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #humidity_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void humidity_cfg_setup ( humidity_cfg_t *cfg );

/**
 * @brief Humidity driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #humidity_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #humidity_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void humidity_drv_interface_selection ( humidity_cfg_t *cfg, humidity_drv_t drv_sel );

/**
 * @brief Humidity initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #humidity_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #humidity_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t humidity_init ( humidity_t *ctx, humidity_cfg_t *cfg );

/**
 * @brief Humidity read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #humidity_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t humidity_read_raw_adc ( humidity_t *ctx, uint16_t *raw_adc );

/**
 * @brief Humidity read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #humidity_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t humidity_read_voltage ( humidity_t *ctx, float *voltage );

/**
 * @brief Humidity set vref function.
 * @details This function sets the voltage reference for Humidity click driver.
 * @param[in] ctx : Click context object.
 * See #humidity_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b humidity_init is 3.3V.
 */
err_t humidity_set_vref ( humidity_t *ctx, float vref );

/**
 * @brief Humidity voltage to relative humidity function.
 * @details This function calculates relative humidity percents based on the @b voltage input.
 * @param[in] ctx : Click context object.
 * See #humidity_t object definition for detailed explanation.
 * @param[in] voltage : Voltage from OUT (volts).
 * @return Relative humidity percents.
 * @note None.
 */
float humidity_voltage_to_rh ( humidity_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // HUMIDITY_H

/*! @} */ // humidity

// ------------------------------------------------------------------------ END
