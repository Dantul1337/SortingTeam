#include "registry.h"

// #include "algorithms/insertion_sort.h"
// #include "algorithms/merge_sort.h"
// #include "algorithms/quick_sort.h"
// #include "algorithms/radix_sort.h"

const std::vector<Algorithm>& algorithms()
{
    static const std::vector<Algorithm> list = {
        // {"InsertionSort", &InsertionSort::sort, "insertion"},
        // {"MergeSort",     &MergeSort::sort,     "merge"},
        // {"QuickSort",     &QuickSort::sort,     "quick"},
        // {"RadixSort",     &RadixSort::sort,     "radix"},
    };
    return list;
}