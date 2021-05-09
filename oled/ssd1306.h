#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stdint.h>
#include "timer.h"

// Macro definitions
#define I2C_MODULE2_CLKEN 0x00000004
#define GPIO_PORTN_CLKEN 0x00001000
#define PORTN_I2C_EN 0x00000030
#define PORTN4_OD 0x00000010
#define PORTN4_I2C_MODE 0x00030000
#define PORTN5_I2C_MODE 0x00300000
#define I2C_MASTER_MODE_EN 0x00000010
#define OLED_ADDRESS 0x3C
#define TRANSMIT_MODE 0x00

#define RUN 0x00000001
#define START 0x00000002
#define STOP 0x00000004

// Bit mask for status bit BUSY
#define BUSY 0x00000001

// LCD dimensions

#define LCDHEIGHT 32
#define LCDWIDTH 128

//Commands
#define DISPLAY_ON 0xAF
#define FULL_DISPLAY_ON 0xA5


extern uint8_t display_buffer[LCDHEIGHT * LCDWIDTH / 8];



void init_OLEDInterface(void);

void init_ssd1306(void);

void OLED_command(uint8_t command);

void OLED_data(uint8_t data); 

void display(uint8_t *);

void clear(void);


#endif 
