import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class DS2 {
    private static DS2 o = new DS2();
    
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
    
    private static int components;
    private static int[] parent;
    private static int[] rank;
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        components = n;
        parent = new int[n+1];
        rank = new int[n+1];
        int count = 0;
        for (int i = 1; i <= n; i++){
            parent[i] = i;
        }
        ArrayList<Integer> list = new ArrayList<Integer>();
        for (int i = 1; i <= m; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                list.add(i);
                count++;
                union(u, v);
                if (count == n-1) break;
            }
        }
        if (components > 1) {
            System.out.println("Disconnected Graph");
        } else {
            for (int i: list) {
                System.out.println(i);
            }
        }
    }
    
    public static int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }
    
    public static void union(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        components--;
    }
}
