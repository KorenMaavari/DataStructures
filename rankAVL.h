#ifndef RANK_AVL_H
#define RANK_AVL_H

#include <iostream>

template <class K, class D>
class TreeNode {
    public:
        // TreeNode constructor
        TreeNode(K key, D data)
        :
        m_key(key),
        m_data(data),
        m_left(nullptr),
        m_right(nullptr),
        m_height(1),
        m_subTreeNodesNum(1)
        {}

        // Maximal int
        int maxInt(int a, int b) {
            return (a > b) ? a : b;
        }

        // Calculate height
        int heightGetter() {
            if (this == nullptr) {
                return 0;
            }
            return m_height;
        }

        // Get subTreeNodesNum
        int getmSubTreeNodesNum() {
            if (this == nullptr) {
                return 0;
            }
            return m_subTreeNodesNum;
        }

        // Calculate the balance value of a TreeNode
        int balanceFactor() {
            if (this == nullptr) {
                return 0;
            }
            return (m_left->heightGetter()-m_right->heightGetter());
        }

        // Rotate right
        TreeNode<K,D> *rightRotate(TreeNode<K,D> *originalRoot) {
            TreeNode<K,D> *newRoot = originalRoot->m_left;
            TreeNode<K,D> *subtree = newRoot->m_right;
            newRoot->m_right = originalRoot;
            originalRoot->m_left = subtree;
            originalRoot->m_height = maxInt(
                originalRoot->m_left->heightGetter(),
                originalRoot->m_right->heightGetter()) +1;
            newRoot->m_height = maxInt(newRoot->m_left->heightGetter(),
                newRoot->m_right->heightGetter()) +1;
            originalRoot->m_subTreeNodesNum = originalRoot->m_left->
                getmSubTreeNodesNum() + originalRoot->m_right->
                getmSubTreeNodesNum() + 1;
            newRoot->m_subTreeNodesNum = newRoot->m_left->
                getmSubTreeNodesNum() + newRoot->m_right->
                getmSubTreeNodesNum() + 1;
            return newRoot;
        }

        // Rotate left
        TreeNode<K,D> *leftRotate(TreeNode<K,D> *originalRoot) {
            TreeNode<K,D> *newRoot = originalRoot->m_right;
            TreeNode<K,D> *subtree = newRoot->m_left;
            newRoot->m_left = originalRoot;
            originalRoot->m_right = subtree;
            originalRoot->m_height = maxInt(
                originalRoot->m_left->heightGetter(),
                originalRoot->m_right->heightGetter()) +1;
            newRoot->m_height = maxInt(newRoot->m_left->heightGetter(),
                newRoot->m_right->heightGetter()) +1;
            originalRoot->m_subTreeNodesNum = originalRoot->m_left->
                getmSubTreeNodesNum() + originalRoot->m_right->
                getmSubTreeNodesNum() + 1;
            newRoot->m_subTreeNodesNum = newRoot->m_left->
                getmSubTreeNodesNum() + newRoot->m_right->
                getmSubTreeNodesNum() + 1;
            return newRoot;
        }

        // Insert a TreeNode
        TreeNode<K,D> *insertNodeNode(TreeNode<K,D> *root, TreeNode<K,D> *node) {
            // Find the correct location and insert the node
            if (root == nullptr) {
                /////////////return new TreeNode<K,D>(node->m_key, node->m_data);
                return node;
            }
            if (node->m_key < root->m_key) {
                root->m_left = insertNodeNode(root->m_left, node);
                root->m_subTreeNodesNum++;
            }
            else if (node->m_key > root->m_key) {
                root->m_right = insertNodeNode(root->m_right, node);
                root->m_subTreeNodesNum++;
            }
            else { // if (node->m_key == root->m_key)
                return root;
            }
            // Update the balance factor of each node and balance the tree
            root->m_height = maxInt(root->m_left->heightGetter(),
            root->m_right->heightGetter()) +1;
            int balanceFactorValue = root->balanceFactor();
            if (balanceFactorValue >= 2) {
                if (node->m_key < root->m_left->m_key) {
                    return rightRotate(root);
                } else if (node->m_key > root->m_left->m_key) {
                    root->m_left = leftRotate(root->m_left);
                    return rightRotate(root);
                }
            }
            if (balanceFactorValue <= -2) {
                if (node->m_key > root->m_right->m_key) {
                    return leftRotate(root);
                } else if (node->m_key < root->m_right->m_key) {
                    root->m_right = rightRotate(root->m_right);
                    return leftRotate(root);
                }
            }
            return root;
        }

        // TreeNode with minimum value
        TreeNode<K,D> *leftmostNode(TreeNode<K,D> *node) {
            TreeNode<K,D> *current = node;
            while (current->m_left != nullptr)
                current = current->m_left;
            return current;
        }

        TreeNode<K,D>* deleteNodeNode(TreeNode<K,D>* root, K key) {
            // Perform standard BST delete
            if (root == nullptr) {
                return root;
            }
            if (key < root->m_key) {
                root->m_left = deleteNodeNode(root->m_left, key);
            } else if (key > root->m_key) {
                root->m_right = deleteNodeNode(root->m_right, key);
            } else {
                // Node with only one child or no children
                if ((root->m_left == nullptr) || (root->m_right == nullptr)) {
                    TreeNode<K,D>* temp = root->m_left ? root->m_left : root->m_right;
                    // No children
                    if (temp == nullptr) {
                        temp = root;
                        root = nullptr;
                    } else {
                        // One child
                        if (temp == root->m_left) {
                        } else if (temp == root->m_right) {
                        }
                        *root = *temp;
                    }
                    delete temp;
                } else {
                    // Node with two children: Get the inorder successor (smallest in the right subtree)
                    TreeNode<K,D>* temp = leftmostNode(root->m_right);
                    // Copy the inorder successor's content to this node
                    root->m_key = temp->m_key;
                    root->m_data = temp->m_data;
                    // Delete the inorder successor
                    root->m_right = deleteNodeNode(root->m_right, temp->m_key);
                }
            }
            // If the tree had only one node then return
            if (root == nullptr) {
                return root;
            }
            // Update height and subtree nodes num
            root->m_height = 1 + maxInt(root->m_left->heightGetter(), root->m_right->heightGetter());
            root->m_subTreeNodesNum = 1 + root->m_left->getmSubTreeNodesNum() +
                root->m_right->getmSubTreeNodesNum();
            // Get the balance factor
            int balance = root->balanceFactor();
            // If the node is unbalanced, then there are 4 cases
            // Left Left Case
            if (balance > 1 && root->m_left->balanceFactor() >= 0) {
                return rightRotate(root);
            }
            // Left Right Case
            if (balance > 1 && root->m_left->balanceFactor() < 0) {
                root->m_left = leftRotate(root->m_left);
                return rightRotate(root);
            }
            // Right Right Case
            if (balance < -1 && root->m_right->balanceFactor() <= 0) {
                return leftRotate(root);
            }
            // Right Left Case
            if (balance < -1 && root->m_right->balanceFactor() > 0) {
                root->m_right = rightRotate(root->m_right);
                return leftRotate(root);
            }
            return root;
        }

        // Print tree
        void printTreeNode(TreeNode<K,D> *root, bool lastChild = true, std::string indent = "") {
            if (root != nullptr) {
                std::cout << indent;
                if (lastChild) {
                    std::cout << "R--------";
                    indent += "       ";
                } else {
                    std::cout << "L--------";
                    indent += "|      ";
                }
                std::cout << "(key:" << root->m_key << ", data:" <<
                root->m_data << ", v(n):" << root->m_subTreeNodesNum << ")"
                << std::endl;
                this->printTreeNode(root->m_left, false, indent);
                this->printTreeNode(root->m_right, true, indent);
            }
        }

        // Find a node
        TreeNode<K,D> *findNodeNode(TreeNode<K,D> *root, K key) {
            TreeNode<K,D> *res = nullptr;
            if (root == nullptr) {
                return res;
            }
            else if (key < root->m_key) {
                res = findNodeNode(root->m_left, key);
            }
            else if (key > root->m_key) {
                res = findNodeNode(root->m_right, key);
            }
            else { // if (key == root->m_key)
                res = root;
            }
            return res;
        }

        // Delete a node
        void deleteAVLNode(TreeNode<K,D>* root) {
            if (root == nullptr) {
                return;
            }
            deleteAVLNode(root->m_left);
            deleteAVLNode(root->m_right);
        }

        // Get rank
        int getRankNode(TreeNode<K,D> *root, K key, int res) {
            if (root == nullptr) {
                return res;
            }
            if (root->m_key <= key) {
                if (root->m_left != nullptr) {
                    res += 1 + root->m_left->m_subTreeNodesNum;
                } else {
                    res += 1;
                }
            }
            if (key < root->m_key) {
                res = getRankNode(root->m_left, key, res);
            }
            else if (key > root->m_key) {
                res = getRankNode(root->m_right, key, res);
            }
            // else, if (key == root->m_key)
            return res;
        }

        // get index
        TreeNode<K,D> *getNodeByIndexNode(int index, TreeNode<K,D> *res) {
            if (res == nullptr) {
                return nullptr;
            }
            if ((res->m_left == nullptr) ||
                (res->m_right == nullptr)) {
                    if (res->m_left == nullptr) {
                        if (res->m_right == nullptr) { // both false
                            if (index != 1) {
                                res = nullptr;
                            } else {
                                return res;
                            }
                        } else { // right=true
                            if (index == 1) {
                                return res;
                            } else {
                                res = getNodeByIndexNode(index-1, res->m_right);
                            }
                        }
                    } else { // left=true
                        if (index == res->m_subTreeNodesNum) {
                            return res;
                        } else {
                            res = getNodeByIndexNode(index, res->m_left);
                        }
                    }
                } else { // both true
                    if (res->m_left->m_subTreeNodesNum == index-1) {
                        return res;
                    } else if (res->m_left->m_subTreeNodesNum > index -1) {
                        res = getNodeByIndexNode(index, res->m_left);
                    } else { // if (res->m_left->m_subTreeNodesNum < index -1)
                        res = getNodeByIndexNode(index-(res->m_left->m_subTreeNodesNum)-1, res->m_right);
                    }
                }
                return res;
        }

        // delete all nodes in inorder
        void deleteInorder(TreeNode<K,D>* root) {
            if (root == nullptr) {
                return;
            }
            deleteInorder(root->m_left);
            deleteInorder(root->m_right);
            delete root;
        }


        K m_key;
        D m_data;
        TreeNode<K,D> *m_left;
        TreeNode<K,D> *m_right;
        int m_height;
        int m_subTreeNodesNum;
};

template <class K, class D>
class RankAVL {
    public:
        // AVL constructor
        RankAVL(TreeNode<K,D>* root = nullptr)
        :
        m_root(root)
        {}

        // AVL destructor
        ~RankAVL(){
            m_root->deleteInorder(m_root);
        }

        // Call node insertion
        void insertNode(TreeNode<K,D>* node) {
            m_root = m_root->insertNodeNode(m_root, node);
        }

        // Call node deletion
        void deleteNode(K key) {
            m_root = m_root->deleteNodeNode(m_root, key);
        }

        // Call function of tree's printing
        void printTreeRankAVL() {
            if (m_root == nullptr) {
                std::cout << "The AVL is empty" << std::endl;
            } else {
                m_root->printTreeNode(m_root);
            }
        }

        // Call node finding
        TreeNode<K,D>* findNode(K key) {
            return m_root->findNodeNode(m_root, key);
        }

        // Return tree's root
        TreeNode<K,D> *getRoot() {
            return m_root;
        }

        // delete AVL
        void deleteAVL() {
            m_root->deleteAVLNode(m_root);
            m_root = nullptr;
        }

        // TreeNode with minimum value
        TreeNode<K,D> *smallestNode() {
            TreeNode<K,D> *current = m_root;
            while (current->m_left != nullptr) {
                current = current->m_left;
            }
            return current;
        }

        // TreeNode with maximum value
        TreeNode<K,D> *biggestNode() {
            TreeNode<K,D> *current = m_root;
            while (current->m_right != nullptr) {
                current = current->m_left;
            }
            return current;
        }

        // Call rank calculator
        int getRankRankAVL(K key) {
            return m_root->getRankNode(m_root, key, 0);
        }

        // call NodeByIndex calculator
        TreeNode<K,D> *select(int index) {
            return m_root->getNodeByIndexNode(index, m_root);
        }

    private:
        TreeNode<K,D> *m_root;
};

#endif /* RANK_AVL_H */