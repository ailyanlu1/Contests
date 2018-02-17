import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class COCI14C3P5 {
    private static COCI14C3P5 o = new COCI14C3P5();
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
    
    private static DataInputStreamReader in = o.new DataInputStreamReader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static int N, LG, depth[], parent[][];
    
    public static void main(String[] args) throws IOException {
        N = in.nextInt();
        LG = (int) (Math.ceil(Math.log(N + 1) / Math.log(2)) + 1);
        parent = new int[N + 1][LG];
        depth = new int[N + 1];
        int[] stack = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            char c = in.nextChar();
            if (c == 'a') {
                int v = stack[in.nextInt()];
                stack[i] = i;
                depth[i] = depth[v] + 1;
                parent[i][0] = v;
                for (int j = 1; j < LG; j++) {
                    parent[i][j] = parent[parent[i][j - 1]][j - 1];
                }
            } else if (c == 'b') {
                int v = stack[in.nextInt()];
                stack[i] = parent[v][0];
                out.println(v);
            } else if (c == 'c') {
                int v = stack[in.nextInt()];
                int w = stack[in.nextInt()];
                stack[i] = v;
                out.println(depth[lca(v, w)]);
            } else {
                i--;
            }
        }
        out.close();
    }
    
    private static int lca(int v, int w) {
        if (depth[v] < depth[w]) {
            int temp = v;
            v = w;
            w = temp;
        }
        for (int j = LG - 1; j >= 0; j--) {
            if (depth[parent[v][j]] >= depth[w]) {
                v = parent[v][j];
            }
        }
        if (v == w) return v;
        for (int j = LG - 1; j >= 0; j--) {
            if (parent[v][j] != parent[w][j]) {
                v = parent[v][j];
                w = parent[w][j];
            }
        }
        return parent[v][0];
    }
}
