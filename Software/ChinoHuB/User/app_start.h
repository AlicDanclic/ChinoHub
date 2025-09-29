#ifndef __APP_START_H__
#define __APP_START_H__

#include "main.h"
#include "usart.h"
#include "Binary_Hex_Macros.h"
#include "delay.h"
#include "oled.h"

typedef enum{

}LoopStatus;

static LoopStatus Status;
void init(void);
void loop(void);


#endif //__APP_START_H__