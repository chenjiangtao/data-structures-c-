//
// Created by user on 2020/9/13.
//
#ifndef CHAPTER06_HEAP_H
#define CHAPTER06_HEAP_H
#include<iostream>
#include<cstdlib>
using namespace std;
typedef int DataType;
class MinHeap
{
private:
    DataType* heap;
    int len;
    int MaxSize;
public:
    MinHeap(int size);
    ~MinHeap(){
        delete[] heap;
    }
    void ClearHeap();
    bool EmptyHeap();
    void InsertHeap(DataType item);
    DataType DeleteHeap();
};
MinHeap::MinHeap(int sz)
{
    MaxSize=sz;
    heap=new DataType[sz];
    if(heap==NULL)
    {
        cout<<"存储分配错误"<<endl;
        exit(1);
    }
    len=0;
}
void MinHeap::ClearHeap()
{
    len=0;
}
bool MinHeap::EmptyHeap()
{
    return len==0;
}
void MinHeap::InsertHeap(DataType item)
{
    if(len==MaxSize)
    {
        int k=sizeof(DataType);
        heap=(DataType*)realloc(heap,2*MaxSize*k);
        if(heap==NULL)
        {
            cout<<"动态空间用完,退出"<<endl;
            exit(1);
        }
        MaxSize=2*MaxSize;

    }
    int i=len;//len=6 结点的个数
    int j;
    while(i!=0)
    {
        j=(i-1)/2;
        if(item>=heap[j])
            break;
        heap[i]=heap[j];//把j所指向的数据
        i=j;
    }
    heap[i]=item;
    len++;
}
DataType MinHeap::DeleteHeap()
{
    if(len==0)
    {
        cout<<"堆为空,退出"<<endl;
        exit(1);
    }
    DataType temp=heap[0];
    DataType x=heap[len-1];
    len--;//堆元素个数减小1
    if(len==0)
        return temp;
    int i=0;
    int j=1;
    while(j<=len-1)
    {
        if(j<len-1&&heap[j]>heap[j+1])//j=len-1
            j++;//j+1   如果有左右两个儿子结点,
            //需要比较j   j+1所指向结点大小
        if(x<=heap[j])//x=60 heap[j]=26
            break;
        heap[i]=heap[j];//j指向儿子，i指向父结点
        i=j;
        j=2*i+1;//左儿子
    }
    heap[i]=x;//  x=60,i=4
    return temp;
}

#endif //CHAPTER06_HEAP_H
