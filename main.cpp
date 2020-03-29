#include <iostream>

#define INF 100000

struct Node {
    const uint16_t* begin() { return adj; }
    const uint16_t* end() { return adj + nAdj; }
    uint16_t adj[299];
    uint16_t nAdj;
    bool reachable = false;
};

Node* nodes;

struct Edge {
    Edge(const uint8_t cap) : capacity(cap) {}
    const uint8_t capacity;
    uint8_t flow = 0;
};

int main() {

    return 0;
}
