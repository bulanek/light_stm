#ifndef STM8L_H
#define STM8L_H

#include "stdint.h"


#define RTC_ALARM_IRQ_NO    4U
#define SPI_IRQ_NO          26U

typedef struct {
    uint8_t CKM : 3;
    uint8_t : 5;
} CLK_CKDIVR_S;


typedef enum {
    NO_CLOCK = 0,
    CLOCK_HSI=1,
    CLOCK_LSI=2,
    CLOCK_HSE=4,
    CLOCK_LSE=8
} RTCSEL_E;

typedef struct {
    uint8_t RTCSWBSY : 1; /**<The system is busy during a RTC clock change */
    uint8_t RTCSEL : 4; /**< Configurable RTC clock source selection */
    uint8_t RTCDIV : 3;
} CLK_CRTCR_S;

typedef struct {
    uint8_t HSION: 1;
    uint8_t HSIRDY: 1;
    uint8_t LSION: 1;
    uint8_t LSIRDY: 1;
    uint8_t SAHALT : 1;
    uint8_t FHWU: 1;
    uint8_t BEEPHALT : 1;
    uint8_t : 1;
} CLK_ICKCR_S;

typedef struct {
    uint8_t TIM2 : 1;
    uint8_t TIM3 : 1;
    uint8_t TIM4 : 1;
    uint8_t I2C1 : 1;
    uint8_t SPI1 : 1;
    uint8_t USART1 : 1;
    uint8_t BEEP : 1;
    uint8_t DAC : 1;
} CLK_PCKENR1_S;

typedef struct {
    uint8_t ADC1 : 1;
    uint8_t TIM1 : 1;
    uint8_t RTC: 1;
    uint8_t LCD: 1;
    uint8_t DMA1 : 1;
    uint8_t COMP12: 1;
    uint8_t : 1;
    uint8_t BOOT_ROM: 1;
} CLK_PCKENR2_S;

typedef struct {
    uint8_t HSEON : 1;
    uint8_t HSERDY : 1;
    uint8_t LSEON : 1;
    uint8_t LSERDY : 1;
    uint8_t HSEBYP : 1;
    uint8_t LSEBYP : 1;
    uint8_t   : 2;
} CLK_ECKCR_S;

typedef struct {
    uint8_t AES: 1;
    uint8_t TIM6 : 1;
    uint8_t SPI2: 1;
    uint8_t USART2: 1;
    uint8_t USART3 : 1;
    uint8_t CSS_LSE: 1;
    uint8_t : 2;
} CLK_PCKENR3_S;


typedef struct {
    uint8_t SU : 4;
    uint8_t ST : 3;
    uint8_t : 1;
} RTC_TR1_S;

typedef struct {
    uint8_t MNU: 4;
    uint8_t MNT : 3;
    uint8_t : 1;
} RTC_TR2_S;

typedef struct {
    uint8_t HU : 4;
    uint8_t HT : 2;
    uint8_t PM : 1;
    uint8_t : 1;
} RTC_TR3_S;

typedef struct {
    uint8_t DU : 4;
    uint8_t DT : 2;
    uint8_t : 2;
} RTC_DR1_S;

typedef struct {
    uint8_t MU : 4;
    uint8_t MT : 1;
    uint8_t WDU: 3;
} RTC_DR2_S;

typedef struct {
    uint8_t YU : 4;
    uint8_t YT : 4;
} RTC_DR3_S;

typedef struct {
    uint8_t WUCKSEL : 3;
    uint8_t BYPSHAD : 1;
    uint8_t RATIO : 1;
    uint8_t FMT : 1;
    uint8_t : 1;
}RTC_CR1_S;

typedef struct {
    uint8_t ALREAE : 1;
    uint8_t : 1;
    uint8_t WUTE : 1;
    uint8_t : 1;
    uint8_t ALRAIE : 1;
    uint8_t : 1;
    uint8_t WUTIE : 1;
    uint8_t : 1;
} RTC_CR2_S;

typedef struct {

    uint8_t ADD1H : 1;
    uint8_t SUB1H : 1;
    uint8_t BCK : 1;
    uint8_t COSEL : 1;
    uint8_t POL : 1;
    uint8_t OSEL : 1;
    uint8_t COE : 1;
} RTC_CR3_S;

typedef struct {
    uint8_t ALRAWF : 1;
    uint8_t RECALPF : 1;
    uint8_t WUTWF : 1;
    uint8_t SHPF : 1;
    uint8_t INITS : 1;
    uint8_t RSF : 1;
    uint8_t INITF : 1;
    uint8_t INIT : 1;
} RTC_ISR1_S ;

typedef struct {
    uint8_t ALRAF : 1;
    uint8_t : 1;
    uint8_t WUTF : 1;
    uint8_t : 2;
    uint8_t TAMP1F : 1;
    uint8_t TAMP2F : 1;
    uint8_t TAMP3F : 1;
} RTC_ISR2_S ;

typedef struct {
    uint8_t PREDIV_S : 7;
    uint8_t : 1;
} RTC_SPRERH_S;

typedef struct {
    uint8_t PREDIV_S : 8;
} RTC_SPRERL_S;

typedef struct {
    uint8_t PREDIV_A : 7;
    uint8_t : 1;
} RTC_APRER_S;

typedef struct {
    uint8_t WUT : 8;
} RTC_WUTRH_S;

typedef struct {
    uint8_t WUT : 8;
} RTC_WUTRL_S;

/* USART*/

typedef struct {
    uint8_t PE : 1;
    uint8_t FE : 1;
    uint8_t NF : 1;
    uint8_t OR : 1;
    uint8_t IDLE : 1;
    uint8_t RXNE : 1;
    uint8_t TC : 1;
    uint8_t TXE : 1;
} USART_SR_S;

typedef struct {
    uint8_t DR : 8;
} USART_DR_S;

typedef struct {
    uint8_t USART_DIV_2_3 : 8;
} USART_BRR1_S;

typedef struct {
    uint8_t USART_DIV_LSB : 4;
    uint8_t USART_DIV_MSB : 4;
} USART_BRR2_S;

typedef struct {
    uint8_t PIEN : 1;
    uint8_t PS : 1;
    uint8_t PCEN : 1;
    uint8_t WAKE : 1;
    uint8_t M : 1;
    uint8_t USARTD : 1;
    uint8_t T8 : 1;
    uint8_t R8 : 1;
} USART_CR1_S;

typedef struct {
    uint8_t SBK : 1;
    uint8_t RWU : 1;
    uint8_t REN : 1;
    uint8_t TEN : 1;
    uint8_t ILIEN : 1;
    uint8_t RIEN : 1;
    uint8_t TCIEN : 1;
    uint8_t TIEN : 1;
} USART_CR2_S;

typedef struct {
    uint8_t CEN : 1;
    uint8_t UDIS : 1;
    uint8_t URS : 1;
    uint8_t OPM : 1;
    uint8_t DIR : 1;
    uint8_t CMS : 2;
    uint8_t ARPE : 1;
} TIM1_CR1_S;


typedef enum {
    OC1M_FROZEN=0,
    OC1M_ACTIVE_ON_MATCH,
    OC1M_INACTIVE_ON_MATCH,
    OC1M_TOGGLE,
    OC1M_FORCE_INACTIVE,
    OC1M_FORCE_ACTIVE,
    OC1M_PWM_MODE_1,
    OC1M_PWM_MODE_2,
} OC1M_E;

typedef struct {
    uint8_t UG : 1;
    uint8_t CC1G : 1;
    uint8_t CC2G : 1;
    uint8_t CC3G : 1;
    uint8_t CC4G : 1;
    uint8_t COMG : 1;
    uint8_t TG : 1;
    uint8_t BG : 1;
} TIM1_EGR_S;

typedef struct {
    uint8_t CC1S : 2;
    uint8_t OC1FE : 1;
    uint8_t OC1PE : 1;
    OC1M_E  OC1M : 3;
    uint8_t OC1CE : 1;
} TIM1_CCMR1_S;

typedef struct {
    uint8_t KEY : 8;
}RTC_WPR_S;

/* GPIO */
#define PA_ODR *(unsigned char*)0x5000
#define PA_IDR *(unsigned char*)0x5001
#define PA_DDR *(unsigned char*)0x5002
#define PA_CR1 *(unsigned char*)0x5003
#define PA_CR2 *(unsigned char*)0x5004

#define PB_ODR *(unsigned char*)0x5005
#define PB_IDR *(unsigned char*)0x5006
#define PB_DDR *(unsigned char*)0x5007
#define PB_CR1 *(unsigned char*)0x5008
#define PB_CR2 *(unsigned char*)0x5009

#define PC_ODR *(unsigned char*)0x500A
#define PC_IDR *(unsigned char*)0x500B
#define PC_DDR *(unsigned char*)0x500C
#define PC_CR1 *(unsigned char*)0x500D
#define PC_CR2 *(unsigned char*)0x500E

#define PD_ODR *(unsigned char*)0x500F
#define PD_IDR *(unsigned char*)0x5010
#define PD_DDR *(unsigned char*)0x5011
#define PD_CR1 *(unsigned char*)0x5012
#define PD_CR2 *(unsigned char*)0x5013

#define PE_ODR *(unsigned char*)0x5014
#define PE_IDR *(unsigned char*)0x5015
#define PE_DDR *(unsigned char*)0x5016
#define PE_CR1 *(unsigned char*)0x5017
#define PE_CR2 *(unsigned char*)0x5018

#define PF_ODR *(unsigned char*)0x5019
#define PF_IDR *(unsigned char*)0x501A
#define PF_DDR *(unsigned char*)0x501B
#define PF_CR1 *(unsigned char*)0x501C
#define PF_CR2 *(unsigned char*)0x501D

/* CLOCK */
#define CLK_DIVR	*(unsigned char*)0x50C0
#define CLK_CRTCR	((volatile CLK_CRTCR_S*)0x50C1)
#define CLK_ICKR	((volatile CLK_ICKCR_S*)0x50C2)
#define CLK_PCKENR1	((volatile CLK_PCKENR1_S*)0x50C3)
#define CLK_PCKENR2	((volatile CLK_PCKENR2_S*)0x50C4)
#define CLK_CCOR	*(unsigned char*)0x50C5
#define CLK_ECKR	((volatile CLK_ECKCR_S*)0x50C6)
#define CLK_SCSR	*(unsigned char*)0x50C7
#define CLK_SWR 	*(unsigned char*)0x50C8
#define CLK_SWCR	*(unsigned char*)0x50C9
#define CLK_CSSR	*(unsigned char*)0x50CA
#define CLK_CBEEPR	*(unsigned char*)0x50CB
#define CLK_HSICALR	*(unsigned char*)0x50CC
#define CLK_HSITRIMR	*(unsigned char*)0x50CD
#define CLK_HSIUNLCKR	*(unsigned char*)0x50CE
#define CLK_REGCSR	*(unsigned char*)0x50CF


/* RTC */

#define RTC_TR1 ((volatile RTC_TR1_S*) 0x5140)
#define RTC_TR2 ((volatile RTC_TR2_S*) 0x5141)
#define RTC_TR3 ((volatile RTC_TR3_S*) 0x5142)

#define RTC_DR1  ((volatile RTC_DR1_S*) 0x5144)
#define RTC_DR2  ((volatile RTC_DR2_S*) 0x5145)
#define RTC_DR3  ((volatile RTC_DR3_S*) 0x5146)

#define RTC_CR1  ((volatile RTC_CR1_S*) 0x5148)
#define RTC_CR2  ((volatile RTC_CR2_S*) 0x5149)
#define RTC_CR3  ((volatile RTC_CR3_S*) 0x514A)

#define RTC_ISR1 ((volatile RTC_ISR1_S*) 0x514C)
#define RTC_ISR2 ((volatile RTC_ISR2_S*) 0x514D)


#define RTC_SPRERH ((volatile RTC_SPRERH_S*) 0x5150)
#define RTC_SPRERL ((volatile RTC_SPRERL_S*) 0x5151)
#define RTC_APRER ((volatile RTC_APRER_S*) 0x5152)

#define RTC_WUTRH ((volatile RTC_WUTRH_S*) 0x5154)
#define RTC_WUTRL ((volatile RTC_WUTRL_S*) 0x5155)


#define RTC_WPR ((volatile RTC_WPR_S*)0x5159U)

/* ------------------- USART ------------------- */
#define USART1_SR ((volatile USART_SR_S*)0x5230)
#define USART1_DR ((volatile USART_DR_S*)0x5231)
#define USART1_BRR1 ((volatile USART_BRR1_S*)0x5232)
#define USART1_BRR2 ((volatile USART_BRR2_S*)0x5233)
#define USART1_CR1 ((volatile USART_CR1_S*)0x5234)
#define USART1_CR2 ((volatile USART_CR2_S*)0x5235)
#define USART1_CR3 *(unsigned char*)0x5236
#define USART1_CR4 *(unsigned char*)0x5237
#define USART1_CR5 *(unsigned char*)0x5238
#define USART1_GTR *(unsigned char*)0x5239
#define USART1_PSCR *(unsigned char*)0x523A

/* USART_CR1 bits */
#define USART_CR1_R8 (1 << 7)
#define USART_CR1_T8 (1 << 6)
#define USART_CR1_UARTD (1 << 5)
#define USART_CR1_M (1 << 4)
#define USART_CR1_WAKE (1 << 3)
#define USART_CR1_PCEN (1 << 2)
#define USART_CR1_PS (1 << 1)
#define USART_CR1_PIEN (1 << 0)

/* USART_CR2 bits */
#define USART_CR2_TIEN (1 << 7)
#define USART_CR2_TCIEN (1 << 6)
#define USART_CR2_RIEN (1 << 5)
#define USART_CR2_ILIEN (1 << 4)
#define USART_CR2_TEN (1 << 3)
#define USART_CR2_REN (1 << 2)
#define USART_CR2_RWU (1 << 1)
#define USART_CR2_SBK (1 << 0)

/* USART_CR3 bits */
#define USART_CR3_LINEN (1 << 6)
#define USART_CR3_STOP2 (1 << 5)
#define USART_CR3_STOP1 (1 << 4)
#define USART_CR3_CLKEN (1 << 3)
#define USART_CR3_CPOL (1 << 2)
#define USART_CR3_CPHA (1 << 1)
#define USART_CR3_LBCL (1 << 0)

/* USART_SR bits */
#define USART_SR_TXE (1 << 7)
#define USART_SR_TC (1 << 6)
#define USART_SR_RXNE (1 << 5)
#define USART_SR_IDLE (1 << 4)
#define USART_SR_OR (1 << 3)
#define USART_SR_NF (1 << 2)
#define USART_SR_FE (1 << 1)
#define USART_SR_PE (1 << 0)


/* ------------------- TIMERS ------------------- */
#define TIM1_CR1 ((volatile TIM1_CR1_S*)0x52B0)
#define TIM1_CR2 *(unsigned char*)0x52B1
#define TIM1_SMCR *(unsigned char*)0x52B2
#define TIM1_ETR *(unsigned char*)0x52B3
#define TIM1_DER *(unsigned char*)0x52B4
#define TIM1_IER *(unsigned char*)0x52B5
#define TIM1_SR1 *(unsigned char*)0x52B6
#define TIM1_SR2 *(unsigned char*)0x52B7
#define TIM1_EGR ((volatile TIM1_EGR_S *)0x52B8)
#define TIM1_CCMR1 ((volatile TIM1_CCMR1_S*)0x52B9)
#define TIM1_CCMR2 *(unsigned char*)0x52BA
#define TIM1_CCMR3 *(unsigned char*)0x52BB
#define TIM1_CCMR4 *(unsigned char*)0x52BC
#define TIM1_CCER1 *(unsigned char*)0x52BD
#define TIM1_CCER2 *(unsigned char*)0x52BE
#define TIM1_CNTRH *(unsigned char*)0x52BF
#define TIM1_CNTRL *(unsigned char*)0x52C0
#define TIM1_PSCRH *(unsigned char*)0x52C1
#define TIM1_PSCRL *(unsigned char*)0x52C2
#define TIM1_ARRH *(unsigned char*)0x52C3
#define TIM1_ARRL *(unsigned char*)0x52C4
#define TIM1_RCR *(unsigned char*)0x52C5
#define TIM1_CCR1H *(unsigned char*)0x52C6
#define TIM1_CCR1L *(unsigned char*)0x52C7
#define TIM1_CCR2H *(unsigned char*)0x52C8
#define TIM1_CCR2L *(unsigned char*)0x52C9
#define TIM1_CCR3H *(unsigned char*)0x52CA
#define TIM1_CCR3L *(unsigned char*)0x52CB
#define TIM1_CCR4H *(unsigned char*)0x52CC
#define TIM1_CCR4L *(unsigned char*)0x52CD
#define TIM1_BKR *(unsigned char*)0x52CE
#define TIM1_DTR *(unsigned char*)0x52CF
#define TIM1_OISR *(unsigned char*)0x52D0
#define TIM1_DCR1 *(unsigned char*)0x52D1
#define TIM1_DCR2 *(unsigned char*)0x52D2
#define TIM1_DMA1R *(unsigned char*)0x52D3

/* TIM_IER bits */
#define TIM_IER_BIE (1 << 7)
#define TIM_IER_TIE (1 << 6)
#define TIM_IER_COMIE (1 << 5)
#define TIM_IER_CC4IE (1 << 4)
#define TIM_IER_CC3IE (1 << 3)
#define TIM_IER_CC2IE (1 << 2)
#define TIM_IER_CC1IE (1 << 1)
#define TIM_IER_UIE (1 << 0)

/* TIM_CR1 bits */
#define TIM_CR1_APRE (1 << 7)
#define TIM_CR1_CMSH (1 << 6)
#define TIM_CR1_CMSL (1 << 5)
#define TIM_CR1_DIR (1 << 4)
#define TIM_CR1_OPM (1 << 3)
#define TIM_CR1_URS (1 << 2)
#define TIM_CR1_UDIS (1 << 1)
#define TIM_CR1_CEN (1 << 0)

/* TIM_SR1 bits */
#define TIM_SR1_BIF (1 << 7)
#define TIM_SR1_TIF (1 << 6)
#define TIM_SR1_COMIF (1 << 5)
#define TIM_SR1_CC4IF (1 << 4)
#define TIM_SR1_CC3IF (1 << 3)
#define TIM_SR1_CC2IF (1 << 2)
#define TIM_SR1_CC1IF (1 << 1)
#define TIM_SR1_UIF (1 << 0)
#endif // !STM8L_H
