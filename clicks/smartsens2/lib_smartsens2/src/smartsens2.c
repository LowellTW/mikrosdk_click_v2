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
 * @file smartsens2.c
 * @brief Smart Sens 2 Click Driver.
 */

#include "smartsens2.h"

#if SMARTSENS2_FLASH && SMARTSENS2_FLASHIMG
#include "bhi260_aux_bmm150_bmp390_bme688_flash.h"
#elif SMARTSENS2_FLASH
const unsigned char smartsens2_firmware_image[ ] = { 0 }; 
#elif SMARTSENS2_RAM
#include "bhi260_aux_bmm150_bmp390_bme688.h"
#else
#error FIRMWARE_SOURCE_DEFINED
#endif

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Float to uint32.
 * @details Union that converts float to uint32_t.
 */
union smartsens2_hif_float_u32
{
    float as_float;
    uint32_t reg;
};

/**
 * @brief Buffer status.
 * @details Buffer status enum.
 */
typedef enum
{
    SMARTSENS2_BUFFER_STATUS_OK,
    SMARTSENS2_BUFFER_STATUS_RELOAD
} buffer_status_t;

/*
 * Array base address "0" corresponds to virtual sensor id 245
 * Debug Data: 250 : event size : 18
 * 245 & 251 : Timestamp small Delta : event size : 2
 * 252 & 246 : Timestamp Large Delta : event size : 3
 * 253 & 247 : Full timestamp: event size: 6
 * 254 & 248 : Meta event: event size: 4
 * Filler: 255 : event size : 1
 */
static const uint8_t smartsens2_sysid_event_size[ 11 ] = { 2, 3, 6, 4, 0, 18, 2, 3, 6, 4, 1 };

/**
 * @brief Smart Sens 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartsens2_i2c_write ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart Sens 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartsens2_i2c_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart Sens 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartsens2_spi_write ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart Sens 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartsens2_spi_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Get information of a virtual sensor.
 * @details Function get information of a virtual sensor.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] sensor_id : Sensor ID of the virtual sensor
 * @param[out] info     : Reference to the data buffer to store the sensor info
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t smartsens2_hif_get_sensor_info ( smartsens2_t *ctx, uint8_t sensor_id, 
                                              struct smartsens2_sensor_info *info );

/**
 * @brief Configure a virtual sensor.
 * @details Function to configure a virtual sensor.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] sensor_id     : Sensor ID of the virtual sensor
 * @param[in] sample_rate   : Sample rate in Hz
 * @param[in] latency       : Report latency in milliseconds
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t smartsens2_hif_exec_sensor_conf_cmd ( smartsens2_t *ctx, uint8_t sensor_id,
                                                   float sample_rate, uint32_t latency );

/**
 * @brief Get data from the Non-wake-up/wake-up FIFO
 * @details Function to get data from the Non-wake-up/wake-up FIFO
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] reg           : Non-wake-up/wake-up FIFO reg.
 * @param[out] fifo         : Reference to the data buffer to store data from the FIFO.
 * @param[out] bytes_read   : Number of bytes read into the data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t smartsens2_hif_get_fifo ( smartsens2_t *ctx, uint8_t reg, uint8_t *fifo, uint16_t *bytes_read );

/**
 * @brief Parse fifo data.
 * @details Function to parse fifo data.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] source           : Non-wake-up/wake-up FIFO reg.
 * @param[in] fifo_p           : Fifo buffer data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t parse_fifo ( smartsens2_t *ctx, enum smartsens2_fifo_type source, 
                          struct smartsens2_fifo_buffer *fifo_p );

/**
 * @brief Get callback information.
 * @details Function to check for callback.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] sensor_id      : Sensor to check callback for.
 * @param[out] info          : Callback.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t get_callback_info ( smartsens2_t *ctx, uint8_t sensor_id, 
                                 struct smartsens2_fifo_parse_callback_table *info );

/**
 * @brief Get buffer status.
 * @details Function to check fifo buffer status.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] fifo_p           : Fifo buffer.
 * @param[in] event_size       : Event size.
 * @param[out] status          : Fifo buffer status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t get_buffer_status ( struct smartsens2_fifo_buffer *fifo_p, uint8_t event_size, buffer_status_t *status );

/**
 * @brief Get time stamp.
 * @details Function to get time stamp.
 * @param[in] ctx : Click context object.
 * See #smartsens2_t object definition for detailed explanation.
 * @param[in] source           : Fifo type.
 * @param[out] time_stamp      : Timestamp.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t get_time_stamp ( smartsens2_t *ctx, enum smartsens2_fifo_type source, uint32_t **time_stamp );

void smartsens2_cfg_setup ( smartsens2_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTSENS2_SLAVE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTSENS2_DRV_SEL_SPI;
}

void smartsens2_drv_interface_selection ( smartsens2_cfg_t *cfg, smartsens2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartsens2_init ( smartsens2_t *ctx, smartsens2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( SMARTSENS2_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = smartsens2_i2c_read;
        ctx->write_f = smartsens2_i2c_write;
        
        digital_out_t chip_select;
        digital_out_init( &chip_select, cfg->cs );
        digital_out_high( &chip_select );
    } 
    else 
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

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

        ctx->read_f  = smartsens2_spi_read;
        ctx->write_f = smartsens2_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SMARTSENS2_OK;
}

err_t smartsens2_default_cfg ( smartsens2_t *ctx ) 
{
    uint8_t read_data = 0;
    uint8_t work_buffer[ 2 ] = { 0 };
    /* HW reset */
    smartsens2_reset( ctx );
    /* Chip ID */
    smartsens2_byte_read( ctx, SMARTSENS2_REG_CHIP_ID, &read_data );
    if ( SMARTSENS2_CHIP_ID_VALUE != read_data )
    {
        return SMARTSENS2_ERROR;
    }
    /* Product ID */
    smartsens2_byte_read( ctx, SMARTSENS2_REG_FUSER2_PRODUCT_ID, &read_data );
    if ( SMARTSENS2_FUSER2_PRODUCT_ID_VALUE != read_data )
    {
        return SMARTSENS2_ERROR;
    }
    /* SW Reset */
    smartsens2_sw_reset( ctx );
    /* Set host interrupt */
    smartsens2_byte_write( ctx, SMARTSENS2_REG_HOST_INTERRUPT_CTRL, 0 );
    /* Set host intefrace */
    smartsens2_byte_write( ctx, SMARTSENS2_REG_HOST_INTERFACE_CTRL, 0 );
    /* Check Boot Status */
    smartsens2_byte_read( ctx, SMARTSENS2_REG_BOOT_STATUS, &read_data );
    if ( !(read_data & SMARTSENS2_BOOTSTATUS_HOST_INTERFACE_READY) )
    {
        return SMARTSENS2_ERROR;
    }
    /* Load FW */
    if ( smartsens2_power_on_device( ctx ) )
    {
        return SMARTSENS2_ERROR;
    }
    /* Check Error */
    smartsens2_byte_read( ctx, SMARTSENS2_REG_ERROR_VALUE, &read_data );
    if ( read_data )
    {
        return SMARTSENS2_ERROR;
    }
    /* Wait until host intefrace is ready */
    do
    {
        Delay_10ms( );
        smartsens2_byte_read( ctx, SMARTSENS2_REG_BOOT_STATUS, &read_data );
    } while ( !( read_data & SMARTSENS2_BOOTSTATUS_HOST_INTERFACE_READY ) );
    /* Check Kernel Vesion */
    smartsens2_generic_read( ctx, SMARTSENS2_REG_KERNEL_VERSION, work_buffer, 2 );
    if ( !( work_buffer[ 0 ] | ( ( uint16_t )work_buffer[ 1 ] << 8 ) ) )
    {
        return SMARTSENS2_ERROR;
    }
    /* Check Feature Status */    
    smartsens2_byte_read( ctx, SMARTSENS2_REG_FEATURE_STATUS, &read_data );
    if ( !read_data )
    {
        return SMARTSENS2_ERROR;
    }
    return SMARTSENS2_OK;
}

err_t smartsens2_generic_write ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smartsens2_generic_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t smartsens2_byte_write ( smartsens2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return smartsens2_generic_write( ctx, reg, &data_in, 1 );
}

err_t smartsens2_byte_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return smartsens2_generic_read( ctx, reg, data_out, 1 );
}

uint8_t smartsens2_get_interrupt ( smartsens2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t smartsens2_cmd_write ( smartsens2_t *ctx, uint16_t cmd, uint8_t *cmd_buf, uint16_t cmd_len )
{
    uint8_t write_buf[ 0xFF ] = { 0 };
    
    uint16_t cmd_size = cmd_len;
    
    while( cmd_size % 4 )
    {
        cmd_size = ( ( cmd_size >> 2 ) + 1 ) << 2;
    }

    write_buf[ 0 ] = ( uint8_t ) cmd;
    write_buf[ 1 ] = ( uint8_t ) ( cmd >> 8 );
    write_buf[ 2 ] = ( uint8_t ) cmd_len;
    write_buf[ 3 ] = ( uint8_t ) ( cmd_len >> 8 );
    
    for ( uint32_t cnt = 4; cnt < cmd_len + 4; cnt++ )
    {
        write_buf[ cnt ] = *( cmd_buf++ );
    }
    
    return smartsens2_generic_write( ctx, SMARTSENS2_REG_COMMAND_INPUT, write_buf, cmd_len + 4 );
}

err_t smartsens2_status_read ( smartsens2_t *ctx, uint16_t *cmd, uint8_t *cmd_buf, uint16_t *cmd_len )
{
    uint8_t temp_buf[ 4 ] = { 0 };
    
    err_t ret_val = smartsens2_generic_read( ctx, SMARTSENS2_REG_STATUS_DEBUG_FIFO, temp_buf, 4 );
    *cmd = temp_buf[ 0 ] | ( ( uint16_t )temp_buf[ 1 ] << 8 );
    *cmd_len = temp_buf[ 2 ] | ( ( uint16_t )temp_buf[ 3 ] << 8 );
    if ( *cmd_len )
    {
        ret_val |= smartsens2_generic_read( ctx, SMARTSENS2_REG_STATUS_DEBUG_FIFO, cmd_buf, *cmd_len );
    }
    
    return ret_val;
}

err_t smartsens2_get_parameter ( smartsens2_t *ctx, uint16_t parameter, uint8_t *parameter_buf, uint16_t *parameter_len )
{
    int16_t timeout = 1000;
    uint16_t parameter_cpy = parameter;
    uint8_t intefrace_ctrl = 0;
    uint8_t intefrace_ctrl_save = 0;
    if ( smartsens2_byte_read( ctx, SMARTSENS2_REG_HOST_INTERFACE_CTRL, &intefrace_ctrl_save ) )
    {
        return SMARTSENS2_ERROR;
    }
    else
    {
        intefrace_ctrl &= (uint8_t)(~(SMARTSENS2_HIF_CTRL_ASYNC_STATUS_CHANNEL));
        if ( smartsens2_byte_write( ctx, SMARTSENS2_REG_HOST_INTERFACE_CTRL, intefrace_ctrl ) )
        {
            return SMARTSENS2_ERROR;
        }
    }
    
    err_t ret_val = smartsens2_cmd_write( ctx, parameter | SMARTSENS2_CMD_SYSTEM_PARAMETERS_READ_MASK, NULL, 0 );
    while ( timeout-- && !ret_val )
    {
        uint8_t int_status;
        ret_val |= smartsens2_byte_read( ctx, SMARTSENS2_REG_INTERRUPT_STATUS, &int_status );
        if ( ret_val || ( int_status & SMARTSENS2_IST_MASK_STATUS ) )
        {
            break;
        }
        Delay_10ms( );
    }
    if ( ( timeout < 0 ) || ret_val )
    {
        return SMARTSENS2_ERROR;
    }
    
    ret_val |= smartsens2_status_read( ctx, &parameter_cpy, parameter_buf, parameter_len );
    
    if ( parameter_cpy != parameter )
    {
        return SMARTSENS2_ERROR;
    }
    
    ret_val |= smartsens2_byte_write( ctx, SMARTSENS2_REG_HOST_INTERFACE_CTRL, intefrace_ctrl_save );
    
    return ret_val;
}

void smartsens2_reset ( smartsens2_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1ms();
    digital_out_high( &ctx->rst );
    Delay_1sec();
}

err_t smartsens2_sw_reset ( smartsens2_t *ctx )
{
    uint8_t temp_data = 1;
    err_t ret_val = smartsens2_byte_write( ctx, SMARTSENS2_REG_RESET_REQUEST, temp_data );
    do 
    {
        Delay_1ms();
        ret_val |= smartsens2_byte_read( ctx, SMARTSENS2_REG_RESET_REQUEST, &temp_data );
        
    } while( temp_data & 1 );
    Delay_1sec( );
    return ret_val;
}

err_t smartsens2_update_firmware ( smartsens2_t *ctx )
{
    err_t ret_val = SMARTSENS2_OK;
    uint32_t step = 240;
    uint8_t temp[ 0x1FF ] = { 0 };
    uint32_t cnt = 0;
    uint32_t remaining = sizeof( smartsens2_firmware_image );
    uint8_t status;
    
#if SMARTSENS2_FLASH
        volatile uint32_t start_addr = SMARTSENS2_START_FLASH_ADR;        
        //ERASE
        temp[ 0 ] = start_addr;
        temp[ 1 ] = start_addr >> 8;
        temp[ 2 ] = start_addr >> 16;
        temp[ 3 ] = start_addr >> 24;
        temp[ 4 ] = ( start_addr + remaining );
        temp[ 5 ] = ( start_addr + remaining ) >> 8;
        temp[ 6 ] = ( start_addr + remaining ) >> 16;
        temp[ 7 ] = ( start_addr + remaining ) >> 24;
        smartsens2_cmd_write( ctx, SMARTSENS2_CMD_ERASE_FLASH, temp, 8 );
        
        do 
        {
            smartsens2_byte_read( ctx, SMARTSENS2_REG_ERROR_VALUE, &status );
            if ( status )
            {
                return status;
            }
            smartsens2_byte_read( ctx, SMARTSENS2_REG_INTERRUPT_STATUS, &status );
            Delay_10ms( );
        } while ( !( status & 0x20 ) );
        volatile uint16_t cmd;
        volatile uint16_t cmd_len;
        volatile uint8_t cmd_buf[ 0xFF ] = { 0 };
        smartsens2_status_read( ctx, &cmd, cmd_buf, &cmd_len );
        if ( 0x000F == cmd )
        {
            return SMARTSENS2_ERROR;
        }
        //DONE ERASE
        
        //WRITE FLASH 
        start_addr = SMARTSENS2_START_FLASH_ADR; 
        
        do
        {
            volatile uint32_t size;
            if ( remaining > step )
            {
                remaining -= step;
                size = step + 4;
            }
            else
            {
                size = remaining + 4;
                remaining = 0;
            }
            
            temp[ 0 ] = start_addr;
            temp[ 1 ] = start_addr >> 8;
            temp[ 2 ] = start_addr >> 16;
            temp[ 3 ] = start_addr >> 24;
            memcpy( &temp[ 4 ], &smartsens2_firmware_image[ cnt ], size );
            cnt += size - 4;
            
            smartsens2_cmd_write( ctx, SMARTSENS2_CMD_WRITE_FLASH, temp, size );
            
            do 
            {
                smartsens2_byte_read( ctx, SMARTSENS2_REG_INTERRUPT_STATUS, &status );
                Delay_10ms( );
            } while ( !( status & 0x20 ) );
            
            smartsens2_status_read( ctx, &cmd, cmd_buf, &cmd_len );
            
            if ( 0x000F == cmd )
            {
                ret_val = SMARTSENS2_ERROR;
                break;
            }
            
            start_addr += ( size - 4 );
            
        } while ( remaining );
        
#elif SMARTSENS2_RAM
        
        uint32_t enc = 0;     
        uint16_t temp_index = 0;
        
        temp[ 0 ] = ( uint8_t )SMARTSENS2_CMD_UPLOAD_TO_RAM;
        temp[ 1 ] = ( uint8_t )( SMARTSENS2_CMD_UPLOAD_TO_RAM >> 8 );
        uint16_t size = sizeof( smartsens2_firmware_image ) / 4;
        temp[ 2 ] = ( uint8_t )size;
        temp[ 3 ] = ( uint8_t )( size >> 8 );
        while ( cnt < sizeof( smartsens2_firmware_image ) )
        {
            if ( !(enc++) )
            {
                temp_index = 4;
            }
            else
            {
                temp_index = 0;
            }

            while ( 0 != ( cnt % 4 ) )
            {
                cnt = ( ( cnt >> 2 ) + 1 ) << 2;
            }
            
            volatile uint32_t limit = step * enc;
            
            for ( ; ( cnt < limit ) && ( cnt < sizeof( smartsens2_firmware_image ) ); cnt++ )
            {
                temp[ temp_index++ ] = smartsens2_firmware_image[ cnt ];
            }
            
            smartsens2_generic_write( ctx, SMARTSENS2_REG_COMMAND_INPUT, temp, temp_index );
        }
        
        do
        {
            Delay_10ms( );
            smartsens2_byte_read( ctx, SMARTSENS2_REG_BOOT_STATUS, &status );
            
        } while ( !( status & SMARTSENS2_BOOTSTATUS_HOST_FW_VERIFY_DONE ) );
        
#endif
    return ret_val;
}

err_t smartsens2_boot_firmware( smartsens2_t *ctx )
{
    err_t ret_val = SMARTSENS2_OK;
    volatile uint8_t status;
    uint16_t cmd;
    uint16_t cmd_len;
    uint8_t cmd_buf[ 0xFF ] = { 0 };
    
#if SMARTSENS2_FLASH
        
    smartsens2_cmd_write( ctx, SMARTSENS2_CMD_BOOT_FLASH, 0, 0 );
    
    do
    {
        Delay_10ms(  );
        Delay_10ms(  );
        Delay_10ms(  );
        Delay_10ms(  );
        Delay_10ms(  );
        smartsens2_byte_read( ctx, SMARTSENS2_REG_BOOT_STATUS, &status );
     } while ( !( status & SMARTSENS2_BOOTSTATUS_FLASH_VERIFY_DONE ) && 
               !( status & SMARTSENS2_BOOTSTATUS_FLASH_VERIFY_ERROR ) && 
               !( status & SMARTSENS2_BOOTSTATUS_HOST_INTERFACE_READY ) );
        
    if ( status & SMARTSENS2_BOOTSTATUS_FLASH_VERIFY_ERROR )
    {     
        smartsens2_reset( ctx );
        smartsens2_sw_reset( ctx );
        
        status = 0;
        do
        {
            if ( status )
            {
                smartsens2_byte_read( ctx, SMARTSENS2_REG_INTERRUPT_STATUS, &status );
                status &= 0xA0;
                if ( status )
                {
                    smartsens2_status_read( ctx, &cmd, cmd_buf, &cmd_len );
                }
            }
            smartsens2_byte_read( ctx, SMARTSENS2_REG_ERROR_VALUE, &status );
            
        } while ( status );
            
        
        ret_val = SMARTSENS2_ERROR;
    }
    else if ( status & SMARTSENS2_BOOTSTATUS_FLASH_VERIFY_DONE )
    {
        ret_val = SMARTSENS2_OK;
    }
#elif SMARTSENS2_RAM
    ret_val = smartsens2_cmd_write( ctx, SMARTSENS2_CMD_BOOT_RAM, 0, 0 );
#endif
    return ret_val;
}

err_t smartsens2_power_on_device( smartsens2_t *ctx )
{
    err_t ret_val = SMARTSENS2_ERROR;    
    if ( smartsens2_sw_reset( ctx ) )
    {
        return SMARTSENS2_ERROR;
    }
#if ( SMARTSENS2_FLASH == 1 ) && ( SMARTSENS2_FLASHIMG == 0 )
    if ( smartsens2_boot_firmware( ctx ) )
#endif
    {
        if ( smartsens2_update_firmware( ctx ) )
        {
            return SMARTSENS2_ERROR;
        }
        else
        {
            if ( smartsens2_boot_firmware( ctx ) )
            {
                return SMARTSENS2_ERROR;
            }
        }
    }
    return SMARTSENS2_OK;
}

err_t smartsens2_update_virtual_sensor_list ( smartsens2_t *ctx )
{
    err_t ret_val = SMARTSENS2_OK;
    uint8_t sensor_id;
    struct smartsens2_sensor_info info;
    uint8_t present_buff[ 32 ];
    uint8_t sensor_index;
    uint8_t bit_mask;

    /* Each bit corresponds to presence of Virtual sensor */
    ret_val |= smartsens2_get_virt_sensor_list( ctx, present_buff );
    if ( SMARTSENS2_OK == ret_val )
    {
        /* Padding: Sensor id*/
        ctx->table[ 0 ].event_size = 1;

        for ( sensor_id = 1; 
              ( sensor_id < SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET ) && ( SMARTSENS2_OK == ret_val ); 
              sensor_id++ )
        {
            sensor_index = ( uint8_t )( sensor_id / 8.0 );
            bit_mask = ( uint8_t )( 0x01 << ( sensor_id % 8 ) );

            if ( present_buff[ sensor_index ] & bit_mask )
            {
                ret_val = smartsens2_hif_get_sensor_info( ctx, sensor_id, &info );
                if ( SMARTSENS2_OK == ret_val )
                {
                    if ( 0 == info.event_size )
                    {
                        ret_val = SMARTSENS2_ERROR;
                        break;
                    }
                    else
                    {
                        ctx->table[ sensor_id ].event_size = info.event_size;
                    }
                }
            }
        }

        for ( sensor_id = SMARTSENS2_N_VIRTUAL_SENSOR_MAX - 1; sensor_id >= SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET; sensor_id-- )
        {
            ctx->table[ sensor_id ].event_size = smartsens2_sysid_event_size[ sensor_id - SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET ];
        }
    }
    
    return ret_val;
}

err_t smartsens2_get_virt_sensor_list ( smartsens2_t *ctx, uint8_t *sensor_list )
{
    uint16_t sensor_len = 32;
    return smartsens2_get_parameter( ctx, SMARTSENS2_CMD_META_EVENT_CTRL_VIRUAL_SENSOR_PRESENT, sensor_list, &sensor_len );
}

err_t smartsens2_set_virt_sensor_cfg( smartsens2_t *ctx, uint8_t sensor_id, float sample_rate, uint32_t latency )
{
    return smartsens2_hif_exec_sensor_conf_cmd( ctx, sensor_id, sample_rate, latency );
}

err_t smartsens2_get_and_process_fifo( smartsens2_t *ctx, uint8_t *work_buffer, uint32_t buffer_size )
{
    uint8_t int_status, int_status_bak;
    uint16_t bytes_read = 0;
    err_t rslt;
    struct smartsens2_fifo_buffer fifos;

    if ( ( NULL == ctx ) || ( NULL == work_buffer ) )
    {
        return SMARTSENS2_ERROR;
    }

    if ( 0 == buffer_size )
    {
        return SMARTSENS2_ERROR;
    }

    memset( work_buffer, 0, buffer_size );
    memset( &fifos, 0, sizeof( struct smartsens2_fifo_buffer ) );

    fifos.buffer = work_buffer;
    fifos.buffer_size = buffer_size;

    rslt = smartsens2_byte_read( ctx, SMARTSENS2_REG_INTERRUPT_STATUS, &int_status_bak );
    if ( SMARTSENS2_OK != rslt )
    {
        return rslt;
    }

    /* Get and process the Wake up FIFO */
    fifos.read_length = 0;
    int_status = int_status_bak;
    while ( ( int_status || fifos.remain_length ) && ( SMARTSENS2_OK == rslt ) )
    {
        if ( ( ( SMARTSENS2_IS_INT_FIFO_W( int_status ) ) == SMARTSENS2_IST_FIFO_W_DRDY ) ||
             ( ( SMARTSENS2_IS_INT_FIFO_W( int_status ) ) == SMARTSENS2_IST_FIFO_W_LTCY ) ||
             ( ( SMARTSENS2_IS_INT_FIFO_W( int_status ) ) == SMARTSENS2_IST_FIFO_W_WM ) || 
               ( fifos.remain_length ) )
        {
            /* Reset read_pos to the start of the buffer */
            fifos.read_pos = 0;

            /* Append data into the work_buffer linked through fifos */
            rslt = smartsens2_hif_get_fifo( ctx, SMARTSENS2_REG_WAKE_UP_FIFO,
                                            &fifos.buffer[ fifos.read_length ], &bytes_read );
            if ( SMARTSENS2_OK != rslt )
            {
                return rslt;
            }
            fifos.read_length += bytes_read;
        }

        rslt = parse_fifo( ctx, SMARTSENS2_FIFO_TYPE_WAKEUP, &fifos );
        int_status = 0;
    }

    /* Get and process the Non Wake-up FIFO */
    fifos.read_length = 0;
    int_status = int_status_bak;
    while ( ( int_status || fifos.remain_length ) && ( rslt == SMARTSENS2_OK ) )
    {
        if ( ( ( SMARTSENS2_IS_INT_FIFO_NW( int_status ) ) == SMARTSENS2_IST_FIFO_NW_DRDY ) ||
            ( ( SMARTSENS2_IS_INT_FIFO_NW( int_status ) ) == SMARTSENS2_IST_FIFO_NW_LTCY ) ||
            ( ( SMARTSENS2_IS_INT_FIFO_NW( int_status ) ) == SMARTSENS2_IST_FIFO_NW_WM ) || ( fifos.remain_length ) )
        {
            /* Reset read_pos to the start of the buffer */
            fifos.read_pos = 0;

            /* Append data into the work_buffer linked through fifos */
            rslt = smartsens2_hif_get_fifo( ctx, SMARTSENS2_REG_NON_WAKE_UP_FIFO,
                                            &fifos.buffer[ fifos.read_length ], &bytes_read );
            
            if ( SMARTSENS2_OK != rslt )
            {
                return rslt;
            }
            fifos.read_length += bytes_read;
        }

        rslt = parse_fifo( ctx, SMARTSENS2_FIFO_TYPE_NON_WAKEUP, &fifos );
        int_status = 0;
    }

    /* Get and process the Status fifo */
    fifos.read_length = 0;
    int_status = int_status_bak;
    while ( ( int_status || fifos.remain_length ) && ( SMARTSENS2_OK == rslt ) )
    {
        if ( ( ( ( SMARTSENS2_IS_INT_ASYNC_STATUS( int_status ) ) == SMARTSENS2_IST_MASK_DEBUG ) || ( fifos.remain_length ) ) )
        {
            fifos.read_pos = 0;
            rslt = smartsens2_hif_get_fifo( ctx, SMARTSENS2_REG_STATUS_DEBUG_FIFO,
                                            &fifos.buffer[fifos.read_length], &bytes_read );
            if ( SMARTSENS2_OK != rslt )
            {
                return rslt;
            }
            fifos.read_length += bytes_read;
        }

        rslt = parse_fifo( ctx, SMARTSENS2_FIFO_TYPE_STATUS, &fifos );
        int_status = 0;
    }
    return rslt;
}

err_t smartsens2_register_fifo_parse_callback( smartsens2_t *ctx, uint8_t sensor_id,
                                              smartsens2_fifo_parse_callback_t callback,
                                              void *callback_ref )
{
    if ( ( NULL == ctx ) || ( NULL == callback ) )
    {
        return SMARTSENS2_ERROR;
    }
    else
    {
        ctx->table[ sensor_id ].callback = callback;
        ctx->table[ sensor_id ].callback_ref = callback_ref;
    }
    return SMARTSENS2_OK;
}

static err_t smartsens2_i2c_write ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t smartsens2_i2c_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smartsens2_spi_write ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t smartsens2_spi_read ( smartsens2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t smartsens2_hif_get_sensor_info ( smartsens2_t *ctx, uint8_t sensor_id, 
                                              struct smartsens2_sensor_info *info )
{
    volatile uint16_t length = 0;
    uint8_t bytes[ 28 ];

    if ( info != NULL )
    {
        /* Checking for a valid sensor ID */
        if ( sensor_id > SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET )
        {
            return SMARTSENS2_ERROR;
        }
        else
        {
            if ( SMARTSENS2_OK == smartsens2_get_parameter( ctx, ( uint16_t )( SMARTSENS2_CMD_VIRTUAL_SENSOR_INFO + sensor_id ), 
                                                            bytes, &length ) )
            {
                if ( length != 28 )
                {
                    return SMARTSENS2_ERROR;
                }
                else
                {
                    info->sensor_type = bytes[ 0 ];
                    info->driver_id = bytes[ 1 ];
                    info->driver_version = bytes[ 2 ];
                    info->power = bytes[ 3 ];
                    info->max_range.bytes[ 0 ] = bytes[ 4 ];
                    info->max_range.bytes[ 1 ] = bytes[ 5 ];
                    info->resolution.bytes[ 0 ] = bytes[ 6 ];
                    info->resolution.bytes[ 1 ] = bytes[ 7 ];
                    info->max_rate.bytes[ 0 ] = bytes[ 8 ];
                    info->max_rate.bytes[ 1 ] = bytes[ 9 ];
                    info->max_rate.bytes[ 2 ] = bytes[ 10 ];
                    info->max_rate.bytes[ 3 ] = bytes[ 11 ];
                    info->fifo_reserved.bytes[ 0 ] = bytes[ 12 ];
                    info->fifo_reserved.bytes[ 1 ] = bytes[ 13 ];
                    info->fifo_reserved.bytes[ 2 ] = bytes[ 14 ];
                    info->fifo_reserved.bytes[ 3 ] = bytes[ 15 ];
                    info->fifo_max.bytes[ 0 ] = bytes[ 16 ];
                    info->fifo_max.bytes[ 1 ] = bytes[ 17 ];
                    info->fifo_max.bytes[ 2 ] = bytes[ 18 ];
                    info->fifo_max.bytes[ 3 ] = bytes[ 19 ];
                    info->event_size = bytes[ 20 ];
                    info->min_rate.bytes[ 0 ] = bytes[ 21 ];
                    info->min_rate.bytes[ 1 ] = bytes[ 22 ];
                    info->min_rate.bytes[ 2 ] = bytes[ 23 ];
                    info->min_rate.bytes[ 3 ] = bytes[ 24 ];
                    info->max_range.u16_val = SMARTSENS2_LE2U16( info->max_range.bytes );
                    info->resolution.u16_val = SMARTSENS2_LE2U16( info->resolution.bytes );
                    info->max_rate.u32_val = SMARTSENS2_LE2U32( info->max_rate.bytes );
                    info->fifo_reserved.u32_val = SMARTSENS2_LE2U32( info->fifo_reserved.bytes );
                    info->fifo_max.u32_val = SMARTSENS2_LE2U32( info->fifo_max.bytes );
                    info->min_rate.u32_val = SMARTSENS2_LE2U32( info->min_rate.bytes );
                    return SMARTSENS2_OK;
                }
            }
        }
    }
    return SMARTSENS2_ERROR;
}

static err_t smartsens2_hif_exec_sensor_conf_cmd ( smartsens2_t *ctx, uint8_t sensor_id,
                                                   float sample_rate, uint32_t latency )
{
    uint8_t tmp_buf[ 8 ];
    union smartsens2_hif_float_u32 sample_rate_u;

    sample_rate_u.as_float = sample_rate;

    /* Sample rate is 32bits, latency is 24bits */
    tmp_buf[ 0 ] = sensor_id;
    tmp_buf[ 1 ] = ( uint8_t )( sample_rate_u.reg & 0xFF );
    tmp_buf[ 2 ] = ( uint8_t )( ( sample_rate_u.reg >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t )( ( sample_rate_u.reg >> 16 ) & 0xFF );
    tmp_buf[ 4 ] = ( uint8_t )( ( sample_rate_u.reg >> 24 ) & 0xFF );
    tmp_buf[ 5 ] = ( uint8_t )( latency & 0xFF);
    tmp_buf[ 6 ] = ( uint8_t )( ( latency >> 8 ) & 0xFF );
    tmp_buf[ 7 ] = ( uint8_t )( ( latency >> 16 ) & 0xFF );

    return smartsens2_cmd_write( ctx, SMARTSENS2_CMD_CONFIGURE_SENSOR, tmp_buf, 8 );
}

static err_t smartsens2_hif_get_fifo ( smartsens2_t *ctx, uint8_t reg, uint8_t *fifo, uint16_t *bytes_read )
{
    err_t rslt = SMARTSENS2_OK;
    uint8_t n_bytes[ 2 ];
    uint32_t read_len;
    uint32_t read_write_len = 64;
    uint32_t offset;
    uint32_t bytes_remain;

    if ( ( NULL != ctx ) && ( NULL != fifo ) && ( NULL != bytes_read ) )
    {
        rslt = smartsens2_generic_read( ctx, reg, n_bytes, 2 ); /* Read the available size */
        bytes_remain = SMARTSENS2_LE2U16(n_bytes);

        if ( bytes_remain && ( SMARTSENS2_OK == rslt ) )
        {
            *bytes_read = bytes_remain;
            read_len = *bytes_read;
            offset = 0;
            while ( read_len > read_write_len )
            {
                rslt = smartsens2_generic_read( ctx, reg, &fifo[offset], read_write_len );
                if ( SMARTSENS2_OK != rslt )
                {
                    break;
                }
                read_len -= read_write_len;
                offset += read_write_len;
            }

            if ( read_len )
            {
                rslt = smartsens2_generic_read( ctx, reg, &fifo[offset], read_len );
            }
            bytes_remain -= *bytes_read;
        }
    }
    else
    {
        rslt = SMARTSENS2_ERROR;
    }

    return rslt;
}

static err_t parse_fifo ( smartsens2_t *ctx, enum smartsens2_fifo_type source, struct smartsens2_fifo_buffer *fifo_p )
{
    uint8_t tmp_sensor_id = 0;
    err_t rslt = SMARTSENS2_OK;
    uint32_t tmp_read_pos;
    struct smartsens2_fifo_parse_data_info data_info;
    uint32_t *time_stamp;
    struct smartsens2_fifo_parse_callback_table info;
    buffer_status_t status = SMARTSENS2_BUFFER_STATUS_OK;

    for ( ; ( fifo_p->read_pos < fifo_p->read_length ) && ( SMARTSENS2_BUFFER_STATUS_OK == status ); )
    {
        tmp_read_pos = fifo_p->read_pos;
        tmp_sensor_id = fifo_p->buffer[tmp_read_pos];

        rslt = get_time_stamp( ctx, source, &time_stamp );
        if ( SMARTSENS2_OK != rslt )
        {
            return rslt;
        }
        switch ( tmp_sensor_id )
        {
            case SMARTSENS2_SYS_ID_FILLER:
            case SMARTSENS2_SYS_ID_PADDING:
                fifo_p->read_pos += 1;
                break;
            case SMARTSENS2_SYS_ID_TS_SMALL_DELTA_WU:
            case SMARTSENS2_SYS_ID_TS_SMALL_DELTA:
                rslt = get_buffer_status( fifo_p, 2, &status );
                if ( SMARTSENS2_OK != rslt )
                {
                    return rslt;
                }
                if ( SMARTSENS2_BUFFER_STATUS_OK != status )
                {
                    break;
                }
                *time_stamp += fifo_p->buffer[ tmp_read_pos + 1 ];
                fifo_p->read_pos += 2;
                break;
            case SMARTSENS2_SYS_ID_TS_LARGE_DELTA:
            case SMARTSENS2_SYS_ID_TS_LARGE_DELTA_WU:
                rslt = get_buffer_status( fifo_p, 3, &status );
                if ( SMARTSENS2_OK != rslt )
                {
                    return rslt;
                }
                if ( SMARTSENS2_BUFFER_STATUS_OK != status )
                {
                    break;
                }
                *time_stamp += SMARTSENS2_LE2U16( fifo_p->buffer + tmp_read_pos + 1 );
                fifo_p->read_pos += 3;
                break;
            case SMARTSENS2_SYS_ID_TS_FULL:
            case SMARTSENS2_SYS_ID_TS_FULL_WU:
                rslt = get_buffer_status( fifo_p, 6, &status );
                if ( SMARTSENS2_OK != rslt )
                {
                    return rslt;
                }
                if ( SMARTSENS2_BUFFER_STATUS_OK != status )
                {
                    break;
                }
                *time_stamp = SMARTSENS2_LE2U40( fifo_p->buffer + tmp_read_pos + ( uint8_t )( 1 ) );
                fifo_p->read_pos += 6;
                break;
            default:

                rslt = get_callback_info( ctx, tmp_sensor_id, &info );

                if ( SMARTSENS2_OK != rslt )
                {
                    return rslt;
                }
                rslt = get_buffer_status( fifo_p, info.event_size, &status );
                if ( SMARTSENS2_OK != rslt )
                {
                    return rslt;
                }
                if ( SMARTSENS2_BUFFER_STATUS_OK != status )
                {
                    break;
                }
                if ( NULL != info.callback )
                {
                    /* Read position is incremented by 1 to exclude sensor id */
                    data_info.data_ptr = &fifo_p->buffer[ tmp_read_pos + 1 ];
                    data_info.fifo_type = source;
                    data_info.time_stamp = time_stamp;
                    data_info.sensor_id = tmp_sensor_id;
                    data_info.data_size = info.event_size;
                    info.callback( &data_info, info.callback_ref );
                }
                fifo_p->read_pos += info.event_size;
                break;
        }
    }
    if ( fifo_p->read_length )
    {
        if ( fifo_p->read_length < fifo_p->read_pos )
        {
            return SMARTSENS2_ERROR;
        }
        fifo_p->read_length -= fifo_p->read_pos;
        if ( fifo_p->read_length )
        {
            for ( uint32_t cnt = 0; cnt < fifo_p->read_length; cnt++ )
            {
                fifo_p->buffer[ cnt ] = fifo_p->buffer[ fifo_p->read_pos + cnt ];
            }
        }
    }

    return rslt;
}

static err_t get_callback_info ( smartsens2_t *ctx, uint8_t sensor_id,
                                 struct smartsens2_fifo_parse_callback_table *info )
{
    err_t rslt = SMARTSENS2_OK;

    if ( ( NULL != ctx ) && ( NULL != info ) )
    {
        *info = ctx->table[ sensor_id ];
        if ( ( sensor_id >= SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET ) && ( 0 == info->event_size ) )
        {
            info->callback = NULL;
            info->callback_ref = NULL;
            info->event_size = smartsens2_sysid_event_size[ sensor_id - SMARTSENS2_SPECIAL_SENSOR_ID_OFFSET ];
        }
        if ( ( 0 == sensor_id ) && ( 0 == info->event_size ) )
        {
            info->callback = NULL;
            info->callback_ref = NULL;
            info->event_size = 1;
        }
    }
    else
    {
        rslt = SMARTSENS2_ERROR;
    }

    return rslt;
}

static err_t get_buffer_status ( struct smartsens2_fifo_buffer *fifo_p, uint8_t event_size, buffer_status_t *status )
{
    if ( ( fifo_p->read_pos + event_size ) <= fifo_p->read_length )
    {
        *status = SMARTSENS2_BUFFER_STATUS_OK;
    }
    else
    {
        *status = SMARTSENS2_BUFFER_STATUS_RELOAD;
    }
    return SMARTSENS2_OK;
}

static err_t get_time_stamp ( smartsens2_t *ctx, enum smartsens2_fifo_type source, uint32_t **time_stamp )
{
    err_t rslt = SMARTSENS2_OK;

    if ( source < SMARTSENS2_FIFO_TYPE_MAX )
    {
        *time_stamp = &ctx->last_time_stamp[source];
    }
    else
    {
        rslt = SMARTSENS2_ERROR;
    }
    return rslt;
}

// ------------------------------------------------------------------------ END
