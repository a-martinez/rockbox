/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id:$
 *
 * Copyright (C) 2010 by Marcin Bukat
 *
 * code taken mostly from mkboot.c 
 * Copyright (C) 2005 by Linus Nielsen Feltzing
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mkmpioboot.h"

#define OF_FIRMWARE_LEN 0x100000 /* size of HD200_UPG.SYS file */
#define MPIO_STRING_OFFSET 0xfffe0

/* We support only 1.30.05 version of OF for now */
static char *mpio_string = "HD200  HDD Audio Ver113005";

/* MPIO HD200 firmware is plain binary image
 * 4 bytes of initial SP (loaded on reset)
 * 4 bytes of initial PC (loaded on reset)
 * binary image with entry point 0x00000008
 *
 * We put our bootloader code at 0x000e0000
 * and patch reset vector to jump directly
 * into our code on reset
 */

#ifndef RBUTIL
static void usage(void)
{
    printf("usage: mkmpioboot <firmware file> <boot file> <output file>\n");

    exit(1);
}
#endif

static unsigned char image[OF_FIRMWARE_LEN];

#ifndef RBUTIL
int main(int argc, char *argv[])
{
    char *infile, *bootfile, *outfile;
    int origin = 0xe0000;   /* MPIO HD200 bootloader address */

    if(argc < 3) {
        usage();
    }

        infile = argv[1];
        bootfile = argv[2];
        outfile = argv[3];

    return mkmpioboot(infile, bootfile, outfile, origin);
}
#endif

int mkmpioboot(const char* infile, const char* bootfile, const char* outfile, int origin)
{
    FILE *f;
    int i;
    int len;

    memset(image, 0xff, sizeof(image));

    /* First, read the mpio original firmware into the image */
    f = fopen(infile, "rb");
    if(!f) {
        perror(infile);
        return -1;
    }

    i = fread(image, 1, OF_FIRMWARE_LEN, f);
    if(i < OF_FIRMWARE_LEN) {
        perror(infile);
        fclose(f);
        return -2;
    }

    fclose(f);

    /* Now check if we have OF file loaded based on presence
     * of the version string in firmware 
     */

    if (strcmp((char*)(image + MPIO_STRING_OFFSET),mpio_string) != 0)
    {
        perror("Loaded firmware file does not look like MPIO OF file!");
        return -3;
    }

    /* Now, read the boot loader into the image */
    f = fopen(bootfile, "rb");
    if(!f) {
        perror(bootfile);
        fclose(f);
        return -4;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);

    /* Now check if the place we want to put
     * our bootloader is free
     */
    for(i=0;i<len;i++)
    {
        if (image[origin+i] != 0)
        {
            perror("Place for bootloader in OF file not empty");
            return -5;
        }
    }

    fseek(f, 0, SEEK_SET);

    i = fread(image + origin, 1, len, f);
    if(i < len) {
        perror(bootfile);
        fclose(f);
        return -6;
    }

    fclose(f);

    f = fopen(outfile, "wb");
    if(!f) {
        perror(outfile);
        return -7;
    }

    /* Patch the stack pointer address */    
    image[0] = image[origin + 0];
    image[1] = image[origin + 1];
    image[2] = image[origin + 2];
    image[3] = image[origin + 3];

    /* Patch the reset vector to start the boot loader */
    image[4] = image[origin + 4];
    image[5] = image[origin + 5];
    image[6] = image[origin + 6];
    image[7] = image[origin + 7];

    i = fwrite(image, 1, OF_FIRMWARE_LEN, f);
    if(i < OF_FIRMWARE_LEN) {
        perror(outfile);
        fclose(f);
        return -8;
    }

    printf("Wrote 0x%x bytes in %s\n", OF_FIRMWARE_LEN, outfile);
    
    fclose(f);
    
    return 0;
}
