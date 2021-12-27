//
// Created by user on 2020/10/18.
//
#ifndef CHAPTER09_RECORDLIST_H
#define CHAPTER09_RECORDLIST_H
#include<iostream>
#include<cstdlib>
const int DefaultSize=100;
class Element
{
    int key;
    friend class recordList;
};
class recordList{
private:
    Element* R;
    int MaxSize;
    int CurrentSize;
    void ShellInsert(int gap);
    void QSort(int left,int right);
    int Partition(int low,int high);
    void MSort(recordList SR,recordList& TR1,int s,int t);
public:
    recordList(int MaxSz=DefaultSize)
    {
        R=new Element[MaxSz];
        MaxSize=MaxSz;
        CurrentSize=0;
    }
    ~recordList(){
        delete[] R;
    }
    int getKey(int i)
    {
        return R[i].key;
    }
    void setKey(int i,int value)
    {
        R[i].key=value;
    }
    void swap(Element& x,Element& y)
    {
        Element temp=x;
        x=y
        y=temp;
    }
    void InsertionSort();
    void BinaryInsertSort();
    void ShellSort();
    void BubbleSort();
    void QuickSort();
    void SelectSort();
    void merge(recordList SR,recordList &TR,int s,int m,int n);
    void MergeSort(recordList& L)

};
void recordList::InsertionSort()
{
    int i,j;
    for(i=1;i<CurrentSize;i++)
    {
        Element temp=R[i];
        for(j=i-1;j>=0;j--)
            if(temp.key<R[j].key)
                R[j+1]=R[j];
            else
                R[j+1]=temp;
    }
}
void recordList::BinaryInsertSort()
{
    int left,right;
    for(int i=1;i<CurrentSize;i++)
    {
        left=0,right=i-1;
        Element temp=R[i];
        while(left<=right)
        {
            int middle=(left+right)/2;
            if(temp.key<R[middle].key)
                right=middle-1;
            else
                left=middle+1;
        }
        for(int k=i-1;k>=left;k--)
            R[k+1]=R[k];
        R[left]=temp;
    }
}
void recordList::ShellSort()
{
    int gap=CurrentSize/2;
    while(gap)
    {
        ShellInsert(gap);
        gap=(int)(gap/2);
    }
}
void recordList::ShellInsert(int gap)
{
    for(int i=gap;i<CurrentSize;i++)
    {
        Element temp=R[i];
        int j=i;
        while(j>=gap && temp.key<R[j-gap].key)
        {
            R[j]=R[j-gap];
            j=j-gap;
        }
        R[j]=temp;
    }
}
void recordList::BubbleSort()
{
    int pass=1;
    int NoSwap=0;
    Element temp;
    while(pass<CurrentSize &&!NoSwap)
    {
        NoSwap=1;
        for(int j=CurrentSize-1;j>=pass;j--)
            if(R[j-1].key>R[j].key)
            {
                temp=R[j-1];
                R[j-1]=R[j];
                R[j]=temp;
                NoSwap=0;
            }
        pass++;
    }
}
void recordList::QSort(int left,int right)
{
    if(left<right)
    {
        int pivotpos=Partition(left,right);
        QSort(left,pivotpos-1);
        QSort(pivotpos+1,right);
    }

}
void recordList::QuickSort()
{
    QSort(0,CurrentSize-1);
}
int recordList::Partition(int low,int high)
{
    Element pivot=R[low];
    while(low<high)
    {
        while(low<high && R[high].key>=pivot.key)
            high--;
        R[low]=R[high];
        while(low<high&&R[low].key<=pivot.key)
            low++;
        R[high]=R[low];
    }
    R[low]=pivot;
    return low;
}
void recordList::SelectSort()
{
    Element temp;
    for(int i=0;i<CurrentSize;i++)
    {
        int k=i;
        for(int j=i+1;j<CurrentSize;j++)
            if(R[j].key<R[k].key)
                k=j;
        if(k!=i)
        {
            temp=R[i];
            R[i]=R[k];
            R[k]=temp;
        }
    }
}
void recordList::merge(recordList SR,recordList &TR,int s,int m,int n)
{
    int i=s,j=m+1,k=s;
    while(i<=m&&j<=n)
    {
        if(SR.R[i].key<=SR.R[j].key)
        {
            TR.R[k]=SR.R[i];
            i++;
            k++;
        }
        else
        {
            TR.R[k]=SR.R[j];
            j++;
            k++;
        }
    }
    while(i<=m)
    {
        TR.R[k]=SR.R[i];
        i++;
        k++;
    }
    while(j<=t)
    {
        TR.R[k]=SR.R[j];
        j++;
        k++;
    }
}
void recordList::MSort(recordList SR,recordList& TR1,int s,int t)
{
    int middle;
    recordList TR2;
    if(s==t)
        TR1.R[s]=SR.R[s];
    else
    {
        middle=(s+t)/2;
        MSort(SR,TR2,s,middle);
        MSort(SR,TR2,middle+1,t);
        merge(TR2,TR1,s,middle,t);
    }
}
void recordList::MergeSort(recordList& L)
{
    MSort(L,L,0,L.CurrentSize-1);
}

#endif //CHAPTER09_RECORDLIST_H
