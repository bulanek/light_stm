#define _EXTI 1
#define _GPIO 1

// sdcc includes
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <stm8l.h>
#include "calendar_com.h"
#include "trace_out.h"

/* needed here for correct asm translation. */
extern void _wakeupInterrupt(void) __interrupt(RTC_ALARM_IRQ_NO);
extern void SPI_IRQHandler(void) __interrupt(SPI_IRQ_NO);

static void printHelp(void)
{
	printf("\nConfiguration for light:\n");
	printf("\th - this help\n");
	printf("\t1 - Get datetime\n");
	printf("\t2 - Set datetime\n");
	printf("\t3 - Send intensity\n");
	printf("\t4 - Get intensity regarding time\n");
}

static void execute(const char a)
{
    switch (a)
    {
		case 'h':
			printHelp();
			break;
        case '1':
        {
            CALENDAR_DATE_S date;
            CALENDAR_TIME_S time;
            getCalendar(&date, &time);
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
			printf("\t Calendar set\n");
		}
			break;
		case '3':
		{
			uint16_t intensity = (getchar() - (int)'0') * 100;
			intensity +=(getchar() - (int)'0') * 10;
			intensity +=(getchar() - (int)'0') ;
			sendIntensity(intensity);
		}
		break;
		case '4':
		{
			CALENDAR_DATE_S date;
			CALENDAR_TIME_S time;
			getCalendar(&date, &time);
			printf("Intensity: %i\n", getIntensity(&date, &time));
		}
		break;
        default:
            TRACE_01(TRACE_LEVEL_ERROR, "Unexpected choice %i", (int)a);
    }
}


int main() {
	unsigned long i = 0;

	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
	__asm__("rim"); // enable interrupt
	rtcInit();
	uartDebugInit();
    printHelp();
	do {
		char a = getchar();
		execute(a);
	} while (1);
}
