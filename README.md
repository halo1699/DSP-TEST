# 介绍
- 本代码使用串口打印生成的浮点数
- 最主要的是CMAKE要添加一个选项：set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections -u_printf_float")。这样才能正确台南佳浮点数