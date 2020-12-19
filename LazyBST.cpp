#include "LazyBST.h"
#include "iostream"
using namespace std;

LazyBST::LazyBST(): myRoot(0),mySize(0),flaggedSize(0) //empty BST constructor
{}

inline bool LazyBST::empty() const
{
    return mySize == 0;
}

//returns number of unerased nodes inside the BST
 int LazyBST::size()
{
    return mySize-flaggedSize; 
}
        //************************************************SEARCH*************************************************************

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
 void LazyBST::insert(const ElementType &item)
{
    LazyBST::NodePointer
        locptr = myRoot, // search pointer
        parent = 0;      // pointer to parent of current node
    bool found = false;  // indicates if item already in BST

    search(item, found, locptr, parent);

    if (!found)
    {
        locptr = new Node(item);
        if (parent == 0)
        { // empty tree
            myRoot = locptr;
            mySize++;
        }

        else if (item < parent->data){ // insert to left of parent
            //cout <<mySize<< " parent L " << parent->data <<" element "<< item<< endl;
            parent->left = locptr;
            mySize++;
           
        }
      
        else if (item > parent->data) // insert to right of parent
        {
            //cout << mySize << " parent R " << parent->data << " element " << item << endl;
            parent->right = locptr;
            mySize++;
        }
    }
    else if (found && locptr->isDeleted)
    {
        locptr->isDeleted = false;
        flaggedSize--;
    }
    else
        cout << "Item already in the tree\n";
}

             //************************************************FRONT*************************************************************

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

bool LazyBST::erase(ElementType item) 
{
    if(empty())
    {
        cerr << "empty tree" << endl;
        return false;
    }
    LazyBST::NodePointer locPtr, parent;
    bool found=false;
    search(item, found, locPtr, parent);
    if (found==false)
    {
        cerr << "item not in the tree" << endl;
        return false;
    }
        else if (found == true && locPtr->isDeleted)
        {
            cerr << "item already tagged as deleted" << endl;
            return false;
        }
            else if (found==true && !locPtr->isDeleted)
            {
                locPtr->isDeleted = true;
                cout << "deleted" << endl;
                flaggedSize++;
                return true;
            }
            return found;
}
