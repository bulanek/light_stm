#include "stm32f1xx.h"

void enableInterrupt(void)
{
	__enable_irq();
}

void waitForInterrupt(void)
{
	__WFI();
}
