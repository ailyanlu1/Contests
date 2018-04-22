import java.io.*;
import java.math.*;
import java.util.*;

public class CCC18S3 {
    private static CCC18S3 o = new CCC18S3();
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
    
    static int[][] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        in.setLength(200);
        int N = in.nextInt();
        int M = in.nextInt();
        boolean[][] vis = new boolean[N][M];
        char[][] grid = new char[N][M];
        int[][] dist = new int[N][M];
        int start = 0;
        for (int i = 0; i < N; i++) {
            String s = in.next();
            for (int j = 0; j < M; j++) {
                grid[i][j] = s.charAt(j);
                if (grid[i][j] == 'S') {
                    start = i * M + j;
                    grid[i][j] = '.';
                }
                dist[i][j] = -1;
                vis[i][j] = false;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == 'C') {
                    for (int k = i + 1; k < N; k++) {
                        if (grid[k][j] == 'W') break;
                        if (grid[k][j] == '.') {
                            grid[k][j] = 'X';
                            vis[k][j] = true;
                        }
                    }
                    for (int k = i - 1; k >= 0; k--) {
                        if (grid[k][j] == 'W') break;
                        if (grid[k][j] == '.') {
                            grid[k][j] = 'X';
                            vis[k][j] = true;
                        }
                    }
                    for (int k = j + 1; k < M; k++) {
                        if (grid[i][k] == 'W') break;
                        if (grid[i][k] == '.') {
                            grid[i][k] = 'X';
                            vis[i][k] = true;
                        }
                    }
                    for (int k = j - 1; k >= 0; k--) {
                        if (grid[i][k] == 'W') break;
                        if (grid[i][k] == '.') {
                            grid[i][k] = 'X';
                            vis[i][k] = true;
                        }
                    }
                    vis[i][j] = true;
                } else if (grid[i][j] == 'W') {
                    vis[i][j] = true;
                }
            }
        }
        Queue<Integer> q = new ArrayDeque<Integer>();
        dist[start / M][start % M] = 0;
        vis[start / M][start % M] = true;
        q.offer(start);
        while (!q.isEmpty()) {
            int cur = q.poll();
            if (grid[cur / M][cur % M] == '.') {
                for (int i = 0; i < 4; i++) {
                    int next = cur + dir[i][0] * M + dir[i][1];
                    boolean loop = false;
                    HashSet<Integer> vis2 = new HashSet<Integer>();
                    while (grid[next / M][next % M] != '.') {
                        if (vis2.contains(next)) {
                            loop = true;
                            break;
                        }
                        vis2.add(next);
                        if (grid[next / M][next % M] == 'U') next -= M;
                        else if (grid[next / M][next % M] == 'D') next += M;
                        else if (grid[next / M][next % M] == 'L') next--;
                        else if (grid[next / M][next % M] == 'R') next++;
                    }
                    if (!vis[next / M][next % M] && !loop) {
                        dist[next / M][next % M] = dist[cur / M][cur % M] + 1;
                        vis[next / M][next % M] = true;
                        q.offer(next);
                    }
                }
            }
        }
        grid[start / M][start % M] = 'S';
        for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) if (grid[i][j] == '.' || grid[i][j] == 'X') out.println(dist[i][j]);
    }
}
