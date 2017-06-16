package ccoqr16p3_data_structure;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class CCOQR16P3 {
    private static CCOQR16P3 o = new CCOQR16P3();
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
    
    public static class Block implements Comparable<Block> {
        public int r;
        public int c;
        
        public Block(int r, int c) {
            this.r = r;
            this.c = c;
        }
        
        @Override
        public int compareTo(Block b) {
            return c - b.c;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        Block[] data = new Block[M];
        for (int i = 0; i < M; i++) {
            data[i] = new Block(in.nextInt(), in.nextInt());
        }
        Arrays.sort(data);
        
        long ans = 0;
        long height = 0;
        for (int i = 0; i < M; i++) {
            long length = 0;
            if (i > 0) length = Math.min(height, data[i].c - data[i - 1].c);
            else length = Math.min(height, data[i].c);
            ans += (length) * (length + 1) / 2 + Math.max(0, length * (height - length));
            height = Math.max(height - length, N - data[i].r + 1);
        }
        long length = Math.min(height, N - data[M - 1].c + 1);
        ans += (length) * (length + 1) / 2 + Math.max(0, length * (height - length));
        out.println(ans);
        out.close();
    }
}
