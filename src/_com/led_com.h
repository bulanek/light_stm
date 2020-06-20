#ifndef LED_COM_H
#define LED_COM_H


#include "stdint.h"

void uartDebugInit(void);

void sendIntensity(const uint8_t intensity);

#endif // !LED_COM_H
