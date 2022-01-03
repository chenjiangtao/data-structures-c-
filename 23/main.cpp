#include <iostream>
#include <string>
#include "template_seqqueue.h"
using namespace std;
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
    Dancing(8,5,5);
    return 0;
}