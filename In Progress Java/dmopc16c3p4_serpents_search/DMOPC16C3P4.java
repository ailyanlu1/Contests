import java.io.*;
import java.math.*;
import java.util.*;

public class DMOPC16C3P4 {
    private static DMOPC16C3P4 o = new DMOPC16C3P4();
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 16;
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

        public byte nextByte() throws IOException {
            byte ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret *= 10;
                ret += c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return (byte) (-ret);
            return ret;
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (c == '.') while ((c = read()) >= '0' && c <= '9') ret += (c - '0') / (div *= 10);
            if (neg) return -ret;
            return ret;
        }

        public char nextChar() throws IOException {
            byte c;
            do {
                c = read();
            } while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1);
            return (char) c;
        }

        public String next() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            c = read();
            while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) c = read();
            buf[cnt++] = (byte) c;
            while ((c = read()) != -1) {
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }
        
        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n' || c == '\r') break;
                buf[cnt++] = (byte) c;
            }
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
    
    public static void main(String[] args) throws Exception {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            try {
                run(i);
            } catch (Exception e) {
                out.println("Exception thrown on test case " + i);
                e.printStackTrace(out);
            }
            out.flush();
        }
        out.close();
    }
    
    private static final long MAXXY = (long) (1e9 + 1);
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
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
    }
    
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
}
