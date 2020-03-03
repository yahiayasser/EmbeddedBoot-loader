/*
 * Compiler.h
 *
 *  Created on: 25 Feb 2020
 *      Author: Yahia
 */

#ifndef COMPILER_H_
#define COMPILER_H_


#define	BootloaderSection	__attribute__ ((section (".bootloader")))
#define	AppSection	__attribute__ ((section (".text")))

#endif /* COMPILER_H_ */
