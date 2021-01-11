#include "LazyBST.h"
#include <iostream>
using namespace std;

int main()
{
    LazyBST l1 ;
    cout << "is empty? "<<l1.empty()<< endl;

    l1.insert(5);
    l1.insert(10);
    l1.insert(3);
    l1.insert(2);
    l1.insert(12);
    l1.insert(1);
    l1.insert(5);
    l1.insert(8);



    cout<< "Size: " << l1.size() << endl;
    cout << "Height: " << l1.height() << endl;
    cout << "Front: " << l1.front() << endl;
    cout << "Back: " << l1.back()<<endl;

    cout <<"before erasing:"<< endl;
    l1.breadth_first_traversal();
    cout << l1.size() << endl;
    cout << "Erase: " << l1.erase(3) << endl;
    cout << "Erase again: " << l1.erase(3) << endl;
    cout << "Erase non existing item: " << l1.erase(111) << endl;
    cout << "after erasing: " << endl;
    l1.breadth_first_traversal();

    cout << endl;

    cout << "member: "<< l1.member(2) << endl;
    cout << l1.member(4) << endl;

    l1.clean();
    l1.erase(3);
}