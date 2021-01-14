#include "LazyBST.h"
#include <queue>
#include "iostream"
using namespace std;

 //empty BST constructor
LazyBST::LazyBST(): myRoot(0),mySize(0),flaggedSize(0)
{}

//checks if root node is empty or not
inline bool LazyBST::empty() const
{
    return myRoot == 0;
}

//returns number of unerased nodes inside the BST
 int LazyBST::size()
{
    return mySize-flaggedSize;
}
        //************************************************SEARCH*************************************************************

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
                //************************************************INSERT*************************************************************
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
        else if (item < parent->data){ // insert to left of parent
            locptr->Level = (parent->Level) + 1;
            cout << "Item " << item << " Level " << locptr->Level <<" parent " << parent->data << endl;
            parent->left = locptr;
            mySize++;
        }

        else if (item > parent->data) // insert to right of parent
        {
            locptr->Level = (parent->Level) + 1;
            cout << "Item " << item << " Level " << locptr->Level << " parent "<< parent->data <<endl;
            parent->right = locptr;
            mySize++;
        }
    }
    else if (found && locptr->isDeleted)
    {
        cout << "item in the tree and tagged as deleted" << endl;
        locptr->isDeleted = false;
        flaggedSize--;
    }
    else
        cout << "Item already in the tree\n";
}

             //************************************************FRONT*************************************************************

//front returns the data of the smallest item in the tree
//first we check if tree is empty
//secondly if there is no left child, then the root is the smallest node
//else we descend to the leftmost node which will contain the smallest element
ElementType LazyBST::front()

{
   if(empty())
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
            //************************************************BACK*************************************************************
//back returns the data of the largest item in the tree
//first we check if tree is empty
//secondly if there is no right child, then the root is the largest node
//else we descend to the rightmost node which will contain the largest element
ElementType LazyBST::back()

{
   if(empty())
   {
       throw "underflow exception, tree is empty!";
       return false;
   }

   if(myRoot->right==NULL)
        return myRoot->data;

    ElementType maximum;
    LazyBST::NodePointer ptr,succPtr;
    ptr=myRoot; //ptr points on the myRoot
    succPtr=myRoot->right; //succPtr points to the left descendent of the myRoot

    while(succPtr!=0)
    {
        if(!(succPtr->isDeleted))
        {
            maximum=succPtr->data;
        }

            ptr=succPtr;
            succPtr=succPtr->right;

    }
    return maximum;

}
            //************************************************ERASE*************************************************************
//erase tags an element as deleted
//first we check if the tree is empty or not
//secondly we call search and search for the item
//returning false if the item is not in the tree
//if the item is inside the tree and is tagged, we return false
//else if the item is inside the tree and is not tagged we tag it
//and increment the flaggedSize, then return true;

bool LazyBST::erase(ElementType item)
{
    if(empty()) //checks to see if the tree is empty or not
    {
        cerr << "empty tree" << endl;
        return false;
    }
    LazyBST::NodePointer locPtr, parent;
    bool found=false;
    search(item, found, locPtr, parent);
    if (found==false) //checks if the item to be deleted exists in the tree or not
    {
        cerr << "item not in the tree" << endl;
        return false;
    }
        else if (found == true && locPtr->isDeleted) //if the item is already tagged do nothing
        {
            cerr << "item already tagged as deleted" << endl;
            return false;
        }
            else if (found==true && !locPtr->isDeleted) // if the item is found and not tagged then change *isDeleted* flag to true and
                                                        // increment the flagged size
            {
                locPtr->isDeleted = true;
                cout << item << " is deleted" << endl;
                flaggedSize++;
                return true;
            }
    return found;
}

    //************************************************BREADTH_FIRST_TRAVERSAL*************************************************************
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
        if ((q.front()->isDeleted==0))
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

                //************************************************HEIGHT_AUX*************************************************************
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
            //************************************************---HEIGHT---*************************************************************
    //height calls heightAux, check heightAux for explanation
    int LazyBST::height()
    {
        return heightAux(myRoot);
    }
            //************************************************---MEMBER---*************************************************************
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
    else if (found == true && !locPtr->isDeleted) // item is found but not erased
    {
        cout << item << " is in the tree at level " << locPtr->Level << " and its parent is " << parent->data << endl;
        return true;
    }
    return found;
}
            //************************************************---REMOVE---*************************************************************
void LazyBST::remove(const ElementType &item)
{
    bool found;
    NodePointer locptr, parent;

    search(item, found, locptr, parent);

    if (found == false)
    {
        cout << "Item is not in the BST" << endl;
        return;
    }
    if (locptr->left != 0 && locptr->right != 0)
    {
        NodePointer y = locptr->right;

        for (parent = locptr; y->left != 0;)
        {
            parent = y;
            y = y->left;
        }

        locptr->data = y->data;
        locptr->isDeleted = false;
        locptr = y;
}
    NodePointer z = locptr->left;

    if (z == NULL)
    {
        z = locptr->right;
    }

    if (parent == NULL)
    {
        myRoot = z;
    }

    else if (parent->left == locptr)
    {
        parent->left = z;
    }

    else
    {
        parent->right = z;
    }

    delete locptr;
}

            //************************************************---cleanTraverse---*************************************************************
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
            //************************************************---CLEAN---*************************************************************
void LazyBST::clean()
{
    cleanTraverse(myRoot);
    for (int i = 0; i < flaggedSize; i++)
    {
        ElementType deletedElement = cleanQ.front();
        remove(deletedElement);
        cleanQ.pop();
    }
}
            //************************************************---CLEAR---*************************************************************
void LazyBST::clear()
{
    clearAUX(myRoot);
}
            //************************************************---CLEAR_AUX---*************************************************************
void LazyBST::clearAUX(NodePointer root)
{
    if (root != NULL)
    {
        clearAUX(root->left);
        root->left = NULL;
        clearAUX(root->right);
        root->right = NULL;
        myRoot = nullptr;
    }
}
