
#include "BinarySearchTree.h"

/**
 * The overload constructor sets the root to nullptr, length to
 * 0, and makes a copy of the original tree.
 * @tparam DataType
 * @param rhs: common parameter name to copy items
 * @return none
 * @see deepCopy, a helper function that will copy the tree
 */
template<class DataType> //part 2
BinarySearchTree<DataType>::BinarySearchTree(const BinarySearchTree<DataType> &rhs) {
    length=0;
    root=nullptr;
    deepCopy(rhs.root); //copy tree
}

/**
 * The default constructor of the BinarySearchTree class sets the root
 * to nullptr and length of 0, whenever an object of this ADT is defined.
 * @tparam DataType
 * @param none
 * @return none
 */
template<class DataType>
BinarySearchTree<DataType>::BinarySearchTree() {
    root = nullptr;
    length = 0;
}

/**
 * The deconstructor deletes all the tree with help
 * of the deleteAll function
 * @tparam DataType
 * @param none
 * @return none
 * @see deleteAll, helper function that deletes tree
 * from the bottom up
 */
template<class DataType>
BinarySearchTree<DataType>::~BinarySearchTree() {
    deleteAll(root);
}

/**
 * The deepCopy function recursively calls it self to create
 * a direct copy of tree. It uses preorder (general function)
 * function concept to do this.
 * @tparam DataType
 * @param tree: the tree being copied
 * @return void
 * @see putItem, putItem is a function that will put the tree's
 * value into the new tree.
 */
template<class DataType>
void BinarySearchTree<DataType>::deepCopy(const Node<DataType> *tree) {
    //preorder concept: null-return, print, tree->left, tree->right
    if(tree==nullptr){return;}
    putItem(tree->value);
    deepCopy(tree->left);
    deepCopy(tree->right);
}

/**
 * The deleteAll helper method is a recursive method that repeatively calls
 * the left and right subtrees of the tree until it reaches a node with
 * no children then it stops and deletes the tree.
 * @tparam DataType
 * @param tree: The tree being deleted
 * @return void
 * @see no helper functions
 */
template<class DataType>
void BinarySearchTree<DataType>::deleteAll(const Node<DataType>* tree){
    //base case
    if(tree==nullptr){
        return;
    }
    //general case, call with the subtree
    deleteAll(tree->right);
    deleteAll(tree->left);
    //delete tree after recursive call
    delete tree;
}

/**
 * The getLength method returns the length/height of the BST.
 * It is an accessor method of the private variable length.
 * @tparam DataType
 * @param none
 * @return length, length of BST
 * @see no helper functions
 */
template<class DataType>
int BinarySearchTree<DataType>::getLength() {
    return length;
}

/**
 * The putItem method finds a node that points to nullptr and
 * inserts an item into a new Node, with the help of the insert
 * function, which then returns true.
 * @tparam DataType
 * @param item: value of Node user is inputting
 * @return bool: true once it inserts item, doesn't return false
 * @see insert, a helper recursive method that helps find a location
 * to insert the new Node
 */
template<class DataType>
bool BinarySearchTree<DataType>::putItem(const DataType &item) {
    //base case
    if(root==nullptr){
        root = new Node<DataType>();  //create new Node
        root->value = item;           //set that Node's value to item
        length++;                     //increment
        return true;
    }
    //general case
    return(insert(root,item));
}

/**
 * The insert helper is a recursive method helps with the putItem
 * method to find a location for the item to be inserted to correctly.
 * @tparam DataType
 * @param tree: the BST the new item is being inserted into
 * @param item: the value of the item
 * @return bool: false if value already exists in tree
 *               true if finds location for item
 * @see n/a
 */
template<class DataType>
bool BinarySearchTree<DataType>::insert(Node<DataType>* tree, const DataType &item){
    //base case / fails if item already in there
    if(tree->value==item){
        return false;
    }
    //if item needs to go inside left subtree
    else if(item < tree->value) {
        //find a spot with no children then create new node and insert
        if (tree->left == nullptr) {
            tree->left = new Node<DataType>();
            tree->left->value = item;
            length++;
            return true;
        } else {   //didn't find spot so recursive call for left subtree
            return (insert(tree->left, item));
        }
    }
    //if item needs to go to right subtree
    else if(item > tree->value) {
        //find a spot with no children then create new node and insert
        if(tree->right == nullptr){
            tree->right= new Node<DataType>();
            tree->right->value=item;
            length++;
            return true;
        }
        else{ //didn't find a spot so recursive call of right subtree
            return(insert(tree->right,item));
        }
    }
    //doesn't meet any condition (impossible)
    return false;
}

/**
 * The getItem method searches through the BST to find the
 * requested item in the parameter via helper function find.
 * Returns true or false depending on success or failure.
 * @tparam DataType
 * @param item: item being looked for by the user
 * @param found_item: item found equivalent to one being search
 *                    for is copied into this variable
 * @return true, when successfully finds item
 *         false, when does not find
 * @see find, a helper function that helps search thru the BST
 */
template<class DataType>
bool BinarySearchTree<DataType>::getItem(const DataType &item, DataType &found_item) {
    //create new node found set to return value of find
    Node<DataType>* found = find(root,item);
    //if found is nullptr then unsuccessful
    if(found!=nullptr){
        found_item = found->value; //copy value into found_item
        return true; //success! :D
    }
    else{ //found==nullptr
        return false; //fail :(
    }
}

/**
 * The recursive find helper function works with the getItem
 * method to search thru a BST
 * @tparam DataType
 * @param tree: the tree being searched
 * @param item: the item being searched for
 * @return tree, if value is found equal to item
 *         nullptr, if unsuccessful in finding item
 * @see n/a
 */
template<class DataType>
Node<DataType>* BinarySearchTree<DataType>::find(Node<DataType>* tree, const DataType &item) {
    //base case
    if (tree == nullptr) {
        return nullptr;
    }
    //general case
    if (tree->value == item) { //found the item and return it
            return tree;
    } else if (item < tree->value) { //item is less so search to the left
            return (find(tree->left, item));
    } else {  //item > this->item, item is more so search to the right
        return (find(tree->right, item));
    }
}


/**
 * The isFull method returns false if list is not full
 * and true if it is
 * @tparam DataType
 * @param none
 * @return false, always because unlimited space in our scope of memory use
 * @see n/a
 */
template<class DataType>
bool BinarySearchTree<DataType>::isFull() {
    return false;
}

/**
 * The makeEmpty methods deletes everything in a tree with
 * help of the deleteAll function and resets the length and root.
 * @tparam DataType
 * @param none
 * @return void
 * @see deleteAll, a recursive method that deletes each node from
 * the BST from the bottom up
 */
template<class DataType>
void BinarySearchTree<DataType>::makeEmpty() {
    deleteAll(root); //sends root down to be deleted
    length = 0; //length is 0 b/c empty now
    root = nullptr; //root now points to null
}

/**
 * The resetList method reloads the BST in sorted order
 * @tparam DataType
 * @param none
 * @return void
 * @see loadQueueInOrder, is the recursive helper method
 * that prints the BST in numerical order
 */
template<class DataType>
void BinarySearchTree<DataType>::resetList() {
    std::queue<int> empty;
    std::swap( inOrder, empty );
    loadQueueInOrder(root); //call helper

}

/**
 * The helper method loadQueueInOrder, is recursive and
 * puts the BST in numerical order in a queue.
 * @tparam DataType
 * @param tree: BST that is going to be put into order
 * @return void
 * @see none
 */
template<class DataType>
void BinarySearchTree<DataType>::loadQueueInOrder(Node<DataType> *tree) {
    //once reach end return
    if(tree==nullptr){
        return;
    }
    //go to left of curr node bc smaller, goes to very left
    loadQueueInOrder(tree->left);
    //once at very left push value unto queue
    inOrder.push(tree->value);
    //go to right of curr node bc larger, goes to very right
    loadQueueInOrder(tree->right);
}

/**
 * The getNextItem method returns the front of the queue of the
 * BST in numerical order then deletes it.
 * @tparam DataType
 * @param item: the item that is at the front of the queue is set to
 * @return true, if there is a next item
 *         false, if queue is empty to begin with
 * @see: none
 */
template<class DataType>
bool BinarySearchTree<DataType>::getNextItem(DataType &item) {
    //nothing in BST to begin with
    if(inOrder.empty()) {
        return false;
    }
    //set item to front of queue
    item = inOrder.front();
    //delete item
    inOrder.pop();
    return true;
}

/**
 * The bool min method calls a min overload function and then
 * gets that resulting value and returns it as the minimum
 * value in the BST
 * @tparam DataType
 * @param found_item: the minimum value in the BST
 * @return true, if tree is not empty will return leftmost item
 *         false, if the tree is empty
 * @see: Node* min, will find the actual min value and return it
 * to bool min
 */
template<class DataType>
bool BinarySearchTree<DataType>::min(DataType &found_item) {
    if(root==nullptr){return false;}    //tree is empty
    Node<DataType>* temp = min(root);   //create new node
    found_item=temp->value;             //value of temp is min
    return true;
}

/**
 * The Node min function recursively calls itself until
 * it finds the leftmost node which is the minimum of the tree
 * @tparam DataType
 * @param tree: the tree being searched for the minimum
 * @return tree, if there is not another left value
 *         min(tree->left) a recursive call passing the left subtree
 * @see: none
 */
template<class DataType>
Node<DataType>* BinarySearchTree<DataType>::min(Node<DataType> *tree) {
    if(tree->left==nullptr){return tree;} //no more tree so at minimum
    return(min(tree->left));              //return left subtree
}

/**
 * The bool max method calls a max overload function and then
 * gets that resulting value and returns it as the maximum
 * value in the BST
 * @tparam DataType
 * @param found_item: the maximum value of the BST
 * @return true, if tree is not empty will return rightmost item
 *         false, if the tree is empty
 * @see: Node* max, will find the actual max value and return it
 * to bool max
 */
template<class DataType>
bool BinarySearchTree<DataType>::max(DataType &found_item) {
    if(root==nullptr){return false;}     //tree is empty
    Node<DataType>* temp = max(root);    //new node
    found_item = temp->value;            //value of temp is max
    return true;
}

/**
 * The Node max function recursively calls itself until
 * it finds the rightmost node which is the maximum of the tree
 * @tparam DataType
 * @param tree: the tree being searched for the maximum
 * @return tree, if there is not another right value
 *         min(tree->left) a recursive call passing the right subtree
 * @see: none
 */
template<class DataType>
Node<DataType>* BinarySearchTree<DataType>::max(Node<DataType> *tree){
    if(tree->right==nullptr){return tree;}      //no more right values
    return(max(tree->right));                   //recursive call passing right subtree
}

/**
 * The deleteItem method calls the remove helper function
 * to delete the passed in item from the BST
 * @tparam DataType
 * @param item: the item to be deleted
 * @return false, if item was not in BST, or BST is empty
 *         true, if successfully deleted item from BST
 * @see:  remove, helper function that finds node with item
 * and deletes it based on 3 possible cases
 */
template<class DataType>
bool BinarySearchTree<DataType>::deleteItem(const DataType &item) {
    if(root==nullptr){return false;}    //if empty false
    Node<DataType>* dmw = remove(root, item, nullptr); //set dmw to return value of remove
    if(dmw==nullptr){return false;} //if item was not in BST then false
    else{
        delete dmw;           //delete Node
        length--;             //decrement
        return true;          //success
    }
}

/**
 * The remove helper function first finds the location of the node with
 * the value item, if finds that value, it deletes the node using one of three
 * processes. The process chosen depends on the number of children the node has:
 * none, one, or two. Remove uses recursion
 * @tparam DataType
 * @param tree: the tree being searched for the item
 * @param item: the item to be deleted
 * @param parent: the parent node of the subtree just passed in
 * @return nullptr: if tree==nullptr, item is not there
 *         temp: node with the item
 *         rip: node with the item if it has two chidlren
 * @see: none, but it is recursive
 */
template<class DataType>
Node<DataType>* BinarySearchTree<DataType>::remove(Node<DataType>* tree,const DataType &item, Node<DataType>* parent){
    //if cant find item then nullptr
    if(tree==nullptr){return nullptr;}

    // if hasn't found the item yet
    if(tree->value!=item){
        //curr item is less than item then return left subtree
        if(item<tree->value){return(remove(tree->left,item,tree));}
        //curr item is greater than item then return right subtree
        else{return(remove(tree->right, item, tree));}
    }
    //the value in the tree node is the item
    else{
        //case 1: node to be deleted has no children
        if(tree->left==nullptr && tree->right==nullptr){
            Node<DataType>* temp = tree; //new node
            //if no parent aka root
            if(parent==nullptr) {
                root = nullptr;
                return temp;
            }
            //not root
            else{
                //assess if on left or right side of parent then change to nullptr
                if(temp->value < parent->value){parent->left=nullptr;}
                else{parent->right=nullptr;}
                return temp;
            }
        }
        //case 2: node to be deleted has one child either left or right
        else if(tree->right==nullptr||tree->left==nullptr){
            //create temp and child
            Node<DataType>* temp=tree;
            Node<DataType>* child;
            //set child to be on the right if node to be deleted child is on the right
            if(tree->right!=nullptr){ child=tree->right; }
            //set child to be on the left if node to be deleted child is on the left
            else{child=tree->left;}

            //parent is root so change child to root
            if(parent==nullptr){root=child;}
            //parent is not root now move child values up
            else{
                //set parent's left subtree equal to child
                if(temp->value < parent->value){parent->left=child;}
                //set parent's right subtree equal to child
                else{parent->right=child;}
            }
            //return temp aka node to be deleted
            return temp;
        }
        //case 3: node to be deleted has 2 children
        else{ //(tree->right!=nullptr&&tree->left!=nullptr){
            //new node equal to the minimum value of the right subtree
            Node<DataType>* temp = min(tree->right);
            tree->value = temp->value;
            //set minimum value to be deleted
            Node<DataType>* rip = remove(tree->right, temp->value, tree);
            //return node
            return rip;
        }
    }
}

/**
 * This is the operator overload for the assignment "=" operator
 * this is used when one has to copy one tree's value into another's
 * tree.
 * @tparam: DataType
 * @param: rhs: basic parameter to copy items
 * @return>: void
 * @see: deleteAll, deletes all values in the tree
 * @see: deepCopy, copies all values into a tree
 */
template<class DataType>
void BinarySearchTree<DataType>::operator=(const BinarySearchTree<DataType> &rhs) {
    deleteAll(root);
    root=nullptr;
    length=0;
    deepCopy(rhs.root);
}

