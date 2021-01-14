#include "LazyBST.h"
#include <queue>
#include <iostream>

using namespace std;

int main()
{
    string x;
    LazyBST l1;
    cout << "\nConstructing empty BST\n";

BreakOperation:
    cout << "\nChoose an operation of the following by typing in the operation name:" << endl;
    cout << "\nInsert || Traverse || Size || Minimum(front) || Maximum(back) || Height || Erase || Clear || Clean || You can exit by typing in -999\n";
    cin >> x;


   Insert: if (x == "Insert")
    {
        ElementType number;
        for (;;)
        {
            cout << "Enter numbers to add in the tree: ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.insert(number);
            cout << endl;
        }
    }

    Traverse: if (x== "Traverse")
    {
        l1.breadth_first_traversal();
        goto BreakOperation;
    }

    Size: if (x=="Size")
    {
        cout << "tree size is: "<< l1.size()<<"\n";
        goto BreakOperation;
    }

    Front: if (x=="Front")
    {
        cout << "Smallest Number is: " << l1.front() << endl;
        goto BreakOperation;
    }
    Back: if (x=="Back")
    {
        l1.back();
        goto BreakOperation;
    }

    Height: if (x=="Height")
    {
        l1.height();
        goto BreakOperation;
    }

    Erase: if (x=="Erase")
    {
        ElementType number;
        for (;;)
        {
            cout << "Enter numbers to tag as deleted in the tree: ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.erase(number);
            cout << endl;
        }
    }

    Clear: if (x=="Clear")
    {
        l1.clear();
        cout << "Emptying the tree" << endl;
        goto BreakOperation;
    }

    Clean: if (x=="Clean")
    {
        l1.clean();
        cout << "cleaning tagged nodes" << endl;
        goto BreakOperation;
    }
}
