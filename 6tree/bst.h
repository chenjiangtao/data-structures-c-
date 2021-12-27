//
// Created by user on 2020/9/6.
//
#ifndef CHAPTER06_BST_H
#define CHAPTER06_BST_H
#include<iostream>
#include<cstdlib>
#include <stack>
using namespace std;
typedef int DataType;
class BinTreeNode
{
    friend class BST;
    DataType data;
    BinTreeNode* leftChild;
    BinTreeNode* rightChild;
    BinTreeNode(DataType d,BinTreeNode* l=NULL,BinTreeNode* r=NULL)
    {
        data=d;
        leftChild=l;
        rightChild=r;
    }
};
struct VistedNode
{
    BinTreeNode* node;
    bool vistedRightChild=false;
};
class BST
{
private:
    BinTreeNode* root;
    BinTreeNode* lastfound;
    void MakeEmpty(BinTreeNode*& ptr);
    void Insert(DataType x,BinTreeNode*& ptr);
    bool Remove(DataType x,BinTreeNode*& ptr);
    BinTreeNode* Copy(BinTreeNode*& ptr);
    BinTreeNode* Find(DataType x,BinTreeNode* ptr);

public:
    BST():root(NULL){
    }
    BST(DataType a[],int n)
    {
        root=NULL;
        BST(root,a,n);
    }
    BST(BinTreeNode*& ptr,DataType a[],int n);

    ~BST(){
        MakeEmpty(root);
    }
    void MakeEmpty()
    {
        MakeEmpty(root);
        root=NULL;
    }
    BinTreeNode* Find(DataType x)
    {
        return Find(x,root);
    }
    void Insert(DataType x)
    {
        Insert(x,root);
    }
    void Remove(DataType x)
    {
        Remove(x,root);
    }
    void MiddleTravel();
    void MiddleTravel(BinTreeNode* ptr);
    void MidOrder();
    void PreOrder();
    void PostOrder();


};
/*
BST::BST(BinTreeNode* ptr,DataType a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        Insert(a[i],root);
}*/
//非递归的中序遍历
void BST::MidOrder()
{
    stack<BinTreeNode*>  S;
    BinTreeNode* p = root;   //初始化
    do{
        while(p != NULL )
        {
            S.push(p);
            p = p->leftChild;
        }
        if(!S.empty())
        {                   //栈非空
            p =S.top();
            S.pop();     //退栈
            cout<< p->data << endl;      //访问根
            p = p->rightChild;              //向右链走
        }
    }while(p != NULL || !S.empty());
}
//非递归的前序遍历
void BST::PreOrder()
{
    stack<BinTreeNode*>  S;
    BinTreeNode* p = root;   //初始化
    do{
        while(p != NULL )
        {
            cout<< p->data << endl;//立刻输出
            //进栈之前就输出data
            S.push(p);
            p = p->leftChild;
        }
        if(!S.empty())
        {                   //栈非空
            p =S.top();
            S.pop();     //退栈
            p = p->rightChild;              //向右链走
        }
    }while(p != NULL || !S.empty());
}
//非递归的后序遍历
void BST::PostOrder()
{
    stack<VistedNode>  S;
    BinTreeNode* p = root;   //初始化
    VistedNode vd;
    vd.node=p;
    vd.vistedRightChild=false;
    S.push(vd);
    p=p->leftChild;
    while(!S.empty())
    {
        while(p!=NULL)
        {
            vd.node=p;
            vd.vistedRightChild=false;
            S.push(vd);
            p=p->leftChild;
        }
        vd=S.top();
        if(vd.node->rightChild!=NULL&&vd.vistedRightChild==false)
        {
            S.pop();
            vd.vistedRightChild=true;
            S.push(vd);
            p=vd.node->rightChild;
        }
        else
        {
            S.pop();
            cout<<vd.node->data<<"--";
            p=NULL;
        }

    }
}
void BST::MiddleTravel()
{
    MiddleTravel(root);
}
void BST::MiddleTravel(BinTreeNode* ptr)
{
    if(ptr==NULL)
        return;
    MiddleTravel(ptr->leftChild);
    cout<<ptr->data<<" , ";
    MiddleTravel(ptr->rightChild);
}
void BST::MakeEmpty(BinTreeNode*& ptr)
{
    if(ptr==NULL)
        return ;
    else
    {
        MakeEmpty(ptr->leftChild);
        MakeEmpty(ptr->rightChild);
        delete ptr;
        ptr=NULL;
    }
}
BinTreeNode* BST::Find(DataType x,BinTreeNode* ptr)
{
    if(ptr==NULL)
        return NULL;
    if(ptr->data==x)
        return ptr;
    if(x<ptr->data)
        return Find(x,ptr->leftChild);
    else
        return Find(x,ptr->rightChild);
}
//非递归版的查找算法
//BinTreeNode* Find(DataType x,BinTreeNode* ptr)
/*
BinTreeNode* BST::Find(DataType x,BinTreeNode* ptr)
{
	if(ptr!=NULL)
	{
		BinTreeNode* temp=ptr;
		while(temp!=NULL)
		{
			if(temp->data==x)
			   return temp;
			if(x<temp->data)
			   temp=temp->leftChild;
			else
			   temp=temp->rightChild;
		}
	}
	return NULL;
}
 */
void BST::Insert(DataType x,BinTreeNode*& ptr)
{
    if(ptr==NULL)
    {
        ptr=new BinTreeNode(x,NULL,NULL);
        if(ptr==NULL)
        {
            cout<<"存储不足"<<endl;
        }
    }
    else if(x<ptr->data)
        Insert(x,ptr->leftChild);
    else if(x>ptr->data)
        Insert(x,ptr->rightChild);
}
//插入结点的非递归算法
/*
void BST::Insert(DataType x,BinTreeNode*& ptr)
{
	BinTreeNode* t=ptr,*parent=NULL;
	while(t!=NULL)
	{
		parent=t;
		if(x==t->data)
		  return ;
		if(x<t->data)
		  t=t->leftChild;
		else
		  t=t->rightChild;
	}
	BinTreeNode* p=new BinTreeNode(x,NULL,NULL);
	if(parent==NULL)
	  ptr=p;
	else if(x<parent->data)
	        parent->leftChild=p;
	     else
	        parent->rightChild=p;

 } */
BST::BST(BinTreeNode*& ptr,DataType a[],int n)
{
    ptr=NULL;
    for(int i=0;i<n;i++)
        Insert(a[i],ptr);
}
bool BST::Remove(DataType x,BinTreeNode*& ptr)
{
    if(ptr==NULL)
        return false;
    BinTreeNode* p=ptr,*parent=NULL;
    while(p!=NULL)
    {
        if(x==p->data)
            break;
        if(x<p->data)
        {
            parent=p;
            p=p->leftChild;
        }
        else
        {
            parent=p;
            p=p->rightChild;
        }
    }
    if(p==NULL)
        return false;
    else
    {
        if(p->leftChild==NULL)
        {
            if(parent==NULL)
                ptr=p->rightChild;
            else if(parent->leftChild==p)
                parent->leftChild=p->rightChild;
            else
                parent->rightChild=p->rightChild;
        }
        else if(p->rightChild==NULL)//p无右子女
        {
            if(parent==NULL)
                ptr=p->leftChild;
            else if(parent->leftChild==p)
                parent->leftChild=p->leftChild;
            else
                parent->rightChild=p->leftChild;
        }
        else //p既有左子女 又有右子女
        {
            BinTreeNode* rr=p,*r=p->rightChild;
            while(r->leftChild)
            {
                rr=r;
                r=r->leftChild;
            }
            p->data=r->data;
            if(rr==p)
                rr->rightChild=r->rightChild;
            else
                rr->leftChild=r->rightChild;
            delete r;
        }
    }

}
#endif //CHAPTER06_BST_H
