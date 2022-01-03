#include <iostream>
#include "bst.h"
//#include "binarytree.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
//    BinaryTree bt;
//    bt.CreateBinTree();
//    cout<< bt.IsEmpty();
//    bt.PrintTree();
//    bt.PostOrder();
//    bt.PreOrder();
//    bt.MiddleOrder();

//    HuffmanTree hft;
//	HTreeNode* root;
//	hft.CreateHuffman(a,5);
//	root=hft.GetRoot();
//	hft.HuffmanCoding(root,0);

    int a[5] = {35, 25, 20, 15, 10};
    BST bt = BST(a, 5);
//    bt.PostOrder();
    BinTreeNode *node = bt.Find(0);
    if (node !=NULL)
        cout<< node << "存在节点" <<endl;


    return 0;
}
