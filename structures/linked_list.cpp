#include "linked_list.h"

#include <stdexcept>

Node* createList(const int* values, std::size_t count){
    if(values == nullptr && count > 0){
        throw std::invalid_argument("Values array is null");
    }
    
    Node* head = nullptr;
    Node* tail = nullptr;
    
    try{
        for(std::size_t i = 0; i < count; ++i){
            Node* node = new Node(values[i]);
            if(head == nullptr){
                head = node;
            }
            else{
                tail->next = node;
            }
            tail = node;
        }
    } catch (...){
        deleteList(head);
        throw;
    }
    return head;
}

Node* copyList(const Node* source){
    Node* copyHead = nullptr;
    Node* copyTail = nullptr;

    try{
        while(source != nullptr){
            Node* node = new Node(source->data);
            if(copyHead == nullptr){
                copyHead = node;
            } else{
                copyTail->next = node;
            }
            copyTail = node;
            source = source->next;
        }
    } catch(...){
        deleteList(copyHead);
        throw;
    }

    return copyHead;
}

void pushBack(Node*& head, int value){
    Node* node = new Node(value);
    if(head == nullptr){
        head = node;
        return;
    }

    Node* current = head;

    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = node;
}

void deleteList(Node*& head){
    while(head != nullptr){
        Node* next = head->next;
        delete head;
        head = next;
    }
}

std::size_t listSize(const Node* head){
    std::size_t count = 0;
    while(head != nullptr){
        ++count;
        head = head->next;
    }
    return count;
}

bool isSorted(const Node* head){
    while(head != nullptr && head->next != nullptr){
        if(head->data > head->next->data){
            return false;
        }
        head = head->next;
    }
    return true;
}

bool areListsEqual(const Node* first, const Node* second){
    while (first != nullptr && second != nullptr){
        if(first->data != second->data){
            return false;
        }
        first = first->next;
        second = second->next;
    }
    return first == nullptr && second == nullptr;
}