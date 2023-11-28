#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
typedef int ElementType;
typedef  struct GNode *PtrToGNode;
typedef  PtrToGNode GList;
struct  GNode {
    int Tag; /* 标志域：0表示该结点是单元素；1表示该结点是广义表 */
    union 
    {  /* 子表指针域Sublist与单元素数据域Data复用，即共用存储空间 */
	    ElementType Data;
	    GList    Sublist;
    } URegion;
    PtrToGNode Next; /* 指向后继结点 */
};




typedef enum {Head, Term} NodeTag;
struct TermNode 
{ /* 非零元素结点 */
	int Row, Col;
	ElementType Value;
};

typedef struct MNode *PtrToMNode;
struct MNode { /* 矩阵结点定义 */
	PtrToMNode  Down, Right;
	NodeTag  Tag;
	union { /* Head对应Next指针；Term对应非零元素结点 */
		PtrToMNode  Next;
		struct  TermNode  Term;
	} URegion;
};
typedef   PtrToMNode  Matrix; /* 稀疏矩阵类型定义 */
Matrix   HeadNode [MAXSIZE]; /* MAXSIZE是矩阵最大非0元素个数 */
