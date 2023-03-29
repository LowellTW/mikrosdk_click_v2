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

#include "c3dhall3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C3DHALL3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c3dhall3_i2c_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall3_i2c_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall3_spi_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall3_spi_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3dhall3_cfg_setup ( c3dhall3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ccs = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x1E;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->sel = C3DHALL3_MASTER_I2C;
}

C3DHALL3_RETVAL c3dhall3_init ( c3dhall3_t *ctx, c3dhall3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C3DHALL3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed  = cfg->i2c_speed;
        i2c_cfg.scl    = cfg->scl;
        i2c_cfg.sda    = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C3DHALL3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        digital_out_write( &ctx->ccs, 1 );
        
        ctx->read_f = c3dhall3_i2c_read;
        ctx->write_f = c3dhall3_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed     = cfg->spi_speed;
        spi_cfg.sck       = cfg->sck;
        spi_cfg.miso      = cfg->miso;
        spi_cfg.mosi      = cfg->mosi;

        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
        {
            return  C3DHALL3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C3DHALL3_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
       
        digital_out_write( &ctx->ccs, 1 );
        
        ctx->read_f = c3dhall3_spi_read;
        ctx->write_f = c3dhall3_spi_write;

    }
    // Output pins 

    digital_out_init( &ctx->ccs, cfg->ccs );
 
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return C3DHALL3_OK;
}

void c3dhall3_default_cfg ( c3dhall3_t *ctx )
{
    uint8_t aux_buffer[ 1 ];

    aux_buffer[ 0 ] =  C3DHALL3_CFGA_REBOOT_MEMORY | 
                       C3DHALL3_CFGA_SOFT_RESET | 
                       C3DHALL3_CFGA_MODE_CONTINIOUS;
    ctx->write_f( ctx, C3DHALL3_CONFIGURATION_REGISTER_A, aux_buffer, 1 );

    Delay_100ms( );

    aux_buffer[ 0 ] =  C3DHALL3_CFGA_TEMPERATURE_COMPENSATION | 
                       C3DHALL3_CFGA_OUTPUT_DATA_RATE_100 | 
                       C3DHALL3_CFGA_MODE_CONTINIOUS;
    ctx->write_f( ctx, C3DHALL3_CONFIGURATION_REGISTER_A, aux_buffer, 1 );

    aux_buffer[ 0 ] =  C3DHALL3_CFGC_ASYNC_DATA_READ | C3DHALL3_CFGC_DATA_READY_ON_INT;
    ctx->write_f( ctx, C3DHALL3_CONFIGURATION_REGISTER_C, aux_buffer, 1 );
}

void c3dhall3_generic_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c3dhall3_generic_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c3dhall3_read_status ( c3dhall3_t *ctx )
{
    uint8_t aux_buffer[ 1 ];

    ctx->read_f( ctx, C3DHALL3_STATUS, aux_buffer, 1 );

    return aux_buffer[ 0 ];
}

int16_t c3dhall3_read_x ( c3dhall3_t *ctx )
{
    uint16_t out_x;
    uint8_t aux_buffer[2];

    ctx->read_f( ctx, C3DHALL3_OUTX_L, aux_buffer, 2 );
    
    out_x = aux_buffer[ 1 ];
    out_x <<= 8;
    out_x |= aux_buffer[ 0 ];

    return out_x;
}

int16_t c3dhall3_read_y ( c3dhall3_t *ctx )
{
    int16_t out_y;
    uint8_t aux_buffer[ 2 ];

    ctx->read_f( ctx, C3DHALL3_OUTY_L, aux_buffer, 2 );

    out_y = aux_buffer[ 1 ];
    out_y <<= 8;
    out_y |= aux_buffer[ 0 ];

    return out_y;
}

int16_t c3dhall3_read_z ( c3dhall3_t *ctx )
{
    int16_t out_z;
    uint8_t aux_buffer[ 2 ];

    ctx->read_f( ctx, C3DHALL3_OUTZ_L, aux_buffer, 2 );

    out_z = aux_buffer[ 1 ];
    out_z <<= 8;
    out_z |= aux_buffer[ 0 ];

    return out_z;
}

void c3dhall3_read_xyz ( c3dhall3_t *ctx, int16_t *out_xyz )
{
    uint8_t aux_buffer[ 6 ];

    ctx->read_f( ctx, C3DHALL3_OUTX_L, aux_buffer, 6 );
    
    out_xyz[ 0 ] = aux_buffer[1];
    out_xyz[ 0 ] <<= 8;
    out_xyz[ 0 ] |= aux_buffer[0];

    out_xyz[ 1 ] = aux_buffer[3];
    out_xyz[ 1 ] <<= 8;
    out_xyz[ 1 ] |= aux_buffer[2];

    out_xyz[ 2 ] = aux_buffer[5];
    out_xyz[ 2 ] <<= 8;
    out_xyz[ 2 ] |= aux_buffer[4];
}

void c3dhall3_write_offset ( c3dhall3_t *ctx, uint8_t axis, uint16_t offset )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = ( offset & 0x00FF );
    aux_buffer[ 1 ] = ( offset >> 8) & 0x00FF;

    ctx->write_f( ctx, offset, aux_buffer, 2 );
}

uint8_t c3dhall3_read_interrupt_source ( c3dhall3_t *ctx )
{
    uint8_t aux_buffer[ 1 ];

    ctx->read_f( ctx, C3DHALL3_INT_SOURCE, aux_buffer, 1  );

    return aux_buffer[ 0 ];
}

void c3dhall3_interrupt_threshold ( c3dhall3_t *ctx, uint16_t threshold )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = ( threshold & 0x00FF );
    aux_buffer[ 1 ] = ( threshold >> 8 ) & 0x00FF;
    
    ctx->write_f( ctx, C3DHALL3_INT_THS_L, aux_buffer, 2 );
}

uint8_t c3dhall3_check_int_pin ( c3dhall3_t *ctx )
{
    uint8_t int_pin_status;

    int_pin_status = digital_in_read( &ctx->int_pin );

    return int_pin_status;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c3dhall3_i2c_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c3dhall3_i2c_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c3dhall3_spi_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    digital_out_high( &ctx->ccs );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void c3dhall3_spi_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    digital_out_high( &ctx->ccs );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    digital_out_low( &ctx->ccs );
    spi_master_read( &ctx->spi, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}
// ------------------------------------------------------------------------- END

