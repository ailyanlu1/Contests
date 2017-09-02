#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define m(x, y) (x + (y - x) / 2)
#define MIN(a, b) (a = min(a, b))
#define MAX(a, b) (a = max(a, b))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

const double PI = 3.141592653589793;

struct Point2D {
public:
    double x;
    double y;

    Point2D() {};

    /**
     * Initializes a new point (x, y).
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    Point2D(double x, double y) {
        if (x == 0.0) this->x = 0.0;  // convert -0.0 to +0.0
        else          this->x = x;

        if (y == 0.0) this->y = 0.0;  // convert -0.0 to +0.0
        else          this->y = y;
    }

    /**
     * Returns the x-coordinate.
     * @return the x-coordinate
     */
    double getX() {
        return x;
    }

    /**
     * Returns the y-coordinate.
     * @return the y-coordinate
     */
    double getY() {
        return y;
    }

    /**
     * Returns the polar radius of this point.
     * @return the polar radius of this point in polar coordiantes: sqrt(x*x + y*y)
     */
    double polarRadius() {
        return sqrt(x*x + y*y);
    }

    /**
     * Returns the angle of this point in polar coordinates.
     * @return the angle (in radians) of this point in polar coordiantes (between –&pi;/2 and &pi;/2)
     */
    double theta() {
        return atan2(y, x);
    }

    /**
     * Returns the angle between this point and that point.
     * @return the angle in radians (between –&pi; and &pi;) between this point and that point (0 if equal)
     */
    double angleTo(Point2D &that) {
        double dx = that.x - x;
        double dy = that.y - y;
        return atan2(dy, dx);
    }

    /**
     * Returns true if a→b→c is a counterclockwise turn.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return { -1, 0, +1 } if a→b→c is a { clockwise, collinear; counterclocwise } turn.
     */
    static int ccw(Point2D &a, Point2D &b, Point2D &c) {
        double area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
        if      (area2 < 0) return -1;
        else if (area2 > 0) return +1;
        else                return  0;
    }

    /**
     * Returns twice the signed area of the triangle a-b-c.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return twice the signed area of the triangle a-b-c
     */
    static double area2(Point2D &a, Point2D &b, Point2D &c) {
        return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
    }

    /**
     * Returns a point that is this point rotated theta radians around that point.
     *
     * @param that the pivot point
     * @param theta the angle in radians
     * @return
     */
    Point2D &rotate(Point2D that, double theta) {
        double x = that.x + (this->x - that.x) * cos(theta) - (this->y - that.y) * sin(theta);
        double y = that.y + (this->x - that.x) * sin(theta) + (this->y - that.y) * cos(theta);
        return *(new Point2D(x, y));
    }

    /**
     * Returns the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the Euclidean distance between this point and that point
     */
    double distanceTo(Point2D &that) {
        double dx = x - that.x;
        double dy = y - that.y;
        return sqrt(dx*dx + dy*dy);
    }

    /**
     * Returns the square of the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the square of the Euclidean distance between this point and that point
     */
    double distanceSquaredTo(Point2D &that) {
        double dx = x - that.x;
        double dy = y - that.y;
        return dx*dx + dy*dy;
    }

    /**
     * Compares two points by y-coordinate, breaking ties by x-coordinate.
     * Formally, the invoking point (x0, y0) is less than the argument point (x1, y1)
     * if and only if either {@code y0 < y1} or if {@code y0 == y1} and {@code x0 < x1}.
     *
     * @param  that the other point
     * @return the value {@code 0} if this string is equal to the argument
     *         string (precisely when {@code equals()} returns {@code true});
     *         a negative integer if this point is less than the argument
     *         point; and a positive integer if this point is greater than the
     *         argument point
     */
    int compareTo(Point2D &that) {
        if (y < that.y) return -1;
        if (y > that.y) return +1;
        if (x < that.x) return -1;
        if (x > that.x) return +1;
        return 0;
    }

    /**
     * Compares this point to the specified point.
     *
     * @param  other the other point
     * @return {@code true} if this point equals {@code other};
     *         {@code false} otherwise
     */
    bool operator == (const Point2D &other) const {
        return x == other.x && y == other.y;
    }

    /**
     * Compares this point to the specified point.
     *
     * @param  other the other point
     * @return {@code true} if this point does not equal {@code other};
     *         {@code false} otherwise
     */
    bool operator != (const Point2D &other) const {
        return x != other.x || y != other.y;
    }

    // X ORDER

    /**
     * Compares two points by x-coordinate. Less than comparator.
     */
    static bool xOrderLt(Point2D &p, Point2D &q) { return p.x < q.x; }

    /**
     * Compares two points by x-coordinate. Less than or equal to comparator.
     */
    static bool xOrderLe(Point2D &p, Point2D &q) { return p.x < q.x; }

    /**
     * Compares two points by x-coordinate. Greater than comparator.
     */
    static bool xOrderGt(Point2D &p, Point2D &q) { return p.x > q.x; }

    /**
     * Compares two points by x-coordinate. Greater than or equal to comparator.
     */
    static bool xOrderGe(Point2D &p, Point2D &q) { return p.x >= q.x; }

    // Y ORDER

    /**
     * Compares two points by y-coordinate. Less than comparator.
     */
    static bool yOrderLt(Point2D &p, Point2D &q) { return p.y < q.y; }

    /**
     * Compares two points by y-coordinate. Less than or equal to comparator.
     */
    static bool yOrderLe(Point2D &p, Point2D &q) { return p.y <= q.y; }

    /**
     * Compares two points by y-coordinate. Greater than comparator.
     */
    static bool yOrderGt(Point2D &p, Point2D &q) { return p.y > q.y; }

    /**
     * Compares two points by y-coordinate. Greater than or equal to comparator.
     */
    static bool yOrderGe(Point2D &p, Point2D &q) { return p.y >= q.y; }

    // R ORDER

    /**
     * Compares two points by polar radius. Less than comparator.
     */
    static bool rOrderLt(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) < (q.x*q.x + q.y*q.y); }

    /**
     * Compares two points by polar radius. Less than or equal to comparator.
     */
    static bool rOrderLe(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) <= (q.x*q.x + q.y*q.y); }

    /**
     * Compares two points by polar radius. Greater than comparator.
     */
    static bool rOrderGt(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) > (q.x*q.x + q.y*q.y); }

    /**
     * Compares two points by polar radius. Greater than or equal to comparator.
     */
    static bool rOrderGe(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) >= (q.x*q.x + q.y*q.y); }

    // Polar Order

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Less than comparator.
     */
    bool polarOrderLt(Point2D &q1, Point2D &q2) {
        double dx1 = q1.x - x;
        double dy1 = q1.y - y;
        double dx2 = q2.x - x;
        double dy2 = q2.y - y;

        if      (dy1 >= 0 && dy2 < 0) return true;    // q1 above; q2 below
        else if (dy2 >= 0 && dy1 < 0) return false;   // q1 below; q2 above
        else if (dy1 == 0 && dy2 == 0) {              // 3-collinear and horizontal
            if      (dx1 >= 0 && dx2 < 0) return true;
            else if (dx2 >= 0 && dx1 < 0) return false;
            else                          return false;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Less than or equal to comparator.
     */
    bool polarOrderLe(Point2D &q1, Point2D &q2) {
        double dx1 = q1.x - x;
        double dy1 = q1.y - y;
        double dx2 = q2.x - x;
        double dy2 = q2.y - y;

        if      (dy1 >= 0 && dy2 < 0) return true;    // q1 above; q2 below
        else if (dy2 >= 0 && dy1 < 0) return false;   // q1 below; q2 above
        else if (dy1 == 0 && dy2 == 0) {              // 3-collinear and horizontal
            if      (dx1 >= 0 && dx2 < 0) return true;
            else if (dx2 >= 0 && dx1 < 0) return false;
            else                          return true;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Greater than comparator.
     */
    bool polarOrderGt(Point2D &q1, Point2D &q2) {
        double dx1 = q1.x - x;
        double dy1 = q1.y - y;
        double dx2 = q2.x - x;
        double dy2 = q2.y - y;

        if      (dy1 >= 0 && dy2 < 0) return false;   // q1 above; q2 below
        else if (dy2 >= 0 && dy1 < 0) return true;    // q1 below; q2 above
        else if (dy1 == 0 && dy2 == 0) {              // 3-collinear and horizontal
            if      (dx1 >= 0 && dx2 < 0) return false;
            else if (dx2 >= 0 && dx1 < 0) return true;
            else                          return false;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Greater than or equal to comparator.
     */
    bool polarOrderGe(Point2D &q1, Point2D &q2) {
        double dx1 = q1.x - x;
        double dy1 = q1.y - y;
        double dx2 = q2.x - x;
        double dy2 = q2.y - y;

        if      (dy1 >= 0 && dy2 < 0) return false;   // q1 above; q2 below
        else if (dy2 >= 0 && dy1 < 0) return true;    // q1 below; q2 above
        else if (dy1 == 0 && dy2 == 0) {              // 3-collinear and horizontal
            if      (dx1 >= 0 && dx2 < 0) return false;
            else if (dx2 >= 0 && dx1 < 0) return true;
            else                          return true;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    // Atan2 Order

    /**
     * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
     * Less than comparator.
     */
    bool atan2OrderLt(Point2D &q1, Point2D &q2) { return angleTo(q1) < angleTo(q2); }

    /**
     * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
     * Less than or equal to comparator.
     */
    bool atan2OrderLe(Point2D &q1, Point2D &q2) { return angleTo(q1) <= angleTo(q2); }

    /**
     * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
     * Greater than comparator.
     */
    bool atan2OrderGt(Point2D &q1, Point2D &q2) { return angleTo(q1) > angleTo(q2); }

    /**
     * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
     * Greater than or equal to comparator.
     */
    bool atan2OrderGe(Point2D &q1, Point2D &q2) { return angleTo(q1) >= angleTo(q2); }

    // DistanceTo Order

    /**
     * Compares two points by distance to this point. Less than comparator.
     */
    bool distanceToOrderLt(Point2D &p, Point2D &q) { return distanceSquaredTo(p) < distanceSquaredTo(q); }

    /**
     * Compares two points by distance to this point. Less than or equal to comparator.
     */
    bool distanceToOrderLe(Point2D &p, Point2D &q) { return distanceSquaredTo(p) <= distanceSquaredTo(q); }

    /**
     * Compares two points by distance to this point. Greater than comparator.
     */
    bool distanceToOrderGt(Point2D &p, Point2D &q) { return distanceSquaredTo(p) > distanceSquaredTo(q); }

    /**
     * Compares two points by distance to this point. Greater than or equal to comparator.
     */
    bool distanceToOrderGe(Point2D &p, Point2D &q) { return distanceSquaredTo(p) >= distanceSquaredTo(q); }
};

struct Point2D_hash {
    size_t operator ()(const Point2D &p) const {
        return 31 * hash<double> {}(p.x) + hash<double> {}(p.y);
    }
};

#define MAXN 100005

int vertex[MAXN];

struct Node {
    Point2D p;
    double theta, percent;
    Node(double x, double y, double theta, double percent) {
        this->p = Point2D(x, y);
        this->theta = theta;
        this->percent = percent;
    }
    Node() : Node(0.0, 0.0, 0.0, 1.0) {}
} *op[MAXN];

Node *merge(Node *a, Node *b) {
    Node *n = new Node();
    n->p.x = a->p.x * b->percent;
    n->p.y = a->p.y * b->percent;
    Point2D rot = b->p.rotate(Point2D(0.0, 0.0), -a->theta);
    n->p.x += rot.x;
    n->p.y += rot.y;
    n->theta = a->theta + b->theta;
    n->percent = a->percent * b->percent;
    return n;
}

struct SegmentTree {
private:
    vector<Node*> tree1, tree2;
    int N;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree1[cur] = tree2[cur] = op[vertex[cL]];
            return;
        }
        int m = m(cL, cR);
        build(l(cur), cL , m);
        build(r(cur), m + 1, cR);
        tree1[cur] = merge(tree1[l(cur)], tree1[r(cur)]);
        tree2[cur] = merge(tree2[r(cur)], tree2[l(cur)]);
        fflush(stdout);
    }

    void update(int cur, int cL, int cR, int ind) {
        if (cL >= ind && cR <= ind) {
            tree1[cur] = tree2[cur] = op[vertex[ind]];
            return;
        }
        int m = m(cL, cR);
        if (ind <= m) update(l(cur), cL, m, ind);
        else update(r(cur), m + 1, cR, ind);
        tree1[cur] = merge(tree1[l(cur)], tree1[r(cur)]);
        tree2[cur] = merge(tree2[r(cur)], tree2[l(cur)]);
    }

    Node *query(int cur, int cL, int cR, int l, int r, bool reverse) {
        if (cL >= l && cR <= r) return reverse ? tree2[cur] : tree1[cur];
        int m = m(cL, cR);
        if (r <= m) return query(l(cur), cL, m, l, r, reverse);
        else if (l > m) return query(r(cur), m + 1, cR, l, r, reverse);
        Node *a = query(l(cur), cL, m, l, m, reverse);
        Node *b = query(r(cur), m + 1, cR, m + 1, r, reverse);
        return reverse ? merge(b, a) : merge(a, b);
    }

public:
    SegmentTree(int size): tree1((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))), tree2((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        build(1, 1, size);
        N = size;
    }

    void update(int ind) {
        update(1, 1, N, ind);
    }

    Node *query(int l, int r, bool reverse) {
        return query(1, 1, N, l, r, reverse);
    }

    int size() {
        return N;
    }
};

struct Graph {
private:
    int V;
    int E;
    vector<int> *adjList;

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

    vector<int> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<pair<int, int>> &edges() {
        vector<pair<int, int>> *list = new vector<pair<int, int>>;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (int w : adj(v)) {
                if (w > v) {
                    list->push_back(make_pair(v, w));
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (w == v) {
                    if (selfLoops % 2 == 0) list->push_back(make_pair(v, w));
                    selfLoops++;
                }
            }
        }
        return *list;
    }
};

class LCA {
private:
    int *depth, *parent, *chain, *size, *head, *base;
    int chainNum, baseNum;
    SegmentTree *st;

    void dfs(Graph *G, int v, int d, int prev) {
        depth[v] = d;
        parent[v] = prev;
        size[v] = 1;
        for (int w: G->adj(v)) {
            if (w != prev) {
                dfs(G, w, d + 1, v);
                size[v] += size[w];
            }
        }
    }

    void hld(Graph *G, int v, int prev) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        base[v] = baseNum;
        vertex[baseNum++] = v;
        int maxIndex = -1;
        for (int w: G->adj(v)) {
            if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
        }
        if (maxIndex != -1) hld(G, maxIndex, v);
        for (int w: G->adj(v)) {
            if (w != prev && w != maxIndex) {
                chainNum++;
                hld(G, w, v);
            }
        }
    }

    Node *queryUp(int v, int w, bool reverse, bool includeW) {
        Node *ans = new Node();
        while (chain[v] != chain[w]) {
            ans = reverse ? merge(ans, st->query(base[head[chain[v]]], base[v], reverse)) : merge(st->query(base[head[chain[v]]], base[v], reverse), ans);
            v = parent[head[chain[v]]];
        }
        if (!includeW && v == w) return ans;
        return reverse ? merge(ans, st->query(base[w] + !includeW, base[v], reverse)) : merge(st->query(base[w] + !includeW, base[v], reverse), ans);
    }

    Node *queryPath(int v, int w) {
        int lcaVertex = lca(v, w);
        return merge(queryUp(v, lcaVertex, true, false), queryUp(w, lcaVertex, false, true));
    }

public:
    LCA(Graph *G) {
        depth = new int[G->getV()];
        parent = new int[G->getV()];
        chain = new int[G->getV()];
        size = new int[G->getV()];
        head = new int[G->getV()];
        base = new int[G->getV()];
        chainNum = 0;
        baseNum = 1;
        for (int i = 0; i < G->getV(); i++) {
            head[i] = -1;
        }
        dfs(G, 0, 0, -1);
        hld(G, 0, -1);
        st = new SegmentTree(G->getV());
    }

    /**
     * Returns the lowest common ancestor of vertex {@code v} and {@code w}.
     *
     * @param v the first vertex
     * @param w the first vertex
     * @return the lowest common ancestor of vertex {@code v} and {@code w}
     */
    int lca(int v, int w) {
        while (chain[v] != chain[w]) {
            if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
            else v = parent[head[chain[v]]];
        }
        if (depth[v] < depth[w]) return v;
        return w;
    }

    void update(int v) {
        st->update(base[v]);
    }

    Point2D &query(int v, int w, double x, double y) {
        Node *ans = merge(new Node(x, y, 0.0, 1.0), queryPath(v, w));
        return ans->p.rotate(Point2D(0, 0), ans->theta);
    }
};

int N, M;
Graph *G;
LCA *lca;

int main() {
    ri(N);
    ri(M);
    G = new Graph(N);
    char c;
    double t, x, y, p;
    FOR(v, N) {
        rc(c);
        if (c == 'R') {
            rd(t);
            op[v] = new Node(0.0, 0.0, t / 180.0 * PI, 1.0);
        } else if (c == 'T') {
            rd(x);
            rd(y);
            op[v] = new Node(x, y, 0.0, 1.0);
        } else if (c == 'M') {
            rd(x);
            rd(y);
            rd(p);
            p /= 100.0;
            op[v] = new Node(x * (1.0 - p), y * (1.0 - p), 0.0, p);
        } else {
            v--;
        }
    }
    int v, w;
    FOR(i, N - 1) {
        ri(v);
        ri(w);
        G->addEdge(v - 1, w - 1);
    }
    lca = new LCA(G);
    Point2D ans;
    FOR(i, M) {
        rc(c);
        if (c == 'Q') {
            ri(v); v--;
            ri(w); w--;
            rd(x);
            rd(y);
            ans = lca->query(v, w, x, y);
            printf("%.6f %.6f\n", ans.x, ans.y);
        } else if (c == 'U') {
            ri(v); v--;
            rc(c);
            if (c == 'R') {
                rd(t);
                op[v] = new Node(0.0, 0.0, t / 180.0 * PI, 1);
            } else if (c == 'T') {
                rd(x);
                rd(y);
                op[v] = new Node(x, y, 0.0, 1.0);
            } else if (c == 'M') {
                rd(x);
                rd(y);
                rd(p);
                p /= 100.0;
                op[v] = new Node(x * (1.0 - p), y * (1.0 - p), 0.0, p);
            }
            lca->update(v);
        } else {
            i--;
        }
    }
    return 0;
}
