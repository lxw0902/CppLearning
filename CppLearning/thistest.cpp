// thistest.cpp : Defines the entry point for the console application.
//

/*探头c++ this指针是如何传入函数内部， 并用C语言方式调用C++虚函数*/

#include <iostream>

class A
{
public:
    int p;

    virtual int add(int x, int y)
    {
        return x + y + p;
    }
};


class B
{
public:
    int p;

    int add(const int &x, int y)
    {
        return x + y + p;
    }
};


typedef int (*func)(int, int);

void ThisTest()
{
    A a;
    B b;
    a.p = 13;
    b.p = 14;

    int *vptr = (int *)(*(int *)(&a));
    func fadd = (func)(vptr[0]);
    int s1 = 0;
    int s2 = 0;

    // msvc里面this指针是赋值给ecx的方式传入
    // gcc里面this指针是作为函数的第一个参数传入的
    _asm
    {
        lea ecx,[a]
    }
     s2 = fadd(2,3);
    s1 = b.add(2, 3);

    printf ("add:%d--%d\n", s1, s2);
}

