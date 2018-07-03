// https://open.kattis.com/problems/closestpair1
import java.io.*;
import java.math.*;
import java.util.*;

public class ClosestPair1 {
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 12;
        private int LENGTH = -1;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (neg) return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (c == '.') while ((c = read()) >= '0') ret += (c - '0') / (div *= 10);
            if (neg) return -ret;
            return ret;
        }

        public char nextChar() throws IOException {
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            return (char) c;
        }

        public String next() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = (byte) c;
            } while ((c = read()) > ' ');
            return new String(buf, 0, cnt);
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = (byte) c;
            } while ((c = read()) >= ' ');
            return new String(buf, 0, cnt);
        }
        
        public void setLength(int length) {
            LENGTH = length;
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead) fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null) return;
            din.close();
        }
    }
    
    private static Reader in;
    private static PrintWriter out;
    
    private static int NUM_OF_TEST_CASES = 1; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "input.txt";
    private static final String OUTPUT_FILE_NAME = "output.txt";
    
    private static boolean stdIn = true;
    private static boolean stdOut = true;
    private static boolean crash = true;
    private static boolean flush = false;
    
    public static void main(String[] args) throws Exception {
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME)));
        for (int i = 1; ; i++) {
            try {
                if(!run(i)) break;
            } catch (Exception e) {
                out.println("Exception thrown on test case " + i);
                e.printStackTrace(out);
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
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
        public double angleTo(Point2D that) {
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
         * Returns a point that is this point rotated theta radians around that point.
         * 
         * @param that the pivot point
         * @param theta the angle in radians
         * @return  
         */
        public Point2D rotate(Point2D that, double theta) {
            double x = that.x + (this.x - that.x) * Math.cos(theta) - (this.y - that.y) * Math.sin(theta);
            double y = that.y + (this.x - that.x) * Math.sin(theta) + (this.y - that.y) * Math.cos(theta);
            return new Point2D(x, y);
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
         * Is this point on the line segment pq?
         * @param p one point of the line segment
         * @param q the other point of the line segment
         * @returns whether this point is on the line segment pq
         */
        public boolean onSegment(Point2D p, Point2D q) {
            return x <= Math.max(p.x, q.x) && x >= Math.min(p.x, q.x) && y <= Math.max(p.y, q.y) && y >= Math.min(p.y, q.y);
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
        public static boolean intersects(Point2D p1, Point2D q1, Point2D p2, Point2D q2) {
            // Find the four orientations needed for general and special cases
            int o1 = ccw(p1, q1, p2);
            int o2 = ccw(p1, q1, q2);
            int o3 = ccw(p2, q2, p1);
            int o4 = ccw(p2, q2, q1);
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
        public static Point2D intersection(Point2D p1, Point2D q1, Point2D p2, Point2D q2) {
            double A1 = q1.y - p1.y;
            double B1 = p1.x - q1.x;
            double C1 = A1 * p1.x + B1 * p1.y;
            double A2 = q2.y - p2.y;
            double B2 = p2.x - q2.x;
            double C2 = A2 * p2.x + B2 * p2.y;
            double det = A1 * B2 - A2 * B1;
            if (Math.abs(det) <= 1e-12) throw new RuntimeException("The lines do not intersect");
            Point2D r = new Point2D((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);
            return r;
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
            return 31 * hashX + hashY;
        }
    }
    
    public static class ClosestPair {
    
        // closest pair of points and their Euclidean distance
        private Point2D best1, best2;
        private double bestDistance = Double.POSITIVE_INFINITY;
    
        /**
         * Computes the closest pair of points in the specified array of points.
         *
         * @param  points the array of points
         * @throws NullPointerException if {@code points} is {@code null} or if any
         *         entry in {@code points[]} is {@code null}
         */
        public ClosestPair(Point2D[] points) {
            int n = points.length;
            if (n <= 1) return;
    
            // sort by x-coordinate (breaking ties by y-coordinate)
            Point2D[] pointsByX = new Point2D[n];
            for (int i = 0; i < n; i++)
                pointsByX[i] = points[i];
            Arrays.sort(pointsByX, Point2D.X_ORDER);
    
            // check for coincident points
            for (int i = 0; i < n-1; i++) {
                if (pointsByX[i].equals(pointsByX[i+1])) {
                    bestDistance = 0.0;
                    best1 = pointsByX[i];
                    best2 = pointsByX[i+1];
                    return;
                }
            }
    
            // sort by y-coordinate (but not yet sorted) 
            Point2D[] pointsByY = new Point2D[n];
            for (int i = 0; i < n; i++)
                pointsByY[i] = pointsByX[i];
    
            // auxiliary array
            Point2D[] aux = new Point2D[n];
    
            closest(pointsByX, pointsByY, aux, 0, n-1);
        }
    
        // find closest pair of points in pointsByX[lo..hi]
        // precondition:  pointsByX[lo..hi] and pointsByY[lo..hi] are the same sequence of points
        // precondition:  pointsByX[lo..hi] sorted by x-coordinate
        // postcondition: pointsByY[lo..hi] sorted by y-coordinate
        private double closest(Point2D[] pointsByX, Point2D[] pointsByY, Point2D[] aux, int lo, int hi) {
            if (hi <= lo) return Double.POSITIVE_INFINITY;
    
            int mid = lo + (hi - lo) / 2;
            Point2D median = pointsByX[mid];
    
            // compute closest pair with both endpoints in left subarray or both in right subarray
            double delta1 = closest(pointsByX, pointsByY, aux, lo, mid);
            double delta2 = closest(pointsByX, pointsByY, aux, mid+1, hi);
            double delta = Math.min(delta1, delta2);
    
            // merge back so that pointsByY[lo..hi] are sorted by y-coordinate
            merge(pointsByY, aux, lo, mid, hi);
    
            // aux[0..m-1] = sequence of points closer than delta, sorted by y-coordinate
            int m = 0;
            for (int i = lo; i <= hi; i++) {
                if (Math.abs(pointsByY[i].x() - median.x()) < delta)
                    aux[m++] = pointsByY[i];
            }
    
            // compare each point to its neighbors with y-coordinate closer than delta
            for (int i = 0; i < m; i++) {
                // a geometric packing argument shows that this loop iterates at most 7 times
                for (int j = i+1; (j < m) && (aux[j].y() - aux[i].y() < delta); j++) {
                    double distance = aux[i].distanceTo(aux[j]);
                    if (distance < delta) {
                        delta = distance;
                        if (distance < bestDistance) {
                            bestDistance = delta;
                            best1 = aux[i];
                            best2 = aux[j];
                        }
                    }
                }
            }
            return delta;
        }
    
        /**
         * Returns one of the points in the closest pair of points.
         *
         * @return one of the two points in the closest pair of points;
         *         {@code null} if no such point (because there are fewer than 2 points)
         */
        public Point2D either() {
            return best1;
        }
    
        /**
         * Returns the other point in the closest pair of points.
         *
         * @return the other point in the closest pair of points
         *         {@code null} if no such point (because there are fewer than 2 points)
         */
        public Point2D other() {
            return best2;
        }
    
        /**
         * Returns the Eucliden distance between the closest pair of points.
         *
         * @return the Euclidean distance between the closest pair of points
         *         {@code Double.POSITIVE_INFINITY} if no such pair of points
         *         exist (because there are fewer than 2 points)
         */
        public double distance() {
            return bestDistance;
        }
    
        // is v < w ?
        private static boolean less(Comparable v, Comparable w) {
            return v.compareTo(w) < 0;
        }
    
        // stably merge a[lo .. mid] with a[mid+1 ..hi] using aux[lo .. hi]
        // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
        private static void merge(Comparable[] a, Comparable[] aux, int lo, int mid, int hi) {
            // copy to aux[]
            for (int k = lo; k <= hi; k++) {
                aux[k] = a[k];
            }
        
            // merge back to a[] 
            int i = lo, j = mid+1;
            for (int k = lo; k <= hi; k++) {
                if      (i > mid)              a[k] = aux[j++];
                else if (j > hi)               a[k] = aux[i++];
                else if (less(aux[j], aux[i])) a[k] = aux[j++];
                else                           a[k] = aux[i++];
            }
        }
    }
    
    public static boolean run(int testCaseNum) throws Exception {
        int N = in.nextInt();
        if (N == 0) return false;
        Point2D[] P = new Point2D[N];
        for (int i = 0; i < N; i++) P[i] = new Point2D(in.nextDouble(), in.nextDouble());
        ClosestPair cp = new ClosestPair(P);
        Point2D a = cp.either(), b = cp.other();
        out.println(a.x() + " " + a.y() + " " + b.x() + " " + b.y());
        return true;
    }
}
