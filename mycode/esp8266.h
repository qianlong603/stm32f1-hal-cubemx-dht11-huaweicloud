#ifndef __ESP8266_H
#define __ESP8266_H

#include "main.h"
#include "usart.h"
#include <string.h>

// 华为云连接参数（请替换为你自己的）
#define WIFI_SSID          "vivo"
#define WIFI_PASSWORD      "12345"
#define DOMAINNAME         "myhuaweicloud.com"
#define CLIENTID           "6967434d211507"
#define USERNAME           "69674"
#define PASSWORD           "04ebd80cf010bf6b60"
#define PRODUCTID          "6967dd21"
#define DEVICENAME         "sh"

// 函数声明
void ESP8266_Init(UART_HandleTypeDef *huart);
uint8_t ESP8266_SendCommand(const char* command, const char* expected_response, uint32_t timeout);
void Send_SensorData_To_Cloud(uint8_t temperature, uint8_t humidity);

#endif