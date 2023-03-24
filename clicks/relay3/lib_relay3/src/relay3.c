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

#include "relay3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void relay3_cfg_setup ( relay3_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->re1 = HAL_PIN_NC;
    cfg->re2   = HAL_PIN_NC;
}

RELAY3_RETVAL relay3_init ( relay3_t *ctx, relay3_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->re1, cfg->re1 );
    digital_out_init( &ctx->re2, cfg->re2 );

    return RELAY3_OK;
}

void relay3_relay_on ( relay3_t *ctx, uint8_t relay )
{
    if ( relay == 1 )
    {
        digital_out_high( &ctx->re1 );
    }
    else if ( relay == 2 )
    {
        digital_out_high( &ctx->re2 );
    }
	else if ( relay == 3 )
    {
        digital_out_high( &ctx->re2 );
        digital_out_high( &ctx->re1 );
    } 
}

void relay3_relay_off ( relay3_t *ctx, uint8_t relay ) 
{
    if ( relay == 1 )
    {
        digital_out_low( &ctx->re1 );
    }
    else if ( relay == 2 )
    {
        digital_out_low( &ctx->re2 );
    }
	else if ( relay == 3 )
    {
        digital_out_low( &ctx->re2 );
        digital_out_low( &ctx->re1 );
    }
}

void relay3_on_delay ( relay3_t *ctx, uint8_t relay, uint8_t units, uint16_t time )
{
    uint16_t i;
    
    if ( units == 0 )
    {
        relay3_relay_off( ctx, relay );
        
        for ( i = 0; i < time; i ++ )
        {
            Delay_1ms( );
        }
        
        relay3_relay_on( ctx, relay );
    }
    else if ( units == 1 )
    {
        relay3_relay_off( ctx, relay );
        
        for ( i = 0; i < time; i ++ )
        {
            Delay_1ms( );
        }
        
        relay3_relay_on( ctx, relay );
    }
}

void relay3_off_delay ( relay3_t *ctx, uint8_t relay, uint8_t units, uint16_t time )
{
    uint16_t i;
    
    if ( units == 0 )
    {
        relay3_relay_on ( ctx, relay );

        for (i = 0; i < time; i ++)
        {
            Delay_1ms( );
        }

        relay3_relay_off( ctx, relay );
    }
    else if ( units == 1 )
    {
        relay3_relay_on( ctx, relay );

        for (i = 0; i < time; i ++)
        {
            Delay_1ms( );
        }

        relay3_relay_off( ctx, relay );
    }
}

// ------------------------------------------------------------------------- END

