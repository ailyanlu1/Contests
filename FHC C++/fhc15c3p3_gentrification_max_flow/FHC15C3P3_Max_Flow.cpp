/*
 * FHC15C3P3_Max_Flow.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

struct FlowEdge {
private:
    // to deal with floating-point roundoff errors
    double FLOATING_POINT_EPSILON = 1E-10;

    int v;             // from
    int w;             // to
    double capacity;   // capacity
    double flow;             // flow

public:
    /**
     * Initializes an edge from vertex {@code v} to vertex {@code w} with
     * the given {@code capacity} and zero flow.
     * @param v the tail vertex
     * @param w the head vertex
     * @param capacity the capacity of the edge
     * @throws invalid_argument if either {@code v} or {@code w}
     *    is a negative integer
     * @throws invalid_argument if {@code capacity < 0.0}
     */
    FlowEdge(int v, int w, double capacity) {
        if (v < 0) throw invalid_argument("vertex index must be a non-negative integer");
        if (w < 0) throw invalid_argument("vertex index must be a non-negative integer");
        if (!(capacity >= 0.0)) throw invalid_argument("Edge capacity must be non-negative");
        this->v         = v;
        this->w         = w;
        this->capacity  = capacity;
        this->flow      = 0.0;
    }

    /**
     * Initializes an edge from vertex {@code v} to vertex {@code w} with
     * the given {@code capacity} and {@code flow}.
     * @param v the tail vertex
     * @param w the head vertex
     * @param capacity the capacity of the edge
     * @param flow the flow on the edge
     * @throws invalid_argument if either {@code v} or {@code w}
     *    is a negative integer
     * @throws invalid_argument if {@code capacity} is negative
     * @throws invalid_argument unless {@code flow} is between
     *    {@code 0.0} and {@code capacity}.
     */
    FlowEdge(int v, int w, double capacity, double flow) {
        if (v < 0) throw invalid_argument("vertex index must be a non-negative integer");
        if (w < 0) throw invalid_argument("vertex index must be a non-negative integer");
        if (!(capacity >= 0.0))  throw invalid_argument("edge capacity must be non-negative");
        if (!(flow <= capacity)) throw invalid_argument("flow exceeds capacity");
        if (!(flow >= 0.0))      throw invalid_argument("flow must be non-negative");
        this->v         = v;
        this->w         = w;
        this->capacity  = capacity;
        this->flow      = flow;
    }

    /**
     * Initializes a flow edge from another flow edge.
     * @param e the edge to copy
     */
    FlowEdge(FlowEdge *e) {
        this->v         = e->v;
        this->w         = e->w;
        this->capacity  = e->capacity;
        this->flow      = e->flow;
    }

    /**
     * Returns the tail vertex of the edge.
     * @return the tail vertex of the edge
     */
    int from() {
        return v;
    }

    /**
     * Returns the head vertex of the edge.
     * @return the head vertex of the edge
     */
    int to() {
        return w;
    }

    /**
     * Returns the capacity of the edge.
     * @return the capacity of the edge
     */
    double getCapacity() {
        return capacity;
    }

    /**
     * Returns the flow on the edge.
     * @return the flow on the edge
     */
    double getFlow() {
        return flow;
    }

    /**
     * Returns the endpoint of the edge that is different from the given vertex
     * (unless the edge represents a self-loop in which case it returns the same vertex).
     * @param vertex one endpoint of the edge
     * @return the endpoint of the edge that is different from the given vertex
     *   (unless the edge represents a self-loop in which case it returns the same vertex)
     * @throws invalid_argument if {@code vertex} is not one of the endpoints
     *   of the edge
     */
    int other(int vertex) {
        if      (vertex == v) return w;
        else if (vertex == w) return v;
        else throw invalid_argument("invalid endpoint");
    }

    /**
     * Returns the residual capacity of the edge in the direction
     *  to the given {@code vertex}.
     * @param vertex one endpoint of the edge
     * @return the residual capacity of the edge in the direction to the given vertex
     *   If {@code vertex} is the tail vertex, the residual capacity equals
     *   {@code capacity() - flow()}; if {@code vertex} is the head vertex, the
     *   residual capacity equals {@code flow()}.
     * @throws invalid_argument if {@code vertex} is not one of the endpoints of the edge
     */
    double residualCapacityTo(int vertex) {
        if      (vertex == v) return flow;              // backward edge
        else if (vertex == w) return capacity - flow;   // forward edge
        else throw invalid_argument("invalid endpoint");
    }

    /**
     * Increases the flow on the edge in the direction to the given vertex.
     *   If {@code vertex} is the tail vertex, this increases the flow on the edge by {@code delta};
     *   if {@code vertex} is the head vertex, this decreases the flow on the edge by {@code delta}.
     * @param vertex one endpoint of the edge
     * @param delta amount by which to increase flow
     * @throws invalid_argument if {@code vertex} is not one of the endpoints
     *   of the edge
     * @throws invalid_argument if {@code delta} makes the flow on
     *   on the edge either negative or larger than its capacity
     * @throws invalid_argument if {@code delta} is {@code NaN}
     */
    void addResidualFlowTo(int vertex, double delta) {
        if (!(delta >= 0.0)) throw invalid_argument("Delta must be nonnegative");

        if      (vertex == v) flow -= delta;           // backward edge
        else if (vertex == w) flow += delta;           // forward edge
        else throw invalid_argument("invalid endpoint");

        // round flow to 0 or capacity if within floating-point precision
        if (abs(flow) <= FLOATING_POINT_EPSILON)
            flow = 0;
        if (abs(flow - capacity) <= FLOATING_POINT_EPSILON)
            flow = capacity;

        if (!(flow >= 0.0))      throw invalid_argument("Flow is negative");
        if (!(flow <= capacity)) throw invalid_argument("Flow exceeds capacity");
    }
};

struct FlowNetwork {
private:
    int V;
    int E;
    vector<FlowEdge*>* adjList;

public:
    /**
     * Initializes an empty flow network with {@code V} vertices and 0 edges.
     * @param V the number of vertices
     * @throws invalid_argument if {@code V < 0}
     */
    FlowNetwork(int V) {
        if (V < 0) throw new invalid_argument("Number of vertices in a Graph must be nonnegative");
        this->V = V;
        this->E = 0;
        adjList = new vector<FlowEdge*>[V];
    }

    /**
     * Returns the number of vertices in the edge-weighted graph.
     * @return the number of vertices in the edge-weighted graph
     */
    int getV() {
        return V;
    }

    /**
     * Returns the number of edges in the edge-weighted graph.
     * @return the number of edges in the edge-weighted graph
     */
    int getE() {
        return E;
    }

    /**
     * Adds the edge {@code e} to the network.
     * @param e the edge
     * @throws IndexOutOfBoundsException unless endpoints of edge are between
     *         {@code 0} and {@code V-1}
     */
    void addEdge(FlowEdge *e) {
        int v = e->from();
        int w = e->to();
        adjList[v].push_back(e);
        adjList[w].push_back(e);
        E++;
    }

    /**
     * Returns the edges incident on vertex {@code v} (includes both edges pointing to
     * and from {@code v}).
     * @param v the vertex
     * @return the edges incident on vertex {@code v} as an Iterable
     * @throws invalid_argument unless {@code 0 <= v < V}
     */
    vector<FlowEdge*> adj(int v) {
        return adjList[v];
    }

    // return list of all edges - excludes self loops
    vector<FlowEdge*> edges() {
        vector<FlowEdge*> list;
        for (int v = 0; v < V; v++)
            for (FlowEdge *e : adj(v)) {
                if (e->to() != v)
                    list.push_back(e);
            }
        return list;
    }
};

class EdmondsKarpMaxFlow {
private:
    double FLOATING_POINT_EPSILON = 1E-10;
    int V;          // number of vertices
    bool *marked;     // marked[v] = true if s->v path in residual graph
    FlowEdge **edgeTo;    // edgeTo[v] = last edge on shortest residual s->v path
    double value;         // current value of max flow

    // is there an augmenting path?
    // if so, upon termination edgeTo[] will contain a parent-link representation of such a path
    // this implementation finds a shortest augmenting path (fewest number of edges),
    // which performs well both in theory and in practice
    bool hasAugmentingPath(FlowNetwork *G, int s, int t) {
        edgeTo = new FlowEdge*[G->getV()];
        marked = new bool[G->getV()];
        for (int i = 0; i < G->getV(); i++) {
            marked[i] = false;
        }
        // breadth-first search
        queue<int> q;
        q.push(s);
        marked[s] = true;
        while (!q.empty() && !marked[t]) {
            int v = q.front();
            q.pop();

            for (FlowEdge *e : G->adj(v)) {
                int w = e->other(v);

                // if residual capacity from v to w
                if (e->residualCapacityTo(w) > 0) {
                    if (!marked[w]) {
                        edgeTo[w] = e;
                        marked[w] = true;
                        q.push(w);
                    }
                }
            }
        }

        // is there an augmenting path?
        return marked[t];
    }

    // return excess flow at vertex v
    double excess(FlowNetwork *G, int v) {
        double excessCapacity = 0.0;
        for (FlowEdge *e : G->adj(v)) {
            if (v == e->from()) excessCapacity -= e->getFlow();
            else               excessCapacity += e->getFlow();
        }
        return excessCapacity;
    }


public:
    /**
     * Compute a maximum flow and minimum cut in the network {@code G}
     * from vertex {@code s} to vertex {@code t}.
     *
     * @param  G the flow network
     * @param  s the source vertex
     * @param  t the sink vertex
     * @throws invalid_argument unless {@code 0 <= s < V}
     * @throws invalid_argument unless {@code 0 <= t < V}
     * @throws invalid_argument if {@code s == t}
     * @throws invalid_argument if initial flow is infeasible
     */
    EdmondsKarpMaxFlow(FlowNetwork *G, int s, int t) {
        V = G->getV();
        if (s == t)               throw invalid_argument("Source equals sink");

        // while there exists an augmenting path, use it
        value = excess(G, t);
        while (hasAugmentingPath(G, s, t)) {
            // compute bottleneck capacity
            double bottle = numeric_limits<double>::infinity();
            for (int v = t; v != s; v = edgeTo[v]->other(v)) {
                bottle = min(bottle, edgeTo[v]->residualCapacityTo(v));
            }

            // augment flow
            for (int v = t; v != s; v = edgeTo[v]->other(v)) {
                edgeTo[v]->addResidualFlowTo(v, bottle);
            }

            value += bottle;
        }
    }

    /**
     * Returns the value of the maximum flow.
     *
     * @return the value of the maximum flow
     */
    double getValue()  {
        return value;
    }

    /**
     * Returns true if the specified vertex is on the {@code s} side of the mincut.
     *
     * @param  v vertex
     * @return {@code true} if vertex {@code v} is on the {@code s} side of the micut;
     *         {@code false} otherwise
     * @throws invalid_argument unless {@code 0 <= v < V}
     */
    bool inCut(int v)  {
        return marked[v];
    }
};

#define MAXN 500

int N, M;
bool connected[MAXN][MAXN];

void run(int testCaseNum) {
    ri(N);
    ri(M);
    Fill(connected, false);
    for (int i = 0; i < N; i++) {
        connected[i][i] = true;
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        ri(a);
        ri(b);
        connected[a][b] = true;
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                connected[i][j] = connected[i][j] || (connected[i][k] && connected[k][j]);
            }
        }
    }
    FlowNetwork G(N * 2 + 2);
    int s = 2 * N;
    int t = 2 * N + 1;
    for (int i = 0; i < N; i++) {
        G.addEdge(new FlowEdge(s, i, 1));
        G.addEdge(new FlowEdge(N + i, t, 1));
    }
    for (int i = 0; i < N; i++) {
        G.addEdge(new FlowEdge(N + i, i, 1));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (connected[i][j] && !connected[j][i]) G.addEdge(new FlowEdge(i, N + j, 1));
        }
    }
    EdmondsKarpMaxFlow maxFlow(&G, s, t);
    printf("Case #%d: %d\n", testCaseNum, (int) (N - maxFlow.getValue()));
}

int main() {
    freopen("gentrification.txt", "r", stdin);
    freopen("gentrification.out", "w", stdout);
    int T;
    ri(T);
    for (int i = 1; i <= T; i++) {
        run(i);
    }
    return 0;
}
