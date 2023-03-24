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
 * @file pressure15.c
 * @brief Pressure 15 Click Driver.
 */

#include "pressure15.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Calculation resolutions.
 * @details Resolution used for calculating pressure and temperature values.
 */
#define PRESSURE15_TEMP_RES     100.0
#define PRESSURE15_PRESS_RES    4096.0

/**
 * @brief Pressure 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure15_i2c_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure15_i2c_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 15 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure15_spi_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 15 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure15_spi_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void pressure15_cfg_setup ( pressure15_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE15_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE15_DRV_SEL_SPI;
}

void pressure15_drv_interface_selection ( pressure15_cfg_t *cfg, pressure15_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure15_init ( pressure15_t *ctx, pressure15_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == PRESSURE15_DRV_SEL_I2C ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = pressure15_i2c_read;
        ctx->write_f = pressure15_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = pressure15_spi_read;
        ctx->write_f = pressure15_spi_write;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return 0;
}

err_t pressure15_default_cfg ( pressure15_t *ctx ) 
{
    uint8_t temp_data = 0x70;
    err_t error_flag = pressure15_generic_write( ctx, PRESSURE15_REG_CTRL_REG1, &temp_data, 1 );
    temp_data = 0x04;
    error_flag |= pressure15_generic_write( ctx, PRESSURE15_REG_CTRL_REG3, &temp_data, 1 );
    
    return error_flag;
}

err_t pressure15_generic_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure15_generic_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t pressure15_get_int ( pressure15_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t pressure15_get_temperature ( pressure15_t *ctx, float *temperature )
{
    uint16_t temp_data;
    uint8_t temp_buf[ 2 ] = { 0 };

    err_t error_flag = pressure15_generic_read( ctx, PRESSURE15_REG_TEMP_OUT_L, temp_buf, 2 );
    temp_data = ( ( uint16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
    *temperature = temp_data / PRESSURE15_TEMP_RES;
    
    return error_flag;
}

err_t pressure15_get_pressure ( pressure15_t *ctx, float *pressure )
{
    uint32_t press_data;
    uint8_t temp_buf[ 3 ] = { 0 };
    
    err_t error_flag = pressure15_generic_read( ctx, PRESSURE15_REG_PRESSURE_OUT_XL, temp_buf, 3 );
    press_data = ( ( uint32_t )temp_buf[ 2 ] << 16 ) | 
                 ( ( uint32_t )temp_buf[ 1 ] << 8 ) | 
                 temp_buf[ 0 ];
    *pressure = press_data / PRESSURE15_PRESS_RES;
    
    return error_flag;
}

static err_t pressure15_i2c_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 30 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t pressure15_i2c_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure15_spi_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 30 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t pressure15_spi_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
