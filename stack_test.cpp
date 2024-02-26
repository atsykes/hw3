#include <iostream>
#include "heap.h"

using namespace std;

int main()
{

    Heap<int> s;
    s.push(4);
    s.push(10);
    s.push(3);
    s.push(1);
    s.push(2);

    size_t size = s.size();
    for (int i=0; i < size; ++i)
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}