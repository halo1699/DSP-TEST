#include "arm_math.h"
#include "com_log.h"
#include "com_dsp.h"

#if defined(SEMIHOSTING)
#include <stdio.h>
#endif

#define TEST_LENGTH_SAMPLES 2048

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES / 2];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
arm_cfft_instance_f32 varInstCfftF32;

/* Reference index at which max energy of bin occurs */
uint32_t refIndex = 213, testIndex = 0;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */

void dsp_test(void)
{
    arm_status status;
    float32_t maxValue;

    status = ARM_MATH_SUCCESS;

    // 初始化 CFFT
    status = arm_cfft_init_f32(&varInstCfftF32, fftSize);

    if (status != ARM_MATH_SUCCESS)
    {
        printf("CFFT Initialization failed.\n");
        return;
    }

    // 打印输入数据 (testInput_f32_10khz)
    printf("Input Data (testInput_f32_10khz):\n");
    for (int i = 0; i < TEST_LENGTH_SAMPLES; i += 2) {
        printf("testInput_f32_10khz[%d] = %.8f + %.8fi\n", i, testInput_f32_10khz[i], testInput_f32_10khz[i + 1]);
    }

    // 进行 CFFT 变换
    arm_cfft_f32(&varInstCfftF32, testInput_f32_10khz, ifftFlag, doBitReverse);

    // 打印 CFFT 输出 (testInput_f32_10khz)
    printf("CFFT Output (testInput_f32_10khz):\n");
    for (int i = 0; i < TEST_LENGTH_SAMPLES; i += 2) {
        printf("testInput_f32_10khz[%d] = %.8f + %.8fi\n", i, testInput_f32_10khz[i], testInput_f32_10khz[i + 1]);
    }

    // 计算复数幅度
    arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);

    // 查找最大幅值和对应的频率 bin
    arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

    // 对比参考值，并设置测试状态
    status = (testIndex != refIndex) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

    // 打印出最大幅值和对应的频率 bin
    printf("Max Value: %.8f\n", maxValue);
    printf("Frequency Bin: %d\n", testIndex);

    // 打印测试结果
    if (status != ARM_MATH_SUCCESS)
    {
        printf("FAILURE\n");
    }
    else
    {
        printf("SUCCESS\n");
    }
}
