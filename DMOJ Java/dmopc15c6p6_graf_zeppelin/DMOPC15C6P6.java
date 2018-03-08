import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.BitSet;

public class DMOPC15C6P6 {
    
    private static DMOPC15C6P6 o = new DMOPC15C6P6();
    
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
        int M = in.nextInt();
        int K = in.nextInt();
        BitSet[] adj = new BitSet[N];
        BitSet[] cur = new BitSet[N];
        BitSet[] total = new BitSet[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new BitSet();
            cur[i] = new BitSet();
            total[i] = new BitSet();
        }
        for (int i = 0; i < M; i++) {
            int a = in.nextInt() - 1;
            int b = in.nextInt() - 1;
            adj[a].set(b);
            adj[b].set(a);
            cur[a].set(b);
            cur[b].set(a);
            total[a].set(b);
            total[b].set(a);
        }
        for (int k = 1; k < K; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (cur[i].get(j)) total[i].or(adj[j]);
                }
            }
            for (int i = 0; i < N; i++) {
                cur[i].or(total[i]);
            }
        }
        for (int i = 0; i < N; i++) {
            int count = total[i].cardinality();
            if (!total[i].get(i)) count += 1;
            out.println(count);
        }
        out.close();
    }
}
