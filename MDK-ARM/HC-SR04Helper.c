#include "HC-SR04Helper.h"

static TIM_HandleTypeDef* delay_handler;
static TIM_HandleTypeDef* trig_handler;
	
static uint32_t IC_Val1 = 0;
static uint32_t IC_Val2 = 0;
static uint32_t Difference = 0;
static uint8_t Is_First_Captured = 0;  // is the first value captured ?
static uint8_t Distance  = 0;

#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOA

void init_HCSR04(TIM_HandleTypeDef* delay_handler_in, TIM_HandleTypeDef* trig_handler_in)
{
	delay_handler = delay_handler_in;
	trig_handler = trig_handler_in;
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(delay_handler,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(delay_handler) < us);  // wait for the counter to reach the us input in the parameter
}
	
void HCSR04_Read (void)
{
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay_us(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(trig_handler, TIM_IT_CC1);
}
	
// Let's write the callback function
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if (Is_First_Captured==0) // if the first value is not captured
		{
			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured==1)   // if the first is already captured
		{
			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val2 > IC_Val1)
			{
				Difference = IC_Val2-IC_Val1;
			}

			else if (IC_Val1 > IC_Val2)
			{
				Difference = (0xffff - IC_Val1) + IC_Val2;
			}

			Distance = Difference * .034/2;
			Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(trig_handler, TIM_IT_CC1);
		}
	}
}

uint8_t get_ultrasonic_distance()
{
	return Distance;
}