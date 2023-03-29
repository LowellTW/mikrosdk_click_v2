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

#include "fram3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fram3_cfg_setup ( fram3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = FRAM3_SLAVE_ADDR;
}

FRAM3_RETVAL fram3_init ( fram3_t *ctx, fram3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return FRAM3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return FRAM3_OK;
}

void fram3_generic_write ( fram3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void fram3_generic_read ( fram3_t *ctx, uint8_t *tx_buf, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 3, data_buf, len );
}

uint8_t fram3_read_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size )
{
    uint8_t write_buf[ 3 ];
    uint8_t read_buf[ 20 ];
    uint8_t n_cnt;

    if ( ( start_addr > FRAM3_MAX_ADDR ) && ( n_buf_size > FRAM3_MAX_BUF_SIZE ) )
    {
        return FRAM3_ERROR;
    }

    write_buf[ 0 ] = 0x4D;
    write_buf[ 1 ] = start_addr;
    write_buf[ 2 ] = n_buf_size;

    fram3_generic_read( ctx, write_buf, read_buf, n_buf_size + 2 );
    
    if ( ( read_buf[ 0 ] != 0x4D ) || ( read_buf[ 1 ] != 0x00 ) )
    {
        return FRAM3_ERROR;
    }

    for ( n_cnt = 2; n_cnt < n_buf_size + 2; n_cnt++ )
    {
        data_buf[ n_cnt - 2 ] = read_buf[ n_cnt ];
    }

    return FRAM3_SUCCESS;
}

uint8_t fram3_write_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size )
{
    uint8_t write_buf[ 20 ];
    uint8_t read_buf[ 3 ];
    uint8_t n_cnt;

    if ( ( start_addr > FRAM3_MAX_ADDR ) && ( n_buf_size > FRAM3_MAX_BUF_SIZE ) )
    {
        return FRAM3_ERROR;
    }

    write_buf[ 0 ] = 0x47;
    write_buf[ 1 ] = start_addr;
    write_buf[ 2 ] = n_buf_size;

    for ( n_cnt = 3; n_cnt < n_buf_size + 3; n_cnt++ )
    {
        write_buf[ n_cnt ] = *data_buf;
        data_buf++;
    }

    i2c_master_write_then_read( &ctx->i2c, write_buf, n_buf_size + 3, read_buf, 2 );


    if ( ( read_buf[ 0 ] != 0x47 ) || ( read_buf[ 1 ] != 0x00 ) )
    {
        return FRAM3_ERROR;
    }

    return FRAM3_SUCCESS;
}

// ------------------------------------------------------------------------- END
