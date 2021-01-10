#define _EXTI 1
#define _GPIO 1

// sdcc includes
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "time.h"

#include "calendar_com.h"
#include "trace_out.h"
#include "led_com.h"
#include "sun_com.h"
#include "flash_com.h"
#include "hal_com.h"

/* needed here for correct asm translation. */


#ifdef STM8
#include "../adapt_stm8/stm8l.h"
extern void _wakeupInterrupt(void) __interrupt(RTC_ALARM_IRQ_NO);
extern void SPI_IRQHandler(void) __interrupt(SPI_IRQ_NO);
extern void _overflowInterrupt(void) __interrupt(TIM1_UPDATE_OVERFLOW_TRIGER_IRQ);
extern void _captureInterrupt(void) __interrupt(TIM1_CAPTURE_IRQ);
#endif /* STM8 */

void _init(void)
{
}

static void printHelp(void)
{
	printf("\n");
	printf("\nConfiguration for light:\n");
	printf("\th - this help\n");
	printf("\t1 - Get datetime\n");
	printf("\t2 - Set datetime\n");
	printf("\t3 - Send intensity\n");
	printf("\t4 - Get intensity regarding time\n");
	printf("\t5 - Check if summer time\n");
	printf("\t6 - Continue (halt)\n");
}

static bool execute(const char a)
{
	bool retVal = true;
    switch (a)
    {
		case 'h':
			printHelp();
			break;
        case '1':
        {
            CALENDAR_DATE_S date;
            CALENDAR_TIME_S time;
            //getCalendar(&date, &time);
            NV_DATA_S dataNV;
			readFlash(&dataNV, sizeof(dataNV));
			date = dataNV._date;
			time = dataNV._time;
            printf("\n Current datetime: (%i.%i.%i, %i) (%i:%i:%i)\n", date.day, date.month, date.year,date.weekDay, time.hour, time.minute, time.second);
        }
        break;
		case '2':
		{
			CALENDAR_DATE_S date;
			CALENDAR_TIME_S time;

			printf("\t Set datetime:\n");
			printf("\tDay: \n");
			date.day = (getchar() - (int)'0') * 10;
			date.day += getchar() - (int)'0';
 			printf("\tMonth: \n");
			date.month= (getchar() - (int)'0') * 10;
			date.month += getchar() - (int)'0';
			printf("\tYear: \n");
			date.year= (getchar() - (int)'0') * 10;
			date.year += getchar() - (int)'0';
			printf("\tWeekday:  1-7 \n");
			date.weekDay = (getchar() - (int)'0');

			printf("\tHours: \n");
			time.hour = (getchar() - (int)'0') * 10;
			time.hour += getchar() - (int)'0';
			printf("\tMinutes: \n");
			time.minute = (getchar() - (int)'0') * 10;
			time.minute += getchar() - (int)'0';
			printf("\tSeconds: \n");
			time.second = (getchar() - (int)'0') * 10;
			time.second += getchar() - (int)'0';
            setCalendar(&date, &time);
            NV_DATA_S dataNV;
            dataNV._date = date;
            dataNV._time = time;
			if (eraseFlash() == true)
			{
				if (writeFlash(&dataNV, sizeof(dataNV)) == true)
				{
					printf("\t Calendar set\n");
				}
			}
        }
        break;
        case '3':
        {
            printf("\tTwo digits (00-99): \n");
            int intensity = (getchar() - (int)'0') * 10;
            intensity += (getchar() - (int)'0');
			sendIntensity(intensity);
			TRACE_01(TRACE_LEVEL_LOG, "Sent intensity %i", intensity);
		}
		break;
		case '4':
		{
			CALENDAR_DATE_S date;
			CALENDAR_TIME_S time;
			getCalendar(&date, &time);
			TRACE_01(TRACE_LEVEL_LOG,"Intensity: %i", getIntensity(&date, &time));
		}
		break;
		case '5':
		{
			CALENDAR_DATE_S date;
			getCalendar(&date, NULL);
			printf("Is summertime: %i\n", isSummerTime(&date));
		}
		break;
		case '6':
		{
			retVal = false;
			printf("Continue \n");
		}
		break;
        default:
            TRACE_01(TRACE_LEVEL_ERROR, "Unexpected choice %i", (int)a);
    }
	return retVal;
}



int main() {
	unsigned long i = 0;

	enableInterrupt();
	uartDebugInit();
	timerInit();
	flashInit();
	clockInit();

	NV_DATA_S data;
 //   readFlash(&data, sizeof(data));
	//setCalendar(&data._date, &data._time);

	//char test[] = "Hello";
	//writeFlash(test, sizeof(test));
	//eraseFlash();
	//writeFlash(test, sizeof(test));
	printHelp();
	volatile int k = 0;
	int f_counter = 0U;
	uint8_t f_intensity = 0U;

    CALENDAR_DATE_S calDate;
    CALENDAR_TIME_S calTime;

	do {
		char a = getchar();
		if (execute(a) == false)
		{
			break;
		}
	} while (1);

	do
    {
        waitForInterrupt();
		time_t unixtime = time(NULL);
		struct tm* timeCurrent = localtime(&unixtime);


        getCalendar(&calDate, &calTime);
        uint8_t intensity = getIntensity(&calDate, &calTime);

        if (f_intensity != intensity)
        {
            TRACE_02(TRACE_LEVEL_LOG,"New intensity: %i -> %i",f_intensity, intensity);
            f_intensity = intensity;
            sendIntensity(intensity);
        }

        if (((++f_counter) % 60U) == 0)
        {
			TRACE_01(TRACE_LEVEL_LOG, "f_counter = %i", f_counter);
            do
            {

                calDate.day = timeCurrent->tm_mday;
                calDate.month = timeCurrent->tm_mon;
                calDate.year = timeCurrent->tm_year - 100U;
                calDate.weekDay = timeCurrent->tm_wday;
                calTime.hour = timeCurrent->tm_hour;
                calTime.minute = timeCurrent->tm_min;
                calTime.second = timeCurrent->tm_sec;
                if (eraseFlash() == false)
                {
                    TRACE_00(TRACE_LEVEL_ERROR, "Erase flash failed");
                    break;
                }
                NV_DATA_S nvData;
                nvData._date = calDate;
                nvData._time = calTime;
                if (writeFlash(&nvData, sizeof(nvData)) == false)
                {
                    TRACE_00(TRACE_LEVEL_ERROR, "Write flash failed");
                    break;
                }
                TRACE_00(TRACE_LEVEL_LOG, "Write date to flash");
            } while (0);
        }
    } while (1);
}
