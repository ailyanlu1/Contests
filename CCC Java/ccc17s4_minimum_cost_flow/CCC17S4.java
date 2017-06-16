package ccc17s4_minimum_cost_flow;

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

public class CCC17S4 {
    private static CCC17S4 o = new CCC17S4();
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
    
    public class UF {

        private int[] parent;  // parent[i] = parent of i

        /**
         * Initializes an empty union–find data structure with {@code n} sites
         * {@code 0} through {@code n-1}. Each site is initially in its own 
         * component.
         *
         * @param  n the number of sites
         * @throws IllegalArgumentException if {@code n < 0}
         */
        public UF(int n) {
            if (n < 0) throw new IllegalArgumentException();
            parent = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        /**
         * Returns the component identifier for the component containing site {@code p}.
         *
         * @param  p the integer representing one site
         * @return the component identifier for the component containing site {@code p}
         * @throws IndexOutOfBoundsException unless {@code 0 <= p < n}
         */
        public int find(int p) {
            validate(p);
            while (p != parent[p]) {
                parent[p] = parent[parent[p]];    // path compression by halving
                p = parent[p];
            }
            return p;
        }
      
        /**
         * Returns true if the the two sites are in the same component.
         *
         * @param  p the integer representing one site
         * @param  q the integer representing the other site
         * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
         *         {@code false} otherwise
         * @throws IndexOutOfBoundsException unless
         *         both {@code 0 <= p < n} and {@code 0 <= q < n}
         */
        public boolean connected(int p, int q) {
            return find(p) == find(q);
        }
      
        /**
         * Merges the component containing site {@code p} with the 
         * the component containing site {@code q}.
         *
         * @param  p the integer representing one site
         * @param  q the integer representing the other site
         * @throws IndexOutOfBoundsException unless
         *         both {@code 0 <= p < n} and {@code 0 <= q < n}
         */
        public boolean union(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if ((rootP ^ rootQ) != 0) {
                parent[rootP] = rootQ;
                return true;
            }
            return false;
        }

        // validate that p is a valid index
        private void validate(int p) {
            int n = parent.length;
            if (p < 0 || p >= n) {
                throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n-1));  
            }
        }
    }
    
    public static class Edge implements Comparable<Edge>{
        public int from;
        public int to;
        public int weight;
        public int current;
        
        public Edge (int from, int to, int weight, int current) {
            this.from = from;
            this.to = to;
            this.weight = weight;
            this.current = current;
        }
        
        @Override
        public int compareTo(Edge e) {
            if (weight != e.weight) return weight - e.weight;
            return current - e.current;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        int D = in.nextInt();
        Edge[] edges = new Edge[M];
        for (int i = 0; i < M; i++) {
            if (i < N - 1) edges[i] = new Edge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt(), 0);
            else edges[i] = new Edge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt(), 1);
        }
        Arrays.sort(edges);
        UF uf = o.new UF(N);
        int days = 0;
        int count = 0;
        int max = 0;
        int i = 0;
        for (i = 0; i < edges.length; i++) {
            if (count == N - 1) break;
            Edge e = edges[i];
            if (uf.union(e.from, e.to)) {
                count++;
                max = e.weight;
                if (e.current == 1) days++;
            }
        }
        if (edges[i - 1].current == 1) {
            uf = o.new UF(N);
            for (Edge e: edges) {
                if (!uf.connected(e.from, e.to)) {
                    if (e.weight < max || (e.weight == max && e.current == 0)) {
                        uf.union(e.from, e.to);
                    } else if (e.current == 0 && e.weight <= D) {
                        days--;
                        break;
                    }
                }
            }
        }
        out.println(days);
        out.close();
    }
}
