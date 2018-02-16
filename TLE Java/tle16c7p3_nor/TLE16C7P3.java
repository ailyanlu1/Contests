import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class TLE16C7P3 {
    private static TLE16C7P3 o = new TLE16C7P3();
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
        int[] k = new int[N];
        int K = -1;
        for (int i = 0; i < N; i++) {
            int a = in.nextInt();
            if (a == 1) K = i;
            k[i] = K;
        }
        int Q = in.nextInt();
        for (int i = 0; i < Q; i++) {
            int x = in.nextInt() - 1;
            int y = in.nextInt() - 1;
            if (k[y] == x) {
                if ((y - x) % 2 == 0) out.println(1);
                else out.println(0);
            } else if (k[y] < x) {
                if ((y - x - 1) % 2 == 0) out.println(1);
                else out.println(0);
            } else /*if (k[y] > x)*/{
                if ((y - k[y] - 1) % 2 == 0) out.println(1);
                else out.println(0);
            }
        }
        out.close();
    }
}
