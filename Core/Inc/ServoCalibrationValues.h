// servo control class

#ifndef SERVO_CAL_H
#define SERVO_CAL_H

#include "stdint.h"
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

	// Steering Servo
	#define STEER_MAX 0.09
	#define STEER_CENTER 0.078
	#define STEER_MIN 0.065
	
	// Drive Servo
	#define DRIVE_MAX 0.085
	#define DRIVE_CENTER 0.076
	#define DRIVE_MIN 0.065
	
	// TOF servo
	#define TOF_MAX 0.115
	#define TOF_CENTER 0.065
	#define TOF_MIN 0.0257

#ifdef __cplusplus
}
#endif

#endif
