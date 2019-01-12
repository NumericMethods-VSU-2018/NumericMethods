#include "BorderRules.h"

void countBorderRules(Matrix& matrix, Vector& f, std::map<int, double> &boundaryCondition)
{
    for (auto cond : boundaryCondition)
    {
        int nodeId = cond.first;
        double val = cond.second;

        matrix[nodeId][nodeId] = 1;
        f[nodeId] = val;

        for (int i = 1; i < matrix.size(); i++)
        {
            if (i != nodeId)
            {
                matrix[nodeId][i] = 0;
                f[i] = f[i] - matrix[i][nodeId] * val;
                matrix[i][nodeId] = 0;
            }
        }
    }
}

