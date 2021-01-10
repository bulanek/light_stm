#ifndef _HAL_COM_H_
#define _HAL_COM_H_


void enableInterrupt();
void waitForInterrupt(void);

void initRunGpio(void);
bool isRunGpioOn(void);



#endif // !_HAL_COM_H_
