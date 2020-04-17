// saxpytest.cpp : Defines the entry point for the console application.
//

//#include "avxintrin_emu.h"  
#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

uint64_t get_time_stamp();

void saxpy(float a, float* x,float* y, float* __restrict z, int n)
{
	int i;
	for(i =0; i < n;++i)
		z[i] = y[i] + a * x[i];
}

void saxpy_avx(float a, const float* x, const float* y, float* __restrict z, int len)
{
    int i = 0;
    __m256 a_ = _mm256_set1_ps(a);

    for (int len16_ = len & -16; i + 16 <= len16_; i += 16)
    {
        __m256 x1_ = _mm256_loadu_ps(x + i);
        __m256 x2_ = _mm256_loadu_ps(x + i + 8);

        __m256 y1_ = _mm256_loadu_ps(y + i);
        __m256 y2_ = _mm256_loadu_ps(y + i + 8);

        x1_ = _mm256_mul_ps(x1_, a_);
        x2_ = _mm256_mul_ps(x2_, a_);

        x1_ = _mm256_add_ps(x1_, y1_);
        x2_ = _mm256_add_ps(x2_, y2_);

        _mm256_storeu_ps(z + i, x1_);
        _mm256_storeu_ps(z + i + 8, x2_);
    }
}

#define TEST_SIZE	1024*1024*32


void SAXPYTEST()
{
	uint64_t start_time;
	uint64_t end_time;
	float *x = new float[TEST_SIZE],
		*y = new float[TEST_SIZE],
		*z = new float[TEST_SIZE];
	float a = 1.2f;
	for (int i = 0; i < TEST_SIZE; i++)
	{
			x[i] = 1.1f + i;
			y[i] = 1.2f * i;
			z[i] = 0.0f;
	}

	{
		start_time = get_time_stamp();
		saxpy(a, x, y, z, TEST_SIZE); 
		end_time = get_time_stamp();
		printf ("normal time: %ld\n", end_time - start_time);
		
		for (int i = 0; i < 32; i++)
			printf("z[%d] = %f\n",i , z[i]);
		printf("...\n\n");
	}

	{
		start_time = get_time_stamp();
		saxpy_avx(a, x, y, z, TEST_SIZE); 
		end_time = get_time_stamp();
		printf (" speed time: %ld\n", end_time - start_time);
		for (int i = 0; i < 32; i++)
			printf("z[%d] = %f\n",i , z[i]);
		printf("...\n\n");
	}
}


/////////////////////////
//测试结果，没有看到加速效果//
/////////////////////////
