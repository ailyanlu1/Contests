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

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

// convention is same as priority_queue in STL
template <typename Key, typename Comparator = less<Key>>
struct ArrayIndexPQ {
private:
    Comparator cmp;

    int maxN;       // the maximum number of elements in the priority queue
    int n;          // number of elements on PQ
    int *pq;        // binary heap using 1-based indexing
    int *qp;        // inverse of pq; qp[i] = heap location of the key at index i; qp[pq[i]] = pq[qp[i]] = i
    Key *keys;      // keys[i] = priority of index i

    void exch(int i, int j) {
        swap(pq[i], pq[j]);
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    void swim(int k) {
        while (k > 1 && cmp(keys[pq[k/2]], keys[pq[k]])) {
            exch(k, k/2);
            k = k/2;
        }
    }

    void sink(int k) {
        while (2*k <= n) {
            int j = 2*k;
            if (j < n && cmp(keys[pq[j]], keys[pq[j+1]])) j++;
            if (!cmp(keys[pq[k]], keys[pq[j]])) break;
            exch(k, j);
            k = j;
        }
    }

public:
    ArrayIndexPQ(int maxN) {
        assert(maxN >= 0);
        this->maxN = maxN;
        n = 0;
        keys = new Key[maxN];
        pq = new int[maxN + 1];
        qp = new int[maxN];
        for (int i = 0; i < maxN; i++) qp[i] = -1;
    }

    ~ArrayIndexPQ() {
        delete[](pq);
        delete[](qp);
        delete[](keys);
    }

    bool isEmpty() {
        return n == 0;
    }

    bool contains(int i) {
        assert(0 <= i && i < maxN);
        return qp[i] != -1;
    }

    int size() {
        return n;
    }

     void insert(int i, Key key) {
         assert(0 <= i && i < maxN);
         if (contains(i)) throw invalid_argument("index is already in the priority queue");
         n++;
         qp[i] = n;
         pq[n] = i;
         keys[i] = key;
         swim(n);
     }

     pair<int, Key> top() {
         if (n == 0) throw no_such_element_exception("Priority queue underflow");
         return make_pair(pq[1], keys[pq[1]]);
     }

     pair<int, Key> pop() {
         if (n == 0) throw no_such_element_exception("Priority queue underflow");
         int minInd = pq[1];
         Key minKey = keys[minInd];
         exch(1, n--);
         sink(1);
         // assert pq[n+1] == min;
         qp[minInd] = -1;        // delete
         pq[n+1] = -1;        // not needed
         return make_pair(minInd, minKey);
     }

     Key keyOf(int i) {
         assert(0 <= i && i < maxN);
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         else return keys[i];
     }

     void changeKey(int i, Key key) {
         assert(0 <= i && i < maxN);
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         Key old = keys[i];
         keys[i] = key;
         if (cmp(old, key)) swim(qp[i]);
         else if (cmp(key, old)) sink(qp[i]);
     }

     void remove(int i) {
         assert(0 <= i && i < maxN);
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         int index = qp[i];
         exch(index, n--);
         swim(index);
         sink(index);
         qp[i] = -1;
     }
};

typedef ll unit;
const ll INF = LL_INF;
struct WeightedEdge {
private:
    int v, w;
    unit weight;

public:
    WeightedEdge(int v, int w, unit weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    unit getWeight() {
        return weight;
    }

    int either() {
        return v;
    }

    int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw new invalid_argument("Illegal endpoint");
    }

    bool operator == (const WeightedEdge &e) const {
        return (((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) const {
        return !(((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator < (const WeightedEdge &e) const {
        return (weight < e.weight);
    }

    bool operator <= (const WeightedEdge &e) const {
        return (weight <= e.weight);
    }

    bool operator > (const WeightedEdge &e) const {
        return (weight > e.weight);
    }

    bool operator >= (const WeightedEdge &e) const {
        return (weight >= e.weight);
    }
};

struct WeightedEdge_less {
    const bool operator ()(const WeightedEdge *a, const WeightedEdge *b) const {
        return *a < *b;
    }
};

struct WeightedEdge_greater {
    const bool operator ()(const WeightedEdge *a, const WeightedEdge *b) const {
        return *a > *b;
    }
};

bool WeightedEdge_p_cmp_less (WeightedEdge *a, WeightedEdge *b) {
    return *a < *b;
}

bool WeightedEdge_p_cmp_greater (WeightedEdge *a, WeightedEdge *b) {
    return *a > *b;
}

struct WeightedGraph {
private:
    int V;
    int E;
    vector<WeightedEdge*> *adjList;

public:
    WeightedGraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<WeightedEdge*>[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(WeightedEdge *e) {
        int v = e->either();
        int w = e->other(v);
        adjList[v].push_back(e);
        adjList[w].push_back(e);
        E++;
    }

    vector<WeightedEdge*> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<WeightedEdge*> &edges() {
        vector<WeightedEdge*> *list = new vector<WeightedEdge*>;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (WeightedEdge *e : adj(v)) {
                if (e->other(v) > v) {
                    list->push_back(e);
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (e->other(v) == v) {
                    if (selfLoops % 2 == 0) list->push_back(e);
                    selfLoops++;
                }
            }
        }
        return *list;
    }
};

struct UF {
private:
    int *parent;
    char *rank; // equivalent to byte
    int count;

public:
    UF(int n) {
        count = n;
        parent = new int[n];
        rank = new char[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }

    int getCount() {
        return count;
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    int getRank(int p) {
        return (int) rank[find(p)];
    }

    bool join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return false;
        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
        return true;
    }
};

class StoerWagnerMinCut {
private:
    // the weight of the minimum cut
    unit weight = INF;

    // cut[v] = true if v is on the first subset of vertices of the minimum cut;
    // or false if v is on the second subset
    bool *cut;

    // number of vertices
    int V;

    class CutPhase {
    public:
        unit weight; // the weight of the minimum s-t cut
        int s;         // the vertex s
        int t;         // the vertex t
        CutPhase(unit weight, int s, int t) {
            this->weight = weight;
            this->s = s;
            this->t = t;
        }
    };

    void makeCut(int t, UF *uf) {
        for (int v = 0; v < V; v++) cut[v] = uf->connected(v, t);
    }

    CutPhase *minCutPhase(WeightedGraph *G, bool *marked, CutPhase *cp) {
        ArrayIndexPQ<unit, less<unit>> pq(V);
        for (int v = 0; v < V; v++) if (v != cp->s && !marked[v]) pq.insert(v, 0);
        pq.insert(cp->s, INF);
        while (!pq.isEmpty()) {
            int v = pq.top().first;
            pq.pop();
            cp->s = cp->t;
            cp->t = v;
            for (WeightedEdge *e : G->adj(v)) {
                int w = e->other(v);
                if (pq.contains(w)) pq.changeKey(w, pq.keyOf(w) + e->getWeight());
            }
        }
        cp->weight = 0;
        for (WeightedEdge *e : G->adj(cp->t)) cp->weight += e->getWeight();
        return cp;
    }

    WeightedGraph *contractEdge(WeightedGraph *G, int s, int t) {
        WeightedGraph *H = new WeightedGraph(V);
        for (int v = 0; v < V; v++) {
            for (WeightedEdge *e : G->adj(v)) {
                int w = e->other(v);
                if ((v == s && w == t) || (v == t && w == s)) continue;
                if (v < w) {
                    if (w == t) H->addEdge(new WeightedEdge(v, s, e->getWeight()));
                    else if (v == t) H->addEdge(new WeightedEdge(w, s, e->getWeight()));
                    else H->addEdge(new WeightedEdge(v, w, e->getWeight()));
                }
            }
        }
        return H;
    }

    void minCut(WeightedGraph *G, int a) {
        UF *uf = new UF(V);
        bool *marked = new bool[V];
        cut = new bool[V];
        for (int v = 0; v < V; v++) {
            marked[v] = false;
            cut[v] = false;
        }
        CutPhase *cp = new CutPhase(0, a, a);
        for (int v = V; v > 1; v--) {
            cp = minCutPhase(G, marked, cp);
            if (cp->weight < weight) {
                weight = cp->weight;
                makeCut(cp->t, uf);
            }
            G = contractEdge(G, cp->s, cp->t);
            marked[cp->t] = true;
            uf->join(cp->s, cp->t);
        }
    }

public:
    StoerWagnerMinCut(WeightedGraph *G) {
        V = G->getV();
        minCut(G, 0);
    }

    unit getWeight() {
        return weight;
    }

    bool getCut(int v) {
        return cut[v];
    }
};

int N, M;
WeightedGraph *G;
StoerWagnerMinCut *mc;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    G = new WeightedGraph(N);
    int k, a, b, c;
    ll f, tot = 0;
    FOR(i, M) {
        cin >> k >> f;
        tot += 2 * f;
        if (k == 2) {
            cin >> a >> b;
            a--; b--;
            G->addEdge(new WeightedEdge(a, b, 2 * f));
        } else {
            cin >> a >> b >> c;
            a--; b--; c--;
            G->addEdge(new WeightedEdge(a, b, f));
            G->addEdge(new WeightedEdge(b, c, f));
            G->addEdge(new WeightedEdge(c, a, f));
        }
    }
    mc = new StoerWagnerMinCut(G);
    cout << (tot - mc->getWeight()) / 2 << nl;
    return 0;
}
