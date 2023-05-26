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

#include "angle3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ANGLE3_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void angle3_cfg_setup ( angle3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    cfg->spi_mode = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t angle3_init ( angle3_t *ctx, angle3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, ANGLE3_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Output pins 
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ANGLE3_OK;
}

void angle3_default_cfg ( angle3_t *ctx )
{
    ANGLE3_SET_DATA_SAMPLE_EDGE;
    angle3_set_normal_mode( ctx );
}

void angle3_write_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg, uint16_t write_data )
{
    uint8_t tx_buf[ 3 ] = { 0 };

    reg <<= 1;

    tx_buf[ 0 ] = ( opcode << 4 ) | ( reg >> 4 );
    tx_buf[ 1 ] = ( reg << 4 ) | (( write_data >> 8 ) & 0x0F );
    tx_buf[ 2 ] = write_data & 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
}

uint16_t angle3_read_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg )
{
    uint8_t tx_buf[ 1 ] = { 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t raw_data = 0;

    reg <<= 1;

    tx_buf[ 0 ] = ( opcode << 4 ) | ( reg >> 4 );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_set_default_write_data( &ctx->spi, reg << 4 );
    spi_master_read( &ctx->spi, &rx_buf[0], 1 );
    spi_master_set_default_write_data( &ctx->spi, ANGLE3_REG_ANG );
    spi_master_read( &ctx->spi, &rx_buf[1], 1 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, ANGLE3_DUMMY );

    raw_data = rx_buf[ 0 ];
    raw_data <<= 8;
    raw_data |= rx_buf[ 1 ];

    return raw_data;
}

void angle3_write_eeprom ( angle3_t* ctx, uint8_t reg_addr, uint16_t write_data )
{
    angle3_write_data( ctx, ANGLE3_OPCODE_WRITE_EEPROM, reg_addr, write_data);
}

uint16_t angle3_read_eeprom ( angle3_t* ctx, uint8_t reg_addr )
{
    uint16_t result = 0;

    result = angle3_read_data( ctx, ANGLE3_OPCODE_READ_EEPROM, reg_addr);

    result &= 0x0FFF;

    return result;
}

void angle3_lock_eeprom ( angle3_t* ctx )
{
    angle3_write_eeprom ( ctx, ANGLE3_EEPROM_MLK, ANGLE3_OPCODE_LOCK_EEPROM);
}

void angle3_write_register ( angle3_t* ctx, uint8_t reg_addr, uint16_t write_data )
{
    angle3_write_data( ctx, ANGLE3_OPCODE_WRITE_REG, reg_addr, write_data );
}

uint16_t angle3_read_register ( angle3_t* ctx, uint8_t reg_addr )
{
    uint16_t result = 0;

    result = angle3_read_data ( ctx, ANGLE3_OPCODE_READ_REG, reg_addr );

    result &= 0x0FFF;

    return result;
}

void angle3_set_mode ( angle3_t* ctx, uint16_t set_mode )
{
    angle3_write_data( ctx, ANGLE3_OPCODE_CHANGE_MODE, ANGLE3_REG_CHMD, set_mode);
}

void angle3_set_normal_mode ( angle3_t* ctx )
{
    angle3_set_mode( ctx, ANGLE3_NORMAL_MODE );
}

void angle3_set_user_mode ( angle3_t* ctx )
{
    angle3_set_mode( ctx, ANGLE3_USER_MODE );
}

uint16_t angle3_read_angle_data ( angle3_t* ctx )
{
    uint16_t result = 0;

    result = angle3_read_data( ctx, ANGLE3_OPCODE_READ_ANGLE, ANGLE3_REG_ANG );

    result &= 0x0FFF;

    return result;
}

float angle3_calculate_degrees ( angle3_t* ctx, uint16_t angle )
{
    float result = 0;

    result = ( 360 * ( float ) angle ) / 4096;

    return result;
}

uint8_t angle3_read_error ( angle3_t* ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------ END
