package dmopc14c2p6_selective_cutting;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class DMOPC14C2P6 {
    private static DMOPC14C2P6 o = new DMOPC14C2P6();
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
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static class Tree implements Comparable<Tree> {
        public int i;
        public int m;
        public Tree(int i, int m) {
            this.i = i;
            this.m = m;
        }
        @Override
        public int compareTo(Tree t) {
            return t.m - m;
        }
    }
    
    public static class Query implements Comparable<Query> {
        public int i;
        public int l;
        public int r;
        public int m;
        public Query(int i, int l, int r, int m) {
            this.i = i;
            this.l = l;
            this.r = r;
            this.m = m;
        }
        @Override
        public int compareTo(Query q) {
            return q.m - m;
        }
    }
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        Tree[] trees = new Tree[N];
        FenwickTree ft = o.new FenwickTree(N);
        for (int i = 0; i < N; i++) {
            trees[i] = new Tree(i + 1, in.nextInt());
        }
        Arrays.sort(trees);
        int Q = in.nextInt();
        Query[] queries = new Query[Q];
        int[] ans = new int[Q];
        for (int i = 0; i < Q; i++) {
            queries[i] = new Query(i, in.nextInt() + 1, in.nextInt() + 1, in.nextInt());
        }
        Arrays.sort(queries);
        for (int i = 0, j = 0; i < Q; i++) {
            for (;j < N && queries[i].m <= trees[j].m; j++) {
                ft.update(trees[j].i, trees[j].m);
            }
            ans[queries[i].i] = ft.rsq(queries[i].l, queries[i].r);
        }
        for (int i = 0; i < Q; i++) {
            out.println(ans[i]);
        }
        out.close();
    }
}
