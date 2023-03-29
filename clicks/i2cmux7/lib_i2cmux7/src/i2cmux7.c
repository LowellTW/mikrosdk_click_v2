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
 * @file i2cmux7.c
 * @brief I2C MUX 7 Click Driver.
 */

#include "i2cmux7.h"

void i2cmux7_cfg_setup ( i2cmux7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CMUX7_DEV_ADDR_A2A1A0_000;
}

err_t i2cmux7_init ( i2cmux7_t *ctx, i2cmux7_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

err_t i2cmux7_set_channel ( i2cmux7_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr )
{
    if ( ch_sel > I2CMUX7_CHANNEL_7 )
    {
        return I2CMUX7_ERROR;
    }
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    error_flag |= i2c_master_write( &ctx->i2c, &ch_sel, 1 );
    ctx->ch_slave_address = ch_slave_addr;
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->ch_slave_address );
    return error_flag;
}

err_t i2cmux7_read_channel ( i2cmux7_t *ctx, uint8_t *ch_sel )
{
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    error_flag |= i2c_master_read( &ctx->i2c, ch_sel, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->ch_slave_address );
    return error_flag;
}

void i2cmux7_reset_device ( i2cmux7_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t i2cmux7_generic_write ( i2cmux7_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t i2cmux7_generic_read ( i2cmux7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

// ------------------------------------------------------------------------- END
