import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

// https://code.google.com/codejam/contest/dashboard?c=3264486#s=p2&a=0
public class GCJ2017QRC {
    private static GCJ2017QRC o = new GCJ2017QRC();
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
    
    private static Reader in;
    private static PrintWriter out;
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String input = "C-large-practice.in";
    private static final String output = "C-large-practice.out";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    
    public static void main(String[] args) throws IOException {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = o.new Reader(System.in);
        else in = o.new Reader(packageName + input);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + output)));
        
        int T = in.nextInt();
        for (int i = 1; i <= T; i++) {
            run(i);
        }
        out.close();
    }
    
    public static void run(int t) throws IOException {
        long N = in.nextLong();
        long K = in.nextLong();
        long max = N;
        long min = N;
        long pow = 1;
        while (K - pow > 0) {
            max = max / 2;
            min = (min - 1) / 2;
            K -= pow;
            pow <<= 1;
        }
        if (max != min) {
            if (K > (N - pow * (min + 1) + 1) / (max - min)) {
                max = min / 2;
                min = (min - 1) / 2;
            } else {
                min = (max - 1) / 2;
                max = max / 2;
            }
        } else {
            max = max / 2;
            min = (min - 1) / 2;
        }
        out.println("Case #" + t + ": " + max + " " + min);
    }
}
