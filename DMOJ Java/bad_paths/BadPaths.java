package bad_paths;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class BadPaths {
    private static BadPaths o = new BadPaths();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;
        
        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        } // Reader InputStream constructor
        
        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        } // Reader String constructor

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            } // while
            return st.nextToken();
        } // next method
        
        public long nextLong() throws IOException {
            return Long.parseLong(next());
        } // nextLong method
        
        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        } // nextInt method
        
        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        } // nextDouble method
        
        public String nextLine() throws IOException {
            return in.readLine().trim();
        } // nextLine method
    } // Reader class
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    private static long[] factorial;
    private static long[] prefix;
    private static long MOD = (long) (1e9 + 7);
    
    public static void main(String[] args) throws IOException {
        factorial((long) 1e6, MOD);
        int N = in.nextInt();
        for (int i = 0; i < N; i++) {
            long x = in.nextLong();
            long total = (factorial[(int) x] * prefix[(int) x] - (x + 1)) % MOD;
            long tree = (x * (x - 1)) % MOD;
            long ans = divMod(((total - tree) % MOD + MOD) % MOD, 2, MOD);
            out.println(ans);
        }
        out.close();
    }
    
    public static void factorial(long n, long mod) {
        factorial = new long[(int) (n + 1)];
        prefix = new long[(int) (n + 1)];
        factorial[0] = 1;
        prefix[0] = 1;
        for (int i = 1; i <= n; i++) {
            factorial[i] = (factorial[i - 1] * i) % mod;
            prefix[i] = (prefix[i - 1] + divMod(1, factorial[i], MOD)) % MOD;
        }
    }
    
    public static long pow(long base, long pow, long mod) {
        if (pow == 0)
            return 1;
        if (pow == 1)
            return base;
        if (pow % 2 == 0)
            return pow(base * base % mod, pow / 2, mod);
        return base * pow(base * base % mod, pow / 2, mod) % mod;
    }
    
    public static long divMod(long i, long j, long p) {
        return i * pow(j, p - 2, p) % p;
    }
}
