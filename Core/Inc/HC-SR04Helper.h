// servo control class

#ifndef HC_SR04_HELPER
#define HC_SR04_HELPER

#include "stdint.h"
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif



void init_HCSR04(TIM_HandleTypeDef* delay_handler_in, TIM_HandleTypeDef* trig_handler_in);
	
void delay_us (uint16_t us);
	
void HCSR04_Read (void);
	
// Let's write the callback function
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

uint8_t get_ultrasonic_distance();

#ifdef __cplusplus
}
#endif

#endif
