import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class ECOO17R2P3_Binary_Search {
    private static ECOO17R2P3_Binary_Search o = new ECOO17R2P3_Binary_Search();
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
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run();
        } // for i
        out.close();
    } // main method
    
    public static void run() throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        long K = in.nextLong();
        int[] arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = in.nextInt();
        }
        long lo = Integer.MIN_VALUE;
        long hi = Integer.MAX_VALUE;
        while (lo <= hi) {
            long mid = lo + (hi - lo) / 2;
            long drops = 0;
            long exacts = 0;
            for (int i = 0; i < N; i++) {
                if (arr[i] >= mid) {
                    if ((arr[i] - mid) % M == 0) {
                        drops += (arr[i] - mid) / M;
                        exacts++;
                    } else {
                        drops += (arr[i] - mid) / M + 1;
                    }
                }
                if (drops >= K) break;
            }
            if (drops >= K) {
                lo = mid + 1;
            } else if (drops + exacts < K) {
                hi = mid - 1;
            } else {
                int x = (int) (K - drops);
                for (int i = 0; i < N; i++) {
                    if (arr[i] >= mid && (arr[i] - mid) % M == 0) {
                        x--;
                        if (x == 0) {
                            out.println(i + 1);
                            return;
                        }
                    }
                }
            }
        }
    }
} // QuestionThree class