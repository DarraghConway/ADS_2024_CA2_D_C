#include "TreeMap.h"
#include <iostream>
#include <fstream>

using namespace std;


void testPrintInOrder() {
    TreeMap<char, BinaryTree<string>> map;

    const string tree1words[] = {
                "apple", "avocado"
            };
    const string tree2words[] = {
                "banana", "basil"
    };
    const string tree3words[] = {
                "carrot", "chili"
    };
    BinaryTree<string> tree1;
    for (string w : tree1words) {
                tree1.add(w);
            }

    BinaryTree<string> tree2;
    for (string w : tree2words) {
        tree2.add(w);
    }
    BinaryTree<string> tree3;
    for (string w : tree3words) {
        tree3.add(w);
    }

    map.put('a', tree1);
    map.put('b', tree2);
    map.put('c', tree3);

    cout << "Printing TreeMap:" << endl;
    
    for (char key = 'a'; key <= 'z'; ++key) {
        if(map.containsKey(key))
        map[key].printInOrder();
    }


}


void testStageOneFunctions() {
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
}



int main() {
    testPrintInOrder();

    return 0;
}
