#include<stdio.h>

#include "app.h"
#include "main.h"

#include "arm_math.h"
#include "arm_const_structs.h"

#define UART_TIMEOUT 1000

extern UART_HandleTypeDef huart3;

q7_t multiplicacion(q7_t a, q7_t b);
void my_q7_to_float(q7_t * a, float * b);

uint32_t msg_gen(uint8_t *buffer, q7_t a, q7_t b, q7_t c, float c_arm, float c_my);

void app_lauch()
{
	uint8_t buffer[256] = {0};
	q7_t a = 0x040;
	q7_t b = 0x23;
	q7_t c;
	float arm;
	float my;
	uint32_t size;

	while(1)
	{
		c = multiplicacion(a, b);
		arm_q7_to_float(&c, &arm, 1);
		my_q7_to_float(&c, &my);
		size = msg_gen(buffer, a, b, c, arm, my);
		HAL_UART_Transmit(&huart3, buffer, size, UART_TIMEOUT);
		HAL_Delay(1000);
	}
}

uint32_t msg_gen(uint8_t *buffer, q7_t a, q7_t b, q7_t c, float c_arm, float c_my)
{
	return sprintf((char *)buffer, "A: 0x%X | B: 0x%X | C: 0x%X - 0d%d - arm_q7_to_float: %.15f - my_q7_to_float: %.15f\n\r", a, b, c, c, c_arm, c_my);
}

void my_q7_to_float(q7_t * a, float * b)
{
	q7_t aux_q7 = *a;
	float aux_float;
	/* Verifico el signo: q7 es de 8 bits y float es de 16 */
	aux_float = (aux_q7 & 0x80) ? (-1) : 0;

	for(uint8_t i = 1; i < 8; ++i)
	{
		/* Cada bit de q7 representa 2^(-n) */
		if(aux_q7&(0x80>>i))
		{
			/* rotación a la izquierda es una forma barata de dividir x2 */
			aux_float = aux_float + (1.0 / (1U << i));
	    }
	}
	*b = aux_float;
}

q7_t multiplicacion(q7_t a, q7_t b)
{
	q15_t result;
	result = a * b;
	result = result << 1;
	return ((q7_t)(result >> 8));
}
