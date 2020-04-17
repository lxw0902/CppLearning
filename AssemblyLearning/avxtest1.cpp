// avxtest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int supports_AVX()
{   
	_asm{
		mov eax, 1;
		cpuid;
		and ecx, 018000000H;
		cmp ecx, 018000000H;    check both OSXSAVE and AVX feature flags
		jne not_supported;      processor supports AVX instructions and XGETBV is enabled by OS
		mov ecx, 0;             specify 0 for XCR0 register
		XGETBV ;                result in EDX:EAX
		and eax, 06H;
		cmp eax, 06H;           check OS has enabled both XMM and YMM state support
		jne not_supported;
		mov eax, 1;
		jmp done;
NOT_SUPPORTED:
		mov eax, 0;
done:
	}
}

void AVXTEST1()
{
	int x = 0;
	int y = 1;
	int c = 0;
	int d = 0;

	c = (x == 1);

	for (int i = 0; i < 128; i++)
		d++;

	_asm{
		xor eax, eax;
		XGETBV;
		mov dword ptr [x], eax;

		cmp dword ptr [y], 0;
		sete al;
		mov dword ptr [c], eax;
	}

	printf("x=%d y=%d c=%d d=%d\n", x, y, c, d);
	printf("cpu%s supports avx\n", supports_AVX() ? "" : " not");
}

