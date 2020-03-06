# EmbeddedBoot-loader
Embedded Boot-loader 1.0.0
Created on: 6 March 2020
Author: Yahia Yasser

In this repo you can find boot-loader project, and here we are going to demonstrate how to use it in your project.
To use this project you have to copy all the files and put it in your project folder, Include the header file 
in your project, You can only use the macros and APIs in Bootloader_interface file. To configure the boot-loader,
you have to edit parameters in Bootloader_cfg.h file.

Boot-loader specifications:
1- This service allow a systems software to be updated without the use of specialized hardware such as a JTAG 
   programmer, The boot-loader manages the systems images.
2- This service is also the earliest point at which the integrity of a system can be checked, it is automatically 
   called after uC reset without user intervention. 
3- This service can communicate over a variety of protocols such as USART, CAN, I2C, Ethernet, USB and the list 
   goes on for as many protocols that exist, depending on the uC capabilities and user configuration (Only UART in the mean time).
4- This service must be updated with the use of specialized hardware such as a JTAG programmer or another boot-loader. 
5- This service can parse different types of Hex files such as Intel HEX, Motorola S-Records and Raw Binary (In the 
   mean time, it only accepts Intel HEX files).
   
   For any further information, contact yahiayasserwah@gmail.com
