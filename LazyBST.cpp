#include "LazyBST.h"
#include <queue>
#include <iomanip>
#include "LazyBST.h"
#include <queue>
#include "iostream"
using namespace std;

//empty BST constructor
LazyBST::LazyBST() : myRoot(0), mySize(0), flaggedSize(0)
{
}

//checks if root node is empty or not
inline bool LazyBST::empty() const
{
    return myRoot == 0;
}

//returns number of unerased nodes inside the BST
int LazyBST::size()
{
    return mySize - flaggedSize;
}
//*****************SEARCH********************

//searches for specific item inside the tree
//used in Insert, Remove, Member, Erase functions
//search takes two pointers locPtr, Parent and manipulate them
//parent is a successor pointer for locPtr
//locPtr identifies the place of item
void LazyBST::search(const ElementType &item, bool &found, NodePointer &locptr, NodePointer &parent) const
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data) // descend left
        {

            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->data < item) // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else // item found
            found = true;
    }
}
//*****************INSERT********************
//Inserting an item inside the tree
//first we check if the item exists inside the tree
//if it does not exist, we create a new node
//then we check if the tree is empty (parent==0)
//we assign myRoot to locPtr, increment tree's size, and assign Level to the node (locPtr)
//else if item's data is less than the parent's node, we insert left, set node's level as parent's level +1
//else if item's data is bigger than parent's node, we insert right, set node's level as parent's level +1
//else if item's found and tagged as deleted, we remove the tag
//else the item is already in the tree and can't be inserted

void LazyBST::insert(const ElementType &item)
{
    LazyBST::NodePointer
        locptr = myRoot, // search pointer
        parent = 0;      // pointer to parent of rootent node
    bool found = false;  // indicates if item already in BST

    search(item, found, locptr, parent);

    if (!found)
    {
        locptr = new Node(item);
        if (parent == 0)
        { // empty tree

            locptr->Level = 0;
            myRoot = locptr;
            mySize++;
            cout << "Item " << item << " Level " << locptr->Level << endl;
        }
        else if (item < parent->data)
        { // insert to left of parent
            locptr->Level = (parent->Level) + 1;
            cout << "Item " << item << " Level " << locptr->Level << " parent " << parent->data << endl;
            parent->left = locptr;
            mySize++;
        }

        else if (item > parent->data) // insert to right of parent
        {
            locptr->Level = (parent->Level) + 1;
            cout << "Item " << item << " Level " << locptr->Level << " parent " << parent->data << endl;
            parent->right = locptr;
            mySize++;
        }
    }
    else if (found && locptr->isDeleted)
    {
        cout << "Item in the tree and tagged as deleted" << endl;
        locptr->isDeleted = false;
        flaggedSize--;
    }
    else
        cout << "Item already in the tree\n";
}

//*****************FRONT********************

//front returns the data of the smallest item in the tree
//first we check if tree is empty
//secondly if there is no left child, then the root is the smallest node
//else we descend to the leftmost node which will contain the smallest element
ElementType LazyBST::front()

{
    if (empty())
    {
        cerr << "underflow exception, tree is empty!" << endl;
    }

    if (myRoot->left == NULL) //there is no left child, so the myRoot is the minimum element
        return myRoot->data;

    ElementType minimum;
    LazyBST::NodePointer ptr, succPtr;
    ptr = myRoot;           //ptr points on the myRoot
    succPtr = myRoot->left; //succPtr points to the left descendent of the myRoot

    while (succPtr != 0)
    {
        if (!(succPtr->isDeleted))
        {
            minimum = succPtr->data;
        }
        ptr = succPtr;
        succPtr = succPtr->left;
    }
    return minimum;
}
//*****************BACK********************
//back returns the data of the largest item in the tree
//first we check if tree is empty
//secondly if there is no right child, then the root is the largest node
//else we descend to the rightmost node which will contain the largest element
ElementType LazyBST::back()

{
    if (empty())
    {
        throw "underflow exception, tree is empty!";
        return false;
    }

    if (myRoot->right == NULL)
        return myRoot->data;

    ElementType maximum;
    LazyBST::NodePointer ptr, succPtr;
    ptr = myRoot;            //ptr points on the myRoot
    succPtr = myRoot->right; //succPtr points to the left descendent of the myRoot

    while (succPtr != 0)
    {
        if (!(succPtr->isDeleted))
        {
            maximum = succPtr->data;
        }

        ptr = succPtr;
        succPtr = succPtr->right;
    }
    return maximum;
}
//*****************ERASE********************
//erase tags an element as deleted
//first we check if the tree is empty or not
//secondly we call search and search for the item
//returning false if the item is not in the tree
//if the item is inside the tree and is tagged, we return false
//else if the item is inside the tree and is not tagged we tag it
//and increment the flaggedSize, then return true;

bool LazyBST::erase(ElementType item)
{
    if (empty()) //checks to see if the tree is empty or not
    {
        cerr << "empty tree" << endl;
        return false;
    }
    LazyBST::NodePointer locPtr, parent;
    bool found = false;
    search(item, found, locPtr, parent);
    if (found == false) //checks if the item to be deleted exists in the tree or not
    {
        cerr << "item not in the tree" << endl;
        return false;
    }
    else if (found == true && locPtr->isDeleted) //if the item is already tagged do nothing
    {
        cerr << "item already tagged as deleted" << endl;
        return false;
    }
    else if (found == true && !locPtr->isDeleted) // if the item is found and not tagged then change isDeleted flag to true and
                                                  // increment the flagged size
    {
        locPtr->isDeleted = true;
        cout << item << " is deleted" << endl;
        flaggedSize++;
        return true;
    }
    return found;
}

//*****************BREADTH_FIRST_TRAVERSAL********************
//breadth first traversal is a level order traversal
//first we initiliaze a queue in which we push the root first inside the queue
//then we loop on the queue while it is not empty
//
//we output the tagged elements with x beside it
//if the left of the front element is not null we push it to the queue
//if the right of the front element is not null we push it to the queue
//then we dequeue the front element
//
void LazyBST::breadth_first_traversal()
{
    queue<NodePointer> q;
    LazyBST::NodePointer root = myRoot;
    q.push(root);
    while (!q.empty())
    {
        if ((q.front()->isDeleted == 0))
            cout << (q.front()->data) << " ";

        else
            cout << (q.front()->data) << "x ";

        if ((q.front()->left) != nullptr)
            q.push(q.front()->left);

        if ((q.front()->right) != nullptr)
            q.push(q.front()->right);
        q.pop();
    }
}

//*****************HEIGHT_AUX********************
//Height Aux is called inside height since we cannot access root in the main function
//if tree is empty we return 0
//else we return 1 + (the comparison between the left and right tree recursively)
//max determines the biggest element of the two arguments
int LazyBST::heightAux(NodePointer root)
{
    if (root == NULL)
        return 0; //empty tree
    else
    {
        return 1 + max(heightAux(root->left), heightAux(root->right));
    }
}
//****************---HEIGHT---*********************
//height calls heightAux, check heightAux for explanation
int LazyBST::height()
{
    return heightAux(myRoot);
}
//****************---MEMBER---*********************
//member determines if a specific element is in the tree and not tagged
//first we check if the tree is empty
//secondly we search for the item in the tree
//if not found, return false
//else if found and tagged as deleted return false
//else if found and is not deleted return true
bool LazyBST::member(ElementType const &item)
{
    if (empty())
    {
        cerr << "tree is empty" << endl;
        return false;
    }

    LazyBST::NodePointer locPtr, parent;
    bool found = false;
    search(item, found, locPtr, parent);
    if (found == false)
    {
        cerr << "item not in the tree" << endl;
        return false;
    }
    else if (found == true && locPtr->isDeleted) //item is found and is erased
    {
        cerr << "item tagged as deleted" << endl;
        return false;
    }
    else if (found == true && !locPtr->isDeleted && locPtr!=myRoot) // item is found but not erased
    {
        cout << item << " is in the tree at level " << locPtr->Level << " and its parent is " << parent->data << endl;
        return true;
    }
    else if (found == true && !locPtr->isDeleted && locPtr == myRoot) // item is found but not erased
    {
        cout << item << " is root " << endl;
        return true;
    }
        return found;
    }
//****************---REMOVE---*********************
/*
we first check on the tagged node if it has two children
if the node has two children, we call the search() to return two pointers one on the tagged node and the other on its parent apply the right-leftmost technique
after we apply the right-leftmost technique, the node we are pointing on is having either a right child or it is a leaf node
so we check on these two conditions and take actions to delete the node
if we had a node with one child or a leaf node from the beginning, we would not have made the right-leftmost technique by skipping its condition
lastly, we delete the node that we have taken its data 
*/
void LazyBST::remove(const ElementType &item)
{
    bool found;
    NodePointer locptr, parent;

    search(item, found, locptr, parent); //returns two pointers, one on the tagged node "locptr" and its parent to use them in the removing oper.

    if (found == false)
    {
        cout << "Item is not in the BST" << endl;
        return;
    }
    if (locptr->left != 0 && locptr->right != 0) //node has two children
    {
        NodePointer y = locptr->right; //right

        for (parent = locptr; y->left != 0;) //loop to reach the leftmost node and its parent
        {
            parent = y;
            y = y->left;
        }

        locptr->data = y->data;    //replacing information of the tagged node with the right-leftmost node
        locptr->isDeleted = false; //changing the tag of the tagged node after replacing its information
        locptr = y;                //updating the pointer (locptr) to point on the node to be deleted
    }
    
    NodePointer z = locptr->left; //if the node has one child or a leaf node

    if (z == NULL) //checking as the node could be a node with one child that has come from the above if condition
    {
        z = locptr->right;
    }

    if (parent == NULL) //checking if the node has no parent, so it is the root of the tree
    {
        myRoot = z;
    }

    else if (parent->left == locptr) //replacing the node to be deleted with its left child
    {
        parent->left = z;
    }

    else
    {
        parent->right = z; //replacing the node to be deleted with its right child
    }

    delete locptr; //deleting the pointer that has the address of the node to be deleted
}

//****************---cleanTraverse---*********************
/*
    using inorder traversal (left-node-right) recursively to fill a queue with all the tagged elements of the tree in ascending order
    the ascending order is used to check on the nodes sorted, to delete the tree from below. To prevent having a node that needs to be
    removed (tagged), while the node that will replace it is tagged as well. If we did this, we might replace a node with another that is
    supposed to be removed, in this case we will need to traverse the tree from its root to check on all nodes if they are tagged.
*/

void LazyBST::cleanTraverse(NodePointer subtreeRoot)
{
    if (subtreeRoot != 0)
    {
        cleanTraverse(subtreeRoot->left); // L operation
        if (subtreeRoot->isDeleted)
        {
            cleanQ.push(subtreeRoot->data); // Push operation
        }
        cleanTraverse(subtreeRoot->right); // R operation
    }
}
//****************---CLEAN---*********************
/*
    using front() in the queue to store the tagged items, then send the tagged items one by one to the implemented remove() function
*/

void LazyBST::clean()
{
    cleanTraverse(myRoot);                //to fill in the queue
    for (int i = 0; i < flaggedSize; i++) //loop to send all the tagged items from the queue to the remove function to clean the tree
    {
        ElementType deletedElement = cleanQ.front();
        remove(deletedElement);
        cleanQ.pop(); //to get the next item in the next iteration
    }
}
//****************---CLEAR---*********************
/*
    to clear all nodes from the tree whether they are tagged or not by calling the clearAUX
*/

void LazyBST::clear()
{
    clearAUX(myRoot);
}
//****************---CLEAR_AUX---*********************
/*
    using postorder traversal (left-right-node) to clear all nodes of the tree by setting them equal to NULL
    clearAUX is used to take the root as a parameter
*/

void LazyBST::clearAUX(NodePointer root)
{
    if (root != NULL)
    {
        clearAUX(root->left);
        root->left = NULL; //clearning L
        clearAUX(root->right);
        root->right = NULL; //clearing R
        myRoot = nullptr;   //clearing N
        mySize = 0;
        flaggedSize = 0;
    }
}

void LazyBST::showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void LazyBST::printTree(NodePointer root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "r -";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    if(root->isDeleted)
        cout << root->data<<'x' << endl;
    else
        cout << root->data << endl;
    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

void LazyBST::printTreeAUX(){
    printTree(myRoot, nullptr, false);
}