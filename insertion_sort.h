#pragma once

#include <vector>

template <typename T>
void insertionSort(std::vector<T>& data)
{
    for (int i = 1; i < data.size(); i++) {
        const T key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}