import java.io.*;
import java.math.*;
import java.util.*;

public class APIO16P2_SkewHeap {
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
                System.err.println("Exception thrown on test case " + i);
                e.printStackTrace(System.err);
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
    }
    
    public static class SkewHeap<Value> {
        private class Node {
            public Value val;
            public Node left = null, right = null;
            public Node(Value val) {
                this.val = val;
            }
        }
        
        private int cmp(Value a, Value b) {
            if (comparator == null) return ((Comparable<Value>) a).compareTo(b);
            else return comparator.compare(a, b);
        }
        
        private int size = 0;
        private Node root = null;
        private Comparator<Value> comparator;
        
        public SkewHeap() {}
        
        public SkewHeap(Comparator<Value> comparator) {
            this.comparator = comparator;
        }
        
        private Node merge(Node a, Node b) {
            if (a == null || b == null) return a == null ? b : a;
            if (cmp(a.val, b.val) > 0) {
                Node temp = a;
                a = b;
                b = temp;
            }
            a.right = merge(b, a.right);
            Node temp = a.left;
            a.left = a.right;
            a.right = temp;
            return a;
        }
        
        public boolean isEmpty() {
            return root == null;
        }
        
        public Value peek() {
            return root.val;
        }
        
        public Value poll() {
            Value ret = root.val;
            root = merge(root.left, root.right);
            size--;
            return ret;
        }
        
        public void offer(Value val) {
            root = merge(root, new Node(val));
            size++;
        }
        
        public void merge(SkewHeap<Value> h) {
            root = merge(root, h.root);
            size += h.size;
        }
        
        int size() {
            return size;
        }
    }

    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt(), M = in.nextInt();
        int[] P = new int[N + M + 1], C = new int[N + M + 1], inDeg = new int[N + M + 1];
        long[] E = new long[N + M + 1];
        SkewHeap<Long>[] PQ = new SkewHeap[N + M + 1];
        for (int i = 2; i <= N + M; inDeg[P[i] = in.nextInt()]++, C[i++] = in.nextInt());
        for (int i = 1; i <= N + M; i++) PQ[i] = new SkewHeap<Long>(Collections.reverseOrder());
        for (int i = N + M; i >= 2; E[P[i]] += E[i] - C[i], i--) {
            for (int j = 0; j < inDeg[i] - 1; j++) E[i] += PQ[i].poll();
            for (int j = 0; j < 2; j++) PQ[P[i]].offer(PQ[i].isEmpty() ? C[i] : C[i] + PQ[i].poll());
            PQ[P[i]].merge(PQ[i]);
        }
        long ans = E[1];
        for (int j = 0; j < inDeg[1]; j++) ans += PQ[1].poll();
        out.println(ans);
    }
}
