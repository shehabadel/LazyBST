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
    cout << "\ninsert || traverse || size || front(Min) || back(Max) || Height || Erase || Clear || Clean || member || You can exit by typing in -999\n\n";
    cout << "Perform: ";
    cin >> x;
    cout << "\n";

   Insert: if (x == "insert")
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

    Traverse: if (x== "traverse" && !l1.empty())
    {
        l1.breadth_first_traversal();
        goto BreakOperation;
    }
    else if(x == "traverse" && l1.empty())
        {
            cout << "\n***ERORR:TREE IS EMPTY***" << endl;
            goto BreakOperation;
    }
    Size: if (x=="size")
    {
        cout << "\ntree size is: "<< l1.size()<<"\n";
        goto BreakOperation;
    }
    

    Front: if (x=="front" && !l1.empty())
    {
        cout << "\nSmallest Number is: " << l1.front() << endl;
        goto BreakOperation;
    }
    else if (x == "front" && l1.empty())
    {
        cout << "\n***ERORR:TREE IS EMPTY***" << endl;
        goto BreakOperation;
    }

    Back: if (x=="back" && !l1.empty())
    {
        cout << "\nLargest Number is: " << l1.back() << endl;
        goto BreakOperation;
    }
    else if (x == "back" && l1.empty())
    {
        cout << "\n***ERORR:TREE IS EMPTY***" << endl;
        goto BreakOperation;
    }

    Height: if (x=="height")
    {
        cout << l1.height()<<"\n";
        goto BreakOperation;
    }

    Erase: if (x=="erase")
    {
        ElementType number;
        for (;;)
        {
            cout << "\nEnter numbers to tag as deleted in the tree: ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.erase(number);
            cout << endl;
        }
    }

    Clear: if (x=="clear")
    {
        l1.clear();
        cout << "\nEmptying the tree....." << endl;
        goto BreakOperation;
    }

    Clean: if (x=="clean")
    {
        l1.clean();
        cout << "\ncleaning tagged nodes....." << endl;
        goto BreakOperation;
    }
    Member: if (x=="member")
    {
        ElementType number;
        for (;;)
        {
            cout << "\nEnter numbers to search for in the tree: ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.member(number);
            cout << endl;
        }
    }
    else 
    {
        cout << "\n***ERROR: CHOOSE AN EXISTING OPERATION***\n";
        goto BreakOperation;
    }
}
