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