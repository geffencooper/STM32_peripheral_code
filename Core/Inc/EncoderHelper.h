// servo control class

#ifndef ENCODER_HELPER_H
#define ENCODER_HELPER_H

#include "stdint.h"
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif
	
void increment_count();
float get_encoder_distance();
	
#ifdef __cplusplus
}
#endif

#endif
