package clique;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class Clique {
    private static Clique o = new Clique();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken();
        }

        public String next(String delim) throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken(delim);
        }

        /*
        public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }
        */

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public byte nextByte(String delim) throws IOException {
            return Byte.parseByte(next(delim));
        }

        public char nextChar() throws IOException {
            return next().charAt(0);
        }

        public char nextChar(String delim) throws IOException {
            return next(delim).charAt(0);
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public double nextDouble(String delim) throws IOException {
            return Double.parseDouble(next(delim));
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }

        public float nextFloat(String delim) throws IOException {
            return Float.parseFloat(next(delim));
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public int nextInt(String delim) throws IOException {
            return Integer.parseInt(next(delim));
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public long nextLong(String delim) throws IOException {
            return Long.parseLong(next(delim));
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public short nextShort(String delim) throws IOException {
            return Short.parseShort(next(delim));
        }

        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }
    } // Reader class
    
    public class AdjMatrixGraph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private boolean[][] adj;
        
        /**
         * Initializes an empty graph with {@code V} vertices and 0 edges.
         * @param V the number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public AdjMatrixGraph(int V) {
            if (V < 0) throw new IllegalArgumentException("number of vertices must be nonnegative");
            this.V = V;
            this.E = 0;
            this.adj = new boolean[V][V];
        }

        /**
         * Returns the number of vertices in the graph.
         * @return the number of vertices in the graph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in the graph.
         * @return the number of edges in the graph
         */
        public int E() {
            return E;
        }

        /**
         * Adds the edge to the graph (if there is not already an edge with the same endpoints).
         * @param v the first vertex
         * @param w the second vertex
         */
        public void addEdge(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            if (!adj[v][w]) {
                E++;
                adj[v][w] = true;
                adj[w][v] = true;
            }
        }
        
        /**
         * Returns whether there is an edge between v and w
         * 
         * @param v the first vertex
         * @param w the second vertex
         * @return true if there is an edge between v and w, false otherwise
         */
        public boolean hasEdge(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            return adj[v][w];
        }

        /**
         * Returns the  edges incident from vertex {@code v}.
         * @param v the vertex
         * @return the  edges incident from vertex {@code v} as an Iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<Integer> adj(int v) {
            validateVertex(v);
            return new AdjIterator(v);
        }

        // support iteration over graph vertices
        private class AdjIterator implements Iterator<Integer>, Iterable<Integer> {
            private int v;
            private int w = 0;

            public AdjIterator(int v) {
                this.v = v;
            }

            public Iterator<Integer> iterator() {
                return this;
            }

            public boolean hasNext() {
                while (w < V) {
                    if (adj[v][w]) return true;
                    w++;
                }
                return false;
            }

            public Integer next() {
                if (!hasNext()) {
                    throw new NoSuchElementException();
                }
                return w++;
            }

            public void remove() {
                throw new UnsupportedOperationException();
            }
        }

        /**
         * Returns a string representation of the graph. This method takes
         * time proportional to <em>V</em><sup>2</sup>.
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
         *   followed by the <em>V</em> adjacency lists of edges
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " " + E + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(v + ": ");
                for (int w: adj(v)) {
                    s.append(w + "  ");
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
    }
    
    public class BronKerboschMaxClique {
        private boolean[][] adj;
        private int[] W;
        private int maxClique;
        
        public BronKerboschMaxClique(AdjMatrixGraph G) {
            adj = new boolean[G.V()][G.V()];
            W = new int[G.V()];
            for (int v = 0; v < G.V(); v++) {
                W[v] = 1;
                for (int w = 0; w < G.V(); w++) {
                    adj[v][w] = G.hasEdge(v, w);
                }
            }
            maxClique = solve(G.V(), 0, (int) ((1l << G.V()) - 1), 0);
        }
        
        public int maxClique() {
            return maxClique;
        }
        
        private int solve(int nodes, int curr, int pool, int excl) {
            if (pool == 0 && excl == 0) {
                int cnt = 0;
                for (int i = 0; i < nodes; i++)
                    if ((curr & 1l << i) > 0) cnt += W[i];
                return cnt;
            }
            int res = 0;
            int j = 0;
            for (int i = 0; i < nodes; i++)
                if ((pool & 1l << i) > 0 || (excl & 1l << i) > 0) j = i;

            for (int i = 0; i < nodes; i++) {
                if ((pool & 1l << i) == 0 || adj[i][j]) continue;
                int ncurr = curr, npool = 0, nexcl = 0;
                ncurr |= 1l << i;

                for (int k = 0; k < nodes; k++) {
                    if (adj[i][k]) {
                        npool |= pool & 1l << k;
                        nexcl |= excl & 1l << k;
                    }
                }
                res = Math.max(res, solve(nodes, ncurr, npool, nexcl));

                pool &= ~(1l << i);
                excl |= 1 >> i;
            }
            return res;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        AdjMatrixGraph G = o.new AdjMatrixGraph(N);
        for (int i = 0; i < M; i++) {
            G.addEdge(in.nextInt() - 1, in.nextInt() - 1);
        }
        BronKerboschMaxClique maxClique = o.new BronKerboschMaxClique(G);
        out.println(maxClique.maxClique());
        out.close();
    }
}
