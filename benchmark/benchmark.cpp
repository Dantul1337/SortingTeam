#include "benchmark.h"

#include "data_loader.h"
#include "linked_list.h"
#include "registry.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>

namespace {
std::vector<int> collect(const Node* head, std::size_t limit, bool& tooLong)
{
    std::vector<int> values;
    values.reserve(limit);
    tooLong = false;
    while (head != nullptr) {
        if (values.size() >= limit) {
            tooLong = true;
            break;
        }
        values.push_back(head->data);
        head = head->next;
    }
    return values;
}

long long singleRun(SortFunction sort, const Node* input, std::size_t size,
                    const std::vector<int>& expected)
{
    Node* work = copyList(input);

    const auto start = std::chrono::steady_clock::now();
    sort(work);
    const auto stop = std::chrono::steady_clock::now();

    const auto timeUs =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    bool tooLong = false;
    const std::vector<int> actual = collect(work, size, tooLong);
    const bool ok = !tooLong && actual == expected;
 
    if (!tooLong) {
        deleteList(work);
    }
    return ok ? static_cast<long long>(timeUs) : -1;
}

}

std::string BenchmarkResult::toLine() const
{
    std::ostringstream oss;
    oss << '"' << dataset << "\"\t"
        << size << '\t'
        << method << '\t'
        << timeUs;
    return oss.str();
}

BenchmarkResult runBenchmark(const std::string& method,
                             SortFunction sort,
                             const Node* input,
                             const std::string& dataset,
                             int repeats)
{
    const std::size_t size = listSize(input);

    bool unused = false;
    std::vector<int> expected = collect(input, size, unused);
    std::sort(expected.begin(), expected.end());

    std::vector<long long> times;
    for (int i = 0; i < std::max(repeats, 1); ++i) {
        const long long t = singleRun(sort, input, size, expected);
        if (t < 0) {
            return BenchmarkResult{dataset, size, method, -1};
        }
        times.push_back(t);
    }

    std::sort(times.begin(), times.end());
    return BenchmarkResult{dataset, size, method, times[times.size() / 2]};
}

std::vector<std::string> runAllBenchmarks(
    const std::string& dataRoot,
    int repeats,
    const std::function<void(const std::string&)>& onResult)
{
    std::vector<std::string> logs;

    const std::vector<std::string> files = listAllDataFiles(dataRoot);
    if (files.empty()) {
        std::cerr << "[skip] no data files in " << dataRoot << '\n';
        return logs;
    }

    for (const std::string& file : files) {
        Node* input = loadList(file);

        for (const Algorithm& algorithm : algorithms()) {
            const BenchmarkResult result = runBenchmark(
                algorithm.name, algorithm.sort, input, datasetName(file), repeats);

            logs.push_back(result.toLine());
            if (onResult) {
                onResult(logs.back());
            }
        }

        deleteList(input);
    }
    return logs;
}