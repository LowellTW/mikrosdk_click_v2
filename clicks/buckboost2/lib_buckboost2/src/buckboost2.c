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

#include "buckboost2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buckboost2_cfg_setup ( buckboost2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->mod = HAL_PIN_NC;
}

BUCKBOOST2_RETVAL buckboost2_init ( buckboost2_t *ctx, buckboost2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->mod, cfg->mod );
    digital_out_write( &ctx->en, 1 );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return BUCKBOOST2_OK;
}

void buckboost2_power_on ( buckboost2_t *ctx  )
{
    digital_out_high( &ctx->en );
}

void buckboost2_power_off ( buckboost2_t *ctx )
{
    digital_out_low( &ctx->en );
}

void buckboost2_set_mode ( buckboost2_t *ctx , uint8_t mode )
{
    digital_out_write( &ctx->en, mode );
}

// ------------------------------------------------------------------------- END

