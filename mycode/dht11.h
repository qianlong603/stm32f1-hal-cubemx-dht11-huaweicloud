#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"  // 改为包含main.h，因为CubeMX生成的配置都在这里
#include "stm32f1xx_hal.h"
#include <stdint.h>
/*****************辰哥单片机设计******************
											STM32
 * 文件			:	DHT11温湿度传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.4
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码	
 * IP账号		:	辰哥单片机设计（同BILIBILI|抖音|快手|小红书|CSDN|公众号|视频号等）
 * 作者			:	辰哥
 * 工作室		: 异方辰电子工作室
 * 讲解视频	:	https://www.bilibili.com/video/BV182421Z7by/?share_source=copy_web&vd_source=097fdeaf6b6ecfed8a9ff7119c32faf2
 * 官方网站	:	www.yfcdz.cn

**********************BEGIN***********************/		


/***************根据自己需求更改****************/
//DHT11引脚宏定义
#define DHT11_GPIO_PORT  GPIOA
#define DHT11_GPIO_PIN   GPIO_PIN_6
/*********************END**********************/

//输出状态定义
#define OUT 1
#define IN  0

//控制DHT11引脚输出高低电平
#define DHT11_Low   HAL_GPIO_WritePin(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_PIN_RESET)
#define DHT11_High  HAL_GPIO_WritePin(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_PIN_SET)
#define DHT11_Read  HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_GPIO_PIN)

uint8_t DHT11_Init(void);  // 初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);  // 读取温湿度数据
uint8_t DHT11_Read_Byte(void);  // 读取一个字节的数据
uint8_t DHT11_Read_Bit(void);  // 读取一位的数据
void DHT11_Mode(uint8_t mode);  // DHT11引脚输出模式控制
uint8_t DHT11_Check(void);  // 检测DHT11
void DHT11_Rst(void);  // 复位DHT11

#endif
