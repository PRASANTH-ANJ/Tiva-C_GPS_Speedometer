
#include "timer.h"
/*
 * Function: timerInit
 *
 * Description: Initializes the Timer0 module in TM4C1294NCPDT to the following configuration:
 *					** 32-bit
 *					** One-Shot Timer
 *					** Up-counting
 *					** No interrupts enabled
 *					** Configured for 1 second delay
 *
 * Notes: This function is specific to the TM4C1294NCPDT Controller.
 *
 * Returns: None.
 */
 
 void timerInit(void){
 	
 	SYSCTL_RCGCTIMER_R |= TIMER0_CLKEN; // Enabling clock to the timer0 module.
 	
 	for(unsigned int i = 0; i<500; i++); // Delay for timer starting 
 	
 	TIMER0_CTL_R &= TIMER0_DISABLE; // Disabling both the A and B sub-modules of Timer0 for register configuration.
 	
 	TIMER0_CFG_R = 0x00; // Write of 0x00 for 32-bit timer configuration.
 	
 	TIMER0_TAMR_R |=  (ONESHOT_MODE | COUNT_UP); // Setting the mode of timer_A as one-shot mode and direction as up counting.
 							// Only Timer_A register is required in 32-bit mode.
 	
 }
 
 
/*
 * Function: delay_ms
 *
 * Description: Handles the timer for generating the requested ms of delay.
 *
 * Notes: This function is specific to the TM4C1294NCPDT Controller. Uses polling instead of interrupts.
 *
 * Returns: None.
 */
 
 void delay_ms(uint32_t milliseconds){
 
 	uint32_t delay_value = milliseconds * ONE_MILLISECOND_COUNT;
 
 	TIMER0_TAILR_R = delay_value; // Value for getting requested ms of delay in 32-bit timer mode, with 16MHz clock from PIOSC.
 
 	TIMER0_CTL_R |= TIMER0_ENABLE; // Starts timer
 	
 	while((TIMER0_RIS_R & TIMER0_TIMEOUT) == 0){ // Wait for the timeout event to occur through polling.
 	
 	}
 	
 	TIMER0_ICR_R |= TIMER0_TIMEOUT; // Clear the timeout event status flag.
 	
 }
 
 
