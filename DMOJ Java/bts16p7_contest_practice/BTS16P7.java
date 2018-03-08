import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class BTS16P7 {
    private static BTS16P7 o = new BTS16P7();
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
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int P = in.nextInt();
        int Q = in.nextInt();
        int N = in.nextInt();
        int[] pow = new int[P + 1];
        pow[0] = 1;
        for (int i = 1; i <= P; i++) {
            pow[i] = pow[i - 1] * Q;
        }
        int[] ind = new int[pow[P]];
        for (int i = 0; i < N; i++) {
            int x = 0;
            for (int j = 0; j < P; j++) {
                x += (Q - in.nextInt() - 1) * pow[j];
            }
            ind[x]++;
        }
        for (int i = 0; i <= P; i++) {
            for (int j = 0; j < pow[P]; j++) {
                if ((j / pow[i]) % Q != 0) ind[j] += ind[j - pow[i]];
            }
        }
        int X = in.nextInt();
        for (int i = 0; i < X; i++) {
            int x = 0;
            for (int j = 0; j < P; j++) {
                x += (Q - in.nextInt() - 1) * pow[j];
            }
            out.println(ind[x]);
        }
        out.close();
    }
}
