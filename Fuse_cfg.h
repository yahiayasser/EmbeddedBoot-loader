/*
 * Fuse_cfg.h
 *
 *  Created on: 25 Feb 2020
 *      Author: Yahia
 */

#ifndef FUSE_CFG_H_
#define FUSE_CFG_H_

#define CKSEL0      1	//Select Clock source
#define CKSEL1      0	//Select Clock source
#define CKSEL2      0	//Select Clock source
#define CKSEL3      0	//Select Clock source
#define SUT0        0	//Select start-up time
#define SUT1        1	//Select start-up time
#define BODEN       1	//Brown-out Detector enable
#define BODLEVEL    1	//Brown-out Detector trigger level

/* High Fuse Byte */
#define BOOTRST     0	//Select reset vector
#define BOOTSZ0     (BOOTLOADER_BootSizeConfiguration & 0x01)
#define BOOTSZ1     ((BOOTLOADER_BootSizeConfiguration & 0x10) >> 1)
#define EESAVE      1	//EEPROM memory is preserved through the Chip Erase
#define CKOPT       1	//Oscillator options
#define SPIEN       0	//Enable SPI Serial Program and Data Downloading
#define JTAGEN      0	//Enable JTAG
#define OCDEN       1	//Enable OCD

#endif /* FUSE_CFG_H_ */
