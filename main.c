/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

void delay();


main(int argc, char* argv[])
{
	volatile uint32_t *ahb1 = 0x40023800 +0x30;
	volatile uint32_t *mode = 0x40020000 +0x00;
	volatile uint32_t *odr  = 0x40020000 +0x14;

	*ahb1 |= (1<< 0);
	*mode |= (1<< 12)|(1<< 14)|(1<<2)|(1<<4)|(1<<6)|(1<<8)|(1<<16)|(1<<18)|(1<<20);
	while(1)
	{
		*odr |= (1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<8)|(1<<9)|(1<<10);

	*odr  |=(1<<6);
	        delay();
	*odr |= (1<<7);
	       delay();
	*odr &= ~(1<<6);
     	   delay();
    *odr &=~(1<< 7);
 //   *odr |= (1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<8)|(1<<9)|(1<<10);

      }
}
void delay()
{
 volatile uint32_t *apb1 =0x40023800 +0x40;
 volatile uint32_t *arr  =0x40000000 +0x2c;
 volatile uint32_t *psc  =0x40000000 +0x28;
 volatile uint32_t *cnt  =0x40000000 +0x00;
 volatile uint32_t *st   =0x40000000 +0x10;
 volatile uint32_t *cunt =0x40000000 +0x24;

 *apb1 |= (1 << 0);
 *cnt  |= (1 << 0);
 *cunt =0x0000;
//*st |=(1<< 0);
 *psc  =0x0000;
 *arr   = 0xFFF;

 trace_printf("counter:%d arr:%d uif:%d",*cunt,*arr,*st);
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
