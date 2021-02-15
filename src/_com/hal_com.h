#ifndef _HAL_COM_H_
#define _HAL_COM_H_

typedef enum
{
    RUN_MODE = 0,
    CFG_MODE = 1
} DEV_MODE_E;

void enableInterrupt(void);
void disableInterrupt(void);
void waitForInterrupt(void);

void initRunGpio(void);
DEV_MODE_E GetMode(void);



#endif // !_HAL_COM_H_
