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

#include "mpuimu.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MPUIMU_DUMMY 0

// Temperature calculation constant

#define MPUIMU_TEMP_CALC_CONST   36.54 

// Temperature calculation factor

#define MPUIMU_TEMP_CALC_FACT    340

#define MPUIMU_SPI_READ_CMD      0x80

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void mpuimu_i2c_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void mpuimu_i2c_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void mpuimu_spi_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void mpuimu_spi_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mpuimu_cfg_setup ( mpuimu_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->fsy     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MPUIMU_I2C_ADDR_1;

    cfg->spi_speed   = 1000000; 
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel         = MPUIMU_MASTER_I2C;
}

MPUIMU_RETVAL mpuimu_init ( mpuimu_t *ctx, mpuimu_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == MPUIMU_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return MPUIMU_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        i2c_master_set_timeout( &ctx->i2c, 0 );

        ctx->read_f  = mpuimu_i2c_read;
        ctx->write_f = mpuimu_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = MPUIMU_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  MPUIMU_INIT_ERROR;
        }
         
        spi_master_set_default_write_data( &ctx->spi, MPUIMU_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f  = mpuimu_spi_read;
        ctx->write_f = mpuimu_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->fsy, cfg->fsy );
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return MPUIMU_OK;
}

void mpuimu_default_cfg ( mpuimu_t *ctx )
{
    uint8_t buf;
        
    // Enables Accel and Gyro data registers to be written into the FIFO buffer.
    buf = MPUIMU_CFG_FIFO_ENABLE;
    mpuimu_generic_write( ctx, MPUIMU_REG_FIFO_EN, &buf, 1 );
    dev_comm_delay( );
    
    // Enables that FIFO buffer overflow will generate an interrupt.
    buf = MPUIMU_CFG_INT_ENABLE;
    mpuimu_generic_write( ctx, MPUIMU_REG_INT_ENABLE, &buf, 1 );
    dev_comm_delay( );
}

void mpuimu_generic_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void mpuimu_generic_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

int16_t mpuimu_get_axis ( mpuimu_t *ctx, uint8_t adr_reg_high )
{
    uint16_t result;
    uint8_t buf_lsb;
    uint8_t buf_msb;

    mpuimu_generic_read( ctx, adr_reg_high, &buf_msb, 1 );
    mpuimu_generic_read( ctx, adr_reg_high + 1, &buf_lsb, 1 );

    result = buf_msb;
    result <<= 8;
    result |= buf_lsb;

    return result;
}

void mpuimu_read_accel ( mpuimu_t *ctx, mpuimu_accel_data_t *accel_data )
{
    accel_data->accel_x = mpuimu_get_axis( ctx, MPUIMU_ACCEL_XOUT_H );
    accel_data->accel_y = mpuimu_get_axis( ctx, MPUIMU_ACCEL_YOUT_H );
    accel_data->accel_z = mpuimu_get_axis( ctx, MPUIMU_ACCEL_ZOUT_H );
}

void mpuimu_read_gyro ( mpuimu_t *ctx, mpuimu_gyro_data_t *gyro_data )
{
    gyro_data->gyro_x = mpuimu_get_axis( ctx, MPUIMU_GYRO_XOUT_H );
    gyro_data->gyro_y = mpuimu_get_axis( ctx, MPUIMU_GYRO_YOUT_H );
    gyro_data->gyro_z = mpuimu_get_axis( ctx, MPUIMU_GYRO_ZOUT_H );
}

float mpuimu_read_temperature ( mpuimu_t *ctx )
{
    float temperature;
    int16_t result;
    uint8_t buf_low;
    uint8_t buf_high;
    
    mpuimu_generic_read( ctx, MPUIMU_TEMP_OUT_H, &buf_high, 1 );
    mpuimu_generic_read( ctx, MPUIMU_TEMP_OUT_L, &buf_low, 1 );

    result = buf_high;
    result <<= 8;
    result |= buf_low;
    
    temperature  =  ( float ) result;
    temperature /=  MPUIMU_TEMP_CALC_FACT;
    temperature +=  MPUIMU_TEMP_CALC_CONST;

    return temperature;
}

void software_reset ( mpuimu_t *ctx )
{
    uint8_t buf;
    
    //  Resets all internal registers to their default values.
    buf = MPUIMU_CFG_PWR;
    mpuimu_generic_write( ctx, MPUIMU_REG_PWR_MGMT_1, &buf, 1 );
    dev_comm_delay( );
    
    buf = MPUIMU_CFG_PWR_SET;
    mpuimu_generic_write( ctx, MPUIMU_REG_PWR_MGMT_1, &buf, 1 );
    dev_comm_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void mpuimu_i2c_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void mpuimu_i2c_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void mpuimu_spi_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

static void mpuimu_spi_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void dev_comm_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

