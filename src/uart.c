#include <stm8l.h>
#include "stdint.h"

int putchar(int aChar) {
	USART1_DR->DR = (uint8_t)aChar;
	while (USART1_SR->TXE == 0);
	if (aChar == '\n') {
		USART1_DR->DR = (uint8_t)'\r';
		while (USART1_SR->TXE == 0);
	}
	return aChar;
}

int getchar(void)
{
	int output = (int)'\0';
	while (USART1_SR->RXNE  == 0);
	output = (int)USART1_DR->DR;
	return output;
}

void uartDebugInit(void)
{
	PC_DDR = 1<<3; // Put TX line on
	PC_CR1 |= 1<<3; /* Tx push-pull*/

	PC_DDR |= 0<<2; // Put RX line on
	PC_CR1 |= 1<<2; /* Rx pull up*/


	USART1_CR2->TEN = 1; // Allow TX & RX
	USART1_CR3 &= ~(USART_CR3_STOP1 | USART_CR3_STOP2); // 1 stop bit

	/* 9600 baud*/
	USART1_BRR2->USART_DIV_LSB = 0x3;
	USART1_BRR1->USART_DIV_2_3 = 0x68;
}

const uint8_t STARTUP_NUM = 0x1F;

typedef enum {
	DEFAULT = 0,
	RED,
	GREEN,
	BLUE
} CHANNEL_NUM_E;

typedef struct {
	uint8_t _startupNum;
	uint8_t _channelNum;
	uint8_t _intensity;
	uint8_t _checkSum;
} LED_MESSAGE_S;

void sendIntensity(const uint8_t intensity)
{
	LED_MESSAGE_S message;
	
	message._startupNum = STARTUP_NUM;
	for (int i = 0; i < 3; i++)
	{
		message._channelNum = i + 1;
		message._intensity = intensity;
		message._checkSum = message._startupNum + message._channelNum + message._intensity;
		for (int j = 0; j < 4; j++)
		{
			putchar(*(((uint8_t*)&message) + j));
		}
	}
}
