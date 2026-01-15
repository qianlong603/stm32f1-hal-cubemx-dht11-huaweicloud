#include "esp8266.h"
#include <stdio.h>

// 用于指向ESP8266连接的串口句柄
UART_HandleTypeDef *esp8266_huart;

// 简单的延时函数
static void ESP8266_Delay(uint32_t ms) {
    HAL_Delay(ms);
}

// 发送AT指令并检查响应
// 参数：指令，期望的响应字符串，超时时间(ms)
// 返回值：0-成功，1-超时或响应错误
uint8_t ESP8266_SendCommand(const char* command, const char* expected_response, uint32_t timeout) {
    char response_buffer[256] = {0};
    uint32_t start_time = HAL_GetTick();
    uint16_t index = 0;

    // 1. 清空接收缓冲区
    __HAL_UART_FLUSH_DRREGISTER(esp8266_huart);

    // 2. 发送指令
    HAL_UART_Transmit(esp8266_huart, (uint8_t*)command, strlen(command), 1000);
    // 发送换行符 \r\n
    HAL_UART_Transmit(esp8266_huart, (uint8_t*)"\r\n", 2, 1000);

    printf("[ESP8266] Sent: %s\r\n", command);

    // 3. 循环接收数据，直到超时或找到预期响应
    while ((HAL_GetTick() - start_time) < timeout) {
        uint8_t byte;
        if (HAL_UART_Receive(esp8266_huart, &byte, 1, 50) == HAL_OK) {
            if (index < sizeof(response_buffer) - 1) {
                response_buffer[index++] = byte;
                response_buffer[index] = '\0'; // 始终保持字符串结束符

                // 检查是否收到预期响应（例如 "OK" 或 "WIFI GOT IP"）
                if (expected_response != NULL && strstr(response_buffer, expected_response) != NULL) {
                    printf("[ESP8266] Recv: %s\r\n", response_buffer);
                    printf("[ESP8266] Command Success: %s\r\n", command);
                    return 0; // 成功
                }
                // 检查是否收到错误响应（例如 "ERROR"）
                if (strstr(response_buffer, "ERROR") != NULL || strstr(response_buffer, "FAIL") != NULL) {
                    printf("[ESP8266] Recv: %s\r\n", response_buffer);
                    printf("[ESP8266] Command Error: %s\r\n", command);
                    return 1; // 失败
                }
            }
        }
    }

    // 如果超时，打印接收到的内容（如果有）
    if (index > 0) {
        printf("[ESP8266] Timeout! Recv: %s\r\n", response_buffer);
    } else {
        printf("[ESP8266] Timeout! No response.\r\n");
    }
    return 1; // 超时失败
}

// ESP8266初始化流程
void ESP8266_Init(UART_HandleTypeDef *huart) {
   esp8266_huart = huart;
    
    uart_print(&huart1, "Initializing ESP8266...");
    
    // 给模块上电后一点启动时间
    HAL_Delay(2000);
    
    // 直接按照顺序发送AT指令，只进行简单延时
    uart_print(esp8266_huart, "AT+RST");          // 复位
    HAL_Delay(1000);
    
    uart_print(esp8266_huart, "ATE0");            // 关闭回显
    HAL_Delay(1000);
    
    uart_print(esp8266_huart, "AT+CWMODE=3");     // 设置双模式
    HAL_Delay(1000);
    
    // 连接WiFi
    uart_print(esp8266_huart, "AT+CWJAP=\"vivo x80\",\"abc12345\"");
    HAL_Delay(5000);
    
    // 配置MQTT
    uart_print(esp8266_huart, "AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"", USERNAME, PASSWORD);
    HAL_Delay(2000);
    
    uart_print(esp8266_huart, "AT+MQTTCLIENTID=0,\"%s\"", CLIENTID);
    HAL_Delay(3000);
    
    uart_print(esp8266_huart, "AT+MQTTCONN=0,\"%s\",1883,1", DOMAINNAME);
    HAL_Delay(4000);
    
    // 订阅主题
    uart_print(esp8266_huart, "AT+MQTTSUB=0,\"/%s/%s/user/get\",1", PRODUCTID, DEVICENAME);
    HAL_Delay(1000);
    
    uart_print(&huart1, "ESP8266 Initialization Complete!");
}

// 发送传感器数据到华为云
void Send_SensorData_To_Cloud(uint8_t temperature, uint8_t humidity) {
//    uart_print(esp8266_huart, 
//               "AT+MQTTPUB=0,\"$oc/devices/6967434b25dd2168b6ffeabd_jiuhusi_0_0_2026011507/sys/properties/report\","
//               "\"{\\\"services\\\":[{\\\"service_id\\\":\\\"sh\\\","
//               "\\\"properties\\\":{\\\"wendu\\\":%d,\\\"shidu\\\":%d}}]}\",0,0",
//               temperature, humidity);
	uart_print(esp8266_huart, "AT+MQTTPUB=0,\"$oc/devices/6967434b25dd2168b6ffeabd_jiuhusi_0_0_2026011507/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"sh\\\"\\,\\\"properties\\\":{\\\"wendu\\\": %d\\,\\\"shidu\\\": %d}}]}\",0,0\r\n",temperature, humidity);
}