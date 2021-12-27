#ifndef CHAPTER03_SEQQUEUE_H
#define CHAPTER03_SEQQUEUE_H
#include <iostream>
#include <cstdlib>
using namespace std;
typedef int DataType;
const int MaxQSize=50;
class Queue
{
    int front,rear;
    DataType QueueList[MaxQSize];
public:
    Queue();
    ~Queue(){
    };
    void EnQueue(DataType item);
    DataType DeQueue();
    DataType GetFront();
    void ClearQueue();
    bool IsEmpty();
    bool IsFull();
    int Length();
};
Queue::Queue()
{
    front=rear=0;//空队列
}
void Queue::EnQueue(DataType item)
{
    if((rear+1)%MaxQSize==front)
    {
        cout<<"队列已满,不能入队"<<endl;
        exit(0);
    }
    else
    {
        QueueList[rear]=item;//队尾进对
        rear=(rear+1)%MaxQSize;//rear指向了队尾元素
        //的下一个空白位置
    }
}
DataType Queue::DeQueue()
{
    if(front==rear)
    {
        cout<<"队列已空,不能出队"<<endl;
        exit(0);
    }
    DataType e=QueueList[front];
    front=(front+1)%MaxQSize;//front++指针往后移动
    return e;
}
void Queue::ClearQueue()
{
    rear=front;
}
bool Queue::IsEmpty()
{
    if(rear==front)
        return true;
    else
        return false;
}
bool Queue::IsFull()
{
    if((rear+1)%MaxQSize==front)
        return true;
    else
        return false;
}
DataType Queue::GetFront()
{
    return QueueList[front];
}
int Queue::Length()
{
    return (rear-front+MaxQSize)%MaxQSize;
}

#endif //CHAPTER03_SEQQUEUE_H
