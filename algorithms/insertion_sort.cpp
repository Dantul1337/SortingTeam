#include "insertion_sort.h"

// Идея: строим новый отсортированный список "sorted", по одному перекладывая
// в него узлы исходного. Указатель tail хранит последний узел отсортированной
// части, поэтому есть три быстрых/медленных варианта вставки:
//   1) current >= tail   -> дописываем в конец за O(1)
//                           (>= сохраняет порядок равных, т.е. устойчивость);
//   2) current < sorted  -> ставим в начало за O(1);
//   3) иначе             -> идём от головы, пока не найдём место (O(k)).
// Уже отсортированный вход всегда попадает в вариант 1, поэтому лучший случай O(n).
void InsertionSort::sort(Node *&head)
{
    Node *sorted = nullptr;
    Node *tail = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        Node *next = current->next;

        if (sorted == nullptr)
        {
            current->next = nullptr;
            sorted = tail = current;
        }
        else if (current->data >= tail->data)
        {
            current->next = nullptr;
            tail->next = current;
            tail = current;
        }
        else if (current->data < sorted->data)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            // Здесь sorted->data <= current->data < tail->data,
            // поэтому цикл всегда остановится до конца списка.
            Node *position = sorted;
            while (position->next->data <= current->data)
            {
                position = position->next;
            }
            current->next = position->next;
            position->next = current;
        }

        current = next;
    }

    head = sorted;
}
