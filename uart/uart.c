#include "uart.h"

/*
 * Function : uartInit
 *
 * Description : Initialize the UART0 module with the following spec:
 *			9600 baud rate
 *			8 data bits
 *			No parity bits
 *			One stop bit
 *			Clocked from default 16MHz PIOSC
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : None
 */
 
 void uartInit(void)
 {
 
 	/****************************** Port Configuration ******************************/
 	
 	/* Enable clock to the UART0 module */
 	SYSCTL_RCGCUART_R |= UART0_ENABLE;	
 	
 	/* Enable clock to the Port A GPIO module, connected to the UART0 signals */
 	SYSCTL_RCGCGPIO_R |= EN_PORTA;
 	
 	/* Set GPIOAFSEL for Port A to enable the alternate functions on pins 0 and 1 */
 	GPIO_PORTA_AHB_AFSEL_R |= (PA1 | PA0);
 	
 	/* Set the slewrate and current level for the pins PA0 and PA1*/
 	/* Since there is no specific information, we enable 8mA drive for the pins 
 	   and the slewrate is kept untouched*/
 	GPIO_PORTA_AHB_DR8R_R |= (PA1 | PA0);
 	
 	/* Select the peripheral signal to be assigned to the pins PA0 and PA1 */
 	GPIO_PORTA_AHB_PCTL_R = ASSIGN_UART0;
 	
	/* Enable digital functions on the selected pins PA0 and PA1 */
 	GPIO_PORTA_AHB_DEN_R |= (PA1 | PA0);
 	
 	
 	/****************************** UART-0 Configuration ******************************
 		Baud-rate	:	9600
 		Data length	:	8-bits 
 		Parity		:	None
 		Stop bits	:	1
 		FIFO status	:	Disabled
 		Interrupts	: 	Disabled
 	*/
 	
 	/* Disable UART module before any configuration */
 	UART0_CTL_R |= DIS_UART;
 	
 	/* Write integer portion of Baud-Rate Divisor */
 	UART0_IBRD_R = 0x68; // refer to baud rate divisor calculation equation on page 1165. 
 	
 	/* Write fractional portion of BRD */
 	UART0_FBRD_R = 0x2B; // refer to baud rate divisor calculation equation on page 1165.
 	
 	/* Configure the desired serial parameters 
 			8-bits data length
 			FIFO enabled */
 	UART0_LCRH_R |= 0x00000070;
 	
 	/* Enable UART */
 	UART0_CTL_R |= EN_UART;
 	
 }
 
 /*
 * Function : charSend
 *
 * Description : Send the character to the pc through UART0
 *
 * Parameters : 
 *		
 *		chdata -> byte data to be send.
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : None
 */
 
void charSend(char chdata)
{
	/* Place the data to be transmitted in the data register */
	UART0_DR_R = chdata;
	
	/* check for transmission complete */
	while(UART0_FR_R & BUSY_FLAG);

}


 /*
 * Function : stringSend
 *
 * Description : Send the string to the pc through UART0
 *
 * Parameters : 
 *
 *		strdata -> pointer to the string
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : None
 */

void stringSend(char * strdata)
{

	uint16_t i;
	
	for(i=0; i<strlen(strdata); i++)
	{

		/* Place the data to be transmitted in the data register */
		UART0_DR_R = strdata[i];	
		
		/* Wait here if the FIFO is full */
		while(UART0_FR_R & TXFFULL);
		
	}
	
	/* check for transmission complete */
	while(UART0_FR_R & BUSY_FLAG);

}


/*
 * Function : charReceive
 *
 * Description : Receive a character from the pc through UART0
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : The byte data received
 */
 
 
 char charReceive(void)
 {
 	/* Temporary storage variable for received data along with 4 error status bits */
 	uint16_t temp;
 	
 	/* Variable for extracted data field from 'temp'*/
 	char cdata;
 	
 	temp = UART0_DR_R;
 	
 	if(temp & OVERRUN_ERROR)
 	{
 		stringSend("Overrun Error Occured!\n");
 	}
 	
 	if(temp & BREAK_ERROR)
 	{
 		stringSend("Break Error occured!\n");
 	}
 	
 	if(temp & FRAME_ERROR)
 	{
 		stringSend("Frame Error occured!\n");
 	}
 	
 	/* Clear the error flags by writing to error clear register*/
 	UART0_ECR_R = 0;
 	
 	/* Extract the data field */ 	
 	cdata = temp & DATA_BITS;
 	
 	return cdata;

 }
 
 
 /*
 * Function : loopTest
 *
 * Description : Receive a character from the pc through UART0 and
 *
 * 		 send it to the pc to form a loopback test
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : None
 */
 
 void loopTest(void)
 {
 	char recdata;
 	
 	if(UART0_FR_R & RXFFULL)
 	{
 		recdata = charReceive();
 		
 		charSend(recdata);
 		
 		stringSend("\n");
 		
 	}
 
 }
 
 
 
 /*
 * Function : stringReceive
 *
 * Description : Receive characters from the pc through UART0 and store it in a char array 
 *
 * 		 to form a string. The string is made with characters that come after a given start character
 *
 * 		 'header' and terminated by a given stop character 'footer'.
 *
 * 		 eg.: If header : '$' and footer : '*', then $prasanth* will make the string prasanth. 
 *
 * Parameters: 
 *
 * 		str_data -> pointer to the char array, where the characters are stored
 *		count    -> pointer to uint16_t variable, where the count of characters stored
 *		header   -> required start character
 *		footer	 -> required end character	
 *
 * Notes : This function is specific to the EK-TM4C1294XL board.
 *
 * Returns : None
 */
 
 void stringReceive(char str_data[], uint16_t * count, char header, char footer)
 {
 	uint16_t temp, i = 0;
 	
 	while(UART0_FR_R & RXFEMPTY);
 	
 	while((UART0_DR_R & DATA_BITS) != header);
 	
 	while(UART0_FR_R & RXFEMPTY);
 	
 	temp = UART0_DR_R;
 	
 	while((temp & DATA_BITS) != footer)
 	{
 		
 		str_data[i] = (temp & DATA_BITS);
 		 		
 		i++;
 		
 		if(temp & (OVERRUN_ERROR | BREAK_ERROR | FRAME_ERROR))
 		{
 		 			
 			if(temp & OVERRUN_ERROR)
 			{
		 		stringSend("Overrun Error Occured!\n");
		 	}
 	
		 	if(temp & BREAK_ERROR)
		 	{
		 		stringSend("Break Error occured!\n");
		 	}
 	
		 	if(temp & FRAME_ERROR)
		 	{
		 		stringSend("Frame Error occured!\n");
		 	}
		 	
		 	break;
 		}
 		
 		while(UART0_FR_R & RXFEMPTY);
 		
 		temp = UART0_DR_R;
 		
 	}
 	
 	str_data[i] = '\0';
 	 	
 	*count = i;
 	
 }
 
