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

#include "leddriver4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void leddriver4_cfg_setup ( leddriver4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->ctl = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dev_pwm_freq   = LEDDRIVER4_DEF_FREQ;
}

LEDDRIVER4_RETVAL leddriver4_init ( leddriver4_t *ctx, leddriver4_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->ctl;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->ctl, &pwm_cfg );
    pwm_set_freq( &ctx->ctl, pwm_cfg.freq_hz );

    return LEDDRIVER4_OK;
}

void leddriver4_set_duty_cycle ( leddriver4_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->ctl, duty_cycle ); 
}

void leddriver4_pwm_stop ( leddriver4_t *ctx )
{
    pwm_stop( &ctx->ctl ); 
}

void leddriver4_pwm_start ( leddriver4_t *ctx )
{
    pwm_start( &ctx->ctl ); 
}

// ------------------------------------------------------------------------- END

