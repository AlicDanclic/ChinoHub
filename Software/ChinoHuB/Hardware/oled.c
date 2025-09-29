#include "oled.h"

// SSD1306指令宏定义
#define OLED_CMD_DISPLAY_OFF          	0xAE // 关闭显示
#define OLED_CMD_SET_CLOCK_DIV        	0xD5 // 设置时钟分频因子
#define OLED_CMD_SET_MULTIPLEX        	0xA8 // 设置复用率
#define OLED_CMD_SET_DISP_OFFSET      	0xD3 // 设置显示偏移
#define OLED_CMD_SET_START_LINE       	0x40 // 设置起始行
#define OLED_CMD_SET_SEGMENT_REMAP    	0xA1 // 设置段重映射
#define OLED_CMD_SET_COMSCAN_DEC      	0xC8 // 设置COM扫描方向为递减
#define OLED_CMD_SET_COM_PINS         	0xDA // 设置COM引脚配置
#define OLED_CMD_SET_CONTRAST         	0x81 // 设置对比度
#define OLED_CMD_SET_PRECHARGE        	0xD9 // 设置预充电周期
#define OLED_CMD_SET_VCOMH            	0xDB // 设置VCOMH电平
#define OLED_CMD_DISPLAY_ALL_ON_RES   	0xA4 // 关闭全屏显示
#define OLED_CMD_NORMAL_DISPLAY       	0xA6 // 正常显示模式
#define OLED_CMD_CHARGE_PUMP          	0x8D // 设置电荷泵
#define OLED_CMD_DISPLAY_ON           	0xAF // 打开显示
#define OLED_CMD_STOP_SCROLL          	0x2E // 停止滚动
#define OLED_CMD_START_SCROLL         	0x2F // 开始滚动
#define OLED_CMD_SET_SCROLL_AREA      	0xA3 // 设置滚动区域
#define OLED_CMD_SET_SCROLL_SPEED     	0x26 // 设置滚动速度
#define OLED_CMD_SET_SCROLL_DIRECTION 	0x27 // 设置滚动方向
#define OLED_CMD_SET_SCROLL_REGION    	0x29 // 设置滚动区域
#define OLED_CMD_SET_SCROLL_MODE      	0x2A // 设置滚动模式
#define OLED_CMD_SET_SCROLL_OFFSET    	0x2B // 设置滚动偏移量
#define OLED_CMD_SET_SCROLL_START     	0x2C // 设置滚动起始页
#define OLED_CMD_SET_SCROLL_END       	0x2D // 设置滚动结束页
#define OLED_CMD_SET_SCROLL_ACTIVATE  	0x2F // 激活滚动
#define OLED_CMD_SET_SCROLL_DEACTIVATE 	0x2E // 禁用滚动
#define OLED_CMD_SET_SCROLL_EXIT      	0x2E // 退出滚动
#define OLED_CMD_ENABLE_CHARGE_PUMP   	0x14 // 启用电荷泵
#define OLED_CMD_SET_CLOCK_DIV_VALUE  	0x80  // 设置时钟分频因子的值
#define OLED_CMD_SET_MULTIPLEX_VALUE  	0x3F  // 设置复用率的值
#define OLED_CMD_SET_DISP_OFFSET_VALUE 	0x00 // 设置显示偏移的值
#define OLED_CMD_SET_COM_PINS_VALUE    	0x12  // 设置COM引脚配置的值
#define OLED_CMD_SET_CONTRAST_VALUE   	0xCF  // 设置对比度的值
#define OLED_CMD_SET_PRECHARGE_VALUE  	0xF1  // 设置预充电周期的值
#define OLED_CMD_SET_VCOMH_VALUE      	0x40  // 设置VCOMH电平的值
#define OLED_CMD_SCROLL_DUMMY_BYTE    	0x00 // 虚拟字节
#define OLED_CMD_SCROLL_SPEED         	0x07 // 设置滚动速度
#define OLED_CMD_SCROLL_START_PAGE    	0x00 // 设置滚动起始页
#define OLED_CMD_SCROLL_END_PAGE      	0x07 // 设置滚动结束页
#define OLED_CMD_SCROLL_OFFSET        	0x01 // 垂直滚动偏移量
#define OLED_CMD_SCROLL_DUMMY_BYTE2   	0xFF // 虚拟字节

// I2C地址和内存地址宏定义
#define OLED_I2C_ADDRESS              0x78 // OLED显示屏的I2C地址
#define OLED_CMD_ADDRESS              0x00 // 命令寄存器地址
#define OLED_DATA_ADDRESS             0x40 // 数据寄存器地址
#define OLED_I2C_TIMEOUT              0x100 // I2C通信超时时间

// 初始化指令序列
uint8_t CMD_Data[] = {
    OLED_CMD_DISPLAY_OFF,            // 关闭显示，确保在初始化过程中显示屏不会意外显示内容
    OLED_CMD_SET_CLOCK_DIV,          // 设置时钟分频因子，用于调整显示时钟频率
    OLED_CMD_SET_CLOCK_DIV_VALUE,    // 设置时钟分频因子的具体值，通常为0x80
    OLED_CMD_SET_MULTIPLEX,          // 设置复用率，定义显示屏的行数
    OLED_CMD_SET_MULTIPLEX_VALUE,    // 设置复用率的具体值，通常为0x3F（1/64复用率）
    OLED_CMD_SET_DISP_OFFSET,        // 设置显示偏移量，用于调整显示内容的垂直位置
    OLED_CMD_SET_DISP_OFFSET_VALUE,  // 设置显示偏移量的具体值，通常为0x00（无偏移）
    OLED_CMD_SET_START_LINE,         // 设置起始行，定义数据写入的起始行地址
    OLED_CMD_SET_SEGMENT_REMAP,      // 设置段重映射，定义列地址的映射方式
    OLED_CMD_SET_COMSCAN_DEC,        // 设置COM扫描方向为递减，定义行扫描的方向
    OLED_CMD_SET_COM_PINS,           // 设置COM引脚配置，定义COM引脚的连接方式
    OLED_CMD_SET_COM_PINS_VALUE,     // 设置COM引脚配置的具体值，通常为0x12
    OLED_CMD_SET_CONTRAST,           // 设置对比度，定义显示内容的对比度
    OLED_CMD_SET_CONTRAST_VALUE,     // 设置对比度的具体值，通常为0xCF
    OLED_CMD_SET_PRECHARGE,          // 设置预充电周期，定义预充电的时间
    OLED_CMD_SET_PRECHARGE_VALUE,    // 设置预充电周期的具体值，通常为0xF1
    OLED_CMD_SET_VCOMH,              // 设置VCOMH电平，定义VCOMH的电压水平
    OLED_CMD_SET_VCOMH_VALUE,        // 设置VCOMH电平的具体值，通常为0x40
    OLED_CMD_DISPLAY_ALL_ON_RES,     // 关闭全屏显示，确保只有特定区域显示内容
    OLED_CMD_NORMAL_DISPLAY,         // 设置正常显示模式，关闭反向显示
    OLED_CMD_CHARGE_PUMP,            // 设置电荷泵，用于生成所需的电压
    OLED_CMD_ENABLE_CHARGE_PUMP,     // 启用电荷泵，确保显示屏能够正常工作
    OLED_CMD_DISPLAY_ON              // 打开显示，使显示屏开始显示内容
};

/**
 * 写入指令函数。
 * 通过I2C接口向OLED显示屏发送指令。
 *
 * @param cmd 要发送的指令
 */
void _OLED_Write_CMD(uint8_t cmd) {
    HAL_I2C_Mem_Write(&OLED_I2C, OLED_I2C_ADDRESS, OLED_CMD_ADDRESS, I2C_MEMADD_SIZE_8BIT, &cmd, 1, OLED_I2C_TIMEOUT);
}

/**
 * 写入数据函数。
 * 通过I2C接口向OLED显示屏发送数据。
 *
 * @param data 要发送的数据
 */
void _OLED_Write_DATA(uint8_t data) {
    HAL_I2C_Mem_Write(&OLED_I2C, OLED_I2C_ADDRESS, OLED_DATA_ADDRESS, I2C_MEMADD_SIZE_8BIT, &data, 1, OLED_I2C_TIMEOUT);
}

/**
 * 打开显示。
 * 启用电荷泵并打开OLED显示屏。
 */
void _OLED_Display_On(void) {
    _OLED_Write_CMD(OLED_CMD_CHARGE_PUMP);
    _OLED_Write_CMD(OLED_CMD_ENABLE_CHARGE_PUMP);
    _OLED_Write_CMD(OLED_CMD_DISPLAY_ON);
}

/**
 * 关闭显示。
 * 关闭电荷泵并关闭OLED显示屏。
 */
void _OLED_Display_Off(void) {
    _OLED_Write_CMD(OLED_CMD_CHARGE_PUMP);
    _OLED_Write_CMD(OLED_CMD_ENABLE_CHARGE_PUMP);
    _OLED_Write_CMD(OLED_CMD_DISPLAY_OFF);
}

/**
 * 设置光标位置。
 * 设置OLED显示屏的光标位置。
 *
 * @param x 水平位置
 * @param y 垂直位置
 */
void _OLED_Set_Pos(uint8_t x, uint8_t y) {
    _OLED_Write_CMD(0xb0 + y);       // 设置页地址
    _OLED_Write_CMD(((x & 0xf0) >> 4) | 0x10); // 设置列地址高4位
    _OLED_Write_CMD(x & 0x0f);       // 设置列地址低4位
}

/**
 * 填充屏幕。
 * 填充OLED显示屏的整个屏幕。
 */
void _OLED_On(void) {
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        _OLED_Write_CMD(0xb0 + i);   // 设置页地址
        _OLED_Write_CMD(0x00);       // 设置列地址低4位
        _OLED_Write_CMD(0x10);       // 设置列地址高4位
        for (n = 0; n < 128; n++) {
            _OLED_Write_DATA(1);     // 填充数据
        }
    }
}

/**
 * 初始化OLED显示屏。
 * 发送初始化指令序列以配置OLED显示屏。
 */
void OLED_Init(void) {
    uint8_t i = 0;
    for (i = 0; i < 23; i++) {
        _OLED_Write_CMD(CMD_Data[i]); // 发送初始化指令
    }
}

/**
 * 清屏函数。
 * 清除OLED显示屏的内容。
 */
void OLED_Clear(void) {
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        _OLED_Write_CMD(0xb0 + i);   // 设置页地址
        _OLED_Write_CMD(0x00);       // 设置列地址低4位
        _OLED_Write_CMD(0x10);       // 设置列地址高4位
        for (n = 0; n < 128; n++) {
            _OLED_Write_DATA(0);     // 填充数据
        }
    }
}

/**
 * 计算幂函数。
 * 计算 m 的 n 次幂。
 *
 * @param m 底数
 * @param n 指数
 * @return 计算结果
 */
unsigned int oled_pow(uint8_t m, uint8_t n) {
    unsigned int result = 1;
    while (n--) result *= m;
    return result;
}

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
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2, uint8_t Color_Turn) {
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++) {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1)) {
            if (temp == 0) {
                OLED_ShowChar(x + (size2) * t, y, ' ', size2, Color_Turn);
                continue;
            } else enshow = 1;
        }
        OLED_ShowChar(x + (size2) * t, y, temp + '0', size2, Color_Turn);
    }
}

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
void OLED_Showdecimal(uint8_t x, uint8_t y, float num, uint8_t z_len, uint8_t f_len, uint8_t size2, uint8_t Color_Turn) {
    uint8_t t, temp, i = 0;
    uint8_t enshow;
    int z_temp, f_temp;
    if (num < 0) {
        z_len += 1;
        i = 1;
        num = -num;
    }
    z_temp = (int)num;
    // 显示整数部分
    for (t = 0; t < z_len; t++) {
        temp = (z_temp / oled_pow(10, z_len - t - 1)) % 10;
        if (enshow == 0 && t < (z_len - 1)) {
            if (temp == 0) {
                OLED_ShowChar(x + (size2) * t, y, ' ', size2, Color_Turn);
                continue;
            } else enshow = 1;
        }
        OLED_ShowChar(x + (size2) * t, y, temp + '0', size2, Color_Turn);
    }
    // 显示小数点
    OLED_ShowChar(x + (size2 ) * (z_len), y, '.', size2, Color_Turn);

    f_temp = (int)((num - z_temp) * (oled_pow(10, f_len)));
    // 显示小数部分
    for (t = 0; t < f_len; t++) {
        temp = (f_temp / oled_pow(10, f_len - t - 1)) % 10;
        OLED_ShowChar(x + (size2) * (t + z_len) + 5, y, temp + '0', size2, Color_Turn);
    }
    if (i == 1) {
        OLED_ShowChar(x, y, '-', size2, Color_Turn);
        i = 0;
    }
}

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
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t Color_Turn) {
    unsigned char c = 0, i = 0;
    c = chr - ' ';
    if (x > 128 - 1) { x = 0; y = y + 2; }
    if (Char_Size == 16) {
        _OLED_Set_Pos(x, y);
        for (i = 0; i < 8; i++) {
            if (Color_Turn) {
                _OLED_Write_DATA(~F8X16[c * 16 + i]);
            } else {
                _OLED_Write_DATA(F8X16[c * 16 + i]);
            }
        }
        _OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 8; i++) {
            if (Color_Turn) {
                _OLED_Write_DATA(~F8X16[c * 16 + i + 8]);
            } else {
                _OLED_Write_DATA(F8X16[c * 16 + i + 8]);
            }
        }
    } else {
        _OLED_Set_Pos(x, y);
        for (i = 0; i < 6; i++) {
            if (Color_Turn) {
                _OLED_Write_DATA(~F6x8[c][i]);
            } else {
                _OLED_Write_DATA(F6x8[c][i]);
            }
        }
    }
}

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
void OLED_ShowString(uint8_t x, uint8_t y, char *chr, uint8_t Char_Size, uint8_t Color_Turn) {
    uint8_t j = 0;
    while (chr[j] != '\0') {
        OLED_ShowChar(x, y, chr[j], Char_Size, Color_Turn);
        if (Char_Size == 8) {
            x += 6; // 6x8字体列加6，显示下一个字符
        } else {
            x += 8; // 8x16字体列加8，显示下一个字符
        }
        if (x > 122 && Char_Size == 12) {
            x = 0;
            y++;
        }
        if (x > 120 && Char_Size == 16) {
            x = 0;
            y++;
        }
        j++;
    }
}

/**
 * 显示汉字。
 * 在OLED显示屏上显示汉字。
 *
 * @param x 水平位置
 * @param y 垂直位置
 * @param no 汉字的索引
 * @param Color_Turn 颜色模式
 */
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no, uint8_t Color_Turn) {
    uint8_t t = 0;
    _OLED_Set_Pos(x, y);
    for (t = 0; t < 16; t++) {
        if (Color_Turn) {
            _OLED_Write_DATA(~Hzk[2 * no][t]); // 显示汉字的上半部分
        } else {
            _OLED_Write_DATA(Hzk[2 * no][t]); // 显示汉字的上半部分
        }
    }
    _OLED_Set_Pos(x, y + 1);
    for (t = 0; t < 16; t++) {
        if (Color_Turn) {
            _OLED_Write_DATA(~Hzk[2 * no + 1][t]); // 显示汉字的下半部分
        } else {
            _OLED_Write_DATA(Hzk[2 * no + 1][t]); // 显示汉字的下半部分
        }
    }
}

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
void OLED_DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t *BMP, uint8_t Color_Turn) {
    uint32_t j = 0;
    uint8_t x = 0, y = 0;

    if (y1 % 8 == 0) {
        y = y1 / 8;
    } else {
        y = y1 / 8 + 1;
    }
    for (y = y0; y < y1; y++) {
        _OLED_Set_Pos(x0, y);
        for (x = x0; x < x1; x++) {
            if (Color_Turn) {
                _OLED_Write_DATA(~BMP[j++]); // 显示反相图片
            } else {
                _OLED_Write_DATA(BMP[j++]); // 显示图片
            }
        }
    }
}

/**
 * 全屏水平滚动。
 * 设置OLED显示屏的全屏水平滚动。
 *
 * @param direction 滚动方向
 */
void OLED_HorizontalShift(uint8_t direction) {
    _OLED_Write_CMD(OLED_CMD_STOP_SCROLL); // 停止滚动
    _OLED_Write_CMD(direction); // 设置滚动方向
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_SCROLL_START_PAGE); // 设置开始页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_SPEED); // 设置滚动速度
    _OLED_Write_CMD(OLED_CMD_SCROLL_END_PAGE); // 设置结束页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE2); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_START_SCROLL); // 开启滚动
}

/**
 * 部分水平滚动。
 * 设置OLED显示屏的部分水平滚动。
 *
 * @param direction 滚动方向
 * @param start 开始页地址
 * @param end 结束页地址
 */
void OLED_Some_HorizontalShift(uint8_t direction, uint8_t start, uint8_t end) {
    _OLED_Write_CMD(OLED_CMD_STOP_SCROLL); // 停止滚动
    _OLED_Write_CMD(direction); // 设置滚动方向
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(start); // 设置开始页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_SPEED); // 设置滚动速度
    _OLED_Write_CMD(end); // 设置结束页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE2); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_START_SCROLL); // 开启滚动
}

/**
 * 垂直水平滚动。
 * 设置OLED显示屏的垂直水平滚动。
 *
 * @param direction 滚动方向
 */
void OLED_VerticalAndHorizontalShift(uint8_t direction) {
    _OLED_Write_CMD(OLED_CMD_STOP_SCROLL); // 停止滚动
    _OLED_Write_CMD(direction); // 设置滚动方向
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_SCROLL_START_PAGE); // 设置开始页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_SPEED); // 设置滚动速度
    _OLED_Write_CMD(OLED_CMD_SCROLL_END_PAGE); // 设置结束页地址
    _OLED_Write_CMD(OLED_CMD_SCROLL_OFFSET); // 垂直滚动偏移量
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_SCROLL_DUMMY_BYTE2); // 虚拟字节
    _OLED_Write_CMD(OLED_CMD_START_SCROLL); // 开启滚动
}

/**
 * 设置显示模式。
 * 设置OLED显示屏的显示模式。
 *
 * @param mode 显示模式
 */
void OLED_DisplayMode(uint8_t mode) {
    _OLED_Write_CMD(mode);
}

/**
 * 设置亮度。
 * 设置OLED显示屏的亮度。
 *
 * @param intensity 亮度值
 */
void OLED_IntensityControl(uint8_t intensity) {
    _OLED_Write_CMD(OLED_CMD_SET_CONTRAST);
    _OLED_Write_CMD(intensity);
}