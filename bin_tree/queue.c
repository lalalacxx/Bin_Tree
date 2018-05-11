#include<stdio.h>
#include<stdlib.h>
#include"queue.h"


//队列初始化函数
void QueueInit(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}
//队列销毁函数
void QueueDestroy(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}
//入队列操作函数
void QueuePush(Queue *queue,DataType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size >= max_size)
    {
        //队列满了
        return;
    }
    queue->data[queue->tail++] = value;
    queue->size++;
    if(queue->tail > max_size)
    {
        //如果tail走到了队列的尾部
        queue->tail = 0;
    }
}
//出队列操作函数
void QueuePop(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size == 0)
    {
        //空队列
        return;
    }
    if(queue->head >= max_size)
    {
        //如果head走到了队列的最后一个元素
        //呢出队列以后继续回到队列一开始的地方
        //就相当于是将最后一个元素出对队列
        queue->head = 0;
    }
    //否则直接将head往后移动一步
    queue->head++;
    //将对列元素个数-1
    queue->size--;
    if(queue->size == 0)
    {
        queue->head = 0;
        queue->tail = 0;
    }
}
//取队首元素函数
int QueueGetTop(Queue *queue,DataType *value)
{
    if(queue == NULL)
    {
        //非法输入
        return 0; 
    }
    if(queue->size == 0)
    {
        //空队列
        return 0;
    }
    *value = queue->data[queue->head];
    return 1;
}
void Print(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size == 0)
    {
        return;
    }
    if(queue->head < queue->tail)
    {
        int i = queue->head;
        for(;i < queue->tail;i++)
        {
            printf("%p ",queue->data[i]);
        }
    }
    else
    {
        int i = queue->head;
        while(queue->head < max_size)
        {
            printf("%p ",queue->data[queue->head]);
            queue->head++;
        }
        queue->head = 0;
        for(;i < queue->tail;i++)
        {
            printf("%p ",queue->data[i]);
        }
    }
    printf("\n\n");
}
