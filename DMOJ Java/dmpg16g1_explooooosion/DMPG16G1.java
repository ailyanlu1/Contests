package dmpg16g1_explooooosion;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMPG16G1 {
    private static DMPG16G1 o = new DMPG16G1();
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
    
    private static final int mod = 1000000007;
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int N = in.nextInt();
        int[] p = new int[1002];
        for (int i = 0; i < N; i++) {
            p[in.nextInt()]++;
        }
        long min = 0;
        for (int i = 2; i < p.length; i++) {
            min = (min + (p[i] * i) % mod) % mod;
        }
        if (min == 0) out.println(1);
        else out.println(min);
        ////////////////////////////////////////
        long max = 1;
        int comb = Math.min(p[1], p[2]);
        p[3] += comb;
        p[2] -= comb;
        p[1] -= comb;
        
        comb = p[1] / 3;
        p[3] += comb;
        p[1] -= comb * 3;
        
        comb = p[1] / 2;
        p[2] += comb;
        p[1] -= comb * 2;
        
        if (p[1] == 1) {
            for (int i = 2; i < p.length - 1; i++) {
                if (p[i] > 0) {
                    p[i + 1] ++;
                    p[i] --;
                    break;
                }
            }
        }
        
        for (int i = 2; i < p.length; i++) {
            max = (max * pow(i, p[i])) % mod;
        }
        out.println(max);
        out.close();
    }
    
    private static long pow (long base, long pow) {
        if (pow == 0)
            return 1;
        if (pow == 1)
            return base;
        if (pow % 2 == 0)
            return pow(base * base % mod, pow / 2);
        return base * pow(base * base % mod, pow / 2) % mod;
    }
}
