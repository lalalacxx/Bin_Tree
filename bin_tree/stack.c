#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//栈初始化
void StackInit(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (DataType*)malloc(stack->capacity * sizeof(DataType));
}
//栈销毁函数
void StackDestroy(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}
//入栈操作
void StackPush(Stack *stack,DataType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size >= stack->capacity)
    {
        //栈满了
        return;
    }
    //栈没满
    stack->data[stack->size++] = value;
}
//出栈操作
void StackPop(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空栈
        return;
    }
    stack->size--;
}
//取栈顶元素函数
int StackGetTop(Stack *stack,DataType *value)
{
    if(stack == NULL)
    {
        //非法输入
        return 0;
    }
    if(stack->size == 0)
    {
        //空栈
        return 0;
    }
    *value = stack->data[stack->size-1];
    return 1;
}

void Print2(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size == 0)
    {
        //空栈
        return;
    }
    int i = 0;
    for(;i < stack->size;i++)
    {
        printf("%p ",stack->data[i]);
    }
    printf("\n\n");
}



