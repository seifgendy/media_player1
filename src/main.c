#include "../include/BIT_MATH.h"
#include "../include/STD_TYPES.h"

#include "../include/GPIO_interface.h"
#include "../include/RCC_interface.h"
#include "../include/SPI_interface.h"
#include "../include/STK_interface.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"

#include "../include/TFT_interfae.h"
#include "../include/Image.h"


u8 checker = 1;

void tft(void)
{
	// Initialize System Clock
	RCC_voidInit();
	// Enable Clock for GPIOA Peripheral
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	// Enable Clock For SPI1 Peripheral
	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_SPI1EN);
	// Setup The SPI Pins
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_AF); // PA5 (SCK1) To Be AF
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN7, GPIO_AF); // PA7 (MOSI1) To Be AF
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN4, GPIO_AF); // PA7 (MOSI1) To Be AF
	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN5, 5); // PA5 To operate as SCK1
	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN7, 5); // PA7 To operate as MOSI1
		MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN4, 5); // PA7 To operate as MOSI1
	// Initialize SysTick
	MSTK_voidInit();
	// Initialize SPI1
	SPI1_voidInit();
	//Initialize TFT
	HTFT_voidInit();
	u8 checker = 1;
while( 1 )
{
		HTFT_voidDisplayImage(&image);
if (checker == 0)
{

	break;
}
}
}


void tft2(void)
{
	// Initialize System Clock
	RCC_voidInit();
	// Enable Clock for GPIOA Peripheral
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	// Enable Clock For SPI1 Peripheral
	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_SPI1EN);
	// Setup The SPI Pins
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_AF); // PA5 (SCK1) To Be AF
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN7, GPIO_AF); // PA7 (MOSI1) To Be AF
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN4, GPIO_AF); // PA7 (MOSI1) To Be AF
	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN5, 5); // PA5 To operate as SCK1
	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN7, 5); // PA7 To operate as MOSI1
		MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN4, 5); // PA7 To operate as MOSI1
	// Initialize SysTick
	MSTK_voidInit();
	// Initialize SPI1
	SPI1_voidInit();
	//Initialize TFT
	HTFT_voidInit();

while(1)
{
		HTFT_voidDisplayImage(&image);
}
}















#define NO_START	0
#define START		1

void GetFrame(void);
void TakeAction(void);
void APP_voidPlay(void);

u8 u8ButtonData = 0;
u8 APP_u8StartBitFlag = NO_START;
u8 u8EdgeCounter = 0;
u32 u32ReceivedFrame[100];

void main(void)
{
	/*Initialize The System Clock*/
	RCC_voidInit();
	/*Enable GPIOA Peripheral Clock*/
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);

	/*Set RGB LED Pins, PA1, PA2, and PA3*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT);

	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN2, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN3, GPIO_LOW_SPEED);

	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT_PP);

	/*Set PA0 To Be Input Float*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);

	/*Initialize The SysTick*/
	MSTK_voidInit();

	/*Initialize The NVIC*/
	MNVIC_voidInit();

	/*Setup EXTI0 To Sense The Falling Edge*/
	MEXTI_voidChangeSenseMode(MEXTI_EXTI0, MEXTI_FALLING);
	/*Set The Callback function for EXTI0*/
	MEXTI_voidSetCallBack(MEXTI_EXTI0, &GetFrame);
	/*Enable EXTI0*/
	MEXTI_voidEnableInterrupt(MEXTI_EXTI0);

	/*NVIC Enable Interrupt For EXTI0*/
	MNVIC_voidPeripheralInterruptControl(6, MNVIC_INT_ENABLE);

	while(1)
	{
		;
	}
}

void GetFrame(void)
{
	if(APP_u8StartBitFlag == NO_START)
	{
		MSTK_voidSetPreloadValue(1000000);
		MSTK_voidSetSingleInterval2(&TakeAction);
		APP_u8StartBitFlag = START;
		u8 checker = 0;
	}
	else
	{
		u32ReceivedFrame[u8EdgeCounter] = MSTK_voidGetElapsedTime();
		MSTK_voidResetTimer();
		MSTK_voidSetPreloadValue(1000000);
		u8EdgeCounter++;
	}
}



void TakeAction(void)
{
	u8 Local_u8LoopCounter = 0;
	for(Local_u8LoopCounter = 0; Local_u8LoopCounter < 8; Local_u8LoopCounter++)
	{
		if(		(u32ReceivedFrame[17+Local_u8LoopCounter] >= 1000) &&
				(u32ReceivedFrame[17+Local_u8LoopCounter] <= 1500))
		{
			CLR_BIT(u8ButtonData, Local_u8LoopCounter);
		}
		else
		{
			SET_BIT(u8ButtonData, Local_u8LoopCounter);
		}
	}
	u8EdgeCounter = 0;
	APP_u8StartBitFlag = NO_START;
	MSTK_voidSTKEnable();
	APP_voidPlay();
}


void APP_voidPlay(void)
{
	switch(u8ButtonData)
	{
	case 12:
		tft();
		break;
	case 24:

		tft2();
		break;
	case 94:

		break;
	case 69:

		break;
	default:
		break;
	}
}

/* Power Button -> 69
 * Mute Button -> 71
 * 1 Button -> 12
 * 2 Button -> 24
 * 3 Button -> 94
 * */




















