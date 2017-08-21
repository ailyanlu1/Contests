/*
 * MMCC15P1.cpp
 *
 *  Created on: May 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>
#include "inaho.h"

using namespace std;

struct Node {
    int parent, size;
};

vector<Node> uf;
stack<pair<int, int>> order;

int find(int p) {
    if (uf[p].parent != p) {
        return find(uf[p].parent);
    }
    return uf[p].parent;
}

void join(int rootP, int rootQ) {
    if (rootP == rootQ) return;
    if (uf[rootP].size < uf[rootQ].size) {
        uf[rootQ].size += uf[rootP].size;
        uf[rootP].parent = rootQ;
    } else {
        uf[rootP].size += uf[rootQ].size;
        uf[rootQ].parent = rootP;
    }
}

void disjoin(int rootP, int rootQ) {
    if (rootP == rootQ) return;
    if (uf[rootP].size < uf[rootQ].size) {
        uf[rootQ].size -= uf[rootP].size;
        uf[rootP].parent = rootP;
    } else {
        uf[rootP].size -= uf[rootQ].size;
        uf[rootQ].parent = rootQ;
    }
}

void Init(int N) {
    for (int i = 0; i <= N; i++) {
        uf.push_back(Node { i, 1 });
    }
}

void AddEdge(int U, int V) {
    int rootP = find(U);
    int rootQ = find(V);
    order.push(make_pair(rootP, rootQ));
    join(rootP, rootQ);
}

void RemoveLastEdge() {
    disjoin(order.top().first, order.top().second);
    order.pop();
}

int GetSize(int U) {
    return uf[find(U)].size;
}
