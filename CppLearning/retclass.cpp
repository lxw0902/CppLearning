#include <iostream>
#include <new>


/*探索C++返回函数的情况*/

using namespace std;

class RetA
{
public:
    explicit RetA(int x = 1, int y = 1) : a(x), b(y)
    {
        string = new char[x + y];
        for (int i = 0; i < x + y; i++)
            string[i] = i + '0';

        cout << "construct:" << (long *)this << endl;
    }

    RetA(const RetA &other)
    {
        a = other.a;
        b = other.b;

        string = new char[a + b];
        for (int i = 0; i < a + b; i++)
            string[i] = other.string[i];

        cout << "copy construct: copy from " << (long *)&other << "to " << (long *)this << endl;
    }

    RetA& operator=(const RetA &other)
    {
        a = other.a;
        b = other.b;

        delete [] string;
        string = new char[a + b];
        for (int i = 0; i < a + b; i++)
            string[i] = other.string[i];

        cout << "opertor=: copy from " << (long *)&other << "to " << (long *)this << endl;
        return *this;
    }

    ~RetA() {
        delete [] string;
        cout << "destruct:" << (long *)this << endl;
    }

    void print()
    {
        cout << "print:" << (long *)this << endl;
        cout << a << b << endl;

        for (int i = 0; i < a + b; i++)
            cout << string[i];
        cout << endl;
    }

    int a;
    int b;
    char *string;
};

RetA getClass()
{
    RetA a(1,2);
    return a;
}

void ReturnClassTest()
{
    //1.
    {
        RetA b = getClass(); // 先构造getClass里面的RetA，再调用b的拷贝构造函数
        b.print();

        // 运行结果
        //construct:0022FBB4
        //copy construct: copy from 0022FBB4to 0022FBE4
        //destruct:0022FBB4
        //print:0022FBE4
        //12
        //012
        //destruct:0022FBE4
    }
    //2.
    {
        cout << endl;
        RetA b(3,4); // 先构造一个b
        b = getClass(); // 构造getClass里面的RetA，返回值给一个隐藏的RetA并调用其拷贝构造函数， 再调用b的=操作符
        b.print();

        // 运行结果
        //construct:0022FBD8
        //construct:0022FBB4
        //copy construct: copy from 0022FBB4to 0022FBCC
        //destruct:0022FBB4
        //opertor=: copy from 0022FBCCto 0022FBD8
        //destruct:0022FBCC
        //print:0022FBD8
        //12
        //012
        //destruct:0022FBD8
    }
}
