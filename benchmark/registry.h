#pragma once

#include "sort_interface.h"

#include <string>
#include <vector>

struct Algorithm
{
    std::string name;
    SortFunction sort;
};

const std::vector<Algorithm>& algorithms();