#include <stdio.h>
#include <iostream>
using namespace std;
typedef int ElementType;

#pragma once
class LazyBST
{
private:
	class Node
	{
	public:
		ElementType data;
		Node* left;
		Node* right;
		bool isDeleted;

		Node() :left(0), right(0), isDeleted(0)
		{}

		Node(ElementType item) : data(item), left(0), right(0), isDeleted(0)
		{}
	};
	typedef Node* NodePointer;
	
	void searching(const ElementType &item, bool & found, NodePointer & locPtr, NodePointer & parent ) const;
	/*------------------------------------------------------------------------
     Locate a node containing item and its parent.
     
     Precondition:  None.
     Postcondition: locptr points to node containing item or is null if
     not found, and parent points to its parent.#include <iostream>
     ------------------------------------------------------------------------*/

public:

	LazyBST();
	/*--------------------------------------------------------------------
	 Default constructor: builds an empty Tree object.
	 --------------------------------------------------------------------*/
	bool empty() const;
	/*--------------------------------------------------------------------
	 Return true if the tree is empty (the size is 0).
	 --------------------------------------------------------------------*/
	int size();
	/*--------------------------------------------------------------------
	 Returns the number of nodes in the tree not including nodes tagged as erased.
	 --------------------------------------------------------------------*/
	int height(NodePointer root);
	/*--------------------------------------------------------------------
	 Returns the height of the tree including nodes tagged as erased.
    ---------------------------------------------------------------------*/
	bool member(ElementType const& item);
	/*--------------------------------------------------------------------
	 Return true if the argument is in the tree and not tagged as erased and false otherwise.
	---------------------------------------------------------------------*/
	ElementType front();
	/*--------------------------------------------------------------------
	 Return the minimum non-erased object of this tree by calling front on the root node.
	---------------------------------------------------------------------*/
	ElementType back();
	/*--------------------------------------------------------------------
	 Return the maximum non-erased object of this tree by calling back on the root node.
	---------------------------------------------------------------------*/
	void breadth_first_traversal();
	/*--------------------------------------------------------------------
	 Perform a breadh-first traversal.
	---------------------------------------------------------------------*/
	bool insert(ElementType item);
	/*--------------------------------------------------------------------
	 Insert the new object into the tree: 
	 If the object is already in the tree and not tagged as erased, return false and do nothing; 
	 if the object is already in the tree but tagged as erased, untag it and return true; 
	 if the object is not in the tree, create a new leaf node in the appropriate location and return true. 
	 If the root node is nullptr, this requires the creation of a new root node; 
	 otherwise, the corresponding function is called on the root node. 
	---------------------------------------------------------------------*/
	bool erase(ElementType item);
	/*--------------------------------------------------------------------
	 Removes the object from the tree: 
	 If the object is not already in the tree, return false;
	 if the object is in the tree but tagged as erased, return false;
	 if the object is in the tree and not tagged as erased, tag it as erased and return true.
	 If the root node is nullptr, all that is done is that false is returned; 
	 otherwise, the corresponding function is called on the root node.
	---------------------------------------------------------------------*/
	void clear();
	/*--------------------------------------------------------------------
	 Delete all the nodes in the tree.
	---------------------------------------------------------------------*/

	void clean();
	/*--------------------------------------------------------------------
	 Delete all nodes tagged as deleted within the tree following the description found in the lazy-deletion node class.
	---------------------------------------------------------------------*/
	/*void inorder(ostream &out) const;
	void inorderAux(ostream &out, NodePointer subtreePtr) const;*/

private:
	NodePointer myRoot;
	int mySize; //size of all nodes inside the BST
	int flaggedSize; //size of isDeleted or flagged nodes inside the BST
};

//ostream &operator<<(ostream &out,  LazyBST &LazyBST1);
