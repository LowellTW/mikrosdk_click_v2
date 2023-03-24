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

#include "expand4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EXPAND4_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void expand4_cfg_setup ( expand4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->clr = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

EXPAND4_RETVAL expand4_init ( expand4_t *ctx, expand4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EXPAND4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EXPAND4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EXPAND4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->clr, cfg->clr );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->en );
    digital_out_high( &ctx->clr );

    return EXPAND4_OK;
}

void expand4_enable_output ( expand4_t *ctx )
{
    digital_out_low( &ctx->en );
}

void expand4_disable_output ( expand4_t *ctx )
{
    digital_out_high( &ctx->en );
}

void expand4_reset ( expand4_t *ctx )
{
    digital_out_low( &ctx->clr );
    Delay_100ms( );
    digital_out_high( &ctx->clr );
    Delay_100ms( );
}

void expand4_write_data ( expand4_t *ctx, uint8_t write_command )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &write_command, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void expand4_turn_on_by_position ( expand4_t *ctx, uint8_t position )
{
    expand4_write_data( ctx, EXPAND4_D0 << position );
}

// ------------------------------------------------------------------------- END

