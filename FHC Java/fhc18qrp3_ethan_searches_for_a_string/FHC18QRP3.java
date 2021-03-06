// https://www.facebook.com/hackercup/problem/1153996538071503/
import java.io.*;
import java.math.*;
import java.util.*;

public class FHC18QRP3 {
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
    private static final String INPUT_FILE_NAME = "ethan_searches_for_a_string.txt";
    private static final String OUTPUT_FILE_NAME = "ethan_searches_for_a_string_out.txt";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    private static boolean crash = true;
    private static boolean flush = false;
    
    public static void main(String[] args) throws Exception {
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME)));
        in.setLength(2005);
        NUM_OF_TEST_CASES = in.nextInt();
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

    static boolean fast = true;

    public static void run(int testCaseNum) throws Exception {
        String S = in.next();
        out.print("Case #" + testCaseNum + ": ");
        if (fast) {
            for (int i = 1; i < S.length() - 1; i++) {
                if (S.charAt(0) == S.charAt(i)) {
                    for (int j = 1; i + j < S.length(); j++) {
                        if (S.charAt(j) != S.charAt(i + j)) {
                            out.println(S.substring(0, i) + S);
                            return;
                        }
                    }
                    out.println("Impossible");
                    return;
                }
            }
            out.println("Impossible");
        } else {
            int[] z = new int[S.length()];
            int l = 0, r = 0;
            if (S.length() > 0) z[0] = S.length();
            for (int i = 1; i < S.length(); i++) {
                if (i > r) {
                    l = r = i;
                    while (r < S.length() && S.charAt(r) == S.charAt(r - l)) r++;
                    r--;
                    z[i] = r - l + 1;
                } else {
                    int j = i - l;
                    if (z[j] < r - i + 1) z[i] = z[j];
                    else {
                        l = i;
                        while (r < S.length() && S.charAt(r) == S.charAt(r - l)) r++;
                        r--;
                        z[i] = r - l + 1;
                    }
                }
            }
            for (int i = 0; i < S.length(); i++) {
                if (z[i] > 0 && i + z[i] < S.length()) {
                    assert(S.charAt(z[i]) != S.charAt(i + z[i]));
                    out.println(S.substring(0, i) + S);
                    return;
                }
            }
            out.println("Impossible");
        }
    }
}
