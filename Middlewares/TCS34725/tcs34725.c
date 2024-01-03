#include "tcs34725.h"

COLOR_RGBC rgb;
COLOR_HSL hsl;
Window brightness_window;

// ��ʼ������

uint32_t DWT_Dalay_Init(void)
{
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	DWT->CYCCNT = 0;
	__ASM volatile("NOP");
	__ASM volatile("NOP");
	__ASM volatile("NOP");

	if (DWT->CYCCNT)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// ��ʱ����,������n΢��
void DWT_Delay_us(volatile uint32_t nus)
{
	uint32_t clk_cycle_start = DWT->CYCCNT; // ��õ�ǰ����
	nus *= 72;								// 72MHZʱ��1us��ʱ������Ϊ72��1us����72�Σ�nus����nus *= 72

	while ((DWT->CYCCNT - clk_cycle_start < nus))
		; // �����������ﵽԤ��ʱ������ѭ��
}

void TCS34725_I2C_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11; // PB10/PB10=���I2C
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		 // ͨ���������
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;					   // �ٶ�
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);							   // ��ѡ�йܽų�ʼ��
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET); // �ߵ�ƽ
}
/*********************************************/
void TCS34725_I2C_Start()
{
	TCS_SDA_OUT();
	TCS_SDA_H;
	TCS_SCL_H;
	DWT_Delay_us(4); // delay_us(4);
	TCS_SDA_L;
	DWT_Delay_us(4); // delay_us(4);
	TCS_SCL_L;
}
/*********************************************/
void TCS34725_I2C_Stop()
{
	TCS_SDA_OUT();
	TCS_SCL_L;
	TCS_SDA_L;
	DWT_Delay_us(4); // delay_us(4);
	TCS_SCL_H;
	TCS_SDA_H;
	DWT_Delay_us(4); // delay_us(4);
}
/*********************************************/
// ����ֵ��1������Ӧ��ʧ��
//         0������Ӧ��ɹ�
uint8_t TCS34725_I2C_Wait_ACK()
{
	uint32_t t = 0;

	TCS_SDA_IN(); // SDA����Ϊ����
	TCS_SDA_H;
	DWT_Delay_us(1); // delay_us(1);
	TCS_SCL_H;
	DWT_Delay_us(1); // delay_us(1);
	while (TCS_SDA_READ)
	{
		t++;
		if (t > 250)
		{
			TCS34725_I2C_Stop();
			return 1;
		}
	}
	TCS_SCL_L;
	return 0;
}
/*********************************************/
// ����ACKӦ��
void TCS34725_I2C_ACK()
{
	TCS_SCL_L;
	TCS_SDA_OUT(); // sda�����
	TCS_SDA_L;
	DWT_Delay_us(2); // delay_us(2);
	TCS_SCL_H;
	DWT_Delay_us(2); // delay_us(2);
	TCS_SCL_L;
}
/*********************************************/
// ������ACKӦ��
void TCS34725_I2C_NACK()
{
	TCS_SCL_L;
	TCS_SDA_OUT(); // sda�����
	TCS_SDA_H;
	DWT_Delay_us(2); // delay_us(2);
	TCS_SCL_H;
	DWT_Delay_us(2); // delay_us(2);
	TCS_SCL_L;
}
/*********************************************/
// I2C����һ���ֽ�
void TCS34725_I2C_Send_Byte(uint8_t byte)
{
	uint8_t i;

	TCS_SDA_OUT(); // sda�����
	TCS_SCL_L;	   // ����ʱ�ӿ�ʼ���ݴ���
	for (i = 0; i < 8; i++)
	{
		if (((byte & 0x80) >> 7) == 1)
			TCS_SDA_H;
		else
			TCS_SDA_L;
		byte <<= 1;

		DWT_Delay_us(2); // delay_us(2);
		TCS_SCL_H;
		DWT_Delay_us(2); // delay_us(2);
		TCS_SCL_L;
		DWT_Delay_us(2); // delay_us(2);
	}
}
/*********************************************/
// ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t TCS34725_I2C_Read_Byte(uint8_t ack)
{
	uint8_t i, receive = 0;

	TCS_SDA_IN();
	for (i = 0; i < 8; i++)
	{
		TCS_SCL_L;
		DWT_Delay_us(2); // delay_us(2);
		TCS_SCL_H;
		receive <<= 1;
		if (TCS_SDA_READ)
			receive++;
		DWT_Delay_us(1); // delay_us(1);
	}
	if (!ack)
		TCS34725_I2C_NACK(); // ����nACK
	else
		TCS34725_I2C_ACK(); // ����ACK

	return receive;
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*******************************************************************************
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
 *******************************************************************************/
void TCS34725_I2C_Write(uint8_t slaveAddress, uint8_t *dataBuffer, uint8_t bytesNumber, uint8_t stopBit)
{
	uint8_t i = 0;

	TCS34725_I2C_Start();
	TCS34725_I2C_Send_Byte((slaveAddress << 1) | 0x00); // ���ʹӻ���ַд����
	TCS34725_I2C_Wait_ACK();
	for (i = 0; i < bytesNumber; i++)
	{
		TCS34725_I2C_Send_Byte(*(dataBuffer + i));
		TCS34725_I2C_Wait_ACK();
	}
	if (stopBit == 1)
		TCS34725_I2C_Stop();
}
/*******************************************************************************
 * @brief Reads data from a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes to read.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
 *******************************************************************************/
void TCS34725_I2C_Read(uint8_t slaveAddress, uint8_t *dataBuffer, uint8_t bytesNumber, uint8_t stopBit)
{
	uint8_t i = 0;

	TCS34725_I2C_Start();
	TCS34725_I2C_Send_Byte((slaveAddress << 1) | 0x01); // ���ʹӻ���ַ������
	TCS34725_I2C_Wait_ACK();
	for (i = 0; i < bytesNumber; i++)
	{
		if (i == bytesNumber - 1)
		{
			*(dataBuffer + i) = TCS34725_I2C_Read_Byte(0); // ��ȡ�����һ���ֽڷ���NACK
		}
		else
		{
			*(dataBuffer + i) = TCS34725_I2C_Read_Byte(1);
		}
	}
	if (stopBit == 1)
		TCS34725_I2C_Stop();
}
/*******************************************************************************
 * @brief Writes data into TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes that will be sent.
 *
 * @return None.
 *******************************************************************************/
void TCS34725_Write(uint8_t subAddr, uint8_t *dataBuffer, uint8_t bytesNumber)
{
	uint8_t sendBuffer[10] = {
		0,
	};
	uint8_t byte = 0;

	sendBuffer[0] = subAddr | TCS34725_COMMAND_BIT;
	for (byte = 1; byte <= bytesNumber; byte++)
	{
		sendBuffer[byte] = dataBuffer[byte - 1];
	}
	TCS34725_I2C_Write(TCS34725_ADDRESS, sendBuffer, bytesNumber + 1, 1);
}
/*******************************************************************************
 * @brief Reads data from TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes that will be read.
 *
 * @return None.
 *******************************************************************************/
void TCS34725_Read(uint8_t subAddr, uint8_t *dataBuffer, uint8_t bytesNumber)
{
	subAddr |= TCS34725_COMMAND_BIT;

	TCS34725_I2C_Write(TCS34725_ADDRESS, (uint8_t *)&subAddr, 1, 0);
	TCS34725_I2C_Read(TCS34725_ADDRESS, dataBuffer, bytesNumber, 1);
}
/*******************************************************************************
 * @brief TCS34725���û���ʱ��
 *
 * @return None
 *******************************************************************************/
void TCS34725_SetIntegrationTime(uint8_t time)
{
	TCS34725_Write(TCS34725_ATIME, &time, 1);
}
/*******************************************************************************
 * @brief TCS34725��������
 *
 * @return None
 *******************************************************************************/
void TCS34725_SetGain(uint8_t gain)
{
	TCS34725_Write(TCS34725_CONTROL, &gain, 1);
}
/*******************************************************************************
 * @brief TCS34725ʹ��
 *
 * @return None
 *******************************************************************************/
void TCS34725_Enable(void)
{
	uint8_t cmd = TCS34725_ENABLE_PON;

	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	cmd = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	// delay_s(600000);//delay_ms(3);//��ʱӦ�÷�������AEN֮��
}
/*******************************************************************************
 * @brief TCS34725ʧ��
 *
 * @return None
 *******************************************************************************/
void TCS34725_Disable(void)
{
	uint8_t cmd = 0;

	TCS34725_Read(TCS34725_ENABLE, &cmd, 1);
	cmd = cmd & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
}
/*******************************************************************************
 * @brief TCS34725��ʼ��
 *
 * @return ID - ID�Ĵ����е�ֵ
 *******************************************************************************/
uint8_t TCS34725_Init(void)
{
	uint8_t id = 0;

	TCS34725_I2C_Init();
	TCS34725_Read(TCS34725_ID, &id, 1); // TCS34725 �� ID �� 0x44 ���Ը���������ж��Ƿ�ɹ�����,0x4D��TCS34727;
	if (id == 0x4D | id == 0x44)
	{
		TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
		TCS34725_SetGain(TCS34725_GAIN_60X);
		brightness_window.gain = TCS34725_GAIN_60X;
		TCS34725_Enable();
		return 1;
	}
	return 0;
}
/*******************************************************************************
 * @brief TCS34725��ȡ����ͨ������
 *
 * @return data - ��ͨ����ת��ֵ
 *******************************************************************************/
uint16_t TCS34725_GetChannelData(uint8_t reg)
{
	uint8_t tmp[2] = {0, 0};
	uint16_t data;

	TCS34725_Read(reg, &tmp[0], 1);
	TCS34725_Read((reg + 1), &tmp[1], 1);
	data = (tmp[1] << 8) | tmp[0];

	return data;
}
/*******************************************************************************
 * @brief TCS34725��ȡ����ͨ������
 *
 * @return 1 - ת����ɣ����ݿ���
 *   	   0 - ת��δ��ɣ����ݲ�����
 *******************************************************************************/
uint8_t TCS34725_GetRawData(COLOR_RGBC *rgbc)
{
	uint8_t status = TCS34725_STATUS_AVALID;
	const uint8_t AGAIN_list[] = {1, 4, 16, 60};
	float CPL = AGAIN_list[brightness_window.gain] / 0.49548; // AGAIN * 0.49548 = AGAIN * (256 - 192) * 2.4 / (310)
	TCS34725_Read(TCS34725_STATUS, &status, 1);

	if (status & TCS34725_STATUS_AVALID)
	{
		rgbc->c = TCS34725_GetChannelData(TCS34725_CDATAL);
		rgbc->r = TCS34725_GetChannelData(TCS34725_RDATAL);
		rgbc->g = TCS34725_GetChannelData(TCS34725_GDATAL);
		rgbc->b = TCS34725_GetChannelData(TCS34725_BDATAL);

		rgbc->IR = abs(rgbc->b + rgbc->r + rgbc->g - rgbc->c) / 2;
		rgbc->c = rgbc->c - rgbc->IR;
		rgbc->r = rgbc->r - rgbc->IR;
		rgbc->g = rgbc->g - rgbc->IR;
		rgbc->b = rgbc->b - rgbc->IR;

		rgbc->Lux = ((rgbc->r * 136 + rgbc->g * 1000 - rgbc->b * 444) / 1000) / CPL;
		// rgbc->Lux = (rgbc->r + rgbc->g + rgbc->b ) / 3;
		return 1;
	}
	return 0;
}
/******************************************************************************/
// RGBתHSL
void RGBtoHSL(COLOR_RGBC *Rgb, COLOR_HSL *Hsl)
{
	uint8_t maxVal, minVal, difVal;
	uint8_t r = Rgb->r * 100 / Rgb->c; //[0-100]
	uint8_t g = Rgb->g * 100 / Rgb->c;
	uint8_t b = Rgb->b * 100 / Rgb->c;

	maxVal = max3v(r, g, b);
	minVal = min3v(r, g, b);
	difVal = maxVal - minVal;

	// ��������
	Hsl->l = (maxVal + minVal) / 2; //[0-100]

	if (maxVal == minVal) // ��r=g=b,�Ҷ�
	{
		Hsl->h = 0;
		Hsl->s = 0;
	}
	else
	{
		// ����ɫ��
		if (maxVal == r)
		{
			if (g >= b)
				Hsl->h = 60 * (g - b) / difVal;
			else
				Hsl->h = 60 * (g - b) / difVal + 360;
		}
		else
		{
			if (maxVal == g)
				Hsl->h = 60 * (b - r) / difVal + 120;
			else if (maxVal == b)
				Hsl->h = 60 * (r - g) / difVal + 240;
		}

		// ���㱥�Ͷ�
		if (Hsl->l <= 50)
			Hsl->s = difVal * 100 / (maxVal + minVal); //[0-100]
		else
			Hsl->s = difVal * 100 / (200 - (maxVal + minVal));
	}
}

/******************************************************************************/
// AGC

void initialize_window(Window *window)
{
	for (int i = 0; i < WINDOW_SIZE; ++i)
	{
		window->values[i] = 0;
	}
	window->index = 0;
	window->sum = 0;
}

void update_window(Window *window, int value)
{
	window->sum -= window->values[window->index];
	window->values[window->index] = value;
	window->sum += value;
	window->index = (window->index + 1) % WINDOW_SIZE;
}

int calculate_average(Window *window)
{
	return window->sum / WINDOW_SIZE;
}

uint8_t adjust_gain(COLOR_RGBC data, Window *brightness_window)
{
	// ���㵱ǰ����
	// int current_brightness = (data.r + data.g + data.b) / 3;

	// ���»�������ƽ��
	update_window(brightness_window, (data.r + data.g + data.b ) / 3);

	// ���㻬������ƽ������
	uint16_t average_brightness = calculate_average(brightness_window);

	// �����ǰ���ȹ��ͣ���������
	if (average_brightness < TARGET_brightness_Min && brightness_window->gain < 3)
	{
		brightness_window->gain++;
		return 1;
	}
	// �����ǰ���ȹ��ߣ���С����
	else if (((average_brightness > TARGET_brightness_Max) || (rgb.b > 9500) || (rgb.g > 9500) || (rgb.r > 9500)) && brightness_window->gain > 0)
	{
		brightness_window->gain--;
		return 1;
	}
	// �������治��
	else
	{
		return 0;
	}
}
/******************************************************************************/
