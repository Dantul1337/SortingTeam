#include <cstdlib>
#include <iostream>

#include "insertion_sort.h"

void printList(Node* head)
{
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

bool isSorted(Node* head)
{
    while (head != nullptr && head->next != nullptr) {
        if (head->data > head->next->data) {
            return false;
        }
        head = head->next;
    }
    return true;
}

void fillBest(Node*& head, int n)
{
    for (int i = n; i >= 1; i--) {
        pushBack(head, i);
    }
}

void fillWorst(Node*& head, int n)
{
    for (int i = 1; i <= n; i++) {
        pushBack(head, i);
    }
}

void fillAverage(Node*& head, int n)
{
    for (int i = 0; i < n; i++) {
        pushBack(head, std::rand() % 100);
    }
}

void testCase(const char* name, Node*& head)
{
    std::cout << name << std::endl;
    std::cout << "before: ";
    printList(head);

    insertionSort(head);

    std::cout << "after:  ";
    printList(head);
    std::cout << std::endl;
}

int main()
{
    std::srand(1337);

    const int n = 2000;

    Node* best = nullptr;
    Node* average = nullptr;
    Node* worst = nullptr;

    fillBest(best, n);
    fillAverage(average, n);
    fillWorst(worst, n);

    testCase("best (descending)", best);
    testCase("average (random)", average);
    testCase("worst (ascending)", worst);

    deleteList(best);
    deleteList(average);
    deleteList(worst);

    return 0;
}