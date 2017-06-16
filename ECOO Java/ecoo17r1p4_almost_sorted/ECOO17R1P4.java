package ecoo17r1p4_almost_sorted;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

public class ECOO17R1P4 {
    public static int min = Integer.MAX_VALUE;
    private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    private static StringTokenizer st;
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run();
        } // for i
    } // main method
    
    public static void run () throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
        int n = nextInt();
        String[] names = new String[n];
        for (int i = 0; i < n; i++) {
            names[i] = nextLine();
        }
        for (int i = 0; i < n; i++) {
            String[] sub = new String[n-1];
            for (int j = 0; j < i; j++) {
                sub[j] = names[j];
            }
            for (int j = i + 1; j < names.length; j++) {
                sub[j-1] = names[j];
            }
            int count = sort(sub);
            if (count < min) {
                min = count;
            }
        }
        System.out.println(min);
        min = Integer.MAX_VALUE;
    } // run method
    
    public static int sort(String[] a) {
        int swaps = 0;
        for (int i = 0; i < a.length - 1; ++i){    // moves the dashed line - the last time we only have the biggest so one less pass
            int smallestIndex = i;
            for (int j = i + 1; j < a.length; ++j){
                if (a[j].compareTo(a[smallestIndex]) < 0)
                    smallestIndex = j;
            } // for
            if (i != smallestIndex) {
                String temp = a[i];
                a[i] = a[smallestIndex];
                a[smallestIndex] = temp;
                swaps ++;
            }
            if (swaps > min) {
                return Integer.MAX_VALUE;
            }
        } // for
        return swaps;
    }
    private static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine().trim());
        } // while
        return st.nextToken();
    } // next method
    
    private static long nextLong() throws IOException {
        return Long.parseLong(next());
    } // nextLong method
    
    private static int nextInt() throws IOException {
        return Integer.parseInt(next());
    } // nextInt method
    
    private static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    } // nextDouble method
    
    private static String nextLine() throws IOException {
        return in.readLine().trim();
    } // nextLine method
} // QuestionFour class
