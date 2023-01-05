///////////////////////////////
//add remove nextNode to List//
///////////////////////////////

#ifndef LIST_H_
#define LIST_H_
#include <iostream>





template <class Data, class Key>
class Node
{
public:
   Data data;
   Key key;
   Node* next;
   Node() = default;
   void removeNextNode();
   Node(Data data, Key key):data(data), key(key), next(nullptr){
//    std::cout << std::endl << "Node constructor: " << std::endl << "Key is: " << key << std::endl;
   }
   ~Node() = default;


};

template<class Data, class Key>
void Node<Data, Key>::removeNextNode() {
    if(this->next == nullptr)
        return;
    Node<Data, Key>* temp = this->next->next;
    this->next->next = nullptr; // so it won't erase recursively
    delete this->next;
    this->next = temp;
    
}

template<class Data, class Key>
class List
{
private:
public:
    int size;
     Node<Data, Key>* head;
     List():size(0), head(nullptr){}
     ~List();
     void append(Data newItem, Key key);
     Data operator[](Key key);
     bool doesExist(Key key);
     void appendList(List<Data, Key>& other);
     void remove(Key key);
     void clearNodes(Node<Data, Key>* node);
     
    friend std::ostream& operator<<(std::ostream& os, const List<Data, Key>& list){
        Node<Data, Key>* current = list.head;
        if(current == nullptr){
            std::cout<<"[EMPTY]"<<std::endl;
            return os;
        }
        std::cout << "[";
        while(current->next != nullptr){
            std::cout << (current->data) << ", ";
            current = current->next;
        }
        std::cout << (current->data) << "]"<<std::endl;
        return os;
    }
};

template<class Data, class Key>
void List<Data, Key>::appendList(List<Data, Key>& other){
    Node<Data, Key>* current = other.head;
    while(current != nullptr){
        this->append(current->data, current->key);
        current = current->next;
    }
}
template<class Data, class Key>
void List<Data, Key>::append(Data newItem, Key key){
     Node<Data, Key>* newNode = new Node<Data, Key>(newItem, key);
     if(this->head == nullptr){
          head = newNode;
          size++;
          return;
     }
     newNode->next = head;
     head = newNode;
     size++;
}

template<class Data, class Key>
bool List<Data, Key>::doesExist(Key key){
  //      std::cout << "id List thinks its looking for: " << key << std::endl;

    Data dataToCheck = (*this)[key];
    if(dataToCheck == nullptr){
        return false;
    }
    return true;
}
template<class Data, class Key>
Data List<Data, Key>::operator[](Key key){
        //std::cout << "id operator [] thinks its looking for: " << key << std::endl;


        Node<Data, Key>* current = this->head;
       // std::cout << "Search in List: "<< std::endl << "List adress: "<< this << std::endl;
        //std::cout<< "List Size: " << this->size << std::endl;

        //std::cout << "head: " << current->key << std::endl;
        if(current == nullptr){
            return nullptr;
        }
        while(current != nullptr){
            if(current->key == key){
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }





template<class Data, class Key>
void List<Data, Key>::clearNodes(Node<Data, Key>* node){
    while(node != nullptr){
        Node<Data, Key>* temp = node->next;
        node->next = nullptr;
        delete node;
        node = temp;
    }
}

template<class Data, class Key>
List<Data, Key>::~List() {
    if (head == nullptr)return;
    clearNodes(head);
}

template<class Data, class Key>
void List<Data, Key>::remove(Key key) {
    if(head == nullptr)
        return;
    if(head->key == key){
        Node<Data, Key>* temp = head->next;
        head->next = nullptr;
        delete head;
        head = temp;
        return;
    }
    Node<Data, Key>* current = head;
    while(current->next != nullptr){
        if(current->next->key == key){
            current->removeNextNode();
            return;
        }
        current = current->next;
    }

}

#endif
