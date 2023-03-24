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

#include "bargraph2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BARGRAPH2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void drv_segment_switch ( bargraph2_t *ctx, uint8_t reg_1, uint8_t reg_2, 
uint8_t reg_3 );

static uint8_t drv_get_segment ( uint8_t index );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bargraph2_cfg_setup ( bargraph2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mr = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BARGRAPH2_RETVAL bargraph2_init ( bargraph2_t *ctx, bargraph2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BARGRAPH2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BARGRAPH2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BARGRAPH2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->mr, cfg->mr );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return BARGRAPH2_OK;
}

void bargraph2_generic_transfer ( bargraph2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void bargraph2_reset ( bargraph2_t *ctx ) 
{
    digital_out_low( &ctx->mr );
    Delay_100ms( );
    digital_out_high( &ctx->mr );
}

void bargraph2_write_byte ( bargraph2_t *ctx, uint8_t input_data ) 
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &input_data, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

void bargraph2_led_green ( bargraph2_t *ctx, uint8_t index )
{
    uint8_t segment_index = index;
    
    switch ( segment_index ) 
    {
        case 1:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_1 );
            break;
        }
        case 2:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_2 );
            break;
        }
        case 3:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_3 );
            break;
        }
        case 4:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_4 );
            break;
        }
        case 5:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_5 );
            break;
        }    
        case 6:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_6 );
            break;
        }
        case 7:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_7 );
            break;
        }
        case 8:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_8 );
            break;
        }
         case 9:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_1, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
         case 10:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_2, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        default:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
    }
}

void bargraph2_led_red ( bargraph2_t *ctx, uint8_t index )
{   
    uint8_t segment_index = index;
    
    switch ( segment_index ) 
    {
        case 1:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_3,
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 2:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_4,
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 3:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_5,
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 4:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_6, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 5:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_7, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }    
        case 6:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_8, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 7:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_1, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        case 8:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_2,
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
         case 9:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_3, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
         case 10:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_4, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        default:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
    }
}

void bargraph2_led_yellow ( bargraph2_t *ctx, uint8_t index )
{   
    uint8_t segment_index = index;

    switch ( segment_index ) 
    {
        case 1:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_3,
                                     BARGRAPH2_LED_SEG_1 );
            break;
        }
        case 2:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_4,
                                     BARGRAPH2_LED_SEG_2 );
            break;
        }
        case 3:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_5,
                                     BARGRAPH2_LED_SEG_3 );
            break;
        }
        case 4:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_6, 
                                     BARGRAPH2_LED_SEG_4 );
            break;
        }
        case 5:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0,
                                     BARGRAPH2_LED_SEG_7, 
                                     BARGRAPH2_LED_SEG_5 );
            break;
        }    
        case 6: 
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_8, 
                                     BARGRAPH2_LED_SEG_6 );
            break;
        }
        case 7: 
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_1, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_7 );
            break;
        }
        case 8: 
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_2,
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_8 );
            break;
        }
         case 9: 
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_3, 
                                     BARGRAPH2_LED_SEG_1, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
         case 10:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_4, 
                                     BARGRAPH2_LED_SEG_2, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
        default:
        {
            drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0, 
                                     BARGRAPH2_LED_SEG_0 );
            break;
        }
    }
}

void bargraph2_leds_green ( bargraph2_t *ctx, int start_index, int end_index ) 
{
    uint8_t reg_1 = 0x00;
    uint8_t reg_2 = 0x00;

    int i = start_index;

    for( i = start_index; i <= end_index; i++ )
    {
        if ( i > 8 )
        {
            reg_2 |= drv_get_segment( i % 9 );
        }
        else
        {
            reg_1 |= drv_get_segment( i - 1 );
        }
    }

    drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, reg_2, reg_1 );
}

void bargraph2_leds_red ( bargraph2_t *ctx, int start_index, int end_index ) 
{
    uint8_t reg_2 = 0x00;
    uint8_t reg_3 = 0x00;

    int i = start_index;

    for( i = start_index; i <= end_index; i++ )
    {
        if ( i > 6 )
        {
            reg_3 |= drv_get_segment( i % 7 );
        }
        else
        {
            reg_2 |= drv_get_segment( i + 1 );
        }
    }

    drv_segment_switch( ctx, reg_3, reg_2, BARGRAPH2_LED_SEG_0 );
}

void bargraph2_leds_yellow ( bargraph2_t *ctx, int start_index, int end_index ) 
{
    uint8_t reg_1 = 0x00;
    uint8_t reg_2 = 0x00;
    uint8_t reg_3 = 0x00;

    int i = start_index;

    for( i = start_index; i <= end_index; i++ )
    {
        if ( i <= 6 )
        {
            reg_1 |= drv_get_segment( i - 1 );
            reg_2 |= drv_get_segment( i + 1 );
        }
        else if ( i > 6 & i < 9 ) 
        {
            reg_1 |= drv_get_segment( i - 1 );
            reg_3 |= drv_get_segment( i % 7 );
        }
        else
        {
            reg_2 |= drv_get_segment( i % 9 );
            reg_3 |= drv_get_segment( i % 7 );
        }
    }

    drv_segment_switch( ctx, reg_3, reg_2, reg_1 );
}

void bargraph2_lights_out ( bargraph2_t *ctx ) 
{
    drv_segment_switch( ctx, BARGRAPH2_LED_SEG_0, BARGRAPH2_LED_SEG_0, BARGRAPH2_LED_SEG_0 );
}

void barpgraph2_power ( bargraph2_t *ctx, uint8_t power_on_off )
{
    if ( 0 == power_on_off )
    {
        digital_out_low( &ctx->pwm );
    }
    else
    {
        digital_out_high( &ctx->pwm );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
 
static void drv_segment_switch ( bargraph2_t *ctx, uint8_t reg_3, 
uint8_t reg_2, uint8_t reg_1 )
{    
    bargraph2_reset( ctx );

    bargraph2_write_byte( ctx, reg_3 );
    bargraph2_write_byte( ctx, reg_2 );
    bargraph2_write_byte( ctx, reg_1 );
}

static uint8_t drv_get_segment ( uint8_t index )
{
    uint8_t segment_index = index;
    
    switch ( segment_index ) 
    {
        case 0:
        {
            return BARGRAPH2_LED_SEG_1;            
        }
        case 1:
        {
            return BARGRAPH2_LED_SEG_2;
        }
        case 2:
        {
            return BARGRAPH2_LED_SEG_3;
        }
        case 3:
        {
            return BARGRAPH2_LED_SEG_4;
        }
        case 4:
        {
            return BARGRAPH2_LED_SEG_5;
        }    
        case 5:
        {
            return BARGRAPH2_LED_SEG_6;
        }
        case 6:
        {
            return BARGRAPH2_LED_SEG_7;
        }
        case 7:
        {
            return BARGRAPH2_LED_SEG_8;
        }
        default:
        {
            return BARGRAPH2_LED_SEG_0;
        }
    }
}

// ------------------------------------------------------------------------- END

