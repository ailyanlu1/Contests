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

using namespace std;
using namespace std::placeholders;

struct Vector {
private:
    int d;                          // dimension of the vector
    double *data = nullptr;         // array of vector's components

public:
    Vector() {}

    /**
     * Initializes a d-dimensional zero vector.
     *
     * @param d the dimension of the vector
     */
    Vector(int d) {
        this->d = d;
        this->data = new double[d];
        for (int i = 0; i < d; i++) data[i] = 0.0;
    }

    /**
     * Initializes a vector from an array.
     *
     * @param d the dimension of the vector
     * @param a the array
     */
    Vector(int d, double *a) {
        this->d = d;
        // defensive copy so that client can't alter our copy of data[]
        this->data = new double[d];
        for (int i = 0; i < d; i++) this->data[i] = a[i];
    }

    Vector(const Vector &v) {
        this->d = v.d;
        this->data = new double[this->d];
        for (int i = 0; i < d; i++) {
            this->data[i] = v.data[i];
        }
    }

    Vector &operator = (const Vector &v) {
        if (this != &v) {
            delete this->data;
            this->d = v.d;
            this->data = new double[this->d];
            for (int i = 0; i < d; i++) {
                this->data[i] = v.data[i];
            }
        }
        return *this;
    }

    Vector(Vector &&v) {
        this->d = v.d;
        this->data = v.data;
        v.data = nullptr;
    }

    Vector &operator = (Vector &&v) {
        if (this != &v) {
            delete this->data;
            this->d = v.d;
            this->data = v.data;
            v.data = nullptr;
        }
        return *this;
    }

    ~Vector() {
        delete data;
    }

    /**
     * Returns the dimension of this vector.
     *
     * @return the dimension of this vector
     */
    int dimension() {
        return d;
    }

    /**
     * Returns the dot product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the dot product of this vector and that vector
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    double dot(Vector &that) {
        if (d != that.d) throw invalid_argument("Dimensions don't agree");
        double sum = 0.0;
        for (int i = 0; i < d; i++)
            sum = sum + (data[i] * that.data[i]);
        return sum;
    }

    /**
     *
     * Returns the dot product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the dot product of this vector and that vector
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    double operator * (Vector &that) {
        return dot(that);
    }

    /**
     * Returns the 2-D cross product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the 2-D cross product of this vector and that vector
     * @throws invalid_argument if the two vectors are not 2-dimensional
     */
    double cross2D(Vector &that) {
        if (d != 2 || that.d != 2) throw invalid_argument("Vectors must be 2-dimensional");
        return data[0] * that.data[1] - data[1] * that.data[0];
    }

    /**
     * Returns the 2-D cross product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the 2-D cross product of this vector and that vector
     * @throws invalid_argument if the two vectors are not 2-dimensional
     */
    double operator | (Vector &that) {
        return cross2D(that);
    }

    /**
     * Returns the 3-D cross product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the 3-D cross product of this vector and that vector
     * @throws invalid_argument if the two vectors are not 3-dimensional
     */
    Vector &cross3D(Vector &that) {
        if (d != 3 || that.d != 3) throw invalid_argument("Vectors must be 3-dimensional");
        Vector *c = new Vector(d);
        c->data[0] = data[1] * that.data[2] - data[2] * that.data[1];
        c->data[1] = data[2] * that.data[0] - data[0] * that.data[2];
        c->data[2] = data[0] * that.data[1] - data[1] * that.data[0];
        return *c;
    }

    /**
     * Returns the 3-D cross product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the 3-D cross product of this vector and that vector
     * @throws invalid_argument if the two vectors are not 3-dimensional
     */
    Vector &operator ^ (Vector &that) {
        return cross3D(that);
    }

    /**
     * Returns the magnitude of this vector.
     * This is also known as the L2 norm or the Euclidean norm.
     *
     * @return the magnitude of this vector
     */
    double magnitude() {
        return sqrt(this->dot(*this));
    }

    /**
     * Returns the Euclidean distance between this vector and the specified vector.
     *
     * @param  that the other vector
     * @return the Euclidean distance between this vector and that vector
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    double distanceTo(Vector &that) {
        if (d != that.d) throw invalid_argument("Dimensions don't agree");
        return minus(that).magnitude();
    }

    /**
     * Returns the sum of this vector and the specified vector.
     *
     * @param  that the vector to add to this vector
     * @return the vector whose value is {@code (this + that)}
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    Vector &plus(Vector &that) {
        if (d != that.d) throw invalid_argument("Dimensions don't agree");
        Vector *c = new Vector(d);
        for (int i = 0; i < d; i++)
            c->data[i] = data[i] + that.data[i];
        return *c;
    }

    /**
     * Returns the sum of this vector and the specified vector.
     *
     * @param  that the vector to add to this vector
     * @return the vector whose value is {@code (this + that)}
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    Vector &operator + (Vector &that) {
        return plus(that);
    }

    /**
     * Returns the difference between this vector and the specified vector.
     *
     * @param  that the vector to subtract from this vector
     * @return the vector whose value is {@code (this - that)}
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    Vector &minus(Vector &that) {
        if (d != that.d) throw invalid_argument("Dimensions don't agree");
        Vector *c = new Vector(d);
        for (int i = 0; i < d; i++)
            c->data[i] = data[i] - that.data[i];
        return *c;
    }

    /**
     * Returns the difference between this vector and the specified vector.
     *
     * @param  that the vector to subtract from this vector
     * @return the vector whose value is {@code (this - that)}
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    Vector &operator - (Vector &that) {
        return minus(that);
    }

    /**
     * Returns the ith cartesian coordinate.
     *
     * @param  i the coordinate index
     * @return the ith cartesian coordinate
     */
    double cartesian(int i) {
        return data[i];
    }

    // mutator operator
    double &operator [](int i) {
        return data[i];
    }

    // accessor operator
    double operator [](int i) const {
        return data[i];
    }

    /**
     * Returns the scalar-vector product of this vector and the specified scalar
     *
     * @param  alpha the scalar
     * @return the vector whose value is {@code (alpha * this)}
     */
    Vector &scale(double alpha) {
        Vector *c = new Vector(d);
        for (int i = 0; i < d; i++)
            c->data[i] = alpha * data[i];
        return *c;
    }

    /**
     * Returns the scalar-vector product of this vector and the specified scalar
     *
     * @param  alpha the scalar
     * @return the vector whose value is {@code (alpha * this)}
     */
    Vector &operator * (double alpha) {
        return scale(alpha);
    }

    /**
     * Returns the scalar-vector product of this vector and the specified the reciprocal of the scalar
     *
     * @param  alpha the scalar
     * @return the vector whose value is {@code (alpha * this)}
     */
    Vector &operator / (double alpha) {
        return scale(1.0 / alpha);
    }

    /**
     * Returns a unit vector in the direction of this vector.
     *
     * @return a unit vector in the direction of this vector
     * @throws runtime_error if this vector is the zero vector
     */
    Vector &direction() {
        if (magnitude() == 0.0) throw runtime_error("Zero-vector has no direction");
        return scale(1.0 / magnitude());
    }

    /**
     * Returns the direction cosine of this angle in the ith dimension.
     *
     * @param i the direction number (0-indexed)
     * @return the direction cosine of this angle in the ith dimension
     */
    double directionCosine(int i) {
        return data[i] / magnitude();
    }

    /**
     * Returns a projection of this vector on that vector.
     *
     * @param that the vector that this vector is to be projected on
     * @return a projection of this vector on that vector
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     */
    Vector &projectionOn(Vector &that) {
        if (d != that.d) throw invalid_argument("Dimensions don't agree");
        return that.scale(dot(that) / that.dot(that));
    }

    /**
     * Returns a vector that is this vector rotated theta radians around that vector.
     *
     * @param that vector representing the axis of rotation
     * @param theta the angle in radians
     * @return a vector that is this vector rotated theta radians around that vector
     * @throws invalid_argument if the dimensions of the two vectors are not equal
     * @throws invalid_argument if the two vectors are not 2-dimensional or 3-dimensional
     */
    Vector &rotate(Vector &that, double theta) {
        if (d == 2 && that.d == 2) {
            Vector *r = new Vector(2);
            r->data[0] = that.data[0] + (data[0] - that.data[0]) * cos(theta) - (data[1] - that.data[1]) * sin(theta);
            r->data[1] = that.data[1] + (data[0] - that.data[0]) * sin(theta) + (data[1] - that.data[1]) * cos(theta);
            return *r;
        } else if (d == 3 && that.d == 3) {
            Vector *r = new Vector(3);
            r = &this->scale(cos(theta)).plus(that.direction().cross3D(*this).scale(sin(theta))).plus(that.direction().scale(that.direction().dot(*this)).scale(1.0 - cos(theta)));
            return *r;
        } else if (d == that.d) {
            throw invalid_argument("Vectors must be 2-dimensional or 3-dimensional");
        } else {
            throw invalid_argument("Dimensions don't agree");
        }
    }
};

typedef double T;
constexpr static T EPS = 1e-9;

struct Point2D {
public:
    T x;
    T y;

    Point2D() {}

    /**
     * Initializes a new point (x, y).
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    Point2D(T x, T y) {
        this->x = x;
        this->y = y;
    }

    /**
     * Returns the x-coordinate.
     * @return the x-coordinate
     */
    T getX() {
        return x;
    }

    /**
     * Returns the y-coordinate.
     * @return the y-coordinate
     */
    T getY() {
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
     * @return the angle (in radians) of this point in polar coordiantes (between -&pi;/2 and &pi;/2)
     */
    double theta() {
        return atan2(y, x);
    }

    /**
     * Returns the angle between this point and that point.
     * @return the angle in radians (between -&pi; and &pi;) between this point and that point (0 if equal)
     */
    double angleTo(Point2D &that) {
        T dx = that.x - x;
        T dy = that.y - y;
        return atan2(dy, dx);
    }

    /**
     * Returns true if a->b->c is a counterclockwise turn.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return { -1, 0, +1 } if a->b->c is a { clockwise, collinear; counterclockwise } turn.
     */
    static int ccw(Point2D &a, Point2D &b, Point2D &c) {
        T area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
        if      (area2 < -EPS) return -1;
        else if (area2 > EPS) return +1;
        else                  return  0;
    }

    /**
     * Returns twice the signed area of the triangle a-b-c.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return twice the signed area of the triangle a-b-c
     */
    static T area2(Point2D &a, Point2D &b, Point2D &c) {
        return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
    }

    /**
     * Returns a point that is this point rotated theta radians around that point.
     *
     * @param that the pivot point
     * @param theta the angle in radians
     * @return a point that is this point rotated theta radians around that point
     */
    Point2D &rotate(Point2D &that, double theta) {
        T x = that.x + (this->x - that.x) * cos(theta) - (this->y - that.y) * sin(theta);
        T y = that.y + (this->x - that.x) * sin(theta) + (this->y - that.y) * cos(theta);
        return *(new Point2D(x, y));
    }

    /**
     * Returns the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the Euclidean distance between this point and that point
     */
    double distanceTo(Point2D &that) {
        T dx = x - that.x;
        T dy = y - that.y;
        return sqrt(dx*dx + dy*dy);
    }

    /**
     * Returns the square of the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the square of the Euclidean distance between this point and that point
     */
    T distanceSquaredTo(Point2D &that) {
        T dx = x - that.x;
        T dy = y - that.y;
        return dx*dx + dy*dy;
    }

    /**
     * Is this point on the line segment pq?
     * @param p one point of the line segment
     * @param q the other point of the line segment
     * @returns whether this point is on the line segment pq
     */
    bool onSegment(Point2D &p, Point2D &q) {
        return x <= max(p.x, q.x) + EPS && x >= min(p.x, q.x) - EPS && y <= max(p.y, q.y) + EPS && y >= min(p.y, q.y) - EPS;
    }

    /**
     * Does line segment p1q1 intersect line segment p2q2?
     *
     * @param p1 one point of the first line segment
     * @param q1 the other point of the first line segment
     * @param p2 one point of the second line segment
     * @param q2 the other point of the second line segment
     * @return whether line segment p1q1 intersects line segment p2q2
     */
    static bool intersects(Point2D &p1, Point2D &q1, Point2D &p2, Point2D &q2) {
        // Find the four orientations needed for general and special cases
        int o1 = Point2D::ccw(p1, q1, p2);
        int o2 = Point2D::ccw(p1, q1, q2);
        int o3 = Point2D::ccw(p2, q2, p1);
        int o4 = Point2D::ccw(p2, q2, q1);
        // General case
        if (o1 != o2 && o3 != o4) return true;
        // Special Cases
        // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == 0 && p2.onSegment(p1, q1)) return true;
        // p1, q1 and p2 are colinear and q2 lies on segment p1q1
        if (o2 == 0 && q2.onSegment(p1, q1)) return true;
        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == 0 && p1.onSegment(p2, q2)) return true;
         // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == 0 && q1.onSegment(p2, q2)) return true;
        return false; // Doesn't fall in any of the above cases
    }

    /**
     * Calculates the point of intersection of 2 lines.
     *
     * @param p1 one point on the first line
     * @param q1 the other point on the first line
     * @param p2 one point on the second line
     * @param q2 the other point on the second line
     * @return the point of intersection of the 2 lines
     * @throws RuntimeException if there is no point of intersection
     */
    static Point2D &intersection(Point2D &p1, Point2D &q1, Point2D &p2, Point2D &q2) {
        T A1 = q1.y - p1.y;
        T B1 = p1.x - q1.x;
        T C1 = A1 * p1.x + B1 * p1.y;
        T A2 = q2.y - p2.y;
        T B2 = p2.x - q2.x;
        T C2 = A2 * p2.x + B2 * p2.y;
        T det = A1 * B2 - A2 * B1;
        if (abs(det) <= EPS) throw runtime_error("The lines do not intersect");
        Point2D *r = new Point2D((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);
        return *r;
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
        if (y < that.y - EPS) return -1;
        if (y > that.y + EPS) return +1;
        if (x < that.x - EPS) return -1;
        if (x > that.x + EPS) return +1;
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
        return abs(x - other.x) <= EPS && abs(y - other.y) <= EPS;
    }

    /**
     * Compares this point to the specified point.
     *
     * @param  other the other point
     * @return {@code true} if this point does not equal {@code other};
     *         {@code false} otherwise
     */
    bool operator != (const Point2D &other) const {
        return abs(x - other.x) > EPS || abs(y - other.y) > EPS;
    }

    // X ORDER

    /**
     * Compares two points by x-coordinate. Less than comparator.
     */
    static bool xOrderLt(Point2D &p, Point2D &q) { return q.x - p.x < EPS; }

    /**
     * Compares two points by x-coordinate. Less than or equal to comparator.
     */
    static bool xOrderLe(Point2D &p, Point2D &q) { return q.x - p.x <= -EPS; }

    /**
     * Compares two points by x-coordinate. Greater than comparator.
     */
    static bool xOrderGt(Point2D &p, Point2D &q) { return p.x - q.x < EPS; }

    /**
     * Compares two points by x-coordinate. Greater than or equal to comparator.
     */
    static bool xOrderGe(Point2D &p, Point2D &q) { return p.x - q.x <= -EPS; }

    // Y ORDER

    /**
     * Compares two points by y-coordinate. Less than comparator.
     */
    static bool yOrderLt(Point2D &p, Point2D &q) { return q.y - p.y < EPS; }

    /**
     * Compares two points by y-coordinate. Less than or equal to comparator.
     */
    static bool yOrderLe(Point2D &p, Point2D &q) { return q.y - p.y <= -EPS; }

    /**
     * Compares two points by y-coordinate. Greater than comparator.
     */
    static bool yOrderGt(Point2D &p, Point2D &q) { return p.y - q.y < EPS; }

    /**
     * Compares two points by y-coordinate. Greater than or equal to comparator.
     */
    static bool yOrderGe(Point2D &p, Point2D &q) { return p.y - q.y <= -EPS; }

    // R ORDER

    /**
     * Compares two points by polar radius. Less than comparator.
     */
    static bool rOrderLt(Point2D &p, Point2D &q) { return (q.x*q.x + q.y*q.y) - (p.x*p.x + p.y*p.y) < EPS; }

    /**
     * Compares two points by polar radius. Less than or equal to comparator.
     */
    static bool rOrderLe(Point2D &p, Point2D &q) { return (q.x*q.x + q.y*q.y) - (p.x*p.x + p.y*p.y) <= -EPS; }

    /**
     * Compares two points by polar radius. Greater than comparator.
     */
    static bool rOrderGt(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) - (q.x*q.x + q.y*q.y) < EPS; }

    /**
     * Compares two points by polar radius. Greater than or equal to comparator.
     */
    static bool rOrderGe(Point2D &p, Point2D &q) { return (p.x*p.x + p.y*p.y) - (q.x*q.x + q.y*q.y) <= -EPS; }

    // POLAR ORDER

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Less than comparator.
     */
    bool polarOrderLt(Point2D &q1, Point2D &q2) {
        T dx1 = q1.x - x;
        T dy1 = q1.y - y;
        T dx2 = q2.x - x;
        T dy2 = q2.y - y;

        if      (dy1 >= -EPS && dy2 < -EPS) return true;    // q1 above; q2 below
        else if (dy2 >= -EPS && dy1 < -EPS) return false;   // q1 below; q2 above
        else if (abs(dy1) <= EPS && abs(dy2) <= EPS) {      // 3-collinear and horizontal
            if      (dx1 >= -EPS && dx2 < -EPS) return true;
            else if (dx2 >= -EPS && dx1 < EPS)  return false;
            else                                return false;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Less than or equal to comparator.
     */
    bool polarOrderLe(Point2D &q1, Point2D &q2) {
        T dx1 = q1.x - x;
        T dy1 = q1.y - y;
        T dx2 = q2.x - x;
        T dy2 = q2.y - y;

        if      (dy1 >= -EPS && dy2 < -EPS) return true;    // q1 above; q2 below
        else if (dy2 >= -EPS && dy1 < -EPS) return false;   // q1 below; q2 above
        else if (abs(dy1) <= EPS && abs(dy2) <= EPS) {      // 3-collinear and horizontal
            if      (dx1 >= -EPS && dx2 < -EPS) return true;
            else if (dx2 >= -EPS && dx1 < EPS)  return false;
            else                                return true;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Greater than comparator.
     */
    bool polarOrderGt(Point2D &q1, Point2D &q2) {
        T dx1 = q1.x - x;
        T dy1 = q1.y - y;
        T dx2 = q2.x - x;
        T dy2 = q2.y - y;

        if      (dy1 >= -EPS && dy2 < -EPS) return false;   // q1 above; q2 below
        else if (dy2 >= -EPS && dy1 < -EPS) return true;    // q1 below; q2 above
        else if (abs(dy1) <= EPS && abs(dy2) <= EPS) {      // 3-collinear and horizontal
            if      (dx1 >= -EPS && dx2 < -EPS) return false;
            else if (dx2 >= -EPS && dx1 < EPS)  return true;
            else                                return false;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     * Greater than or equal to comparator.
     */
    bool polarOrderGe(Point2D &q1, Point2D &q2) {
        T dx1 = q1.x - x;
        T dy1 = q1.y - y;
        T dx2 = q2.x - x;
        T dy2 = q2.y - y;

        if      (dy1 >= -EPS && dy2 < -EPS) return false;   // q1 above; q2 below
        else if (dy2 >= -EPS && dy1 < -EPS) return true;    // q1 below; q2 above
        else if (abs(dy1) <= EPS && abs(dy2) <= EPS) {      // 3-collinear and horizontal
            if      (dx1 >= -EPS && dx2 < -EPS) return false;
            else if (dx2 >= -EPS && dx1 < EPS)  return true;
            else                                return true;
        }
        else return ccw(*this, q1, q2) > 0;     // both above or below
        // Note: ccw() recomputes dx1, dy1, dx2, and dy2
    }

    // ATAN2 ORDER

    /**
     * Compares two points by atan2() angle (between -&pi; and &pi;) with respect to this point.
     * Less than comparator.
     */
    bool atan2OrderLt(Point2D &q1, Point2D &q2) { return angleTo(q1) - angleTo(q2) < EPS; }

    /**
     * Compares two points by atan2() angle (between -&pi; and &pi;) with respect to this point.
     * Less than or equal to comparator.
     */
    bool atan2OrderLe(Point2D &q1, Point2D &q2) { return angleTo(q1) - angleTo(q2) <= -EPS; }

    /**
     * Compares two points by atan2() angle (between -&pi; and &pi;) with respect to this point.
     * Greater than comparator.
     */
    bool atan2OrderGt(Point2D &q1, Point2D &q2) { return angleTo(q1) - angleTo(q2) < EPS; }

    /**
     * Compares two points by atan2() angle (between -&pi; and &pi;) with respect to this point.
     * Greater than or equal to comparator.
     */
    bool atan2OrderGe(Point2D &q1, Point2D &q2) { return angleTo(q1) - angleTo(q2) <= -EPS; }

    // DISTANCETO ORDER

    /**
     * Compares two points by distance to this point. Less than comparator.
     */
    bool distanceToOrderLt(Point2D &p, Point2D &q) { return distanceSquaredTo(p) - distanceSquaredTo(q) < EPS; }

    /**
     * Compares two points by distance to this point. Less than or equal to comparator.
     */
    bool distanceToOrderLe(Point2D &p, Point2D &q) { return distanceSquaredTo(p) - distanceSquaredTo(q) <= -EPS; }

    /**
     * Compares two points by distance to this point. Greater than comparator.
     */
    bool distanceToOrderGt(Point2D &p, Point2D &q) { return distanceSquaredTo(p) - distanceSquaredTo(q) < EPS; }

    /**
     * Compares two points by distance to this point. Greater than or equal to comparator.
     */
    bool distanceToOrderGe(Point2D &p, Point2D &q) { return distanceSquaredTo(p) - distanceSquaredTo(q) <= -EPS; }
};

Vector TT[2][4];
double totalArea = 0.0;

int main() {
    FOR(t, 2) {
        FOR(p, 4) {
            TT[t][p] = Vector(3);
            FOR(i, 3) cin >> TT[t][p][i];
        }
    }
    Vector A, B, C, AB, AC, BC, cross, normal, proj, x, y;
    double faceArea, borderArea, abn, acn, avgX, avgY;
    vector<Point2D> check, intersect, border;
    Point2D face[3];
    FOR(t, 2) {
        FOR(p, 4) {
            check.clear();
            intersect.clear();
            border.clear();
            A = TT[t][(p + 1) % 4];
            B = TT[t][(p + 2) % 4];
            C = TT[t][(p + 3) % 4];
            AB = B - A;
            AC = C - A;
            cross = AB ^ AC;
            faceArea = cross.magnitude() / 2.0;
            borderArea = 0.0;
            normal = cross.direction();
            x = AB.direction();
            y = x ^ normal;
            face[0] = Point2D(0, 0);
            face[1] = Point2D(AB * x, AB * y);
            face[2] = Point2D(AC * x, AC * y);
            FOR(q, 4) {
                For(r, q + 1, 4) {
                    B = TT[t ^ 1][q];
                    C = TT[t ^ 1][r];
                    AB = B - A;
                    AC = C - A;
                    abn = AB * normal;
                    acn = AC * normal;
                    if (copysign(1, abn) != copysign(1, acn)) {
                        check.pb(Point2D(AB * x, AB * y));
                        check.pb(Point2D(AC * x, AC * y));
                    }
                }
            }
            check.erase(unique(check.begin(), check.end()), check.end());
            if (check.size() >= 3) {
                avgX = avgY = 0.0;
                for (Point2D &pp : check) {
                    avgX += pp.x;
                    avgY += pp.y;
                }
                avgX /= check.size();
                avgY /= check.size();
                sort(check.begin(), check.end(), bind(&Point2D::polarOrderLt, Point2D(avgX, avgY), _1, _2));
                if (Point2D::ccw(face[0], face[1], face[2]) == -1) swap(face[1], face[2]);
                bool inside;
                for (Point2D &pp : check) {
                    inside = true;
                    FOR(i, 3) {
                        if (Point2D::ccw(face[i], pp, face[(i + 1) % 3]) == 1) inside = false;
                    }
                    if (inside) border.pb(pp);
                }
                FOR(i, 3) {
                    inside = true;
                    FOR(j, (int) check.size()) {
                        if (Point2D::ccw(check[j], face[i], check[(j + 1) % check.size()]) == 1) inside = false;
                    }
                    if (inside) border.pb(face[i]);
                }
                FOR(i, 3) {
                    Point2D &p1 = face[i];
                    Point2D &q1 = face[(i + 1) % 3];
                    FOR(j, (int) check.size()) {
                        Point2D &p2 = check[j];
                        Point2D &q2 = check[(j + 1) % check.size()];
                        if (Point2D::intersects(p1, q1, p2, q2)) {
                            if (p1 == p2 || p1 == q2) border.pb(p1);
                            else if (q1 == p2 || q1 == q2) border.pb(q1);
                            else border.pb(Point2D::intersection(p1, q1, p2, q2));
                        }
                    }
                }
                border.erase(unique(border.begin(), border.end()), border.end());
                if (border.size() >= 3) {
                    avgX = avgY = 0.0;
                    for (Point2D &pp : border) {
                        avgX += pp.x;
                        avgY += pp.y;
                    }
                    avgX /= border.size();
                    avgY /= border.size();
                    sort(border.begin(), border.end(), bind(&Point2D::polarOrderLt, Point2D(avgX, avgY), _1, _2));
                    FOR(i, (int) border.size()) {
                        borderArea += border[i].x * border[(i + 1) % border.size()].y - border[(i + 1) % border.size()].x * border[i].y;
                    }
                    borderArea /= 2.0;
                }
            }
            totalArea += faceArea - borderArea;
        }
    }
    cout << fixed << setprecision(6) << totalArea << nl;
    return 0;
}
