#ifndef __GLASSLCD_RTC_H
#define __GLASSLCD_RTC_H

#include "stm32f10x.h"
#include "SystemConfig_RTC.h"

/*----------------------- LCD user configuration -----------------------------*/
/* Incomment the define line of the used LCD and comment the other one */
//#define USE_LCD_REF_PD_878    /* LCD ref: PD_878 : 8 digits 128 segments */
#define USE_LCD_REF_CT4_098  /* LCD ref: CT4-098: 4 digits 64 segments */

/* Common lines configuration - Port where the 4 common lines are connected */
#define CommonLines_Port   GPIOB

/* The previous line is to define where Common lines are located:
 * - Uncomment this line: the 4 common lines
 *   are located between PX.8 and PX.15
 * - Comment this line: the 4 common lines
 *   are located between PX.0 and PX.7
 */
#define CommonLines_EightHighPortPins  

/* Pin offset (do not exceed 4: [0..4]) offset of eight low port pins or
 * eight high port pins according to CommonLines_EightHighPortPins commented
 * or not
 */
#define CommonLines_Pin_Offset   4

/* Configuration of the two GPIOs which drive the LCD (power on/off) */
/* Port which the LCD bias plus pins are connected */
#define LCD_Bias_Port        GPIOA

/* The number of the first GPIO (LCD bias plus)
 * wich will power-off the resistor bridge in
 * low power mode
 */
#define LCD_BiasPlus_Pin     GPIO_Pin_8

/* Segment lines configuration */
/* Port where the Low Quarter digits segment lines are connected */
#define SegmentsLines_LQD_Port   GPIOB  

/* Enable the used GPIOs clocks */
#define RCC_APB2Periph_Used_GPIO    RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA

/* LCD interrupt priority configuration */
#define LCD_Priority_Value       1

/* If the LCD interrupt is run always as priority 0 please comment this line */
#define LCD_Use_Boost_Priority 

/* LCD Contrast value settings */
/* LCDContrastValue and PeriodValue are the only parameters modifiable by the user */
#define LCDContrastValue          70  /* LCD Contrast value in percent from 0 to 100 */
#define PeriodValue               28  /* Period */

/* Parameters not modifiable by the user */
#define PulseValueForContrast     ((LCDContrastValue * PeriodValue) / 100)
#define DeadTimeValue             (PeriodValue - PulseValueForContrast)
#define PulseValueForContrastLow  (PulseValueForContrast & (uint32_t)0x0000FFFF)
#define PulseValueForContrastHigh ((PulseValueForContrast & (uint32_t)0xFFFF0000) >> 16)
#define DeadTimeValueLow          (DeadTimeValue & (uint32_t)0x0000FFFF)
#define DeadTimeValueHigh         ((DeadTimeValue & (uint32_t)0xFFFF0000) >> 16)

/* GPIOs Masks definitions (section not modifiable by the user) */
#define PinsConfig         CRH
#define ALL_COMMON_LINES  (uint16_t)(0xF000)
#define ALL_COMMON_LINES_PP   (0x33330000)
#define ALL_SEGMENT_LINES      0x0FFF
#define ALL_SEGMENT_LINES_PP   0x33333333

void LCD_GPIO_Init(void);
void LCD_WriteInt(int val);
void LCD_WriteLines();
void LCD_WriteNone();
void LCD_WriteAll();
void LCD_WriteCfg();
void LCD_WriteError();

#endif
