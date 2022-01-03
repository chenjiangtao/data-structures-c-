#include <iostream>
#include <queue>
#include "string.h"
using namespace std;
const int MAX=99999999;
typedef struct node
{
    int data;
    int index;
} Node;
/*
 *9.4.2 锦标赛排序
 * */
void TournamentSort(int nums[],int n)
{//nums[0]....nums[n-1]
    int loser=0;
    int i,j,k;
    queue<Node> q;
    Node node;
    Node node1,node2;
    int num1,num2;
    for(i=0;i<n;i++)
    {
        if(nums[i]<MAX)//不再参加排序的结点的值是MAX
        {

            node.data=nums[i];
            node.index=i;
            q.push(node);
        }

    }
    node.data=MAX;
    node.index=-1;//特殊结点#
    q.push(node);
    while(q.empty()==false)
    {
        while(q.front().index != -1) {
            node1 = q.front();
            q.pop();
            node2 = q.front();
            q.pop();
            if(q.empty()==true)
                break;
            if(node2.data ==MAX)//node2 #
            {
                q.push(node1);
                q.push(node2);
            }
            else {
                if (node1.data < node2.data)
                    q.push(node1);
                else
                    q.push(node2);
            }
            // cout<<"node1.data="<<node1.data<<",node2.data="<<node2.data<<endl;
        }
        if(q.empty()== false&&q.front().index == -1)
        {
            node2 = q.front();
            q.pop();
            q.push(node2);
        }
    }
    cout<<node1.data<<"   ";
    nums[node1.index]=MAX;//修改了原始数据
    //有待改进
}
void InsertSort(int R[],int n)
{
    int i;
    int temp;
    int j;
    cout<<"排序前:"<<endl;
    for(i=0;i<n;i++)
        cout<<R[i]<<"  ";
    cout<<endl;
    //每次插入1个元素，
    //插入n-1次
    //R[i]......R[n-1]
    for(i=1;i<n;i++)
    {
        temp=R[i];
        //temp需要被插入到R[0]....R[i-1]
        j=i-1;
        while(j>=0 && R[j]>temp)
        {//把所有比temp大的元素
            // 往后平移1个单位
            R[j+1]=R[j];
            j--;//j==-1
        }
        R[j+1]=temp;
    }
    cout<<"排序后:"<<endl;
    for(i=0;i<n;i++)
        cout<<R[i]<<"  ";
    cout<<endl;
}
//补充算法,二分插入排序
//折半插入排序,n-1次
//每次从R[i].....R[n-1]
//temp=R[i]
//temp需要插入到R[0]....R[i-1]
//R[0]....R[i-1]有序子序列，所以可以用
//left指针指出的位置就是temp应该放的位置
//R[left]....R[i-1]都需要往后平移1个单位
void BinaryInsertSort(int R[],int n)
{
    int i;
    int temp;
    int j,left,right,mid;
    cout<<"排序前:"<<endl;
    for(i=0;i<n;i++)
        cout<<R[i]<<"  ";
    cout<<endl;
    for(i=1;i<n;i++)
    {
        //R[i].....R[n-1]
        temp=R[i];
        left=0;
        right=i-1;
        while(left<=right)
        {
            mid=(left+right)/2;
            if(temp<R[mid])
                right=mid-1;
            else //temp>=R[mid]
                left=mid+1;
        }
        //算法停下来的时候
        //left指针指向的位置，就是temp应该插入的位置
        //R[left]....R[i-1]后移动
        for(j=i-1;j>=left;j--)
            R[j+1]=R[j];
        R[left]=temp;
    }
    cout<<"排序后:"<<endl;
    for(i=0;i<n;i++)
        cout<<R[i]<<"  ";
    cout<<endl;
}
void ShellInsert(int R[],int gap,int n)
{
    int i,j,temp;
    //R[gap]-->R[0]
    //R[i]-->R[i-gap], R[i-2gap]....
    for(i=gap;i<n;i++)
    {
        temp=R[i];
        j=i-gap;//j=0,1,...gap-1
        while(j>=0 && R[j]>temp)
        {
            R[j+gap]=R[j];//往后移动1个单位 平移
            j=j-gap;//j--
        }
        R[j+gap]=temp;
        // data[     data[i-gap]
    }
}

int Partition(int R[],int left,int right)
{
    int pivot=R[left];
    int i,j;
    i=left,j=right;
    while(i<j)
    {//i>=j i==j找到了pivot应该存放的位置
        while(i<j&&R[j]>pivot)
            j--;
        R[i]=R[j];
        while(i<j&&R[i]<=pivot)
            i++;
        R[j]=R[i];
    }
    R[i]=pivot;
    return i;//i==j
}
void QSort(int R[],int left,int right)
{
    int pos,i;
    if(left<right)
    {
        pos=Partition(R,left,right);
        QSort(R,left,pos-1);
        QSort(R,pos+1,right);
    }


}
void ShellSort(int R[],int n)
{
    int gap,i;
    gap=n/2;
    while(gap>=1)
    {
        ShellInsert(R,gap,n);
        gap=gap/2;
    }
    cout<<"排序后:"<<endl;
    for(i=0;i<n;i++)
        cout<<R[i]<<"  ";
    cout<<endl;
}
void BubbleSort(int a[],int n)
{
    int i,j,temp;
    bool swap;//
    for(i=0;i<n-1;i++)//n-1次冒泡排序
    {
        swap= false;
        for(j=0;j<n-i-1;j++)//j=n-2   j+1=n-1
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                swap=true;
            }
        }
        if(swap==false)
            break;
    }
    cout<<"冒泡排序后:"<<endl;
    for(i=0;i<n;i++)
        cout<<a[i]<<"  ";
    cout<<endl;
}
//选择排序
void SelectSort(int a[],int n)
{
    int i;//n-1
    int j,min;
    int temp;
    //a[0]..........a[n-1]
    // a[1].........a[n-1]
    //   a[2].......a[n-1]
    //
    //       a[n-2].a[n-1]
    for(i=0;i<n-1;i++)//n-1
    {
        min=i;
        for(j=i+1;j<n;j++)
            if(a[j]<a[min])
                min=j;
        if(min!=i){
            temp=a[i];
            a[i]=a[min];
            a[min]=temp;
        }
    }
}
/*
 * 9.4.3堆排序
 * */
void SiftDown(int a[],int start,int n)
{
    if(n<=1)
        return;
    int i=start;
    int j=2*i+1;//i-->2*i+1, 2*i+2
    int temp=a[i];
    while(j<n)//j这个编号存在,结点存在
    {
        if(j+1<n && a[j+1]>a[j])
            j=j+1;
        if(a[j]>temp)
        {
            a[i]=a[j];
            i=j;
            j=2*i+1;
        }
        else
            break;

    }
    a[i]=temp;
    /* cout<<"n="<<n<<endl;
     for(i=0;i<n;i++)
         cout<<a[i]<<"  ";
     cout<<"----------------------"<<endl;*/
}
void HeapSort(int a[],int n)
{
    int m;
    int temp;
    for(m=n;m>0;m--)
    {
        temp=a[0];
        a[0]=a[m-1];
        a[m-1]=temp;
        SiftDown(a,0,m-1);

        /* SiftDown(a,0,m);
          temp=a[0];
           a[0]=a[m-1];
           a[m-1]=temp;*/
    }
}
void CreateHeap(int a[],int n)
{
    int i;
    //int  a[n],  a[0].......a[n-1]
    i=(n-2)/2;
    for(;i>=0;i--)
        SiftDown(a,i,n);//i=4,3,2,1,0
}
void Merge(int nums[],int i1,int j1,int i2,int j2)
{   //nums[i1]....nums[j1]
    //nums[i2]....nums[j2]
    if(i1>j1||i2>j2)
        return;
    int k1,k2;
    int i;
    vector<int> a;
    for(k1=i1,k2=i2;k1<=j1&&k2<=j2;)
    {
        if(nums[k1]<=nums[k2])
            a.push_back(nums[k1++]);
        else
            a.push_back(nums[k2++]);
    }
    while(k1<=j1)
        a.push_back(nums[k1++]);
    while(k2<=j2)
        a.push_back(nums[k2++]);
    for(i=0;i<a.size();i++)
        nums[i1+i]=a[i];//拷贝回去nums
}
void MergeSort(int nums[],int start,int end)
{
    if(start>=end)
        return;
    int mid=(start+end)/2;
    MergeSort(nums,start,mid);
    MergeSort(nums,mid+1,end);
    Merge(nums,start,mid,mid+1,end);
}
/*
 * 9.6基数排序
 * */
//arrays[i]=3456
//arrays[i]=746
int findMax(int arrays[],int L,int R)
{
    //如果该数组只有一个数，那么最大的就是该数组第一个值了
    if (L == R)
        return arrays[L];
    else
    {
        int a = arrays[L];
        int b = findMax(arrays, L + 1, R);//找出整体的最大值
        if (a > b)
            return a;
        else
        {
            return b;
        }
    }
}
/*
 * 代码不唯一
 * 桶子  用数组，还是链表
 * n*10
 * */
void radixSort(int arrays[],int n)
{
    int max = findMax(arrays, 0,n - 1);
    //需要遍历的次数由数组最大值的位数来决定
    for (int i = 1; max / i > 0; i = i * 10)
    {
        int buckets[n][10];
        //获取每一位数字(个、十、百、千位...分配到桶子里)
        memset(buckets,0,sizeof(buckets));//【重点】一定要memset 一定要memset 否则会内存泄漏(Segmentation fault)
        for (int j = 0; j < n; j++)
        {
            int num = (arrays[j] / i) % 10;
            //将其放入桶子里
            buckets[j][num] = arrays[j];
        }
        //回收桶子里的元素
        int k = 0;
        //有10个桶子
        for (int j = 0; j < 10; j++)
        {
            //对每个桶子里的元素进行回收
            for (int l = 0; l < n; l++)
            {
                //如果桶子里面有元素就回收(数据初始化会为0)
                if (buckets[l][j] != 0)
                {
                    arrays[k++] = buckets[l][j];
                }
            }
        }
    }
}
/*
 * 9.9 综合案例 比赛排名问题
 * */
int main() {
    std::cout << "Hello, World!" << std::endl;
    int data[10]={49,38,65,97,76,13,27,50,35,22};
    CreateHeap(data,10);
    HeapSort(data,10);
    int i;
    cout<<"排序后:"<<endl;
    for(i=0;i<10;i++)
        cout<<data[i]<<"  ";
    cout<<endl;
    return 0;
}