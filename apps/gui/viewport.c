/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2008 by Jonathan Gordon
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

#include <stdlib.h>
#include "config.h"
#include "lcd.h"
#include "lcd-remote.h"
#include "font.h"
#include "viewport.h"
#include "screen_access.h"
#include "settings.h"
#include "misc.h"

/*some short cuts for fg/bg/line selector handling */
#ifdef HAVE_LCD_COLOR
#define FG_FALLBACK global_settings.fg_color
#define BG_FALLBACK global_settings.bg_color
#else
#define FG_FALLBACK LCD_DEFAULT_FG
#define BG_FALLBACK LCD_DEFAULT_BG
#endif

/* all below isn't needed for pc tools (i.e. checkwps/wps editor)
 * only viewport_parse_viewport() is */
#ifndef __PCTOOL__
#include "string.h"
#include "kernel.h"
#include "system.h"
#include "statusbar.h"
#include "appevents.h"
#include "panic.h"
#ifdef HAVE_LCD_BITMAP
#include "language.h"
#endif
#include "statusbar-skinned.h"
#include "debug.h"
#include "viewport.h"

#define VPSTACK_DEPTH 16
struct viewport_stack_item
{
    struct  viewport* vp;
    bool   enabled;
};

#ifdef HAVE_LCD_BITMAP
static void viewportmanager_redraw(void* data);

static int theme_stack_top[NB_SCREENS]; /* the last item added */
static struct viewport_stack_item theme_stack[NB_SCREENS][VPSTACK_DEPTH];
static bool is_theme_enabled(enum screen_type screen);


static void toggle_events(bool enable)
{
    if (enable)
    {
        add_event(GUI_EVENT_ACTIONUPDATE, false, viewportmanager_redraw);
#if defined(HAVE_LCD_ENABLE) || defined(HAVE_LCD_SLEEP)
        add_event(LCD_EVENT_ACTIVATION, false, do_sbs_update_callback);
#endif
        add_event(PLAYBACK_EVENT_TRACK_CHANGE, false,
                                                do_sbs_update_callback);
        add_event(PLAYBACK_EVENT_NEXTTRACKID3_AVAILABLE, false,
                                                do_sbs_update_callback);
    }
    else
    {
#if defined(HAVE_LCD_ENABLE) || defined(HAVE_LCD_SLEEP)
        remove_event(LCD_EVENT_ACTIVATION, do_sbs_update_callback);
#endif
        remove_event(PLAYBACK_EVENT_TRACK_CHANGE, do_sbs_update_callback);
        remove_event(PLAYBACK_EVENT_NEXTTRACKID3_AVAILABLE, do_sbs_update_callback);
        remove_event(GUI_EVENT_ACTIONUPDATE, viewportmanager_redraw);
    }
}


static void toggle_theme(enum screen_type screen, bool force)
{
    bool enable_event = false;
    static bool was_enabled[NB_SCREENS] = {false};
    static bool after_boot[NB_SCREENS] = {false};
    int i;

    FOR_NB_SCREENS(i)
    {
        enable_event = enable_event || is_theme_enabled(i);
        sb_set_title_text(NULL, Icon_NOICON, i);
    }
    toggle_events(enable_event);

    if (is_theme_enabled(screen))
    {
        bool first_boot = theme_stack_top[screen] == 0;
        /* remove the left overs from the previous screen.
         * could cause a tiny flicker. Redo your screen code if that happens */
#if LCD_DEPTH > 1 || defined(HAVE_REMOTE_LCD) && LCD_REMOTE_DEPTH > 1
        screens[screen].backdrop_show(sb_get_backdrop(screen));
#endif
        if (LIKELY(after_boot[screen]) && (!was_enabled[screen] || force))
        {
            struct viewport deadspace, user;
            viewport_set_defaults(&user, screen);
            deadspace = user; /* get colours and everything */
            /* above */
            deadspace.x = 0;
            deadspace.y = 0;
            deadspace.width = screens[screen].lcdwidth;
            deadspace.height = user.y;
            if (deadspace.width && deadspace.height)
            {
                screens[screen].set_viewport(&deadspace);
                screens[screen].clear_viewport();
                screens[screen].update_viewport();
            }
            /* below */
            deadspace.y = user.y + user.height;
            deadspace.height = screens[screen].lcdheight - deadspace.y;
            if (deadspace.width && deadspace.height)
            {
                screens[screen].set_viewport(&deadspace);
                screens[screen].clear_viewport();
                screens[screen].update_viewport();
            }
            /* left */
            deadspace.x = 0;
            deadspace.y = 0;
            deadspace.width = user.x;
            deadspace.height = screens[screen].lcdheight;
            if (deadspace.width && deadspace.height)
            {
                screens[screen].set_viewport(&deadspace);
                screens[screen].clear_viewport();
                screens[screen].update_viewport();
            }
            /* below */
            deadspace.x = user.x + user.width;
            deadspace.width = screens[screen].lcdwidth - deadspace.x;
            if (deadspace.width && deadspace.height)
            {
                screens[screen].set_viewport(&deadspace);
                screens[screen].clear_viewport();
                screens[screen].update_viewport();
            }
            screens[screen].set_viewport(NULL);
        }
        intptr_t force = first_boot?0:1;
        send_event(GUI_EVENT_ACTIONUPDATE, (void*)force);
    }
    else
    {
#if LCD_DEPTH > 1 || (defined(LCD_REMOTE_DEPTH) && LCD_REMOTE_DEPTH > 1)
        screens[screen].backdrop_show(NULL);
#endif
        screens[screen].stop_scroll();
    }
    /* let list initialize viewport in case viewport dimensions is changed. */
    send_event(GUI_EVENT_THEME_CHANGED, NULL);
    FOR_NB_SCREENS(i)
        was_enabled[i] = is_theme_enabled(i);

    after_boot[screen] = true;
}

void viewportmanager_theme_enable(enum screen_type screen, bool enable,
                                 struct viewport *viewport)
{
    int top = ++theme_stack_top[screen];
    if (top >= VPSTACK_DEPTH-1)
        panicf("Stack overflow... viewportmanager");
    theme_stack[screen][top].enabled = enable;
    theme_stack[screen][top].vp = viewport;
    toggle_theme(screen, false);
    /* then be nice and set the viewport up */
    if (viewport)
        viewport_set_defaults(viewport, screen);
}

void viewportmanager_theme_undo(enum screen_type screen, bool force_redraw)
{
    int top = --theme_stack_top[screen];
    if (top < 0)
        panicf("Stack underflow... viewportmanager");
    
    toggle_theme(screen, force_redraw);
}


static bool is_theme_enabled(enum screen_type screen)
{
    int top = theme_stack_top[screen];
    return theme_stack[screen][top].enabled;
}
#endif /* HAVE_LCD_BITMAP */

int viewport_get_nb_lines(const struct viewport *vp)
{
#ifdef HAVE_LCD_BITMAP
    return vp->height/font_get(vp->font)->height;
#else
    (void)vp;
    return 2;
#endif
}

static void viewportmanager_redraw(void* data)
{
    int i;
    FOR_NB_SCREENS(i)
    {
#ifdef HAVE_LCD_BITMAP
        if (is_theme_enabled(i))
            sb_skin_update(i, NULL != data);
#else
        (void)data;
        gui_statusbar_draw(&statusbars.statusbars[i], NULL, NULL);
#endif
    }
}

void viewportmanager_init()
{
#ifdef HAVE_LCD_BITMAP
    int i;
    FOR_NB_SCREENS(i)
    {
        theme_stack_top[i] = -1; /* the next call fixes this to 0 */
        /* We always want the theme enabled by default... */
        viewportmanager_theme_enable(i, true, NULL);
    }
#else
    add_event(GUI_EVENT_ACTIONUPDATE, false, viewportmanager_redraw);
#endif
}

#ifdef HAVE_LCD_BITMAP
void viewportmanager_theme_changed(const int which)
{
    int i;
#ifdef HAVE_BUTTONBAR
    if (which & THEME_BUTTONBAR)
    {   /* don't handle further, the custom ui viewport ignores the buttonbar,
         * as does viewport_set_defaults(), since only lists use it*/
        screens[SCREEN_MAIN].has_buttonbar = global_settings.buttonbar;
    }
#endif
    if (which & THEME_UI_VIEWPORT)
    {
    }
    if (which & THEME_LANGUAGE)
    {
    }
    if (which & THEME_STATUSBAR)
    {
        FOR_NB_SCREENS(i)
        {
            /* This can probably be done better...
             * disable the theme so it's forced to do a full redraw  */
            viewportmanager_theme_enable(i, false, NULL);
            viewportmanager_theme_undo(i, true);
        }
    }
    send_event(GUI_EVENT_THEME_CHANGED, NULL);
}

#ifdef HAVE_TOUCHSCREEN
/* check if a point (x and y coordinates) are within a viewport */
bool viewport_point_within_vp(const struct viewport *vp,
                               const int x, const int y)
{
    bool is_x = (x >= vp->x && x < (vp->x + vp->width));
    bool is_y = (y >= vp->y && y < (vp->y + vp->height));
    return (is_x && is_y);
}
#endif /* HAVE_TOUCHSCREEN */

static void set_default_align_flags(struct viewport *vp)
{
    vp->flags &= ~VP_FLAG_ALIGNMENT_MASK;
    if (UNLIKELY(lang_is_rtl()))
        vp->flags |= VP_FLAG_ALIGN_RIGHT;
}

#endif /* HAVE_LCD_BITMAP */
#endif /* __PCTOOL__ */

#ifdef HAVE_LCD_COLOR
#define ARG_STRING(_depth) ((_depth) == 2 ? "dddddgg":"dddddcc")
#else
#define ARG_STRING(_depth) "dddddgg"
#endif


void viewport_set_fullscreen(struct viewport *vp,
                              const enum screen_type screen)
{
    vp->x = 0;
    vp->y = 0;
    vp->width = screens[screen].lcdwidth;
    vp->height = screens[screen].lcdheight;

#ifdef HAVE_LCD_BITMAP
#ifndef __PCTOOL__
    set_default_align_flags(vp);
#endif
    vp->font = FONT_UI + screen; /* default to UI to discourage SYSFONT use */
    vp->drawmode = DRMODE_SOLID;
#if LCD_DEPTH > 1
#ifdef HAVE_REMOTE_LCD
    /* We only need this test if there is a remote LCD */
    if (screen == SCREEN_MAIN)
#endif
    {
        vp->fg_pattern = FG_FALLBACK;
        vp->bg_pattern = BG_FALLBACK;
#ifdef HAVE_LCD_COLOR
        vp->lss_pattern = global_settings.lss_color;
        vp->lse_pattern = global_settings.lse_color;
        vp->lst_pattern = global_settings.lst_color;
#endif
    }
#endif

#if defined(HAVE_REMOTE_LCD) && LCD_REMOTE_DEPTH > 1
    if (screen == SCREEN_REMOTE)
    {
        vp->fg_pattern = LCD_REMOTE_DEFAULT_FG;
        vp->bg_pattern = LCD_REMOTE_DEFAULT_BG;
    }
#endif
#endif
}

void viewport_set_defaults(struct viewport *vp,
                            const enum screen_type screen)
{
#if defined(HAVE_LCD_BITMAP) && !defined(__PCTOOL__)
    struct viewport *sbs_area = NULL;
    if (!is_theme_enabled(screen))
    {
        viewport_set_fullscreen(vp, screen);
        return;
    }
    sbs_area = sb_skin_get_info_vp(screen);
    
    if (sbs_area)
        *vp = *sbs_area;
    else
#endif /* HAVE_LCD_BITMAP */
        viewport_set_fullscreen(vp, screen);
}


#ifdef HAVE_LCD_BITMAP
const char* viewport_parse_viewport(struct viewport *vp,
                                    enum screen_type screen,
                                    const char *bufptr,
                                    const char separator)
{
    /* parse the list to the viewport struct */
    const char *ptr = bufptr;
    int depth;
    uint32_t set = 0;

    enum {
        PL_X = 0,
        PL_Y,
        PL_WIDTH,
        PL_HEIGHT,
        PL_FONT,
        PL_FG,
        PL_BG,
    };
    
    /* Work out the depth of this display */
    depth = screens[screen].depth;
#if (LCD_DEPTH == 1) || (defined(HAVE_REMOTE_LCD) && LCD_REMOTE_DEPTH == 1)
    if (depth == 1)
    {
        if (!(ptr = parse_list("ddddd", &set, separator, ptr,
                    &vp->x, &vp->y, &vp->width, &vp->height, &vp->font)))
            return NULL;
    }
    else
#endif
#if (LCD_DEPTH > 1) || (defined(HAVE_REMOTE_LCD) && LCD_REMOTE_DEPTH > 1)
    if (depth >= 2)
    {
        if (!(ptr = parse_list(ARG_STRING(depth), &set, separator, ptr,
                    &vp->x, &vp->y, &vp->width, &vp->height, &vp->font,
                    &vp->fg_pattern,&vp->bg_pattern)))
            return NULL;
    }
    else
#endif
    {}
#undef ARG_STRING

    /* X and Y *must* be set */
    if (!LIST_VALUE_PARSED(set, PL_X) || !LIST_VALUE_PARSED(set, PL_Y))
        return NULL;
    /* check for negative values */
    if (vp->x < 0)
        vp->x += screens[screen].lcdwidth;
    if (vp->y < 0)
        vp->y += screens[screen].lcdheight;
        
    /* fix defaults, 
     * and negative width/height which means "extend to edge minus value */
    if (!LIST_VALUE_PARSED(set, PL_WIDTH))
        vp->width = screens[screen].lcdwidth - vp->x;
    else if (vp->width < 0)
        vp->width = (vp->width + screens[screen].lcdwidth) - vp->x;
    if (!LIST_VALUE_PARSED(set, PL_HEIGHT))
        vp->height = screens[screen].lcdheight - vp->y;
    else if (vp->height < 0)
        vp->height = (vp->height + screens[screen].lcdheight) - vp->y;

#if (LCD_DEPTH > 1) || (defined(HAVE_REMOTE_LCD) && LCD_REMOTE_DEPTH > 1)
    if (!LIST_VALUE_PARSED(set, PL_FG))
        vp->fg_pattern = FG_FALLBACK;
    if (!LIST_VALUE_PARSED(set, PL_BG))
        vp->bg_pattern = BG_FALLBACK;
#endif /* LCD_DEPTH > 1 || LCD_REMOTE_DEPTH > 1 */

#ifdef HAVE_LCD_COLOR
    vp->lss_pattern = global_settings.lss_color;
    vp->lse_pattern = global_settings.lse_color;
    vp->lst_pattern = global_settings.lst_color;
#endif

    /* Validate the viewport dimensions - we know that the numbers are
       non-negative integers, ignore bars and assume the viewport takes them
       * into account */
    if ((vp->x >= screens[screen].lcdwidth) ||
        ((vp->x + vp->width) > screens[screen].lcdwidth) ||
        (vp->y >= screens[screen].lcdheight) ||
        ((vp->y + vp->height) > screens[screen].lcdheight))
    {
        return NULL;
    }

    /* Default to using the user font if the font was an invalid number or '-'
     * font 1 is *always* the UI font for the current screen
     * 2 is always the first extra font    */
    if (!LIST_VALUE_PARSED(set, PL_FONT))
        vp->font = FONT_UI;

    /* Set the defaults for fields not user-specified */
    vp->drawmode = DRMODE_SOLID;
#ifndef __PCTOOL__
    set_default_align_flags(vp);
#endif

    return ptr;
}
#endif
