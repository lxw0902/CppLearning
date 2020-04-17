#ifndef ARMNEONTEST_H
#define ARMNEONTEST_H

/* arm neno 汇编功能测试
 */


#include <qglobal.h>



#if defined (Q_WS_QWS)
#include <arm_neon.h>
#include <stdio.h>

int ArmAsmTest(int x, int y)
{
    int a = x;
    int b = y;
    int ret = 0;

    __asm__
    __volatile__ ("add %1, %0;"
                  :"=r"(a)
                  :"r"(b));
    return ret;
}

#endif

#endif // ARMNEONTEST_H
