import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;

public class CCO15P5 {
    private static CCO15P5 o = new CCO15P5();
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

    private static int N, D;
    private static int[] pitch, time;
    private static ArrayList<ArrayList<Integer>> states = new ArrayList<ArrayList<Integer>>();
    private static double[][] dp;

    public static void main(String[] args) throws IOException {
        N = in.nextInt();
        D = in.nextInt();
        time = new int[N];
        pitch = new int[N];
        for (int i = 0; i < N; i++) {
            time[i] = in.nextInt();
            pitch[i] = in.nextInt();
        }
        computeStates(0, new ArrayList<Integer>());
        dp = new double[states.size()][N];
        for (int i = 0; i < states.size(); i++) {
            for (int j = 0; j < N; j++) {
                dp[i][j] = -1;
            }
        }
        double ans = 0;
        for (int i = 0; i < states.size(); i++) {
            ans = Math.max(ans, solve(i, 0));
        }
        out.printf("%.2f\n", (ans == Double.POSITIVE_INFINITY) ? 0 : ans);
        out.close();
    }

    private static double solve(int state, int i) {
        if (dp[state][i] != -1) return dp[state][i];
        double ret = 0;
        boolean valid = false;
        for (int j: states.get(state)) {
            if (j == pitch[i]) valid = true;
        }
        if (!valid) return dp[state][i] = 0;
        if (i == N - 1) return dp[state][i] = Double.POSITIVE_INFINITY;
        for (int j = 0; j < states.size(); j++) {
            int cnt = 0;
            for (int k = 0; k < D; k++) {
                if (states.get(state).get(k) != states.get(j).get(k)) cnt++;
            }
            if (cnt == 0) ret = Math.max(ret, solve(j, i + 1));
            else ret = Math.max(ret, Math.min((double) (time[i + 1] - time[i]) / cnt, solve(j, i + 1)));
        }
        return dp[state][i] = ret;
    }

    private static void computeStates(int i, ArrayList<Integer> list) {
        if (i == D) {
            for (int j = 1; j < D; j++) {
                if (list.get(j) <= list.get(j - 1)) return;
            }
            ArrayList<Integer> add = new ArrayList<Integer>();
            add.addAll(list);
            states.add(add);
        } else {
            for (int j = 1; j <= 12; j++) {
                list.add(j);
                computeStates(i + 1, list);
                list.remove(i);
            }
        }
    }
}
