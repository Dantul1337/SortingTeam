#include "benchmark.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#ifndef SORT_PROJECT_ROOT
#define SORT_PROJECT_ROOT "."
#endif

namespace {

struct Options
{
    std::string dataDir = std::string(SORT_PROJECT_ROOT) + "/data";
    std::string outFile = std::string(SORT_PROJECT_ROOT) + "/results/results.tsv";
    int repeats = 5;
};

void printUsage()
{
    std::cout <<
        "Использование: sort_benchmark [параметры]\n"
        "  --data DIR      папка с данными (по умолчанию <проект>/data)\n"
        "  --out FILE      файл результатов (по умолчанию <проект>/results/results.tsv)\n"
        "  --repeats N     сколько раз повторять каждый замер, берётся медиана (по умолчанию 5)\n"
        "  --help          эта справка\n";
}

bool parseArgs(int argc, char** argv, Options& options, int& exitCode)
{
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            printUsage();
            exitCode = 0;
            return false;
        }

        const bool known = arg == "--data" || arg == "--out" || arg == "--repeats";
        if (!known || i + 1 >= argc) {
            std::cerr << "Неизвестный параметр или не указано значение: " << arg << "\n\n";
            printUsage();
            exitCode = 2;
            return false;
        }

        const std::string value = argv[++i];
        if (arg == "--data")      options.dataDir = value;
        else if (arg == "--out")  options.outFile = value;
        else {
            try {
                options.repeats = std::stoi(value);
            } catch (const std::exception&) {
                options.repeats = 0;
            }
            if (options.repeats < 1) {
                std::cerr << "--repeats должен быть целым числом >= 1\n";
                exitCode = 2;
                return false;
            }
        }
    }
    return true;
}

}

int main(int argc, char** argv)
{
    Options options;
    int exitCode = 0;
    if (!parseArgs(argc, argv, options, exitCode)) {
        return exitCode;
    }

#ifndef NDEBUG
    std::cerr << "ВНИМАНИЕ: это Debug-сборка, времена не годятся для итогового замера. "
                 "Собери в Release.\n";
#endif

    try {
        const std::filesystem::path outPath(options.outFile);
        if (outPath.has_parent_path()) {
            std::filesystem::create_directories(outPath.parent_path());
        }

        std::ofstream out(outPath);
        if (!out) {
            std::cerr << "Не удалось открыть файл результатов: " << options.outFile << '\n';
            return 1;
        }
        out << "dataset\tsize\tmethod\ttime_us\n";

        std::cout << "Данные: " << options.dataDir << ", повторов: " << options.repeats
                  << ", результаты: " << options.outFile << "\n\n";
        std::cout << "dataset\tsize\tmethod\ttime_us\n";

        const std::vector<std::string> logs = runAllBenchmarks(
            options.dataDir, options.repeats,
            [&out](const std::string& line) {
                std::cout << line << std::endl;
                out << line << std::endl;
            });

        std::size_t invalid = 0;
        for (const std::string& line : logs) {
            if (line.size() >= 3 && line.compare(line.size() - 3, 3, "\t-1") == 0) {
                ++invalid;
            }
        }

        std::cout << "\nЗамеров: " << logs.size() << ", с неверным результатом (-1): " << invalid << '\n';
        if (invalid > 0) {
            std::cout << "-1 значит, что после сортировки список не отсортирован или потерял элементы "
                         "(или алгоритм ещё заглушка).\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}