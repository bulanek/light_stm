#include "stdint.h"
#include "led_com.h"
#include "stm32f1xx.h"




/* gpioa -p2 - tx, p3 rx*/
void uartDebugInit(void)
{
    RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    //RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART2->CR1 = 0;
    USART2->CR2 = 0;
    USART2->CR3 = 0;

    GPIOA->CRL &= ~GPIO_CRL_MODE2; 
    GPIOA->CRL |= GPIO_CRL_MODE2_0; /* output max speed 10 MHz*/
                                    /* floating input - default*/

    GPIOA->CRL &= ~GPIO_CRL_CNF2; 
    GPIOA->CRL |= GPIO_CRL_CNF2_1; /* alternate output*/
                                   /* alternate input default*/

    //enable uart
    USART2->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_UE;

    /*USARDIV = 16 MHz / (required UART clock * 8x (2-OVER8))  OVER8 = 0*/
    /* UPDATE FREQ!  fr 14.5 MHz -> value USARDIV = 7.8668 ->  Mantisa = 7, Fraction*16 = 14 */
    //USART2->BRR = 0x07E; /* 8.6875 -> Mantisa(USARDIV)=8 <4 | Fraction*16 (0.6875*16 = 11) */
    /* UPDATE FREQ!  fr 87MHz/4(presc) = 21.75 -> value USARDIV = 11.8001 ->  Mantisa = 11, Fraction*16 = 12 */
    /*USARDIV = 8 MHz / (9600  * 16) =  52.0833 -> Mant = 34, frac D */
    USART2->BRR = 0x34D;

    /* Configure USART1 */
    /* 8 data bit, 1 start bit, 1 stop bit; no parity; transmit enable;
     * over-sampling 16 */
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
    //USART2->CR1 |= USART_CR1_RXNEIE; /* Enable rx interrupt*/

    //IRQn_Type type = USART2_IRQn;
    //NVIC_EnableIRQ(type);
    //NVIC_SetPriority(type, 15U);

    while ((USART2->SR & USART_SR_TC) == 0);
}


