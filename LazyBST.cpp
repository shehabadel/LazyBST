#include "LazyBST.h"
#include "iostream"
using namespace std;

inline LazyBST::LazyBST(): root(0),mySize(0),flaggedSize(0) //empty BST constructor
{}

inline bool LazyBST::empty() const
{
    return root==0;
}

//returns number of unerased nodes inside the BST
inline int LazyBST::size()
{
    return mySize-flaggedSize; 
}

    int LazyBST::height(NodePointer root)
    {
        if (root == NULL)
            return 0; //empty tree
        else
        {
            return 1 + max(height(root->left), height(root->right);
        }

    }

bool LazyBST::member(ElementType const& item)
{
    NodePointer locptr = root;
    bool found = false;
    while (found == false)
    {
        if (item == locptr->data)
        {
            found = true;
            if (locptr->isDeleted == False)
                return True;
            else
                return False;
        }
        else if (item < locptr->data)
            locptr = locptr->left;
        else
            locptr = locptr->right;
    }
    return false;
    }
}

void LazyBST::clear()
{
    
    
}
