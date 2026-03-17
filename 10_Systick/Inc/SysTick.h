/*
 * SysTick.h
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


/* ***** #defines ***** */
#define SYSTICK_ms_LoadVal		4000 //For default of 4MHZ, this load value produces 1ms of delay

#define ST_CTRL_ENABLE			(1U<<0)
#define ST_CTRL_CLKSRC			(1U<<2)
#define ST_CTRL_COUNTFLAG		(1U<<16)


/* ***** Function Prototypes ***** */
void SYS_Delay_ms(uint32_t delay);

#endif /* SYSTICK_H_ */
