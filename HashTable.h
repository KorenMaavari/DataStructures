#ifndef HASHTABLE
#define HASHTABLE

#include <ostream>
#include "List.h"
///////////////////////////////////
//assuming == for List arguments //
//it means player an team have to//
//have operator (player == int)  //
///////////////////////////////////

const int initialSize = 64;
const double minLoadFactor = .25;
const double maxLoadFactor = 4;

template <class Data, class Key, class HashFunction>
class HashTable
{
private:
    int tableSize;
    int numOfItems;
    HashFunction hashFunction;

public:
    List<Data, Key>* table;
    HashTable();
    ~HashTable();

    void insert(Data newData, Key key);
    void remove(Key key);
    Data operator[](Key key);
    bool doesExist(Key key) const;
    int getNumOfItems() const;
    int getTableSize() const;

    void print(std::ostream& os) const;
    double loadFactor() const;
    void validifyTable();
    void resize(int newSize);

};

template<class Data, class Key, class HashFunction>
Data HashTable<Data, Key, HashFunction>::operator[](Key key){
    int index = hashFunction(key);
    List<Data, Key>& list = table[index];

    return list[key];

}




template<class Data, class Key, class HashFunction>
void HashTable<Data, Key, HashFunction>::insert(Data newData, Key key){
    int index = hashFunction(key); // hashFunction operator(const Data& toHashFrom)
    table[index].append(newData, key);
//     std::cout<<"hash insert: " <<std::endl << std::endl  << "List address: " << table[index] << std::endl;
//     std::cout << "key:  " << table[index].head->key << std::endl;
    numOfItems++;
    validifyTable();
}
template<class Data, class Key, class HashFunction>
void HashTable<Data, Key, HashFunction>::resize(int newSize){
    hashFunction = HashFunction(newSize);
    List<Data, Key> temp;
    for (int i = 0; i < tableSize; i++)
    {
        temp.appendList(table[i]);
    }
    List<Data, Key>* newTable = nullptr;
    try{
        newTable = new List<Data, Key>[newSize];
        Node<Data, Key>* current = temp.head;
        while(current != nullptr){
            int index = hashFunction(current->key);
            newTable[index].append(current->data, current->key);
            current = current->next;
        }
        delete []table;
        table = newTable;
        tableSize = newSize;
    }catch(std::exception& e){
        if(newTable != nullptr){
            delete newTable;
        }
        throw std::bad_alloc();
    }

}

template<class Data, class Key, class HashFunction>
void HashTable<Data, Key, HashFunction>::validifyTable(){
    if(loadFactor() < minLoadFactor && tableSize > initialSize){
        resize(tableSize/2);
    }
    else if(loadFactor() > maxLoadFactor){
        resize(tableSize*2);
    }
}

template<class Data, class Key, class HashFunction>
double HashTable<Data, Key, HashFunction>::loadFactor() const{
    return (double)numOfItems/tableSize;
}

template<class Data, class Key, class HashFunction>
int HashTable<Data, Key, HashFunction>::getNumOfItems() const{
    return numOfItems;
}

template<class Data, class Key, class HashFunction>
int HashTable<Data, Key, HashFunction>::getTableSize() const{
    return tableSize;
}
template<class Data, class Key, class HashFunction>
HashTable<Data, Key, HashFunction>::HashTable():
        table(new List<Data, Key> [initialSize]),tableSize(initialSize),numOfItems(0), hashFunction(tableSize)
{
}
template<class Data, class Key, class HashFunction>
HashTable<Data, Key, HashFunction>::~HashTable()
{
//    for (int i = 0; i < tableSize; ++i) {
//        table[i].clearNodes(table[i].head);
//    }
    delete [] table;
}
template<class Data, class Key, class HashFunction>
bool HashTable<Data, Key, HashFunction>::doesExist(Key key) const{
//     std::cout << "id hash table thinks its looking for: " << key << std::endl;
//     std::cout << " Table index is: " << hashFunction(key) << std::endl;
//     std::cout << "size of list: " << table[1].size<< std::endl;
//     Node<Data, Key>* current = table[1].head;
//     std::cout<< "head key next is: "<< current->next << std::endl;
    return (table[hashFunction(key)]).doesExist(key);
}
template<class Data, class Key, class HashFunction>
void HashTable<Data, Key, HashFunction>::print(std::ostream& os) const{
    for (int i = 0; i < this->getTableSize(); i++)
    {
        os <<i+1<<": "<< this->table[i] <<std::endl;
    }
}
template<class Data, class Key, class HashFunction>
void HashTable<Data, Key, HashFunction>::remove(Key key) {
    int index = hashFunction(key);
    table[index].remove(key);
    numOfItems--;
    validifyTable();
}
template<class Data, class Key, class HashFunction>
std::ostream& operator<<(std::ostream& os, const HashTable<Data, Key, HashFunction>& hash){
    hash.print(os);
    return os;
}
#endif