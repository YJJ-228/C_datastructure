#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char middle_tree[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
char post_tree[] = {'D', 'E', 'B', 'F', 'G', 'C', 'A'};

// 树
typedef char ElementType;
typedef struct TNode *BinTree; /* 二叉树类型 */
struct TNode
{					  /* 树结点定义 */
	ElementType Data; /* 结点数据 */
	BinTree Left;	  /* 指向左子树 */
	BinTree Right;	  /* 指向右子树 */
};

void checking_search()
{
    char *p=middle_tree;
    while (p!=NULL)
    {
        if(*p>*(p+1))
        {
            printf("\n不是二叉搜索树\n");
            return;
        }
        p++;
    }
    printf("\n是二叉搜索树\n");
    return;
}

int find_index(char str[], int start, int end, char ch)
{
    for (int i = start; i <= end; i++)
    {
        if (str[i] == ch)
            return i;
    }
    return -1;
}

void tree_change(int ml, int mr, int pl, int pr)
{
    if (ml > mr)
        return;
    printf("%c", post_tree[pr]);
    // 根结点
    int middle_root_index = find_index(middle_tree, ml, mr, post_tree[pr]);
    // 处理左子树
    tree_change(ml, middle_root_index - 1, pl, pl + middle_root_index - 1 - ml);
    // 处理右子树
    tree_change(middle_root_index + 1, mr, pl + middle_root_index - 1 - ml + 1, pr - 1); // 利用子树聚集在一起且和相同的特性
}

int main()
{
    int len = sizeof(middle_tree);
    tree_change(0, len - 1, 0, len - 1);
    checking_search();
    return 0;
}