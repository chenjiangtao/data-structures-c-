#ifndef CHAPTER02_POLYN_H
#define CHAPTER02_POLYN_H
#include <cstdlib>
#include <iostream>
using namespace std;
const int MaxPolySize=100;
typedef int DataType;
class PNode
        {
    friend class Polyn;
    int coef;
    int expn;
    PNode* next;
        };
class Polyn
        {
    PNode* phead;
        public:
            Polyn(){
                phead=new PNode();
                if(phead==NULL)
                    exit(0);
                phead->next=NULL;
            }
            ~Polyn();
            void PolynAdd(Polyn pa,Polyn pb);
            void print();
            void create();
        };
void Polyn::PolynAdd(Polyn pa,Polyn pb)
{
    PNode *t1,*t2,*t3;
    t1=pa.phead->next;
    t2=pb.phead->next;
    t3=phead;
    while(t1&&t2)
    {
        if(t1->expn<t2->expn)
        {
            t3->next=new PNode();
            t3=t3->next;
            t3->coef=t2->coef;
            t3->expn=t2->expn;
            t2=t2->next;
            continue;
        }
        else if(t1->expn>t2->expn)
        {
            t3->next=new PNode();
            t3=t3->next;
            t3->coef=t1->coef;
            t3->expn=t1->expn;
            t1=t1->next;
            continue;
        }
        else
        {
            double a=t1->coef+t2->coef;
            if(a!=0)
            {
                t3->next=new PNode();
                t3=t3->next;
                t3->coef=a;
                t3->expn=t1->expn;
            }
            t1=t1->next;
            t2=t2->next;
            continue;
        }
    }
    while(t1!=NULL)
    {
        t3->next=new PNode();
        t3=t3->next;
        t3->coef=t1->coef;
        t3->expn=t1->expn;
        t1=t1->next;
    }
    while(t2!=NULL)
    {
        t3->next=new PNode();
        t3=t3->next;
        t3->coef=t2->coef;
        t3->expn=t2->expn;
        t2=t2->next;
    }
    t3->next=NULL;
    return ;
}
void Polyn::create()
{
    PNode*p,*q;
    int n;
    q=phead;
    cout<<"请输入多项式的项数:"<<endl;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        p=new PNode();
        cout<<"请输入多项式各项的系数和指数:"<<endl;
        cin>>p->coef>>p->expn;
        p->next=NULL;
        q->next=p;
        q=p;
    }
}
void Polyn::print()
{
    PNode* p;
    p=phead->next;
    cout<<"\n";
    while(p!=NULL)
    {
        cout<<"("<<p->coef<<","<<p->expn<<")";
        p=p->next;
    }
    cout<<endl;
}
Polyn::~Polyn()
{
    PNode* p,*q;
    p=phead->next;
    while(p)
    {
        q=p;
        p=p->next;
        delete q;
    }
    phead->next=NULL;
}

#endif //CHAPTER02_POLYN_H
