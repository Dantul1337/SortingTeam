#include "data_loader.h"
 
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>

Node* loadList(const std::string& path){
    std::ifstream in(path);
    if(!in){
        throw std::runtime_error("Cannot open data file: " + path);
    }
    
    std::size_t count = 0;
    if(!(in >> count)){
        throw std::runtime_error("Missing element count in: " + path);
    }

    std::vector<int> values;
    values.reserve(count);
    int value = 0;
    while (values.size() < count && (in >> value)){
        values.push_back(value);
    }
    if(values.size() != count){
        throw std::runtime_error("Expected " + std::to_string(count) + " numbers, got " + std::to_string(values.size()) + " in: " + path);
    }
    if (in >> value){
        throw std::runtime_error("Extra data after " + std::to_string(count) + " numbers in: " + path);
    }

    return createList(values.data(), values.size());
}

std::vector<std::string> listDataFiles(const std::string& directory){
    namespace fs = std::filesystem;
    std::vector<std::string> files;
    std::error_code ec;
    if(!fs::is_directory(directory, ec)){
        return files;
    }
    for (const auto& entry : fs:: directory_iterator(directory, ec)){
        if (entry.is_regular_file() && entry.path().extension()== ".txt"){
            files.push_back(entry.path().string());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

std::string datasetName(const std::string& path){
    return std::filesystem::path(path).stem().string();
}