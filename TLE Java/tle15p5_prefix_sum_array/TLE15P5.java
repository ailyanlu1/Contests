import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class TLE15P5 {
    private static TLE15P5 o = new TLE15P5();
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
    
    private static final int MOD = (int)(1e9 + 7);
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int N = in.nextInt();
        long[] arr = new long[N];
        for (int i = 0; i < N; i++) {
            arr[i] = in.nextInt();
        }
        int M = in.nextInt();
        long[] output = new long[N];
        long multiplier = -1L;
        for (int i = 0; i < N; i++) {
            if (multiplier == -1) {
                multiplier = 1;
            } else {
                multiplier = (multiplier * (i + M - 1)) % MOD;
                multiplier = divMod(multiplier, (i));
            }
            for (int j = i; j < N; j++) {
                output[j] = (output[j] + multiplier * arr[j - i]) % MOD;
            }
        }
        for (int i = 0; i < N; i++) {
            out.print(output[i] + " ");
        }
        out.println();
        out.close();
    }
    
    private static long divMod(long i, long j) {
        return i * pow(j, MOD - 2) % MOD;
    }

    private static long pow(long base, long pow) {
        if (pow == 0)
            return 1;
        if (pow == 1)
            return base;
        if (pow % 2 == 0)
            return pow(base * base % MOD, pow / 2);
        return base * pow(base * base % MOD, pow / 2) % MOD;
    }
}
