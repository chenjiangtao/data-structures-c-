#ifndef CHAPTER03_LINKEDSTACK_H
#define CHAPTER03_LINKEDSTACK_H
#include <iostream>
#include <cstdlib>
using namespace std;
typedef int DataType;
class Stack;
class StackNode
{
    friend class Stack;
private:
    DataType data;  //结点数据
    StackNode *next;  //结点链指针
public:
    StackNode(int d = 0,StackNode *link = NULL ):data(d), next(link) { }
};
class Stack{
private:
    StackNode *top;  //栈顶指针
public:
    Stack(){// 具有头结点的链栈
        top=new StackNode(); }
    ~Stack(){Clear();delete top; }
    void Push(DataType item);  //进栈
    DataType Pop();  //退栈
    DataType GetTop();  //读取栈顶元素
    void Clear();  //实现与 ~LinkedStack( ) 同
    bool IsEmpty() { return ( top->next== NULL) ? true : false; }
    void Display();
};

void Stack:: Push(DataType item)
{
    StackNode* p;
    p=new StackNode();
    p->data=item;
    p->next=top->next;
    top->next=p;
}
DataType Stack::Pop()
{
    StackNode* p;
    if(IsEmpty()==true)
    {
        cout<<"栈空,无法出栈"<<endl;
        exit(0);
    }
    else
    {
        p=top->next;
        DataType value=p->data;
        top->next=p->next;
        delete p;
        return value;
    }
}

DataType Stack::GetTop()
{
    StackNode* p;
    if(IsEmpty()==true)
    {
        cout<<"栈空,无法取到栈顶元素"<<endl;
        exit(0);
    }
    else
    {
        p=top->next;
        DataType value=p->data;
        return value;
    }
}

void Stack::Display()
{
    StackNode* p=top->next;
    while(p->next!=NULL)
    {
        cout<<p->data<<"-->";
        p=p->next;
    }
    cout<<p->data<<endl;
    return;
}
#endif //CHAPTER03_LINKEDSTACK_H
