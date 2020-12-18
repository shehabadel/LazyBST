#include "LazyBST.h"
#include "iostream"
using namespace std;

inline LazyBST::LazyBST(): root(0),mySize(0),flaggedSize(0) //empty BST constructor
{}

inline bool LazyBST::empty() const
{
    return mySize==0;
}

//returns number of unerased nodes inside the BST
inline int LazyBST::size()
{
    return mySize-flaggedSize; 
}

void LazyBST::searching(const ElementType &item, bool & found, NodePointer & locPtr, NodePointer & parent ) const
{
    locPtr = root;
    parent = 0;
    found = false;
    while (!found && locPtr != 0)
    {
        if (item < locPtr->data)       // descend left
        {
            parent = locPtr;
            locPtr = locPtr->left;
        }
        else if (locPtr->data < item)  // descend right
        {
            parent = locPtr;
            locPtr = locPtr->right;
        }
        else                           // item found
            found = true;
    }
}

bool LazyBST::insert(ElementType item)
{
    /*--------------------------------------------------------------------
	 Insert the new object into the tree: 
	 If the object is already in the tree and not tagged as erased, return false and do nothing; *DONE*
	 if the object is already in the tree but tagged as erased, untag it and return true;  *DONE*
	 if the object is not in the tree, create a new leaf node in the appropriate location and return true. *DONE*
	 If the root node is nullptr, this requires the creation of a new root node; *DONE*
	 otherwise, the corresponding function is called on the root node. 
	---------------------------------------------------------------------*/

    LazyBST::NodePointer insertedNode = new Node(item);
    if(empty())         //empty tree, so created assigned root to the insertedNode
    {
       root = insertedNode;     //the root node holding the insertedNode
        return true;
    }
    bool found=false;
    LazyBST::NodePointer locPtr, parent;
    searching(item, found, locPtr,parent);
    if(!found)          //not found, inserting new node and returning true. no duplicate node
    {
        //inserting after locPtr position in which we stopped at after searching!!!

        if(insertedNode->data <locPtr->data)
        {
            locPtr->left=insertedNode; //inserting on the left as the data is smaller than the parent node
        }
        else
        {
            locPtr->right=insertedNode; //inserting on the left as the data is bigger than the parent node
        }
        return true;
    }
    else if(found && locPtr->isDeleted) //found, and tagged as erased
    {
        locPtr->isDeleted=false;        //marking the node as unerased
        flaggedSize--;                  //decrementing the number of flagged nodes size
        return true;
    }
    else if(found && !(locPtr->isDeleted)) //found, but not tagged as erased
    {
        return false;
    }

    else //default case breaking, because couldn't understand the otherwise case from the documentation
    {
        return true;

    }
}