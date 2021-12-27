#ifndef CHAPTER02_SEQLIST_H
#define CHAPTER02_SEQLIST_H
#include <cstdlib>
#include <iostream>
using namespace std;
const int MaxListSize= 100;
typedef int DataType;
//顺序表
class List{
    DataType data[MaxListSize];  //存放数组
    int size;  //当前顺序表里元素的个数

public:
    List(int sz=0){size=sz;}  //构造函数
    ~List(){}  //析构函数
    void Clear(){size=0;}
    bool IsEmpty()
    { return ( size ==0 ) ? true : false; }
    bool IsFull()
    { return ( size >=MaxListSize ) ? true : false; }
    DataType  GetElem ( int i ) ;  //取第 i 个表项的值

    int Locate(DataType e);
    void Insert(int i,DataType e);
    DataType Delete(int i);
    int Length() const { return size; }

    void PrintList();  //输出
    void input();
    void MergeList(List la,List lb);//有序列表合并
    void Union(List& la,List& lb);

};

void List::Insert(int i,DataType e)
{//i=1,2,...size,  size+1
    //顺序表满的时候,不能插入新的元素
    if(i<1||i>size+1||size>=MaxListSize)
    {
        cout<<"Insert error"<<endl;
        exit(0);
    }
    else
    {
        for(int j=size-1;j>=i-1;j--)
            data[j+1]=data[j];
        data[i-1]=e;// datai
        size++;
    }
}
DataType List::Delete(int i)
{
    //从表中删除第 i 个表项
    //通过引用型参数 x 返回删除的元素值
    if(size <=0 )
        exit(0);
    if(i < 1 || i > size )
    {
        cout<<"delete error"<<endl;
        exit(0);
    }
    else
    {
        DataType e=data[i-1];
        for (int j = i-1; j <size-1; j++ )
            data[j] = data[j+1];
        size--;
        return e;
    }
}
//在当前list找一找有没有哪个元素的值等于e
int List::Locate(DataType e)
{
    int i=1;//i=1,2,...size
    while(i<=size&&data[i-1]!=e)
        i++;
    if(i>size)
        return 0;//没有发现e这个元素
    else
        return i;//
}

DataType List::GetElem(int i)
{//i是元素的序号,1,2,....size
    if(i<1||i>size)
    {
        cout<<"getelem error"<<endl;
        exit(0);
    }
    else
        return data[i-1];
}
void List::PrintList()
{
    if(size==0)
    {
        cout<<"print error"<<endl;
        exit(0);
    }
    else
    {
        for(int i=0;i<size-1;i++)
            cout<<data[i]<<"-->";
        cout<<data[size-1]<<endl;


    }

}
//MergeList(List la,List lb)
void List::MergeList(List la,List lb)
{
    int i,j,k;
    DataType x,y;
    i=0;
    j=0;
    k=0;
    while(i<la.size&&j<lb.size)
    {
        x=la.data[i];
        y=lb.data[j];
        if(x<=y)
        {
            data[k]=x;
            i++;
            k++;
        }
        else
        {
            data[k]=y;
            j++;
            k++;
        }
    }
    while(i<la.size)
    {
        data[k]=la.data[i];
        i++;
        k++;
    }
    while(j<lb.size)
    {
        data[k]=lb.data[j];
        j++;
        k++;
    }
    size=k;
}

void List::input()
{

    if(size<0||size>=MaxListSize)
        return;

    cout<<"开始输入元素:"<<endl;
    for(int i=0;i<size;i++)
    {
        cin>>data[i];
        cout<<"继续输入"<<endl;
    }


}
void List::Union(List &la, List &lb)
{

    int i,j;
    for(i=1;i<=la.Length();i++)
        Insert(i,la.GetElem(i));
    for(j=1;j<=lb.Length();j++)
        if(la.Locate(lb.GetElem(j))==0)
            Insert(i++,lb.GetElem(j));

}
#endif //CHAPTER02_SEQLIST_H
