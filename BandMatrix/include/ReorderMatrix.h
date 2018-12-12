#pragma once

#include "common.h"

using Reorder = std::vector<size_t>;

Reorder getReorder(const Matrix& m);
Matrix reorder(const Matrix& m, const Reorder& r);
Vector reorder(const Vector& v, const Reorder& r);

Vector restoreOrder(const Vector& m, const Reorder& r);