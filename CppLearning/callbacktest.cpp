#ifndef CALLBACKTEST_H
#define CALLBACKTEST_H

#include <iostream>

using namespace std;

// C++回调测试 -- mingw 能够使用， vs2010不能
#ifdef __cplusplus
extern "C" {
typedef void (__stdcall *FUNC)(void *);
}
#endif
class B
{
public:
    void run(FUNC func, void *param)
    {
        func(param);
    }
};


class A
{
public:
    void print()
    {
        cout << i << endl;
    }

    void test()
    {
        i = 123;
        cout << "test start" << endl;
        print();

        union {
            void (__stdcall *func)(void *);
            void (A::*print)();
        }p_conv;

        p_conv.print = &A::print;

        b.run(p_conv.func, this);
    }

    int i;
    B b;
};

#endif // CALLBACKTEST_H
