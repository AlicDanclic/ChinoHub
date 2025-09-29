#include "muart.h"

#define CHOOSE_UART huart1
#define UART_CHANNEL USART1
/**
 * 接收缓冲区，用于存储接收到的数据。
 * 大小由 BUFFER_SIZE 宏定义。
 */
uint8_t rx_buffer[BUFFER_SIZE] = {0};

/**
 * 接收到的有效数据长度。
 * 记录当前缓冲区中有效数据的数量。
 */
uint16_t rx_length = 0;

/**
 * 数据接收完成标志。
 * 当值为 1 时，表示数据接收完成，可以进行数据处理。
 */
uint8_t is_data_ready = 0;

/**
 * 存储接收到的单个字符。
 * 用于 UART 中断接收。
 */
uint8_t received_char = 0;

/**
 * 状态标志，用于判断当前接收的状态。
 * - 0：等待起始字符 '@'
 * - 1：正在接收数据
 */
uint8_t state = 0;

/**
 * 启动 UART 接收。
 * 启用 UART 接收中断，开始接收第一个字符。
 */
void UART_Start(void) {
    __HAL_UART_ENABLE_IT(&CHOOSE_UART, UART_IT_RXNE);
    HAL_UART_Receive_IT(&CHOOSE_UART, &received_char, 1);
}

/**
 * UART 接收完成回调函数。
 * 当 UART 接收完成一个字符时，此函数被调用。
 * 根据接收到的字符更新状态，并继续接收下一个字符。
 *
 * @param huart UART 句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART_CHANNEL) {
        if (state == 0) {
            if (received_char == '@') {
                state = 1;
            }
        } else {
            if (received_char == '#') {
                state = 0;
                is_data_ready = 1;
            } else {
                if (rx_length < BUFFER_SIZE - 1) {
                    rx_buffer[rx_length++] = received_char;
                }
            }
        }
        HAL_UART_Receive_IT(&CHOOSE_UART, &received_char, 1);
    }
}

/**
 * 计算字符串长度。
 * 遍历字符串，直到遇到终止符 '\0'，计算字符串的长度。
 *
 * @param s 输入字符串
 * @return 字符串长度
 */
size_t strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - s);
}

/**
 * 发送字符。
 * 通过 UART 发送指定长度的字符数据。
 *
 * @param huart UART 句柄
 * @param str   要发送的字符数据
 * @param length 数据长度
 */
void UART_Sendchar(UART_HandleTypeDef *huart, const char *str, uint8_t length) {
    HAL_UART_Transmit(huart, (uint8_t *)str, length, HAL_MAX_DELAY);
}

/**
 * 发送字符串。
 * 通过 UART 发送字符串。
 *
 * @param huart UART 句柄
 * @param str   要发送的字符串
 */
void UART_SendString(UART_HandleTypeDef *huart, const char *str) {
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

/**
 * 数据解析。
 * 解析接收到的数据，提取有效数据并存储到输出数组中。
 * 数据格式：@data1|data2|...|datan|#
 *
 * @param outputArray 输出数组，存储解析后的数据
 * @param arraySize   输出数组的大小
 * @return 解析成功返回 1，否则返回 0
 */
uint8_t Data_Resolve(int16_t *outputArray, uint16_t arraySize) {
    if (is_data_ready == 1) {
        __HAL_UART_DISABLE_IT(&CHOOSE_UART, UART_IT_RXNE);
        uint16_t index = 1;
        for (int8_t i = 0; i < rx_length;) {
            for (int8_t j = i; j < rx_length; j++) {
                if (rx_buffer[j] == '@') {
                    i++;
                    break;
                } else if (rx_buffer[j] == '|') {
                    int16_t sum = 0;
                    int16_t f = 1;
                    if (rx_buffer[i] == '-') {
                        i++;
                        f = -1;
                    }
                    while (i < j) {
                        sum = sum * 10 + rx_buffer[i] - '0';
                        i++;
                    }
                    if (index < arraySize) {
                        outputArray[index++] = sum * f;
                    }
                    i = j + 1;
                    break;
                }
            }
        }
        uint16_t count = 0;
        for (int8_t i = 0; i < rx_length; i++) {
            if (rx_buffer[i] == '|') {
                count++;
            }
        }
        outputArray[0] = count;
        is_data_ready = 0;
        rx_length = 0;
        __HAL_UART_ENABLE_IT(&CHOOSE_UART, UART_IT_RXNE);
        return 1;
    }
    return 0;
}

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
void formatArrayToCString(int16_t *inputArray, int16_t arraySize, char *outputString, uint16_t stringSize) {
    uint8_t index = 0;
    outputString[index++] = '@';
    uint8_t temp[4];
    int8_t s = 0;
    int16_t t = 0;

    for (int16_t i = 1; i <= inputArray[0]; i++) {
        t = inputArray[i];
        s = 0;
        if (t < 0) {
            t = -t;
            outputString[index++] = '-';
        }
        while (t) {
            temp[s++] = '0' + t % 10;
            t /= 10;
        }
        for (int8_t k = s - 1; k >= 0; k--) {
            outputString[index++] = temp[k];
        }
        outputString[index++] = '|';
    }
    outputString[index++] = '#';
    outputString[index++] = '\0';
}