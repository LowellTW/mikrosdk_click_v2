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
 * @file color16.c
 * @brief Color 16 Click Driver.
 */

#include "color16.h"

void color16_cfg_setup ( color16_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ldr = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR16_DEVICE_ADDRESS;
}

err_t color16_init ( color16_t *ctx, color16_cfg_t *cfg )
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

    digital_out_init( &ctx->ldr, cfg->ldr );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t color16_default_cfg ( color16_t *ctx )
{
    err_t error_flag = COLOR16_OK;
    error_flag |= color16_set_reg_bank_access ( ctx, COLOR16_ACCESS_REG_BANK_20H_7FH );
    if ( COLOR16_ERROR == color16_check_communication ( ctx ) )
    {
        return COLOR16_ERROR;
    }
    error_flag |= color16_set_reg_bank_access ( ctx, COLOR16_ACCESS_REG_BANK_ABOVE_80H );
    
    error_flag |= color16_write_register ( ctx, COLOR16_REG_ENABLE, COLOR16_ENABLE_POFF );
    Delay_100ms ( );
    error_flag |= color16_write_register ( ctx, COLOR16_REG_ENABLE, COLOR16_ENABLE_PON );
    Delay_100ms ( );
    error_flag |= color16_write_register ( ctx, COLOR16_REG_CONTROL, COLOR16_CONTROL_SW_RESET );
    Delay_100ms ( );
    error_flag |= color16_enable_ext_led ( ctx, COLOR16_LED_DRIVE_CURR_DEFAULT );
    
    error_flag |= color16_set_integration_time_ms ( ctx, COLOR16_INTEGRATION_TIME_DEFAULT );
    
    error_flag |= color16_set_wait_time_ms ( ctx, COLOR16_WAIT_TIME_DEFAULT );
    
    error_flag |= color16_write_register ( ctx, COLOR16_REG_CFG_1, COLOR16_CFG_1_AGAIN_4 );
     
    error_flag |= color16_write_register ( ctx, COLOR16_REG_CFG_20, COLOR16_CFG_20_AUTO_SMUX_18CH );
    
    error_flag |= color16_write_register ( ctx, COLOR16_REG_ENABLE, COLOR16_ENABLE_WEN | 
                                                                    COLOR16_ENABLE_SP_EN | 
                                                                    COLOR16_ENABLE_PON );
    return error_flag;
}

err_t color16_generic_write ( color16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write ( &ctx->i2c, data_buf, len + 1 );
}

err_t color16_generic_read ( color16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color16_write_register ( color16_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write ( &ctx->i2c, data_buf, 2 );
}

err_t color16_read_register ( color16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t color16_write_register_word ( color16_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write ( &ctx->i2c, data_buf, 3 );
}

err_t color16_read_register_word ( color16_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        return COLOR16_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    return COLOR16_OK;
}

err_t color16_check_communication ( color16_t *ctx )
{
    uint8_t device_id;
    if ( COLOR16_OK == color16_read_register ( ctx, COLOR16_REG_ID, &device_id ) )
    {
        if ( COLOR16_DEVICE_ID == device_id )
        {
            return COLOR16_OK;
        }
    }
    return COLOR16_ERROR;
}

void color16_set_ldr_pin ( color16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ldr, state );
}

uint8_t color16_get_int_pin ( color16_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t color16_set_reg_bank_access ( color16_t *ctx, uint8_t reg_bank )
{
    uint8_t cfg_0;
    if ( COLOR16_ERROR == color16_read_register ( ctx, COLOR16_REG_CFG_0, &cfg_0 ) )
    {
        return COLOR16_ERROR;
    }
    if ( reg_bank && ( COLOR16_CFG_0_REG_BANK != ( cfg_0 & COLOR16_CFG_0_REG_BANK ) ) )
    {
        cfg_0 |= COLOR16_CFG_0_REG_BANK;
        return color16_write_register ( ctx, COLOR16_REG_CFG_0, cfg_0 );
    }
    if ( !reg_bank && ( COLOR16_CFG_0_REG_BANK == ( cfg_0 & COLOR16_CFG_0_REG_BANK ) ) )
    {
        cfg_0 &= ~COLOR16_CFG_0_REG_BANK;
        return color16_write_register ( ctx, COLOR16_REG_CFG_0, cfg_0 );
    }
    return COLOR16_OK;
}

err_t color16_disable_ext_led ( color16_t *ctx )
{
    color16_set_ldr_pin ( ctx, 0 );
    return color16_write_register ( ctx, COLOR16_REG_LED, 0 );
}

err_t color16_enable_ext_led ( color16_t *ctx, uint8_t led_curr )
{
    if ( ( led_curr > COLOR16_LED_DRIVE_CURR_MAX ) || ( led_curr < COLOR16_LED_DRIVE_CURR_MIN ) )
    {
        return COLOR16_ERROR;
    }
    uint8_t led_drive = ( led_curr - COLOR16_LED_DRIVE_CURR_MIN ) / COLOR16_LED_DRIVE_CURR_STEP;
    color16_set_ldr_pin ( ctx, 1 );
    return color16_write_register ( ctx, COLOR16_REG_LED, led_drive | COLOR16_LED_ON );
}

err_t color16_set_integration_time_ms ( color16_t *ctx, float int_time_ms )
{
    if ( ( int_time_ms > COLOR16_INTEGRATION_TIME_MAX ) || ( int_time_ms < COLOR16_INTEGRATION_TIME_MIN ) )
    {
        return COLOR16_ERROR;
    }
    uint16_t astep = 0;
    uint16_t atime = 0;
    for ( uint16_t cnt = 0; cnt <= COLOR16_ATIME_MAX; cnt++ )
    {
        if ( ( int_time_ms / ( cnt + 1 ) ) < ( ( COLOR16_ASTEP_MAX + 1 ) * COLOR16_SINGLE_STEP_MS ) )
        {
            atime = cnt;
            astep = ( uint16_t ) ( int_time_ms / ( ( atime + 1 ) * COLOR16_SINGLE_STEP_MS ) );
            break;
        }
    }
    if ( COLOR16_ERROR == color16_write_register ( ctx, COLOR16_REG_ATIME, ( uint8_t ) ( atime & 0xFF ) ) )
    {
        return COLOR16_ERROR;
    }
    if ( COLOR16_ERROR == color16_write_register_word ( ctx, COLOR16_REG_ASTEP_LSB, astep ) )
    {
        return COLOR16_ERROR;
    }
    return COLOR16_OK;
}

err_t color16_set_wait_time_ms ( color16_t *ctx, float wait_time_ms )
{
    if ( ( wait_time_ms > COLOR16_WAIT_TIME_MAX ) || ( wait_time_ms < COLOR16_WAIT_TIME_MIN ) )
    {
        return COLOR16_ERROR;
    }
    uint16_t wtime = ( wait_time_ms / COLOR16_WAIT_STEP_MS );
    if ( wtime )
    {
        wtime--;
    }
    return color16_write_register ( ctx, COLOR16_REG_WTIME, ( uint8_t ) ( wtime & 0xFF ) );
}

err_t color16_read_data ( color16_t *ctx, color16_data_t *data_out )
{
    uint8_t status2;
    if ( COLOR16_OK == color16_read_register ( ctx, COLOR16_REG_STATUS_2, &status2 ) )
    {
        if ( status2 & COLOR16_STATUS_2_AVALID )
        {
            uint8_t data_buf[ 38 ];
            if ( COLOR16_OK == color16_generic_read ( ctx, COLOR16_REG_STATUS, data_buf, 38 ) )
            {
                data_out->status = data_buf[ 0 ];
                data_out->astatus = data_buf[ 1 ];
                data_out->ch_fz = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
                data_out->ch_fy = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
                data_out->ch_fxl = ( ( uint16_t ) data_buf[ 7 ] << 8 ) | data_buf[ 6 ];
                data_out->ch_nir = ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 8 ];
                data_out->ch_2x_vis_1 = ( ( uint16_t ) data_buf[ 11 ] << 8 ) | data_buf[ 10 ];
                data_out->ch_fd_1 = ( ( uint16_t ) data_buf[ 13 ] << 8 ) | data_buf[ 12 ];
                data_out->ch_f2 = ( ( uint16_t ) data_buf[ 15 ] << 8 ) | data_buf[ 14 ];
                data_out->ch_f3 = ( ( uint16_t ) data_buf[ 17 ] << 8 ) | data_buf[ 16 ];
                data_out->ch_f4 = ( ( uint16_t ) data_buf[ 19 ] << 8 ) | data_buf[ 18 ];
                data_out->ch_f6 = ( ( uint16_t ) data_buf[ 21 ] << 8 ) | data_buf[ 20 ];
                data_out->ch_2x_vis_2 = ( ( uint16_t ) data_buf[ 23 ] << 8 ) | data_buf[ 22 ];
                data_out->ch_fd_2 = ( ( uint16_t ) data_buf[ 25 ] << 8 ) | data_buf[ 24 ];
                data_out->ch_f1 = ( ( uint16_t ) data_buf[ 27 ] << 8 ) | data_buf[ 26 ];
                data_out->ch_f5 = ( ( uint16_t ) data_buf[ 29 ] << 8 ) | data_buf[ 28 ];
                data_out->ch_f7 = ( ( uint16_t ) data_buf[ 31 ] << 8 ) | data_buf[ 30 ];
                data_out->ch_f8 = ( ( uint16_t ) data_buf[ 33 ] << 8 ) | data_buf[ 32 ];
                data_out->ch_2x_vis_3 = ( ( uint16_t ) data_buf[ 35 ] << 8 ) | data_buf[ 34 ];
                data_out->ch_fd_3 = ( ( uint16_t ) data_buf[ 37 ] << 8 ) | data_buf[ 36 ];
                return COLOR16_OK;
            }
        }
    }
    return COLOR16_ERROR;
}

// ------------------------------------------------------------------------- END
