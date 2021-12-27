//
// Created by user on 2020/9/13.
//

#ifndef CHAPTER06_HUFFMANTREE_H
#define CHAPTER06_HUFFMANTREE_H
#include<iostream>
#include<cstdlib>
using namespace std;
typedef int DataType;
class HTreeNode
{
    friend class HuffmanTree;
    DataType data;
    HTreeNode* leftChild;
    HTreeNode* rightChild;
};
class HuffmanTree{
    HTreeNode* root;
public:
    HuffmanTree(){
    }
    void CreateHuffman(DataType a[],int n);
    void HuffmanCoding();
    void HuffmanCoding(HTreeNode* FBH,int len);
    HTreeNode* GetRoot(){
        return root;
    }
};
void HuffmanTree::CreateHuffman(DataType a[],int n)
{
    HTreeNode **b,*q;
    b=new HTreeNode*[n];
    int i,j;
    for(i=0;i<n;i++)
    {
        b[i]=new HTreeNode();
        b[i]->data=a[i];
        b[i]->leftChild=NULL;
        b[i]->rightChild=NULL;
    }
    for(i=1;i<n;i++)
    {
        int k1=-1;
        int k2;
        for(j=0;j<n;j++)
        {
            if(b[j]!=NULL&&k1==-1)
            {
                k1=j;//k1指向第一个非空结点
                continue;
            }
            if(b[j]!=NULL)
            {
                k2=j;//k2指向的是k1右边的第一个非空结点
                break;
            }
        }
        //k1,k2所指向的结点的值大小要确保
        //b[k1]<b[k2]
        for(j=k2;j<n;j++)
        {
            if(b[j]!=NULL)
            {
                if(b[j]->data<b[k1]->data)
                {
                    k2=k1;//k2指向第二小
                    k1=j;//k1指向最小
                }
                else if(b[j]->data<b[k2]->data)
                    k2=j;
            }
        }
        q=new HTreeNode();
        q->data=b[k1]->data+b[k2]->data;
        q->leftChild=b[k1];
        q->rightChild=b[k2];
        b[k1]=q;
        b[k2]=NULL;//
    }
    delete[] b;
    root=q;
}
void HuffmanTree::HuffmanCoding(HTreeNode* FBT,int len)
{
    static int a[10];
    if(FBT!=NULL)
    {
        if(FBT->leftChild==NULL&&FBT->rightChild==NULL)
        {
            cout<<"结点的权值为"<<FBT->data<<"的编码";
            for(int i=0;i<len;i++)
                cout<<a[i]<<" ";
            cout<<endl;
        }
        else
        {
            a[len]=0;
            HuffmanCoding(FBT->leftChild,len+1);
            a[len]=1;
            HuffmanCoding(FBT->rightChild,len+1);
        }
    }
}

#endif //CHAPTER06_HUFFMANTREE_H
