#include <iostream>
#include <sstream>
#include "seqstack.h"
#include "seqqueue.h"
#include <string>
#include "template_seqqueue.h"
#include <stack>
#include <vector>
using namespace std;
/*【例3.1】如果元素的进栈顺序是1、2 、3 、 4 、5,
 * 问能否得到3 、1 、4 、2 、5的出栈顺序?
判断能否得到某个出栈顺序
 bool Judge
 * */
void Stringsplit(string str, const char split,vector<string>& res)
{
    istringstream iss(str);	// 输入流
    string token;			// 接收缓冲区
    while (getline(iss, token, split))	// 以split为分隔符
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
 * 【例3.4】判断一个字符串是否是对称串
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
            return false;//不是回文
        i++;
    }
    return true;//是回文
}
/*
 * 3.2栈综合案例
 * 3.2.1 进制转换
 * 十进制数字N转换成d进制
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
 * 3.2.2 表达式求值
 * 两个子函数的定义
 * 首先是运算符优先级函数
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
/*简单算术运算函数
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
/*3.2.2 表达式求值
 * 计算中缀表达式的求值算法
 */
void EvaluationExpression(string s)
{///   "#30+15*2-(3+7)#"
    int i=0;
    stack<char> OPTR;//操作符栈
    //'+','*','-','+'
    stack<int> OPND;//操作数栈
    int number=0;
    int opt1,opt2,result;
    char opt;
    char currentopt,stackopt;
    OPTR.push('#');//栈底
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
           OPND.push(number);//得到的操作数进栈
       }
       if(s[i]=='(')//直接进栈
           OPTR.push(s[i++]);
       else if(s[i]==')')//括号表达式结束,立刻计算
           {
               opt=OPTR.top();//操作符栈
               while(opt!='(')
               {
                   OPTR.pop();
                   opt1=OPND.top();//操作数栈
                   OPND.pop();
                   opt2=OPND.top();
                   OPND.pop();
                   result=compute(opt1,opt2,opt);
                   OPND.push(result);
                   opt=OPTR.top();
               }
               OPTR.pop();//'('出栈
               i++;
           }
          else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
               {
                   currentopt=s[i];//将要进栈的运算符
                   stackopt=OPTR.top();//栈顶运算符,不出栈
                   while(Precedence(currentopt)<=Precedence(stackopt))
                   {
                       OPTR.pop();//优先级比 即将要进栈的运算符
                       //高，就需要出栈
                       opt1=OPND.top();
                       OPND.pop();
                       opt2=OPND.top();
                       OPND.pop();
                       result=compute(opt1,opt2,stackopt);
                       OPND.push(result);
                       stackopt=OPTR.top();
                   }
                   OPTR.push(currentopt);//栈所有优先级>=当前
                   //运算符全都出栈以后，当前运算符才进栈
                   i++;
               } else if(s[i]=='#')//'#'结束标志
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
 *3.2.3检验表达式中的括号匹配情况
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
 * 检索表达式中的括号匹配情况
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
 * 3.问题的解法是递归的
 * 八皇后问题
 * 可以写递归算法,也可以写迭代算法
 * */
bool CheckPosition(int queens[],int m)
{
 if(m==0)
     return true;//不冲突
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
 return true;//可用的位置
}
void placeQueen(int n)
{
    int queens[n];
    int i,j,stars;
    int count=0;//解的个数
    stars=1;//queen
    for(i=0;i<n;i++)
        queens[i]=0;//
    while(queens[0]<n)//queens[0]==n 整个算法结束
    {
       while(CheckPosition(queens,stars)==false)
       {
           queens[stars]++;

           while(queens[stars]==n&&stars!=0)
           {//回溯
               queens[stars]=0;
               stars--;
               queens[stars]++;//上一行皇后->移动
           }
       }
       stars++;
       if(stars==n)
       {//找到一个解,输出
           count++;
           cout<<"The "<<count<<"solution"<<endl;
           for(i=0;i<n;i++)
               cout<<queens[i]<<"  ";
           cout<<endl;
           stars=stars-1;//最后一行
           queens[stars]++;//寻找下一个解

           while(queens[stars]==n&& stars!=0)
           {//回溯
               queens[stars]=0;
               stars--;
               queens[stars]++;
           }
       }
    }
    cout<<"count="<<count<<endl;
}
/*
 * 3.5.1使用队列打印杨辉三角形
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
    for(i=0;i<n;)//打印n行
    {
        number1=queue.DeQueue();//队首元素出队
        number2=queue.GetFront();//读新的队首元素
        if(number1==0)
            queue.EnQueue(0);
        if(number1>0)
            cout<<number1<<"  ";
        queue.EnQueue(number1+number2);
        if(number2==0)
        {
            queue.DeQueue();//0出队
            queue.EnQueue(0);
            i++;//这一行结束了
            cout<<endl;//换行;
        }

    }
}

/*
 * 二维数组打印杨辉三角参考代码
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
 * 3.5.3舞伴问题
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
