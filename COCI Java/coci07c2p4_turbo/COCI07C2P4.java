package coci07c2p4_turbo;

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

public class COCI07C2P4 {
    private static COCI07C2P4 o = new COCI07C2P4();
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

        int[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

        public FenwickTree(int size) {
            array = new int[size + 1];
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
        public int rsq(int ind) {
            int sum = 0;
            for (int x = ind; x > 0; x -= (x & -x)) {
                sum += array[x];
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
        public int rsq(int a, int b) {
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
        public void update(int ind, int value) {
            for (int x = ind; x < array.length; x += (x & -x)) {
                array[x] += value;
            }
        }

        public int size() {
            return array.length - 1;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int[] arr = new int[N + 1];
        FenwickTree ft = o.new FenwickTree(N);
        for (int i = 1; i <= N; i++) {
            arr[in.nextInt()] = i;
            ft.update(i, 1);
        }
        int low = 1;
        int high = N;
        for (int i = 1; i <= N; i++) {
            if (i % 2 == 0) {
                ft.update(arr[high], -1);
                out.println(ft.rsq(arr[high], N));
                high--;
            } else {
                ft.update(arr[low], -1);
                out.println(ft.rsq(1, arr[low]));
                low++;
            }
        }
        out.close();
    }
}
