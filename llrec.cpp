#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

/* DELETE INCLUDES LATER*/
#include <iostream>
using namespace std;

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    Node* next = head->next;
    if (head->val <= pivot)
    {
        if (smaller == nullptr)
        {
            smaller = head;
            smaller->next = nullptr;
            if (!next) {return;}
            llpivot(next, smaller, larger, pivot);
        }
        else
        {
            smaller->next = head;
            smaller->next->next = nullptr;
            if (!next) {return;}
            llpivot(next, smaller->next, larger, pivot);
        }
    }
    else
    {
        if (larger == nullptr)
        {
            larger = head;
            larger->next = nullptr;
            if (!next) {return;}
            llpivot(next, smaller, larger, pivot);
        }
        else
        {
            larger->next = head;
            larger->next->next = nullptr;
            if (!next) {return;}
            llpivot(next, smaller, larger->next, pivot);
        }
    }
    return;
}



/*DELETE AFTER; ONLY FOR TESTING
int main()
{
    Node* three = new Node(3, nullptr);
    Node* eight = new Node(8, three);
    Node* four = new Node(4, eight);
    Node* two = new Node(2, four);
    Node* smaller = nullptr;
    Node* larger = nullptr;
    llpivot(two, smaller, larger, 5);


    while (smaller != nullptr)
    {
        cout << smaller->val;
        smaller = smaller->next;
    }
    cout << '\n';
    while (larger != nullptr)
    {
        cout << larger->val;
        larger = larger->next;
    }
    cout << '\n';

    return 0; 
}
*/