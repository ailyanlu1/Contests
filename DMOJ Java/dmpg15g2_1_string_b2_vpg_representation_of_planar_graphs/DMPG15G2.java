package dmpg15g2_1_string_b2_vpg_representation_of_planar_graphs;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.StringTokenizer;

public class DMPG15G2 {
    private static DMPG15G2 o = new DMPG15G2();
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
    
    public class Pair<Item, Item2> {
        private Item first;
        private Item2 second;

        public Pair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }

        public Item getFirst() {
            return this.first;
        }

        public void setFirst(Item first) {
            this.first = first;
        }

        public Item2 getSecond() {
            return this.second;
        }

        public void setSecond(Item2 second) {
            this.second = second;
        }

        public void set(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int hashCode() {
            return 31 * first.hashCode() + second.hashCode();
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return p.first.equals(first) && p.second.equals(second);
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static Point2D[] points;
    private static ArrayList<Pair<Integer, Integer>> graph = new ArrayList<Pair<Integer, Integer>>();
    private static boolean[][] mat;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        points = new Point2D[N + 1];
        mat = new boolean[N + 1][N + 1];
        for (int i = 1; i <= N; i++) {
            points[i] = new Point2D(in.nextInt(), in.nextInt());
        }
        for (int i = 0; i < M; i++) {
            boolean valid = true;
            int u = in.nextInt();
            int v = in.nextInt();
            for (Pair<Integer, Integer> p: graph) {
                if (intersection(p.getFirst(), p.getSecond(), u, v)) valid = false;
            }
            if (valid) {
                graph.add(o.new Pair<Integer, Integer>(u, v));
                mat[u][v] = mat[v][u] = true;
            }
        }
        int ans = 1;
        Main: for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (mat[i][j]) {
                    ans = Math.max(ans, 2);
                    for (int k = j + 1; k <= N; k++) {
                        if (mat[i][k] && mat[j][k]) {
                            ans = Math.max(ans, 3);
                            for (int m = k + 1; m <= N; m++) {
                                if (mat[i][m] && mat[j][m] && mat[k][m]) {
                                    ans = 4;
                                    break Main;
                                }
                            }
                        }
                    }
                }
            }
        }
        out.println(ans);
        out.close();
    }
    
    private static boolean intersection(int a1, int a2, int b1, int b2) {
        double A1 = points[a2].y() - points[a1].y();
        double B1 = points[a1].x() - points[a2].x();
        double C1 = A1 * points[a1].x() + B1 * points[a1].y();
        
        double A2 = points[b2].y() - points[b1].y();
        double B2 = points[b1].x() - points[b2].x();
        double C2 = A2 * points[b1].x() + B2 * points[b1].y();
        
        double det = A1 * B2 - A2 * B1;
        if (det == 0) return A1 * C2 == A2 * C1 && B1 * C2 == B2 * C1;
        double X = (B2 * C1 - B1 * C2) / det;
        return X > Math.min(points[a1].x(), points[a2].x()) && X < Math.max(points[a1].x(), points[a2].x())
            && X > Math.min(points[b1].x(), points[b2].x()) && X < Math.max(points[b1].x(), points[b2].x());
    }
}
