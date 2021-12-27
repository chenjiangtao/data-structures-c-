#ifndef CHAPTER02_CIRCLELIST_H
#define CHAPTER02_CIRCLELIST_H
#include <cstdlib>
#include <iostream>
using namespace std;
typedef int DataType;
class CircLinkNode
{
    friend class CircList;

private:
    DataType data;
    CircLinkNode* link;//next
public:

    CircLinkNode(CircLinkNode* next=NULL)
    {
        link=next;
    }
    CircLinkNode(int newdata,CircLinkNode* next=NULL)
    {
        data=newdata;
        link=next;
    }

};
class CircList
{
private:
    CircLinkNode *first, *last, *current;
    //循环链表的表头指针、尾指针和当前元素指针
    //head,tail
public:

    CircList()
    {
        first=NULL;
        last=NULL;
        current=NULL;
    }
    CircList(DataType value=0);
    CircList(CircList& L );
    ~CircList( )
    {
        if(first!=NULL)//first==NULL不需处理
        {
            CircLinkNode *p=first;
            if(first==last)//只有一个结点
            {
                delete p;
                return;
            }
            first=first->link;
            delete p;
            while(first!=last)
            {
                p=first;
                first=first->link;
                delete p;
            }
            delete last;
        }


    }
    int Length( ) const;
    CircLinkNode * GetHead( ) const
    {return first;}
    void SetHead(CircLinkNode *p )
    { first = p; }
    CircLinkNode * Search(DataType value );
    CircLinkNode * Locate(int i );
    //DataType GetData( int i );
    void SetData( int i, DataType &x );
    bool Insert( int i, DataType x );
    bool Remove (int i, DataType &x );
    void Delete(DataType x);
    bool IsEmpty ( ) const
    { return first == NULL ? true : false; }
    //first->link==first;
    void Sort();
    void Input();
    void Add(DataType x );
    void PrintList();
    void Josephus(int n,int m);
    void MagicCard(int n);
};
/*
 * 循环链表的构造函数
 * 可以是带头结点的循环链表
 * 也可以没有头结点
 * 为了解决魔法师发牌和约瑟夫问题
 * 我们创建不带头结点的循环链表
 * */
CircList::CircList(DataType value)
{

    first=last= new CircLinkNode(value);

    last->link=first;//构成一个环
}
void CircList::Add(DataType x )
{
    CircLinkNode* s=new CircLinkNode(x,first);
    if(first==NULL)
    {
        first=s;
        last=s;
    }
    last->link=s;
    last=s;//s->link=first
}
/*
 *【例2.12】一个带头结点的循环单链表L,
 * 设计算法计算链表的长度
 * */
int CircList::Length( ) const
{

    if(first==NULL)
        return 0;
    CircLinkNode *p=first->link;
    int count=1;
    while(p!=first)
    {
        count++;
        p=p->link;
    }
    return count;
}
/*
 * 约瑟夫问题
 * */
void CircList::Josephus(int n, int m )
{
    CircLinkNode *p =GetHead(), *pre=NULL;
    for(int i = 0; i<n-1; i++ )
    {  //执行 n-1 次,只要有n-1个退出了
        //最后剩下的，就是求解

        for(int j = 0; j<m-1; j++ )
        {

            pre=p;
            p = p->link;
        }
        cout << p->data<<"出列--";//删除
        pre->link = p->link;
        delete p;
        p = pre->link;
    }
    cout<<endl;
    cout <<"最后出列的人是:" << p->data << endl;
}
/*
 * 魔法师发牌问题
 * */
void CircList::MagicCard(int n)
{
    int i,j;
    int number;
    current=first;//不带头结点单循环链表
    current->data=1;//A插进去
    for(i=2;i<=n;i++)//2,3,....13
    {
     //   cout<<"i="<<i<<endl;
        for(j=0;j<i;)
        {
            current=current->link;
            if(current->data==0)
                j++;
        }
        current->data=i;
        //node=node.getNext();
    }
    current=first->link;
    cout<<"A"<<"--";
    while(current!=first)
    {
        number=current->data;
        if(number<=10)
            cout<<number<<"--";
        else
        {
            switch(number)
            {
                case 11:
                    cout<<"J"<<"--";
                    break;
                case 12:
                    cout<<"Q"<<"--";
                    break;
                case 13:
                    cout<<"K"<<"--";
                    break;
                default:
                    cout<<"--";
                    break;
            }
        }
        current=current->link;
    }
}
CircLinkNode* CircList::Search(DataType value)
{  //在链表中从头搜索其数据值为value的结点
    if(first->data==value)
        return first;
    current = first->link;
    while(current != first &&current->data != value )
        current = current->link;
    if(current==first)
        current=NULL;
    return current;
}
bool CircList::Insert(int i, DataType x ) {
//将新元素 x 插入在链表中第 i 个位置
    CircLinkNode *p = Locate(i);
    //定位第 i 个元素
    if(p== NULL)
        return false;
    //参数 i 的值不合理，函数返回 false
    CircLinkNode *NewNode =new CircLinkNode(x);
    //创建含 x 的结点


    if(p->link == first)
    {
        p->link = NewNode;

        last = NewNode;

        NewNode->link=first;
    }
    else
    {
        NewNode->link=p->link;
        p->link=NewNode;
    }
    return true; //插入成功，函数返回 true
}

CircLinkNode* CircList::Locate(int i)
{
//定位函数：返回表中第 i 个元素的地址
//若 i<0 或 i 超出表中结点个数，则返回 NULL
    if(i<0)
        return NULL; // i 值不合理
    CircLinkNode *p = first;
    int j = 0;
    //检测指针 p 指向表中第一个结点
    while(p!= NULL && j < i )
    {
        p = p->link;
        j++;
    }  //寻找第 i 个结点的地址
    return p;
    //返回第 i 个结点地址，若返回 NULL，表示 i 值太大
}
void CircList::PrintList()
{

    cout<<first->data<<"-->";
    current=first->link;
    while(current!=first)
    {
        cout<<current->data<<"-->";
        current=current->link;
    }
    cout<<endl;
}

#endif //CHAPTER02_CIRCLELIST_H
