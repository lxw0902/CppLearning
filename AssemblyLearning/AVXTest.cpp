// bintest.cpp : Defines the entry point for the console application.
//
// saxpytest.cpp : Defines the entry point for the console application.
//

//#include "avxintrin_emu.h"  
#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <random>

uint64_t get_time_stamp();

// C语言二值化运算
void bin(uint8_t* pb_src, uint8_t* pb_mask, int threshold, int num_pixels)
{
	for (int i = 0; i < num_pixels; i++)
		*pb_mask++ = (*pb_src++ > threshold) ? 0xff : 0x00;
}

// 利用AVX库的二值化运算
void bin_avx(uint8_t* pb_src, uint8_t* pb_mask, int threshold, int num_pixels)
{
	__m128i pimask = _mm_cvtsi32_si128(0);
	__m128i pipixels = _mm_cvtsi32_si128(0);
    __m128i piscale = _mm_cvtsi32_si128(0x80);
    piscale = _mm_shuffle_epi8(piscale, pimask);
 
    __m128i pithreshold = _mm_cvtsi32_si128(threshold);
    pithreshold = _mm_shuffle_epi8(pithreshold, pimask);
    pithreshold = _mm_sub_epi8(pithreshold, piscale);
 
    for (int i = 0; i < num_pixels; i += 16)
    {
        pipixels = *(__m128i*)(pb_src+i);
        pipixels = _mm_sub_epi8(pipixels, piscale);
        *((__m128i*)(pb_mask+i)) = _mm_cmpgt_epi8(pipixels, pithreshold);
    }
}

// 运用汇编和AVX指令集的二值化运算
/*void bin_asm()
{
    __asm{
        ; Initialize packed threshold
        movzx eax,byte ptr [edx+ITD.Threshold]  ;eax = threshold
        movd xmm1,eax                           ;xmm1[7:0] = threshold
        pxor xmm0,xmm0                          ;mask for pshufb
        pshufb xmm1,xmm0                        ;xmm1 = packed threshold
        movdqa xmm2,xmmword ptr [PixelScale]
        psubb xmm1,xmm2                         ;xmm1 = scaled threshold

; Create the mask image
@@:     movdqa xmm0,[esi]                   ;load next packed pixel
        psubb xmm0,xmm2                     ;xmm0 = scaled image pixels
        pcmpgtb xmm0,xmm1                   ;compare against threshold
        movdqa [edi],xmm0                   ;save packed threshold mask
        add esi,16
        add edi,16
        dec ecx
        jnz @B                              ;repeat until done
    }
}*/

#define TEST_SIZE	1024*1024*32


void AVXTEST()
{
	uint64_t start_time;
	uint64_t end_time;
	uint8_t *x = new uint8_t[TEST_SIZE],
		*y = new uint8_t[TEST_SIZE],
		*x1 = new uint8_t[TEST_SIZE],
		*y1 = new uint8_t[TEST_SIZE];
	int a = 127;
	srand(a);
	for (int i = 0; i < TEST_SIZE; i++)
	{
		x[i] = (char)(rand() % 256);
		x1[i] = x[i];
		y[i] = 0;
		y1[i] = y[i];
	}

	{
		start_time = get_time_stamp();
		bin(x, y, a, TEST_SIZE); 
		end_time = get_time_stamp();
		printf ("normal time: %ld\n", end_time - start_time);
	}

	{
		start_time = get_time_stamp();
		bin_avx(x1, y1, a, TEST_SIZE); 
		end_time = get_time_stamp();
		printf ("avx time: %ld\n", end_time - start_time);
	}
}

/////////////////////////
//加速效果还行           //
/////////////////////////

