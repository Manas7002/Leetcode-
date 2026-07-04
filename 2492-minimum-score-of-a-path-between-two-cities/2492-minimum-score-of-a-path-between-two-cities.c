#include <limits.h>
#include <stdlib.h>
#include <string.h>

// forward declarations
int find(int* parent, int x);
void unite(int* parent, int* rank_, int x, int y);

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    int* parent = malloc((n + 1) * sizeof(int));
    int* rank_ = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }

    for (int i = 0; i < roadsSize; i++) {
        unite(parent, rank_, roads[i][0], roads[i][1]);
    }

    int root1 = find(parent, 1);
    int minW = INT_MAX;

    for (int i = 0; i < roadsSize; i++) {
        if (find(parent, roads[i][0]) == root1) {
            if (roads[i][2] < minW) {
                minW = roads[i][2];
            }
        }
    }

    free(parent);
    free(rank_);
    return minW;
}

int find(int* parent, int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int* parent, int* rank_, int x, int y) {
    int rx = find(parent, x), ry = find(parent, y);
    if (rx == ry) return;
    if (rank_[rx] < rank_[ry]) {
        int t = rx; rx = ry; ry = t;
    }
    parent[ry] = rx;
    if (rank_[rx] == rank_[ry]) rank_[rx]++;
}