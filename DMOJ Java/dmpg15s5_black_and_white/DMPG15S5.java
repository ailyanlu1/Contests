package dmpg15s5_black_and_white;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMPG15S5 {
    private static DMPG15S5 o = new DMPG15S5();
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
        int M = in.nextInt();
        boolean[][] board = new boolean[N + 1][N + 1];
        for (int i = 0; i < M; i++) {
            int x = in.nextInt();
            int y = in.nextInt();
            int w = in.nextInt();
            int h = in.nextInt();
            board[x][y] ^= true;
            board[x][y + h] ^= true;
            board[x + w][y] ^= true;
            board[x + w][y + h] ^= true;
        }
        for (int i = 0; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                board[i][j] ^= board[i][j - 1];
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                board[i][j] ^= board[i - 1][j];
            }
        }
        int ans = 0;
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                if (board[i][j]) ans ++;
            }
        }
        out.println(ans);
        out.close();
    }
}
