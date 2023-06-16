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

#include "rtd2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RTD2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief SPI communication 10 us delay function.
 *
 * @details Delay time, first SCLK rising edge after CS falling edge.
**/
static void dev_communication_delay ( void );

/**
 * @brief Reset 1 ms delay function.
 *
 * @details Delay time, SCLK rising edge,
 * start of serial interface communication, after RESET rising edge.
**/
static void dev_reset_delay ( void );

/**
 * @brief Configuration 10 ms delay function.
 *
 * @details Delay time after write the configuration in the registers.
**/
static void dev_config_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtd2_cfg_setup ( rtd2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->str = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

err_t rtd2_init ( rtd2_t *ctx, rtd2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RTD2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
    {
        return RTD2_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RTD2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    
    // Output pins 
    digital_out_init( &ctx->str, cfg->str );
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->rdy, cfg->rdy );
    
    spi_master_deselect_device( ctx->chip_select ); 
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->str );

    return RTD2_SUCCESS;
}

void rtd2_default_cfg ( rtd2_t *ctx )
{
    RTD2_SET_DATA_SAMPLE_EDGE;
    
    rtd2_write_reg ( ctx, RTD2_REG_MUX0, RTD2_AINP1 | RTD2_AINN2 );
    dev_config_delay( );

    rtd2_write_reg ( ctx, RTD2_REG_VBIAS, RTD2_VBIAS0 );
    dev_config_delay( );

    rtd2_write_reg ( ctx, RTD2_REG_MUX1, RTD2_INT_VREF_ON | RTD2_INT_REF0 );
    dev_config_delay( );

    rtd2_write_reg ( ctx, RTD2_REG_SYS0, RTD2_GAIN_4 | RTD2_DR_20 );
    dev_config_delay( );

    rtd2_write_reg ( ctx, RTD2_REG_IDAC0, RTD2_IDAC_ID | RTD2_IDAC_1000 );
    dev_config_delay( );

    rtd2_write_reg ( ctx, RTD2_REG_IDAC1, RTD2_IDAC1_A0 | RTD2_IDAC2_A3 );
    dev_config_delay( );
}

void rtd2_hw_reset ( rtd2_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
}

void rtd2_toggle_cs ( rtd2_t *ctx, uint8_t cs_state )
{
    if ( 1 == cs_state )
    {
        spi_master_deselect_device( ctx->chip_select ); 
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
    }
}

void rtd2_enable_start ( rtd2_t *ctx, uint8_t en_start )
{
    if ( 1 == en_start )
    {
        digital_out_high( &ctx->str );
    }
    else
    {
        digital_out_low( &ctx->str );
    }
}

uint8_t rtd2_check_interupt ( rtd2_t *ctx )
{
   return digital_in_read( &ctx->rdy );
}

void rtd2_send_cmd ( rtd2_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void rtd2_set_wakeup ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_WAKEUP );
}

void rtd2_set_sleep ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_SLEEP );
}

void rtd2_set_sync ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_SYNC );
}

void rtd2_set_reset ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_RESET );
}

void rtd2_set_read_data_once ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_RDATA );
}

void rtd2_set_read_data_continuous ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_RDATAC );
}

void rtd2_set_stop_data ( rtd2_t *ctx )
{
    rtd2_send_cmd( ctx, RTD2_CMD_SDATAC );
}

void rtd2_write_continuous ( rtd2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 2 ] = { 0 };

    if ( n_bytes < 1 )
    {
        n_bytes = 1;
    }

    rtd2_toggle_cs( ctx, 1 );

    tx_buf[ 0 ] = RTD2_CMD_RDATAC;
    tx_buf[ 1 ] = RTD2_CMD_WREG;
    tx_buf[ 1 ] |= reg;
    tx_buf[ 2 ] = n_bytes - 1;

    rtd2_toggle_cs( ctx, 0 );
    dev_communication_delay( );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_write( &ctx->spi, p_tx_data, n_bytes );
    dev_communication_delay( );
    rtd2_toggle_cs( ctx, 1 );
}

void rtd2_read_continuous ( rtd2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 2 ] = { 0 };

    if ( n_bytes < 1 )
    {
        n_bytes = 1;
    }

    reg &= 0x0F;

    tx_buf[ 0 ] = RTD2_CMD_RDATA;
    tx_buf[ 0 ] |= reg;
    tx_buf[ 1 ] = n_bytes - 1;

    rtd2_toggle_cs( ctx, 0 );
    dev_communication_delay( );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_read( &ctx->spi, p_rx_data, n_bytes );
    dev_communication_delay( );
    rtd2_toggle_cs( ctx, 1 );
}

void rtd2_write_reg ( rtd2_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 4 ] = { 0 };

    reg &= 0x0F;

    tx_buf[ 0 ]  = RTD2_CMD_WREG;
    tx_buf[ 0 ] |= reg;
    tx_buf[ 1 ]  = 0x00;
    tx_buf[ 2 ]  = tx_data;

    dev_reset_delay( );
    rtd2_set_stop_data( ctx );

    spi_master_select_device( ctx->chip_select );
    dev_communication_delay( );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    dev_communication_delay( );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t rtd2_read_reg ( rtd2_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 4 ] = { 0 };
    uint8_t rx_buf[ 1 ] = { 0 };

    tx_buf[ 0 ]  = RTD2_CMD_RDATA;
    tx_buf[ 1 ]  = RTD2_CMD_RREG;
    tx_buf[ 1 ] |= reg;
    tx_buf[ 2 ]  = RTD2_RW_DUMMY;
    tx_buf[ 3 ]  = RTD2_RW_DUMMY;

    spi_master_select_device( ctx->chip_select );
    dev_communication_delay( );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    dev_communication_delay( );
    spi_master_deselect_device( ctx->chip_select ); 

    return rx_buf[ 0 ];
}

uint8_t rtd2_set_burn_out_source ( rtd2_t *ctx, uint8_t burn_out )
{
    uint8_t data_buf = 0;
    uint8_t error = 0;
    
    error = RTD2_SUCCESS;
    
    data_buf = rtd2_read_reg( ctx, RTD2_REG_MUX0 );
    
    data_buf &= 0x3f;
    
    switch ( burn_out )
    {
        case 0:
        {
            data_buf |= RTD2_BCS_OFF;
            break;
        }
        case 1:
        {
            data_buf |= RTD2_BCS_500;
            break;
        }
        case 2:
        {
            data_buf |= RTD2_BCS_2;
            break;
        }
        case 3:
        {
            data_buf |= RTD2_BCS_10;
            break;
        }
        default:
        {
            error = RTD2_ERROR;
            data_buf = RTD2_BCS_OFF;
            break;
        }
    }

    rtd2_write_reg ( ctx, RTD2_REG_MUX0, data_buf );

    return error;
}

void rtd2_set_mux_sel ( rtd2_t *ctx, uint8_t adc_pos, uint8_t adc_neg )
{
    uint8_t mux_sel = 0;
    
    adc_pos &= RTD2_AIN_POS;
    adc_neg &= RTD2_AIN_NEG;
    
    mux_sel = rtd2_read_reg( ctx, RTD2_REG_MUX0 );

    mux_sel &= RTD2_BCS_10;
    mux_sel |= adc_pos;
    mux_sel |= adc_neg;

    rtd2_write_reg ( ctx, RTD2_REG_MUX0, mux_sel );
}

uint8_t rtd2_set_bias ( rtd2_t *ctx, uint8_t bias )
{
    uint8_t v_bias = 0;
    uint8_t error = 0;

    error = RTD2_SUCCESS;

    v_bias = rtd2_read_reg( ctx, RTD2_REG_VBIAS );

    v_bias &= ~0x0F;
    
    switch ( bias )
    {
        case RTD2_VBIAS_OFF:
        {
            v_bias |= RTD2_VBIAS_OFF;
            break;
        }
        case RTD2_VBIAS0:
        {
            v_bias |= RTD2_VBIAS0;
            break;
        }
        case RTD2_VBIAS1:
        {
            v_bias |= RTD2_VBIAS1;
            break;
        }
        case RTD2_VBIAS2:
        {
            v_bias |= RTD2_VBIAS2;
            break;
        }
        case RTD2_VBIAS3:
        {
            v_bias |= RTD2_VBIAS3;
            break;
        }
        default:
        {
            error = RTD2_ERROR;
            v_bias |= RTD2_VBIAS_OFF;
        }
    }

    rtd2_write_reg ( ctx, RTD2_REG_MUX0, v_bias );

    return error;
}

uint8_t rtd2_set_int_ref ( rtd2_t *ctx, uint8_t s_ref )
{
    uint8_t tmp_ref = 0;
    uint8_t error = 0;

    error = RTD2_SUCCESS;
    
    if ( s_ref && 0x60 )
    {
        s_ref &= 0x1F;
        error = RTD2_ERROR;
    }

    tmp_ref = rtd2_read_reg( ctx, RTD2_REG_MUX1 );
    
    tmp_ref |= s_ref;

    rtd2_write_reg ( ctx, RTD2_REG_MUX1, tmp_ref );

    return error;
}

void rtd2_set_system_monitor ( rtd2_t *ctx, uint8_t sys_mon )
{
    uint8_t s_mon = 0;

    sys_mon &= RTD2_MEAS_DVDD;

    s_mon = rtd2_read_reg( ctx, RTD2_REG_MUX1 );

    s_mon &= 0xF8;
    s_mon |= sys_mon;

    rtd2_write_reg ( ctx, RTD2_REG_MUX1, s_mon );
}

void rtd2_set_system_control ( rtd2_t *ctx, uint8_t gain, uint8_t output_rate )
{
    uint8_t sys_con = 0;
    
    gain &= RTD2_GAIN_128;
    output_rate &= RTD2_DR_2000;

    sys_con = gain;
    sys_con |= output_rate;

    rtd2_write_reg ( ctx, RTD2_REG_SYS0, sys_con );
}

void rtd2_set_idac_current_mag ( rtd2_t *ctx, uint8_t c_idac )
{
    c_idac &= RTD2_IDAC_1500;
    c_idac |= RTD2_IDAC_ID;

    rtd2_write_reg ( ctx, RTD2_REG_IDAC0, c_idac );
}

void rtd2_set_idac_current_out ( rtd2_t *ctx, uint8_t c_out_1, uint8_t c_out_2 )
{
    uint8_t c_idac_out = 0;
    
    c_out_1 &= 0x30;
    c_out_2 &= 0x03;
    
    c_idac_out = RTD2_IDAC1_A3;
    c_idac_out &= RTD2_IDAC2_A3;
    c_idac_out |= c_out_1;
    c_idac_out |= c_out_2;

    rtd2_write_reg ( ctx, RTD2_REG_IDAC1, c_idac_out );
}

uint8_t rtd2_check_new_data_ready ( rtd2_t *ctx )
{
    uint8_t data_ready = 0;
    
    data_ready = RTD2_NEW_DATA_IS_NOT_READY;
    
    while ( rtd2_check_interupt( ctx ) == RTD2_PIN_LOW );
    while ( rtd2_check_interupt( ctx ) == RTD2_PIN_HIGH );
    
    if ( rtd2_check_interupt( ctx ) == RTD2_PIN_LOW )
    {
        data_ready = RTD2_NEW_DATA_IS_READY;
    }
    
    return data_ready;
}

int32_t rtd2_read_output_data ( rtd2_t *ctx )
{
    uint32_t data_buf = 0;
    int32_t result = 0;
    uint8_t rx_buf[ 3 ] = { 0 };
    uint8_t tx_buf[ 4 ] = { 0 };

    tx_buf[ 0 ] = RTD2_CMD_RDATA;
    tx_buf[ 1 ] = RTD2_RW_DUMMY;
    tx_buf[ 2 ] = RTD2_RW_DUMMY;
    tx_buf[ 3 ] = RTD2_RW_DUMMY;

    rtd2_toggle_cs( ctx, 0 );
    dev_communication_delay( );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, 3 );
    dev_communication_delay( );
    rtd2_toggle_cs( ctx, 1 );

    data_buf = rx_buf[ 0 ];
    data_buf <<= 8;
    data_buf |= rx_buf[ 1 ];
    data_buf <<= 8;
    data_buf |= rx_buf[ 2 ];

    result = ( int32_t ) ( data_buf << 8 );
    result >>= 8;

    return result;
}

float rtd2_calc_temperature ( int32_t adc_val )
{
    float temperature = 0;
    float rt_val = 0;
    
    rt_val = ( float ) adc_val;
    rt_val *= COEFF_ADC_RES_RT_P;
    rt_val -= COEFF_ADC_COR_FACT;

    if ( rt_val < COEFF_PT100_RESISTANCE_OHMS_0_C )
    {
        temperature = ( COEFF_PT100_RESISTANCE_OHMS_0_C - rt_val ) / COEFF_ALPHA;
    }
    else
    {
        temperature = ( rt_val - COEFF_PT100_RESISTANCE_OHMS_0_C ) / COEFF_ALPHA;
    }
    
    return temperature;
}

float rtd2_get_temperature ( rtd2_t *ctx )
{
    float temperature = 0;
    int32_t adc_val = 0;

    rtd2_enable_start( ctx, RTD2_START_CONVERSION_ENABLE );
    
    adc_val = rtd2_read_output_data( ctx );
    
    temperature = rtd2_calc_temperature( adc_val );

    return temperature;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_communication_delay ( void )
{
    Delay_10us( );
}

static void dev_reset_delay ( void )
{
    Delay_1ms( );
}

static void dev_config_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

