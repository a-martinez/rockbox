/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id:$
 *
 * Copyright (C) 2010 Marcin Bukat
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#include "config.h"
#include "cpu.h"
#include "system.h"
#include "kernel.h"
#include "thread.h"
#include "adc.h"


/* blocking delay loop */
#define DELAY   \
    ({                                \
        int _x_;                      \
        asm volatile (                \
            "move.l #10000, %[_x_] \r\n" \
        "1:                     \r\n" \
            "subq.l #1, %[_x_]  \r\n" \
            "bhi.b  1b          \r\n" \
            : [_x_]"=&d"(_x_)         \
        );                            \
    })

unsigned short adc_scan(int channel)
{
    int level = disable_irq_save();

    /* set source
     * remark
     * ADCONFIG is 16bit wide so we have to shift data by 16bits left
     * thats why we shift <<24 instead of <<8
     */

    and_l(~(3<<24),&ADCONFIG);
    or_l(((channel & 0x03) << 24), &ADCONFIG);

    restore_irq(level);

    /* this is needed as setup time for ADC
     * otherwise battery readings tend to saturate
     * and return ~4.6V which is by no means not true.
     * Buttons scans are not affected which is weird
     */

    DELAY;
    return ADVALUE;
}

void adc_init(void)
{
    /* GPIO38 GPIO39 */
    and_l(~((1<<6)|(1<<7)), &GPIO1_FUNCTION);

    /* ADCONFIG taken from OF */
    ADCONFIG = 0x480;
}
