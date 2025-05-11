// simple_log.h
#pragma once

#include "main.h"  // 根据你的芯片修改
#include <stdio.h>
#include <string.h>


// 定义日志级别
typedef enum {
    LOG_ERROR = 0,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;


#include "stdio.h"
#include "usart.h"

// 重写_write函数


#define DEBUE //串口输出开关,注释掉此定义就可关闭串口打印

#ifdef DEBUG
#define LOG_I(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define LOG_I(fmt, ...)  // 空定义，忽略调试信息
#endif


// 初始化日志系统
void log_init(UART_HandleTypeDef *huart);

// 基础日志函数
void log_print(LogLevel level, const char *format, ...);

// 便捷宏
#define LOG_E(fmt, ...) log_print(LOG_ERROR, "[E]" fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) log_print(LOG_WARNING, "[W]" fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...) log_print(LOG_INFO, "[I]" fmt, ##__VA_ARGS__)
#define LOG_D(fmt, ...) log_print(LOG_DEBUG, "[D]" fmt, ##__VA_ARGS__)
