#include "ase.h"
#include "KalmanFilterTest.h"
#include "HuffmanTreeTest.h"
#include "GSLTest.h"
#include "bpnettest.h"

int main(int argc, char *argv[])
{
    // BP神经网络测试
    BPTest();

    // GSL 测试
    GSLTest();

    // 卡夫曼滤波器测试
    KalmanFiterTest();

    // 霍夫曼树测试
    HuffmanTreeTest();

    // ASE加密算法测试
    AESTest();

    return 0;
}
