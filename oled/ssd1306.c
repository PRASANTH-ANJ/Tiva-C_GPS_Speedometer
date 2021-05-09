#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "ssd1306.h"

/* space for display buffer */
/*uint8_t display_buffer[LCDHEIGHT * LCDWIDTH / 8] = {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xc0, 0xc0, 
	0x00, 0xd0, 0xdc, 0xdc, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 
	0x18, 0x38, 0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x23, 0xc1, 
	0xfe, 0xff, 0x1f, 0xe0, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x22, 0x22, 0x22, 0x32, 0x06,
	0x00, 0x02, 0x8e, 0xde, 0x38, 0xf0, 0xce, 0x86, 0x02, 0x00, 0xc0, 0x78, 0x4e, 0x4e, 0x7e, 0xf0, 
	0xc0, 0x00, 0x9c, 0x1e, 0x32, 0x32, 0x32, 0xe6, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 
	0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x07, 0x1f, 0x7f, 0xff, 0xe0, 0xe3, 
	0xe3, 0xe3, 0xe0, 0xe3, 0x7f, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0a, 0xfb, 0xfb, 0x0a, 0x00, 0x42, 0xc3, 0xc3, 0x82, 0x02, 0x02, 0x42, 0xc3, 
	0x42, 0x83, 0xc3, 0x40, 0x40, 0x42, 0xc3, 0x03, 0x82, 0x43, 0x43, 0xc0, 0xc0, 0x40, 0x40, 0xc3, 
	0x03, 0xc2, 0xc1, 0xc1, 0x42, 0x42, 0xc2, 0x81, 0x01, 0x40, 0xc0, 0xc0, 0x40, 0x00, 0x00, 0x00, 
	0x40, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x40, 0x00, 0x40, 
	0xc0, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x40, 0xc0, 0x40, 
	0x80, 0xc0, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x80, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00, 
	
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 
	0x07, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x40, 0x7f, 0x7f, 0x40, 0x00, 0x40, 0x7f, 0x01, 0x07, 0x0e, 0x1c, 0x38, 0x7f, 
	0x00, 0x33, 0x67, 0x46, 0x46, 0x4c, 0x7c, 0x3d, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x40, 0x00, 0x00, 
	0x00, 0x7f, 0x7f, 0x4c, 0x04, 0x0c, 0x3f, 0x77, 0x63, 0x40, 0x1f, 0x7f, 0x60, 0x40, 0x40, 0x40, 
	0x60, 0x3f, 0x00, 0x00, 0x7f, 0x41, 0x07, 0x3e, 0x78, 0x1c, 0x03, 0x7f, 0x7f, 0x40, 0x00, 0x40, 
	0x7f, 0x7f, 0x44, 0x44, 0x44, 0x40, 0x20, 0x00, 0x7f, 0x41, 0x03, 0x07, 0x0e, 0x1c, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x01, 0x63, 0x67, 0x46, 0x46, 0x4c, 0x7c, 0x38
};//16*32*/



/* Bitmap for TI splash screen */
/*uint8_t ti_buffer[LCDHEIGHT * LCDWIDTH / 8] = {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xc0, 0xc0, 
	0x00, 0xd0, 0xdc, 0xdc, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x38, 0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x23, 0xc1, 
	0xfe, 0xff, 0x1f, 0xe0, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x22, 0x22, 0x22, 0x32, 0x06, //ti
	0x00, 0x02, 0x8e, 0xde, 0x38, 0xf0, 0xce, 0x86, 0x02, 0x00, 0xc0, 0x78, 0x4e, 0x4e, 0x7e, 0xf0, 
	0xc0, 0x00, 0x9c, 0x1e, 0x32, 0x32, 0x32, 0xe6, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x07, 0x1f, 0x7f, 0xff, 0xe0, 0xe3, 
	0xe3, 0xe3, 0xe0, 0xe3, 0x7f, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0a, 0xfb, 0xfb, 0x0a, 0x00, 0x42, 0xc3, 0xc3, 0x82, 0x02, 0x02, 0x42, 0xc3, 
	0x42, 0x83, 0xc3, 0x40, 0x40, 0x42, 0xc3, 0x03, 0x82, 0x43, 0x43, 0xc0, 0xc0, 0x40, 0x40, 0xc3, 
	0x03, 0xc2, 0xc1, 0xc1, 0x42, 0x42, 0xc2, 0x81, 0x01, 0x40, 0xc0, 0xc0, 0x40, 0x00, 0x00, 0x00, 
	0x40, 0xc0, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x40, 0x00, 0x40, 
	0xc0, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x40, 0xc0, 0x40, 
	0x80, 0xc0, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x80, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 
	0x07, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x40, 0x7f, 0x7f, 0x40, 0x00, 0x40, 0x7f, 0x01, 0x07, 0x0e, 0x1c, 0x38, 0x7f, 
	0x00, 0x33, 0x67, 0x46, 0x46, 0x4c, 0x7c, 0x3d, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x40, 0x00, 0x00, 
	0x00, 0x7f, 0x7f, 0x4c, 0x04, 0x0c, 0x3f, 0x77, 0x63, 0x40, 0x1f, 0x7f, 0x60, 0x40, 0x40, 0x40, 
	0x60, 0x3f, 0x00, 0x00, 0x7f, 0x41, 0x07, 0x3e, 0x78, 0x1c, 0x03, 0x7f, 0x7f, 0x40, 0x00, 0x40, 
	0x7f, 0x7f, 0x44, 0x44, 0x44, 0x40, 0x20, 0x00, 0x7f, 0x41, 0x03, 0x07, 0x0e, 0x1c, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x01, 0x63, 0x67, 0x46, 0x46, 0x4c, 0x7c, 0x38
};//16*32*/


// the memory buffer for the LCD
/*static uint8_t buffer_ubuntu[LCDHEIGHT * LCDWIDTH / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0x7c, 0x3c, 0x7c, 0x9e, 
	0x9e, 0x9e, 0xbe, 0x4c, 0x4c, 0xf8, 0xf8, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0xf9, 0xf9, 0xe0, 0xc6, 0xdf, 0xbf, 
	0x3f, 0x3f, 0x9f, 0x1f, 0x44, 0xe4, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Ubuntu
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
	0x30, 0x20, 0x20, 0x3f, 0x00, 0x00, 0x3f, 0x21, 0x21, 0x11, 0x1e, 0x00, 0x1f, 0x30, 0x20, 0x20, 
	0x3f, 0x00, 0x3f, 0x3f, 0x01, 0x01, 0x3f, 0x00, 0x00, 0x3f, 0x21, 0x21, 0x00, 0x1f, 0x20, 0x20, 
	0x20, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};*/




/*
 * Function : init_OLEDInterface
 *
 * Description : Initializes the port pins PN5 (I2C_2_SCL) & PN4 (I2C_2_SDA) for I2C operation.
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None.
 */
 
void init_OLEDInterface(void){
	
	/* Enable and provide a clock to I2C module 2 in Run mode */
	SYSCTL_RCGCI2C_R |= I2C_MODULE2_CLKEN;
	
	/* Enable and provide a clock to GPIO Port N in Run mode */
	SYSCTL_RCGCGPIO_R |= GPIO_PORTN_CLKEN;
	
	GPIO_PORTN_DEN_R |= 0x30; // DEN
	
	/* Enable peripheral (I2C-2) signal on pins PN5 and PN4 */
	GPIO_PORTN_AFSEL_R |= PORTN_I2C_EN; 
	
	/* The PN4 (I2C_2_SDA) pin is configured as open drain */
	GPIO_PORTN_ODR_R |= PORTN4_OD;
	
	/* Assign the I2C signals to the pins through port control */
	GPIO_PORTN_PCTL_R |= (PORTN4_I2C_MODE | PORTN5_I2C_MODE); 
	
	/* I2C Master mode is enabled */
	I2C2_MCR_R |= I2C_MASTER_MODE_EN;
	
	/* Set the desired SCL clock speed of 100 Kbps (refer to equation) */
	I2C2_MTPR_R = 0x00000007;
	
}

/*
 * Function : OLED_command
 *
 * Description : Send a command to the OLED driver SSD1306.
 *
 * Notes : This function is specific to the I2C module in TM4C1294NCPDT controller.
 *
 * Returns : None.
 */

void OLED_command(uint8_t command){
	
	/* Setting OLED address (0x3C) and setting controller in transmit mode*/
	I2C2_MSA_R |= ((OLED_ADDRESS << 1) | TRANSMIT_MODE);
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = 0x00; // Control byte with D/C set to 0.
	
	/* start transmission by setting START & RUN bits to 1 */
	I2C2_MCS_R = (START | RUN);
	
	while((I2C2_MCS_R & BUSY) == 0); 
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = command; 
	
	I2C2_MCS_R = (STOP | RUN); // Stop transmission following the next byte.
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.*/
			
}


/*
 * Function : OLED_data
 *
 * Description : Send a data byte to the GDDRAM of OLED driver SSD1306.
 *
 * Notes : This function is specific to the I2C module in TM4C1294NCPDT controller.
 *
 * Returns : None.
 */

void OLED_data(uint8_t data){
	
	/* Setting OLED address (0x3C) and setting controller in transmit mode*/
	I2C2_MSA_R |= ((OLED_ADDRESS << 1) | TRANSMIT_MODE);
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = 0x40; // Data byte with D/C set to 1.
	
	/* start transmission by setting START & RUN bits to 1 */
	I2C2_MCS_R = (START | RUN);
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = data; 
	
	I2C2_MCS_R = (STOP | RUN); // Stop transmission following the next byte.
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
}





/*
 * Function : display
 *
 * Description : Write to the GDDRAM of the OLED driver SSD1306 from the 'buffer_***' array.
 *
 * Notes : This function is specific to the I2C module in TM4C1294NCPDT controller and to the SSD1306 command set.
 *
 * Returns : None.
 */

void display(uint8_t * buffer){
	
	/* Setting OLED address (0x3C) and setting controller in transmit mode*/
	I2C2_MSA_R |= ((OLED_ADDRESS << 1) | TRANSMIT_MODE);
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = 0x40; // Data byte with D/C set to 1.
	
	/* start transmission by setting START & RUN bits to 1 */
	I2C2_MCS_R = (START | RUN);
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
	for(uint16_t i = 0; i <= ((LCDHEIGHT * LCDWIDTH / 8) - 2); i++){
		
		I2C2_MDR_R = buffer[i]; 
	
		I2C2_MCS_R = (RUN); // Keep in run mode.
	
		while((I2C2_MCS_R & BUSY) == 0);
	
		while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
		
	}
	
	I2C2_MDR_R = buffer[((LCDHEIGHT * LCDWIDTH / 8) - 1)]; 
	
	I2C2_MCS_R = (STOP | RUN); // Stop transmission following the next byte.
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
}




/*
 * Function : clear
 *
 * Description : Clear the buffer array (write 0x00 to all locations).
 *
 * Notes : This function is specific to the I2C module in TM4C1294NCPDT controller and to the SSD1306 command set.
 *
 * Returns : None.
 */


void clear(void){
	
	/************** First clear the GDDRAM *************/
	/* Setting OLED address (0x3C) and setting controller in transmit mode*/
	I2C2_MSA_R |= ((OLED_ADDRESS << 1) | TRANSMIT_MODE);
	
	/* Placing data to be transmitted in data register */
	I2C2_MDR_R = 0x40; // Data byte with D/C set to 1.
	
	/* start transmission by setting START & RUN bits to 1 */
	I2C2_MCS_R = (START | RUN);
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
	
	for(uint16_t i = 0; i <= ((LCDHEIGHT * LCDWIDTH / 8) - 2); i++){
		
		I2C2_MDR_R = 0x00; 
	
		I2C2_MCS_R = (RUN); // Keep in run mode.
	
		while((I2C2_MCS_R & BUSY) == 0);
	
		while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.
		
	}
	
	I2C2_MDR_R = 0x00; 
	
	I2C2_MCS_R = (STOP | RUN); // Stop transmission following the next byte.
	
	while((I2C2_MCS_R & BUSY) == 0);
	
	while((I2C2_MCS_R & BUSY) == 1); // Checking the transmittion end.


	/***************** Secondly clear the local display buffer***************/
	for(uint16_t i = 0; i < (LCDHEIGHT * LCDWIDTH / 8); i++){
		
		display_buffer[i] = 0x00;	
		
	}
	
	display(display_buffer);
	
}




/*
 * Function : init_ssd1306
 *
 * Description : Initializes the OLED driver SSD1306 and displays a splash screen (to make sure everything worked fine), then clear the display.
 *
 * Notes : This function is specific to the I2C module in TM4C1294NCPDT controller and to the SSD1306 command set.
 *
 * Returns : None.
 */

void init_ssd1306(void){

    OLED_command(0xAE);				// Display off
    
    OLED_command(0b10101000);                    // SETMULTIPLEX
    OLED_command(0b00011111);                    // 1/32 duty 
    
    OLED_command(0b11010011);                    // SETDISPLAYOFFSET 
    OLED_command(0b00000000);                    // no offset 
    
    OLED_command(0b01000000);                    // SETSTARTLINE - line #0 
    
    OLED_command(0b10100000);                    // SEGREMAP 
    
    OLED_command(0b11000000);                    // COM SCAN Dir   0xC0 @ reset
    
    OLED_command(0b11011010);                    // SETCOMPINS           0xDA
    OLED_command(0b00000010);                    //                      0x02
    
    OLED_command(0b10000001);                    // SETCONTRAST          0x81
    OLED_command(0b10001111);                    //                      0x8F
    
    OLED_command(0b10100100);                    // DISPLAYALLON_RESUME  0xA4
    
    OLED_command(0b10100110);                    // NORMALDISPLAY        0xA6
    
    OLED_command(0b11010101);                    // SETDISPLAYCLOCKDIV   0xD5
    OLED_command(0b10000000);                    // the suggested ratio  0x80
    
    OLED_command(0b10001101);                    // CHARGEPUMP           0x8D
    OLED_command(0b00010100);                    // internal VCC
    
    OLED_command(0b00100000);                    // MEMORYMODE           0x20
    OLED_command(0b00000000);                    // horizontal addressing mode
    
    OLED_command(0b00100001);                          // SETCOLADDRESS       0x21
    OLED_command(0b00000000);                          // min                  0x00  start address
    OLED_command(0b01111111);                          // max                  0x7F  end address
    
    OLED_command(0b00100010);                          // SETPAGEADDRESS       0x22
    OLED_command(0b00000000);                          // min                  0x00  start address
    OLED_command(0b00000011);                          // max                  0x03  end address
    
    OLED_command(0b10101111);                    // DISPLAYON
      
    //display(); 
    
    //OLED_command(0b10100101);                    // DISPLAYALLON_ENTIRE  0xA5
    
    OLED_command(0b10100100);                    // DISPLAYALLON_RESUME  0xA4
    
    /* Displaying the splash screens */
    
	
	/* Set contrast to 0 prior to splash screen */
	OLED_command(0x81);                    // SETCONTRAST          0x81
    	OLED_command(0x00);                    // Blank screen                     0x00
    	
    	/* Splash screen */
    	display(display_buffer);
    	
    	/* FADE IN */
    	for(uint8_t i = 0; i < 0x8F; i++){
    		
    		OLED_command(0b10000001);      // SETCONTRAST          0x81
    		OLED_command(i);                    	
    		delay_ms(10);
    		
    	}
    	
    	/* Fade Out*/
    	for(uint8_t i = 0x8F; i > 0; i--){
    		
    		OLED_command(0b10000001);      // SETCONTRAST          0x81
    		OLED_command(i);                    	
    		delay_ms(10);
    		
    	}
    	
    	clear();
    	
    /* Re-set contrast to normal value */
	OLED_command(0x81);                    // SETCONTRAST          0x81
    	OLED_command(0x8F);                    
    	
    	
	
}





