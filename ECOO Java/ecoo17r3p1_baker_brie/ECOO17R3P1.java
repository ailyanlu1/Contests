package ecoo17r3p1_baker_brie;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class ECOO17R3P1 {
    private static ECOO17R3P1 o = new ECOO17R3P1();
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
    private static final int NUM_OF_TEST_CASES = 10;
    
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) run();
        out.close();
    }
    
    public static void run() throws IOException {
        int F = in.nextInt();
        int D = in.nextInt();
        int[] Fs = new int[F];
        int count = 0;
        for (int d = 0; d < D; d++) {
            int sum = 0;
            for (int f = 0; f < F; f++) {
                int g = in.nextInt();
                Fs[f] += g;
                sum += g;
            }
            if (sum % 13 == 0) count += sum / 13;
        }
        for (int i = 0; i < F; i++) {
            if (Fs[i] % 13 == 0) count += Fs[i] / 13;
        }
        out.println(count);
    }
}
