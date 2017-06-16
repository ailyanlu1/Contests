package dmopc15c1p5_lelei_and_dragon_scales;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMOPC15C1P5 {
    private static DMOPC15C1P5 o = new DMOPC15C1P5();
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
    
    public class PrefixSumArray2D {
        private int[][] prefixSum;
        
        /**
         * Initializes a prefix sum array for the given {@code array} array.
         * @param array the original array of integers
         */    
        public PrefixSumArray2D(int[][] array) {
            prefixSum = new int[array.length + 1][array[0].length + 1];
            for (int i = 1; i < prefixSum.length; i++) {
                for (int j = 1; j < prefixSum[i].length; j++) {
                    prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + array[i - 1][j - 1];
                }
            }
        }
        
        /**
         * Returns the cumulative sum from index 1, 1 to <em>endX</em>, <em>endY</em>
         * @param endX the 1-based endX index (inclusive)
         * @param endY the 1-based endY index (inclusive
         * @return the cumulative sum
         */
        public int query(int endX, int endY) {
            return prefixSum[endX][endY];
        }
        
        /**
         * Returns the cumulative sum from index <em>startX</em>, <em>startY</em> to <em>endX</em>, <em>endY</em>
         * @param startX the 1-based startX index (inclusive)
         * @param startY the 1-based startY index (inclusive)
         * @param endX the 1-based endX index (inclusive)
         * @param endY the 1-based endY index (inclusive)
         * @return the cumulative sum
         */
        public int query(int startX, int startY, int endX, int endY) {
            if (endX < startX || endY < startY) throw new IllegalArgumentException();
            return query(endX, endY) - query(startX - 1, endY) - query(endX, startY - 1) + query(startX - 1, startY - 1);
        }
    }

    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    private static int W, H, N;
    private static int[][] grid;
    private static PrefixSumArray2D pre;
    
    public static void main(String[] args) throws IOException {
        W = in.nextInt();
        H = in.nextInt();
        N = in.nextInt();
        grid = new int[H][W];
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                grid[i][j] = in.nextInt();
            }
        }
        pre = o.new PrefixSumArray2D(grid);
        int max = 0;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                max = Math.max(max, rectangles(i, j));
            }
        }
        out.println(max);
        out.close();
    }
    
    private static int rectangles(int i, int j) {
        int max = 0;
        for (int r = 1; r <= Math.sqrt(N); r++) {
            int x = Math.min(i + r, H + 1) - 1;
            int y = Math.min(j + N / r, W + 1) - 1;
            max = Math.max(max, pre.query(i, j, x, y));
            x = Math.min(i + N / r, H + 1) - 1;
            y = Math.min(j + r, W + 1) - 1;
            max = Math.max(max, pre.query(i, j, x, y));
        }
        return max;
    }
}
