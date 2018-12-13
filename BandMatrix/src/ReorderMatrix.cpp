#include "ReorderMatrix.h"

#include <set>
#include <queue>
#include <limits>
#include <algorithm>

using Wave = std::set<size_t>;
using Waves = std::vector<Wave>;

static bool alreadyVisited(const Waves& waves, size_t node)
{
    for (auto& wave : waves) {
        auto it = wave.find(node);
        if (it != wave.end()) {
            return true;
        }
    }

    return false;
}

struct WaveElement {
    size_t node;
    size_t waveNum;
};

static Waves buildWaves(const Matrix& m, size_t startNode)
{
    const size_t totalNodes = m.size();
    std::vector<std::set<size_t>> waves = { { startNode } };
    std::queue<WaveElement> queue;
    queue.push({ startNode, 0 }); // start with wave 0

    while (not queue.empty()) {
        const auto elem = queue.front();
        queue.pop();

        const size_t waveNum = elem.waveNum + 1;
        waves.resize(waveNum + 1);

        for (size_t i = 0; i < totalNodes; i++) {
            const auto value = m[elem.node][i];
            if (value != 0 && !alreadyVisited(waves, i)) {
                waves[waveNum].insert(i);
                queue.push({i, waveNum});
            }
        }
    }

    // Last is always empty
    waves.pop_back();
    return waves;
}

static size_t getStartNode(const Matrix& m)
{
    Waves waves = buildWaves(m, 0);
    const auto& lastWave = waves.back();
    if (lastWave.size() == 1) {
        return *lastWave.begin();
    }

    for (auto node: lastWave) {
        Waves waves = buildWaves(m, node);
        const auto& lastWave = waves.back();
        if (lastWave.size() == 1) {
            return *lastWave.begin();
        }
    }

    return std::numeric_limits<size_t>::max();
}

static size_t countNeighbors(const Matrix& m, size_t node)
{
    return std::count_if(m[node].begin(), m[node].end(),
            [](auto val) { return val != 0; });
}

struct Neighbor
{
    size_t node;
    size_t neighborCount;
};

static std::vector<size_t> getNeighbors(const Matrix& m, size_t node)
{
    std::vector<Neighbor> neighbors;

    for (size_t i = 0; i < m.size(); i++) {
        if (m[node][i] != 0 && node != i) {
            const auto count = countNeighbors(m, i);
            neighbors.push_back({i, count});
        }
    }

    std::sort(neighbors.begin(), neighbors.end(),
        [](const auto& a, const auto& b) {
            return a.neighborCount < b.neighborCount;
    });

    std::vector<size_t> res;
    for (const auto& neighbor: neighbors) {
        res.push_back(neighbor.node);
    }

    return res;
}

struct NodeAndNeighbors {
    size_t node;
    std::vector<size_t> neighbors;
};

Reorder getReorder(const Matrix& m)
{
    size_t startNode = getStartNode(m);
    std::vector<NodeAndNeighbors> nodes;
    nodes.push_back({startNode, getNeighbors(m, startNode)});
    for (int i = 0; i < nodes.size(); ++i) {
        for (const auto& nnode: nodes[i].neighbors) {
            auto it = std::find_if(nodes.begin(), nodes.end(),
                [nnode](const NodeAndNeighbors& n) { return n.node == nnode; });
            const bool alreadyAdded = it != nodes.end();

            if (not alreadyAdded) {
                nodes.push_back({nnode, getNeighbors(m, nnode)});
            }
        }
    }

    Reorder reorder;
    for (const auto& node: nodes) {
        reorder.push_back(node.node);
    }

    return reorder;
}

Matrix reorder(const Matrix& m, const Reorder& r)
{
    Matrix res;
    res.resize(m.size());

    for (size_t i = 0; i < m.size(); i++) {
        res[i] = reorder(m[r[i]], r);
    }

    return res;
}

Vector reorder(const Vector& v, const Reorder& r)
{
    Vector res;
    res.resize(v.size());

    for (size_t i = 0; i < v.size(); i++) {
        res[i] = v[r[i]];
    }

    return res;
}

Vector restoreOrder(const Vector& m, const Reorder& r)
{
    Reorder reverce(r.size());
    for (size_t i = 0; i < r.size(); ++i) {
        reverce[r[i]] = i;
    }

    return reorder(m, reverce);
}
