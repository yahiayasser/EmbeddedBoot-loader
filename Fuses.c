/*
 * Fuses.c
 *
 *  Created on: 25 Feb 2020
 *      Author: Yahia
 */

#include "Bootloader.h"
#include "Fuse_cfg.h"

/* Low Fuse Byte */
#define _CKSEL0      (CKSEL0 << 0)
#define _CKSEL1      (CKSEL1 << 1)
#define _CKSEL2      (CKSEL2 << 2)
#define _CKSEL3      (CKSEL3 << 3)
#define _SUT0        (SUT0 << 4)
#define _SUT1        (SUT1 << 5)
#define _BODEN       (BODEN << 6)
#define _BODLEVEL    (BODLEVEL << 7)

/* High Fuse Byte */
#define _BOOTRST     (BOOTRST << 0)
#define _BOOTSZ0     (BOOTSZ0 << 1)
#define _BOOTSZ1     (BOOTSZ1 << 2)
#define _EESAVE      (EESAVE << 3)
#define _CKOPT       (CKOPT << 4)
#define _SPIEN       (SPIEN << 5)
#define _JTAGEN      (JTAGEN << 6)
#define _OCDEN       (OCDEN << 7)

FUSES =
    {
    	(_CKSEL0 | _CKSEL1 | _CKSEL2 | _CKSEL3 | _SUT0 | _SUT1 | _BODEN | _BODLEVEL), // .low
        (_BOOTRST | _BOOTSZ0 | _BOOTSZ1 | _EESAVE | _CKOPT | _SPIEN | _JTAGEN | _OCDEN) // .high
    };
