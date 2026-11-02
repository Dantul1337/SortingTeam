#include "merge_sort.h"

// Сортировка слиянием для односвязного списка (in-place, устойчивая).
// Список режется пополам (середина находится быстрым и медленным указателем),
// половины сортируются рекурсивно и сливаются. Глубина рекурсии log2(n),
// узлы только перестраиваются, новые не создаются.
// Время O(n log n) в любом случае, дополнительная память O(log n) на рекурсию.

namespace
{
// Сливает два отсортированных списка. Устойчивость: при равенстве берём узел
// из первого списка (он раньше в исходном порядке).
Node *mergeLists(Node *a, Node *b)
{
    Node dummy(0);
    Node *tail = &dummy;

    while (a != nullptr && b != nullptr)
    {
        if (b->data < a->data)
        {
            tail->next = b;
            b = b->next;
        }
        else
        {
            tail->next = a;
            a = a->next;
        }
        tail = tail->next;
    }

    tail->next = (a != nullptr) ? a : b;
    return dummy.next;
}

Node *sortList(Node *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    // slow останавливается на последнем узле первой половины
    // (в первой половине (n + 1) / 2 узлов).
    Node *slow = head;
    Node *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *second = slow->next;
    slow->next = nullptr;

    return mergeLists(sortList(head), sortList(second));
}
} // namespace

void MergeSort::sort(Node *&head)
{
    head = sortList(head);
}
