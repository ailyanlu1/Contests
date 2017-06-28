/*
 * FHC15C3P3_Max_Match.cpp
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

struct Graph {
private:
    int V;
    int E;
    vector<int>* adjList;

public:
    Graph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<int>[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjList[w].push_back(v);
        E++;
    }

    vector<int> adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }
};

class Cycle {
private:
    bool *marked;
    int *edgeTo;
    vector<int> cycle;

    // does this graph have a self loop?
    // side effect: initialize cycle to be self loop
    bool hasSelfLoop(Graph *G) {
        for (int v = 0; v < G->getV(); v++) {
            for (int w : G->adj(v)) {
                if (v == w) {
                    cycle.clear();
                    cycle.push_back(v);
                    cycle.push_back(v);
                    return true;
                }
            }
        }
        return false;
    }

    // does this graph have two parallel edges?
    // side effect: initialize cycle to be two parallel edges
    bool hasParallelEdges(Graph *G) {
        marked = new bool[G->getV()];
        for (int i = 0; i < G->getV(); i++) {
            marked[i] = false;
        }

        for (int v = 0; v < G->getV(); v++) {

            // check for parallel edges incident to v
            for (int w : G->adj(v)) {
                if (marked[w]) {
                    cycle.clear();
                    cycle.push_back(v);
                    cycle.push_back(w);
                    cycle.push_back(v);
                    return true;
                }
                marked[w] = true;
            }

            // reset so marked[v] = false for all v
            for (int w : G->adj(v)) {
                marked[w] = false;
            }
        }
        return false;
    }

    void dfs(Graph *G, int u, int v) {
        marked[v] = true;
        for (int w : G->adj(v)) {

            // short circuit if cycle already found
            if (cycle.size() != 0) return;

            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, v, w);
            }

            // check for cycle (but disregard reverse of edge leading to v)
            else if (w != u) {
                cycle.clear();
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push_back(x);
                }
                cycle.push_back(w);
                cycle.push_back(v);
            }
        }
    }

public:
    /**
     * Determines whether the undirected graph {@code G} has a cycle and,
     * if so, finds such a cycle.
     *
     * @param G the undirected graph
     */
    Cycle(Graph *G) {
        if (hasSelfLoop(G)) return;
        if (hasParallelEdges(G)) return;
        marked = new bool[G->getV()];
        for (int i = 0; i < G->getV(); i++) {
            marked[i] = false;
        }
        edgeTo = new int[G->getV()];
        for (int v = 0; v < G->getV(); v++)
            if (!marked[v])
                dfs(G, -1, v);
    }

    /**
     * Returns true if the graph {@code G} has a cycle.
     *
     * @return {@code true} if the graph has a cycle; {@code false} otherwise
     */
    bool hasCycle() {
        return cycle.size() != 0;
    }

     /**
     * Returns a cycle in the graph {@code G}.
     * @return a cycle if the graph {@code G} has a cycle,
     *         and {@code null} otherwise
     */
    vector<int> getCycle() {
        return cycle;
    }
};

class BipartiteX {
private:
    bool WHITE = false;
    bool BLACK = true;

    bool bipartite;   // is the graph bipartite?
    bool *color;       // color[v] gives vertices on one side of bipartition
    bool *marked;      // marked[v] = true if v has been visited in DFS
    int *edgeTo;          // edgeTo[v] = last edge on path to v
    queue<int> cycle;  // odd-length cycle
    vector<int> vectorCycle;

    void bfs(Graph *G, int s) {
        queue<int> q;
        color[s] = WHITE;
        marked[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G->adj(v)) {
                if (!marked[w]) {
                    marked[w] = true;
                    edgeTo[w] = v;
                    color[w] = !color[v];
                    q.push(w);
                }
                else if (color[w] == color[v]) {
                    bipartite = false;

                    // to form odd cycle, consider s-v path and s-w path
                    // and let x be closest node to v and w common to two paths
                    // then (w-x path) + (x-v path) + (edge v-w) is an odd-length cycle
                    // Note: distTo[v] == distTo[w];
                    queue<int> temp;
                    swap(temp, cycle);
                    stack<int> stk;
                    int x = v, y = w;
                    while (x != y) {
                        stk.push(x);
                        cycle.push(y);
                        x = edgeTo[x];
                        y = edgeTo[y];
                    }
                    stk.push(x);
                    while (!stk.empty()) {
                        cycle.push(stk.top());
                        stk.pop();
                    }
                    cycle.push(w);
                    return;
                }
            }
        }
    }

public:
    /**
     * Determines whether an undirected graph is bipartite and finds either a
     * bipartition or an odd-length cycle.
     *
     * @param  G the graph
     */
    BipartiteX(Graph *G) {
        bipartite = true;
        color  = new bool[G->getV()];
        marked = new bool[G->getV()];
        edgeTo = new int[G->getV()];
        for (int i = 0; i < G->getV(); i++) {
            color[i] = false;
            marked[i] = false;
        }
        for (int v = 0; v < G->getV() && bipartite; v++) {
            if (!marked[v]) {
                bfs(G, v);
            }
        }
        while (!cycle.empty()) {
            vectorCycle.push_back(cycle.front());
            cycle.pop();
        }
    }

    /**
     * Returns true if the graph is bipartite.
     *
     * @return {@code true} if the graph is bipartite; {@code false} otherwise
     */
    bool isBipartite() {
        return bipartite;
    }

    /**
     * Returns the side of the bipartite that vertex {@code v} is on.
     *
     * @param  v the vertex
     * @return the side of the bipartition that vertex {@code v} is on; two vertices
     *         are in the same side of the bipartition if and only if they have the
     *         same color
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @throws UnsupportedOperationException if this method is called when the graph
     *         is not bipartite
     */
    bool getColor(int v) {
        if (!bipartite)
            throw runtime_error("Graph is not bipartite");
        return color[v];
    }


    /**
     * Returns an odd-length cycle if the graph is not bipartite, and
     * {@code null} otherwise.
     *
     * @return an odd-length cycle if the graph is not bipartite
     *         (and hence has an odd-length cycle), and {@code null}
     *         otherwise
     */
    vector<int> oddCycle() {
        return vectorCycle;
    }
};

class HopcroftKarpMaxMatch {
private:
    int UNMATCHED = -1;

    int V;                 // number of vertices in the graph
    BipartiteX *bipartition;      // the bipartition
    int cardinality;             // cardinality of current matching
    int *mate;                  // mate[v] =  w if v-w is an edge in current matching
                                         //         = -1 if v is not in current matching
    bool *inMinVertexCover;  // inMinVertexCover[v] = true iff v is in min vertex cover
    bool *marked;            // marked[v] = true iff v is reachable via alternating path
    int *distTo;                // distTo[v] = number of edges on shortest path to v

    // is the edge v-w a forward edge not in the matching or a reverse edge in the matching?
    bool isResidualGraphEdge(int v, int w) {
        if ((mate[v] != w) &&  bipartition->getColor(v)) return true;
        if ((mate[v] == w) && !bipartition->getColor(v)) return true;
        return false;
    }

    // is the edge v-w in the level graph?
    bool isLevelGraphEdge(int v, int w) {
        return (distTo[w] == distTo[v] + 1) && isResidualGraphEdge(v, w);
    }

    /*
     * is there an augmenting path?
     *   - if so, upon termination adj[] contains the level graph;
     *   - if not, upon termination marked[] specifies those vertices reachable via an alternating
     *     path from one side of the bipartition
     *
     * an alternating path is a path whose edges belong alternately to the matching and not
     * to the matching
     *
     * an augmenting path is an alternating path that starts and ends at unmatched vertices
     */
    bool hasAugmentingPath(Graph *G) {
        // shortest path distances
        marked = new bool[V];
        distTo = new int[V];
        for (int v = 0; v < V; v++) {
            marked[v] = false;
            distTo[v] = INT_MAX;
        }

        // breadth-first search (starting from all unmatched vertices on one side of bipartition)
        queue<int> q;
        for (int v = 0; v < V; v++) {
            if (bipartition->getColor(v) && !isMatched(v)) {
                q.push(v);
                marked[v] = true;
                distTo[v] = 0;
            }
        }

        // run BFS until an augmenting path is found
        // (and keep going until all vertices at that distance are explored)
        bool hasAugmentingPath = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G->adj(v)) {

                // forward edge not in matching or backwards edge in matching
                if (isResidualGraphEdge(v, w)) {
                    if (!marked[w]) {
                        distTo[w] = distTo[v] + 1;
                        marked[w] = true;
                        if (!isMatched(w))
                            hasAugmentingPath = true;

                        // stop enqueuing vertices once an alternating path has been discovered
                        // (no vertex on same side will be marked if its shortest path distance longer)
                        if (!hasAugmentingPath) q.push(w);
                    }
                }
            }
        }

        return hasAugmentingPath;
    }

public:
    /**
     * Determines a maximum matching (and a minimum vertex cover)
     * in a bipartite graph.
     *
     * @param  G the bipartite graph
     * @throws invalid_argument if {@code G} is not bipartite
     */
    HopcroftKarpMaxMatch(Graph *G) {
        bipartition = new BipartiteX(G);
        if (!bipartition->isBipartite()) {
            throw invalid_argument("graph is not bipartite");
        }

        // initialize empty matching
        V = G->getV();
        cardinality = 0;
        mate = new int[V];
        for (int v = 0; v < V; v++)
            mate[v] = UNMATCHED;

        // the call to hasAugmentingPath() provides enough info to reconstruct level graph
        while (hasAugmentingPath(G)) {

            // to be able to iterate over each adjacency list, keeping track of which
            // vertex in each adjacency list needs to be explored next
            int iter[V];
            vector<int> adj[V];
            for (int i = 0; i < V; i++) {
                adj[i] = G->adj(i);
                iter[i] = 0;
            }

            // for each unmatched vertex s on one side of bipartition
            for (int s = 0; s < V; s++) {
                if (isMatched(s) || !bipartition->getColor(s)) continue;   // or use distTo[s] == 0

                // find augmenting path from s using nonrecursive DFS
                stack<int> path;
                path.push(s);
                while (!path.empty()) {
                    int v = path.top();

                    // retreat, no more edges in level graph leaving v
                    if (iter[v] >= adj[v].size())
                        path.pop();

                    // advance
                    else {
                        // process edge v-w only if it is an edge in level graph
                        int w = adj[v][iter[v]++];
                        if (!isLevelGraphEdge(v, w)) continue;

                        // add w to augmenting path
                        path.push(w);

                        // augmenting path found: update the matching
                        if (!isMatched(w)) {
                            // StdOut.println("augmenting path: " + toString(path));

                            while (!path.empty()) {
                                int x = path.top();
                                path.pop();
                                int y = path.top();
                                path.pop();
                                mate[x] = y;
                                mate[y] = x;
                            }
                            cardinality++;
                        }
                    }
                }
            }
        }

        // also find a min vertex cover
        inMinVertexCover = new bool[V];
        for (int v = 0; v < V; v++) {
            inMinVertexCover[v] = false;
            if (bipartition->getColor(v) && !marked[v]) inMinVertexCover[v] = true;
            if (!bipartition->getColor(v) && marked[v]) inMinVertexCover[v] = true;
        }
    }

    /**
     * Returns the vertex to which the specified vertex is matched in
     * the maximum matching computed by the algorithm.
     *
     * @param  v the vertex
     * @return the vertex to which vertex {@code v} is matched in the
     *         maximum matching; {@code -1} if the vertex is not matched
     * @throws invalid_argument unless {@code 0 <= v < V}
     *
     */
    int getMate(int v) {
        return mate[v];
    }

    /**
     * Returns true if the specified vertex is matched in the maximum matching
     * computed by the algorithm.
     *
     * @param  v the vertex
     * @return {@code true} if vertex {@code v} is matched in maximum matching;
     *         {@code false} otherwise
     * @throws invalid_argument unless {@code 0 <= v < V}
     *
     */
    bool isMatched(int v) {
        return mate[v] != UNMATCHED;
    }

    /**
     * Returns the number of edges in any maximum matching.
     *
     * @return the number of edges in any maximum matching
     */
    int getCardinality() {
        return cardinality;
    }

    /**
     * Returns true if the graph contains a perfect matching.
     * That is, the number of edges in a maximum matching is equal to one half
     * of the number of vertices in the graph (so that every vertex is matched).
     *
     * @return {@code true} if the graph contains a perfect matching;
     *         {@code false} otherwise
     */
    bool isPerfect() {
        return cardinality * 2 == V;
    }

    /**
     * Returns true if the specified vertex is in the minimum vertex cover
     * computed by the algorithm.
     *
     * @param  v the vertex
     * @return {@code true} if vertex {@code v} is in the minimum vertex cover;
     *         {@code false} otherwise
     * @throws invalid_argument unless {@code 0 <= v < V}
     */
    bool getInMinVertexCover(int v) {
        return inMinVertexCover[v];
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
    Graph G(N * 2);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (connected[i][j] && !connected[j][i]) G.addEdge(i, N + j);
        }
    }
    HopcroftKarpMaxMatch maxMatch(&G);
    printf("Case #%d: %d\n", testCaseNum, (int) (N - maxMatch.getCardinality()));
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
