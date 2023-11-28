#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100

typedef struct SNode *PtrToSNode;
typedef double ElementType;
struct SNode
{
    char Data;
    PtrToSNode Next;
    ElementType Number;
};
typedef PtrToSNode Stack;
typedef PtrToSNode Position;

Stack Create_Stack()
{
    Stack S;
    S = (PtrToSNode)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

int Ifempty(Stack S)
{
    if (S->Next == NULL)
        return 1;
    return 0;
}

// 入栈
int Push(Stack S, char X)
{
    Position Tempcell;
    Tempcell = (Position)malloc(sizeof(struct SNode));
    Tempcell->Next = S->Next;
    S->Next = Tempcell; // 新元素永远在头节点S的后面
    Tempcell->Data = X;
    return 1;
}

// 出栈  头节点之后的那个就是栈顶
char Pop(Stack S)
{
    if (Ifempty(S) == 1)
    {
        printf("栈空");
        return 'x';
    }
    else
    {
        Position First;
        First = S->Next;
        S->Next = First->Next;
        return First->Data;
    }
}

// 栈顶元素
char Tops(Stack S)
{
    if (Ifempty(S) == 1)
    {
        return 'x';
    }
    else
    {
        Position First;
        First = S->Next;
        char temp = First->Data; // 存储数据到临时变量
        return temp;             // 返回临时变量的值
    }
}

double Push_double(Stack S, ElementType X)
{
    Position Tempcell;
    Tempcell = (Position)malloc(sizeof(struct SNode));
    Tempcell->Next = S->Next;
    S->Next = Tempcell; // 新元素永远在头节点S的后面
    Tempcell->Number = X;
    return 1;
}

double Pop_double(Stack S)
{
    if (Ifempty(S) == 1)
    {
        printf("栈空");
        return -1;
    }
    else
    {
        Position First;
        First = S->Next;
        S->Next = First->Next;
        return First->Number;
    }
}

// 逆转元素
Stack Reverse(Stack S)
{
    Position head = S, p = S->Next, q = p->Next, r = q->Next;
    p->Next = NULL;
    while (q->Next != NULL)
    {
        q->Next = p;
        p = q;
        q = r;
        r = r->Next;
    }
    q->Next = p;
    head->Next = q;
    return head;
}

void adding(Stack S1, Stack S2)
{
    if (Tops(S1) == 'x' || Tops(S1) == '(') // 除了空或者(
    {
        Push(S1, '+');
        Push(S1, ' ');
    }
    else
    {
        Push(S2, Pop(S1));
        adding(S1, S2);
    }
}

void minusing(Stack S1, Stack S2)
{
    if (Tops(S1) == 'x' || Tops(S1) == '(')
    {
        Push(S1, '-');
        Push(S1, ' ');
    }
    else
    {
        Push(S2, Pop(S1));
        minusing(S1, S2);
    }
}

void multiplying(Stack S1, Stack S2)
{
    if (Tops(S1) == 'x' || Tops(S1) == '(' || Tops(S1) == '+' || Tops(S1) == '-')
    {
        Push(S1, '*');
        Push(S1, ' ');
    }
    else
    {
        Push(S2, Pop(S1));
        multiplying(S1, S2);
    }
}

void dividing(Stack S1, Stack S2)
{
    if (Tops(S1) == 'x' || Tops(S1) == '(' || Tops(S1) == '+' || Tops(S1) == '-')
    {
        Push(S1, '/');
        Push(S1, ' ');
    }
    else
    {
        Push(S2, Pop(S1));
        dividing(S1, S2);
    }
}

Stack Transferring(Stack S1, Stack S2)
{
    char str[100] = {'0'};
    // 输入中缀
    printf("输入中缀表达式:");
    gets(str);
    int len = strlen(str);
    for (int j = 0; j < len; j++)
    {
        if (isdigit(str[j]))
        {
            Push(S2, str[j]);
        }
        else if (str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/' || str[j] == '(' || str[j] == ')')
        {
            switch (str[j])
            {
            case '+':
            {
                Push(S2, ' ');
                adding(S1, S2);
                break;
            }
            case '-':
            {
                Push(S2, ' ');
                minusing(S1, S2);
                break;
            }
            case '*':
            {
                Push(S2, ' ');
                multiplying(S1, S2);
                break;
            }
            case '/':
            {
                Push(S2, ' ');
                dividing(S1, S2);
                break;
            }
            case '(':
            {
                Push(S1, '(');
                break;
            }
            case ')':
            {
                while (Tops(S1) != '(')
                {
                    Push(S2, Pop(S1));
                }
                Pop(S1);
                break;
            }
            }
        }
        else
        {
            Push(S2, str[j]);
        }
    }
    while (Tops(S1) != 'x')
    {
        Push(S2, Pop(S1));
    }
    Reverse(S2);
    return S2;
}

// 用于测试后缀表达式转化
int Debug()
{
    Stack S1 = Create_Stack();
    Stack S2 = Create_Stack();
    S2 = Transferring(S1, S2);
    while (Tops(S2) != 'x')
    {
        printf("%c", Pop(S2));
    }
    return 0;
}

// 以上为栈的定义与基本功能以及中缀转后缀的内容，
// 接下来是读取后缀并计算

size_t str_length(char *str)
{
    size_t length = 0;
    while (*str != '\0' && *str != ' ')
    {
        length++;
        str++;
    }
    return length;
}

double evaluatePostfix(char *exp)
{
    Stack S0 = Create_Stack();
    int i = 0;
    char *p = exp;
    while (*p != '\0')
    {
        if (isdigit(*p))
        {
            Push_double(S0, atof(p));
            p+=str_length(p)+1;
        }
        else if (*p == ' ')
        {
            // 跳过空格
            p++;
        }
        else
        {
            double operand2 = Pop_double(S0);
            double operand1 = Pop_double(S0);
            switch (*p)
            {
            case '+':
                Push_double(S0, operand1 + operand2);
                break;
            case '-':
                Push_double(S0, operand1 - operand2);
                break;
            case '*':
                Push_double(S0, operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("除零错误\n");
                    exit(1);
                }
                Push_double(S0, operand1 / operand2);
                break;
            default:
                printf("无效操作符\n");
                exit(1);
            }
            p++;
        }
    }
    return Pop_double(S0);
}

int main()
{
    char Expr[MAXOP];
    int num;
    Stack S1 = Create_Stack();
    Stack S2 = Create_Stack();
    S2 = Transferring(S1, S2);
    for (int i = 0; Tops(S2) != 'x'; i++)
    {
        Expr[i] = Pop(S2);
        num = i;
    }
    Expr[num + 1] = '\0';
    double result = evaluatePostfix(Expr);
    printf("后缀表达式的计算结果为：%lf\n", result);
    // return 0;
    // Debug();
    return 0;
}