// https://www.spoj.com/problems/INVCNT/
import java.io.*;
import java.math.*;
import java.util.*;

public class INVCNT {
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
        NUM_OF_TEST_CASES = in.nextInt();
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
    
    // merges and counts inversions
    private static long merge(int[] a, int[] aux, int lo, int mid, int hi) {
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }
        long count = 0;
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) { // no inversions if the lower half is completed
                a[k] = aux[j++];
            } else if (j > hi) { // if the upper half is completed, the number of inversions
                                 // is equal to the size of the upper half
                a[k] = aux[i++];
                count += j - (mid + 1);
            } else if (aux[i] <= aux[j]) { // if the lower half element is smaller, the number of inversions
                                           // is equal to the number of elements taken in the upper half
                a[k] = aux[i++];
                count += j - (mid + 1);
            } else {                       // if the upper half element is smaller, the number of inversions
                                           // is equal to the number of elements not taken in the lower half
                a[k] = aux[j++];
                count += mid + 1 - i;
            }
        }
        return count;
    }
    
    private static long countInversions(int[] a, int[] aux, int lo, int hi) {
        if (lo >= hi) return 0; // base case is interval of 1; if lo is greater than or equal to hi,
                                // then the current interval is less than 1
        int mid = lo + (hi - lo) / 2; // to prevent integer overflow
        // recursively divides into 2 subarrays and merges subarrays and counts inversions
        return countInversions(a, aux, lo, mid) + countInversions(a, aux, mid + 1, hi) + merge(a, aux, lo, mid, hi);
    }
    
    /**
     * Counts the number of inversions in an array.
     * 
     * @param a the array
     * @return the number of inversions in {@code a}
     */
    public static long countInversions(int[] a) {
        int[] aux = new int[a.length];
        return countInversions(a, aux, 0, a.length - 1) / 2; // since each inversion is counted twice
    }
    
    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt();
        int[] A = new int[N];
        for (int i = 0; i < N; i++) A[i] = in.nextInt();
        out.println(countInversions(A));
    }
}
