#pragma once
#include "BinaryTree.h"
#include <utility>

using namespace std;

template <class K, class V>
class TreeMap {
    BinaryTree<pair<K, V>> tree;

public:
    TreeMap();
    void clear();
    bool containsKey(const K& key);
    V& get(const K& key);
    BinaryTree<K> keySet();
    void put(const K& key, const V& value);
    int size();
    bool removeKey(const K& key);
    V& operator[](const K& key);
};

template <class K, class V>
TreeMap<K, V>::TreeMap() {
}

template <class K, class V>
void TreeMap<K, V>::clear() {
    tree.clear();
}

template <class K, class V>
bool TreeMap<K, V>::containsKey(const K& key) {
    try {
        pair<K, V> searchPair = { key, V() }; 
        tree.getByKey(searchPair);                     
        return true;                              
    }
    catch (...) {
        return false;                            
    }
}

template <class K, class V>
V& TreeMap<K, V>::get(const K& key) {
    pair<K, V> searchPair = { key, V() };

    try {
        pair<K, V>& resultPair = tree.getByKey(searchPair);
        return resultPair.second;
    }
    catch (const logic_error&) {
        throw logic_error("Key not found in map."); 
    }
}




template <class K, class V>
void TreeMap<K, V>::put(const K& key, const V& value) {
    pair<K, V> entry = { key, value };
    if (containsKey(key)) {
        removeKey(key); 
    }
    tree.add(entry); 
}


template <class K, class V>
BinaryTree<K> TreeMap<K, V>::keySet() {
    BinaryTree<K> keys;
    pair<K, V>* pairsArray = tree.toArray();
    int count = tree.count();

    for (int i = 0; i < count; ++i) {
        keys.add(pairsArray[i].first);
    }

    delete[] pairsArray;
    return keys;
}


template <class K, class V>
int TreeMap<K, V>::size() {
    return tree.count();
}


template <class K, class V>
bool TreeMap<K, V>::removeKey(const K& key) {
    pair<K, V> entry = { key, V() }; 
    return tree.remove(entry); 
}

template <class K, class V>
V& TreeMap<K, V>::operator[](const K& key) {
    if (!containsKey(key)) {
        throw logic_error("Key doesn't exist.");
    }
    return get(key);
}