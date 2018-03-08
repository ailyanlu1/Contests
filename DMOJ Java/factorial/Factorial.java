import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Factorial {
    
    private static Factorial o = new Factorial();
    
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
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int N = in.nextInt();
        for (int i = 0; i < N; i++) {
            String str = in.nextLine();
            if (str.length() >= 3) {
                out.println(0);
                continue;
            }
            long n = Long.parseLong(str);
            long ans = 1;
            long mod = 1L << 32;
            for (int j = 2; j <= Math.min(n, 32); j++)
                ans = (ans * j) % mod;
            out.println(ans);
        }
        out.close();
    }
}
