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
import java.util.StringTokenizer;
import java.util.TreeMap;

public class DMOPC15C2P6 {
    private static DMOPC15C2P6 o = new DMOPC15C2P6();

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
    
    public class DynamicLazySegmentTree {
        private Node root;
        private int size;
        
        private class Node {
            public Node left, right;
            public int max, lazy;
            
            public Node() {
            }
            
            public Node(Node l, Node r) {
                this.left = l;
                this.right = r;
                this.max = Math.max(l.max, r.max);
            }
            
            public void propogate() {
                if (lazy != 0) {
                    max += lazy;
                    if (left != null) {
                        left.lazy += lazy;
                    }
                    if (right != null) {
                        right.lazy += lazy;
                    }
                    lazy = 0;
                }
            }
        }
        
        public DynamicLazySegmentTree(int size) {
            root = build(1, size);
            this.size = size;
        }
        
        public int size() {
            return this.size;
        }
        
        private Node build(int cL, int cR) {
            if (cL == cR) return new Node();
            int m = (cL + cR) >> 1;
            return new Node(build(cL , m), build(m + 1, cR));
        }
        
        public void update(int l, int r, int val) {
            root = update(root, 1, size, l, r, val);
        }
        
        private Node update(Node cur, int cL, int cR, int l, int r, int val) {
            cur.propogate();
            if (cL > r || cR < l) return cur;
            if (cL >= l && cR <= r) {
                cur.lazy += val;
                cur.propogate();
                return cur;
            }
            int m = (cL + cR) >> 1;
            return new Node(update(cur.left, cL, m, l, r, val), update(cur.right, m + 1, cR, l, r, val));
        }
    }

    public static class Point {
        public int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public void rotate() {
            int X = this.x;
            int Y = this.y;
            this.x = X + Y;
            this.y = Y - X;
        }
    }
    
    public static class Line implements Comparable<Line>{
        public int x, y1, y2, val;
        
        public Line (int x, int y1, int y2, int val) {
            this.x = x;
            this.y1 = y1;
            this.y2 = y2;
            this.val = val;
        }

        @Override
        public int compareTo(Line l) {
            if (this.x == l.x) return l.val - this.val;
            return this.x - l.x;
        }
    }

    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static TreeMap<Integer, Integer> ys = new TreeMap<Integer, Integer>();
    private static Line[] lines;

    public static void main(String[] args) throws IOException {
        int M = in.nextInt();
        Point[] magnets = new Point[M];
        for (int i = 0; i < M; i++) {
            magnets[i] = new Point(in.nextInt(), in.nextInt());
        }
        int N = in.nextInt();
        lines = new Line[2 * N];
        for (int i = 0; i < N; i++) {
            Point p = new Point(in.nextInt(), in.nextInt());
            int dist = Integer.MAX_VALUE;
            for (int j = 0; j < M; j++) {
                dist = Math.min(dist, Math.abs(p.x - magnets[j].x) + Math.abs(p.y - magnets[j].y));
            }
            Point l = new Point(p.x - dist + 1, p.y);
            Point r = new Point(p.x + dist - 1, p.y);
            Point u = new Point(p.x, p.y + dist - 1);
            Point d = new Point(p.x, p.y - dist + 1);
            l.rotate(); r.rotate(); u.rotate(); d.rotate();
            lines[i << 1] = new Line(l.x, d.y, l.y, 1);
            lines[i << 1 | 1] = new Line(u.x, r.y, u.y, -1);
            ys.put(l.y, 0);
            ys.put(d.y, 0);
        }
        int ind = 1;
        for (Integer key: ys.keySet()) {
            ys.put(key, ind++);
        }
        Arrays.sort(lines);
        DynamicLazySegmentTree st = o.new DynamicLazySegmentTree(ys.size());
        int ans = 0;
        for (int i = 0; i < 2 * N; i++) {
            st.update(ys.get(lines[i].y1), ys.get(lines[i].y2), lines[i].val);
            ans = Math.max(ans, st.root.max);
        }
        out.println(ans);
        out.close();
    }
}
