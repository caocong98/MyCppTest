#include <iostream>
#include "LRUcache.h"
using namespace std;

int main() {
    LRUcache<int, double> test(2);
    test.put(1, 0);
    test.put(2, 2);
    cout << test.get(1) << endl;
    test.put(3, 3);
    cout << test.get(2) << endl;
    test.put(4, 4);
    test.Size();
    cout << test.get(1) << endl; //
    cout << test.get(3) << endl;
    cout << test.get(4) << endl;
    return 0;
}