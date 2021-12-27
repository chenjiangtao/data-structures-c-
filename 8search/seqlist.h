//
// Created by user on 2020/10/5.
//
#ifndef CHAPTER08_SEQLIST_H
#define CHAPTER08_SEQLIST_H
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
typedef int DataType;

typedef struct node
{
    int data;    //数据域
    DataType key;//主键,关键字
}Node;
//n个Node构成数据列表
//在这n个数据元素里找 key等于某个给定的值的结点元素
//这n个元素存储在一个数组
//顺序查找算法
class searchList
{
private:
    Node* Element;
    int ArraySize;
    int CurrentSize;
public:
    searchList(int sz=10)
    {
        Element=new Node[sz];
        CurrentSize=0;
        ArraySize=sz;
    }
    ~searchList()
    {
        delete[] Element;
    }
    void Create(Node a[],int n);
    int Search(DataType x);
    int Search2(DataType x);
    int BinarySearch(DataType x);
    int BinarySearch(DataType x,int low,int high);
    int fibonacci(int i);
    int fibonacciSearch(vector<int>data, int maxSize, int targetValue);
};
void searchList::Create(Node a[],int n)
{
    for(int i=0;i<n;i++)
        Element[i]=a[i];
    CurrentSize=n;
}
int searchList::Search(DataType x)
{
    int n=CurrentSize;
    for(int i=0;i<n;i++)
        if(Element[i].key==x)
            break;
    if(i<CurrentSize)
        return i;
    else
        return -1;
}
//改进算法,增加一个 监视哨
int searchList::Search2(DataType x)
{
    int n=CurrentSize;
    //0....n-1
    Element[n].key=x;
    int i=0;
    while(Element[i].key!=x)
        i++;
    if(i<CurrentSize)
        return i;
    else//i==n 说明原来的数据里是没有
        return -1;
}
int searchList::BinarySearch(DataType x)
{

    int n=CurrentSize;
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(x==Element[mid].key)
            return mid;
        if(x<Element[mid].key)
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}
int searchList::BinarySearch(DataType x,int low,int high)
{
    int mid=-1;
    if(low<=high)
    {
        mid=(low+high)/2;
        if(x<Element[mid].key)
            mid=BinarySearch(x,low,mid-1);
        else if(x>Element[mid].key)
            mid=BinarySearch(x,mid+1,high);
    }
    return mid;
}
int searchList::fibonacci(int i)
{
    if(i==1||i==2)
        return 1;
    else
        return fibonacci(i-1)+fibonacci(i-2);
}
// 斐波那契查找
int searchList::fibonacciSearch(vector<int>data, int maxSize, int targetValue)
{
    // 1：构建斐波那契数列
    vector<int>fiboArray(maxSize, 0);
    int oriLength = data.size();
    for (int i = 0; i < maxSize-1; i++) {
        fiboArray[i+1] = fibonacci(i);

    }

    // 2：计算数据长度对应斐波那契数列元素
    int index = 0;
    while (fiboArray[index]<data.size())
    {
        index++;
    }
    // printf("%d %d \n", index, fiboArray[index]);

    // 3：对数据进行填充
    for (int i = data.size(); i < fiboArray[index]; i++) {
        data.push_back(data[data.size()-1]);
        // printf("%d ", data[i]);
    }

    // 4：对区间不断分割
    int left = 0;
    int right = data[data.size() - 1];
    while (left<=right && index>=0)
    {
        // 计算中间位置
        int mid = left + fiboArray[index - 1] - 1;

        // 对三种情况分别处理
        // 目标值搜索成功
        if (data[mid] == targetValue) {
            // 如果mid比原始数据长度大，则说明mid位置为填充的元素
            if (mid >= oriLength) { return oriLength - 1; }
            else { return mid; }
        }
            // 目标值在中间值左边，更新右边界
        else if (data[mid]>targetValue) {
            right = mid - 1;
            index = index - 1;
        }
            // 目标值在中间值右边，更新左边界
        else {
            left = mid + 1;
            index = index - 2;
        }
    }
    // 搜索失败
    return -1;
}
#endif //CHAPTER08_SEQLIST_H
