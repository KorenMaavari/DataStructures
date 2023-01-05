#include "rankAVL.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main() {

    cout << endl;

    cout << "Rank AVL verification:" << endl;
    TreeNode<int,string>* node1 = new TreeNode<int,string>(1,"a");
    RankAVL<int,string> rankAVL1(node1);
    rankAVL1.printTreeRankAVL();
    cout << endl;

    cout << "Insertion's verification:" << endl;
    TreeNode<int,string>* node11 = new TreeNode<int,string>(1,"a");
    TreeNode<int,string>* node12 = new TreeNode<int,string>(2,"b");
    TreeNode<int,string>* node13 = new TreeNode<int,string>(3,"c");
    TreeNode<int,string>* node14 = new TreeNode<int,string>(4,"d");
    TreeNode<int,string>* node15 = new TreeNode<int,string>(5,"e");
    TreeNode<int,string>* node16 = new TreeNode<int,string>(6,"f");
    TreeNode<int,string>* node17 = new TreeNode<int,string>(7,"g");
    RankAVL<int,string> rankAVL11(node11);
    rankAVL11.insertNode(node12);
    rankAVL11.insertNode(node13);
    rankAVL11.insertNode(node14);
    rankAVL11.insertNode(node15);
    rankAVL11.insertNode(node16);
    rankAVL11.insertNode(node17);
    rankAVL11.printTreeRankAVL();
    cout << endl;

    cout << "Deletion's verification:" << endl;
    rankAVL11.deleteNode(2);
    rankAVL11.printTreeRankAVL();
    cout << endl;

    cout << "TreeNode finding's verification:" << endl;
    cout << "The node found is: (" << rankAVL11.findNode(3)->m_key << "," << rankAVL11.findNode(3)->m_data << ")" << endl;
    if (rankAVL11.findNode(2) == nullptr) {
        cout << "It's a nullptr. TreeNode does not exist." << endl;
    }
    cout << endl;

    cout << "Root's getter verification:" << endl;
    cout << "The root is: (" << rankAVL11.getRoot()->m_key << "," << rankAVL11.getRoot()->m_data << ")" << endl;
    cout << endl;

    cout << "AVL deletion's verification:" << endl;
    rankAVL11.deleteAVL();
    if (rankAVL11.getRoot() == nullptr) {
        cout << "rankAVL11 deleted successfully" << endl;
    } else {
        cout << "rankAVL11 was not deleted" << endl;
    }
    cout << endl;

    cout << "Null Rank AVL verification:" << endl;
    RankAVL<int,string> rankAVL21(nullptr);
    rankAVL21.printTreeRankAVL();
    TreeNode<int,string>* node21 = new TreeNode<int,string>(1,"a");
    rankAVL21.insertNode(node21);
    rankAVL21.printTreeRankAVL();
    cout << endl;

    cout << "Inserse insertion's verification:" << endl;
    TreeNode<int,string>* node31 = new TreeNode<int,string>(1,"a");
    TreeNode<int,string>* node32 = new TreeNode<int,string>(2,"b");
    TreeNode<int,string>* node33 = new TreeNode<int,string>(3,"c");
    TreeNode<int,string>* node34 = new TreeNode<int,string>(4,"d");
    TreeNode<int,string>* node35 = new TreeNode<int,string>(5,"e");
    TreeNode<int,string>* node36 = new TreeNode<int,string>(6,"f");
    TreeNode<int,string>* node37 = new TreeNode<int,string>(7,"g");
    RankAVL<int,string> rankAVL31(node37);
    rankAVL31.insertNode(node36);
    rankAVL31.insertNode(node35);
    rankAVL31.insertNode(node34);
    rankAVL31.insertNode(node33);
    rankAVL31.insertNode(node32);
    rankAVL31.insertNode(node31);
    rankAVL31.printTreeRankAVL();
    cout << endl;

    cout << "Inverse deletion's verification:" << endl;
    rankAVL31.deleteNode(6);
    rankAVL31.printTreeRankAVL();
    cout << endl;

    cout << "Rank verification:" << endl;
    for (int i=1 ; i<=7 ; ++i) {
        cout << "Rank(" << i << ") = ";
        if (rankAVL31.findNode(i) == nullptr) {
            cout << "nullptr";
        } else {
            cout << rankAVL31.getRankRankAVL(i);
        }
        cout << endl;
    }
    cout << endl;

    cout << "Yitzchak's tree" << endl;
    TreeNode<int,int>* node41 = new TreeNode<int,int>(4,4);
    TreeNode<int,int>* node42 = new TreeNode<int,int>(7,7);
    TreeNode<int,int>* node43 = new TreeNode<int,int>(6,6);
    TreeNode<int,int>* node44 = new TreeNode<int,int>(1,1);
    TreeNode<int,int>* node45 = new TreeNode<int,int>(9,9);
    TreeNode<int,int>* node46 = new TreeNode<int,int>(23,23);
    TreeNode<int,int>* node47 = new TreeNode<int,int>(11,11);
    TreeNode<int,int>* node48 = new TreeNode<int,int>(66,66);
    RankAVL<int,int> rankAVL41(node41);
    rankAVL41.insertNode(node42);
    rankAVL41.insertNode(node43);
    rankAVL41.insertNode(node44);
    rankAVL41.insertNode(node45);
    rankAVL41.insertNode(node46);
    rankAVL41.insertNode(node47);
    rankAVL41.insertNode(node48);
    rankAVL41.printTreeRankAVL();
    cout << endl;

    cout << "Yitzchak's Rank verification:" << endl;
    for (int i=1 ; i<=66 ; ++i) {
        if (rankAVL41.findNode(i) != nullptr) {
            cout << "Rank(" << i << ") = "<< rankAVL41.getRankRankAVL(i) << endl;
        }
    }
    cout << endl;

    cout << "Data of node deletion's verification:" << endl;
    TreeNode<int,string>* node51 = new TreeNode<int,string>(1,"a");
    TreeNode<int,string>* node52 = new TreeNode<int,string>(2,"b");
    TreeNode<int,string>* node53 = new TreeNode<int,string>(3,"c");
    TreeNode<int,string>* node54 = new TreeNode<int,string>(4,"d");
    TreeNode<int,string>* node55 = new TreeNode<int,string>(5,"e");
    TreeNode<int,string>* node56 = new TreeNode<int,string>(6,"f");
    TreeNode<int,string>* node57 = new TreeNode<int,string>(7,"g");
    RankAVL<int,string> rankAVL51(node51);
    rankAVL51.insertNode(node52);
    rankAVL51.insertNode(node53);
    rankAVL51.insertNode(node54);
    rankAVL51.insertNode(node55);
    rankAVL51.insertNode(node56);
    rankAVL51.insertNode(node57);
    rankAVL51.deleteNode(1);
    rankAVL51.deleteNode(2);
    rankAVL51.deleteNode(7);
    rankAVL51.deleteNode(6);
    rankAVL51.deleteNode(4);
    cout << "succeeded!" << endl;
    cout << endl;

    return 0;
}
