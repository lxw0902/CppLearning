#include <iostream>
#include <new>

using namespace std;

void nomorememory()
{
    cerr << "unable to satisfy request for memory\n";
    abort();
}

void NewExceptionTest()
{
    set_new_handler(nomorememory);

    int *w;
    for (int i =0;i<10;i++)
        w = new int[0x7ffffff];
    w[0] = 1;
    cout << w[0] << endl;
}
