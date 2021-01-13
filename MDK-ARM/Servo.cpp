#include "Servo.h"

// TIM4 has a frequency of 8Mhz with prescaler 128, so effective frequency is 62500 cycles/sec
// The counter period is 62500/50 cycles (1/50 seconds == 20ms)
// The pulse width needs to be set to some fraction of this value

// relative value from 0-100%
void Servo::forward(float speed)
{
	static float current_speed = 0;
	if(speed != current_speed)
	{
		__HAL_TIM_SET_COMPARE(handler, channel, (62500/50) * (((float)(speed)*(max-center))/100.0 + center));
		current_speed = speed;
	}
}
void Servo::backward(float speed)
{
	static float current_speed = 0;
	if(speed != current_speed)
	{
		__HAL_TIM_SET_COMPARE(handler, channel, (62500/50) * (center - ((float)(speed)*(center-min))/100.0));
		current_speed = speed;
	}
}
		
// relative value from -100-->100%, 0 is no turn
void Servo::turn(float position)
{
	static float current_position = 0.1;
	if(position != current_position)
	{
		if((position < 0.1) && (position > -0.1))
		{
			__HAL_TIM_SET_COMPARE(handler, channel, (62500/50) * center);
		}
		else if(position < 0)
		{
			backward(position*-1);
		}
		else if(position > 0)
		{
			forward(position);
		}
		current_position = position;
	}
}

void Servo::stop()
{
	__HAL_TIM_SET_COMPARE(handler, channel, (62500/50) * center);
}

void Servo::pause()
{
	__HAL_TIM_SET_COMPARE(handler, channel, (62500/50) * center);
}