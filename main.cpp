#include <iostream>

#define INF 100000

#define source 300
#define sink 301

uint16_t nNodes;
uint16_t nEdges;

struct Node {
    const uint16_t* begin() { return adj; }
    const uint16_t* end() { return adj + nAdj; }
    void add_adj(const uint16_t a) { adj[nAdj++] = a; }
    bool reachable = false;

  private:
    uint16_t adj[299];
    uint16_t nAdj = 0;
};

Node nodes[300];

struct Edge {
    uint8_t capacity;
    uint8_t flow = 0;
};

Edge edges[301][301];

void connect(const uint16_t n1, const uint16_t n2, const uint8_t cap) {
    edges[n1][n2].capacity = edges[n2][n1].capacity = cap;
    nodes[n1].add_adj(n2);
    nodes[n2].add_adj(n1);
}

void read_type(const uint16_t extraNode) {
    uint16_t number;
    std::cin >> number;
    for (uint16_t i = 0; i < number; i++) {
        uint16_t s;
        std::cin >> s;
        connect(s, extraNode, INF);
    }
}

void read_input() {
    // Process first line
    std::cin >> nNodes >> nEdges;
    nNodes += 2;

    // Read edge definitions
    for (uint16_t i = 0; i < nEdges; i++) {
        uint32_t n1, n2;
        uint8_t cap;
        std::cin >> n1 >> n2 >> cap;
        connect(n1, n2, cap);
    }

    // Process sources
    read_type(source);

    // Process sinks
    read_type(sink);
}

int main() {
    read_input();

    return 0;
}
