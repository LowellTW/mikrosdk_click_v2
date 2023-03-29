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

#include "audioxover.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioxover_cfg_setup ( audioxover_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->sdn   = HAL_PIN_NC;
}

AUDIOXOVER_RETVAL audioxover_init ( audioxover_t *ctx, audioxover_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->sdn, cfg->sdn );

    return AUDIOXOVER_OK;
}

void audioxover_power_on ( audioxover_t *ctx )
{
    digital_out_write( &ctx->sdn, AUDIOXOVER_ENABLE );
}

void audioxover_shut_down ( audioxover_t *ctx )
{
    digital_out_write( &ctx->sdn, AUDIOXOVER_DISABLE );
}


// ------------------------------------------------------------------------- END

