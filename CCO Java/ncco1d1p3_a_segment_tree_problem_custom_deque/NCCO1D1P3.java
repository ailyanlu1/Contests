import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class NCCO1D1P3 {
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 20;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public int nextUnsignedInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            return ret;
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
    
    private static Reader in = new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static int[] minA, minB, maxA, maxB;
    public static int minFirst, minLast, maxFirst, maxLast;
    
    public static void main(String[] args) throws Exception {
        int N = in.nextUnsignedInt();
        int M = in.nextUnsignedInt();
        int C = in.nextUnsignedInt();
        minA = new int[M];
        minB = new int[M];
        maxA = new int[M];
        maxB = new int[M];
        minFirst = minLast = maxFirst = maxLast = -1;
        boolean ans = false;
        for (int i = 0; i < M - 1; i++) {
            int a = in.nextUnsignedInt();
            while (minFirst != -1 && minB[minLast] >= a) {
                if (minFirst == minLast) minFirst = minLast = -1;
                else if (minLast == 0) minLast = M - 1;
                else minLast--;
            }
            while (maxFirst != -1 && maxB[maxLast] <= a) {
                if (maxFirst == maxLast) maxFirst = maxLast = -1;
                else if (maxLast == 0) maxLast = M - 1;
                else maxLast--;
            }
            if (minFirst == -1) minFirst = minLast = 0;
            else if (minLast == M - 1) minLast = 0;
            else minLast++;
            if (maxFirst == -1) maxFirst = maxLast = 0;
            else if (maxLast == M - 1) maxLast = 0;
            else maxLast++;
            minA[minLast] = maxA[maxLast] = i;
            minB[minLast] = maxB[maxLast] = a;
        }
        for (int i = M - 1; i < N; i++) {
            int a = in.nextUnsignedInt();
            while (minFirst != -1 && minA[minFirst] <= i - M) {
                if (minFirst == minLast) minFirst = minLast = -1;
                else if (minFirst == M - 1) minFirst = 0;
                else minFirst++;
            }
            while (maxFirst != -1 && maxA[maxFirst] <= i - M) {
                if (maxFirst == maxLast) maxFirst = maxLast = -1;
                else if (maxFirst == M - 1) maxFirst = 0;
                else maxFirst++;
            }
            while (minFirst != -1 && minB[minLast] >= a) {
                if (minFirst == minLast) minFirst = minLast = -1;
                else if (minLast == 0) minLast = M - 1;
                else minLast--;
            }
            while (maxFirst != -1 && maxB[maxLast] <= a) {
                if (maxFirst == maxLast) maxFirst = maxLast = -1;
                else if (maxLast == 0) maxLast = M - 1;
                else maxLast--;
            }
            if (minFirst == -1) minFirst = minLast = 0;
            else if (minLast == M - 1) minLast = 0;
            else minLast++;
            if (maxFirst == -1) maxFirst = maxLast = 0;
            else if (maxLast == M - 1) maxLast = 0;
            else maxLast++;
            minA[minLast] = maxA[maxLast] = i;
            minB[minLast] = maxB[maxLast] = a;
            if (maxB[maxFirst] - minB[minFirst] <= C) {
                ans = true;
                out.println(i - M + 2);
            }
        }
        if (!ans) out.println("NONE");
        out.close();
    }
}
