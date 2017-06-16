package ecoo17r2p1_wizards_windows;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.StringTokenizer;

public class ECOO17R2P1 {
    private static ECOO17R2P1 o = new ECOO17R2P1();
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
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) throws IOException {
        Reader f = o.new Reader(System.in);
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(f);
        } // for i
    } // main method
    
    public static void run(Reader f) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
        int N = f.nextInt();
        int M = f.nextInt();
        HashMap<String, String> rules = new HashMap<String, String>();
        for (int i = 0; i < 4; i++) {
            rules.put(f.next(), f.next());
        }
        char[][] tower = new char[M][N];
        tower[0] = f.next().toCharArray();
        for (int i = 1; i < M; i++) {
            for (int j = 0; j < N; j++) {
                String below = "" + tower[i - 1][(j + N - 1)%N] + tower[i - 1][(j + N + 1)%N];
                tower[i][j] = rules.get(below).charAt(0);
            }
        }
        for (int i = 0; i < N; i++) {
            System.out.print(tower[M-1][i]);
        }
        System.out.println();
        f.nextLine();
    } // run method
} // QuestionOne class
