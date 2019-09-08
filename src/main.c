/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include<stdio.h>
#include<stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"  //this is the first library you must include !
#include "task.h"

TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;
void vTask1_handler(void *pvParameter);
void vTask2_handler(void *pvParameter);

//used for semihosting
extern void initialise_monitor_handles();

int main(void)
{
	initialise_monitor_handles();
	printf("This is hello world example code \n");

	//1. Reset the RCC clock configuration to the default reset state. The projects set the system clock to 180Mhz by default but we don't want that.
	//HSI ON, PLL OFF, HSE OFF, system clock = 16Mhz, cpu_clock = 16Mhz
	RCC_DeInit();

	//2.Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//3. let's create 2 tasks:

	xTaskCreate(vTask1_handler,"Task-1",configMINIMAL_STACK_SIZE,NULL,2,&xTaskHandle1);
	xTaskCreate(vTask2_handler,"Task-2",configMINIMAL_STACK_SIZE,NULL,2,&xTaskHandle2);

	vTaskStartScheduler();
	for(;;);
}

void vTask1_handler(void *pvParameter)
{
	while(1)
	{
		printf("Hello-world: From Task-1 \n");
	}
}

void vTask2_handler(void *pvParameter)
{
	while(1)
	{
		printf("Hello-world: From Task-2 \n");
	}
}
