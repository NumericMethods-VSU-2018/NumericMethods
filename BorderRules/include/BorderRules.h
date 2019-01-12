#pragma once

#include "common.h"
#include <map>
#include <vector>

void countBorderRules(Matrix& matrix, Vector& f, const std::map<int, float> &boundaryCondition);
