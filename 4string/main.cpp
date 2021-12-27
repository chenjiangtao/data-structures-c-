#include <iostream>
#include <string>
#include "sstring.h"
using namespace std;
int BF(string S, string T)
{
    int i,j,k;
    int n,m;
    n=S.length();//����S������n���ַ�
    m=T.length();//�Ӵ�T������m���ַ�
    if(n==0||m==0)
        return -1;
    //m<n   T.length<S.length
    if(m>n)
        return -1;

    for(i=0;i<=n-m;i++)
    {
        for(j=0;j<m;j++)//jָ���Ӵ�T
            if(T[j]!=S[j+i])
                break;
            if(j==m)
                return i;
    }
    return -1;

}
int BF2(string S, string T)
{
    string sub;
    int i,n,m;
    n=S.length();
    m=T.length();
    if(n==0||m==0)
        return -1;
    if(m>n)
        return -1;
    for(i=0;i<=n-m;i++)
    {
        sub=S.substr(i,m);
        //cout<<"sub="<<sub<<endl;
        if(sub==T)
            return i;
    }
    return -1;
}
/*
 * С����
 *����֪��δ֪
 * */
void getNext(string T,int*& next)
{
    int m=T.length();
    int i,j;
    next=new int[m];
    next[0]=-1;//i=1,2,....m-1
    i=1;
    j=next[i-1];
    for(i=1;i<m;)
    {
        if(j==-1||T[i-1]==T[j])
        {
            next[i]=j+1;//i=3 next[3]=3  j=2
            i++;//i=4
            j++;//j=next[i-1];
        }
        else
            j=next[j];
    }
    /* for(i=0;i<m;i++)
           cout<<next[i]<<"  ";
           */
}
void KMP(string S,string T,int*& next)
{
    int i,j;
    int n=S.length(),m=T.length();
    i=0;
    j=0;
    while(i<n && j<m)
    {
        if(S[i]==T[j])//��� �Ƚ���һ���ַ�
        {
            i++;
            j++;
        }
        else //S[i]!=T[j]
        {
            j=next[j];//
            if(j==-1)//T[j]
            {
                i++; //
                j++;//j=0  s[i+1]  t[0]
            }
        }
    }
    if(j==m)
    {
        cout<<"Find,i="<<i-m<<endl;
    }
    else
        cout<<-1<<endl;
}
int main() {
    //std::cout << "Hello, World!" << std::endl;
    string s("ababcabcacbab");
    string t1("abcd");
    string t2("cabca");
    int* next;
    getNext(t2,next);
    KMP(s,t2,next);
    cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
    /*----string�ж�����캯��------*/
    string s1;  // s1 = ""
    string s2("Hello");  // s2 = "Hello"
    string s3(4, 'K');  // s3 = "KKKK"
    string s4("12345", 1, 3);  //s4 = "234"���� "12345" �Ĵ��±� 1 ��ʼ������Ϊ 3 ���Ӵ�
    /*�ж��ַ����Ƿ�Ϊ��*/
    if(s1.empty())
        cout<<"s1 is empty"<<endl;
    /*�� string ����ֵ�����ַ�ʽ*/
    string s5 = "Hello";  // s1 = "Hello"
    s2 = 'K';  // s2 = "K��
    s3.assign(s5);  // s3 = s5
    s2.assign(s5, 1, 2);  // s2 = "el"
    s2.assign(4, 'K');  // s2 = "KKKK"
    s2.assign("abcde", 2, 3);  // s2 = "cde"���� "abcde" ���Ӵ�(2, 3)
    s2=s3;
    /*���ַ����ĳ���*/
    cout<<"s2.length="<<s2.length()<<endl;
    cout<<"s3.length="<<s3.size()<<endl;
    /*string�������ַ���������
     * ������+
     * Ҳ������ append ��Ա����
     * */

    string s6("Hello");
    string s7("world");
    string s8=s6+s7;
    string s9("123"), s10("abc");
    s9.append(s10);  // s9 = "123abc"
    s9.append(s10, 1, 2);  // s9 = "123abcbc"
    s9.append(3, 'K');  // s9 = "123abcbcKKK"
    s9.append("ABCDE", 2, 3);  // s9 = "123abcbcKKKCDE"����� "ABCDE" ���Ӵ�(2, 3)
    /*string����ıȽ�*/
    if(s2>s3)
        cout<<"s2>s3"<<endl;
    int n = s2.compare(s3);
    /*�� string ������Ӵ�
     * s9 = "123abcbcKKKCDE"
     * */
    string s11 = s9.substr(2, 4);  // s11 = "3abc"
    string s12 = s9.substr(2);  // s12 = "3abcbcKKKCDE"
    /*��������string���������*/
    s11.swap(s12);
    /*�����Ӵ����ַ�*/
    if ((n = s12.find("abc")) != string::npos)
       cout<<"���ҳɹ�"<<endl;
    /*�滻�Ӵ�
     * s12 = "3abcbcKKKCDE"
     * */
    s12.replace(1, 5, "XXX");  //���Ӵ�(1,5)�滻Ϊ"XXX"
    /*ɾ���Ӵ�
     * s6="Hello"
     * s8="Helloworld"
     * */
    s6.erase(1, 3);  //ɾ���Ӵ�(1, 3)���˺� s6 = "Ho"
    s8.erase(5);//ɾ���±�5�������������ַ����˺� s8 ="Hello"
    /* �����ַ���*/
    s1.assign("Limitless");
    s2="00";
    s1.insert(2, "123");  //���±� 2 �������ַ���"123"��s1 = "Li123mitless"
    //s1 = "Li123mitless"
    s1.insert(3, s2);  //���±� 2 ������ s2 , s1 = "Li10023mitless"
    string S="ababcabcacbab";
    string T="abcac";
    cout<<"BF="<<BF2(S,T);
    /*�����ַ�����ÿһ���ַ�
   int i;
   for(i=0;i<s12.length();i++)
       cout<<s12[i];

    char s[10]="aabbbcc12";
    SString T;
    T.Assign(s);
    T.DispStr();
    cout<<T.LongestString();
     */
    return 0;
}
