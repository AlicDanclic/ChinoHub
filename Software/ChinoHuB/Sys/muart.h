#ifndef __MUART_H__
#define __MUART_H__

#include "usart.h"

/**
 * 定义接收缓冲区大小。
 */
#define BUFFER_SIZE 128

/**
 * 接收缓冲区，用于存储接收到的数据。
 */
extern uint8_t rx_buffer[BUFFER_SIZE];

/**
 * 接收到的有效数据长度。
 */
extern uint16_t rx_length;

/**
 * 数据接收完成标志。
 */
extern uint8_t is_data_ready;

/**
 * 存储接收到的单个字符。
 */
extern uint8_t received_char;

/**
 * 状态标志，用于判断当前接收的状态。
 */
extern uint8_t state;

/**
 * 启动 UART 接收。
 * 启用 UART 接收中断，开始接收第一个字符。
 */
void UART_Start(void);

/**
 * UART 接收完成回调函数。
 * 当 UART 接收完成一个字符时，此函数被调用。
 *
 * @param huart UART 句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
 * 计算字符串长度。
 * 遍历字符串，直到遇到终止符 '\0'，计算字符串的长度。
 *
 * @param s 输入字符串
 * @return 字符串长度
 */
size_t strlen(const char *s);

/**
 * 发送字符。
 * 通过 UART 发送指定长度的字符数据。
 *
 * @param huart UART 句柄
 * @param str   要发送的字符数据
 * @param length 数据长度
 */
void UART_Sendchar(UART_HandleTypeDef *huart, const char *str, uint8_t length);

/**
 * 发送字符串。
 * 通过 UART 发送字符串。
 *
 * @param huart UART 句柄
 * @param str   要发送的字符串
 */
void UART_SendString(UART_HandleTypeDef *huart, const char *str);

/**
 * 数据解析。
 * 解析接收到的数据，提取有效数据并存储到输出数组中。
 * 数据格式：@data1|data2|...|datan|#
 *
 * @param outputArray 输出数组，存储解析后的数据
 * @param arraySize   输出数组的大小
 * @return 解析成功返回 1，否则返回 0
 */
uint8_t Data_Resolve(int16_t *outputArray, uint16_t arraySize);

/**
 * 将数组格式化为字符串。
 * 将输入数组的数据格式化为特定格式的字符串。
 * 格式：@data1|data2|...|datan|#
 *
 * @param inputArray  输入数组
 * @param arraySize   输入数组的大小
 * @param outputString 输出字符串
 * @param stringSize  输出字符串缓冲区的大小
 */
void formatArrayToCString(int16_t *inputArray, int16_t arraySize, char *outputString, uint16_t stringSize);

#endif /* __MUART_H__ */