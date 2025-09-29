#ifndef __OLED_H__
#define __OLED_H__

#include "i2c.h"
#include "oledfont.h"

#define BIG_Font_Size 16
#define SMALL_Font_Size 8

#define OLED_I2C hi2c1

/**
 * 写入指令函数。
 * 通过I2C接口向OLED显示屏发送指令。
 *
 * @param cmd 要发送的指令
 */
void _OLED_Write_CMD(uint8_t cmd);

/**
 * 写入数据函数。
 * 通过I2C接口向OLED显示屏发送数据。
 *
 * @param data 要发送的数据
 */
void _OLED_Write_DATA(uint8_t data);

/**
 * 打开显示。
 * 启用电荷泵并打开OLED显示屏。
 */
void _OLED_Display_On(void);

/**
 * 关闭显示。
 * 关闭电荷泵并关闭OLED显示屏。
 */
void _OLED_Display_Off(void);

/**
 * 设置光标位置。
 * 设置OLED显示屏的光标位置。
 *
 * @param x 水平位置
 * @param y 垂直位置
 */
void _OLED_Set_Pos(uint8_t x, uint8_t y);

/**
 * 填充屏幕。
 * 填充OLED显示屏的整个屏幕。
 */
void _OLED_On(void);

/**
 * 初始化OLED显示屏。
 * 发送初始化指令序列以配置OLED显示屏。
 */
void OLED_Init(void);

/**
 * 清屏函数。
 * 清除OLED显示屏的内容。
 */
void OLED_Clear(void);

/**
 * 显示数字。
 * 在OLED显示屏上显示数字。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param num 要显示的数字
 * @param len 数字的长度
 * @param size2 字体大小
 * @param Color_Turn 颜色模式
 */
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2, uint8_t Color_Turn);

/**
 * 显示浮点数。
 * 在OLED显示屏上显示浮点数。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param num 要显示的浮点数
 * @param z_len 整数部分的长度
 * @param f_len 小数部分的长度
 * @param size2 字体大小
 * @param Color_Turn 颜色模式
 */
void OLED_Showdecimal(uint8_t x, uint8_t y, float num, uint8_t z_len, uint8_t f_len, uint8_t size2, uint8_t Color_Turn);

/**
 * 显示字符。
 * 在OLED显示屏上显示单个字符。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param chr 要显示的字符
 * @param Char_Size 字体大小
 * @param Color_Turn 颜色模式
 */
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t Color_Turn);

/**
 * 显示字符串。
 * 在OLED显示屏上显示字符串。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param chr 要显示的字符串
 * @param Char_Size 字体大小
 * @param Color_Turn 颜色模式
 */
void OLED_ShowString(uint8_t x, uint8_t y, char *chr, uint8_t Char_Size, uint8_t Color_Turn);

/**
 * 显示汉字。
 * 在OLED显示屏上显示汉字。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param no 汉字的索引
 * @param Color_Turn 颜色模式
 */
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no, uint8_t Color_Turn);

/**
 * 绘制图片。
 * 在OLED显示屏上绘制图片。
 *
 * @param x0 起始水平位置
 * @param y0 起始垂直位置
 * @param x1 结束水平位置
 * @param y1 结束垂直位置
 * @param BMP 图片数据
 * @param Color_Turn 颜色模式
 */
void OLED_DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t *BMP, uint8_t Color_Turn);

/**
 * 全屏水平滚动。
 * 设置OLED显示屏的全屏水平滚动。
 *
 * @param direction 滚动方向
 */
void OLED_HorizontalShift(uint8_t direction);

/**
 * 部分水平滚动。
 * 设置OLED显示屏的部分水平滚动。
 *
 * @param direction 滚动方向
 * @param start 开始页地址
 * @param end 结束页地址
 */
void OLED_Some_HorizontalShift(uint8_t direction, uint8_t start, uint8_t end);

/**
 * 垂直水平滚动。
 * 设置OLED显示屏的垂直水平滚动。
 *
 * @param direction 滚动方向
 */
void OLED_VerticalAndHorizontalShift(uint8_t direction);

/**
 * 设置显示模式。
 * 设置OLED显示屏的显示模式。
 *
 * @param mode 显示模式
 */
void OLED_DisplayMode(uint8_t mode);

/**
 * 设置亮度。
 * 设置OLED显示屏的亮度。
 *
 * @param intensity 亮度值
 */
void OLED_IntensityControl(uint8_t intensity);

#endif