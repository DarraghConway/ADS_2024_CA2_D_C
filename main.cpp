#include "TreeMap.h"
#include <iostream>
#include <fstream>

using namespace std;

void testStageOneFunctions();
void testPrintInOrder();
void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& wordMap);
void displayMenu(TreeMap<char, BinaryTree<string>>& wordMap);

int main() {
    //Run Stage 1:
    /*testStageOneFunctions();*/

    //Run Stage 2:
    TreeMap<char, BinaryTree<string>> map;
    processFile("./word.txt", map);
    displayMenu(map);

    return 0;
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
        if (map.containsKey(key))
            map[key].printInOrder();
    }


}



void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& wordMap) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }

    string word;
    while (file >> word) {
        if (!word.empty()) {
            char firstLetter = tolower(word[0]);

            if (!wordMap.containsKey(firstLetter)) {
                BinaryTree<string> newTree;
                newTree.add(word);
                wordMap.put(firstLetter, newTree);
            }
            else {
                BinaryTree<string>& tree = wordMap.get(firstLetter);
                tree.add(word);
            }
        }
    }
    file.close();
}

void displayMenu(TreeMap<char, BinaryTree<string>>& wordMap) {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. List letters\n";
        cout << "2. View words by letter\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Letters in file:\n";
            for (char key = 'a'; key <= 'z'; ++key) {
                if (wordMap.containsKey(key))
                    cout << key << endl;
            }
            break;
        }
        case 2: {
            char letter;
            cout << "Enter a letter: ";
            cin >> letter;
            letter = tolower(letter);

            if (wordMap.containsKey(letter)) {
                cout << "Words starting with " << letter << ":\n";
                wordMap.get(letter).printInOrder();
            }
            else {
                cout << "No words found for letter " << letter << ".\n";
            }
            break;
        }
        case 3:
            cout << "Exiting program.\n";
            break;
        }
    } while (choice != 3);
}
