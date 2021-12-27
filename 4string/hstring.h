#ifndef CHAPTER04_HSTRING_H
#define CHAPTER04_HSTRING_H
#include <iostream>
#include <cstdlib>
using namespace std;
const int MaxSize=100;
class HString
        {
    char* str;
    int size;
        public:
            HString()
            {
                str=new char[MaxSize+1];
                size=0;
            }
            HString(char* s);
            ~HString()
            {
                delete[] str;
                size=0;
            }
            int Length();
            int Compare(HString S);
            bool Concat(HString S1,HString S2);
            HString Substring(int pos,int len);
            int Index(HString T,int start);
            bool Replace(HString T,HString V);
            bool Assign(char* s);
            int Index_KMP(HString T,int pos,int next[]);
            void get_next(int next[]);

        };
HString::HString(char* s)
{
    size=strlen(s);
    str=new char[size+1];
    if(str==NULL)
    {
        cout<<"申请内存空间失败"<<endl;
        exit(0);
    }
    for(int i=0;i<=size;i++)
        str[i]=s[i];
}
bool HString::Assign(char* s)
{
    size=strlen(s);
    str=new char[size+1];
    if(str==NULL)
    {
        cout<<"申请内存空间失败"<<endl;
        return false;
    }
    else
    {
        for(int i=0;i<=size;i++)
            str[i]=s[i];
    }
}
int HString::Compare(HString S)
{
    for(int i=0;i<size&&i<S.size;i++)
        if(str[i]!=S.str[i])
            return(str[i]-S.str[i]);
        return size-S.size;
}
bool HString::Concat(HString T,HString S)
{
    int i;
    str=new char[T.size+S.size+1];
    if(str==NULL)
    {
        cout<<"申请内存空间失败"<<endl;
        return false;
    }
    size=T.size+S.size;
    for(i=0;i<T.size;i++)
    {
        str[i]=T.str[i];
    }
    for(i=0;i<S.size;i++)
    {
        str[T.size+1]=S.str[i];
    }
    str[size]='\0';
    return true;
}
HString HString::Substring(int pos,int len)
{
    HString Sub;
    if(pos<1||pos>size||len<0||len>size-pos+1)
        return NULL;
    if(Sub.str!=NULL)
        delete[] Sub.str;
    if(len==0)
    {
        Sub.str=NULL;
        Sub.size=0;
    }
    else
    {
        Sub.str=new char[len+1];
        for(int i=0;i<=len-1;i++)
            Sub.str[i]=str[pos+i-1];
        Sub.size=len;
        Sub.str[len]='\0';
    }
    return Sub;
}
/*
4.3.1 求子串的定位函数
*/
int HString::Index(HString T,int pos)
{
    int i=pos;
    int j=0;
    while(i<=size-1&&j<=T.size-1)
    {
        if(str[i]==T.str[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>T.size-1)
        return i-T.size+1;
    else
        return -1;
}
int HString::Index_KMP(HString T,int pos,int next[])
{
    int i=pos-1;
    int j=0;
    while(i<=size-1&&j<=T.size-1)
    {
        if(str[i]==T.str[j])
        {
            i++;
            j++;
        }
        else //str[i]!=T.str[j]
        {
            if(j==0) // i++,j不变
                i++;
            else    //i不变,j=next[j]
            j=next[j];
        }

    }
    if(j>=T.size)
        return i-T.size+1;
    else
        return -1;
}
voi HSting::get_next(int next[])
{
    int i=0;
    int j=-1;
    next[0]=-1;
    while(i<size-1)
    {
        if(j==-1||str[i]==str[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else
            j=next[j];
    }

}

#endif //CHAPTER04_HSTRING_H
