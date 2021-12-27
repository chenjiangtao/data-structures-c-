#ifndef CHAPTER03_SEQSTACK_H
#define CHAPTER03_SEQSTACK_H
#include <iostream>
#include <cstdlib>
using namespace std;
const int MaxStackSize=50;
typedef int DataType;
class Stack {
private:
    int top;  //栈顶指针
    DataType StackList[MaxStackSize];  //栈元素数组

public:
    Stack();  //构造函数
    ~Stack()
    {}
    bool IsEmpty();
    bool IsFull();
    DataType GetTop();
    void Push(DataType x);
    DataType Pop();
    void Clear();
    void Output();

};
//top++
//top--
//top栈顶指针
Stack::Stack()
{
    top=-1;//top=0 栈顶指针指向栈顶元素的上一个空白位置
}
bool Stack::IsEmpty()
{
    if(top==-1)
        return true;
    else
        return false;
}
//栈满的时候，不能进栈
//栈空的时候，不允许执行出栈的动作
bool Stack::IsFull()
{
    if(top==MaxStackSize-1)
        return true;
    else
        return false;
}
DataType Stack::GetTop()
{
    if(IsEmpty())
    {
        cout<<"栈空"<<endl;
        exit(0);
    }
    return StackList[top];//top指向栈顶元素
}
void Stack::Push(DataType x)
{
    if(IsFull())
    {
        cout<<"栈满"<<endl;
        exit(0);
    }
    else
        StackList[++top]=x;
}
DataType Stack::Pop()
{
    if(IsEmpty())
    {
        cout<<"栈空"<<endl;
        exit(0);
    }
    return StackList[top--];
}
void Stack::Clear()
{
    top=-1;
}
//getSize() ,Length()
void Stack::Output( ) {
    for(int i=0;i<=top;i++)
        cout<<StackList[i]<<endl;

}


#endif //CHAPTER03_SEQSTACK_H
