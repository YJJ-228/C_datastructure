#include <stdio.h>
#include <stdlib.h>

void get_father_node(int i, int j)
{
    if (i == j)
    {
        printf("%d", i);
        return;
    }
    else if (i > j)
        get_father_node(i / 2, j);
    else if (j > i)
        get_father_node(i, j / 2);
}

int main()
{
    int i, j;
    printf("请输入i和j:");
    scanf("%d %d", &i, &j);
    get_father_node(i, j);
    return 0;
}