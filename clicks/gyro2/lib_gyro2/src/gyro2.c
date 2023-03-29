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

#include "gyro2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GYRO2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gyro2_cfg_setup ( gyro2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->scs = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = GYRO2_ADDR1;
}

GYRO2_RETVAL gyro2_init ( gyro2_t *ctx, gyro2_cfg_t *cfg )
{

    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return GYRO2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->scs, cfg->scs );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    // Initial pin value

    digital_out_high( &ctx->scs );
    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->cs );

    return GYRO2_OK;
}

uint8_t gyro2_default_cfg ( gyro2_t *ctx )
{
    uint8_t temp;

    temp = gyro2_get_id( ctx );

     if( temp == 0xD7 )
    {
        gyro2_interrupt_event_generation( ctx, GYRO2_RT_CFG_ZTEFE | GYRO2_RT_CFG_YTEFE | GYRO2_RT_CFG_XTEFE );
        gyro2_sensitivity( ctx, 10 ) ;
        gyro2_set_opmode( ctx, GYRO2_ACTIVE );
        gyro2_set_dr( ctx, GYRO2_DR_100Hz );
        gyro2_interrupt_cfg( ctx, GYRO2_INT_CFG_FIFO_INT1, GYRO2_INT_EN_FIFO | GYRO2_INT_EN_DRDY, GYRO2_IPOL_ACTIVE_HI );
        gyro2_fr_setup( ctx, GYRO2_LO_PASS_MOD2, GYRO2_HI_PASS_OFF, GYRO2_SCALE_3 );

         return 1;
     }
     else 
     {
         return 2;
     }
}

void gyro2_generic_write ( gyro2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void gyro2_generic_read ( gyro2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void gyro2_scs_set ( gyro2_t *ctx, uint8_t val )
{
    digital_out_write( &ctx->scs, val );
}

void gyro2_rst_set ( gyro2_t *ctx, uint8_t val )
{
    digital_out_write( &ctx->rst, val );
}

void gyro2_cs_set ( gyro2_t *ctx, uint8_t val )
{
    digital_out_write( &ctx->cs, val );
}

void gyro2_rdy_set ( gyro2_t *ctx, uint8_t val )
{
    digital_out_write( &ctx->rdy_pin, val );
}

uint8_t gyro2_rdy_get ( gyro2_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t gyro2_int_get ( gyro2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void gyro2_hw_reset ( gyro2_t *ctx )
{
    gyro2_rst_set( ctx, 0 );
    Delay_100ms( );
    gyro2_rst_set( ctx, 1 );
    Delay_100ms( );
}

uint8_t gyro2_get_id ( gyro2_t *ctx )
{
    uint8_t w_temp;

    gyro2_generic_read( ctx, GYRO2_WHO_AM_I, &w_temp, 1 );
    
    return w_temp;
}

void gyro2_get_axisraw ( gyro2_t *ctx, int16_t *axis_data )
{
    uint8_t reg_data[ 7 ];

    gyro2_generic_read( ctx, GYRO2_OUT_X_MSB, &reg_data, 6 );

    axis_data[ 0 ] = ( uint16_t )( reg_data[ 0 ] << 8 ) | reg_data[ 1 ];
    axis_data[ 1 ] = ( uint16_t )( reg_data[ 2 ] << 8 ) | reg_data[ 3 ];
    axis_data[ 2 ] = ( uint16_t )( reg_data[ 4 ] << 8 ) | reg_data[ 5 ];
}

void gyro2_calc_axis ( int16_t *axis_data )
{
   axis_data[ 0 ] = ( axis_data[ 0 ] * 0.015625 / 88 * 3.0 );
   axis_data[ 1 ] = ( axis_data[ 1 ] * 0.015625 / 88 * 3.0 );
   axis_data[ 2 ] = ( axis_data[ 2 ] * 0.015625 / 88 * 3.0 );
}

uint8_t gyro2_read_temperature ( gyro2_t *ctx )
{
    uint8_t w_temp;

    gyro2_generic_read( ctx, GYRO2_TEMP, &w_temp, 1 );
    
    return w_temp;
}

void gyro2_sw_reset ( gyro2_t *ctx )
{
    gyro2_generic_read( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );

    ctx->tmp_ctrl_reg.tmp_ctrl_reg1 |= 1 << 6;

    gyro2_generic_write( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );
}

void gyro2_set_dr ( gyro2_t *ctx, uint8_t rate )
{
    if ( rate > 7 )
    {
        rate = 7;
    }

    gyro2_generic_read( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );

    //clear the DR bitfield before setting

    ctx->tmp_ctrl_reg.tmp_ctrl_reg1 &= ~( 7 << 2 ); 

    ctx->tmp_ctrl_reg.tmp_ctrl_reg1 |= ( rate << 2 );

    gyro2_generic_write( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );
}

void gyro2_set_opmode ( gyro2_t *ctx, uint8_t opmode )
{
    if ( opmode > 3 )
    {
        opmode = 3;
    } 
    gyro2_generic_read( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );

    //clear the DR bitfield before setting

    ctx->tmp_ctrl_reg.tmp_ctrl_reg1 &= ~3; 

    ctx->tmp_ctrl_reg.tmp_ctrl_reg1 |= opmode;

    gyro2_generic_write( ctx, GYRO2_CTRL_REG1, &ctx->tmp_ctrl_reg.tmp_ctrl_reg1, 1 );
}

// Interrupt register start

void gyro2_interrupt_cfg ( gyro2_t *ctx, uint8_t int_route, uint8_t int_en, uint8_t polarity_outdrvsetting )
{
   // Test if the parameter IntPin has the bit set/reset and place 1 or 0 on the correct bitfield.
   // interrupt enable
   
   ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_en & 1 << 2 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 4 )  : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xFB );
   ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_en & 1 << 4 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 16 ) : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xEF );
   ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_en & 1 << 6 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 64 ) : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xBF );

   // logic polarity and push pull output driver

   ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( polarity_outdrvsetting & 1 )    ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 1 ) : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xFE );
   ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( polarity_outdrvsetting & 1<<1 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 2 ) : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xFD );

   // CFG route

    ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_route & 1 << 3 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 8 )   : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xF7 );
    ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_route & 1 << 5 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 32 )  : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0xDF );
    ctx->tmp_ctrl_reg.tmp_ctrl_reg2 = ( int_route & 1 << 7 ) ? ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 | 128 ) : ( ctx->tmp_ctrl_reg.tmp_ctrl_reg2 & 0x7F );
    
    gyro2_generic_write( ctx, GYRO2_CTRL_REG2, &ctx->tmp_ctrl_reg.tmp_ctrl_reg2, 1 );
}

void gyro2_interrupt_event_generation ( gyro2_t *ctx, uint8_t cfg )
{
   uint8_t tmp;

   tmp = ( cfg & 0x0F );
   gyro2_generic_write( ctx, GYRO2_RT_CFG, &tmp, 1 );
}

void gyro2_sensitivity ( gyro2_t *ctx, uint8_t s_setting )
{
   uint8_t tmp;

   tmp = ( s_setting & 0x7F );
   gyro2_generic_write( ctx, GYRO2_RT_THS, &tmp, 1 );
}

// Interrupt register end


// filter and range setup

void gyro2_fr_setup ( gyro2_t *ctx, uint8_t low_pass, uint8_t hi_pass, uint8_t scale_set )
{
   uint8_t tmp;

   tmp =  ( low_pass & 0xC0 );
   tmp |= ( hi_pass &  0x1C );
   tmp |= ( scale_set  & 0x03 );

   gyro2_generic_write( ctx, GYRO2_CTRL_REG0, &tmp, 1 );
}

// ------------------------------------------------------------------------ END
