#include "TreeMap.h"
#include <iostream>

using namespace std;

int main() {
    TreeMap<int, string> myMap;

    myMap.put(1, "One");
    myMap.put(2, "Two");
    myMap.put(3, "Three");

    cout << "Size: " << myMap.size() << endl;

    cout << "Get 2: " << myMap.get(2) << endl;
  
    cout << "Contains 3: " << (myMap.containsKey(3) ? "Yes" : "No") << endl;

    myMap.removeKey(1);
    cout << "Size after removal: " << myMap.size() << endl;

    BinaryTree<int> keys = myMap.keySet();
    int* keyArr = keys.toArray();
    for (int i = 0; i < keys.count(); ++i) {
        cout << "Key: " << keyArr[i] << endl;
    }
    delete[] keyArr;

    cout << "Check if [] operator gets 1st element: " << myMap[1] << endl;

    myMap.clear();
    cout << "Size after clear: " << myMap.size() << endl;

    return 0;
}
