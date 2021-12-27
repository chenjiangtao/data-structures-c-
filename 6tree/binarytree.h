//
// Created by user on 2020/9/6.
//
#ifndef CHAPTER06_BINARYTREE_H
#define CHAPTER06_BINARYTREE_H
#include<iostream>
#include<cstdlib>
#include<map>
#include<queue>
#include<math.h>
#include <stack>
using namespace std;
typedef int DataType;
const int RefValue=-1;
const int MaxSize=100;
//结点类
class BinTreeNode
{
    friend class BinaryTree;
    DataType data;
    BinTreeNode *leftChild,*rightChild;
};
struct VistedNode
{
    BinTreeNode* node;
    bool vistedRightChild=false;
};
/*
 * C++ 二叉树参考代码
 * */
class BinaryTree
{
private:
    BinTreeNode* root;
public:
    BinaryTree():root(NULL){
    }
    BinaryTree(BinaryTree &s);
    ~BinaryTree()
    {
        destroy(root);
    }
    void CreateBinTree(BinTreeNode* &subTree);
    void CreateBinTree();
    bool IsEmpty()
    {
        return root==NULL?true:false;
    }
    BinTreeNode* Find(DataType& item);
    void InOrder();
    void InOrder(BinTreeNode* subTree);
    void PreOrder();
    void PreOrder(BinTreeNode* subTree);
    void PostOrder();
    void PostOrder(BinTreeNode* subTree);
    int Count(BinTreeNode* subTree);
    int Count();
    int Height(BinTreeNode* subTree);
    int Height();
    void Copy();
    BinTreeNode* Copy(BinTreeNode*& Tree);
    void destroy(BinTreeNode*& Tree);
    void PrintTree();//打印输出二叉树
    void LevelOrder();//非递归的层序遍历
    void MiddleOrder();//非递归的中序遍历
    void FirstOrder();//非递归的前序遍历
    void LastOrder();//非递归的后序遍历
    void NonRecursivePostOrder();
    void AllPath();
};
void BinaryTree::InOrder()
{
    InOrder(root);
}
void BinaryTree::InOrder(BinTreeNode* subTree)
{
    if(subTree!=NULL)
    {
        InOrder(subTree->leftChild);
        cout<<subTree->data<<" ";
        InOrder(subTree->rightChild);
    }
}
void BinaryTree::PreOrder()
{
    PreOrder(root);
}
void BinaryTree::PreOrder(BinTreeNode* subTree)
{
    if(subTree!=NULL)
    {
        cout<<subTree->data<<" ";
        PreOrder(subTree->leftChild);
        PreOrder(subTree->rightChild);
    }
}
void BinaryTree::PostOrder()
{
    PostOrder(root);
}
void BinaryTree::PostOrder(BinTreeNode* subTree)
{
    if(subTree!=NULL)
    {

        PostOrder(subTree->leftChild);
        PostOrder(subTree->rightChild);
        cout<<subTree->data<<" ";
    }
}
int BinaryTree::Count()
{
    return Count(root);
}
int BinaryTree::Count(BinTreeNode* subTree)
{
    if(subTree==NULL) return 0;
    else
        return Count(subTree->leftChild)+Count(subTree->rightChild)+1;
}
int  BinaryTree::Height(BinTreeNode* subTree)
{
    if(subTree==NULL)
        return 0;
    else
    {
        int dep1=Height(subTree->leftChild);
        int dep2=Height(subTree->rightChild);
        if(dep1>dep2)
            return dep1+1;
        else
            return dep2+1;
    }
}
BinaryTree::BinaryTree(BinaryTree& s)
{
    root=Copy(s.root);
}
BinTreeNode* BinaryTree::Copy(BinTreeNode*& Tree)
{
    if(Tree==NULL)
        return NULL;
    else
    {
        BinTreeNode* temp=new BinTreeNode();
        temp->data=Tree->data;
        temp->leftChild=Copy(Tree->leftChild);
        temp->rightChild=Copy(Tree->rightChild);
        return temp;
    }

}
void BinaryTree::CreateBinTree(BinTreeNode*& subTree)
{
    DataType item;
    cout<<"请输入树根的值:"<<endl;
    cin>>item;
    if(item!=RefValue)
    {
        subTree=new BinTreeNode();
        if(subTree==NULL)
        {
            cout<<"存储分配失败"<<endl;
            exit(1);
        }
        subTree->data=item;
        CreateBinTree(subTree->leftChild);
        CreateBinTree(subTree->rightChild);
    }
    else
        subTree=NULL;
}
void BinaryTree::CreateBinTree()
{
    CreateBinTree(root);
}
void BinaryTree::destroy(BinTreeNode*& Tree)
{
    if(Tree==NULL)
        return;
    destroy(Tree->leftChild);
    destroy(Tree->rightChild);
    delete Tree;
    Tree==NULL;
}
//层序遍历算法
void BinaryTree::LevelOrder()
{
    queue<BinTreeNode*> myqueue;
    BinTreeNode* current;
    myqueue.push(root);//初始化
    while(myqueue.empty()==false)
    {
        current=myqueue.front();
        myqueue.pop();
        cout<<current->data<<"  ";
        if(current->leftChild!=NULL)
            myqueue.push(current->leftChild);
        if(current->rightChild!=NULL)
            myqueue.push(current->rightChild);
    }
}
/*
void BinaryTree::PrintTree()
{
    map<int,int> nodes;
    int i=1;
    DataType data;
    queue<BinTreeNode*> myqueue;
    BinTreeNode* current;
    myqueue.push(root);
    while(myqueue.empty()==false)
    {
        current=myqueue.front();
        if(current!=NULL)
        {
            data=current->data;
            nodes.insert(pair<int,int>(i,data));
        } else
            nodes.insert(pair<int,int>(i,-1));
         i++;
        myqueue.pop();
        if(current!=NULL) {
            myqueue.push(current->leftChild);
            myqueue.push(current->rightChild);
        }
    }
    map<int,int>::iterator iter=nodes.begin();
    int No;
    int lines=0;
    int lineNumbers=1;
    int MinSpace=3;
    int TotalWidth=pow(2,Height(root)-1)*MinSpace;
    int NodeWidth=TotalWidth/lineNumbers;
    int SpaceNumber;
    while(iter!=nodes.end())
    {
        No=iter->first;
        if(No==pow(2,lines))
        {
            for(i=0;i<NodeWidth/2;i++)
                cout<<" ";
        } else
        {
            for(i=0;i<NodeWidth;i++)
                cout<<" ";
        }
        if(iter->second!=-1)
           cout<<iter->second;
        iter++;
        if(floor(log10(No+1)/log10(2))>floor(log10(No)/log10(2)))
        {
            lines++;
            lineNumbers=pow(2,lines);
            NodeWidth=TotalWidth/lineNumbers;
            cout<<endl;
        }
    }
}*/
//非递归的中序遍历
void BinaryTree::MiddleOrder()
{
    stack<BinTreeNode*>  S;
    BinTreeNode* p = root;   //初始化
    do{
        while(p != NULL )
        {
            S.push(p);
            p = p->leftChild;//往左前进
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
void BinaryTree::FirstOrder()
{
    stack<BinTreeNode*>  S;
    BinTreeNode* p = root;   //初始化
    do{
        while(p != NULL )
        {   //立刻输出p所指向的当前结点
            cout<< p->data << endl;
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
    //p==NULL   S.empty()==true
}
//非递归的前序遍历算法
/*
void BinaryTree::FirstOrder()
{
    stack<BinTreeNode*>  S;
    BinTreeNode* p = root;   //初始化
    S.push(p);
    while(!S.empty())
    {

    }
}
 */
//非递归的后序遍历
void BinaryTree::LastOrder()
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
        else//如果弹出的结点是树叶或者 弹出的结点右儿子已经被访问过
        {
            S.pop();
            cout<<vd.node->data<<"--";
            p=NULL;
        }

    }
}
void BinaryTree::NonRecursivePostOrder()
{
    BinTreeNode* cur=root;
    BinTreeNode* parent=NULL;
    BinTreeNode* Stack[MaxSize];//数组
    int top=0;//栈指针,数组下标
    int i;
    Stack[top++]=NULL;
    if(root!=NULL)
    {
        do{
            while(cur!=NULL)
            {

                Stack[top++]=cur;
                parent=cur;
                if(cur->leftChild==NULL)
                    cur=cur->rightChild;
                else
                    cur=cur->leftChild;
            }//cur==NULL
            while(parent!=NULL&&cur==parent->rightChild)
            {
                cout<<parent->data<<"--";
                top--;
                cur=Stack[top];
                parent=Stack[top-1];
            }
            if(parent!=NULL&&cur==parent->leftChild)
                cur=parent->rightChild;
            else
                top=-1;
        }
        while(top>0);

    }
}
void BinaryTree::AllPath()
{
    BinTreeNode* cur=root;
    BinTreeNode* parent=NULL;
    BinTreeNode* Stack[MaxSize];
    int top=0;
    int i;
    Stack[top++]=NULL;
    if(root!=NULL)
    {
        do{

            while(cur!=NULL)
            {

                Stack[top++]=cur;
                parent=cur;
                if(cur->leftChild==NULL)
                    cur=cur->rightChild;
                else
                    cur=cur->leftChild;
            }
            if(Stack[top-1]->leftChild==NULL
               &&Stack[top-1]->rightChild==NULL)
            {
                for(i=top-1;i>1;i--)
                    cout<<Stack[i]->data<<"-->";
                cout<<Stack[1]->data<<endl;
            }
            while(parent!=NULL&&cur==parent->rightChild)
            {
                top--;
                cur=Stack[top];
                parent=Stack[top-1];
            }
            if(parent!=NULL&&cur==parent->leftChild)
                cur=parent->rightChild;
            else
                top=-1;
        }
        while(top>0);

    }
}
void BinaryTree::PrintTree()
{
    int* nodes;
    int height=Height(root);
    int TotalNodes=pow(2,Height(root));
    cout<<"TotalNodes="<<TotalNodes<<endl;
    nodes=new int[TotalNodes];
    int i=1;
    DataType data;
    queue<BinTreeNode*> myqueue;
    BinTreeNode* current;
    myqueue.push(root);
    while(myqueue.empty()==false)
    {
        current=myqueue.front();
        if(current!=NULL)
        {
            data=current->data;
            nodes[i]=data;
        } else
            nodes[i]=-1;
        i++;
        myqueue.pop();
        if(current!=NULL) {
            myqueue.push(current->leftChild);
            myqueue.push(current->rightChild);
        }
    }
    TotalNodes=i-1;
    int No;
    int lines=0;
    int lineNumbers=1;
    int MinSpace=3;
    int TotalWidth=pow(2,Height(root)-1)*MinSpace;
    int NodeWidth=TotalWidth/lineNumbers;
    int SpaceNumber;
    i=1;
    int j=0;
    int k;
    while(i<=TotalNodes)
    {
        No=i;
        if(No>1&&No==pow(2,lines))
        {
            for(j=i;j<=TotalNodes;j++)
            {
                if(j==pow(2,lines))
                {
                    for(k=0;k<NodeWidth/2+1;k++)
                        cout<<" ";
                }
                else
                {
                    for(k=0;k<NodeWidth-1;k++)
                        cout<<" ";
                }
                if(nodes[j]!=-1)
                {
                    if(j%2==0)
                        cout<<"/";
                    else
                        cout<<"\\";
                }
                if(floor(log10(j+1)/log10(2))>floor(log10(j)/log10(2))||j==TotalNodes)
                {
                    cout<<endl;
                    break;
                }
            }
        }

        if(No==pow(2,lines))
        {
            for(j=0;j<NodeWidth/2;j++)
                cout<<" ";
        } else
        {
            for(j=0;j<NodeWidth;j++)
                cout<<" ";
        }
        if(nodes[i]!=-1)
            cout<<nodes[i];
        i++;
        if(floor(log10(No+1)/log10(2))>floor(log10(No)/log10(2)))
        {
            lines++;
            lineNumbers=pow(2,lines);
            NodeWidth=TotalWidth/lineNumbers;
            cout<<endl;
        }
    }
}
#endif //CHAPTER06_BINARYTREE_H