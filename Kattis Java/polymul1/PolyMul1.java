// https://open.kattis.com/problems/polymul1
import java.io.*;
import java.math.*;
import java.util.*;

public class PolyMul1 {
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
    
    public static class Complex {
        private double _real;
        private double _imag;

        public Complex(double real, double imag) {
            _real = real;
            _imag = imag;
        }

        public Complex(Complex c) {
            _real = c._real;
            _imag = c._imag;
        }

        public double real() {
            return _real;
        }

        public double imag() {
            return _imag;
        }

        public double norm() {
            return _real * _real + _imag * _imag;
        }

        public double abs() {
            return Math.sqrt(_real * _real + _imag * _imag);
        }

        public Complex conj() {
            return new Complex(_real, -_imag);
        }

        public Complex add(Complex c) {
            return new Complex(_real + c._real, _imag + c._imag);
        }

        public Complex subtract(Complex c) {
            return new Complex(_real - c._real, _imag - c._imag);
        }

        public Complex multiply(double a) {
            return new Complex(a * _real, a * _imag);
        }

        public Complex multiply(Complex c) {
            return new Complex(_real * c._real - _imag * c._imag, _real * c._imag + _imag * c._real);
        }

        public Complex divide(double a) {
            return new Complex(_real / a, _imag / a);
        }

        public Complex divide(Complex c) {
            double normC = c._real * c._real + c._imag * c._imag;
            return new Complex((_real * c._real + _imag * c._imag) / normC, (_imag * c._real - _real * c._imag) / normC);
        }

        @Override
        public int hashCode() {
            return 31 * ((Double) _real).hashCode() + ((Double) _imag).hashCode();
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Complex)) return false;
            Complex c = (Complex) o;
            return _real == c._real && _imag == c._imag;
        }

        @Override
        public String toString() {
            return "(" + _real + ", " + _imag + ")";
        }
    }
    
    static void fft(Complex[] a, boolean invert) {
        int N = a.length;
        for (int i = 1, j = 0; i < N; i++) {
            int bit = N >> 1;
            for (; j >= bit; bit >>= 1) j -= bit;
            j += bit;
            if (i < j) {
                Complex temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        for (int len = 2; len <= N; len <<= 1) {
            double angle = 2 * Math.PI / len * (invert ? -1 : 1);
            Complex wlen = new Complex(Math.cos(angle), Math.sin(angle));
            for (int i = 0; i < N; i += len) {
                Complex w = new Complex(1, 0);
                for (int j = 0; j < len / 2; j++) {
                    Complex u = a[i + j];
                    Complex v = a[i + j + len / 2].multiply(w);
                    a[i + j] = u.add(v);
                    a[i + j + len / 2] = u.subtract(v);
                    w = w.multiply(wlen);
                }
            }
        }
        if (invert) for (int i = 0; i < N; i++) a[i] = a[i].divide(N);
    }
    
    static int[] multiplyPolynomial(int[] a, int[] b) {
        int N = a.length + b.length - 1;
        while ((N & (N - 1)) != 0) N++;
        Complex[] fa = new Complex[N], fb = new Complex[N];
        for (int i = 0; i < a.length; i++) fa[i] = new Complex(a[i], 0);
        for (int i = a.length; i < N; i++) fa[i] = new Complex(0, 0);
        for (int i = 0; i < b.length; i++) fb[i] = new Complex(b[i], 0);
        for (int i = b.length; i < N; i++) fb[i] = new Complex(0, 0);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < N; i++) fa[i] = fa[i].multiply(fb[i]);
        fft(fa, true);
        int[] temp = new int[N];
        for (int i = 0; i < N; i++) temp[i] = (int) Math.round(fa[i].real());
        while (N > 1 && temp[N - 1] == 0) N--;
        int[] res = new int[N];
        for (int i = 0; i < N; i++) res[i] = temp[i];
        return res;
    }
    
    public static void run(int testCaseNum) throws Exception {
        int[] A = new int[in.nextInt() + 1];
        for (int i = 0; i < A.length; i++) A[i] = in.nextInt();
        int[] B = new int[in.nextInt() + 1];
        for (int i = 0; i < B.length; i++) B[i] = in.nextInt();
        int[] res = multiplyPolynomial(A, B);
        out.println(res.length - 1);
        for (int i = 0; i < res.length; i++) {
            if (i > 0) out.print(" ");
            out.print(res[i]);
        }
        out.println();
    }
}
