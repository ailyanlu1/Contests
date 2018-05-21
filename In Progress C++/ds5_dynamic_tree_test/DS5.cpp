#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

mt19937 rng(time(0));
uniform_real_distribution<double> dis(0.0, 1.0);

#define NONE 0
#define ASSIGN 1
#define INC 2

struct Node {
public:
    int vertex;
    bool isPre;
    int val;
    int depth = 0;
    int chain = 0;
    int subtreeSum = 0;
    int subtreeMax = 0;
    int subtreeMin = 0;
    int lazyChain = -1;
    int lazyVal = 0;
    int lazyFlag = NONE;
    bool rev = 0;
    double priority;
    int preCnt;
    int size;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    Node(int vertex, bool isPre, int val, double priority, int size = 1) :
            vertex(vertex), isPre(isPre), val(val), priority(priority), preCnt(isPre), size(size) {}
};

int size(Node *x) {
    return x ? x->size : 0;
}

Node *root(Node *x) {
    if (!x) return nullptr;
    while (x->parent) x = x->parent;
    return x;
}

Node *min(Node *x) {
    if (!x) return nullptr;
    while (x->left) x = x->left;
    return x;
}

Node *max(Node *x) {
    if (!x) return nullptr;
    while (x->right) x = x->right;
    assert(x);
    return x;
}

void applyVal(Node *x, int val, int flag) {
    if (x) {
        if (flag == ASSIGN) {
            x->subtreeSum = val * x->preCnt;
            x->subtreeMax = val;
            x->subtreeMin = val;
            x->val = x->isPre ? val : 0;
            x->lazyVal = val;
            x->lazyFlag = flag;
        } else if (flag == INC) {
            x->subtreeSum += val * x->preCnt;
            x->subtreeMax += val;
            x->subtreeMin += val;
            x->val += x->isPre ? val : 0;
            x->lazyVal += val;
            x->lazyFlag = flag;
        }
    }
}

void applyChain(Node *x, int val) {
    if (x) {
        x->chain = val;
        x->lazyChain = val;
    }
}

void applyRev(Node *x) {
    if (x) x->rev ^= 1;
}

void update(Node *x) {
    if (x) {
        x->size = 1;
        x->preCnt = x->isPre;
        x->depth = x->isPre ? 1 : -1;
        x->subtreeSum = x->isPre ? x->val : 0;
        x->subtreeMax = x->isPre ? x->val : -INT_INF;
        x->subtreeMin = x->isPre ? x->val : INT_INF;
        if (x->left) {
            x->left->parent = x;
            x->size += x->left->size;
            x->preCnt += x->left->preCnt;
            x->depth += x->left->depth;
            x->subtreeSum += x->left->subtreeSum;
            x->subtreeMax = max(x->subtreeMax, x->left->subtreeMax);
            x->subtreeMin = min(x->subtreeMin, x->left->subtreeMin);
        }
        if (x->right) {
            x->right->parent = x;
            x->size += x->right->size;
            x->preCnt += x->right->preCnt;
            x->depth += x->right->depth;
            x->subtreeSum += x->right->subtreeSum;
            x->subtreeMax = max(x->subtreeMax, x->right->subtreeMax);
            x->subtreeMin = min(x->subtreeMin, x->right->subtreeMin);
        }
    }
}

void propagate(Node *x) {
    if (x) {
        if (x->rev) {
            swap(x->left, x->right);
            if (x->left) x->left->rev ^= 1;
            if (x->right) x->right->rev ^= 1;
            x->rev = 0;
        }
        if (x->lazyFlag == ASSIGN) {
            if (x->left) {
                x->left->subtreeSum = x->lazyVal * x->left->preCnt;
                x->left->subtreeMax = x->lazyVal;
                x->left->subtreeMin = x->lazyVal;
                x->left->val = x->isPre ? x->lazyVal : 0;
                x->left->lazyVal = x->lazyVal;
                x->left->lazyFlag = x->lazyFlag;
            }
            if (x->right) {
                x->right->subtreeSum = x->lazyVal * x->right->preCnt;
                x->right->subtreeMax = x->lazyVal;
                x->right->subtreeMin = x->lazyVal;
                x->right->val = x->isPre ? x->lazyVal : 0;
                x->right->lazyVal = x->lazyVal;
                x->right->lazyFlag = x->lazyFlag;
            }
        } else if (x->lazyFlag == INC) {
            if (x->left) {
                x->left->subtreeSum += x->lazyVal * x->left->preCnt;
                x->left->subtreeMax += x->lazyVal;
                x->left->subtreeMin += x->lazyVal;
                x->left->val += x->isPre ? x->lazyVal : 0;
                x->left->lazyVal += x->lazyVal;
                x->left->lazyFlag = x->lazyFlag;
            }
            if (x->right) {
                x->right->subtreeSum += x->lazyVal * x->right->preCnt;
                x->right->subtreeMax += x->lazyVal;
                x->right->subtreeMin += x->lazyVal;
                x->right->val += x->isPre ? x->lazyVal : 0;
                x->right->lazyVal += x->lazyVal;
                x->right->lazyFlag = x->lazyFlag;
            }
        }
        x->lazyFlag = NONE;
        x->lazyVal = 0;
        if (x->lazyChain != -1) {
            if (x->left) {
                x->left->chain = x->lazyChain;
                x->left->lazyChain = x->lazyChain;
            }
            if (x->right) {
                x->right->chain = x->lazyChain;
                x->right->lazyChain = x->lazyChain;
            }
            x->lazyChain = -1;
        }
    }
}

int index(Node *x) {
    int ind = size(x->left);
    for (; x->parent; x = x->parent) if (x->parent->left != x) ind += 1 + size(x->parent->left);
    return ind;
}

void merge(Node *&x, Node *l, Node *r) {
    propagate(l);
    propagate(r);
    if (!l || !r) {
        x = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(l->right, l->right, r);
        x = l;
    } else {
        merge(r->left, l, r->left);
        x = r;
    }
    update(x);
}

void split(Node *x, Node *&l, Node *&r, int ind) {
    if (!x) {
        l = r = nullptr;
        return;
    }
    propagate(x);
    x->parent = nullptr;
    if (ind <= size(x->left)) {
        split(x->left, l, x->left, ind);
        r = x;
    } else {
        split(x->right, x->right, r, ind - size(x->left) - 1);
        l = x;
    }
    update(x);
}

#define MAXN 100005

int N, M, R, parent[MAXN], sz[MAXN], heavyInd[MAXN], chainNum;
Node *pre[MAXN], *post[MAXN];
uset<int> adj[MAXN];
vector<int> head, chainLen;

void init(int N) {
    Node *dummy = nullptr;
    for (int i = 0; i < N; i++) {
        pre[i] = new Node(i, 0, dis(rng), true);
        post[i] = new Node(i, 0, dis(rng), false);
        merge(dummy, pre[i], post[i]);
    }
}

// returns true if and only if w is in the subtree of v
bool inSubtree(int v, int w, bool inclusive) {
    return index(pre[v]) < index(pre[w]) + inclusive && index(post[v]) >= index(post[w]);
}

void createEdge(int v, int w) {
    parent[w] = v;
    Node *l = nullptr, *r = nullptr;
    split(root(pre[v]), l, r, index(pre[v]) + 1);
    merge(l, l, root(pre[w]));
    merge(l, l, r);
}

bool swapSubtrees(int v, int w) {
    Node *l = nullptr, *vv = nullptr, *mid = nullptr, *ww = nullptr, *r = nullptr;
    int preIndV = index(pre[v]), preIndW = index(pre[w]), postIndV = index(post[v]), postIndW = index(post[w]);
    if (preIndV > preIndW) {
        swap(v, w);
        swap(preIndV, preIndW);
        swap(postIndV, postIndW);
    }
    if (preIndV <= preIndW && postIndV >= postIndW) return false;
    split(root(pre[v]), l, vv, preIndV);
    split(vv, vv, mid, postIndV - preIndV + 1);
    split(mid, mid, ww, preIndW - postIndV - 1);
    split(ww, ww, r, postIndW - preIndW + 1);
    merge(l, l, ww);
    merge(l, l, mid);
    merge(l, l, vv);
    merge(l, l, r);
//    adj[parent[v]].erase(v);
//    adj[v].erase(parent[v]);
//    adj[parent[w]].erase(w);
//    adj[w].erase(parent[w]);
//    swap(parent[v], parent[w]);
//    adj[parent[v]].insert(v);
//    adj[v].insert(parent[v]);
//    adj[parent[w]].insert(w);
//    adj[w].insert(parent[w]);
    return true;
}

int getSubtree(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    int ret = mid->subtreeSum;
    merge(l, l, mid);
    merge(l, l, r);
    return ret;
}

int getSubtreeMax(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    int ret = mid->subtreeMax;
    merge(l, l, mid);
    merge(l, l, r);
    return ret;
}

int getSubtreeMin(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    int ret = mid->subtreeMin;
    merge(l, l, mid);
    merge(l, l, r);
    return ret;
}

void updateValue(int v, int val, int flag) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    applyVal(mid, val, flag);
    merge(l, l, mid);
    merge(l, l, r);
}

void assignChain(int v, int len, int val) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, len);
    applyChain(mid, val);
    merge(l, l, mid);
    merge(l, l, r);
}

void reverse(int lInd, int rInd) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[lInd]), l, mid, lInd);
    split(mid, mid, r, rInd - lInd + 1);
    applyRev(mid);
    merge(l, l, mid);
    merge(l, l, r);
}

pii getDepthAndChain(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, 1);
    pii ret = {l ? l->depth : 0, mid->chain};
    merge(l, l, mid);
    merge(l, l, r);
    return ret;
}

// changes the parent of v to w
void changeParent(int v, int w) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    pii parVDC = getDepthAndChain(parent[v]);
    pii vDC = getDepthAndChain(v);
    pii headDC = getDepthAndChain(head[parent[v]]);
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    merge(l, l, r);
    int curLen = chainLen[vDC.s];
    if (parVDC.s == vDC.s) {
        chainLen[parVDC.s] = vDC.f - headDC.f;
        curLen -= chainLen[parVDC.s];
        head.push_back(v);
        chainLen.push_back(curLen);
        chainNum++;
        assignChain(v, curLen, chainNum);
    }
    adj[parent[v]].erase(v);
    adj[v].erase(parent[v]);
    parent[v] = w;
    adj[parent[v]].insert(v);
    adj[v].insert(parent[v]);
    l = nullptr, mid = nullptr, r = nullptr;
    split(root(pre[w]), l, r, index(post[w]));
    merge(l, l, mid);
    merge(l, l, r);
}

void reroot(int r) {
    int v = r;
    chainNum++;
    head.push_back(r);
    chainLen.push_back(0);
    while (v != -1) {
        pii headDC = getDepthAndChain(head[pre[v]->chain]), vDC = getDepthAndChain(v);
        int indHead = index(pre[head[pre[v]->chain]]), indV = index(pre[v]);

        reverse(indHead, indV);

    }
}

void dfsInit(int v, int prev) {
    for (int w : adj[v]) {
        if (w == prev) continue;
        createEdge(v, w);
        dfsInit(w, v);
    }
}

void dfsSize(int v, int prev, int d) {
    pre[v]->depth = post[v]->depth = d;
    parent[v] = prev;
    sz[v] = 1;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfsSize(w, v, d + 1);
        sz[v] += sz[w];
        if (sz[w] > sz[*adj[v].begin()]) {
            swapSubtrees(w, *adj[v].begin());
            heavyInd[v] = w;
        }
    }
}

void dfsHLD(int v, int prev) {
    if (chainNum == (int) head.size()) {
        head.push_back(v);
        chainLen.push_back(0);
    }
    pre[v]->chain = chainNum;
    chainLen[chainNum]++;
    if (heavyInd[v] != -1) dfsHLD(heavyInd[v], v);
    for (int w : adj[v]) {
        if (w == prev || w == heavyInd[v]) continue;
        chainNum++;
        dfsHLD(w, v);
    }
}

void rebuildHLD() {
    head.clear();
    chainLen.clear();
    chainNum = 0;
    for (int i = 0; i < N; i++) heavyInd[i] = -1;
    dfsSize(0, -1, 0);
    dfsHLD(0, -1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    return 0;
}
