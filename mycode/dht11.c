#include "dht11.h"
#include "main.h"    
/*****************辰哥单片机设计******************
											STM32
 * 文件			:	DHT11温湿度传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.4
 * MCU			:	STM32F103C8T6
 * 接口			:	见dht11.h文件		
 * IP账号		:	辰哥单片机设计（同BILIBILI|抖音|快手|小红书|CSDN|公众号|视频号等）
 * 作者			:	辰哥
 * 工作室		: 异方辰电子工作室
 * 讲解视频	:	https://www.bilibili.com/video/BV182421Z7by/?share_source=copy_web&vd_source=097fdeaf6b6ecfed8a9ff7119c32faf2
 * 官方网站	:	www.yfcdz.cn

**********************BEGIN***********************/		
			
//复位DHT11

extern void delay_us(uint16_t us);

void DHT11_Rst(void)	   
{                 
    DHT11_Mode(OUT);
    DHT11_Low;
    HAL_Delay(20);
    DHT11_High;
    delay_us(30);  // 改为 delay_us
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
uint8_t DHT11_Check(void) 	   
{   
		uint8_t retry = 0;
    DHT11_Mode(IN);
    
    while (DHT11_Read && retry < 100) {
        retry++;
        delay_us(1);  // 改为 delay_us
    }
    if(retry >= 100) return 1;
    
    retry = 0;
    while (!DHT11_Read && retry < 100) {
        retry++;
        delay_us(1);  // 改为 delay_us
    }
    if(retry >= 100) return 1;
    
    return 0;
}

//从DHT11读取一个位
//返回值：1/0
uint8_t DHT11_Read_Bit(void) 			 
{
 uint8_t retry = 0;
    while(DHT11_Read && retry < 100) {
        retry++;
        delay_us(1);  // 改为 delay_us
    }
    
    retry = 0;
    while(!DHT11_Read && retry < 100) {
        retry++;
        delay_us(1);  // 改为 delay_us
    }
    
    delay_us(40);  // 改为 delay_us
    return DHT11_Read ? 1 : 0;
}

//从DHT11读取一个字节
//返回值：读到的数据
uint8_t DHT11_Read_Byte(void)    
{        
	 uint8_t i, dat = 0;
    
    for (i = 0; i < 8; i++) {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    return dat;
}

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5];
    uint8_t i;
    
    DHT11_Rst();
    if(DHT11_Check() == 0) {
        for(i = 0; i < 5; i++) {
            buf[i] = DHT11_Read_Byte();
        }
        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) {
            *humi = buf[0];
            *temp = buf[2];
            return 0;
        }
    }
    return 1;
	    
}

//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
uint8_t DHT11_Init(void)
{	 		    
	 DHT11_Rst();
   return DHT11_Check();
} 

void DHT11_Mode(uint8_t mode)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    if(mode == OUT) {
        GPIO_InitStruct.Pin = DHT11_GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    } else {
        GPIO_InitStruct.Pin = DHT11_GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);
}

