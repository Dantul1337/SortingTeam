#pragma once

#include "sort_interface.h"

#include <functional>
#include <string>
#include <vector>

struct BenchmarkResult
{
    std::string dataset;
    std::size_t size;
    std::string method;
    long long timeUs;

    bool valid() const { return timeUs >= 0; }

    std::string toLine() const;
};

BenchmarkResult runBenchmark(const std::string &method,
                             SortFunction sort,
                             const Node *input,
                             const std::string &dataset,
                             int repeats = 1);

std::vector<std::string> runAllBenchmarks(
    const std::string &dataRoot,
    int repeats,
    const std::function<void(const std::string &)> &onResult = nullptr);