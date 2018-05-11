#pragma once


#define max_size  1000

struct TreeNode;
typedef struct TreeNode* DataType;

typedef struct Queue
{
    DataType data[max_size];
    int head;
    int tail;
    int size;
}Queue;

//队列初始化函数                                  
void QueueInit(Queue *queue);                  
//队列销毁函数                                    
void QueueDestroy(Queue *queue);      
//入队列操作函数                                  
void QueuePush(Queue *queue,DataType value);       
//出队列操作函数                                  
void QueuePop(Queue *queue);    
//取队首元素函数                                  
int QueueGetTop(Queue *queue,DataType *value);     
