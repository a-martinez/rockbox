/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Gilles Roux
 *               2003 Garrett Derner
 *               2010 Yoshihisa Uchida
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
#ifndef PLUGIN_TEXT_VIEWER_BUTTON_H
#define PLUGIN_TEXT_VIEWER_BUTTON_H

/* variable button definitions */

/* Recorder keys */
#if CONFIG_KEYPAD == RECORDER_PAD
#define VIEWER_QUIT         BUTTON_OFF
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_F1
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define VIEWER_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define VIEWER_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define VIEWER_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define VIEWER_BOOKMARK     BUTTON_F2

#elif CONFIG_KEYPAD == ARCHOS_AV300_PAD
#define VIEWER_QUIT         BUTTON_OFF
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_F1
#define VIEWER_AUTOSCROLL   BUTTON_SELECT
#define VIEWER_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define VIEWER_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define VIEWER_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define VIEWER_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define VIEWER_BOOKMARK     BUTTON_F2

/* Ondio keys */
#elif CONFIG_KEYPAD == ONDIO_PAD
#define VIEWER_QUIT           BUTTON_OFF
#define VIEWER_SCROLL_UP      BUTTON_UP
#define VIEWER_SCROLL_DOWN    BUTTON_DOWN
#define VIEWER_SCREEN_LEFT    BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT   BUTTON_RIGHT
#define VIEWER_MENU           (BUTTON_MENU|BUTTON_REPEAT)
#define VIEWER_AUTOSCROLL_PRE BUTTON_MENU
#define VIEWER_AUTOSCROLL     (BUTTON_MENU|BUTTON_REL)
#define VIEWER_BOOKMARK       (BUTTON_MENU|BUTTON_OFF)

/* Player keys */
#elif CONFIG_KEYPAD == PLAYER_PAD
#define VIEWER_QUIT         BUTTON_STOP
#define VIEWER_SCROLL_UP    BUTTON_LEFT
#define VIEWER_SCROLL_DOWN  BUTTON_RIGHT
#define VIEWER_SCREEN_LEFT  (BUTTON_ON|BUTTON_LEFT)
#define VIEWER_SCREEN_RIGHT (BUTTON_ON|BUTTON_RIGHT)
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_ON

/* iRiver H1x0 && H3x0 keys */
#elif (CONFIG_KEYPAD == IRIVER_H100_PAD) || \
      (CONFIG_KEYPAD == IRIVER_H300_PAD)
#define VIEWER_QUIT         BUTTON_OFF
#define VIEWER_RC_QUIT      BUTTON_RC_STOP
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MODE
#define VIEWER_AUTOSCROLL   BUTTON_SELECT
#define VIEWER_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define VIEWER_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define VIEWER_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define VIEWER_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define VIEWER_BOOKMARK     (BUTTON_ON | BUTTON_SELECT)

/* iPods */
#elif (CONFIG_KEYPAD == IPOD_4G_PAD) || \
      (CONFIG_KEYPAD == IPOD_3G_PAD) || \
      (CONFIG_KEYPAD == IPOD_1G2G_PAD)
#define VIEWER_QUIT_PRE     BUTTON_SELECT
#define VIEWER_QUIT         (BUTTON_SELECT | BUTTON_MENU)
#define VIEWER_SCROLL_UP    BUTTON_SCROLL_BACK
#define VIEWER_SCROLL_DOWN  BUTTON_SCROLL_FWD
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_SELECT

/* iFP7xx keys */
#elif CONFIG_KEYPAD == IRIVER_IFP7XX_PAD
#define VIEWER_QUIT         BUTTON_PLAY
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MODE
#define VIEWER_AUTOSCROLL   BUTTON_SELECT
#define VIEWER_BOOKMARK     (BUTTON_LEFT|BUTTON_SELECT)

/* iAudio X5 keys */
#elif CONFIG_KEYPAD == IAUDIO_X5M5_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_SELECT
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_REC

/* GIGABEAT keys */
#elif CONFIG_KEYPAD == GIGABEAT_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_A
#define VIEWER_BOOKMARK     BUTTON_SELECT

/* Sansa E200 keys */
#elif CONFIG_KEYPAD == SANSA_E200_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_SELECT
#define VIEWER_AUTOSCROLL   BUTTON_REC
#define VIEWER_LINE_UP      BUTTON_SCROLL_BACK
#define VIEWER_LINE_DOWN    BUTTON_SCROLL_FWD
#define VIEWER_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* Sansa Fuze keys */
#elif CONFIG_KEYPAD == SANSA_FUZE_PAD
#define VIEWER_QUIT         (BUTTON_HOME|BUTTON_REPEAT)
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_SELECT|BUTTON_REPEAT
#define VIEWER_AUTOSCROLL   BUTTON_SELECT|BUTTON_DOWN
#define VIEWER_LINE_UP      BUTTON_SCROLL_BACK
#define VIEWER_LINE_DOWN    BUTTON_SCROLL_FWD
#define VIEWER_BOOKMARK     BUTTON_SELECT

/* Sansa C200 keys */
#elif CONFIG_KEYPAD == SANSA_C200_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_VOL_UP
#define VIEWER_SCROLL_DOWN  BUTTON_VOL_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_SELECT
#define VIEWER_AUTOSCROLL   BUTTON_REC
#define VIEWER_LINE_UP      BUTTON_UP
#define VIEWER_LINE_DOWN    BUTTON_DOWN
#define VIEWER_BOOKMARK     (BUTTON_DOWN | BUTTON_SELECT)

/* Sansa Clip keys */
#elif CONFIG_KEYPAD == SANSA_CLIP_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_VOL_UP
#define VIEWER_SCROLL_DOWN  BUTTON_VOL_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_SELECT
#define VIEWER_AUTOSCROLL   BUTTON_HOME
#define VIEWER_LINE_UP      BUTTON_UP
#define VIEWER_LINE_DOWN    BUTTON_DOWN
#define VIEWER_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* Sansa M200 keys */
#elif CONFIG_KEYPAD == SANSA_M200_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_VOL_UP
#define VIEWER_SCROLL_DOWN  BUTTON_VOL_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         (BUTTON_SELECT | BUTTON_UP)
#define VIEWER_AUTOSCROLL   (BUTTON_SELECT | BUTTON_REL)
#define VIEWER_LINE_UP      BUTTON_UP
#define VIEWER_LINE_DOWN    BUTTON_DOWN
#define VIEWER_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* iriver H10 keys */
#elif CONFIG_KEYPAD == IRIVER_H10_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_SCROLL_UP
#define VIEWER_SCROLL_DOWN  BUTTON_SCROLL_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_REW
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_FF

/*M-Robe 500 keys */
#elif CONFIG_KEYPAD == MROBE500_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_RC_PLAY
#define VIEWER_SCROLL_DOWN  BUTTON_RC_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_RC_HEART
#define VIEWER_AUTOSCROLL   BUTTON_RC_MODE
#define VIEWER_BOOKMARK     BUTTON_CENTER

/*Gigabeat S keys */
#elif CONFIG_KEYPAD == GIGABEAT_S_PAD
#define VIEWER_QUIT           BUTTON_BACK
#define VIEWER_SCROLL_UP      BUTTON_PREV
#define VIEWER_SCROLL_DOWN    BUTTON_NEXT
#define VIEWER_SCREEN_LEFT    (BUTTON_PLAY | BUTTON_LEFT)
#define VIEWER_SCREEN_RIGHT   (BUTTON_PLAY | BUTTON_RIGHT)
#define VIEWER_MENU           BUTTON_MENU
#define VIEWER_AUTOSCROLL_PRE BUTTON_PLAY
#define VIEWER_AUTOSCROLL     (BUTTON_PLAY|BUTTON_REL)
#define VIEWER_LINE_UP        BUTTON_UP
#define VIEWER_LINE_DOWN      BUTTON_DOWN
#define VIEWER_COLUMN_LEFT    BUTTON_LEFT
#define VIEWER_COLUMN_RIGHT   BUTTON_RIGHT
#define VIEWER_BOOKMARK       BUTTON_SELECT

/*M-Robe 100 keys */
#elif CONFIG_KEYPAD == MROBE100_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_DISPLAY
#define VIEWER_BOOKMARK     BUTTON_SELECT

/* iAUdio M3 keys */
#elif CONFIG_KEYPAD == IAUDIO_M3_PAD
#define VIEWER_QUIT         BUTTON_REC
#define VIEWER_RC_QUIT      BUTTON_RC_REC
#define VIEWER_SCROLL_UP    BUTTON_RC_VOL_UP
#define VIEWER_SCROLL_DOWN  BUTTON_RC_VOL_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_RC_REW
#define VIEWER_SCREEN_RIGHT BUTTON_RC_FF
#define VIEWER_MENU         BUTTON_RC_MENU
#define VIEWER_AUTOSCROLL   BUTTON_RC_MODE
#define VIEWER_BOOKMARK     BUTTON_RC_PLAY

/* Cowon D2 keys */
#elif CONFIG_KEYPAD == COWON_D2_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_SCROLL_UP    BUTTON_MINUS
#define VIEWER_SCROLL_DOWN  BUTTON_PLUS
#define VIEWER_BOOKMARK     (BUTTON_MENU|BUTTON_PLUS)

#elif CONFIG_KEYPAD == IAUDIO67_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_VOLUP
#define VIEWER_SCROLL_DOWN  BUTTON_VOLDOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_RC_QUIT      BUTTON_STOP
#define VIEWER_BOOKMARK     (BUTTON_LEFT|BUTTON_PLAY)

/* Creative Zen Vision:M keys */
#elif CONFIG_KEYPAD == CREATIVEZVM_PAD
#define VIEWER_QUIT         BUTTON_BACK
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_SELECT
#define VIEWER_BOOKMARK     BUTTON_PLAY

/* Philips HDD1630 keys */
#elif CONFIG_KEYPAD == PHILIPS_HDD1630_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_VIEW
#define VIEWER_BOOKMARK     BUTTON_SELECT

/* Philips SA9200 keys */
#elif CONFIG_KEYPAD == PHILIPS_SA9200_PAD
#define VIEWER_QUIT         BUTTON_POWER
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_PREV
#define VIEWER_SCREEN_RIGHT BUTTON_NEXT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_RIGHT

/* Onda VX747 keys */
#elif CONFIG_KEYPAD == ONDAVX747_PAD
#define VIEWER_QUIT BUTTON_POWER
#define VIEWER_MENU BUTTON_MENU
#define VIEWER_BOOKMARK (BUTTON_RIGHT|BUTTON_POWER)

/* Onda VX777 keys */
#elif CONFIG_KEYPAD == ONDAVX777_PAD
#define VIEWER_QUIT BUTTON_POWER
#define VIEWER_BOOKMARK (BUTTON_RIGHT|BUTTON_POWER)

/* SAMSUNG YH-820 / YH-920 / YH-925 keys */
#elif CONFIG_KEYPAD == SAMSUNG_YH_PAD
#define VIEWER_QUIT         BUTTON_REC
#define VIEWER_SCROLL_UP    BUTTON_UP
#define VIEWER_SCROLL_DOWN  BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_LEFT
#define VIEWER_SCREEN_RIGHT BUTTON_RIGHT
#define VIEWER_MENU         BUTTON_PLAY
#define VIEWER_AUTOSCROLL   BUTTON_REW
#define VIEWER_BOOKMARK     BUTTON_FFWD

/* Packard Bell Vibe 500 keys */
#elif CONFIG_KEYPAD == PBELL_VIBE500_PAD
#define VIEWER_QUIT         BUTTON_REC
#define VIEWER_SCROLL_UP    BUTTON_OK
#define VIEWER_SCROLL_DOWN  BUTTON_CANCEL
#define VIEWER_LINE_UP      BUTTON_UP
#define VIEWER_LINE_DOWN    BUTTON_DOWN
#define VIEWER_SCREEN_LEFT  BUTTON_PREV
#define VIEWER_SCREEN_RIGHT BUTTON_NEXT
#define VIEWER_MENU         BUTTON_MENU
#define VIEWER_AUTOSCROLL   BUTTON_PLAY
#define VIEWER_BOOKMARK     BUTTON_POWER

#else
#error No keymap defined!
#endif

#ifdef HAVE_TOUCHSCREEN
#ifdef VIEWER_QUIT
#define VIEWER_QUIT2        BUTTON_TOPLEFT
#else
#define VIEWER_QUIT         BUTTON_TOPLEFT
#endif
#ifdef VIEWER_SCROLL_UP
#define VIEWER_SCROLL_UP2   BUTTON_TOPMIDDLE
#else
#define VIEWER_SCROLL_UP    BUTTON_TOPMIDDLE
#endif
#ifdef VIEWER_SCROLL_DOWN
#define VIEWER_SCROLL_DOWN2 BUTTON_BOTTOMMIDDLE
#else
#define VIEWER_SCROLL_DOWN  BUTTON_BOTTOMMIDDLE
#endif
#ifndef VIEWER_SCREEN_LEFT
#define VIEWER_SCREEN_LEFT  BUTTON_MIDLEFT
#endif
#ifndef VIEWER_SCREEN_RIGHT
#define VIEWER_SCREEN_RIGHT BUTTON_MIDRIGHT
#endif
#ifdef VIEWER_MENU
#define VIEWER_MENU2        BUTTON_TOPRIGHT
#else
#define VIEWER_MENU         BUTTON_TOPRIGHT
#endif
#ifndef VIEWER_AUTOSCROLL
#define VIEWER_AUTOSCROLL   BUTTON_CENTER
#endif
#endif

#endif
