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
 * @file pressure19.h
 * @brief This file contains API for Pressure 19 Click Driver.
 */

#ifndef PRESSURE19_H
#define PRESSURE19_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup pressure19 Pressure 19 Click Driver
 * @brief API for configuring and manipulating Pressure 19 Click driver.
 * @{
 */

/**
 * @defgroup pressure19_set Pressure 19 Registers Settings
 * @brief Settings for registers of Pressure 19 Click driver.
 */

/**
 * @addtogroup pressure19_set
 * @{
 */

/**
 * @brief Pressure 19 pressure calculation values.
 * @details Specified pressure calculation values of Pressure 19 Click driver.
 */
#define PRESSURE19_MIN_PRESSURE         0.2
#define PRESSURE19_MAX_PRESSURE         3.0
#define PRESSURE19_MIN_VOLTAGE          0.4
#define PRESSURE19_MAX_VOLTAGE          4.65
#define PRESSURE19_BAR_TO_MBAR          1000

/**
 * @brief Pressure 19 ADC setting.
 * @details Specified settings for ADC of Pressure 19 Click driver.
 */
#define PRESSURE19_ADC_RESOLUTION       0x0FFF
#define PRESSURE19_VREF_3V3             3.3
#define PRESSURE19_VREF_5V              5.0

/**
 * @brief Pressure 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 19 Click driver.
 */
#define PRESSURE19_SET_DEV_ADDR         0x4D

/*! @} */ // pressure19_set

/**
 * @defgroup pressure19_map Pressure 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 19 Click driver.
 */

/**
 * @addtogroup pressure19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 19 Click to the selected MikroBUS.
 */
#define PRESSURE19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // pressure19_map
/*! @} */ // pressure19

/**
 * @brief Pressure 19 Click driver selector.
 * @details Selects target driver interface of Pressure 19 Click driver.
 */
typedef enum
{
    PRESSURE19_DRV_SEL_ADC,         /**< ADC driver descriptor. */
    PRESSURE19_DRV_SEL_I2C          /**< I2C driver descriptor. */

} pressure19_drv_t;

/**
 * @brief Pressure 19 Click context object.
 * @details Context object definition of Pressure 19 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    float       vref;               /**< ADC reference voltage. */
    pressure19_drv_t drv_sel;       /**< Master driver interface selector. */

} pressure19_t;

/**
 * @brief Pressure 19 Click configuration object.
 * @details Configuration object definition of Pressure 19 Click driver.
 */
typedef struct
{
    pin_name_t  an;                 /**< Analog pin descriptor. */
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    uint32_t                i2c_speed;      /**< I2C serial speed. */
    uint8_t                 i2c_address;    /**< I2C slave address. */
    
    pressure19_drv_t drv_sel;       /**< Master driver interface selector. */

} pressure19_cfg_t;

/**
 * @brief Pressure 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE19_OK = 0,
    PRESSURE19_ERROR = -1

} pressure19_return_value_t;

/*!
 * @addtogroup pressure19 Pressure 19 Click Driver
 * @brief API for configuring and manipulating Pressure 19 Click driver.
 * @{
 */

/**
 * @brief Pressure 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure19_cfg_setup ( pressure19_cfg_t *cfg );

/**
 * @brief Pressure 19 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure19_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure19_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure19_drv_interface_selection ( pressure19_cfg_t *cfg, pressure19_drv_t drv_sel );

/**
 * @brief Pressure 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure19_init ( pressure19_t *ctx, pressure19_cfg_t *cfg );

/**
 * @brief Pressure 19 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #pressure19_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure19_read_raw_adc ( pressure19_t *ctx, uint16_t *raw_adc );

/**
 * @brief Pressure 19 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #pressure19_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t pressure19_read_voltage ( pressure19_t *ctx, float *voltage );

/**
 * @brief Pressure 19 set vref function.
 * @details This function sets the voltage reference for Pressure 19 click driver.
 * @param[in] ctx : Click context object.
 * See #pressure19_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b pressure19_init is 3.3V.
 */
err_t pressure19_set_vref ( pressure19_t *ctx, float vref );

/**
 * @brief Pressure 19 get pressure function.
 * @details This function reads the output voltage and converts it to pressure in mBar.
 * @param[in] ctx : Click context object.
 * See #pressure19_t object definition for detailed explanation.
 * @param[out] pressure : Pressure [mBar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage. 
 * On 3V3 systems the maximal pressure read is about 2110 mBar.
 */
err_t pressure19_get_pressure ( pressure19_t *ctx, uint16_t *pressure );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE19_H

/*! @} */ // pressure19

// ------------------------------------------------------------------------ END
