#include <bits/stdc++.h>

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

class Vector {
private:
    int d;               // dimension of the vector
    double *data;        // array of vector's components

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
    }

    /**
     * Initializes a vector from either an array.
     *
     * @param d the dimension of the vector
     * @param a the array
     */
    Vector(int d, double *a) {
        this->d = d;
        // defensive copy so that client can't alter our copy of data[]
        this->data = new double[d];
        for (int i = 0; i < d; i++)
            this->data[i] = a[i];
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
    double operator ^ (Vector &that) {
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
    Vector &operator * (Vector &that) {
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
     * Returns the angle of this 2-D vector to horizontal.
     *
     *
     * @return the angle of this 2-D vector to horizontal
     * @throws IllegalArgumentException if this vector is not 2-dimensional
     */
    double angle() {
        if (d != 2) throw invalid_argument("Vector must be 2-dimensional");
        return atan2(data[1], data[0]);
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
        return that.scale(dot(that) / (that.magnitude() * that.magnitude()));
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

int T;
double theta;
Vector V(3), A(3), R(3);

int main() {
    ri(T);
    FOR(i, T) {
        rd(V[0]); rd(V[1]); rd(V[2]);
        rd(A[0]); rd(A[1]); rd(A[2]);
        rd(theta);
        R = V.rotate(A, theta);
        printf("%.6f %.6f %.6f\n", R[0], R[1], R[2]);
    }
    return 0;
}
