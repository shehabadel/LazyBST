#include "LazyBST.h"
#include <queue>
#include <iostream>

using namespace std;

int main()
{
    LazyBST l1 ;
    cout << "is empty? "<<l1.empty()<< endl;

    l1.insert(20);
    l1.insert(15);
    l1.insert(25);
    l1.insert(30);
    l1.insert(33);
    l1.insert(27);
    l1.insert(22);
    l1.insert(21);
    l1.insert(24);
    l1.insert(17);
    l1.insert(8);
    l1.insert(5);
    l1.insert(10);
    l1.insert(16);
    l1.insert(19);
    cout << endl;
    /*cout << endl;


    l1.breadth_first_traversal();
    cout << endl;
    cout << endl;

    l1.erase(8);
    l1.erase(10);
    l1.erase(15);
    l1.erase(25);
    l1.erase(17);
    l1.erase(30);
    l1.erase(16);
    l1.erase(27);

    l1.clean();
    cout << endl;*/
  

 

    /*l1.insert(8);
    l1.insert(10);
    l1.insert(15);
    l1.insert(25);
    l1.insert(17);
    l1.insert(30);
    l1.insert(16);
    l1.insert(27);
    l1.breadth_first_traversal();
    cout << endl;*/

    l1.clear();
    cout << endl;
    l1.breadth_first_traversal();
    cout << endl;

    cout << l1.size()<< endl;

    cout << "is empty? "<<l1.empty()<< endl;

}
