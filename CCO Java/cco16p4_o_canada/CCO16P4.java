import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

public class CCO16P4 {
    private static CCO16P4 o = new CCO16P4();
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
        int G = in.nextInt();
        boolean[][] grid;
        HashMap<Integer, Integer> occ = new HashMap<Integer, Integer>();
        for (int g = 0; g < G; g++) {
            grid = new boolean[N][N];
            for (int i = 0; i < N; i++) {
                String line = in.nextLine();
                for (int j = 0; j < N; j++) {
                    grid[i][j] = (line.charAt(j) == 'R');
                }
            }
            for (int i = 0; i < N - 1; i++) {
                for (int j = 0; j < N - 1; j++) {
                    if (grid[i][j]) {
                        grid[i][j] ^= true;
                        grid[i][j + 1] ^= true;
                        grid[i + 1][j] ^= true;
                        grid[i + 1][j + 1] ^= true;
                    }
                }
            }
            int res = 0;
            for (int i = 0; i < N; i++) {
                if (grid[N - 1][i]) res += (1 << i);
                if (grid[i][N - 1]) res += (1 << (i + N));
            }
            if (occ.get(res) == null) occ.put(res, 1);
            else occ.put(res, occ.get(res) + 1);
        }
        int ans = 0;
        for (Integer key: occ.keySet()) {
            ans += occ.get(key) * (occ.get(key) - 1) / 2;
        }
        out.println(ans);
        out.close();
    }
}
