import java.io.BufferedInputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

public class ECOO16R1P4 {
    public final class Point2D implements Comparable<Point2D> {

        private final double x;    // x coordinate
        private final double y;    // y coordinate
        private final String p;        // party

        /**
         * Initializes a new point (x, y).
         * @param x the x-coordinate
         * @param y the y-coordinate
         * @throws IllegalArgumentException if either {@code x} or {@code y}
         *    is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
         *    {@code Double.NEGATIVE_INFINITY}
         */
        public Point2D(double x, double y, String p) {
            this.p = p;
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
        
        public String p() {
            return p;
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
    public static class KNearestPoints {
        /**
         * This class should not be instantiated.
         */
        private KNearestPoints() {}
        
        /**
         * Static method that computes the K closest points in the specified array of points.
         *
         * @param points array of points
         * @param that starting point
         * @param k number of closest points
         * @return List of K array of K closest points
         */
        public static List<Point2D> nearest(Point2D[] points, final Point2D that, int k) {
            List<Point2D> ans = new ArrayList<>();
            Point2D[] copy = new Point2D[points.length]; // to maintain order of points
            for (int i = 0; i < copy.length; i++) {
                copy[i] = points[i];
            }
            quickSelect(copy, that, k);
            double last = 0;
            for (int i = 0; i < k; i++) {
                ans.add(copy[i]);
                if (copy[i].distanceSquaredTo(that) > last) last = copy[i].distanceSquaredTo(that);
            }
            for (int i = k; i < copy.length; i++) {
                if (copy[i].distanceSquaredTo(that) == last){
                    ans.add(copy[i]);
                }
            }
            return ans;
        }
        
        /**
         * Helper method that does a partial quicksort to find the K closest points.
         *
         * @param copy copy of array of points
         * @param that starting point
         * @param k number of closest points
         * @return List of K array of K closest points
         */
        private static void quickSelect(Point2D[] copy, Point2D that, int k) {
            int start = 0, end = copy.length - 1;
            while (start < end) {
                int p = partition(copy, that, start, end);
                if (p == k) {
                    return;
                } else if (p < k) {
                    start = p + 1;
                } else {
                    end = p - 1;
                }
            }
        }
        private static int partition(Point2D[] copy, Point2D that, int start, int end) {
            Point2D pivot = copy[start];
            int i = start, j = end + 1;
            while (true) {
                while (i < end && copy[++i].distanceTo(that) - pivot.distanceTo(that) < 0);
                while (j > start && copy[--j].distanceTo(that) - pivot.distanceTo(that) > 0);
                if (i >= j) {
                    break;
                }
                swap(copy, i, j);
            }
            swap(copy, start, j);
            return j;
        }

        private static void swap(Point2D[] copy, int i, int j) {
            Point2D tmp = copy[i];
            copy[i] = copy[j];
            copy[j] = tmp;
        }
    }
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        ECOO16R1P4 o = new ECOO16R1P4();
        Point2D c = o.new Point2D(f.nextInt(), f.nextInt(), "");
        Point2D[] a = new Point2D[100];
        HashSet<Point2D> hs = new HashSet<Point2D>();
        for (int i = 0; i < 100; i++) {
            a[i] = o.new Point2D(f.nextInt(), f.nextInt(), f.next());
            hs.add(a[i]);
        }
        int den = 0;
        int num = 0;
        for (int x = (int) (c.x() - 50); x <= c.x() + 50; x++){
            for (int y = (int) (c.y() - 50); y <= c.y() + 50; y++){
                Point2D tr = o.new Point2D(x, y, "R");
                Point2D td = o.new Point2D(x, y, "D");
                if (c.distanceSquaredTo(td) <= 2500 && !hs.contains(tr) && !hs.contains(td)) {
                    den ++;
                    ArrayList<Point2D> al = (ArrayList<Point2D>) KNearestPoints.nearest(a, td, 3);
                    int dems = 0;
                    int reps = 0;
                    for (Point2D z: al) {
                        if (z.p().equals("D")) {
                            dems++;
                        } else {
                            reps++;
                        }
                    }
                    if (dems >= reps) {
                        num++;
                    }
                }
            }
        }
        double percent = Math.round(((double) num / (double) den)*1000)/10.0;
        System.out.println(percent);
    } // run method
} // QuestionFour class
