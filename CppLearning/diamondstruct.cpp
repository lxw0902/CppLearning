#include <stdio.h>

/*C++钻石结构测试， 继承关系如下图，虚继承的A只构造了一次
        A
      /   \
      X   Y
       \ /
        P
*/

class A
{
public:
    A(int v = 0) : x(v) {
        printf("in A: x is %d\n", x);
    }

    int x;
};

class X : virtual public A
{
public:
    X() : A(1) {
        printf("in X: x is %d\n", x);
    }

    int getData1() {return x;}
};

class Y : virtual public A
{
public:
    Y() : A(2) {
        printf("in Y: x is %d\n", x);
    }

    int getData2() {return x;}
};

class P : public X, public Y
{
public:
    P() : X(), Y(),  A(123) {
        printf("in P: x is %d\n", x);
    }
};


void DiamondStructTEST()
{
    P z;

    z.getData1();
}
