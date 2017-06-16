package ds1_binary_indexed_tree_test;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DS1 {
private static DS1 o = new DS1();
    
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
    
    public class FenwickTree {

        long[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

        public FenwickTree(int size) {
            array = new long[size + 1];
        }

        /**
         * Range Sum query from 1 to ind
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind index
         * @return sum
         */
        public long rsq(int ind) {
            long sum = 0;
            while (ind > 0) {
                sum += array[ind];
                //Extracting the portion up to the first significant one of the binary representation of 'ind' and decrementing ind by that number
                ind -= ind & (-ind);
            }

            return sum;
        }

        /**
         * Range Sum Query from a to b.
         * Search for the sum from array index from a to b
         * a and b are 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  a left index
         * @param  b right index
         * @return sum
         */
        public long rsq(int a, int b) {
            return rsq(b) - rsq(a - 1);
        }

        /**
         * Update the array at ind and all the affected regions above ind.
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind   index
         * @param  value value
         */
        public void update(int ind, long value) {
            assert ind > 0;
            while (ind < array.length) {
                array[ind] += value;
                //Extracting the portion up to the first significant one of the binary representation of 'ind' and incrementing ind by that number
                ind += ind & (-ind);
            }
        }

        public int size() {
            return array.length - 1;
        }
    }
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int n = in.nextInt();
        int m = in.nextInt();
        FenwickTree tree = o.new FenwickTree(n+1);
        FenwickTree rank = o.new FenwickTree(100001);
        for (int i = 1; i <= n; i++) {
            int v = in.nextInt();
            tree.update(i, v);
            rank.update(v, 1);
        }
        for (int i = 0; i < m; i++) {
            String op = in.next();
            if (op.equals("C")) {
                int index = in.nextInt();
                int val = in.nextInt();
                int old = (int) tree.rsq(index, index);
                tree.update(index, (val - old));
                rank.update(old, -1);
                rank.update(val, 1);
            } else if (op.equals("S")) {
                out.println(tree.rsq(in.nextInt(), in.nextInt()));
            } else {
                out.println(rank.rsq(in.nextInt()));
            }
        }
        out.close();
    }
}
