#pragma once

struct Node {
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

void insertionSort(Node*& head);
void pushBack(Node*& head, int value);
void deleteList(Node*& head);