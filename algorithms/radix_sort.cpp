#include "radix_sort.h"

// Поразрядная сортировка (LSD radix sort) для односвязного списка int.
//
// Число разбивается на 4 байта, на каждом проходе узлы раскладываются по 256
// спискам-корзинам по одному байту и склеиваются обратно. Узлы добавляются в
// конец корзины, поэтому каждый проход устойчивый, а значит и вся сортировка.
//
// Отрицательные числа: ключ = (unsigned)x ^ 0x80000000. Переворот знакового бита
// переводит порядок int в порядок unsigned, и сравнивать байты можно обычным образом.
//
// Оптимизация: перед сортировкой считаем, какие биты различаются у разных ключей.
// Байты, одинаковые у всех чисел, пропускаются. Для малых чисел проходов меньше 4.
// Время O(k * n), где k - число значимых байтов (до 4), память O(1) сверх списка.

namespace
{
constexpr unsigned kSignBit = 0x80000000u;
constexpr int kBuckets = 256;

unsigned keyOf(int value)
{
    return static_cast<unsigned>(value) ^ kSignBit;
}
} // namespace

void RadixSort::sort(Node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    // Биты, которые различаются хотя бы у двух чисел.
    unsigned orAll = 0;
    unsigned andAll = ~0u;
    for (const Node *node = head; node != nullptr; node = node->next)
    {
        const unsigned key = keyOf(node->data);
        orAll |= key;
        andAll &= key;
    }
    const unsigned differing = orAll ^ andAll;

    for (unsigned shift = 0; shift < 32; shift += 8)
    {
        if (((differing >> shift) & 0xFFu) == 0)
        {
            continue; // у всех чисел этот байт одинаковый, порядок не изменится
        }

        Node *heads[kBuckets] = {};
        Node *tails[kBuckets] = {};

        for (Node *node = head; node != nullptr;)
        {
            Node *next = node->next;
            const unsigned bucket = (keyOf(node->data) >> shift) & 0xFFu;

            node->next = nullptr;
            if (tails[bucket] != nullptr)
            {
                tails[bucket]->next = node;
            }
            else
            {
                heads[bucket] = node;
            }
            tails[bucket] = node;

            node = next;
        }

        Node *newHead = nullptr;
        Node *newTail = nullptr;
        for (int bucket = 0; bucket < kBuckets; ++bucket)
        {
            if (heads[bucket] == nullptr)
            {
                continue;
            }
            if (newTail != nullptr)
            {
                newTail->next = heads[bucket];
            }
            else
            {
                newHead = heads[bucket];
            }
            newTail = tails[bucket];
        }
        head = newHead;
    }
}
