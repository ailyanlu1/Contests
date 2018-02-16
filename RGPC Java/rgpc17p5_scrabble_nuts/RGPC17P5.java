import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class RGPC17P5 {
    private static RGPC17P5 o = new RGPC17P5();
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
    private static String word1;
    private static String word2;
    private static int N, M;
    
    public static void main(String[] args) throws IOException {
        N = in.nextInt();
        M = in.nextInt();
        word1 = in.next();
        word2 = in.next();
        out.println(minDistance());
        out.close();
    }
    
    public static int minDistance() {
        int[][] dp = new int[2][M + 1];
        
        int ans = 0;
        
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= M; j++) {
                if (i == 0) {
                    dp[i%2][j] = j;
                } else if (j == 0) {
                    dp[i%2][j] = i;
                } else if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i%2][j] = dp[1 - i%2][j - 1];
                } else {
                    int replace = dp[1 - i%2][j - 1] + 1;
                    int insert = dp[1 - i%2][j] + 1;
                    int delete = dp[i%2][j - 1] + 1;
     
                    int min = replace > insert ? insert : replace;
                    min = delete > min ? min : delete;
                    dp[i%2][j] = min;
                }
            }
        }
        for (int i = 1; i < M; i++) {
            ans += dp[N%2][i];
        }
        return ans;
    }
}
