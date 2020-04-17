// 利用二值化函数测试，分别用C语言，intrin函数库，AVX纯汇编的方式查看效率
//

#include <stdio.h>
#include <intrin.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack (push)
#pragma pack (16)

#define THRESHOLD 127

uint64_t get_time_stamp();
 
void threshold(uint8_t *pb_src, uint8_t *pb_mask, int num_pixels)
{
	for (int i = 0; i < num_pixels; i++)
		*pb_mask++ = (*pb_src++ > THRESHOLD) ? 0xff : 0x00;
}

void threshold_sse(uint8_t *pb_src, uint8_t *pb_mask, int num_pixels)
{
	__m128i pithreshold, piscale, pimask, pipixels;
	//pimask = _mm_cvtsi32_si128(0x00);

	pimask = _mm_set_epi8(0x01, 0x02, 0x03, 0x04, 
		0x05, 0x06, 0x07, 0x08,
		0x09, 0x0a, 0x0b, 0x0c, 
		0x0d, 0x0e, 0x0f, 0x00);
    piscale = _mm_cvtsi32_si128(0x80);
    piscale = _mm_shuffle_epi8(piscale, pimask);
 
    pithreshold = _mm_cvtsi32_si128(THRESHOLD);
    pithreshold = _mm_shuffle_epi8(pithreshold, pimask);
    pithreshold = _mm_sub_epi8(pithreshold, piscale);
 

	for (int i = 0; i < num_pixels; i += 16)
    {
        pipixels = *(__m128i*)(pb_src+i);
        pipixels = _mm_sub_epi8(pipixels, piscale);
        *((__m128i*)(pb_mask+i)) = _mm_cmpgt_epi8(pipixels, pithreshold);
    }
}

extern "C" void threshod_sse_asm(uint8_t *pb_src, uint8_t *pb_mask, int num_pixels);

#define TEST_COUNT  1024*1024*100

void SSETEST()
{
	uint8_t *psrc = new uint8_t[TEST_COUNT];
	uint8_t *psrc1 = new uint8_t[TEST_COUNT];
	uint8_t *pmask = new uint8_t[TEST_COUNT];
	uint8_t *pmask1 = new uint8_t[TEST_COUNT];
	unsigned long long t1, t2;

	srand(100);
	for (int i = 0; i < TEST_COUNT; i++)
	{
		pmask[i] = 0;
		pmask1[i] = pmask[i];
		psrc[i] = rand() % 256;
		psrc1[i] = psrc[i];
	}

	t1 = get_time_stamp();
	threshold(psrc, pmask, TEST_COUNT);
	t2 = get_time_stamp();
	printf ("threshold time is: %d \n", t2 - t1);

	t1 = get_time_stamp();
	threshold_sse(psrc1, pmask1, TEST_COUNT);
	t2 = get_time_stamp();
	printf ("threshold sse time is: %d \n", t2 - t1);
}

#pragma pack(pop)