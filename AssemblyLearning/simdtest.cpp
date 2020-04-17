// simdtest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <intrin.h>
#include <mmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>

void SIMDTEST()
{
	float p = 136.65f;
	float q = 153.34f;
	float a[] = {3.2f,5.2f,6.2f,1.62f,0.52f,1.2f,10.2f,9.2f};
	float b[] = {1.2f,2.2f,3.2f,4.2f,5.2f,6.2f,7.2f,8.2f};
	
	//a[0] = p + q;

	// 方式一
    //__m256 x = _mm256_setr_ps(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    //__m256 y = _mm256_setr_ps(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]); 
    //__m256 z = _mm256_add_ps(x, y);
    //float* pi  = (float*)(&z);

	// 方式二 (推荐)
	float pi[8],pj[8],pk[8],pn[8];
	__m256 x = _mm256_loadu_ps(a);
	__m256 y = _mm256_loadu_ps(b);
	__m256 z = _mm256_mul_ps(x, y);
	__m256 mh = _mm256_movehdup_ps(x);
	__m256 ml = _mm256_moveldup_ps(x);
	_mm256_storeu_ps(pi, z);
	_mm256_storeu_ps(pj, mh); 
	_mm256_storeu_ps(pk, ml);

	for (int i = 0; i < 8; i++)
		printf("sum[%d]=%f\n", i, *(pi+i));

	for (int i = 0; i < 8; i++)
		printf("movup[%d]=%f\n", i, *(pj+i));
	
	for (int i = 0; i < 8; i++)
		printf("movld[%d]=%f\n", i, *(pk+i));
	
	for (int i = 0; i < 8; i++)
		pn[i] = a[i] + b[i];
}
