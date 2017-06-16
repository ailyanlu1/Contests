package ecoo15r2p1_the_interlace_cypher;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class ECOO15R2P1 {
    private static ECOO15R2P1 o = new ECOO15R2P1();
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
        String type = f.nextLine();
        String[] original = f.nextLine().split(" ");
        char[][] arr = new char[original.length][];
        int max = 0;
        String output = "";
        for (int i = 0; i < arr.length; i++) {
            arr[i] = new char[original[i].length()];
            max = Integer.max(max, original[i].length());
        }
        if (type.equals("encode")) {
            for (int i = 0; i < arr.length; i++) {
                for (int j = 0; j < original[i].length(); j++) {
                    arr[i][j] = original[i].charAt(j);
                }
            }
            int count = 0;
            int countIndex = 0;
            for (int i = 0; i < max; i++) {
                for (int j = 0; j < arr.length; j++) {
                    if (i >= arr[j].length) continue;
                    if (count >= original[countIndex].length()) {
                        output += " ";
                        count = 0;
                        countIndex++;
                    }
                    output += arr[j][i];
                    count++;
                }
            }
        } else /*if (type.equals("decode"))*/ {
            int curI = 0;
            int curJ = 0;
            for (int i = 0; i < max; i++) {
                for (int j = 0; j < arr.length; j++) {
                    if (i >= arr[j].length) continue;
                    arr[j][i] = original[curI].charAt(curJ++);
                    if (curJ >= original[curI].length()) {
                        curJ = 0;
                        curI++;
                    }
                }
            }
            for (int i = 0; i < arr.length; i++) {
                for (int j = 0; j < arr[i].length; j++) {
                    output += arr[i][j];
                }
                output += " ";
            }
        }
        System.out.println(output);
    } // run method
} // ECOO15R2P1 class