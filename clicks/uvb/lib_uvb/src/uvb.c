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
 * @file uvb.c
 * @brief UVB Click Driver.
 */

#include "uvb.h"

void uvb_cfg_setup ( uvb_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = UVB_SET_DEV_ADDR;
}

err_t uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t uvb_default_cfg ( uvb_t *ctx ) 
{
    uvb_configuration( ctx, UVB_REG_MODE, UVB_MODE_UVB_OPERATION | UVB_MODE_NORMAL );
    uvb_configuration( ctx, UVB_REG_RES_UV, UVB_RESOLUTION_200ms );
    uvb_configuration( ctx, UVB_REG_RANGE_UVB, UVB_RANGE_x4 );
    uvb_configuration( ctx, UVB_REG_MODE_CTRL, UVB_MCTRL_SLEEP_2_TIMES );
    return UVB_OK;
}

err_t uvb_generic_write ( uvb_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t uvb_generic_read ( uvb_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}


void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cfg;

    uvb_generic_write ( ctx, reg, tx_buf, 1 );  
}

uint8_t uvb_read_byte ( uvb_t *ctx, uint8_t reg )
{
    uint8_t rx_byte;

    uvb_generic_read ( ctx, reg, &rx_byte, 1 );

    return rx_byte;
}

err_t uvb_check_communication ( uvb_t *ctx )
{
    uint8_t device_id;

    device_id = uvb_read_byte( ctx, UVB_REG_CHIP_ID );
    if ( device_id == UVB_DEF_CHIP_ID ) {
        return UVB_OK;
    }
    return UVB_ERROR;
}

uint16_t uvb_get_uv_data ( uvb_t *ctx )
{
    uint16_t uvb_raw_data;
    
    uvb_raw_data = uvb_read_byte( ctx, UVB_REG_UVB_MSB );
    uvb_raw_data <<= 8;
    uvb_raw_data |= uvb_read_byte( ctx, UVB_REG_UVB_LSB );
    
    return uvb_raw_data;
}

// ------------------------------------------------------------------------- END
