#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef void * ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Maxn(int a, int b)
{
    return a > b ? a : b;
}

AVLTree Insert(AVLTree T,ElementType X)
{

}