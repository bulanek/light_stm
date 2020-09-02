#ifndef _FLASH_COM_H_
#define _FLASH_COM_H_

#include "calendar_com.h"

typedef struct {
    CALENDAR_DATE_S _date;
    CALENDAR_TIME_S _time;
} NV_DATA_S;


void flashInit(void);

void writeFlash(const NV_DATA_S* const pData);
void readFlash(NV_DATA_S* const pData);

#endif // !_FLASH_COM_H_
