#include "rankAVL.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main() {

    cout << endl;

    cout << "Rank AVL verification:" << endl;
    Node<int,string> node1(1,"a");
    RankAVL<int,string> rankAVL1(&node1);
    rankAVL1.printTreeRankAVL();
    cout << endl;

    cout << "Insertion's verification:" << endl;
    Node<int,string> node11(1,"a");
    Node<int,string> node12(2,"b");
    Node<int,string> node13(3,"c");
    Node<int,string> node14(4,"d");
    Node<int,string> node15(5,"e");
    Node<int,string> node16(6,"f");
    Node<int,string> node17(7,"g");
    RankAVL<int,string> rankAVL11(&node11);
    rankAVL11.insertNode(&node12);
    rankAVL11.insertNode(&node13);
    rankAVL11.insertNode(&node14);
    rankAVL11.insertNode(&node15);
    rankAVL11.insertNode(&node16);
    rankAVL11.insertNode(&node17);
    rankAVL11.printTreeRankAVL();
    cout << endl;

    cout << "Deletion's verification:" << endl;
    rankAVL11.deleteNode(2);
    rankAVL11.printTreeRankAVL();
    cout << endl;

    cout << "Node finding's verification:" << endl;
    cout << "The node found is: (" << rankAVL11.findNode(3)->m_key << "," << rankAVL11.findNode(3)->m_data << ")" << endl;
    if (rankAVL11.findNode(2) == nullptr) {
        cout << "It's a nullptr. Node does not exist." << endl;
    }
    cout << endl;

    cout << "Root's getter verification:" << endl;
    cout << "The root is: (" << rankAVL11.getRoot()->m_key << "," << rankAVL11.getRoot()->m_data << ")" << endl;
    cout << endl;

    cout << "Null Rank AVL verification:" << endl;
    RankAVL<int,string> rankAVL21(nullptr);
    rankAVL21.printTreeRankAVL();
    Node<int,string> node21(1,"a");
    rankAVL21.insertNode(&node21);
    rankAVL21.printTreeRankAVL();
    cout << endl;

    cout << "Inserse insertion's verification:" << endl;
    Node<int,string> node31(1,"a");
    Node<int,string> node32(2,"b");
    Node<int,string> node33(3,"c");
    Node<int,string> node34(4,"d");
    Node<int,string> node35(5,"e");
    Node<int,string> node36(6,"f");
    Node<int,string> node37(7,"g");
    RankAVL<int,string> rankAVL31(&node37);
    rankAVL31.insertNode(&node36);
    rankAVL31.insertNode(&node35);
    rankAVL31.insertNode(&node34);
    rankAVL31.insertNode(&node33);
    rankAVL31.insertNode(&node32);
    rankAVL31.insertNode(&node31);
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

    return 0;
}
