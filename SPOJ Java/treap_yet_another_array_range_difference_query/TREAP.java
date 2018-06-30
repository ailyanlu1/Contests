// https://www.spoj.com/problems/TREAP/
import java.io.*;
import java.math.*;
import java.util.*;

public class TREAP {
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
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            try {
                run(i);
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

    static Node root = null;
    static Random rng = new Random(System.currentTimeMillis());

    static class Node {
        public int val, lo, hi, size, subtreeVal;
        public double priority;
        public Node left = null, right = null;
        public Node(int val) {
            this.val = this.lo = this.hi = val;
            this.size = 1;
            this.priority = rng.nextDouble();
            this.subtreeVal = Integer.MAX_VALUE;
        }
    }

    static class NodePair {
        public Node l = null, r = null;
        public NodePair() {}
        public NodePair(Node l, Node r) {
            this.l = l;
            this.r = r;
        }
    }

    static int size(Node x) {
        if (x == null) return 0;
        return x.size;
    }

    static int subtreeVal(Node x) {
        if (x == null) return Integer.MAX_VALUE;
        return x.subtreeVal;
    }

    static void update(Node x) {
        if (x != null) {
            x.lo = x.val;
            x.hi = x.val;
            x.size = 1;
            x.subtreeVal = Integer.MAX_VALUE;
            if (x.left != null) {
                x.lo = x.left.lo;
                x.size += x.left.size;
                x.subtreeVal = Math.min(Math.min(x.subtreeVal, x.left.subtreeVal), x.val - x.left.hi);
            }
            if (x.right != null) {
                x.hi = x.right.hi;
                x.size += x.right.size;
                x.subtreeVal = Math.min(Math.min(x.subtreeVal, x.right.subtreeVal), x.right.lo - x.val);
            }
        }
    }

    static NodePair split(Node x, int val) {
        NodePair ret = new NodePair();
        if (x == null) {
            ret.l = null;
            ret.r = null;
        } else if (val < x.val) {
            NodePair y = split(x.left, val);
            ret.l = y.l;
            x.left = y.r;
            ret.r = x;
        } else {
            NodePair y = split(x.right, val);
            x.right = y.l;
            ret.r = y.r;
            ret.l = x;
        }
        update(x);
        return ret;
    }

    static NodePair splitInd(Node x, int ind) {
        NodePair ret = new NodePair();
        if (x == null) {
            ret.l = null;
            ret.r = null;
            return ret;
        }
        if (ind <= size(x.left)) {
            NodePair y = splitInd(x.left, ind);
            ret.l = y.l;
            x.left = y.r;
            ret.r = x;
        } else {
            NodePair y = splitInd(x.right, ind - size(x.left) - 1);
            x.right = y.l;
            ret.r = y.r;
            ret.l = x;
        }
        update(x);
        return ret;
    }

    static Node merge(Node l, Node r) {
        Node x;
        if (l == null || r == null) {
            x = l == null ? r : l;
        } else if (l.priority > r.priority) {
            l.right = merge(l.right, r);
            x = l;
        } else {
            r.left = merge(l, r.left);
            x = r;
        }
        update(x);
        return x;
    }

    static boolean contains(Node x, int val) {
        if (x == null) return false;
        if (val < x.val) return contains(x.left, val);
        else if (val > x.val) return contains(x.right, val);
        else return true;
    }

    static Node select(Node x, int k) {
        if (x == null) return null;
        int t = size(x.left);
        if (t > k) return select(x.left, k);
        else if (t < k) return select(x.right, k - t - 1);
        return x;
    }

    static Node insert(Node x, Node y) {
        if (x == null) x = y;
        else if (x.priority < y.priority) {
            NodePair s = split(x, y.val);
            y.left = s.l;
            y.right = s.r;
            x = y;
        } else if (y.val < x.val) {
            x.left = insert(x.left, y);
        } else {
            x.right = insert(x.right, y);
        }
        update(x);
        return x;
    }

    static Node remove(Node x, int val) {
        if (val == x.val) x = merge(x.left, x.right);
        else if (val < x.val) x.left = remove(x.left, val);
        else x.right = remove(x.right, val);
        update(x);
        return x;
    }

    static int query(Node x, int l, int r) {
        NodePair y = splitInd(x, l);
        Node left = y.l, mid = y.r;
        y = splitInd(mid, r - l + 1);
        mid = y.l;
        Node right = y.r;
        int ret = subtreeVal(mid);
        x = merge(left, mid);
        x = merge(x, right);
        return ret;
    }

    public static void run(int testCaseNum) throws Exception {
        int Q = in.nextInt();
        for (int i = 0; i < Q; i++) {
            char op = in.nextChar();
            if (op == 'I') {
                int v = in.nextInt();
                if (!contains(root, v)) root = insert(root, new Node(v));
            } else if (op == 'D') {
                int v = in.nextInt();
                if (contains(root, v)) root = remove(root, v);
            } else if (op == 'N') {
                int l = in.nextInt(), r = in.nextInt();
                if (l == r) out.println(-1);
                else out.println(query(root, l, r));
            } else if (op == 'X') {
                int l = in.nextInt(), r = in.nextInt();
                if (l == r) out.println(-1);
                else out.println(select(root, r).val - select(root, l).val);
            } else {
                i--;
            }
        }
    }
}
