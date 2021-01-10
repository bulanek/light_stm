#include "flash_com.h"
#include "trace_out.h"
#include "string.h"

#include "stm32f103xb.h"

static const uint32_t ADDRESS_FLASH = 0x800fc00; /* 1 KB page of flash*/

static void _flashUnlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

static void _flashLock(void)
{
}

void flashInit(void)
{
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);


}

bool eraseFlash(void)
{
    bool retVal = true;
    uint16_t* pAddress;
    while (FLASH->SR & FLASH_SR_BSY);
    _flashUnlock();
    FLASH->CR &= ~FLASH_CR_PG;
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = ADDRESS_FLASH;
    FLASH->CR |= FLASH_CR_STRT;
    while (FLASH->SR & FLASH_SR_BSY);
    pAddress = (uint16_t*)ADDRESS_FLASH;
    TRACE_01(TRACE_LEVEL_LOG, "erased flash, %i", *pAddress);
    return retVal;
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
    FLASH->CR &= ~FLASH_CR_PER;
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
        if (FLASH->SR & FLASH_SR_PGERR)
        {
            retVal = false;
            TRACE_00(TRACE_LEVEL_ERROR, "Writting error");
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


