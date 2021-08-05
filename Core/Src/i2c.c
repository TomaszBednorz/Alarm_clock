#include "i2c.h"

I2C_HandleTypeDef hi2c1, hi2c2;


void i2c1_init(void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x2000090E; // I2C standard mode: 100kHz
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		error_handler();
	}

	// Configure Analogue filter
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		error_handler();
	}

}

void i2c2_init(void)
{
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x2000090E; // I2C standard mode: 100kHz
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&hi2c2) != HAL_OK)
	{
		error_handler();
	}

	// Configure Analogue filter
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		error_handler();
	}

}
