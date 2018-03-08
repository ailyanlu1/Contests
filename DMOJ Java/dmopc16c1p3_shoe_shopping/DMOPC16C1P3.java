import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMOPC16C1P3 {
    private static DMOPC16C1P3 o = new DMOPC16C1P3();
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
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int[] s = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            s[i] = in.nextInt();
        }
        double[] dp = new double[N + 1];
        for (int i = 1; i <= N; i++) {
            dp[i] = dp[i - 1] + s[i];
            if (i >= 2) dp[i] = Math.min(dp[i], dp[i - 2] + s[i - 1] + s[i] - Math.min(s[i - 1], s[i]) * 0.5);
            if (i >= 3) dp[i] = Math.min(dp[i], dp[i - 3] + s[i - 2] + s[i - 1] + s[i] - Math.min(s[i - 2], Math.min(s[i - 1], s[i])));
        }
        out.printf("%.1f", dp[N]);
        out.close();
    }
}
