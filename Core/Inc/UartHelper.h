// servo control class

#ifndef UART_HELPER_H
#define UART_HELPER_H

#include "stdint.h"
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

class UartHelper
{
	public:
		UartHelper(UART_HandleTypeDef* handler_in)
		{
			handler = handler_in;
		}
	
		// function to send data over uart, pass in a pointer to the buffer, data size
		void tx_msg(uint8_t* data, int size);
	
	  // function to receive data over uart, will wait for start code 
	  uint8_t rx_msg(uint8_t* buffer, int buffer_size, uint32_t start_code);
	
	private:
		UART_HandleTypeDef* handler;
	  uint8_t start_code_buffer[4];
		uint8_t find_start(uint32_t start_code);
};

#define STM_START_CODE 0xF00DF00D // FOOD = sensor data
#define RPI_START_CODE 0x60606060 // GO = motor data

// 4 byte aligned
struct TX_STM_DATA
{
	 uint32_t start_code;
	 uint32_t frame_id;
	 uint8_t ultrasonic_data;
	 float tof1_data;
	 float tof2_data;
	 float encoder_distance;
};

// 4 byte aligned
struct RX_RPI_DATA
{
	uint32_t start_code;
	uint32_t frame_id;
	float steering_value;
	float drive_value;
};

#ifdef __cplusplus
}
#endif

#endif
