#include "led_com.h"
#include "stm32f103xb.h"

/* Timer 1, channel 1,  PA8*/
void timerInit(void) 
{
    /* gpio pa8*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRH &= ~GPIO_CRH_MODE8;
    GPIOA->CRH |= GPIO_CRH_MODE8_0; /* output max speed 10 MHz*/

    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_CNF8_1; /* alternate output*/

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;/* preload reg enable*/
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0; /* PWM mode 2*/
    TIM1->ARR = 100 << 4;
    TIM1->CCR1 = 0;
    TIM1->CCER |= TIM_CCER_CC1E; /* capture/compare 1 output enable*/
    TIM1->CCER |= TIM_CCER_CC1P; /* Capture/Compare 1 output Polarity */

    TIM1->BDTR |= TIM_BDTR_AOE; /* Automatic Output enable. */
    TIM1->BDTR |= TIM_BDTR_OSSI | TIM_BDTR_OSSR; /* Off-State Selection for Idle, Run mode */

    TIM1->EGR |= TIM_EGR_UG; /* Update Generation */
    TIM1->CR1 |= TIM_CR1_CEN;
}

void sendIntensity(const uint8_t intensity)
{
    if (intensity != 0)
    {
        TIM1->CCR1 = intensity << 4;
        TIM1->CR1 |= TIM_CR1_CEN;
    }
    else
    {
        TIM1->CR1 &= ~TIM_CR1_CEN;
    }
}