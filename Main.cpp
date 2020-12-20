#include "LazyBST.h"
#include <iostream>
using namespace std;

int main()
{
    LazyBST l1 ;

    l1.insert(5);
    l1.insert(10);
    l1.insert(3);
    l1.insert(2);
    l1.insert(12);
    l1.insert(9);
    l1.insert(4);
    l1.erase(4);
    l1.insert(148);
    l1.insert(18);
    l1.insert(1481);
    l1.insert(148213);



    //cout << l1.size() << endl;


    l1.breadth_first_traversal();
}