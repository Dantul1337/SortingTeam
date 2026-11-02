#include "quick_sort.h"

#include <cstddef>

namespace
{
    struct Chain
    {
        Node *head = nullptr;
        Node *tail = nullptr;

        void append(Node *node)
        {
            node->next = nullptr;
            if (tail != nullptr)
            {
                tail->next = node;
            }
            else
            {
                head = node;
            }
            tail = node;
        }

        void appendChain(Chain &other)
        {
            if (other.head == nullptr)
            {
                return;
            }
            if (tail != nullptr)
            {
                tail->next = other.head;
            }
            else
            {
                head = other.head;
            }
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
        }
    };

    Chain quickSortChain(Node *head)
    {
        Chain prefix;
        Chain suffix;

        while (head != nullptr && head->next != nullptr)
        {
            const int pivot = head->data;

            Chain less, equal, greater;
            std::size_t lessCount = 0;
            std::size_t greaterCount = 0;

            for (Node *node = head; node != nullptr;)
            {
                Node *next = node->next;
                if (node->data < pivot)
                {
                    less.append(node);
                    ++lessCount;
                }
                else if (node->data > pivot)
                {
                    greater.append(node);
                    ++greaterCount;
                }
                else
                {
                    equal.append(node);
                }
                node = next;
            }

            if (lessCount <= greaterCount)
            {
                Chain sortedLess = quickSortChain(less.head);
                prefix.appendChain(sortedLess);
                prefix.appendChain(equal);
                head = greater.head;
            }
            else
            {
                Chain sortedGreater = quickSortChain(greater.head);
                equal.appendChain(sortedGreater);
                equal.appendChain(suffix);
                suffix = equal;
                head = less.head;
            }
        }

        Chain middle;
        if (head != nullptr)
        {
            middle.append(head);
        }

        Chain result = prefix;
        result.appendChain(middle);
        result.appendChain(suffix);
        return result;
    }
}

void QuickSort::sort(Node *&head)
{
    head = quickSortChain(head).head;
}
