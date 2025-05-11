// simple_log.c
#include "com_log.h"
#include <stdarg.h>

// #define RTOS 1

#ifdef RTOS
#include "cmsis_os.h"
#endif

static UART_HandleTypeDef *log_huart = NULL;

#ifdef RTOS
extern osMutexId_t TxMutexHandle;
#endif

void log_init(UART_HandleTypeDef *huart) {
    log_huart = huart;
}

void log_print(LogLevel level, const char *format, ...) {
    char buf[20];
    va_list args;
    va_start(args, format);

    // 格式化日志内容
    int len = vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    // 添加换行符
    if (len < sizeof(buf) - 2) {
        strcat(buf, "\r\n");
    }

    // 选择颜色：ANSI 转义序列
    const char *color_start = "";
    const char *color_end = "\x1b[0m";  // 默认重置颜色

    switch (level) {
        case LOG_DEBUG:
            color_start = "\x1b[34m";  // 蓝色
            break;
        case LOG_INFO:
            color_start = "\x1b[32m";  // 绿色
            break;
        case LOG_WARNING:
            color_start = "\x1b[33m";  // 黄色
            break;
        case LOG_ERROR:
            color_start = "\x1b[31m";  // 红色
            break;
        default:
            color_start = "\x1b[37m";  // 白色（默认）
            break;
    }

    // 输出到串口
    if (log_huart) {
#ifdef RTOS
        if (osMutexAcquire(TxMutexHandle, 100) == osOK) {
            HAL_UART_Transmit(log_huart, (uint8_t *)color_start, strlen(color_start), 100);
            HAL_UART_Transmit(log_huart, (uint8_t *)buf, strlen(buf), 100);
            HAL_UART_Transmit(log_huart, (uint8_t *)color_end, strlen(color_end), 100);
            osMutexRelease(TxMutexHandle);
        }
#else
        HAL_UART_Transmit(log_huart, (uint8_t *)color_start, strlen(color_start), 100);
        HAL_UART_Transmit(log_huart, (uint8_t *)buf, strlen(buf), 100);
        HAL_UART_Transmit(log_huart, (uint8_t *)color_end, strlen(color_end), 100);
#endif
    }
}
