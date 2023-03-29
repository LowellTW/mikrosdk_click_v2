/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "i2cmux.h"

// ---------------------------------------------- PRIVATE VARIABLES 

static uint8_t slv_address; 

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void dev_reset_delay ( void );

void i2cmux_aux_read ( i2cmux_t *ctx, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2cmux_cfg_setup ( i2cmux_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CMUX_I2C_SLAVE_ADDRESS_0;
}

I2CMUX_RETVAL i2cmux_init ( i2cmux_t *ctx, i2cmux_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2CMUX_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return I2CMUX_OK;
}

void i2cmux_generic_write ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    i2c_master_set_slave_address( &ctx->i2c, slv_address );
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

void i2cmux_generic_read ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, slv_address );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void i2cmux_hw_reset ( i2cmux_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

void i2cmux_write_cmd ( i2cmux_t *ctx, uint8_t tx_data )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = tx_data;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    i2c_master_write( &ctx->i2c, tx_buf, 1 );
}

uint8_t i2cmux_read_cmd ( i2cmux_t *ctx )
{
    uint8_t rx_buf[ 1 ];
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    i2cmux_aux_read( ctx, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void i2cmux_set_channel ( i2cmux_t *ctx, uint8_t channel, uint8_t ch_slave_address )
{
    slv_address = ch_slave_address;

    i2cmux_write_cmd( ctx, channel );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_reset_delay ( void )
{
    Delay_100ms( );
}

void i2cmux_aux_read ( i2cmux_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );
}

// ------------------------------------------------------------------------- END

