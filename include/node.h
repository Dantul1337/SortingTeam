#pragma once
struct Node
{
    int data;
    Node* next;

    explicit Node(int value) : data(value), next(nullptr) {}
};
