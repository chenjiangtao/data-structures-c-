#include <iostream>
#include "circlelist.h"
#include "linkedlist.h"

using namespace std;
int main() {
//    CircList cl(1);//只有一个结点
//    int i;
//    for(i=2;i<=8;i++)//增加7个结点
//        cl.Add(i);
//    cl.Josephus(8,3);
//
    
     LinkList* la=new LinkList();
     LinkList* lb=new LinkList();

//     LinkList list;
//     list.CreateListR();
//     list.PrintList();
    // list.SplitList(la,lb);
    // cout<<"---la-----"<<endl;
    // la->PrintList();
    // cout<<"---lb-----"<<endl;
    // lb->PrintList();
    // delete la;
    // delete lb;

     LinkList ls;
     ls.CreateListR();
     ls.PrintList();
     ls.ReverseList();
     ls.PrintList();
    /*
    List la;
    List lb;
    List lc;
    la.Insert(1,3);
    la.Insert(2,6);
    la.Insert(3,8);
    la.Insert(4,15);
    la.Insert(5,21);

    lb.Insert(1,2);
    lb.Insert(2,7);
    lb.Insert(3,8);
    lb.Insert(4,9);
    lb.Insert(5,15);
    lb.Insert(6,16);
    lb.Insert(7,21);
    cout<<"-----la-------"<<endl;
    la.PrintList();
    cout<<"-----lb-------"<<endl;
    lb.PrintList();
    lb.Delete(5);
    cout<<"-----after delete,lb-------"<<endl;
    lb.PrintList();
    
     lc.MergeList(la,lb);
     LinkList list;
     list.CreateListR();
     list.PrintList();
     list.ReverseListByArray();
     cout<<"--------Reverse()------------"<<endl;
     list.PrintList();    /*
      CircList cl(1);
     int i;
      for(i=2;i<=8;i++)
          cl.Add(i);
     cl.Josephus(8,3);
*/

/*i
   LinkList* la=new LinkList();
   LinkList* lb=new LinkList();
   LinkList* list2=new LinkList();
    LinkList list;
   list.CreateListR();
   list.PrintList();
   list.SplitList(la,lb);
   la->PrintList();
   lb->PrintList();
*/

   /* List la;
    List lb;
    List lc;
    la.Insert(1,10);
    la.Insert(2,20);
    la.Insert(3,30);
    la.Insert(4,40);
    la.PrintList();
    cout<<"la.Locate(30)"<<la.Locate(30)<<endl;
    int data=la.GetElem(4);
    cout<<"data="<<data<<endl;
    la.Delete(2);
    cout<<"After delte element 2"<<endl;
    la.PrintList();*/
    /*
     * List la(4);
     * la.input();
     * la.PrintList();
    lb.Insert(1,30);
    lb.Insert(2,40);
    lb.Insert(3,50);
    lb.Insert(4,60);
    lb.PrintList();
    lc.Union(la,lb);
    lc.PrintList();
     */
    return 0;
}
