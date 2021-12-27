#ifndef CHAPTER02_LINKEDLIST_H
#define CHAPTER02_LINKEDLIST_H
#include <cstdlib>
#include <iostream>
using namespace std;
typedef int DataType;
//也可以用struct Node
class Node
{
    friend class LinkList;
private:
    DataType data;
    Node *next;
public:
    Node(Node *ptr=NULL)
    { next=ptr;}
    Node(int item,Node *ptr=NULL)
    {
        data=item;
        next=ptr;
    }
};
class LinkList{
//链表类
private:
    Node* head;
    Node* tail;
    //链表的表头指针、尾指针
public:
    LinkList()
    {
        head=new Node();//表头结点
        head->next=NULL;
        tail=head;
    }


    DataType GetElem(int i);
    bool IsEmpty()
    { return head->next == NULL ? true : false; }
    void Create(int n);
    Node* Locate(DataType e);
    ~LinkList();
    void Insert(DataType x, int i);
    DataType Delete(int i);
    void Clear();
    void PrintList();//打印输出单链表
    void Input();
    void CreateListF();//头插法创建链表
    void CreateListR();//尾插法创建链表
    void ReverseList();//链表逆序
    void ReverseListByArray();
    Node* SearchKNode(int k);//查找倒数第k个结点
    void MergeList(LinkList*& lb);//合并链表
    void SplitList(LinkList*& la,LinkList*& lb);
    int getSize();
    void ReverseListRecur();
};
int LinkList::getSize()
{
    int count=0;
    Node* p=head->next;
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    return count;
}
void LinkList::CreateListF()//头插法创建链表
{
    DataType data;
    cout<<"请输入数据(输入0结束):"<<endl;
    cin>>data;
    Node* s;
    while(data>0)
    {
        s=new Node(data,head->next);
        //s->next=head->next;
        head->next=s;
        cout<<"请输入数据(输入0结束):"<<endl;
        cin>>data;
    }
}

void  LinkList::CreateListR()//尾插法创建链表
{
    DataType data;
    cout<<"请输入数据,0结束:"<<endl;
    cin>>data;
    Node* s;
    while(data>0)
    {
        s=new Node(data,NULL);
        tail->next=s;
        tail=s;
        cout<<"请再次输入数据(输入0结束):"<<endl;
        cin>>data;
    }

}
/*
 * 【例2.7】已知一个带头结点的单链表L,
 * 设计一个算法实现链表逆置，
 * 要求不增加额外存储空间
 *
 * */
void  LinkList::ReverseList()
{
    Node* p,*q,*r;
    p=head->next;
    if(p==NULL||p->next==NULL)
        return;
    tail=head->next;
    //p=tail;
    q=p->next;
    tail->next=NULL;
    while(q!=NULL)
    {
        r=q->next;//s
        head->next=q;
        q->next=p;
        p=q;
        q=r;
    }
}
/*
 * 【例2.8】已知带头结点的单链表L,
 * 设计算法实现查找链表倒数第K个结点。
 * 若查找成功，返回指示指针,否则返回NULL。
 * */
Node* LinkList::SearchKNode(int k)
{
    if(head==NULL||head->next==NULL)
        return NULL;
    Node* k_node,*l_node;
    //k_node   p
    //l_node   q
    int i=1;
    k_node=head->next;
    l_node=head->next;
    while(i<k&&l_node!=NULL)//k-1步
    {
        l_node=l_node->next;//往右移动k-1次
        i++;
    }
    if(l_node==NULL)
        return NULL;
    while(l_node->next!=NULL)//k,l两根指针同步->
    {
        k_node=k_node->next;
        l_node=l_node->next;
    }
    cout<<k_node->data<<endl;
    return k_node;

}
/*【例2.9】A和B是两个带头结点的单链表，
 其中元素递增有序，设计一个算法
 将A和B归并程一个递增有序的链表C,
 要求不能增加额外存储空间。
 *
 * */
void LinkList::MergeList(LinkList*& lb)
{
    Node* newhead;
    Node* p1=head->next;
    Node* p2=lb->head->next;
    if(p1->data<=p2->data)
        newhead=head;
    else
        newhead=lb->head;
    tail=newhead;
    while(p1&&p2)
    {
        if(p1->data<=p2->data)//取p1
        {
            tail->next=p1;//尾插法
            tail=p1;
            p1=p1->next;
        }
        else
        {
            tail->next=p2;
            tail=p2;
            p2=p2->next;
        }

    }
    while(p1!=NULL)
    {
        tail->next=p1;
        tail=p1;
        p1=p1->next;
    }
    while(p2!=NULL)
    {
        tail->next=p2;
        tail=p2;
        p2=p2->next;
    }
    head=newhead;
}
/*
 * 【例2.10】有一个带头结点的
 单链表L=(a1,b1,a2,b2,…an,bn)
设计算法将其分拆程两个带头结点的链表
 L1=(a1,a2,…an),L2=(bn,bn-1,…b2,b1)
 * */
void LinkList::SplitList(LinkList*& la,LinkList*& lb)
{
    Node* pa,* pb;
    pa=head->next;// a1
    pb=pa->next;
    lb->tail=pb;//  b1
    while(pa!=NULL&&pb!=NULL)
    {
       la->tail->next=pa;//尾插法把pa所指向的结点
       la->tail=pa;//插入到la的尾节点后
       pa=pb->next;//修改pa指针

       pb->next=lb->head->next;//头插法
       lb->head->next=pb;
       if(pa!=NULL)
           pb=pa->next;

    }
    if(pa!=NULL)
    {
        la->tail->next=pa;
        la->tail=pa;
    }
    la->tail->next=NULL;
    lb->tail->next=NULL;
}
void LinkList::Input()
{
    DataType number;
    int i=1;
    cout<<"Please input a number,0 for end:"<<endl;
    cin>>number;
    while(number>0)
    {
        Insert(number,i);
        i++;
        cout<<"Please input a number,0 for end:"<<endl;
        cin>>number;
    }

}
//Created By YangMingHua 2019-10-08
/*
DataType LinkList::GetElem(int i)
{
  if(i<=0)
      {
    cout<<"非法参数,无法返回元素"<<endl;
    exit(0);
   }
  if(head==NULL||head->next==NULL)
  {
    cout<<"空表,无法返回元素"<<endl;
    exit(0);
  }
  Node* p=head;
  int k=0;
  while(p!=NULL&&k<i)
  {
        p=p->next;
        k++;
  }
  if(p==NULL)
  {
     cout<<"第"<<i<<"个元素不存在,无法返回元素"<<endl;
    exit(0);
  }
  else
     return p->data;
}
*/
DataType LinkList::GetElem(int i)
{
    Node* p;
    int k,j;
    if(head->next==NULL)
    {
        cout<<"空表,无法返回元素"<<endl;
        exit(0);
    }
    else
    {
        p=head;
        k=0;
        while(p!=NULL&&k<i)
        {
            p=p->next;
            k++;
        }
        if(p==NULL||k>i)
        {
            cout<<"第"<<i<<"个元素不存在,无法返回元素"<<endl;
            exit(0);
        }
        return p->data;
    }

}
//LinkList::Insert()  Created By YangMingHua 2019-10-08
/*
void LinkList::Insert(DataType x,int i)
{
    if(i<=0)
    {
       cout<<"第"<<i<<"个元素不存在"<<endl;
       exit(0);
    }
    if(head==NULL)
   {
       cout<<"链表不存在"<<endl;
       exit(0);
    }
  Node* p=head;
  Node* q;
  Node* s;
  int k=0;
  while(p!=NULL&&k<i-1)
   {
                   p=p->next;
                  k++;
   }
   if(p==NULL)
   {
        cout<<"第"<<i<<"个元素不存在"<<endl;
       exit(0);
   }
  else
   {
         q=p->next;
         s=new Node();
        if(s==NULL)
        {
     cout<<"空间分配失败"<<endl;
                exit(0);
       }
       else
        {
             s->data=x;
             s->next=q;
             p->next=s;
        }
   }
}
*/
void LinkList::Insert(DataType x,int i)//将x插在第i个位置
{
    Node* p=head;
    int k=0;
    while(p!=NULL&&k<i-1)
    {
        p=p->next;
        k++;
    }
    if(p==NULL||k<i-1)
    {
        cout<<"第"<<i<<"个元素不存在"<<endl;
        exit(0);
    }
    Node* s=new Node();
    if(s==NULL)
    {
        cout<<"空间分配失败"<<endl;
        exit(0);
    }
    s->data=x;
    s->next=p->next;
    p->next=s;
    if(p==tail)
        tail=s;
}

DataType LinkList::Delete(int i)
{
    Node* p=head;
    int k=0;
    while(p!=NULL&&k<i-1)
    {
        p=p->next;
        k++;
    }
    if(p==NULL||p->next==NULL)
    {
        cout<<"删除位置非法"<<endl;
        exit(0);
    }
    Node* q=p->next;
    p->next=q->next;
    DataType e=q->data;
    delete q;
    if(p->next==NULL)
        tail=p;
    return e;
}
//尾插法创建链表算法2
void LinkList::Create(int n)
{
    int i=0;
    DataType x;
    Node* s;
    while(i<n)
    {
        cout<<"请输入一个数据";
        cin>>x;
        s=new Node();
        s->data=x;
        s->next=NULL;
        tail->next=s;
        tail=s;
        i++;
    }
}
/*
Node* LinkList::Locate(DataType e)
{
    if(head==NULL||head->next==NULL)
      return NULL;
  else
  {
      Node* p=head->next;
      while(p!=NULL&&p->data!=e)
           p=p->next;
      return p;

   }
}
*/
Node* LinkList::Locate(DataType e)
{
    Node* p;
    p=head->next;
    while(p!=NULL)
    {
        if(p->data==e)
            return p;
        else
            p=p->next;
    }
    return NULL;
}
void LinkList::Clear()
{
    Node* q;
    while(head->next!=NULL)
    {
        q=head->next;
        head->next=q->next;
        delete q;
    }
}
LinkList::~LinkList()
{
    Node *p;
    p=head;
    while(p!=NULL)
    {
        p=p->next;//p指向下一个结点
        delete head;//删除head所指向的结点
        head=p;//head更新，指向下一个即将被删除结点
    }
}
/*
 * 单链表逆置之递归算法
 * */
void LinkList::ReverseListRecur()
{
    if(head==NULL||head->next==NULL||head->next->next==NULL)
        return;
    Node* t;
    Node* first=head->next;
    head->next=first->next;
    ReverseListRecur();
    tail->next=first;
    tail=first;
    tail->next=NULL;
}
/*单链表逆置非递归算法
 * 1.用栈
 * 2.用数组
 * 3.既不用栈也不用数组
 * */
void LinkList::ReverseListByArray()
{
  int n=getSize();
  Node* array[n];
  int i=0;
  Node * p;
  p=head->next;
  while(p!=NULL)
  {
      array[i++]=p;
      p=p->next;
  }
  for(i=n-1;i>0;i--)
      array[i]->next=array[i-1];
  //直接修改每个结点的next
  head->next=array[n-1];
  tail=array[0];
  tail->next=NULL;
}
void LinkList::PrintList()
{
    Node* p=head->next;
    while(p->next!=NULL)
    {
        cout<<p->data<<"-->";
        p=p->next;
    }
    cout<<p->data;
    cout<<endl;
}
#endif //CHAPTER02_LINKEDLIST_H
