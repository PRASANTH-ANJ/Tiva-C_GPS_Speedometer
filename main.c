#include "uart.h"
#include "timer.h"
#include "gps.h"
#include "nmea.h"
#include "ssd1306.h"
#include "ugui.h"


uint16_t count;

/* Global variables to recieve data */
char rcvdata[200], time[10], speed[4], validity[2], latitude[15], ns[2], longitude[15], ew[2];

void pset(UG_S16, UG_S16, UG_COLOR);

UG_GUI gui; // Global gui structure


/* space for display buffer */
uint8_t display_buffer[LCDHEIGHT * LCDWIDTH / 8] = {

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
};//16*32



/* 
 * Function : main
 *
 * Description : Get the NMEA string from GPS module and extract its fields using different functions to
 *		store each field in separate character arrays. Then send the array string to 
 *		pc using following configuration:
 *			9600, 8, N, 1
 *
 * Notes : Uses the uart driver specific to the TM4C1294NCPDT Controller.
 *		UART0 : interface with PC
 *		UART7 : Interface with GPS module (Cirocomm 600L)
 *
 * Returns : Contains an infinite loop 
 */
 
 int main (void)
 {	
 	
 	/* Configure the I2C pins */
	init_OLEDInterface();
 		
 	/* Initialize the timer module for delay_ms function */
 	timerInit();
 	
 	/* Initialize the UART0 */
 	uartInit();
 	
 	/* Initialize the OLED module */
	init_ssd1306();
	
	clear();
	
	
	
	
	
	UG_Init(&gui, pset, LCDWIDTH, LCDHEIGHT);
	
	UG_FontSelect(&FONT_6X8);
	
	UG_PutString(0, 0, "Initialization Completed! \n");
	
	display(display_buffer);
	
	delay_ms(1000);
	
	clear();
	
	UG_PutString(0, 0, "Initializing GPS... \n");
	
	display(display_buffer);
	
	
	
	
	
 	
 	/* Initialize the GPS module connected to UART7 */
 	gpsInit();
 	
 	/* Commanding the GPS module to send only GPGGA and GPVTG sentenses */
 	gpsSend("$PMTK314,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n");
 	
 	/* Receive the acknowledge string PMTK001 */
 	nmeaReceive(rcvdata, 1, '$', '*');
 	
 	/* Send the ACK string to pc with a line feed */
 	stringSend(rcvdata);
 	stringSend("\n");
 	
 	stringSend("Initialization completed \n");
 	
 	stringSend("waiting for GPS data....\n");
 	
 	
 	
 	delay_ms(1000);
	
	clear();
	
	UG_PutString(0, 0, "Waiting for GPS data... \n");
	
	display(display_buffer);
 	
 	
 	
 	while(1)
 	{
 		/* Receive the required NMEA sentenses from GPS */
 		nmeaReceive(rcvdata, 2, '$', '*');

		/* Get the validity field value in 'validity' array. '0' -> Invalid fix */
 		getField(validity, VALIDITY_INDEX);
 		
 		/* Checking whether the fix is valid or not */
 		if((validity[0] == '1') || (validity[0] == '2'))
 		{
 		
 			clear();
 			
			/* Get the local time stored in the 'time' array
			   and send it to the pc */
			getlocalTime();
			
			/* Get the speed in Km/h stored in the 'speed' array
			   and send it to the pc */
			getSpeed();
						
			/* Get the Latitude value stored in the 'latitude' array
			   and send it to the pc */
			getLatitude();
			
			/* Get the Longitude value stored in the 'longitude' array
			   and send it to the pc */
			getLongitude();
			
			//display(display_buffer);
			
			//stringSend("\n");
 			
 		}
 		
 		/* Current fix is not valid */
 		else
 		{
 			clear();
 			
 			UG_PutString(0, 0, "No GPS fix found.....!");
	
			display(display_buffer);
 			
 			stringSend("No GPS fix found.....");
 			
	 		stringSend("\n");
 		}
		
 	}
 	
 	return 0;
 	
 }
 
 
 
 void pset(UG_S16 x, UG_S16 y, UG_COLOR c){
	
	display_buffer[x + (y / 8)* LCDWIDTH] |= 1 << (y & 7);
	
	//display(display_buffer);

}


