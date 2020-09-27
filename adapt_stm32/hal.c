#include "stm32f1xx.h"
//#include "core_cm3.h"
//#include "cmsis_gcc.h"

void enableInterrupt(void)
{
	__enable_irq();
}

void waitForInterrupt(void)
{
	__WFI();
}
