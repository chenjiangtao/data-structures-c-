#include <iostream>
#include "linkedlist.h"

using namespace std;
int main() {

    LinkList ls;
    //1.创建打印链表
    ls.CreateListR();
//    //2.查找结点
//    ls.Locate(5);
//    //3.删除结点
//    ls.Delete(5);
    //4.删除重复节点
    ls.DeleteDuplicate();

    return 0;
}
