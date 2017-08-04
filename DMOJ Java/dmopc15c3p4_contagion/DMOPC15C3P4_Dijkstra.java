package dmopc15c3p4_contagion;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class DMOPC15C3P4_Dijkstra {
    private static DMOPC15C3P4_Dijkstra o = new DMOPC15C3P4_Dijkstra();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken();
        }

        public String next(String delim) throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken(delim);
        }

        /*
        public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }
        */

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public byte nextByte(String delim) throws IOException {
            return Byte.parseByte(next(delim));
        }

        public char nextChar() throws IOException {
            return next().charAt(0);
        }

        public char nextChar(String delim) throws IOException {
            return next(delim).charAt(0);
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public double nextDouble(String delim) throws IOException {
            return Double.parseDouble(next(delim));
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }

        public float nextFloat(String delim) throws IOException {
            return Float.parseFloat(next(delim));
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public int nextInt(String delim) throws IOException {
            return Integer.parseInt(next(delim));
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public long nextLong(String delim) throws IOException {
            return Long.parseLong(next(delim));
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public short nextShort(String delim) throws IOException {
            return Short.parseShort(next(delim));
        }

        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }
    } // Reader class
    
    public class IndexMinPQ<Key extends Comparable<Key>> implements Iterable<Integer> {
        private int maxN;        // maximum number of elements on PQ
        private int n;           // number of elements on PQ
        private int[] pq;        // binary heap using 1-based indexing
        private int[] qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
        private Key[] keys;      // keys[i] = priority of i

        /**
         * Initializes an empty indexed priority queue with indices between {@code 0}
         * and {@code maxN - 1}.
         * @param  maxN the keys on this priority queue are index from {@code 0}
         *         {@code maxN - 1}
         * @throws IllegalArgumentException if {@code maxN < 0}
         */
        public IndexMinPQ(int maxN) {
            if (maxN < 0) throw new IllegalArgumentException();
            this.maxN = maxN;
            n = 0;
            keys = (Key[]) new Comparable[maxN + 1];    // make this of length maxN??
            pq   = new int[maxN + 1];
            qp   = new int[maxN + 1];                   // make this of length maxN??
            for (int i = 0; i <= maxN; i++)
                qp[i] = -1;
        }

        /**
         * Returns true if this priority queue is empty.
         *
         * @return {@code true} if this priority queue is empty;
         *         {@code false} otherwise
         */
        public boolean isEmpty() {
            return n == 0;
        }

        /**
         * Is {@code i} an index on this priority queue?
         *
         * @param  i an index
         * @return {@code true} if {@code i} is an index on this priority queue;
         *         {@code false} otherwise
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         */
        public boolean contains(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            return qp[i] != -1;
        }

        /**
         * Returns the number of keys on this priority queue.
         *
         * @return the number of keys on this priority queue
         */
        public int size() {
            return n;
        }

        /**
         * Associates key with index {@code i}.
         *
         * @param  i an index
         * @param  key the key to associate with index {@code i}
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if there already is an item associated
         *         with index {@code i}
         */
        public void insert(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (contains(i)) throw new IllegalArgumentException("index is already in the priority queue");
            n++;
            qp[i] = n;
            pq[n] = i;
            keys[i] = key;
            swim(n);
        }

        /**
         * Returns an index associated with a minimum key.
         *
         * @return an index associated with a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public int minIndex() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return pq[1];
        }

        /**
         * Returns a minimum key.
         *
         * @return a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public Key minKey() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return keys[pq[1]];
        }

        /**
         * Removes a minimum key and returns its associated index.
         * @return an index associated with a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public int delMin() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            int min = pq[1];
            exch(1, n--);
            sink(1);
            assert min == pq[n+1];
            qp[min] = -1;        // delete
            keys[min] = null;    // to help with garbage collection
            pq[n+1] = -1;        // not needed
            return min;
        }

        /**
         * Returns the key associated with index {@code i}.
         *
         * @param  i the index of the key to return
         * @return the key associated with index {@code i}
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public Key keyOf(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            else return keys[i];
        }

        /**
         * Change the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to change
         * @param  key change the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void changeKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            keys[i] = key;
            swim(qp[i]);
            sink(qp[i]);
        }

        /**
         * Change the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to change
         * @param  key change the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @deprecated Replaced by {@code changeKey(int, Key)}.
         */
        @Deprecated
        public void change(int i, Key key) {
            changeKey(i, key);
        }

        /**
         * Decrease the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to decrease
         * @param  key decrease the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if {@code key >= keyOf(i)}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void decreaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) <= 0)
                throw new IllegalArgumentException("Calling decreaseKey() with given argument would not strictly decrease the key");
            keys[i] = key;
            swim(qp[i]);
        }

        /**
         * Increase the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to increase
         * @param  key increase the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if {@code key <= keyOf(i)}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void increaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) >= 0)
                throw new IllegalArgumentException("Calling increaseKey() with given argument would not strictly increase the key");
            keys[i] = key;
            sink(qp[i]);
        }

        /**
         * Remove the key associated with index {@code i}.
         *
         * @param  i the index of the key to remove
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void delete(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            int index = qp[i];
            exch(index, n--);
            swim(index);
            sink(index);
            keys[i] = null;
            qp[i] = -1;
        }


       /***************************************************************************
        * General helper functions.
        ***************************************************************************/
        private boolean greater(int i, int j) {
            return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
        }

        private void exch(int i, int j) {
            int swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }


       /***************************************************************************
        * Heap helper functions.
        ***************************************************************************/
        private void swim(int k) {
            while (k > 1 && greater(k/2, k)) {
                exch(k, k/2);
                k = k/2;
            }
        }

        private void sink(int k) {
            while (2*k <= n) {
                int j = 2*k;
                if (j < n && greater(j, j+1)) j++;
                if (!greater(k, j)) break;
                exch(k, j);
                k = j;
            }
        }


       /***************************************************************************
        * Iterators.
        ***************************************************************************/

        /**
         * Returns an iterator that iterates over the keys on the
         * priority queue in ascending order.
         * The iterator doesn't implement {@code remove()} since it's optional.
         *
         * @return an iterator that iterates over the keys in ascending order
         */
        public Iterator<Integer> iterator() { return new HeapIterator(); }

        private class HeapIterator implements Iterator<Integer> {
            // create a new pq
            private IndexMinPQ<Key> copy;

            // add all elements to copy of heap
            // takes linear time since already in heap order so no keys move
            public HeapIterator() {
                copy = new IndexMinPQ<Key>(pq.length - 1);
                for (int i = 1; i <= n; i++)
                    copy.insert(pq[i], keys[pq[i]]);
            }

            public boolean hasNext()  { return !copy.isEmpty();                     }
            public void remove()      { throw new UnsupportedOperationException();  }

            public Integer next() {
                if (!hasNext()) throw new NoSuchElementException();
                return copy.delMin();
            }
        }
    }
    
    public static final class Point2D implements Comparable<Point2D> {

        /**
         * Compares two points by x-coordinate.
         */
        public static final Comparator<Point2D> X_ORDER = new XOrder();

        /**
         * Compares two points by y-coordinate.
         */
        public static final Comparator<Point2D> Y_ORDER = new YOrder();

        /**
         * Compares two points by polar radius.
         */
        public static final Comparator<Point2D> R_ORDER = new ROrder();

        private final double x;    // x coordinate
        private final double y;    // y coordinate

        /**
         * Initializes a new point (x, y).
         * @param x the x-coordinate
         * @param y the y-coordinate
         * @throws IllegalArgumentException if either {@code x} or {@code y}
         *    is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
         *    {@code Double.NEGATIVE_INFINITY}
         */
        public Point2D(double x, double y) {
            if (Double.isInfinite(x) || Double.isInfinite(y))
                throw new IllegalArgumentException("Coordinates must be finite");
            if (Double.isNaN(x) || Double.isNaN(y))
                throw new IllegalArgumentException("Coordinates cannot be NaN");
            if (x == 0.0) this.x = 0.0;  // convert -0.0 to +0.0
            else          this.x = x;

            if (y == 0.0) this.y = 0.0;  // convert -0.0 to +0.0
            else          this.y = y;
        }

        /**
         * Returns the x-coordinate.
         * @return the x-coordinate
         */
        public double x() {
            return x;
        }

        /**
         * Returns the y-coordinate.
         * @return the y-coordinate
         */
        public double y() {
            return y;
        }

        /**
         * Returns the polar radius of this point.
         * @return the polar radius of this point in polar coordiantes: sqrt(x*x + y*y)
         */
        public double r() {
            return Math.sqrt(x*x + y*y);
        }

        /**
         * Returns the angle of this point in polar coordinates.
         * @return the angle (in radians) of this point in polar coordiantes (between –&pi;/2 and &pi;/2)
         */
        public double theta() {
            return Math.atan2(y, x);
        }

        /**
         * Returns the angle between this point and that point.
         * @return the angle in radians (between –&pi; and &pi;) between this point and that point (0 if equal)
         */
        private double angleTo(Point2D that) {
            double dx = that.x - this.x;
            double dy = that.y - this.y;
            return Math.atan2(dy, dx);
        }

        /**
         * Returns true if a→b→c is a counterclockwise turn.
         * @param a first point
         * @param b second point
         * @param c third point
         * @return { -1, 0, +1 } if a→b→c is a { clockwise, collinear; counterclocwise } turn.
         */
        public static int ccw(Point2D a, Point2D b, Point2D c) {
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
        public static double area2(Point2D a, Point2D b, Point2D c) {
            return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
        }

        /**
         * Returns the Euclidean distance between this point and that point.
         * @param that the other point
         * @return the Euclidean distance between this point and that point
         */
        public double distanceTo(Point2D that) {
            double dx = this.x - that.x;
            double dy = this.y - that.y;
            return Math.sqrt(dx*dx + dy*dy);
        }

        /**
         * Returns the square of the Euclidean distance between this point and that point.
         * @param that the other point
         * @return the square of the Euclidean distance between this point and that point
         */
        public double distanceSquaredTo(Point2D that) {
            double dx = this.x - that.x;
            double dy = this.y - that.y;
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
        public int compareTo(Point2D that) {
            if (this.y < that.y) return -1;
            if (this.y > that.y) return +1;
            if (this.x < that.x) return -1;
            if (this.x > that.x) return +1;
            return 0;
        }

        /**
         * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
         *
         * @return the comparator
         */
        public Comparator<Point2D> polarOrder() {
            return new PolarOrder();
        }

        /**
         * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
         *
         * @return the comparator
         */
        public Comparator<Point2D> atan2Order() {
            return new Atan2Order();
        }

        /**
         * Compares two points by distance to this point.
         *
         * @return the comparator
         */
        public Comparator<Point2D> distanceToOrder() {
            return new DistanceToOrder();
        }

        // compare points according to their x-coordinate
        private static class XOrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                if (p.x < q.x) return -1;
                if (p.x > q.x) return +1;
                return 0;
            }
        }

        // compare points according to their y-coordinate
        private static class YOrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                if (p.y < q.y) return -1;
                if (p.y > q.y) return +1;
                return 0;
            }
        }

        // compare points according to their polar radius
        private static class ROrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                double delta = (p.x*p.x + p.y*p.y) - (q.x*q.x + q.y*q.y);
                if (delta < 0) return -1;
                if (delta > 0) return +1;
                return 0;
            }
        }
     
        // compare other points relative to atan2 angle (bewteen -pi/2 and pi/2) they make with this Point
        private class Atan2Order implements Comparator<Point2D> {
            public int compare(Point2D q1, Point2D q2) {
                double angle1 = angleTo(q1);
                double angle2 = angleTo(q2);
                if      (angle1 < angle2) return -1;
                else if (angle1 > angle2) return +1;
                else                      return  0;
            }
        }

        // compare other points relative to polar angle (between 0 and 2pi) they make with this Point
        private class PolarOrder implements Comparator<Point2D> {
            public int compare(Point2D q1, Point2D q2) {
                double dx1 = q1.x - x;
                double dy1 = q1.y - y;
                double dx2 = q2.x - x;
                double dy2 = q2.y - y;

                if      (dy1 >= 0 && dy2 < 0) return -1;    // q1 above; q2 below
                else if (dy2 >= 0 && dy1 < 0) return +1;    // q1 below; q2 above
                else if (dy1 == 0 && dy2 == 0) {            // 3-collinear and horizontal
                    if      (dx1 >= 0 && dx2 < 0) return -1;
                    else if (dx2 >= 0 && dx1 < 0) return +1;
                    else                          return  0;
                }
                else return -ccw(Point2D.this, q1, q2);     // both above or below

                // Note: ccw() recomputes dx1, dy1, dx2, and dy2
            }
        }

        // compare points according to their distance to this point
        private class DistanceToOrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                double dist1 = distanceSquaredTo(p);
                double dist2 = distanceSquaredTo(q);
                if      (dist1 < dist2) return -1;
                else if (dist1 > dist2) return +1;
                else                    return  0;
            }
        }


        /**       
         * Compares this point to the specified point.
         *       
         * @param  other the other point
         * @return {@code true} if this point equals {@code other};
         *         {@code false} otherwise
         */
        @Override
        public boolean equals(Object other) {
            if (other == this) return true;
            if (other == null) return false;
            if (other.getClass() != this.getClass()) return false;
            Point2D that = (Point2D) other;
            return this.x == that.x && this.y == that.y;
        }

        /**
         * Return a string representation of this point.
         * @return a string representation of this point in the format (x, y)
         */
        @Override
        public String toString() {
            return "(" + x + ", " + y + ")";
        }

        /**
         * Returns an integer hash code for this point.
         * @return an integer hash code for this point
         */
        @Override
        public int hashCode() {
            int hashX = ((Double) x).hashCode();
            int hashY = ((Double) y).hashCode();
            return 31*hashX + hashY;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static Point2D[] points;
    private static long[] distTo;
    private static IndexMinPQ<Long> pq;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        points = new Point2D[N];
        distTo = new long[N];
        for (int i = 0; i < N; i++) {
            points[i] = new Point2D(in.nextInt(), in.nextInt());
        }
        dijkstra(in.nextInt() - 1);
        Arrays.sort(distTo);
        int Q = in.nextInt();
        for (int i = 0; i < Q; i++) {
           long qi = in.nextLong();
           int lo = 0;
           int hi = N - 1;
           while (lo <= hi) {
               int mid = lo + (hi - lo) / 2;
               if (distTo[mid] <= qi) {
                   lo = mid + 1;
               } else {
                   hi = mid - 1;
               }
           }
           out.println(lo);
        }
        out.close();
    }
    
    public static void dijkstra(int s) {
        distTo = new long[points.length];

        for (int v = 0; v < points.length; v++)
            distTo[v] = Long.MAX_VALUE;
        distTo[s] = 0;

        // relax vertices in order of distance from s
        pq = o.new IndexMinPQ<Long>(points.length);
        pq.insert(s, distTo[s]);
        while (!pq.isEmpty()) {
            int v = pq.delMin();
            for (int w = 0; w < points.length; w++) {
                long dist = (long) points[v].distanceSquaredTo(points[w]);
                if (distTo[w] > distTo[v] + dist) {
                    distTo[w] = distTo[v] + dist;
                    if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
                    else                pq.insert(w, distTo[w]);
                }
            }
        }
    }
}
