import java.io.*;
import java.math.*;
import java.util.*;

public class HopScotch2 {
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
    
    public static class Writer {
        private final static int BUFFER_SIZE = 1 << 12;
        private final static int MAX_NUM_LENGTH = 1 << 7;
        private DataOutputStream dout;
        private byte[] buffer, numBuffer, tempBuffer;
        private int bufferPointer, numBufferPointer, tempBufferPointer, width, precision;
        private long precisionBase;
        private char fill;

        public Writer(OutputStream outputStream) {
            dout = new DataOutputStream(outputStream);
            buffer = new byte[BUFFER_SIZE];
            numBuffer = new byte[MAX_NUM_LENGTH];
            tempBuffer = new byte[MAX_NUM_LENGTH];
            bufferPointer = numBufferPointer = tempBufferPointer = 0;
            setWidth(0);
            setPrecision(6);
            setFill(' ');
        }

        public Writer(String file_name) throws IOException {
            dout = new DataOutputStream(new FileOutputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            numBuffer = new byte[MAX_NUM_LENGTH];
            tempBuffer = new byte[MAX_NUM_LENGTH];
            bufferPointer = numBufferPointer = tempBufferPointer = 0;
            setWidth(0);
            setPrecision(6);
            setFill(' ');
        }

        public void setWidth(int x) {
            width = x;
        }

        public void setPrecision(int x) {
            precision = x;
            precisionBase = 1;
            for (int i = 0; i < precision; i++) precisionBase *= 10;
        }

        public void setFill(char x) {
            fill = x;
        }

        public void print(boolean x) throws IOException {
            if (x) println("true");
            else println("false");
        }

        public void println(boolean x) throws IOException {
            print(x);
            write((byte) '\n');
        }


        public void print(char x) throws IOException {
            writeTempBuffer((byte) x);
            flushTempBuffer();
        }

        public void println(char x) throws IOException {
            print(x);
            write((byte) '\n');
        }

        public void print(int x) throws IOException {
            if (x < 0) {
                writeTempBuffer((byte) '-');
                x = -x;
            }
            int cnt = 0;
            for (; x > 0; x /= 10, cnt++) numBuffer[numBufferPointer++] = (byte) ('0' + x % 10);
            for (; cnt < 1; cnt++) numBuffer[numBufferPointer++] = (byte) '0';
            flushNumBuffer();
            flushTempBuffer();
        }

        public void println(int x) throws IOException {
            print(x);
            write((byte) '\n');
        }

        public void print(long x) throws IOException {
            if (x < 0) {
                writeTempBuffer((byte) '-');
                x = -x;
            }
            int cnt = 0;
            for (; x > 0; x /= 10, cnt++) numBuffer[numBufferPointer++] = (byte) ('0' + x % 10);
            for (; cnt < 1; cnt++) numBuffer[numBufferPointer++] = (byte) '0';
            flushNumBuffer();
            flushTempBuffer();
        }

        public void println(long x) throws IOException {
            print(x);
            write((byte) '\n');
        }

        public void print(double x) throws IOException {
            if (Double.isInfinite(x)) {
                println("Inf");
            } else if (Double.isNaN(x)) {
                println("NaN");
            } else {
                if (x < 0) {
                    writeTempBuffer((byte) '-');
                    x = -x;
                }
                long I = (long) x;
                long F = (long) ((x - I) * precisionBase + 0.5);
                if (F >= precisionBase) {
                    I++;
                    F = 0;
                }
                int cnt = 0;
                for (; I > 0; I /= 10, cnt++) numBuffer[numBufferPointer++] = (byte) ('0' + I % 10);
                for (; cnt < 1; cnt++) numBuffer[numBufferPointer++] = (byte) '0';
                flushNumBuffer();
                writeTempBuffer((byte) '.');
                cnt = 0;
                for (; F > 0; F /= 10, cnt++) numBuffer[numBufferPointer++] = (byte) ('0' + F % 10);
                for (; cnt < precision; cnt++) numBuffer[numBufferPointer++] = (byte) '0';
                flushNumBuffer();
                flushTempBuffer();
            }
        }

        public void println() throws IOException {
            write((byte) '\n');
        }

        public void println(double x) throws IOException {
            print(x);
            write((byte) '\n');
        }

        public void print(String x) throws IOException {
            fillBuffer(width - x.length());
            for (int i = 0; i < x.length(); i++) write((byte) x.charAt(i));
            fillBuffer(-width - x.length());
        }


        public void println(String x) throws IOException {
            print(x);
            write((byte) '\n');
        }

        public void flush() throws IOException {
            flushBuffer();
            dout.flush();
        }

        private void flushBuffer() throws IOException {
            dout.write(buffer, 0, bufferPointer);
            bufferPointer = 0;
        }

        private void flushNumBuffer() throws IOException {
            for (; numBufferPointer > 0; writeTempBuffer(numBuffer[--numBufferPointer]));
        }

        private void flushTempBuffer() throws IOException {
            int tempLen = tempBufferPointer;
            fillBuffer(width - tempLen);
            writeOutput();
            fillBuffer(-width - tempLen);
        }

        private void fillBuffer(int x) throws IOException {
            for (int i = 0; i < x; i++) write((byte) fill);
        }

        private void write(byte x) throws IOException {
            if (bufferPointer == buffer.length - 1) flushBuffer();
            buffer[bufferPointer++] = x;
        }

        private void writeTempBuffer(byte x) throws IOException {
            tempBuffer[tempBufferPointer++] = x;
        }

        private void writeOutput() throws IOException {
            for (int i = 0; i < tempBufferPointer; i++) write(tempBuffer[i]);
            tempBufferPointer = 0;
        }

        private void close() throws IOException {
            flush();
            dout.close();
        }
    }
    
    private static Reader in;
    private static Writer out;
    
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
        if (stdOut) out = new Writer(System.out);
        else out = new Writer(OUTPUT_FILE_NAME);
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
    
    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt(), K = in.nextInt();
        long[] A = new long[N + 1];
        int[] ind = new int[N + 1];
        int[] dq = new int[N + 1];
        int front = 0, back = -1;
        A[0] = 0;
        dq[++back] = 0;
        for (int i = 1; i <= N; i++) {
            long ni = in.nextLong();
            while (front <= back && dq[front] < i - K) front++;
            A[i] = A[dq[front]] + ni;
            ind[i] = dq[front];
            while (front <= back && A[dq[back]] >= A[i]) back--;
            dq[++back] = i;
        }
        int cur = 0;
        long ans = Long.MAX_VALUE;
        for (int i = N - K + 1; i <= N; i++) {
            if (A[i] <= ans) {
                ans = A[i];
                cur = i;
            }
        }
        out.println(ans);
        int[] steps = new int[N + 1];
        int len = 0;
        for (; cur != 0; cur = ind[cur]) steps[len++] = cur;
        for (int i = len - 1; i >= 0; i--) {
            out.print(steps[i]);
            if (i > 0) out.print(' ');
        }
        out.println();
    }
}
