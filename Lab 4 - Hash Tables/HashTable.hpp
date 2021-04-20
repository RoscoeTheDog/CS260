//
// Created by admin on 4/20/2021.
//

#ifndef LAB_4___HASH_TABLES_HASHTABLE_HPP
#define LAB_4___HASH_TABLES_HASHTABLE_HPP

#define StringHash  HashTable
#define ChainHash   HashTable

class HashTable {
private:
    unsigned size;
    int **table;
    int ind;

public:

    HashTable() {
        size = 11;
        **table = *new int[size];
    };

    HashTable(unsigned size) {
        this->size = size;
        **table = *new int[size];
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i)
            delete table[i];
        delete [] table;
    }

    void addItem(int value);

    void findItem(int value);

    int findAvail(int value);

    void removeItem(int value);

    void displayTable(int value);

    int &hash(int value);

};


#endif //LAB_4___HASH_TABLES_HASHTABLE_HPP
