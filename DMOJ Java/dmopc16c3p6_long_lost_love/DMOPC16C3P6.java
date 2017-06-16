package dmopc16c3p6_long_lost_love;

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

public class DMOPC16C3P6 { // 60/100 TLE
    private static DMOPC16C3P6 o = new DMOPC16C3P6();
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

        /*public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }*/

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
    
    private static class Node {
        public Node left, right;
        public int pre, suf, sum;
        public Node(int val) {
            this.pre = val;
            this.suf = val;
            this.sum = val;
        }
        
        public Node(Node l, Node r) {
            this.left = l;
            this.right = r;
            this.pre = Math.max(l.pre, r.pre + l.sum);
            this.suf = Math.max(l.suf + r.sum, r.suf);
            this.sum = l.sum + r.sum;
        }
    }
    
    public static void init(int size) {
        rev[0] = build(1, size);
    }
    
    private static Node build(int cL, int cR) {
        if (cL == cR) return new Node(arr[cL]);
        int m = (cL + cR) >> 1;
        return new Node(build(cL , m), build(m + 1, cR));
    }
    
    public static void update(int ind, int val) {
        arr[ind] = val;
        rev[revInd + 1] = update(rev[revInd], 1, arr.length - 1, ind);
        revInd++;
    }
    
    private static Node update(Node cur, int cL, int cR, int ind) {
        if (cL <= ind && ind <= cR) {
            if (cL == cR) return new Node(arr[cL]);
            int m = (cL + cR) >> 1;
            return new Node(update(cur.left, cL, m, ind), update(cur.right, m + 1, cR, ind));
        }
        return cur;
    }
    
    public static int query(int type, int l, int r) {
        if (type == 1) return query(rev[revInd], 1, arr.length - 1, l, r).pre;
        return query(rev[revInd], 1, arr.length - 1, l, r).suf;
    }
    
    private static Query query(Node cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return null;
        if (cL >= l && cR <= r) return new Query(cur.pre, cur.suf, cur.sum);
        int m = (cL + cR) >> 1;
        Query left = query(cur.left, cL, m, l, r);
        Query right = query(cur.right, m + 1, cR, l, r);
        if (left == null) return right;
        if (right == null) return left;
        return new Query(left, right);
    }
    
    public static void revert(int x) {
        rev[++revInd] = rev[x];
    }
    
    private static class Query {
        public int pre, suf, sum;
        public Query(int pre, int suf, int sum) {
            this.pre = pre;
            this.suf = suf;
            this.sum = sum;
        }
        
        public Query(Query l, Query r) {
            this.pre = Math.max(l.pre, r.pre + l.sum);
            this.suf = Math.max(l.suf + r.sum, r.suf);
            this.sum = l.sum + r.sum;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static int[] arr;
    private static Node[] rev;
    private static int revInd = 0;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        arr = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            arr[i] = in.nextInt();
        }
        int Q = in.nextInt();
        rev = new Node[Q];
        init(N);
        for (int i = 0; i < Q; i++) {
            char c = in.nextChar();
            if (c == 'U') {
                update(in.nextInt(), in.nextInt());
            } else if (c == 'G') {
                revert(in.nextInt());
            } else if (c == 'P') {
                out.println(query(1, in.nextInt(), in.nextInt()));
            } else if (c == 'S') {
                out.println(query(2, in.nextInt(), in.nextInt()));
            }
        }
        out.close();
    }
}
