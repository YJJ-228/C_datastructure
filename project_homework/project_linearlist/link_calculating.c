//说明：读取多项式的时候时间复杂度是O(n),乘法函数时间复杂度是O(n^2),总体时间复杂度是O(n^2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct LNode *PtrTolNode;
struct LNode
{
    int coef;
    int expon; 
    PtrTolNode next;
};
typedef PtrTolNode Polynomial; //Polynomial为节点地址

void Attach(int coef, int expon, Polynomial *PtrRear)//*PtrRear 指向尾项
{
	Polynomial P;
	P=(Polynomial)malloc(sizeof(struct LNode));
	P->coef=coef;
	P->expon=expon;
	P->next=NULL;
	if (*PtrRear == NULL)
    {
        // 如果链表为空，将 *PtrRear 直接指向新的节点 P
        *PtrRear = P;
    }
	else
	{
		(*PtrRear)->next=P;
		*PtrRear=P;    //存完新的数据后，保证P是尾部节点。
	}
}

Polynomial PolyMultiply(Polynomial P1, Polynomial P2)
{
	Polynomial P2_head=P2;
    Polynomial rear, tmp,front;
    rear = (Polynomial)malloc(sizeof(struct LNode));
    front = rear;
    while (P1)
    {
        while (P2)
        {
            int coef = (P1->coef) * (P2->coef);
            int expon = P1->expon + P2->expon;
            Attach(coef,expon, &rear);
            P2 = P2->next;
        }
        P1 = P1->next;
        P2 = P2_head; // 重置P2为第二个多项式的头节点
    }
    rear->next = NULL;
    tmp = front;
    front = front->next;
    free(tmp);  // 释放掉多余的头节点
    return front;
}

Polynomial cin_lnode()
{
    int K;int coef, expon;
    Polynomial head = NULL; // 初始时链表为空
    Polynomial rear = NULL;
    printf("请输入共有几项：");
    scanf("%d", &K);
    printf("请依次输入系数和指数：\n");
    for (int i = 1; i <= K; i++)
    {
        scanf("%d %d", &coef, &expon);
        Attach(coef, expon, &rear);
        if (head == NULL)
        {
            head = rear; // 如果链表为空，将头指针指向第一个节点
        }
    }
    return head;
}

int max(int a,int b)
{
    if(a>b)return a;
    else  return b;
}

void cout_lnode(Polynomial P)
{
	int a[1000]={0};
	int num=0;
	while(P!=NULL)
	{
		if(a[P->expon]==0)
		{
			a[P->expon]=P->coef;       //利用桶的结构进行同次数的系数加和
			num=max(num,P->expon);
		}
		else
		{
			a[P->expon]+=P->coef;
		}
		P=P->next;
	}
	for(int i=num;i>=0;i--)
	{
		if(a[i]==0)continue;
		printf("%dx^%d ",a[i],i);
	}
}

int main()
{
	Polynomial P1=cin_lnode();
	Polynomial P2=cin_lnode();
	Polynomial P3=PolyMultiply(P1,P2);
	cout_lnode(P3);
	return 0;
}