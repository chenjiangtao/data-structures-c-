#include <iostream>
#include "binarytree.h"
#include "huffmantree.h"

using namespace std;
int main() {

    BinaryTree bt;
//    bt.CreateBinTree();
//    cout << "------非递归的前序------" << endl;
//    bt.FirstOrder();
//    cout << "\n------全部路径的逆序------" << endl;
//    bt.AllPath();
//    cout << "\n------PrintTree------" << endl;

    bt.PrintTree();
    HuffmanTree hft;
	HTreeNode* root;
	int a[5]={35,25,20,15,10};
	hft.CreateHuffman(a,5);
	root=hft.GetRoot();
	hft.HuffmanCoding(root,0);
//	return 0;

    return 0;
}
