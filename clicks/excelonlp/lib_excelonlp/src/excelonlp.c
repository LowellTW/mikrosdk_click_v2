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

#include "excelonlp.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EXCELONLP_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void excelonlp_cfg_setup ( excelonlp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

EXCELONLP_RETVAL excelonlp_init ( excelonlp_t *ctx, excelonlp_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EXCELONLP_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EXCELONLP_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EXCELONLP_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 

    digital_out_init( &ctx->wp, cfg->wp );

    return EXCELONLP_OK;
}

void excelonlp_generic_transfer ( excelonlp_t *ctx, uint8_t *wr_buf, 
    uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void excelonlp_send_command ( excelonlp_t *ctx, uint8_t opcode )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void excelonlp_read_data ( excelonlp_t *ctx, uint8_t opcode, uint8_t *out_buf, uint8_t n_data )
{    
    excelonlp_generic_transfer( ctx, &opcode, 1, out_buf, n_data );
}

void excelonlp_write_memory_data ( excelonlp_t *ctx, uint8_t opcode, uint32_t addr, uint8_t c_data)
{
    uint8_t tx_buf[ 5 ];

    tx_buf[ 0 ] = opcode;
    tx_buf[ 1 ] = ( addr >> 16 ) & 0x000000FF ;
    tx_buf[ 2 ] = ( addr >> 8  ) & 0x000000FF ;
    tx_buf[ 3 ] = addr & 0x000000FF;
    tx_buf[ 4 ] = c_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t excelonlp_read_memory_data ( excelonlp_t *ctx, uint8_t opcode, uint32_t addr )
{
    uint8_t write_reg[ 4 ];
    uint8_t read_reg[ 1 ];

    write_reg[ 0 ] = ( &ctx->spi, opcode );
    write_reg[ 1 ] = ( &ctx->spi, ( uint8_t ) ( ( addr >> 16 ) & 0x000000FF ) );
    write_reg[ 2 ] = ( &ctx->spi, ( uint8_t ) ( ( addr >> 8 ) & 0x000000FF ) );
    write_reg[ 3 ] = ( &ctx->spi, ( uint8_t ) ( addr & 0x000000FF ) );
    
    excelonlp_generic_transfer( ctx, write_reg, 4, read_reg, 1 );
     
    return read_reg[ 0 ];
}

// ------------------------------------------------------------------------- END

