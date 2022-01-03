#include <cstdlib>
#include <iostream>

using namespace std;
typedef int DataType;

//节点类，也可以用struct Node
class Node {
    friend class LinkList;

private:
    DataType data;
    Node *next;
public:
    Node(Node *ptr = NULL) {
        next = ptr;
    }

    Node(int item, Node *ptr = NULL) {
        data = item;
        next = ptr;
    }
};

//链表类
class LinkList {
private:
    //链表的表头指针、尾指针
    Node *head;
    Node *tail;
public:
    LinkList() {
        head = new Node();//表头结点
        head->next = NULL;
        tail = head;
    }

    ~LinkList();

    void PrintList();//打印输出单链表
    //1.创建、打印链表
    void CreateListR();//尾插法创建链表
    //2.查找结点，找到返回节点逻辑位置，找不到输出：找不到此节点
    void *Locate(DataType e);

    //3.删除指定结点，存在就删除，打印：已经删除；不存在，打印：链表中没有此节点，无法删除
    void Delete(DataType e);

    void DeleteDuplicate();
};

//1.创建并打印链表
void LinkList::CreateListR()//尾插法创建链表
{
    DataType data;
    cout << "请输入数据,0结束:" << endl;
    cin >> data;
    Node *s;
    while (data > 0) {
        s = new Node(data, NULL);
        tail->next = s;
        tail = s;
        cout << "请再次输入数据(输入0结束):" << endl;
        cin >> data;
    }
//    打印链表
    PrintList();
}

//打印链表
void LinkList::PrintList() {
    Node *p = head->next;
    while (p->next != NULL) {
        cout << p->data << "-->";
        p = p->next;
    }
    cout << p->data;
    cout << endl;
}

//2.查找某结点是第几个结点
void *LinkList::Locate(DataType e) {
    Node *p;
    p = head->next;
    int k = 0;
    bool flag = false;
    while (p != NULL) {
        k++;
        if (p->data == e) {
            cout << e << "是第" << k << "个节点" << endl;
            flag = true;
            break;
        } else {
            p = p->next;
        }
    }
    if (!flag)
        cout << "找不到此节点" << endl;
}


//3.删除指定位置元素
void LinkList::Delete(DataType e) {
    Node *p, *preNode = NULL;
    p = head->next;
    bool flag = false;
    while (p != NULL) {
        if (p->data == e) {
            Node *q;//创建临时变量，挪数据
            if (preNode == NULL) {
                head->next = p->next; //删除第一个元素时要注意，用head->next指向下一个值
                delete p;
                if (p->next == NULL)
                    tail = p;
            } else {
                q = preNode->next;
                preNode->next = q->next;
                delete q;
                //重置尾节点
                if (preNode->next == NULL)
                    tail = preNode;
            }
            cout << e << "已经删除" << endl;
            PrintList();
            flag = true;
            break; //找到了就跳出
        } else {
            preNode = p;//记录上一节点
            p = p->next;
        }
    }
    if (!flag)
        cout << e << ":链表中没有此节点，无法删除" << endl;
}


//4.删除重复结点
void LinkList::DeleteDuplicate() {
    Node *p;
    p = head->next;
    while (p != NULL) {
//        cout<< "本次去重前p=" <<p->data<<endl;
//        cout<< "本次去重前链表：" <<endl;
//        PrintList();
        Node *q = p->next;
        while (q != NULL) {
//            cout<< "本次去重前q=" <<q->data<<endl;
            if (q->data == p->data) {
                Delete(q->data);
                //删除后链表指针回到表头效率不高
                //优化：移动到当前位置是最好的，C++的移动不太熟悉，不确定是否可行
                p=head;
            }
            q = q->next;
        }
        p = p->next;
//        cout<< "本次去重后链表："<<endl;
//        PrintList();
    }
    cout<< "全部去重后："<<endl;
    PrintList();
}

LinkList::~LinkList() {
    Node *p;
    p = head;
    while (p != NULL) {
        p = p->next;//p指向下一个结点
        delete head;//删除head所指向的结点
        head = p;//head更新，指向下一个即将被删除结点
    }
}


