
/*-------------------------------------------------------------------------
 * Name:   哈夫曼编码源代码。
 * Date:   2011.04.16
 * Author: Jeffrey Hill+Jezze(解码部分)
 * 在 Win-TC 下测试通过
 * 实现过程：着先通过 HuffmanTree() 函数构造哈夫曼树，然后在主函数 main()中
 *           自底向上开始(也就是从数组序号为零的结点开始)向上层层判断，若在
 *           父结点左侧，则置码为 0,若在右侧,则置码为 1。最后输出生成的编码。
 *------------------------------------------------------------------------*/
#ifndef _HUFFMANTREE_H
#define _HUFFMANTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBIT      100
#define MAXVALUE  10000
#define MAXLEAF     30
#define MAXNODE    MAXLEAF*2 -1

typedef struct
{
    int bit[MAXBIT];
    int start;
} HCodeType;        /* 编码结构体 */
typedef struct
{
    int weight;
    int parent;
    int lchild;
    int rchild;
    int value;
} HNodeType;        /* 结点结构体 */

/* 构造一颗哈夫曼树 */
void HuffmanTree (HNodeType HuffNode[MAXNODE],  int n);

//解码
void decodeing(char string[],HNodeType Buf[],int Num);

void HuffmanTreeTest(void);

#endif
