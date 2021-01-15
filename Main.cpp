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
    cout << "\n";
    cout << "\nChoose an operation of the following by typing the operation index:" << endl;
    cout << "\n 1. Insert\n 2. Traverse\n 3. Size\n 4. Front(Min)\n 5. Back(Max)\n 6. Height\n 7. Erase\n 8. Clear\n 9. Clean\n 10. Member\n 11. Visualize tree\n 12. Exit\n\n";
    cout << "Perform: ";
    cin >> x;
    

   if (x == "1")
    {
        cout << "inserting....";
        cout << "\n";
        ElementType number;
        for (;;)
        {
            cout << "Enter numbers to add in the tree (-999 to stop): ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.insert(number);
            cout << endl;
        }
    }

    if (x== "2" && !l1.empty())
    {
        l1.breadth_first_traversal();
        goto BreakOperation;
    }
    else if(x == "2" && l1.empty())
        {
            cout << "\n***ERORR:TREE IS EMPTY***" << endl;
            goto BreakOperation;
    }
    if (x=="3")
    {
        cout << "\nTree size is: "<< l1.size()<<"\n";
        goto BreakOperation;
    }
    

    if (x=="4" && !l1.empty())
    {
        cout << "\nSmallest Number is: " << l1.front() << endl;
        goto BreakOperation;
    }
    else if (x == "4" && l1.empty())
    {
        cout << "\n***ERORR:TREE IS EMPTY***" << endl;
        goto BreakOperation;
    }

    if (x=="5" && !l1.empty())
    {
        cout << "\nLargest Number is: " << l1.back() << endl;
        goto BreakOperation;
    }
    else if (x == "5" && l1.empty())
    {
        cout << "\n***ERORR:TREE IS EMPTY***" << endl;
        goto BreakOperation;
    }

    if (x=="6")
    {
        cout << "Tree Height is: " <<l1.height()<<"\n";
        goto BreakOperation;
    }

    if (x=="7")
    {
        ElementType number;
        for (;;)
        {
            cout << "\nEnter numbers to tag as deleted in the tree (-999 to stop): ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.erase(number);
            cout << endl;
        }
    }

    if (x=="8")
    {
        l1.clear();
        cout << "\nEmptying the tree....." << endl;
        goto BreakOperation;
    }

    if (x=="9")
    {
        l1.clean();
        cout << "\nCleaning tagged nodes....." << endl;
        goto BreakOperation;
    }
    if (x=="10")
    {
        ElementType number;
        for (;;)
        {
            cout << "\nEnter numbers to search for in the tree (-999 to stop): ";
            cin >> number;
            if (number == -999)
                goto BreakOperation;
            l1.member(number);
            cout << endl;
        }
    }
    if (x == "11" && !l1.empty())
    {
        l1.printTreeAUX();
        goto BreakOperation;
    }
    else if(x=="11"){
        cout << "\n***ERORR:TREE IS EMPTY***\n";
            goto BreakOperation;
    }

    else if(x=="12")
    {
        cout << "Exiting" << endl;
        return 0;
    }
    else 
    {
        cout << "\n***ERROR: CHOOSE AN EXISTING OPERATION***\n";
        goto BreakOperation;
    }
}
