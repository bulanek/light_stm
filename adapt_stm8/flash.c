#include "flash_com.h"
#include "trace_out.h"
#include "stm8l.h"

#include "string.h"

uint8_t* f_pFlashData;

STATIC_ASSERT(sizeof(NV_DATA_S) <= FLASH_BLOCK_SIZE_BYTES, wrong_size_nv_data);

static void _flashUnlock(void)
{
    FLASH_DUKR = 0xAE;
    FLASH_DUKR = 0x56; /* RM0031 3.5.2.  Memory access security system (MASS)*/

    while (FLASH_IAPSR->DUL == 0);
}

static void _flashLock(void)
{
    FLASH_IAPSR->DUL = 0;
}

void flashInit(void)
{
    FLASH_CR2->OPT = 1; /* Access opt bytes.*/
    OPT1 = 0xFF; /* disable readout protection*/
    while (FLASH_IAPSR->EOP != 1);
    OPT1 = 0xAA; /* disable readout protection*/
    while (FLASH_IAPSR->EOP != 1);

    f_pFlashData = DATA_SECTION_START_ADDR;
}

void writeFlash(const NV_DATA_S* const pData)
{
    _flashUnlock();
    volatile uint8_t iapsr;
    volatile FLASH_IAPSR_S* pIapsr;
    //while (FLASH_CR2->PRG == 1);
    //FLASH_CR2->PRG = 1;

    int counter = 0;
    while (++counter <= sizeof(NV_DATA_S))
    {
        *f_pFlashData++ = *((uint8_t*)pData + counter);
        iapsr = *(unsigned char*)0x5054;
        pIapsr = (FLASH_IAPSR_S*)&iapsr;
        while (pIapsr->EOP != 1);
    }
    f_pFlashData = DATA_SECTION_START_ADDR;

    while (pIapsr->EOP != 1);

    if (FLASH_IAPSR->WR_PG_DIS == 1)
    {
        TRACE_00(TRACE_LEVEL_ERROR, "write attempt to a write protected page occurred");
    }
    while (FLASH_IAPSR->EOP != 0); /* cleared by read operation (PM0054 Standard block programing seq).*/
    _flashLock();
}

void readFlash(NV_DATA_S* const pData)
{
    memcpy(pData ,f_pFlashData,sizeof(NV_DATA_S));
}


