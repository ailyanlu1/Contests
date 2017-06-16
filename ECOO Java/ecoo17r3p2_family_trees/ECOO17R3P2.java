package ecoo17r3p2_family_trees;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

public class ECOO17R3P2 {
    private static ECOO17R3P2 o = new ECOO17R3P2();
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
    
    public static class Node {
        public HashMap<Integer, Node> map;
        public int max;
        
        public Node() {
            map = new HashMap<Integer, Node>();
            max = 0;
        }
    }
    
    public static void add(String id) {
        String[] x = id.split("\\.");
        int[] arr = new int[x.length];
        for (int i = 0; i < x.length; i++) {
            arr[i] = Integer.parseInt(x[i]);
        }
        Node cur = root;
        for (int i: arr) {
            if (cur.map.get(i) == null) {
                cur.map.put(i, new Node());
                cur.max = Math.max(cur.max, i);
            }
            cur = cur.map.get(i);
        }
    }
    
    public static long count(Node cur) {
        long count = cur.max % MOD;
        for (int key: cur.map.keySet()) {
            count = (count + count(cur.map.get(key))) % MOD;
        }
        return count;
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
    private static final long MOD = (long) (1e9 + 7);
    private static Node root;
    
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run();
        }
        out.close();
    }
    
    public static void run() throws IOException {
        int N = in.nextInt();
        root = new Node();
        root.max = 1;
        for (int i = 0; i < N; i++) {
            add(in.nextLine());
        }
        out.println(count(root));
    }
}
