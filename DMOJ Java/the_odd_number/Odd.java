package the_odd_number;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Odd {
    static BufferedReader in;
    static PrintWriter out;
    static StringTokenizer st;

    public static void main(String[] args) throws IOException {
        in  = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new OutputStreamWriter(System.out));
        int n = nextInt();
        int odd = 0;
        for (int i = 0; i < n; i++) {
            odd ^= nextInt();
        }
        out.println(odd);
        out.close();
    }
    
    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine().trim());
        } // while
        return st.nextToken();
    } // next method
    
    static long nextLong() throws IOException {
        return Long.parseLong(next());
    } // nextLong method
    
    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    } // nextInt method
    
    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    } // nextDouble method
    
    static String nextLine() throws IOException {
        return in.readLine().trim();
    } // nextLine method
}
