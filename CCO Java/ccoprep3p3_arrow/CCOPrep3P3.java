package ccoprep3p3_arrow;

import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;

public class CCOPrep3P3 {
    private static CCOPrep3P3 o = new CCOPrep3P3();
    public class DataInputStreamReader {
        private final int BUFFER_SIZE = 1 << 16;
        private int MAX_LENGTH = 64;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public DataInputStreamReader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public DataInputStreamReader(InputStream inputStream, int length) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
            MAX_LENGTH = length;
        }

        public DataInputStreamReader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public DataInputStreamReader(String file_name, int length) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
            MAX_LENGTH = length;
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[MAX_LENGTH];
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n' || c == '\r') break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
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
            while (c <= ' ')
                c = read();
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
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg) c = read();

            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg) return -ret;
            return ret;
        }
        
        public char nextChar() throws IOException {
            int c = read();
            while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) {
                c = read();
            }
            return (char) c;
        }
        
        public String next() throws IOException {
            byte[] buf = new byte[MAX_LENGTH];
            int cnt = 0, c;
            c = read();
            while(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) {
                c = read();
            }
            buf[cnt++] = (byte) c;
            while ((c = read()) != -1) {
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
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

    private static class Vector {
        public double x, y;

        public Vector(double x, double y) {
            this.x = x;
            this.y = y;
        }

        // plus
        public Vector plus(Vector v) {
            return new Vector(x + v.x, y + v.y);
        }

        // minus
        public Vector minus(Vector v) {
            return new Vector(x - v.x, y - v.y);
        }

        // scale / times
        public Vector scale(double a) {
            return new Vector(x * a, y * a);
        }

        // dot
        public double dot(Vector v) {
            return x * v.x + y * v.y;
        }

        // cross 2D
        public double cross2D(Vector v) {
            return x * v.y - y * v.x;
        }
        
        public double angle() {
            return Math.atan2(y, x);
        }
    }
    
    private static final double EPS = 1e-15;
    private static Line[] all;
    private static Line[] L;
    
    private static class Line implements Comparable<Line> {
        public Vector a, b;
        public double rad;
        public Line(Vector a, Vector b) {
            this.a = a;
            this.b = b;
            this.rad = b.angle();
        }
        
        public boolean onLeft(Vector v) {
            return this.b.cross2D(v.minus(this.a)) > EPS;
        }
        
        @Override
        public int compareTo(Line l) {
            if (rad < l.rad) return -1;
            else if (rad > l.rad) return 1;
            return 0;
        }
    }
    
    
    private static boolean check(int n) {
        L = new Line[n * 2];
        for (int i = 0; i < n * 2; i++) {
            L[i] = all[i];
        }
        return halfPlaneIntersection(n * 2);
    }
    
    private static Vector getLineIntersection(Line la, Line lb) {
        double t = (lb.b.cross2D(la.a.minus(lb.a))) / la.b.cross2D(lb.b);
        return la.a.plus(la.b.scale(t));
    }
    
    private static boolean halfPlaneIntersection(int n) {
        Vector[] v = new Vector[n];
        Line[] q = new Line[n];
        Arrays.sort(L);
        int front = 0;
        int back = 0;
        q[0] = L[0];
        for (int i = 1; i < n; i++) {
            while (front < back && !L[i].onLeft(v[back - 1])) back--;
            while (front < back && !L[i].onLeft(v[front])) front++;
            if (Math.abs(q[back].b.cross2D(L[i].b)) < EPS) {
                if (q[back].onLeft(L[i].a)) q[back] = L[i];
            } else {
                q[++back] = L[i];
            }
            if (front < back) v[back - 1] = getLineIntersection(q[back - 1], q[back]);
        }
        while (front < back && !q[front].onLeft(v[back - 1])) back--;
        return (back - front) > 1;
    }
    
    private static DataInputStreamReader in = o.new DataInputStreamReader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        all = new Line[N * 2];
        for (int i = 0; i < N; i++) {
            int x = in.nextInt();
            int y1 = in.nextInt();
            int y2 = in.nextInt();
            all[i * 2] = new Line(new Vector(0, (double) y2 / x), new Vector(-1.0 / x, 1.0));
            all[i * 2 + 1] = new Line(new Vector(0, (double) y1 / x), new Vector(1.0 / x, -1.0));
        }
        int l = 1;
        int r = N;
        int count = 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                count = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        out.println(count);
        out.close();
    }
}
