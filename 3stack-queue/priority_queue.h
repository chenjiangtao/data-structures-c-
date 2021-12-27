#ifndef CHAPTER03_PRIORITY_QUEUE_H
#define CHAPTER03_PRIORITY_QUEUE_H
#include <iostream>
#include <cstdlib>
using namespace std;
const int MaxQSize=50;
typedef struct datatype
{
    int number;
    int priority;//优先级
}DataType;
class PriorityQueue
{
    int front,rear;
    DataType data[MaxQSize];
public:
    PriorityQueue();
    ~PriorityQueue(){
    };
    void EnQueue(DataType item);
    DataType DeQueue();
    DataType GetFront();
    void ClearQueue();
    bool IsEmpty();
    bool IsFull();
    int Length();
};
PriorityQueue::PriorityQueue()
{
    front=rear=0;
}
void PriorityQueue::EnQueue(DataType item)
{
    if((rear+1)%MaxQSize==front)
    {
        cout<<"队列已满,不能入队"<<endl;
        exit(0);
    }
    else
    {
        data[rear]=item;
        rear=(rear+1)%MaxQSize;
    }
}
//优先级高的元素出队
DataType PriorityQueue::DeQueue()
{
    if(front==rear)
    {
        cout<<"队列已空,不能出队"<<endl;
        exit(0);
    }
    int max_priority=data[front].priority;
    int maxindex=front;
    for(int i=front;i!=rear;)
    {
        if(data[i].priority>max_priority)
            maxindex=i;
        i=(i+1)%MaxQSize;
    }
    DataType e=data[maxindex];
    data[maxindex]=data[front];
    front=(front+1)%MaxQSize;
    /*
     *
    rear=(rear-1)%MaxQSize;
     data[maxindex]=data[rear];
     * */
    return e;
}
void PriorityQueue::ClearQueue()
{
    rear=front;
}
bool PriorityQueue::IsEmpty()
{
    if(rear==front)
        return true;
    else
        return false;
}
bool PriorityQueue::IsFull()
{
    if((rear+1)%MaxQSize==front)
        return true;
    else
        return false;
}
DataType PriorityQueue::GetFront()
{
    return QueueList[front];
}
int PriorityQueue::Length()
{
    return (rear-front+MaxQSize)%MaxQSize;
}
#endif //CHAPTER03_PRIORITY_QUEUE_H
