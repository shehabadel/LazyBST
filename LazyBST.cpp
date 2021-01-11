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

void LazyBST::breadth_first_traversal()
{
    LazyBST::NodePointer root = myRoot;
  
    int level = 0;

    while (printLevel(root, level))
        level++;
}

        //************************************************AUX_TRAVERSAL*************************************************************

bool LazyBST::printLevel(NodePointer subtree, ElementType level) const
{
    if (this->empty()) //Check if tree is empty
    {
        cerr << "empty tree" << endl;
        return false;
    }

    if (subtree == NULL) //Reaches a leaf node
        return false;

    if (level == 0 && !subtree->isDeleted) //Reaches the required level and checks to see if the node is flagged as deleted or not
    {
        cout << subtree->data << " ";
        return true;
    }

    bool left = printLevel(subtree->left, level - 1);   //recusivly calls the left child of the node until it reaches the required level
    bool right = printLevel(subtree->right, level - 1); //recusivly calls the right child of the node until it reaches the required level

    return left || right;
}


int LazyBST::heightAux(NodePointer root)
{
    if (root == NULL)
        return 0; //empty tree
    else
    {
        return 1+max(heightAux(root->left), heightAux(root->right));
    }
}

int LazyBST::height()
{
    return heightAux(myRoot);
}
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
    else if (found == true && locPtr->isDeleted) //if the item is already tagged do nothing
    {
        cerr << "item tagged as deleted" << endl;
        return false;
    }
    else if (found == true && !locPtr->isDeleted) // if the item is found and not tagged then change *isDeleted* flag to true and
                                                  // increment the flagged size
    {
        cout << item << " is in the tree at level " << locPtr->Level <<" and its parent is " << parent->data<<   endl;
        return true;
    }
    return found;
}

void LazyBST::cleanAUX(NodePointer current)
{
    if (current != NULL)
        return;

    cleanAUX(current->left);
    cleanAUX(current->right);

    if (current->isDeleted == true)
        delete[] current;
}

void LazyBST::clean()
{
    cleanAUX(myRoot);
}