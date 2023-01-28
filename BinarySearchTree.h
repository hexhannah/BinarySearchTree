#include <queue>

#ifndef NODE
#define NODE
template <class DataType>
struct Node {
    DataType value;
    Node<DataType>* left = nullptr;
    Node<DataType>* right = nullptr;
};
#endif


#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class DataType>
class BinarySearchTree {
public:

    // Section 1
    BinarySearchTree();
    ~BinarySearchTree();

    int getLength();
    bool putItem(const DataType &item);
    bool getItem(const DataType &item, DataType &found_item);
    bool isFull();
    void makeEmpty();
    void resetList();
    bool getNextItem(DataType &item);

    // Section 2
    bool max(DataType &found_item);
    bool min(DataType &found_item);
    bool deleteItem(const DataType &item);
    // Section 3
    void operator=(const BinarySearchTree<DataType> &rhs);
    BinarySearchTree(const BinarySearchTree<DataType> &rhs);



private:

    bool insert(Node<DataType>* tree, const DataType &item);
    Node<DataType>* find(Node<DataType>* tree, const DataType &item);
    Node<DataType>* min(Node<DataType>* tree);
    Node<DataType>* max(Node<DataType>* tree);
    Node<DataType>* remove(Node<DataType>* tree, const DataType &item, Node<DataType>* parent);
    void loadQueueInOrder(Node<DataType>* tree);
    void deepCopy(const Node<DataType>* tree);
    void deleteAll(const Node<DataType>* tree);

    Node<DataType>* root;
    long length;
    std::queue<DataType> inOrder;


};

#endif //BINARYSEARCHTREE_H
