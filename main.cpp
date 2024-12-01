#include "TreeMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    int StudentID;
    string Name;
    int Age;
    double GPA;
    string Graduated;
};


void testStageOneFunctions();
void testPrintInOrder();
void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& wordMap);
void displayMenu(TreeMap<char, BinaryTree<string>>& wordMap);
vector<string> splitLine(const string& line, char delimiter = ',');
vector<Student> loadCSV(const string& filename);
void printData(const vector<Student>& data);
void app();


int main() {
    //Run Stage 1:
   /* testStageOneFunctions();*/

    //Run Stage 2:
    /*TreeMap<char, BinaryTree<string>> map;
    processFile("./word.txt", map);
    displayMenu(map);*/

	//Run Stage 4 (Only Prints CSV data):
    app();


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




vector<string> splitLine(const string& line, char delimiter ) {
    vector<string> fields;
    stringstream ss(line);
    string field;

    while (getline(ss, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

vector<Student> loadCSV(const string& filename) {
    vector<Student> data;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields = splitLine(line);
        if (fields.size() == 5) {
            Student student;
            student.StudentID = stoi(fields[0]);
            student.Name = fields[1];
            student.Age = stoi(fields[2]);
            student.GPA = stod(fields[3]);
            student.Graduated = fields[4];
            data.push_back(student);
        }
    }

    file.close();
    return data;
}

void printData(const vector<Student>& data) {
    cout << "StudentID\tName\t\tAge\tGPA\tGraduated\n";
    cout << "---------------------------------------------------\n";
    for (const auto& student : data) {
        cout << student.StudentID << "\t\t"
            << student.Name << "\t\t"
            << student.Age << "\t"
            << student.GPA << "\t"
            << student.Graduated << "\n";
    }
}

void app() try {
    vector<Student> students = loadCSV("./Student_Grades.csv");

    printData(students);
}
catch (const exception& e) {
    cerr << "Error: " << e.what() << endl;
}


// I originally had stage 4 working using an unordered map, because I assumed we could use any map
// But I realized we had to use the TreeMap class we created. I tried to implement it but I couldn't get it to work


//void createIndex(const vector<Student>& data, const string& field) {
//    TreeMap<string, int> index;
//
//    for (const auto& student : data) {
//        if (field == "Age") {
//            string key = to_string(student.Age);
//            if (index.containsKey(key)) {
//                index.put(key, index.get(key) + 1);
//            }
//            else {
//                index.put(key, 1);
//            }
//        }
//        else if (field == "Graduated") {
//            string key = student.Graduated;
//            if (index.containsKey(key)) {
//                index.put(key, index.get(key) + 1);
//            }
//            else {
//                index.put(key, 1);
//            }
//        }
//        else if (field == "GPA") {
//            string key = to_string(student.GPA);
//            if (index.containsKey(key)) {
//                index.put(key, index.get(key) + 1);
//            }
//            else {
//                index.put(key, 1);
//            }
//        }
//        else if (field == "Name") {
//            string key = student.Name;
//            if (index.containsKey(key)) {
//                index.put(key, index.get(key) + 1);
//            }
//            else {
//                index.put(key, 1);
//            }
//        }
//        else {
//            cout << "Invalid field!" << endl;
//            return;
//        }
//    }
//
//    cout << "\nIndex based on field: " << field << "\n";
//    
//    auto keys = index.keySet();  
//
//    for (const auto& key : keys) {
//        cout << key << ": " << index.get(key) << " occurrence(s)\n";
//    }
//}
//
//
//void viewSubset(const vector<Student>& data, const string& field, const string& value) {
//    cout << "\nRecords where " << field << " is " << value << ":\n";
//    bool found = false;
//
//    for (const auto& student : data) {
//        if (field == "Age" && to_string(student.Age) == value) {
//            cout << student.StudentID << "\t" << student.Name << "\t" << student.Age << "\t" << student.GPA << "\t" << student.Graduated << "\n";
//            found = true;
//        }
//        else if (field == "Graduated" && student.Graduated == value) {
//            cout << student.StudentID << "\t" << student.Name << "\t" << student.Age << "\t" << student.GPA << "\t" << student.Graduated << "\n";
//            found = true;
//        }
//        else if (field == "GPA" && to_string(student.GPA) == value) {
//            cout << student.StudentID << "\t" << student.Name << "\t" << student.Age << "\t" << student.GPA << "\t" << student.Graduated << "\n";
//            found = true;
//        }
//        else if (field == "Name" && student.Name == value) {
//            cout << student.StudentID << "\t" << student.Name << "\t" << student.Age << "\t" << student.GPA << "\t" << student.Graduated << "\n";
//            found = true;
//        }
//    }
//
//    if (!found) {
//        cout << "No records found for " << field << " = " << value << "\n";
//    }
//}
//
//
//void app() try {
//    vector<Student> students = loadCSV("./Student_Grades.csv");
//
//    while (true) {
//        cout << "\nMenu:\n";
//        cout << "1. Create index based on a field\n";
//        cout << "2. View subset of data based on a field value\n";
//        cout << "3. Exit\n";
//        cout << "Enter your choice: ";
//
//        int choice;
//        cin >> choice;
//
//        if (choice == 1) {
//            cout << "Enter the field to index by (Age, Name, GPA, Graduated): ";
//            string field;
//            cin >> field;
//            createIndex(students, field);
//        }
//        else if (choice == 2) {
//            cout << "Enter the field to filter by (Age, Name, GPA, Graduated): ";
//            string field;
//            cin >> field;
//            cout << "Enter the value to search for: ";
//            string value;
//            cin >> value;
//            viewSubset(students, field, value);
//        }
//        else if (choice == 3) {
//            cout << "Exiting the program.\n";
//            break;
//        }
//        else {
//            cout << "Invalid choice. Please try again.\n";
//        }
//    }
//}
//catch (const exception& e) {
//    cerr << "Error: " << e.what() << endl;
//}
