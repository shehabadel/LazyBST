#include "LazyBST.h"
#include <queue>
#include "iostream"
using namespace std;

LazyBST::LazyBST(): myRoot(0),mySize(0),flaggedSize(0) //empty BST constructor
{}

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
        cout << "item in the tree and tagged as deleted" << endl;
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
    queue<NodePointer> q;
    LazyBST::NodePointer root = myRoot;
    q.push(root);
    while (!q.empty())
    {
        cout << (q.front()->data) << " ";
        if ((q.front()->left) != nullptr && q.front()->left->isDeleted == 0)
            q.push(q.front()->left);
        if ((q.front()->right) != nullptr && q.front()->right->isDeleted == 0)
            q.push(q.front()->right);
        q.pop();
    }
}
 

    int LazyBST::heightAux(NodePointer root)
    {
        if (root == NULL)
            return 0; //empty tree
        else
        {
            return 1 + max(heightAux(root->left), heightAux(root->right));
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
            cout << item << " is in the tree at level " << locPtr->Level << " and its parent is " << parent->data << endl;
            return true;
        }
        return found;
    }

    void LazyBST::inorder()
    {
        inorderAux(myRoot);
    }

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

    void LazyBST::inorderAux(NodePointer subtreeRoot)
    {
        if (subtreeRoot != 0)
        {
            inorderAux(subtreeRoot->left); // L operation
            if (subtreeRoot->isDeleted)
            {
                cleanQ.push(subtreeRoot->data);
            }                               // V operation
            inorderAux(subtreeRoot->right); // R operation
        }
    }

    void LazyBST::clean()
    {
        inorder();
        for (int i = 0; i < flaggedSize; i++)
        {
            ElementType deletedElement = cleanQ.front();
            remove(deletedElement);
            cleanQ.pop();
        }
    }

    void LazyBST::clear()
    {
        clearAUX(myRoot);
    }

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
