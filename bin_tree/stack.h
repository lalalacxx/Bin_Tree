#pragma once 

struct TreeNode;
typedef struct TreeNode* DataType;
typedef struct Stack
{
    DataType *data;
    //有效元素个数
    int size;
    //表示data段内存中能容纳的元素个数
    int capacity;
}Stack;
//栈初始化                                                              
void StackInit(Stack *stack);                                            
//栈销毁函数                                                            
void StackDestroy(Stack *stack);                                         
//入栈操作                                                              
void StackPush(Stack *stack,DataType value);                             
//出栈操作                                                              
void StackPop(Stack *stack);                                             
//取栈顶元素函数                                                        
int StackGetTop(Stack *stack,DataType *value);                           
