#include <iostream>
#include <sstream>
#include "seqstack.h"
#include "seqqueue.h"
#include <string>
#include "template_seqqueue.h"
#include <stack>
#include <vector>
using namespace std;
/*����3.1�����Ԫ�صĽ�ջ˳����1��2 ��3 �� 4 ��5,
 * ���ܷ�õ�3 ��1 ��4 ��2 ��5�ĳ�ջ˳��?
�ж��ܷ�õ�ĳ����ջ˳��
 bool Judge
 * */
void Stringsplit(string str, const char split,vector<string>& res)
{
    istringstream iss(str);	// ������
    string token;			// ���ջ�����
    while (getline(iss, token, split))	// ��splitΪ�ָ���
        {
        res.push_back(token);
        }
}
bool Judge(string input,string output)
{
    vector<string> v1,v2;
    int i,outdata,indata,stackdata;
    Stringsplit(input,',',v1);
    Stringsplit(output,',',v2);
    Queue inputq,outputq;

    for(i=0;i<v1.size();i++)
        inputq.EnQueue(stoi(v1[i]));
    for(i=0;i<v2.size();i++)
        outputq.EnQueue(stoi(v2[i]));
    outdata=outputq.DeQueue();
    Stack stack;
    indata=inputq.DeQueue();
    stack.Push(indata);
    while(!outputq.IsEmpty())
    {
        while(stack.GetTop()!=outdata&& !inputq.IsEmpty())
            stack.Push(inputq.DeQueue());

        while(!stack.IsEmpty()&&!outputq.IsEmpty()&&stack.GetTop()==outdata)
        {
            stack.Pop();
            outdata=outputq.DeQueue();
        }
        if(outputq.IsEmpty())
            return true;
        if(inputq.IsEmpty()&&!stack.IsEmpty())
            return false;
        if(stack.IsEmpty()&&!inputq.IsEmpty())
        {
            stack.Push(inputq.DeQueue());
            outdata=outputq.DeQueue();
        }
    }
    return true;
}
/*
 * ����3.4���ж�һ���ַ����Ƿ��ǶԳƴ�
 * */
bool Symmetry(string s)
{
    if(s==""||s.length()==1)
        return true;
    Stack stack;
    int i=0;
    //int n=s.length()
    //s[0],s[1],.....s[n-1]
    for(i=0;i<s.length();i++)
        stack.Push(s[i]);
    i=0;
    while(!stack.IsEmpty())
    {
        if(stack.Pop()!=s[i])
            return false;//���ǻ���
        i++;
    }
    return true;//�ǻ���
}
/*
 * 3.2ջ�ۺϰ���
 * 3.2.1 ����ת��
 * ʮ��������Nת����d����
 * */
void Conversion(long N , int  d )
{
    Stack  s;
    while(N!=0){
        int k=N%d  ;
        s.Push(k);
        N=N/d;
    }
    while(!s. IsEmpty ())
        cout<< s.Pop();
    cout<<endl;
}
/*
 * 3.2.2 ���ʽ��ֵ
 * �����Ӻ����Ķ���
 * ��������������ȼ�����
 * */
int Precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
        case '#':
        default:
            return 0;
    }
}
/*���������㺯��
 * */
int compute(int opt1,int opt2,char opt)
{
    if(opt=='+')
        return opt1+opt2;
    if(opt=='-')
        return opt2-opt1;
    if(opt=='*')
        return opt1*opt2;
    if(opt=='/')
        return opt2/opt1;
}
/*3.2.2 ���ʽ��ֵ
 * ������׺���ʽ����ֵ�㷨
 */
void EvaluationExpression(string s)
{///   "#30+15*2-(3+7)#"
    int i=0;
    stack<char> OPTR;//������ջ
    //'+','*','-','+'
    stack<int> OPND;//������ջ
    int number=0;
    int opt1,opt2,result;
    char opt;
    char currentopt,stackopt;
    OPTR.push('#');//ջ��
   for(i=0;i<s.length();)
   {
       if(s[i]>='0'&&s[i]<='9')
       {
           number=0;
           while(s[i]>='0'&&s[i]<='9')
           {//s[i]='6','6'-'0'=6
               number=10*number+(s[i]-'0');
               i++;
           }
           OPND.push(number);//�õ��Ĳ�������ջ
       }
       if(s[i]=='(')//ֱ�ӽ�ջ
           OPTR.push(s[i++]);
       else if(s[i]==')')//���ű��ʽ����,���̼���
           {
               opt=OPTR.top();//������ջ
               while(opt!='(')
               {
                   OPTR.pop();
                   opt1=OPND.top();//������ջ
                   OPND.pop();
                   opt2=OPND.top();
                   OPND.pop();
                   result=compute(opt1,opt2,opt);
                   OPND.push(result);
                   opt=OPTR.top();
               }
               OPTR.pop();//'('��ջ
               i++;
           }
          else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
               {
                   currentopt=s[i];//��Ҫ��ջ�������
                   stackopt=OPTR.top();//ջ�������,����ջ
                   while(Precedence(currentopt)<=Precedence(stackopt))
                   {
                       OPTR.pop();//���ȼ��� ����Ҫ��ջ�������
                       //�ߣ�����Ҫ��ջ
                       opt1=OPND.top();
                       OPND.pop();
                       opt2=OPND.top();
                       OPND.pop();
                       result=compute(opt1,opt2,stackopt);
                       OPND.push(result);
                       stackopt=OPTR.top();
                   }
                   OPTR.push(currentopt);//ջ�������ȼ�>=��ǰ
                   //�����ȫ����ջ�Ժ󣬵�ǰ������Ž�ջ
                   i++;
               } else if(s[i]=='#')//'#'������־
               {
                   while(OPTR.size()>1)
                   {
                       opt=OPTR.top();
                       OPTR.pop();
                       opt1=OPND.top();
                       OPND.pop();
                       opt2=OPND.top();
                       OPND.pop();
                       result=compute(opt1,opt2,opt);
                       OPND.push(result);
                   }
                   cout<<OPND.top()<<endl;
                   return;
               }
   }

}
/*
 *3.2.3������ʽ�е�����ƥ�����
 * */
char LeftPart(char ch)
{
    if(ch==')')
        return '(';
    if(ch==']')
        return '[';
    if(ch=='}')
        return '{';
    return ' ';

}
/*
 * �������ʽ�е�����ƥ�����
 * */
bool CheckMath(string s)
{
    Stack mathes;
    int i;
    char c;
    for(i=0;i<s.length();i++)
    {
        if(s[i]=='('||s[i]=='['||s[i]=='{')
            mathes.Push(s[i]);
        if(s[i]==')'||s[i]==']'||s[i]=='}')
        {
            if(mathes.IsEmpty())
                return false;
            c=mathes.Pop();
            char left=LeftPart(s[i]);
            if(c!=left)
                return false;
        }
    }

    if(mathes.IsEmpty())
        return true;
    else
        return false;
}
/*
 * 3.����Ľⷨ�ǵݹ��
 * �˻ʺ�����
 * ����д�ݹ��㷨,Ҳ����д�����㷨
 * */
bool CheckPosition(int queens[],int m)
{
 if(m==0)
     return true;//����ͻ
 int i;
 int x1,y1,x2,y2;
 x2=m;
 y2=queens[m];
 for(i=0;i<=m-1;i++)
 {
     x1=i;
     y1=queens[i];
     if(x1==x2||y1==y2||x1+y1==x2+y2||x1-y1==x2-y2)
         return false;
 }
 return true;//���õ�λ��
}
void placeQueen(int n)
{
    int queens[n];
    int i,j,stars;
    int count=0;//��ĸ���
    stars=1;//queen
    for(i=0;i<n;i++)
        queens[i]=0;//
    while(queens[0]<n)//queens[0]==n �����㷨����
    {
       while(CheckPosition(queens,stars)==false)
       {
           queens[stars]++;

           while(queens[stars]==n&&stars!=0)
           {//����
               queens[stars]=0;
               stars--;
               queens[stars]++;//��һ�лʺ�->�ƶ�
           }
       }
       stars++;
       if(stars==n)
       {//�ҵ�һ����,���
           count++;
           cout<<"The "<<count<<"solution"<<endl;
           for(i=0;i<n;i++)
               cout<<queens[i]<<"  ";
           cout<<endl;
           stars=stars-1;//���һ��
           queens[stars]++;//Ѱ����һ����

           while(queens[stars]==n&& stars!=0)
           {//����
               queens[stars]=0;
               stars--;
               queens[stars]++;
           }
       }
    }
    cout<<"count="<<count<<endl;
}
/*
 * 3.5.1ʹ�ö��д�ӡ���������
 * */

void YangHui(int n)
{
    Queue queue;
    int i;
    int number1,number2;
    queue.EnQueue(0);
    queue.EnQueue(1);
    queue.EnQueue(0);
    // 0   1   0
    for(i=0;i<n;)//��ӡn��
    {
        number1=queue.DeQueue();//����Ԫ�س���
        number2=queue.GetFront();//���µĶ���Ԫ��
        if(number1==0)
            queue.EnQueue(0);
        if(number1>0)
            cout<<number1<<"  ";
        queue.EnQueue(number1+number2);
        if(number2==0)
        {
            queue.DeQueue();//0����
            queue.EnQueue(0);
            i++;//��һ�н�����
            cout<<endl;//����;
        }

    }
}

/*
 * ��ά�����ӡ������ǲο�����
 * */
void PrintYangHui(int n)
{
    int** d=new int*[n];
    int i=0;
    int j=0;
    for(i=0;i<n;i++)
        d[i]=new int[2*n-1];
    for( i=0;i<n;i++)
    {
        for(j=0;j<2*n-1;j++)
            d[i][j]=0;
    }
    for(i=0,j=n-1;i<n;i++)
    {
        d[i][j]=d[i][2*n-1-j-1]=1;
        j--;
    }
    for( i=1;i<n;i++)
    {
        for (j = 1; j < 2 * n - 1; j++)
            if(d[i-1][j-1]>0&&d[i-1][j+1]>0)
                d[i][j]=d[i-1][j-1]+d[i-1][j+1];
    }
    for( i=0;i<n;i++)
    {
        // cout<<setw(3);
        // cout.setf(ios::internal);
        for(j=0;j<2*n-1;j++)
            if(d[i][j]>0)
            {
                if(d[i][j]>0&&d[i][j]<=9)
                    cout<<" "<<d[i][j]<<" ";
                else if(d[i][j]>=10&&d[i][j]<=99)
                    cout<<d[i][j]<<" ";
                else
                    cout<<d[i][j];
            }
            else
                cout<<"   ";
        cout<<endl;
    }
}
/*
 * 3.5.3�������
 * */
void Dancing(int m,int n,int music)
{
    SeqQueue<string> boys(m+1);
    SeqQueue<string> girls(n+1);
    int i;
    int min;
    int k;
    for(i=1;i<=m;i++)
        boys.EnQueue("Boy"+to_string(i));
    for(i=1;i<=n;i++)
        girls.EnQueue("Girl"+to_string(i));
    if(m<n)
        min=m;
    else
        min=n;

    for(k=1;k<=music;k++)
    {

       cout<<"*****Dancing k="<<k<<"*****"<<endl;
        for(i=0;i<min;i++)
        {
            string g;
            string b;
            girls.GetFront(g);
            boys.GetFront(b);
            cout<<g<<"--"<<b<<endl;
        }
    }

}
int main() {
    //cout<<CheckMath("ab(cd)ef{ee[uuu]ppqq}")<<endl;
   // cout<<"--------------"<<endl;
   // cout<<CheckMath("aa((nnbbbc)pp[000]")<<endl;
   // EvaluationExpression("30+40*(50-20)/10#");
  // string s="32+45*6-(10+20+30)+62/2#";

 //  EvaluationExpression(s);
   // Conversion(100,8);
   // Conversion(100,2);
   // placeQueen(8);
 //  cout<<Judge("1,2,3,4,5","3,1,4,2,5");
 // YangHui(10);
//PrintYangHui(10);
Dancing(8,5,5);
    return 0;
}
