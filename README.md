# Tiva-C_GPS_Speedometer
Tiva C launchpad based GPS Speedometer for bicycles.

Hi all,
This is my first repository related to embedded systems development with ARM Cortex-M4 microcontrollers. You can use this repository to make GPS location finder
with the Cirocomm 600L module and ssd1306 based OLED module. It can also be used as a reference to the startup file, make file, linkerscript and for the driver
library files of the following modules :

    *32-bit timer peripheral
  
    *I2C peripheral
  
    *UART peripheral 
  
sothat you can easily develop on the EK-TM4C1294XL board by using these driver libraries.

Interfacing Details:

OLED : I2C-2 module, Pins PN5 (SDA), PN4 (SCL)

UART : UART0 (Communication with PC), UART7 (GPS module interface)

       Configuration: 9600 8 N 1
       
       
Use the master branch for both the OLED and UART (PC communication) functionalities. If only the PC communication is required, use the 
