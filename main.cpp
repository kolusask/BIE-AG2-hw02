// Max 300 people
// Max 10000 collaborations

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>

#define INF 1000000

#define source 300
#define sink 301

uint32_t nNodes;
uint32_t nEdges;

using NodePair = std::pair<uint32_t, uint32_t>;
using EdgeList = std::list<NodePair>;

struct Node {
    const uint32_t* begin() { return adj; }
    const uint32_t* end() { return adj + nAdj; }
    void add_adj(const uint32_t a) { adj[nAdj++] = a; }
    bool reachable = false;
    bool open = false;
    uint32_t pred;

  private:
    uint32_t adj[350];
    uint32_t nAdj = 0;
};

Node nodes[350];

struct Edge {
    static uint32_t count;
    uint32_t capacity;
    uint32_t order;
};

uint32_t Edge::count = 0;

Edge edges[350][350];

void connect(const uint32_t n1, const uint32_t n2, const uint32_t cap) {
    edges[n1][n2].capacity = edges[n2][n1].capacity = cap;
    edges[n1][n2].order = edges[n2][n1].order = Edge::count++;
    nodes[n1].add_adj(n2);
    nodes[n2].add_adj(n1);
}

void read_type(const uint32_t extraNode) {
    uint32_t number;
    std::cin >> number;
    for (uint32_t i = 0; i < number; i++) {
        uint32_t s;
        std::cin >> s;
        connect(s, extraNode, INF);
    }
}

void read_input() {
    std::cin >> nNodes >> nEdges;
    nNodes += 2;
    for (uint32_t i = 0; i < nEdges; i++) {
        uint32_t n1, n2;
        uint32_t cap;
        std::cin >> n1 >> n2 >> cap;
        connect(n1, n2, cap);
    }
    read_type(source);
    read_type(sink);
}

bool find_augmenting_path(EdgeList& path) {
    path.clear();
    std::queue<uint32_t> queue;
    queue.push(source);
    bool found = false;
    while (!queue.empty()) {
        const uint32_t curr = queue.front();
        queue.pop();
        nodes[curr].open = true;
        for (const uint32_t a : nodes[curr]) {
            if (!nodes[a].open && edges[curr][a].capacity) {
                nodes[a].pred = curr;
                if (a == sink) {
                    found = true;
                    break;
                }
                nodes[a].open = true;
                queue.push(a);
            }
        }
    }
    if (found)
        for (uint32_t n = sink; n != source; n = nodes[n].pred)
            path.push_front(NodePair(nodes[n].pred, n));
    for (uint32_t i = 0; i < nNodes; i++)
        nodes[i].open = false;
    return found;
}

void algFordFulkerson() {
    EdgeList path;
    while (find_augmenting_path(path)) {
        auto& minPair = *std::min_element(
            path.begin(), path.end(), 
            [](const NodePair np1, const NodePair np2) -> bool {
                return edges[np1.first][np1.second].capacity < edges[np2.first][np2.second].capacity;
            }
        );
        uint32_t minCap = edges[minPair.first][minPair.second].capacity;
        for (const auto& pair : path) {
            edges[pair.first][pair.second].capacity -= minCap;
            edges[pair.second][pair.first].capacity += minCap;
        }
    }
    uint32_t maxFlow = 0;
    for (uint32_t a : nodes[sink])
        maxFlow += INF - edges[a][sink].capacity;
    std::cout << maxFlow << std::endl;
}

void mark_reachables(const uint32_t node) {
    nodes[node].open = true;
    nodes[node].reachable = true;
    for (const uint32_t a : nodes[node])
        if (!nodes[a].open && edges[node][a].capacity)
            mark_reachables(a);
}

void print_cut(const uint32_t node) {
    nodes[node].open = true;
    for (uint32_t a : nodes[node]) {
        if (!nodes[a].open) {
            if (nodes[a].reachable)
                print_cut(a);
            else
                std::cout << edges[node][a].order << ' ';
        }
    }
}

int main() {
    read_input();
    algFordFulkerson();
    mark_reachables(source);
    for (uint32_t i = 0; i < nNodes; i++)
        nodes[i].open = false;
    print_cut(source);
    std::cout << std::endl;
    return 0;
}

/*
    6 2
    0 1
    1 2
    3
    0 1 2
    3
    3 4 5
*/
