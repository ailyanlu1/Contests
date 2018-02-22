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
import java.util.StringTokenizer;

public class DMOPC16C3P4 {
    public static class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) { in = new BufferedReader(new InputStreamReader(inputStream)); }

        public Reader(String fileName) throws FileNotFoundException { in = new BufferedReader(new FileReader(fileName)); }

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
        
        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }

        // public BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }

        public byte nextByte() throws IOException { return Byte.parseByte(next()); }
        public byte nextByte(String delim) throws IOException { return Byte.parseByte(next(delim)); }
        public char nextChar() throws IOException { return next().charAt(0); }
        public char nextChar(String delim) throws IOException { return next(delim).charAt(0); }
        public double nextDouble() throws IOException { return Double.parseDouble(next()); }
        public double nextDouble(String delim) throws IOException { return Double.parseDouble(next(delim)); }
        public float nextFloat() throws IOException { return Float.parseFloat(next()); }
        public float nextFloat(String delim) throws IOException { return Float.parseFloat(next(delim)); }
        public int nextInt() throws IOException { return Integer.parseInt(next()); }
        public int nextInt(String delim) throws IOException { return Integer.parseInt(next(delim)); }
        public long nextLong() throws IOException { return Long.parseLong(next()); }
        public long nextLong(String delim) throws IOException { return Long.parseLong(next(delim)); }
        public short nextShort() throws IOException { return Short.parseShort(next()); }
        public short nextShort(String delim) throws IOException { return Short.parseShort(next(delim)); }
    } // Reader class
    
    public static class Pair<Item, Item2> {
        public Item first;
        public Item2 second;

        public Pair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return first.equals(p.first) && second.equals(p.second);
        }
    }

    public static final class Point2D {
        public static final Comparator<Point2D> X_ORDER = new XOrder();
        public static final Comparator<Point2D> Y_ORDER = new YOrder();

        private final long x;    // x coordinate
        private final long y;    // y coordinate

        public Point2D(long x, long y) {
            this.x = x;
            this.y = y;
        }
        
        public long distanceSquaredTo(Point2D that) {
            long dx = this.x - that.x;
            long dy = this.y - that.y;
            return dx*dx + dy*dy;
        }
        
        private static class XOrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                if (p.x < q.x) return -1;
                if (p.x > q.x) return +1;
                return 0;
            }
        }

        private static class YOrder implements Comparator<Point2D> {
            public int compare(Point2D p, Point2D q) {
                if (p.y < q.y) return -1;
                if (p.y > q.y) return +1;
                return 0;
            }
        }
        
        @Override
        public boolean equals(Object other) {
            if (other == this) return true;
            if (other == null) return false;
            if (other.getClass() != this.getClass()) return false;
            Point2D that = (Point2D) other;
            return this.x == that.x && this.y == that.y;
        }
    }
    
    public static final class Rectangle {
        private final long xmin, ymin;   // minimum x- and y-coordinates
        private final long xmax, ymax;   // maximum x- and y-coordinates

        public Rectangle(long xmin, long ymin, long xmax, long ymax) {
            this.xmin = xmin;
            this.ymin = ymin;
            this.xmax = xmax;
            this.ymax = ymax;
        }

        public boolean contains(Point2D p) {
            return (p.x >= xmin) && (p.x <= xmax) && (p.y >= ymin) && (p.y <= ymax);
        }

        public long distanceSquaredTo(Point2D p) {
            long dx = 0L, dy = 0L;
            if      (p.x < xmin) dx = p.x - xmin;
            else if (p.x > xmax) dx = p.x - xmax;
            if      (p.y < ymin) dy = p.y - ymin;
            else if (p.y > ymax) dy = p.y - ymax;
            return dx*dx + dy*dy;
        }
    }
    
    public static class KdTree {
        private static final boolean VERTICAL = false;
        private static final boolean HORIZONTAL = true;
        
        private final long XMIN, YMIN, XMAX, YMAX;
        
        private static class Node {
            Point2D p;
            Node leftUp, rightDown;
            Rectangle r;
            
            Node(Point2D p, Rectangle r) {
                this.p = p;
                this.r = r;
            }
        }
        
        private int size;
        private Node root;
        
        public KdTree(long xmin, long ymin, long xmax, long ymax, Point2D[] points) {
            size = points.length;
            XMIN = xmin;
            YMIN = ymin;
            XMAX = xmax;
            YMAX = ymax;
            root = construct(root, points, 0, points.length - 1, VERTICAL, XMIN, YMIN, XMAX, YMAX);
        }
        
        private Node construct(Node n, Point2D[] points, int lo, int hi, boolean partition, long xmin, long ymin, long xmax, long ymax) {
            if (lo > hi) return null;
            if (partition == VERTICAL) Arrays.sort(points, lo, hi + 1, Point2D.X_ORDER);
            else Arrays.sort(points, lo, hi + 1, Point2D.Y_ORDER);
            int mid = lo + (hi - lo) / 2;
            Point2D p = points[mid];
            n = new Node(p, new Rectangle(xmin, ymin, xmax, ymax));
            if (partition == VERTICAL) {
                n.leftUp = construct(n.leftUp, points, lo, mid - 1, !partition, xmin, ymin, n.p.x, ymax);
                n.rightDown = construct(n.rightDown, points, mid + 1, hi, !partition, n.p.x, ymin, xmax, ymax);
            } else {
                n.leftUp = construct(n.leftUp, points, lo, mid - 1, !partition, xmin, ymin, xmax, n.p.y);
                n.rightDown = construct(n.rightDown, points, mid + 1, hi, !partition, xmin, n.p.y, xmax, ymax);
            }
            return n;
        }
        
        public boolean isEmpty() {
            return size == 0;
        }
        
        public int size() {
            return size;
        }

        public Pair<Point2D, Integer> nearest(Point2D p) {
            if (isEmpty()) return null;
            return nearest(root, p, null);
        }
        
        private Pair<Point2D, Integer> nearest(Node n, Point2D p, Pair<Point2D, Integer> nearest) {
            if (n == null) return nearest;
            if (nearest == null) nearest = new Pair<Point2D, Integer>(n.p, 1);
            else if (nearest.first.distanceSquaredTo(p) == n.p.distanceSquaredTo(p)) nearest = new Pair<Point2D, Integer>(nearest.first, nearest.second + 1);
            else if (nearest.first.distanceSquaredTo(p) > n.p.distanceSquaredTo(p)) nearest = new Pair<Point2D, Integer>(n.p, 1);
            else if (nearest.first.distanceSquaredTo(p) < n.r.distanceSquaredTo(p)) return nearest;
            if (n.leftUp != null && n.leftUp.r.contains(p)) {
                nearest = nearest(n.leftUp, p, nearest);
                nearest = nearest(n.rightDown, p, nearest);
            } else {
                nearest = nearest(n.rightDown, p, nearest);
                nearest = nearest(n.leftUp, p, nearest);
            }
            return nearest;
        }
    }
    
    private static Reader in = new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    private static final long MAXXY = (long) (1e9 + 1);
    
    public static void main(String[] args) throws Exception {
        int N = in.nextInt();
        Point2D[] points = new Point2D[N];
        for (int i = 0; i < N; i++) {
            long x = in.nextLong();
            long y = in.nextLong();
            points[i] = new Point2D(x, y);
        }
        KdTree tree = new KdTree(-MAXXY, -MAXXY, MAXXY, MAXXY, points);
        int Q = in.nextInt();
        for (int i = 0; i < Q; i++) {
            long x = in.nextLong();
            long y = in.nextLong();
            Point2D q = new Point2D(x, y);
            Pair<Point2D, Integer> nearest = tree.nearest(q);
            out.println(nearest.first.distanceSquaredTo(q) + " " + nearest.second);
//            long closest = Long.MAX_VALUE;
//            int count = 0;
//            for (int j = 0; j < N; j++) {
//                if (points[j].distanceSquaredTo(q) < closest) {
//                    closest = points[j].distanceSquaredTo(q);
//                    count = 1;
//                } else if (points[j].distanceSquaredTo(q) == closest) {
//                    count++;
//                }
//            }
//            out.println(closest + " " + count);
//            if (nearest.first.distanceSquaredTo(q) != closest || nearest.second != count) {
//                throw new Exception("Error");
//            }
        }
        out.close();
    }
}
