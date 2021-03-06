import java.io.*;
import java.math.*;
import java.util.*;

public class CCC18S5 {
    private static CCC18S5 o = new CCC18S5();
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
    
    public static class Edge implements Comparable<Edge> {
        int a, b;
        long c;
        boolean type;
        
        public Edge(int a, int b, long c, boolean type) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.type = type;
        }
        
        @Override
        public int compareTo(Edge e) {
            return c < e.c ? -1 : (c == e.c ? 0 : 1);
        }
    }
    
    static int N, M, P, Q;
    static Edge[] edges;
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        P = in.nextInt();
        Q = in.nextInt();
        edges = new Edge[P + Q];
        long total = 0;
        for (int i = 0; i < P; i++) {
            int a = in.nextInt();
            int b = in.nextInt();
            long c = in.nextLong();
            total += c * N;
            edges[i] = new Edge(a - 1, b - 1, c, false);
        }
        for (int i = 0; i < Q; i++) {
            int a = in.nextInt();
            int b = in.nextInt();
            long c = in.nextLong();
            total += c * M;
            edges[P + i] = new Edge(a - 1, b - 1, c, true); 
        }
        out.println(total - mst());
    }
    
    static long mst() {
        long weight = 0;
        PriorityQueue<Edge> PQ = new PriorityQueue<Edge>();
        for (Edge e : edges) PQ.offer(e);
        UF cities = new UF(M), planets = new UF(N);
        while (!PQ.isEmpty() && (cities.cnt > 1 || planets.cnt > 1)) {
            Edge e = PQ.poll();
            if (!e.type && cities.join(e.a, e.b)) weight += planets.cnt * e.c;
            else if (e.type && planets.join(e.a, e.b)) weight += cities.cnt * e.c;
        }
        return weight;
    }
    
    public static class UF {
        public int[] par;
        public char[] rank;
        public int cnt;
        
        public UF(int N) {
            par = new int[N];
            rank = new char[N];
            cnt = N;
            for (int i = 0; i < N; i++) {
                par[i] = i;
                rank[i] = 0;
            }
        }

        int find(int p) {
            while (p != par[p]) p = par[p] = par[par[p]];
            return p;
        }
        
        boolean join(int p, int q) {
            p = find(p);
            q = find(q);
            if (p == q) return false;
            if (rank[p] < rank[q]) par[p] = q;
            else if (rank[p] > rank[q]) par[q] = p;
            else {
                par[q] = p;
                rank[p]++;
            }
            cnt--;
            return true;
        }
    }
}
