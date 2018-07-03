import java.io.*;
import java.math.*;
import java.util.*;

public class NCCO3D1P3 {
    private static NCCO3D1P3 o = new NCCO3D1P3();
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
        
        public short nextShort() throws IOException {
            short ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret *= 10;
                ret += c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return (short) (-ret);
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
        
        public float nextFloat() throws IOException {
            float ret = 0, div = 1;
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
    private static boolean crash = true;
    private static boolean flush = false;
    
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
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
    }
    
    public static class Pair {
        public int first;
        public int second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int hashCode() {
            return 31 * first + second;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return first == p.first && second == p.second;
        }
        
        @Override
        public String toString() {
            return "(" + first + ", " + second + ")";
        }
    }
    
    static int R, C;
    static int[][] grid, cnt;
    static boolean[][] vis;
    static long[][] ways;
    static HashSet<Pair>[][] connected;
    static Pair[] dir = {new Pair(-2, -1), new Pair(-2, 1), new Pair(-1, -2), new Pair(-1, 2), new Pair(1, -2), new Pair(1, 2), new Pair(2, -1), new Pair(2, 1)};
    
    static void dfs(int i, int j, HashSet<Pair> hs) {
        if (i < 0 || i >= R || j < 0 || j >= C) return;
        if (vis[i][j]) return;
        vis[i][j] = true;
        if (grid[i][j] == 2) return;
        if (grid[i][j] == 0) {
            hs.add(new Pair(i, j));
            return;
        }
        for (Pair p : dir) dfs(i + p.first, j + p.second, hs);
    }
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        R = in.nextInt();
        C = in.nextInt();
        grid = new int[R][C];
        cnt = new int[R][C];
        vis = new boolean[R][C];
        ways = new long[R][C];
        connected = new HashSet[R][C];
        int sr = 0, sc = 0, dr = 0, dc = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cnt[i][j] = -1;
                grid[i][j] = in.nextInt();
                if (grid[i][j] == 3) {
                    grid[i][j] = 0;
                    sr = i;
                    sc = j;
                } else if (grid[i][j] == 4) {
                    grid[i][j] = 0;
                    dr = i;
                    dc = j;
                }
            }
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                connected[i][j] = new HashSet<Pair>();
                if (grid[i][j] != 0) continue;
                for (int k = 0; k < R; k++) for (int m = 0; m < C; m++) vis[k][m] = false;
                vis[i][j] = true;
                for (Pair p : dir) dfs(i + p.first, j + p.second, connected[i][j]);
            }
        }
        cnt[sr][sc] = 0;
        ways[sr][sc] = 1;
        int curCnt = 0;
        while (true) {
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (cnt[i][j] == curCnt) {
                        for (Pair p : connected[i][j]) {
                            if (cnt[p.first][p.second] == -1 || cnt[p.first][p.second] == curCnt + 1) {
                                cnt[p.first][p.second] = curCnt + 1;
                                ways[p.first][p.second] += ways[i][j];
                            }
                        }
                    }
                }
            }
            if (ways[dr][dc] > 0) {
                out.println(curCnt);
                out.println(ways[dr][dc]);
                return;
            }
            if (++curCnt > R * C) {
                out.println(-1);
                return;
            }
        }
    }
}
