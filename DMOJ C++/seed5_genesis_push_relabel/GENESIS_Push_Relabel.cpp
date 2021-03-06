/*
 * GENESIS_Push_Relabel.cpp
 *
 *  Created on: Jul 30, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
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
     */
    vector<FlowEdge*> &adj(int v) {
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

class PushRelabelMaxFlow {
private:
    const double FLOATING_POINT_EPSILON = 1E-10;
    double value;
    int *height;
    double *excess;
    bool *done;

public:
    /**
     * Compute a maximum flow in the network {@code G}
     * from vertex {@code s} to vertex {@code t}.
     *
     * @param  G the flow network
     * @param  s the source vertex
     * @param  t the sink vertex
     * @throws invalid_argument if {@code s == t}
     */
    PushRelabelMaxFlow(FlowNetwork *G, int s, int t) {
        if (s == t) throw invalid_argument("Source equals sink");
        queue<int> q;
        height = new int[G->getV()];
        excess = new double[G->getV()];
        done = new bool[G->getV()];
        for (int v = 0; v < G->getV(); v++) {
            height[v] = 0;
            excess[v] = 0.0;
            done[v] = false;
        }
        height[s] = G->getV();
        for (FlowEdge *e : G->adj(s)) {
            int v = e->other(s);
            if (v == e->to()) {
                e->addResidualFlowTo(v, e->getCapacity());
                excess[s] -= e->getCapacity();
                excess[v] += e->getCapacity();
            }
            if (v != t) {
                done[v] = true;
                q.push(v);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            int tempHeight = 2 * G->getV();
            for (FlowEdge *e : G->adj(v)) {
                if (abs(excess[v]) <= FLOATING_POINT_EPSILON) break;
                int w = e->other(v);
                if (e->residualCapacityTo(w) > FLOATING_POINT_EPSILON) {
                    if (height[v] > height[w]) {
                        // PUSH
                        double tempFlow = min(excess[v], e->residualCapacityTo(w));
                        e->addResidualFlowTo(w, tempFlow);
                        excess[v] -= tempFlow;
                        excess[w] += tempFlow;
                        // END PUSH
                        if (!done[w] && w != s && w != t) {
                            done[w] = true;
                            q.push(w);
                        }
                    } else {
                        tempHeight = min(height[w], tempHeight);
                    }
                }
            }
            if (excess[v] > FLOATING_POINT_EPSILON) height[v] = tempHeight + 1;
            else {
                done[v] = false;
                q.pop();
            }
        }
        value = excess[t];
    }

    /**
     * Returns the value of the maximum flow.
     *
     * @return the value of the maximum flow
     */
    double getValue()  {
        return value;
    }
};

inline int in(int i) {
    return (i - 1) * 2;
}

inline int out(int i) {
    return i * 2 - 1;
}

int N, M, E, v, w;
FlowNetwork *G;
PushRelabelMaxFlow *mf;

int main() {
    ri(N);
    G = new FlowNetwork(out(N));
    for (int i = 1; i <= N - 1; i++) {
        ri(E);
        G->addEdge(new FlowEdge(in(i), out(i), E));
    }
    ri(M);
    for (int i = 0; i < M; i++) {
        ri(v);
        ri(w);
        G->addEdge(new FlowEdge(out(v), in(w), INT_INF));
    }
    mf = new PushRelabelMaxFlow(G, in(1), in(N));
    printf("%d\n", (int) mf->getValue());
    return 0;
}
