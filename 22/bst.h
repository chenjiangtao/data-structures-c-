#include<iostream>
#include<cstdlib>
#include <stack>

using namespace std;
typedef int DataType;

class BinTreeNode {
    friend class BST;

    DataType data;
    BinTreeNode *leftChild;
    BinTreeNode *rightChild;

    BinTreeNode(DataType d, BinTreeNode *l = NULL, BinTreeNode *r = NULL) {
        data = d;
        leftChild = l;
        rightChild = r;
    }
};

struct VistedNode {
    BinTreeNode *node;
    bool vistedRightChild = false;
};

class BST {
private:
    BinTreeNode *root;
    BinTreeNode *lastfound;

    void MakeEmpty(BinTreeNode *&ptr);

    void Insert(DataType x, BinTreeNode *&ptr);

    bool Remove(DataType x, BinTreeNode *&ptr);

    BinTreeNode *Find(DataType x, BinTreeNode *ptr);

public:
    BST() : root(NULL) {
    }

    BST(DataType a[], int n) {
        root = NULL;
        BST(root, a, n);
    }

    BST(BinTreeNode *&ptr, DataType a[], int n);

    ~BST() {
        MakeEmpty(root);
    }

    //    结点插入
    void Insert(DataType x) {
        Insert(x, root);
    }

    //    结点删除
    void Remove(DataType x) {
        Remove(x, root);
    }

    //中序遍历
    void MidOrder();

    //前序遍历
    void PreOrder();

    //后序遍历
    void PostOrder();

    //查找结点
    BinTreeNode *Find(DataType x) {
        return Find(x, root);
    }
};

//析构函数清空树
void BST::MakeEmpty(BinTreeNode *&ptr) {
    if (ptr == NULL)
        return;
    else {
        MakeEmpty(ptr->leftChild);
        MakeEmpty(ptr->rightChild);
        delete ptr;
        ptr = NULL;
    }
}

//非递归的中序遍历
void BST::MidOrder() {
    stack<BinTreeNode *> S;
    BinTreeNode *p = root;   //初始化
    do {
        while (p != NULL) {
            S.push(p);
            p = p->leftChild;
        }
        if (!S.empty()) {                   //栈非空
            p = S.top();
            S.pop();     //退栈
            cout << p->data << endl;      //访问根
            p = p->rightChild;              //向右链走
        }
    } while (p != NULL || !S.empty());
}

//非递归的前序遍历
void BST::PreOrder() {
    stack<BinTreeNode *> S;
    BinTreeNode *p = root;   //初始化
    do {
        while (p != NULL) {
            cout << p->data << endl;//立刻输出
            //进栈之前就输出data
            S.push(p);
            p = p->leftChild;
        }
        if (!S.empty()) {                   //栈非空
            p = S.top();
            S.pop();     //退栈
            p = p->rightChild;              //向右链走
        }
    } while (p != NULL || !S.empty());
}

//非递归的后序遍历
void BST::PostOrder() {
    stack<VistedNode> S;
    BinTreeNode *p = root;   //初始化
    VistedNode vd;
    vd.node = p;
    vd.vistedRightChild = false;
    S.push(vd);
    p = p->leftChild;
    while (!S.empty()) {
        while (p != NULL) {
            vd.node = p;
            vd.vistedRightChild = false;
            S.push(vd);
            p = p->leftChild;
        }
        vd = S.top();
        if (vd.node->rightChild != NULL && vd.vistedRightChild == false) {
            S.pop();
            vd.vistedRightChild = true;
            S.push(vd);
            p = vd.node->rightChild;
        } else {
            S.pop();
            cout << vd.node->data << "--";
            p = NULL;
        }

    }
}
//插入结点
void BST::Insert(DataType x, BinTreeNode *&ptr) {
    if (ptr == NULL) {
        ptr = new BinTreeNode(x, NULL, NULL);
        if (ptr == NULL) {
            cout << "存储不足" << endl;
        }
    } else if (x < ptr->data)
        Insert(x, ptr->leftChild);
    else if (x > ptr->data)
        Insert(x, ptr->rightChild);
}

BST::BST(BinTreeNode *&ptr, DataType a[], int n) {
    ptr = NULL;
    for (int i = 0; i < n; i++)
        Insert(a[i], ptr);
}

//删除结点
bool BST::Remove(DataType x, BinTreeNode *&ptr) {
    if (ptr == NULL)
        return false;
    BinTreeNode *p = ptr, *parent = NULL;
    while (p != NULL) {
        if (x == p->data)
            break;
        if (x < p->data) {
            parent = p;
            p = p->leftChild;
        } else {
            parent = p;
            p = p->rightChild;
        }
    }
    if (p == NULL)
        return false;
    else {
        if (p->leftChild == NULL) {
            if (parent == NULL)
                ptr = p->rightChild;
            else if (parent->leftChild == p)
                parent->leftChild = p->rightChild;
            else
                parent->rightChild = p->rightChild;
        } else if (p->rightChild == NULL)//p无右子女
        {
            if (parent == NULL)
                ptr = p->leftChild;
            else if (parent->leftChild == p)
                parent->leftChild = p->leftChild;
            else
                parent->rightChild = p->leftChild;
        } else //p既有左子女 又有右子女
        {
            BinTreeNode *rr = p, *r = p->rightChild;
            while (r->leftChild) {
                rr = r;
                r = r->leftChild;
            }
            p->data = r->data;
            if (rr == p)
                rr->rightChild = r->rightChild;
            else
                rr->leftChild = r->rightChild;
            delete r;
        }
    }
}
//查找结点
BinTreeNode *BST::Find(DataType x, BinTreeNode *ptr) {
    if (ptr == NULL)
        return NULL;
    if (ptr->data == x)
        return ptr;
    if (x < ptr->data)
        return Find(x, ptr->leftChild);
    else
        return Find(x, ptr->rightChild);
}
