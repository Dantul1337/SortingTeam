#include "insertion_sort.h"

void insertionSort(Node*& head)
{
    Node* sorted = nullptr;
    Node* current = head;

    while (current != nullptr)
    {
        Node* next = current->next;

        if (sorted == nullptr || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* position = sorted;

            while (position->next != nullptr &&
                   position->next->data <= current->data) {
                position = position->next;
                   }

            current->next = position->next;
            position->next = current;
        }

        current = next;
    }

    head = sorted;
}

void pushBack(Node*& head, int value)
{
    Node* node = new Node(value);

    if (head == nullptr) {
        head = node;
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

void deleteList(Node*& head)
{
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}
