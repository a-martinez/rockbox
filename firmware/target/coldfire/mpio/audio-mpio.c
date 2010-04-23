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
#include "system.h"
#include "cpu.h"
#include "audio.h"
#include "sound.h"

void audio_set_output_source(int source)
{
    static const unsigned char txsrc_select[AUDIO_NUM_SOURCES+1] =
    {
        [AUDIO_SRC_PLAYBACK+1] = 3, /* PDOR3        */
        [AUDIO_SRC_MIC+1]      = 4, /* IIS1 RcvData */
        [AUDIO_SRC_LINEIN+1]   = 4, /* IIS1 RcvData */
        [AUDIO_SRC_FMRADIO+1]  = 4, /* IIS1 RcvData */
    };

    int level = set_irq_level(DMA_IRQ_LEVEL);

    if ((unsigned)source >= AUDIO_NUM_SOURCES)
        source = AUDIO_SRC_PLAYBACK;

    IIS2CONFIG = (IIS2CONFIG & ~(7 << 8)) | (txsrc_select[source+1] << 8);

    restore_irq(level);
}

void audio_input_mux(int source, unsigned flags)
{
    (void)source;
    (void)flags;

    switch(source)
    {
        case AUDIO_SRC_FMRADIO:
        break;
    }
    /* empty stub */
}
