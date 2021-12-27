#ifndef CHAPTER04_SSTRING_H
#define CHAPTER04_SSTRING_H
#include <iostream>
#include <cstdlib>
#define MAXSTRLEN 255 //最大长度
using namespace std;
/*
 * 模仿C++类库提供的String
 * 写一个类似的字符串类
 * 实现字符串常见的一些函数,方法
 * */
class SString
{
        public:
            char str[MAXSTRLEN+1];
            int length;//字符串实际长度,字符的个数
            SString(){length=0;}
            ~SString()
            {
                //delete[] str;
                length=0;
            }
            bool Assign(char* s);//1.串赋值
            void StrCopy(SString S);//2.串复制
            bool StrEqual(SString S);//3.判断串相等
            int StrLength();//4.计算串长度
            SString Concat(SString S);//5.串连接
            SString Substring(int pos,int len);//6.从串中取子串
            SString InsStr(SString S,int pos);//7.串插入
            void DelStr(int pos,int len);//8.串删除
            bool Replace(int pos,int len,SString T);//9.串替换
            void DispStr();//10.输出串
            int Strcmp(SString S);
            int LongestString();
            //swap
        };

//1.串赋值
bool SString::Assign(char* s)
{
    int i=0;
    while(*s!='\0'&&i<MAXSTRLEN)
    {
        str[i]=*s;
        s++;
        i++;
    }
    str[i]='\0';
    length=i;
    return true;
}
//2.串复制
void SString::StrCopy(SString S)
{
    int i;
    length=S.length;
    for(i=0;i<length;i++)
        str[i]=S.str[i];
    str[length]='\0';
}
//3.判断串相等
bool SString::StrEqual(SString S)
{
    int i;
    if(length!=S.length)
        return false;
    for(i=0;i<length;i++)
        if(str[i]!=S.str[i])
            return false;
    return true;

}
//4.计算串长度
int SString::StrLength()
{
    return length;
}
//5.串连接
//有多种实现方式
SString SString::Concat(SString S)
{
   int i,j;
   SString T;
   T.length=length+S.length;
   for(i=0;i<length;i++)
       T.str[i]=str[i];
   for(j=0;j<S.length;j++)
       T.str[i++]=S.str[j];
   T.str[i]='\0';
       return T;
}
//6.从串中取子串，pos表示字符位置,从1开始
SString SString::Substring(int pos,int len)
{
    SString subs;
    int i;
    if(pos<1||pos>length||len<0||len>length-pos+1)
        return subs;
    for(i=0;i<len;i++)
    {
        subs.str[i]=str[pos+i-1];
    }
    subs.str[len]='\0';
    subs.length=len;
    return subs;
}
//7.串插入
SString SString::InsStr(SString S,int pos)
{
    SString T;
    int i,j;
    if(pos<1||pos>length+1)
        return T;
    T.length=length+S.length;
    for(i=0;i<pos-1;i++)
        T.str[i]=str[i];
    for(j=0;j<S.length;j++)
        T.str[i++]=S.str[j];
    for(j=pos-1;j<length;j++)
        T.str[i++]=str[j];
    T.str[i]='\0';
    return T;
}
//8.串删除
void  SString::DelStr(int pos,int len)
{
    int i;
    int j;
    if(pos<1||pos+len>length+1)
        return;
    i=pos-1;
    j=pos+len-1;
    while(j<length)
        str[i++]=str[j++];
    str[i]='\0';
    length=length-len;
}
//9.串替换
bool SString::Replace(int pos,int len,SString T)
{
    int i,j;
    if(pos+len>length+1)
       return false;
    if(length-len+T.length>MAXSTRLEN)
       return false;
    SString s=Substring(pos+len,length-pos-len+1);
   i=pos-1;
   for(j=0;i<T.length;j++)
       str[i++]=T.str[j];
   for(j=0;i<s.length;j++)
       str[i++]=s.str[j];
   str[i]='\0';
   length=i;
    return true;
}
//10.输出串
void SString::DispStr()
{
    int i;
    for(i=0;i<length;i++)
        cout<<str[i];
    cout<<endl;
}
/*
 * 【例4.1】假设串采用顺序存储结构进行存储，
 * 请设计一个算法Strcmp(SString S),比较S和T的大小
 * */
int SString::Strcmp(SString S)
{
    int i,len;
    if(length<=S.length)
        len=length;
    else
        len=S.length;
    for(i=0;i<len;i++)
    {
        if(str[i]<S.str[i])
            return -1;
        if(str[i]>S.str[i])
            return 1;
    }
    if(length==S.length)
        return 0;
    if(length>S.length)
        return 1;
    else
        return -1;

}
/*
 * 【例4.2】假设串采用顺序存储结构进行存储
 * 请设计一个算法，求串S中出现的第一个最长
 * 的由连续相同字符构成的子串的起始位置。
 * S="aabbbcd"
 *
 * */
int SString::LongestString()
{
    int i=0;
    int max,len;
    int pos=0;
    max=0;
    len=0;
    while(i<length-1)
    {
        if(str[i]==str[i+1])
        {
            i++;
            len++;
        }
        else
        {
            if(max<len)
            {
                max=len;
                pos=i-len;
            }
            i=i+1;
            len=0;
        }
    }
    return pos+1;
}
/*
bool SString::Concat(SString S1,SString S2)
{
    if(s1.size+s2.size<MAXSTRLEN)
    {
        for(int i=0;i<s1.size;i++)
            str[i]=s1.str[i];
        for(i=0;i<s2.size;i++)
            str[i+s1.size]=s2.str[i];
        size=s1.size+s2.size;
        str[size]='\0';
        return true;
    }
    else if(s1.size<MAXSTRLEN)
    {
        for(i=0;i<s1.size;i++)
            str[i]=s1.str[i];
        for(i=0;i<=MAXSTRLEN-s1.size-1;i++)
            str[s1.size+i]=s2.str[i];
        size=MAXSTRLEN;
        str[size]='\0';
        return false;
    }
    else
    {
        for(i=0;i<=MAXSTRLEN-1;i++)
            str[i]=s1.str[i];
        size=MAXSTRLEN;
        str[size]='\0';
        return false;
    }
}*/
#endif //CHAPTER04_SSTRING_H
