#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

typedef int unit;
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

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

class illegal_argument_exception: public runtime_error {
public:
    illegal_argument_exception(): runtime_error("No such element exists"){}
    illegal_argument_exception(string message): runtime_error(message){}
};

/**
 *  The {@code IndexPQ} class represents an indexed priority queue of
 *  generic keys.
 *  It supports the usual <em>insert</em> and <em>pop</em>
 *  operations, along with <em>remove</em> and <em>change-the-key</em>
 *  methods. In order to let the client refer to items on the priority queue,
 *  an index of any type is associated with each key.
 *  The client uses this type to specify which key to delete or change.
 *  It also supports methods for peeking at the top key, testing if the
 *  priority queue is empty, and iterating through the keys.
 *  <p>
 *  This implementation uses a binary heap along with an array to associate
 *  keys with integers in the given range.
 *  The <em>insert</em>, <em>pop</em>, <em>remove</em>,
 *  <em>change-key</em>, <em>decrease-key</em>, and <em>increase-key</em>
 *  operations take logarithmic time.
 *  The <em>is-empty</em>, <em>size</em>, <em>top</em>,
 *  and <em>key-of</em> operations take constant time.
 *  Construction takes time proportional to the specified capacity.
 */
template <typename Index, typename Key, typename Comparator = less<Key>>
struct IndexPQ {
private:
    Comparator cmp;

    const int INIT_CAPACITY = 4;            // default capacity
    int n;                                  // number of elements on PQ
    Index *pq;                                // binary heap using 1-based indexing
    unordered_map<Index, int> qp;           // inverse of pq; qp[i] = heap location of the key at index i; qp[pq[i]] = pq[qp[i]] = i
    unordered_map<Index, Key> keys;         // keys[i] = priority of index i

    // helper function to double the size of the heap array
    void resize(int capacity) {
        // assert capacity > n;
        Index *newpq = new Index[capacity];
        for (int i = 1; i <= n; i++) {
            newpq[i] = pq[i];
        }
        swap(newpq, pq);
        delete[](newpq);
    }

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
    /**
     * Initializes an empty indexed priority queue.
     */
    IndexPQ() {
        n = 0;
        pq = new Index[INIT_CAPACITY];
    }

    /**
     * Initializes an empty indexed priority queue with an initial capacity.
     *
     * @param N the initial capacity of the priority queue
     */
    IndexPQ(int N) {
        n = 0;
        pq = new Index[N + 1];
    }

    /**
     * Returns true if this priority queue is empty.
     *
     * @return {@code true} if this priority queue is empty;
     *         {@code false} otherwise
     */
    bool isEmpty() {
        return n == 0;
    }

    /**
     * Is {@code i} an index on this priority queue?
     *
     * @param  i an index
     * @return {@code true} if {@code i} is an index on this priority queue;
     *         {@code false} otherwise
     */
    bool contains(Index i) {
        return qp.count(i);
    }

    /**
     * Returns the number of keys on this priority queue.
     *
     * @return the number of keys on this priority queue
     */
    int size() {
        return n;
    }

    /**
      * Associate key with index i.
      *
      * @param  i an index
      * @param  key the key to associate with index {@code i}
      * @throws illegal_argument_exception if there already is an item
      *         associated with index {@code i}
      */
     void insert(Index i, Key key) {
         if (contains(i)) throw illegal_argument_exception("index is already in the priority queue");
         n++;
         qp[i] = n;
         pq[n] = i;
         keys[i] = key;
         swim(n);
     }

     /**
      * Returns a pair containing the index and key at the top of the heap.
      *
      * @return a pair containing the index and key at the top of the heap
      * @throws no_such_element_exception if this priority queue is empty
      */
     pair<Index, Key> top() {
         if (n == 0) throw no_such_element_exception("Priority queue underflow");
         return make_pair(pq[1], keys[pq[1]]);
     }

     /**
      * Removes the top key and returns a pair containing its associated index
      * and the key removed.
      *
      * @return a pair containing the index and key at the top of the heap
      * @throws no_such_element_exception if this priority queue is empty
      */
     pair<Index, Key> pop() {
         if (n == 0) throw no_such_element_exception("Priority queue underflow");
         Index minInd = pq[1];
         Key minKey = keys[minInd];
         exch(1, n--);
         sink(1);
         // assert pq[n+1] == min;
         qp.erase(minInd);        // delete
         keys.erase(minInd);
         pq[n+1] = -1;        // not needed
         return make_pair(minInd, minKey);
     }

     /**
      * Returns the key associated with index {@code i}.
      *
      * @param  i the index of the key to return
      * @return the key associated with index {@code i}
      * @throws no_such_element_exception no key is associated with index {@code i}
      */
     Key keyOf(Index i) {
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         else return keys[i];
     }

     /**
      * Change the key associated with index {@code i} to the specified value.
      *
      * @param  i the index of the key to change
      * @param  key change the key associated with index {@code i} to this key
      * @throws no_such_element_exception no key is associated with index {@code i}
      */
     void changeKey(Index i, Key key) {
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         Key old = keys[i];
         keys[i] = key;
         if (cmp(old, key)) swim(qp[i]);
         else if (cmp(key, old)) sink(qp[i]);
     }

     /**
      * Removes the key on the priority queue associated with index {@code i}.
      *
      * @param  i the index of the key to remove
      * @throws no_such_element_exception no key is associated with index {@code i}
      */
     void remove(Index i) {
         if (!contains(i)) throw no_such_element_exception("index is not in the priority queue");
         int index = qp[i];
         exch(index, n--);
         swim(index);
         sink(index);
         qp.erase(i);
         keys.erase(i);
     }
};

int N, M, u, v, w;
WeightedGraph *G;

unit *distTo;
WeightedEdge **edgeTo;

const unit INF = INT_INF;

void dijkstraSP(int s) {
    IndexPQ<int, unit, greater<unit>> PQ(G->getV());
    distTo = new unit[G->getV()];
    edgeTo = new WeightedEdge *[G->getV()];
    for (int v = 0; v < G->getV(); v++) {
        distTo[v] = INF;
    }
    distTo[s] = 0;
    PQ.insert(s, distTo[s]);
    while (!PQ.isEmpty()) {
        int v = PQ.pop().first;
        for (WeightedEdge *e : G->adj(v)) {
            int w = e->other(v);
            if (distTo[w] > distTo[v] + e->getWeight()) {
                distTo[w] = distTo[v] + e->getWeight();
                edgeTo[w] = e;
                if (PQ.contains(w)) PQ.changeKey(w, distTo[w]);
                else PQ.insert(w, distTo[w]);
            }
        }
    }
}

int main() {
    ri(N);
    ri(M);
    G = new WeightedGraph(N);
    FOR(i, M) {
        ri(u);
        ri(v);
        ri(w);
        u--;
        v--;
        G->addEdge(new WeightedEdge(u, v, w));
    }
    dijkstraSP(0);
    FOR(i, N) {
        if (distTo[i] == INF) printf("-1\n");
        else printf("%d\n", (int) distTo[i]);
    }
    return 0;
}
