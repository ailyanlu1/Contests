package primefactorization;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class PrimeFactorization {
    private static PrimeFactorization o = new PrimeFactorization();
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
        int N = in.nextInt();
        for (int i = 0; i < N; i++) {
            ArrayList<Integer> factors = factor(in.nextInt());
            for (int factor: factors) {
                out.print(factor + " ");
            }
            out.println();
        }
        out.close();
    }
    
    private static ArrayList<Integer> factor(int M) {
        int x = M;
        ArrayList<Integer> factors = new ArrayList<Integer>();
        boolean prime = true;
        for (int i = 2; i <= Math.sqrt(M); i++) {
            prime = true;
            if (x % i == 0) {
                factors.add(i);
                x /= i;
                i--;
                prime = false;
            }
        }
        if (prime && x != 1) factors.add(x);
        return factors;
    }
}
