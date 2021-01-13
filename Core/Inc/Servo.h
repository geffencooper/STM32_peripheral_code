// servo control class

#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include "stdint.h"
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

class Servo
{
	public:
		Servo(TIM_HandleTypeDef* handler_in, uint32_t channel_in)
		{
			handler = handler_in;
			channel = channel_in;
			min = 0;
			max = 0;
			center = 0;
		}
		
		void set_calibration_values(float min_in, float center_in, float max_in)
		{
			min = min_in;
			max = max_in;
			center = center_in;
		}
		
		// relative value from 0-100%
		void forward(float speed);
		void backward(float speed);
		
		// relative value from -100-->100%, 0 is no turn
		void turn(float position);
		
		void stop();
		
		void pause();
		
		
	private:
		TIM_HandleTypeDef* handler;
		uint32_t channel;
	  float min;
	  float max;
	  float center;
};

#ifdef __cplusplus
}
#endif

#endif
