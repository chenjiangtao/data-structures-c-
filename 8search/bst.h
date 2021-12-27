//
// Created by user on 2020/10/5.
//
#ifndef CHAPTER08_BST_H
#define CHAPTER08_BST_H
#include<iostream>
#include<cstdlib>
using namespace std;
typedef int DataType;
//struct
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
    BinTreeNode* Find(DataType x);

public:
    BST():root(NULL){
    }
    BST(DataType a[],int n)
    {
        BST(root,a,n);
    }
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
};
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
{//算法一样的
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
BinTreeNode* BST::Find(DataType x)
{
    BinTreeNode* p=root;
    while(p!=NULL)//p==NULL,算法结束
    {
        if(p->data==x)//成功
            return p;
        if(x<p->data)
            p=p->leftChild;
        else
            p=p->rightChild;
    }
    return NULL;
}
//插入结点
//如果树是一颗空树，直接把结点当作树根
//否则，比较待插入x和ptr->data
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

}
BST::BST(BinTreeNode* ptr,DataType a[],int n)
{
    ptr=NULL;
    for(int i=0;i<n;i++)
        Insert(a[i],ptr);
}
//delete
//二叉排序树，删除值为x结点
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
        if(p->leftChild==NULL&&p->rightChild==NULL)
        {
            if(p==parent->leftChild)
                parent->leftChild=NULL;
            else
                parent->rightChild=NULL;
            return true;
        }
        //如果被删除结点p没有左儿子
        if(p->leftChild==NULL)
        {
            if(parent==NULL)
                ptr=p->rightChild;
            else if(parent->leftChild==p)
                parent->leftChild=p->rightChild;
            else
                parent->rightChild=p->rightChild;
            delete p;
            return true;
        }
        else if(p->rightChild==NULL)//p无右子女
        {
            if(parent==NULL)
                ptr=p->leftChild;
            else if(parent->leftChild==p)
                parent->leftChild=p->leftChild;
            else
                parent->rightChild=p->leftChild;
            delete p;
        }
        else //p既有左子女 又有右子女
        {
            BinTreeNode* rr=p,*r=p->leftChild;
            while(r->rightChild)
            {
                rr=r;
                r=r->rightChild;
            }
            p->data=r->data;
            if(rr==p)
                rr->leftChild=r->leftChild;
            else
                rr->rightChild=r->leftChild;
            delete r;
            return true;
        }
    }

}

#endif //CHAPTER08_BST_H
