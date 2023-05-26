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
 * @file hallcurrent14.c
 * @brief Hall Current 14 Click Driver.
 */

#include "hallcurrent14.h"

void hallcurrent14_cfg_setup ( hallcurrent14_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT14_SET_DEV_ADDR;
    cfg->vref        = HALLCURRENT14_VREF_5V;
    cfg->drv_sel     = HALLCURRENT14_DRV_SEL_I2C;
}

void hallcurrent14_drv_interface_selection ( hallcurrent14_cfg_t *cfg, hallcurrent14_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t hallcurrent14_init ( hallcurrent14_t *ctx, hallcurrent14_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( HALLCURRENT14_DRV_SEL_I2C == ctx->drv_sel ) 
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
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
        {
            return ADC_ERROR;
        }
    }

    return HALLCURRENT14_OK;
}

err_t hallcurrent14_read_raw_adc ( hallcurrent14_t *ctx, uint16_t *raw_adc ) 
{
    if ( HALLCURRENT14_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ];
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & HALLCURRENT14_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t hallcurrent14_read_voltage ( hallcurrent14_t *ctx, float *voltage ) 
{
    if ( HALLCURRENT14_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc;
        err_t err_flag = hallcurrent14_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) HALLCURRENT14_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t hallcurrent14_set_vref ( hallcurrent14_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( HALLCURRENT14_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return HALLCURRENT14_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t hallcurrent14_read_current ( hallcurrent14_t *ctx, float *current )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < HALLCURRENT14_NUM_CONVERSIONS )
    {
        if ( HALLCURRENT14_OK == hallcurrent14_read_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= HALLCURRENT14_NUM_CONVERSIONS )
            {
                return HALLCURRENT14_ERROR;
            }
        }
    }
    *current = ( ( voltage_sum / HALLCURRENT14_NUM_CONVERSIONS ) - 
                 ( ctx->vref * HALLCURRENT14_ZERO_CURRENT_OFFSET ) ) / HALLCURRENT14_SENSITIVITY_V_TO_A;
    return HALLCURRENT14_OK;
}

// ------------------------------------------------------------------------- END
