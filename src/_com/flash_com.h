#ifndef _FLASH_COM_H_
#define _FLASH_COM_H_

#include "calendar_com.h"
#include "stdbool.h"

typedef struct {
    CALENDAR_DATE_S _date;
    CALENDAR_TIME_S _time;
} NV_DATA_S;


void flashInit(void);

bool writeFlash(const void* const pData, const uint16_t length);
void readFlash(void* const pData, const uint16_t length);

#endif // !_FLASH_COM_H_
