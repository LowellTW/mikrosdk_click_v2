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
 * @file irda3.c
 * @brief IrDA 3 Click Driver.
 */

#include "irda3.h"

void irda3_cfg_setup ( irda3_cfg_t *cfg ) {
    
    // Communication gpio pins
    
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->mod   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t irda3_init ( irda3_t *ctx, irda3_cfg_t *cfg ) {
    uart_config_t uart_cfg;

    // Default config
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    
    uart_cfg.rx_pin = cfg->rx_pin;      // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;      // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->mod, cfg->mod );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );
    
    return UART_SUCCESS;
}

void irda3_default_cfg( irda3_t *ctx ) {
    digital_out_high( &ctx->rst );
    irda3_pwr_setup( ctx, IRDA3_PWR_ON );
    irda3_mode_setup( ctx, IRDA3_MODE_DATA );
}

void irda3_mode_setup( irda3_t *ctx, irda3_mode_t state ) {
    digital_out_write( &ctx->mod, state );
}

void irda3_pwr_setup( irda3_t *ctx, irda3_pwr_t state ) {
    digital_out_write( &ctx->en, state );
}

void irda3_reset( irda3_t *ctx ) {
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void irda3_generic_multiple_send( irda3_t *ctx, char *tx_data ) {
    while ( *tx_data ) {
        uart_write( &ctx->uart, tx_data, 1 );
        *tx_data++;
    }
}

void irda3_generic_multiple_receive( irda3_t *ctx, char *rx_data, char termination_char ) {
    char rx_dat;
    int32_t rsp_size;

    rx_dat = termination_char + 1;

    while ( rx_dat != termination_char ) {
        rsp_size = uart_read( &ctx->uart, &rx_dat, 1 );
        if ( rsp_size != -1 ) {       
            *rx_data++ = rx_dat;
        }
    }

    *rx_data = '\0';
}

void irda3_generic_single_send( irda3_t *ctx, char tx_data ) {
    uart_write( &ctx->uart, &tx_data, 1 );
}

char irda3_generic_single_receive( irda3_t *ctx ) { 
    char rx_data;
    while ( uart_read( &ctx->uart, &rx_data, 1 ) <= 0 ) {
        Delay_1ms( );
    }
    return rx_data;
}
// ------------------------------------------------------------------------- END
