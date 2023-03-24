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

#include "pac1921.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pac1921_cfg_setup ( pac1921_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PAC1921_SLAVE_ADDRESS;

    cfg->aux_cfg.iarp = 0x03;
    cfg->aux_cfg.measurement_mode_old = 0xFF;
    cfg->aux_cfg.sample_num_old = 0xFF;
}

PAC1921_RETVAL pac1921_init ( pac1921_t *ctx, pac1921_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PAC1921_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );


    // Output pins 

    digital_out_init( &ctx->int_pin, cfg->int_pin );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return PAC1921_OK;
}

void pac1921_default_cfg ( pac1921_t *ctx )
{
    uint8_t gain_cfg_byte = PAC1921_I_RESOLUTION_11_BIT | PAC1921_V_RESOLUTION_11_BIT;
    uint8_t int_cfg_byte = PAC1921_READ_INT_OVERRIDE_ON | PAC1921_FORCED_INTEGRATE_MODE_ON;
    uint8_t control_byte = PAC1921_FORCED_READ_MODE_ON | PAC1921_FORCED_RECALCULATE_MODE_ON;

    pac1921_write_to_reg( ctx, PAC1921_GAIN_CFG_REG, &gain_cfg_byte, 1 );
    pac1921_write_to_reg( ctx, PAC1921_INTEGRATION_CFG_REG, &int_cfg_byte, 1 );
    pac1921_write_to_reg( ctx, PAC1921_CONTROL_REG, &control_byte, 1 ); 
}

void pac1921_generic_write ( pac1921_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void pac1921_generic_read ( pac1921_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void pac1921_write_to_reg ( pac1921_t *ctx, uint8_t reg_addr, uint8_t *write_data, uint8_t len )
{
    pac1921_generic_write( ctx, reg_addr, write_data, len );

    switch ( reg_addr )
    {
        case PAC1921_GAIN_CFG_REG:
        {
            if ( len == 2 )
            {
                ctx->aux.cfg_byte = write_data[ 1 ];
                return;
            }
            else if ( len == 3 )
            {
                ctx->aux.cfg_byte = write_data[ 1 ];
                ctx->aux.ctrl_byte = write_data[ 2 ];
                return;
            }
            break;
        }

        case PAC1921_INTEGRATION_CFG_REG:
        {
            if ( len == 1 )
            {
                ctx->aux.cfg_byte = write_data[ 0 ];
                return;
            }
            else if ( len == 2 )
            {
                ctx->aux.cfg_byte = write_data[ 0 ];
                ctx->aux.ctrl_byte = write_data[ 1 ];
                return;
            }
            break;
        }
        case PAC1921_CONTROL_REG:
        {
            if ( len == 1 )
            {
                ctx->aux.ctrl_byte = write_data[ 0 ];
            }
        }
    }
}

float pac1921_get_measured_data ( pac1921_t *ctx, uint8_t measurement_mode, uint8_t sample_num )
{
    float return_value;
    uint16_t measured_data;
    uint8_t reg_addr;
    uint8_t read_buf[ 2 ] = { 0 };

    if ( ( measurement_mode & 0x3F ) || ( sample_num & 0x0F ) )
    {
        return 0;
    }

    ctx->aux.ctrl_byte &= 0x3F;
    ctx->aux.ctrl_byte |= measurement_mode;

    if ( ctx->aux.measurement_mode_old != ( ctx->aux.ctrl_byte & PAC1921_MEASUREMENT_MODE_MASK ) )
    {
        pac1921_write_to_reg( ctx, PAC1921_CONTROL_REG, &( ctx->aux.ctrl_byte ), 1 );
        ctx->aux.measurement_mode_old = ( ctx->aux.ctrl_byte & PAC1921_MEASUREMENT_MODE_MASK );
    }

    ctx->aux.cfg_byte &= 0x0F;
    ctx->aux.cfg_byte |= sample_num;

    if ( ctx->aux.sample_num_old != ctx->aux.cfg_byte )
    {
        pac1921_write_to_reg( ctx, PAC1921_INTEGRATION_CFG_REG, &( ctx->aux.cfg_byte ), 1 );
        ctx->aux.sample_num_old = ctx->aux.cfg_byte;
    }

    switch ( measurement_mode )
    {
        case PAC1921_MEASUREMENT_MODE_V_SENSE_FREE_RUN:
        {
            reg_addr = PAC1921_VSENSE_RESULT_HIGH;
            ctx->aux.output_fsr = 100;
            break;
        }
        case PAC1921_MEASUREMENT_MODE_V_BUS_FREE_RUN:
        {
            reg_addr = PAC1921_VBUS_RESULT_HIGH;
            ctx->aux.output_fsr = 32000;
            break;
        }
        case PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN:
        {
            reg_addr = PAC1921_VPOWER_RESULT_HIGH;
        }
    }

    pac1921_generic_read( ctx, reg_addr, read_buf, 2 );

    measured_data = read_buf[ 0 ];
    measured_data <<= 2;
    read_buf[ 1 ] >>= 6;
    measured_data |= read_buf[ 1 ];

    return_value = measured_data / 1023.0;

    if ( measurement_mode == PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN )
    {
        return_value *= PAC1921_CURRENT_MAX;
        return_value *= PAC1921_VOLTAGE_MAX;
    }
    else
    {
        return_value *= ctx->aux.output_fsr;
    }

    return return_value;
}

void pac1921_set_int_pin ( pac1921_t *ctx, uint8_t output )
{
    digital_out_write( &ctx->int_pin, output );
}

uint8_t pac1921_get_an_pin ( pac1921_t *ctx )
{
    return digital_in_read( &ctx->an );
}

// ------------------------------------------------------------------------- END

