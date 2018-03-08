import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DS3 {
    private static DS3 o = new DS3();
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
    
    public static class SegmentTree {
        private Node[] tree;
        private int[] array;
        private int N;
        
        private static class Node {
            public int gcd, cnt, min;
            public Node(int val, int cnt) {
                this.min = val;
                this.gcd = val;
                this.cnt = cnt;
            }
            
            public Node(Node left, Node right) {
                this.min = Math.min(left.min, right.min);
                this.gcd = gcd(left.gcd, right.gcd);
                this.cnt = 0;
                if (this.gcd == left.gcd) this.cnt += left.cnt;
                if (this.gcd == right.gcd) this.cnt += right.cnt;
            }
        }
        
        public SegmentTree(int size, int[] arr, boolean oneIndexed) {
            array = new int[size + 1];
            for (int i = 1; i <= size; i++) {
                array[i] = arr[i - (oneIndexed ? 0 : 1)];
            }
            tree = new Node[((int) (2 * Math.pow(2.0, Math.ceil(Math.log((double) size) / Math.log(2.0)))))];
            build(1, 1, size);
            N = size;
        }

        public SegmentTree(int size) {
            array = new int[size + 1];
            tree = new Node[((int) (2 * Math.pow(2.0, Math.ceil(Math.log((double) size) / Math.log(2.0)))))];
            build(1, 1, size);
            N = size;
        }

        private void build(int cur, int cL, int cR) {
            if (cL == cR) {
                tree[cur] = new Node(array[cL], 1);
                return;
            }
            int m = cL + (cR - cL) / 2;
            build(cur * 2, cL , m);
            build(cur * 2 + 1, m + 1, cR);
            tree[cur] = new Node(tree[cur * 2], tree[cur * 2 + 1]);
        }

        private void update(int cur, int cL, int cR, int ind, int val) {
            if (cL > ind || cR < ind) return;
            if (cL >= ind && cR <= ind) {
                tree[cur].min = val;
                tree[cur].gcd = val;
                tree[cur].cnt = 1;
                return;
            }
            int m = cL + (cR - cL) / 2;
            update(cur * 2, cL, m, ind, val);
            update(cur * 2 + 1, m + 1, cR, ind, val);
            tree[cur].min = Math.min(tree[cur * 2].min, tree[cur * 2 + 1].min);
            tree[cur].gcd = gcd(tree[cur * 2].gcd, tree[cur * 2 + 1].gcd);
            tree[cur].cnt = 0;
            if (tree[cur].gcd == tree[cur * 2].gcd) tree[cur].cnt += tree[cur * 2].cnt;
            if (tree[cur].gcd == tree[cur * 2 + 1].gcd) tree[cur].cnt += tree[cur * 2 + 1].cnt;
        }
        
        public void update(int ind, int val) {
            update(1, 1, N, ind, val);
        }
        
        private int minQuery(int cur, int cL, int cR, int l, int r) {
            if (cL > r || cR < l) return Integer.MAX_VALUE;
            if (cL >= l && cR <= r) return tree[cur].min;
            int m = cL + (cR - cL) / 2;
            int left = minQuery(cur * 2, cL, m, l, r);
            int right = minQuery(cur * 2 + 1, m + 1, cR, l, r);
            return Math.min(left, right);
        }

        public int minQuery(int l, int r) {
            return minQuery(1, 1, N, l, r);
        }

        private Pair<Integer, Integer> gcdQuery(int cur, int cL, int cR, int l, int r) {
            if (cL > r || cR < l) return new Pair<Integer, Integer>(0, 0);
            if (cL >= l && cR <= r) return new Pair<Integer, Integer>(tree[cur].gcd, tree[cur].cnt);
            int m = cL + (cR - cL) / 2;
            Pair<Integer, Integer> left = gcdQuery(cur * 2, cL, m, l, r);
            Pair<Integer, Integer> right = gcdQuery(cur * 2 + 1, m + 1, cR, l, r);
            int gcd = gcd(left.first, right.first);
            int cnt = 0;
            if (gcd == left.first) cnt += left.second;
            if (gcd == right.first) cnt += right.second;
            return new Pair<Integer, Integer>(gcd, cnt);
        }

        public Pair<Integer, Integer> gcdQuery(int l, int r) {
            return gcdQuery(1, 1, N, l, r);
        }
    }
    
    private static int gcd(int a, int b) {
        return b == 0 ? a : gcd (b, a % b);
    }
    
    public static class Pair<Item, Item2> {
        public Item first;
        public Item2 second;

        public Pair(Item first, Item2 second) {
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
            return first.equals(p.first) && second.equals(p.second);
        }
    }

    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        int[] arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = in.nextInt();
        }
        SegmentTree st = new SegmentTree(N, arr, false);
        for (int i = 0; i < M; i++) {
            String op = in.next();
            int x = in.nextInt();
            int y = in.nextInt();
            if (op.equals("C")) {
                st.update(x, y);
            } else if (op.equals("M")) {
                out.println(st.minQuery(x, y));
            } else if (op.equals("G")) {
                out.println(st.gcdQuery(x, y).first);
            } else {
                out.println(st.gcdQuery(x, y).second);
            }
        }
        out.close();
    }
}
