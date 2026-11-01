#pragma once

#include "sort_interface.h"

#include <string>
#include <vector>

struct Algorithm
{
    std::string name;
    SortFunction sort;
    std::string dataDir;
};

const std::vector<Algorithm>& algorithms();