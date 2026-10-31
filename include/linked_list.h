#pragma once

#include "node.h"
#include <cstddef>

Node* createList(const int* values, std::size_t count);

Node* copyList(const Node* source);

void pushBack(Node*& head, int value);

void deleteList(Node*& head);

std::size_t listSize(const Node* head);

bool isSorted(const Node* Head);

bool areListsEqual(const Node* first, const Node* second);