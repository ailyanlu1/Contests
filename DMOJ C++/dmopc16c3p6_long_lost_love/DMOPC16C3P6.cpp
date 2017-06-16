/*
 * DMOPC16C3P6.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 100000
#define MAXQ 500000

using namespace std;

int arr[MAXN + 1];
int revInd = 0;
int N, Q, x, y;
char c;

struct Node {
public:
    Node* left;
    Node* right;
    int pre, suf, sum;
    Node(int val) {
        this->pre = val;
        this->suf = val;
        this->sum = val;
        this->left = this->right = nullptr;
    }

    Node(Node* l, Node* r) {
        this->left = l;
        this->right = r;
        this->pre = max(l->pre, r->pre + l->sum);
        this->suf = max(l->suf + r->sum, r->suf);
        this->sum = l->sum + r->sum;
    }
}* rev[MAXQ];

struct Query {
public:
    int pre, suf, sum;
    bool isNull;
    Query() {
        this->pre = 0;
        this->suf = 0;
        this->sum = 0;
        this->isNull = true;
    }
    Query(int pre, int suf, int sum) {
        this->pre = pre;
        this->suf = suf;
        this->sum = sum;
        this->isNull = false;
    }

    Query(Query l, Query r) {
        this->pre = max(l.pre, r.pre + l.sum);
        this->suf = max(l.suf + r.sum, r.suf);
        this->sum = l.sum + r.sum;
        this->isNull = false;
    }
};

Node* build(int l, int r) {
    if (l == r) return new Node(arr[l]);
    int m = (l + r) >> 1;
    return new Node(build(l , m), build(m + 1, r));
}

void init(int size) {
    rev[0] = build(1, size);
}

Node* update(Node* cur, int l, int r, int ind) {
    if (l <= ind && ind <= r) {
        if (l == r) return new Node(arr[l]);
        int m = (l + r) >> 1;
        return new Node(update(cur->left, l, m, ind), update(cur->right, m + 1, r, ind));
    }
    return cur;
}

void update(int ind, int val) {
    arr[ind] = val;
    rev[revInd + 1] = update(rev[revInd], 1, N, ind);
    revInd++;
}

Query query(Node* cur, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return Query();
    if (l >= ql && r <= qr) return Query(cur->pre, cur->suf, cur->sum);
    int m = (l + r) >> 1;
    Query left = query(cur->left, l, m, ql, qr);
    Query right = query(cur->right, m + 1, r, ql, qr);
    if (left.isNull) return right;
    if (right.isNull) return left;
    return Query(left, right);
}

int query(int type, int ql, int qr) {
    if (type == 1) return query(rev[revInd], 1, N, ql, qr).pre;
    return query(rev[revInd], 1, N, ql, qr).suf;
}

void revert(int x) {
    rev[++revInd] = rev[x];
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &Q);
    init(N);
    for (int i = 0; i < Q; i++) {
        scanf("%c", &c);
        if (c == 'U') {
            scanf("%d%d", &x, &y);
            update(x, y);
        } else if (c == 'G') {
            scanf("%d", &x);
            revert(x);
        } else if (c == 'P') {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(1, x, y));
        } else if (c == 'S') {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(2, x, y));
        } else {
            i--;
        }
    }
    return 0;
}
