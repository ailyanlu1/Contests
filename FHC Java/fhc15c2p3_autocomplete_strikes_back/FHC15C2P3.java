package fhc15c2p3_autocomplete_strikes_back;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class FHC15C2P3 {
    private static FHC15C2P3 o = new FHC15C2P3();
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
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "autocomplete_strikes_back.txt";
    private static final String OUTPUT_FILE_NAME = "autocomplete_strikes_back.out";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    
    public static void main(String[] args) throws IOException {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = o.new Reader(System.in);
        else in = o.new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
        int T = in.nextInt();
        for (int i = 1; i <= T; i++) {
            run(i);
            out.flush();
        }
        out.close();
    }
    
    private static int N, K;
    private static int[][] w;
    private static int[][] dp;
    private static int[] c;
    private static final int MAXLEN = 20000;
    private static final int INT_INF = 0x3f3f3f;
    
    public static void run(int testCaseNum) throws IOException {
        N = in.nextInt();
        K = in.nextInt();
        w = new int[MAXLEN][26];
        dp = new int[MAXLEN][K + 1];
        for (int i = 0; i < MAXLEN; i++) {
            for (int j = 0; j <= K; j++) {
                dp[i][j] = INT_INF;
            }
        }
        c = new int[MAXLEN];
        int x = 0;
        for (int i = 0; i < N; i++) {
            String word = in.next();
            int p = 0;
            for (int j = 0; j < word.length(); j++) {
                int ch = word.charAt(j) - 'a';
                if (w[p][ch] == 0) {
                    w[p][ch] = ++x;
                }
                p = w[p][ch];
            }
            c[p]++;
        }
        dfs(0);
        out.println("Case #" + testCaseNum + ": " + dp[0][K]);
    }
    
    private static void dfs(int x) {
        dp[x][0] = 0;
        if (c[x] == 1) {
            dp[x][1] = 0;
        }
        for (int i = 0; i < 26; i++) {
            if (w[x][i] != 0) {
                int[] temp = new int[K + 1];
                for (int j = 0; j <= K; j++) {
                    temp[j] = INT_INF;
                }
                dfs(w[x][i]);
                for (int j = 0; j <= K; j++) {
                    for (int k = j; k <= K; k++) {
                        temp[k] = Math.min(temp[k], dp[x][k - j] + dp[w[x][i]][j] + j);
                    }
                }
                for (int j = 0; j <= K; j++) {
                    dp[x][j] = temp[j];
                }
            }
        }
        dp[x][1] = 0;
    }
}
