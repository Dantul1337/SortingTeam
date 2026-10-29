
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "insertion_sort.h"

std::vector<int> insertion_sort_for_int(std::vector<int>& data)
{
    insertionSort(data);
    return data;
}

std::vector<double> insertion_sort_for_double(std::vector<double>& data)
{
    insertionSort(data);
    return data;
}

int main()
{
    std::mt19937 generator(1337);

    std::uniform_int_distribution int_distribution(-10000, 10000);
    std::uniform_real_distribution double_distribution(-10000.0, 10000.0);

    std::vector<int> int_data;
    std::vector<double> double_data;

    std::ofstream int_file("int_data.txt");
    std::ofstream double_file("double_data.txt");

    for (int i = 0; i < 1000; ++i) {
        int int_value = int_distribution(generator);
        double double_value = double_distribution(generator);

        int_data.push_back(int_value);
        double_data.push_back(double_value);

        int_file << int_value << '\n';
        double_file << double_value << '\n';
    }

    int_file.close();
    double_file.close();

    insertion_sort_for_int(int_data);
    insertion_sort_for_double(double_data);

    std::cout << "Sorted ints:\n";
    for (const auto& value : int_data) {
        std::cout << value << ' ';
    }

    std::cout << "\n\nSorted doubles:\n";
    for (const auto& value : double_data) {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    return 0;
}
