#include "EncoderHelper.h"

volatile uint8_t trigger_count = 0;
volatile float encoder_rotations = 0;
volatile float total_distance = 0;

void increment_count()
{
	trigger_count++;
	if(trigger_count >= 12)
	{
		encoder_rotations++;
		trigger_count = 0;
	}
}

float get_encoder_distance()
{
	total_distance = encoder_rotations/4.0;
}