#define _EXTI 1
#define _GPIO 1

// sdcc includes
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <stm8l.h>
#include "calendar_com.h"
#include "trace_out.h"

void SPI_IRQHandler(void) __interrupt(10) {
}

int main() {
	unsigned long i = 0;

	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
	CLK_PCKENR1 = 0xFF; // Enable peripherals

	rtcInit();
	uartDebugInit();

	do {
		TRACE_00(TRACE_LEVEL_LOG, "Trace in main");
		for (i = 0; i < 147456; i++) {} // Sleep
	} while (1);
}
