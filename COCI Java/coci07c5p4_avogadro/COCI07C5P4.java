import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Stack;
import java.util.StringTokenizer;

public class COCI07C5P4 {
    private static COCI07C5P4 o = new COCI07C5P4();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken();
        }

        public String next(String delim) throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken(delim);
        }

        /*
        public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }
        */

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public byte nextByte(String delim) throws IOException {
            return Byte.parseByte(next(delim));
        }

        public char nextChar() throws IOException {
            return next().charAt(0);
        }

        public char nextChar(String delim) throws IOException {
            return next(delim).charAt(0);
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public double nextDouble(String delim) throws IOException {
            return Double.parseDouble(next(delim));
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }

        public float nextFloat(String delim) throws IOException {
            return Float.parseFloat(next(delim));
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public int nextInt(String delim) throws IOException {
            return Integer.parseInt(next(delim));
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public long nextLong(String delim) throws IOException {
            return Long.parseLong(next(delim));
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public short nextShort(String delim) throws IOException {
            return Short.parseShort(next(delim));
        }

        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }
    } // Reader class
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int[][] arr = new int[3][N];
        int[][] freq = new int[3][N];
        boolean[] del = new boolean[N];
        ArrayList<Integer>[] col = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            col[i] = new ArrayList<Integer>();
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < N; j++) {
                arr[i][j] = in.nextInt() - 1;
                col[arr[i][j]].add(j);
                freq[i][arr[i][j]]++;
            }
        }
        Stack<Integer> s = new Stack<Integer>();
        for (int i = 0; i < N; i++) {
            if (freq[1][i] == 0 || freq[2][i] == 0) {
                s.push(i);
            }
        }
        int ans = 0;
        while (!s.isEmpty()) {
            int i = s.pop();
            for (int j: col[i]) {
                if (del[j]) continue;
                del[j] = true;
                ans++;
                if (--freq[0][arr[0][j]] == 0) s.push(arr[0][j]);
                if (--freq[1][arr[1][j]] == 0) s.push(arr[1][j]);
                if (--freq[2][arr[2][j]] == 0) s.push(arr[2][j]);
            }
        }
        out.println(ans);
        out.close();
    }
}
