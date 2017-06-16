package ecoo16r2p3_battleship;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class ECOO16R2P3 {
    private static ECOO16R2P3 o = new ECOO16R2P3();
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    
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
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in); // TODO REMEMBER TO CHANGE THE FILE NAME
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(in);
        } // for i
    } // main method
    
    private static char[][] board;
    private static int S;
    private static int L;
    
    public static void run(Reader in) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
        S = in.nextInt();
        L = in.nextInt();
        board = new char[S][S];
        for (int i = 0; i < S; i++) {
            board[i] = in.nextLine().toCharArray();
        }
        int count = 0;
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < S; j++) {
                if (checkHor(i, j)) count++;
                if (checkVer(i, j)) count++;
            }
        }
        System.out.println(count);
    } // run method
    
    private static boolean checkHor(int i, int j) {
        if (!valid(i, j + L - 1)) return false;
        for (int x = -1; x <= L; x++) {
            if (x != -1 && x != L && valid(i, j + x) && board[i][j + x] == 'm') return false;
            if ((x == -1 || x == L) && valid(i, j + x) && board[i][j + x] == 'h') return false;
            if (valid(i - 1, j + x) && board[i - 1][j + x] == 'h') return false;
            if (valid(i + 1, j + x) && board[i + 1][j + x] == 'h') return false;
        }
        return true;
    }
    
    private static boolean checkVer(int i, int j) {
        if (!valid(i + L - 1, j)) return false;
        for (int x = -1; x <= L; x++) {
            if (x != -1 && x != L && valid(i + x, j) && board[i + x][j] == 'm') return false;
            if ((x == -1 || x == L) && valid(i + x, j) && board[i + x][j] == 'h') return false;
            if (valid(i + x, j - 1) && board[i + x][j - 1] == 'h') return false;
            if (valid(i + x, j + 1) && board[i + x][j + 1] == 'h') return false;
        }
        return true;
    }
    
    private static boolean valid(int i, int j) {
        return i >= 0 && i < S && j >= 0 && j < S;
    }
} // QuestionThree class
