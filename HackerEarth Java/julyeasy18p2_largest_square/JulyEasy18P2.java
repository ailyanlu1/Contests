// https://www.hackerearth.com/practice/data-structures/arrays/multi-dimensional/practice-problems/algorithm/largest-square-3d7a938a/
import java.io.*;
import java.math.*;
import java.util.*;
 
public class JulyEasy18P2 {
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
    
    static long MAXXY = (long) 1e9 + 5;
        
    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt();
        long[] X = new long[N];
        long[] Y = new long[N];
        HashSet<Long> hs = new HashSet<Long>();
        for (int i = 0; i < N; i++) {
            X[i] = in.nextLong();
            Y[i] = in.nextLong();
            hs.add(X[i] * MAXXY + Y[i]);
        }
        long bestArea = 0, bestX = Long.MAX_VALUE, bestY = Long.MAX_VALUE;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (X[i] == X[j] && Y[i] != Y[j]) {
                    long s = Math.abs(Y[i] - Y[j]);
                    if (hs.contains((X[i] + s) * MAXXY + Y[i]) && hs.contains((X[j] + s) * MAXXY + Y[j])) {
                        if (s * s > bestArea) {
                            bestArea = s * s;
                            bestX = X[i];
                            bestY = Math.min(Y[i], Y[j]);
                        } else if (s * s == bestArea) {
                            long minY = Math.min(Y[i], Y[j]);
                            if (minY < bestY) {
                                bestY = minY;
                                bestX = X[i];
                            } else if (minY == bestY) {
                                bestX = Math.min(bestX, X[i]);
                            }
                        }
                    }
                    if (hs.contains((X[i] - s) * MAXXY + Y[i]) && hs.contains((X[j] - s) * MAXXY + Y[j])) {
                        if (s * s > bestArea) {
                            bestArea = s * s;
                            bestX = X[i] - s;
                            bestY = Math.min(Y[i], Y[j]);
                        } else if (s * s == bestArea) {
                            long minY = Math.min(Y[i], Y[j]);
                            if (minY < bestY) {
                                bestY = minY;
                                bestX = X[i] - s;
                            } else if (minY == bestY) {
                                bestX = Math.min(bestX, X[i] - s);
                            }
                        }
                    }
                }
                if (Y[i] == Y[j] && X[i] != X[j]) {
                    long s = Math.abs(X[i] - X[j]);
                    if (hs.contains(X[i] * MAXXY + Y[i] + s) && hs.contains(X[j] * MAXXY + Y[j] + s)) {
                        if (s * s > bestArea) {
                            bestArea = s * s;
                            bestX = Math.min(X[i], X[j]);
                            bestY = Y[i];
                        } else if (s * s == bestArea) {
                            if (Y[i] < bestY) {
                                bestY = Y[i];
                                bestX = Math.min(X[i], X[j]);
                            } else if (Y[i] == bestY) {
                                bestX = Math.min(bestX, Math.min(X[i], X[j]));
                            }
                        }
                    }
                    if (hs.contains(X[i] * MAXXY + Y[i] - s) && hs.contains(X[j] * MAXXY + Y[j] - s)) {
                        if (s * s > bestArea) {
                            bestArea = s * s;
                            bestX = Math.min(X[i], X[j]);
                            bestY = Y[i] - s;
                        } else if (s * s == bestArea) {
                            if (Y[i] - s < bestY) {
                                bestY = Y[i] - s;
                                bestX = Math.min(X[i], X[j]);
                            } else if (Y[i] - s == bestY) {
                                bestX = Math.min(bestX, Math.min(X[i], X[j]));
                            }
                        }
                    }
                }
            }
        }
        if (bestX == Long.MAX_VALUE) out.println(-1);
        else out.println(bestX + " " + bestY);
    }
}
