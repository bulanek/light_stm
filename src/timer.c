#include "stm8l.h"
#include "led_com.h"

void timerInit(void) {
	CLK_PCKENR2->TIM1 = 1;

	PD_DDR |= 1 << 2; /* output mode D2*/
	PD_CR1 |= 1 << 2; /* push-pull D2*/
	PD_CR2 |= 1 << 2; /* 10 MHz speed*/

	PD_DDR |= 1 << 7; /* output mode D7 inverted*/
	PD_CR1 |= 1 << 7; /* push-pull D7 inverted*/
	PD_CR2 |= 1 << 7; /* 10 MHz speed*/

	TIM1_CCMR1->OC1PE = 1; /* preload reg enable*/
	TIM1_CCMR1->OC1M = OC1M_PWM_MODE_2;// OC1M_PWM_MODE_1; /* in up-counting, channel 1 is active as long as TIM1_CNT < TIM1_CCR1 */

	TIM1_ARRH = 100;
	TIM1_ARRL = 0x00;
	TIM1_CCR1H = 99; /* TODO zero*/
	TIM1_CCR1L = 0x00;

	TIM1_CR1->CMS = 0; /* Edge aligned mode*/
	TIM1_CR1->DIR = 0; /* up-counter*/

	TIM1_CCER1->CC1E = 1; /* capture/compare 1 output enable*/
	TIM1_CCER1->CC1P = 1;
	TIM1_BKR->AOE = 1; /* automatic outout enable. MOE auto */

	TIM1_BKR->OSSR = 1;  
	TIM1_BKR->OSSI = 1;

	TIM1_EGR->UG = 1;  /* Update generation*/
	TIM1_CR1->CEN = 1;
}


void sendIntensity(const uint8_t intensity)
{
	do
	{
		TIM1_CR1->CEN = intensity != 0 ? 1 : 0;
		TIM1_CCR1H = intensity;
		TIM1_CCR1L = 0;
	} while (0);
}