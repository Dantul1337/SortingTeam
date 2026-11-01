#pragma once

#include "linked_list.h"

#include <string>
#include <vector>

Node* loadList(const std::string& path);

std::vector<std::string> listDataFiles(const std::string& directory);

std::string datasetName(const std::string& path);