#include <iostream>
#include<string>
#include<cstring>
using namespace std;
const int max_size=20;//쳲���������ĳ���

/*����һ��쳲���������*/
void Fibonacci(int * F)
{
    F[0]=0;
    F[1]=1;
    for(int i=2;i<max_size;++i)
        F[i]=F[i-1]+F[i-2];
}

/*����쳲��������ҷ�*/
int Fibonacci_Search(int *a, int n, int key)  //aΪҪ���ҵ�����,nΪҪ���ҵ����鳤��,keyΪҪ���ҵĹؼ���
{
    int low=0;
    int high=n-1;

    int F[max_size];
    Fibonacci(F);//����һ��쳲���������F

    int k=0;
    while(n>F[k]-1)//����nλ��쳲��������е�λ��
        ++k;

    int  * temp;//������a��չ��F[k]-1�ĳ���
    temp=new int [F[k]-1];
    memcpy(temp,a,n*sizeof(int));

    for(int i=n;i<F[k]-1;++i)
        temp[i]=a[n-1];

    while(low<=high)
    {
        int mid=low+F[k-1]-1;
        if(key<temp[mid])
        {
            high=mid-1;
            k-=1;
        }
        else if(key>temp[mid])
        {
            low=mid+1;
            k-=2;
        }
        else
        {
            if(mid<n)
                return mid; //�������˵��mid��Ϊ���ҵ���λ��
            else
                return n-1; //��mid>=n��˵������չ����ֵ,����n-1
        }
    }
    delete [] temp;
    return -1;
}
typedef struct node
{
    string name;
    int age;
    char sex;
    string address;
    int key;//id
}Node;
int SimpleSearch(int data[],int n,int k)
{
    int i=0;
    for(;i<n;i++)
        if(data[i]==k)
            return i;
    return -1;
}
int BinarySearch(int data[],int n,int k)
{
    int low=0;
    int high=n-1;
    int mid;
    //���k����data[0]...data[n-1]
    if(k<data[0]||k>data[n-1])
        return -1;//ֱ�ӷ���ʧ��
    //���k>data[0]
    //k<data[n-1]
    // data[0].....k......data[n-1]
    while(low<=high)//low>high
    {
        mid=(low+high)/2;
        if(k==data[mid])
            return mid;
        if(k<data[mid])
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}
//�ݹ��Ķ��ֲ����㷨
int BinarySearch2(int data[],int low,int high,int k)
{
    if(low>high)
        return -1;
    int mid=(low+high)/2;
    if(k==data[mid])
        return mid;
    if(k<data[mid])
        return BinarySearch2(data,low,mid-1,k);
    else
        return BinarySearch2(data,mid+1,high,k);
}

int LIS(int a[],int b[],int n)
{

    int i;
    int j=0;
    int k;
    b[0]=a[0];
    i=1;
    while(i<n)
    {
        if(a[i]>b[j])
        {
            b[++j]=a[i];
            i++;

        }
        else if(a[i]==b[j])
        {
            i++;
        }
        else//if a[i]<b[j]
        {
            k=j;
            while(k>=0&&b[k]>=a[i])
                k--;
            b[k+1]=a[i];
            i++;
        }
    }
    for(k=0;k<=j;k++)
        cout<<b[k]<<" ";
    return j+1;
}
/*�û�������ַ���inputword,�͵��ʱ��
 * ��ĳ���ؼ���wordslist_item�Ƚ�
 * �ǲ���inputword��wordslist_item��һ����ĸ
 * ������ĸ��ȫ��ͬ
*/
bool IsShorter(string inputword,string wordslist_item)
{
    int i,j;
    int n=inputword.length();
    if(n!=wordslist_item.length()-1)
        return false;
    i=0;
    while(i<n&&inputword[i]==wordslist_item[i])
        i++;
    if(i==n)
        return true;
    j=i+1;
    while(i<n&&inputword[i]==wordslist_item[j])
    {
        i++;
        j++;
    }
    if(i==n&&j==wordslist_item.length())
        return true;
    else
        return false;
}
/*�û�������ַ���inputword,�͵��ʱ��
 * ��ĳ���ؼ���wordslist_item�Ƚ�
 * �ǲ���inputword��wordslist_item��һ����ĸ
 * ������ĸ��ȫ��ͬ
*/
bool IsLonger(string inputword,string wordslist_item)
{
    int i,j;
    int n=inputword.length();
    if(n!=wordslist_item.length()+1)
        return false;
    i=0;
    while(i<wordslist_item.length()&&inputword[i]==wordslist_item[i])
        i++;
    if(i==wordslist_item.length())
        return true;
    j=i+1;
    while(i<n&&inputword[j]==wordslist_item[i])
    {
        i++;
        j++;
    }
    if(j==n&&i==wordslist_item.length())
        return true;
    else
        return false;
}
/*�û�������ַ���inputword,�͵��ʱ��
 * ��ĳ���ؼ���wordslist_item�Ƚ�
 * �ǲ���inputword��wordslist_itemֻ��һ����ĸ��ͬ
 * ������ĸ��ȫ��ͬ
*/
bool IsMissing(string inputword,string wordslist_item)
{
    if(inputword.length()!=wordslist_item.length())
        return false;
    int i;
    int n=inputword.length();
    i=0;
    while(i<n&&inputword[i]==wordslist_item[i])
        i++;
    if(i==n)
        return false;
    i++;
    while(i<n&&inputword[i]==wordslist_item[i])
        i++;
    if(i==n)
        return true;
    else
        return false;
}
bool IsEqual(string inputword,string wordslist_item)
{

    if(inputword.length()!=wordslist_item.length())
        return false;
    int i=0;
    int n=inputword.length();
    while(i<n && inputword[i]==wordslist_item[i])
       i++;
    if(i==n)
        return true;
    else
        return false;
}
string& trim(string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}
int stick[100]; //��¼ÿ��ľ���ĳ���
bool use[100];//��¼ľ����ʹ�õ����
int len,n;
void sort(int nums[],int n)
{
    int max;
    int i,j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        max=i;
        for(j=i+1;j<n;j++)
        {
            if(nums[j]>nums[max])
                max=j;
        }
        if(max!=i)
        {
            temp=nums[i];
            nums[i]=nums[max];
            nums[max]=temp;
        }
    }
}
bool dfs(int unused,int left, int preno)
{
    int i;
    if(unused==0&&left==0)
        return true;
    if(left==0)
    {
        left=len;
        preno=0;
    }
    if(preno!=0)
        preno++;
    for(i=preno;i<n;i++)
    {
        if(i>0&&use[i-1]==false && stick[i]==stick[i-1])
        {
            use[i]=false;
            continue;
        }
        if(use[i]==false&&stick[i]<=left)
        {
            use[i]=true;
            if(dfs(unused-1,left-stick[i],i)==true)
                return true;
            else
            {
 //�˳��ϴγ��Ե�ľ����׼��������һ��ľ��
                use[i]=false;
 //�����ǰ���Ե���ĳ��ԭʼľ���еĵ�һ��λ�û����һ��λ�ã�
//���ҵ�������ʧ�ܣ��򲻱��������λ���ϳ������µ�ľ��
                if(left==stick[i]||len==left)
                    return false;
            }
        }
    }
    return false;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    stick[0]=5;
    stick[1]=2;
    stick[2]=1;
    stick[3]=5;
    stick[4]=2;
    stick[5]=1;
    stick[6]=5;
    stick[7]=2;
    stick[8]=1;
    sort(stick,9);
    int sum=0;
    int i;
    n=9;
    //len ����С����ȡֵ����ľ�������һ��
    for(len=stick[0];len<=sum;len++)
    {
        for(i=0;i<n;i++)
        {
            sum=sum+stick[i];
            use[i]= false;
        }
        if(sum%len!=0)
            continue;

        if(dfs(n,len,0)== true)
        {
            cout<<"len="<<len<<endl;
            break;
        }

    }
  // LIS(a,b,11);
    /* string userinputwords;
     string correctwordlist[max_size];
     int n;
     cout<<"������һ������:"<<endl;
     cin>>userinputwords;
     cout<<"�����뵥�ʱ�ĳ���:"<<endl;
     cin>>n;
      cout<<"��ʼ���뵥�ʱ�:"<<endl;
      for(i=0;i<n;i++)
          cin>>correctwordlist[i];
      for(i=0;i<n;i++)
      {
          if(IsEqual(userinputwords,correctwordlist[i])==true)
          {
              cout<<correctwordlist[i]<<endl;
              break;
          }
      }
      if(i==n)//�Ҳ�����ȫ��ͬ�Ĺؼ���
      {
          for(i=0;i<n;i++)
          {
              if(IsShorter(userinputwords,correctwordlist[i])
                 ||IsLonger(userinputwords,correctwordlist[i])
                 ||IsMissing(userinputwords,correctwordlist[i]))
              {
                  cout<<correctwordlist[i]<<endl;
                  break;
              }
          }
          if(i==n)
              cout<<"NoAnswer"<<endl;
      }

       int n=100;
      int data[n];//������������
      Node nodes[n];
      int x;
      cin>>x;
      int i;
      for(i=0;i<n;i++)
          if(data[i]==x)
              break;*/
    return 0;
}
