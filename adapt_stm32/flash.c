#include "flash_com.h"
#include "trace_out.h"
#include "string.h"

#include "stm32f103xb.h"

static const uint16_t RDPRT = 0x00A5;

static const uint32_t ADDRESS_FLASH = 0x08000000;

static void _flashUnlock(void)
{
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

}

static void _flashLock(void)
{
}

void flashInit(void)
{
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);


}

bool writeFlash(const void* const pData, const uint16_t length)
{
    uint16_t* pValue = (uint16_t*)pData;
    uint16_t* pAddress = (uint16_t*)ADDRESS_FLASH;
    uint16_t lengthWord = length / 2;
    bool retVal = true;

    if (FLASH->CR & FLASH_CR_LOCK)
    {
        _flashUnlock();
    }
    FLASH->CR |= FLASH_CR_PG;

    /* write.. 1/2word*/
    while (lengthWord--)
    {
        *pAddress++ = *pValue++;
        while (FLASH->SR & FLASH_SR_BSY);
        if (FLASH->SR & FLASH_SR_WRPRTERR)
        {
            retVal = false;
            TRACE_00(TRACE_LEVEL_ERROR, "Write protection error");
            break;
        }
    }
    return retVal;
}

void readFlash(void* const pData, const uint16_t length)
{
    uint16_t* pAddress = (uint16_t*)ADDRESS_FLASH;
    uint16_t* pValue = (uint16_t*)pData;
    uint16_t lengthWord = length / 2;
    while (lengthWord--)
    {
        *pValue++ = *pAddress++;
    }
}


