#include "LazyBST.h"
#include <iostream>
using namespace std;

int main()
{
    LazyBST l1 ;
    //cout << l1.front() << endl;
    l1.insert(5);
    l1.insert(10);
    l1.insert(3);
    l1.insert(2);
    l1.insert(12);
    l1.insert(9);

    /*cout << l1.size() << endl;
        l1.erase(5);
        cout << l1.size() << endl;
        l1.erase(5);
        l1.erase(22);
        l1.insert(4);
        l1.insert(5);
        cout << l1.size() << endl;*/
    cout << l1.front() << endl;
    cout << l1.back() << endl;

}