import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.HashSet;
import java.util.Stack;

public class CCC16S3 {
    private static CCC16S3 o = new CCC16S3();
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
    
    public class Graph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private HashSet<Integer>[] adj;
        
        /**
         * Initializes an empty graph with {@code V} vertices and 0 edges.
         * param V the number of vertices
         *
         * @param  V number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public Graph(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices must be nonnegative");
            this.V = V;
            this.E = 0;
            adj = (HashSet<Integer>[]) new HashSet[V];
            for (int v = 0; v < V; v++) {
                adj[v] = new HashSet<Integer>();
            }
        }

        /**
         * Initializes a new graph that is a deep copy of {@code G}.
         *
         * @param  G the graph to copy
         */
        public Graph(Graph G) {
            this(G.V());
            this.E = G.E();
            for (int v = 0; v < G.V(); v++) {
                // reverse so that adjacency list is in same order as original
                Stack<Integer> reverse = new Stack<Integer>();
                for (int w : G.adj[v]) {
                    reverse.push(w);
                }
                for (int w : reverse) {
                    adj[v].add(w);
                }
            }
        }

        /**
         * Returns the number of vertices in this graph.
         *
         * @return the number of vertices in this graph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in this graph.
         *
         * @return the number of edges in this graph
         */
        public int E() {
            return E;
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }

        /**
         * Adds the undirected edge v-w to this graph.
         *
         * @param  v one vertex in the edge
         * @param  w the other vertex in the edge
         * @throws IllegalArgumentException unless both {@code 0 <= v < V} and {@code 0 <= w < V}
         */
        public void addEdge(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            E++;
            adj[v].add(w);
            adj[w].add(v);
        }
        
        public void removeAllEdges(int v) {
            for (int w: adj[v]) {
                adj[w].remove(v);
            }
            adj[v] = new HashSet<Integer>();
        }

        /**
         * Returns the vertices adjacent to vertex {@code v}.
         *
         * @param  v the vertex
         * @return the vertices adjacent to vertex {@code v}, as an iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<Integer> adj(int v) {
            validateVertex(v);
            return adj[v];
        }

        /**
         * Returns the degree of vertex {@code v}.
         *
         * @param  v the vertex
         * @return the degree of vertex {@code v}
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int degree(int v) {
            validateVertex(v);
            return adj[v].size();
        }


        /**
         * Returns a string representation of this graph.
         *
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
         *         followed by the <em>V</em> adjacency lists
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " vertices, " + E + " edges " + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(v + ": ");
                for (int w : adj[v]) {
                    s.append(w + " ");
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }

    }
    
    public class DepthFirstSearch {
        private boolean[] marked;    // marked[v] = is there an s-v path?
        private int[] depth;      // depth[v] = depth of vertex v
        private int count;           // number of vertices connected to s

        /**
         * Computes the vertices in graph {@code G} that are
         * connected to the source vertex {@code s}.
         * @param G the graph
         * @param s the source vertex
         * @throws IllegalArgumentException unless {@code 0 <= s < V}
         */
        public DepthFirstSearch(Graph G, int s) {
            marked = new boolean[G.V()];
            depth = new int[G.V()];
            for (int v = 0; v < G.V(); v++)
                depth[v] = -1;
            validateVertex(s);
            dfs(G, s, 0);
        }

        // depth first search from v
        private void dfs(Graph G, int v, int i) {
            count++;
            marked[v] = true;
            depth[v] = i;
            for (int w : G.adj(v)) {
                if (!marked[w]) {
                    dfs(G, w, i+1);
                }
            }
        }
        
        /**
         * Returns the depth of vertex {@code v} from the source vertex {@code s}
         * @param v the vertex
         * @return the depth of a vertex
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int depthOf(int v) {
            validateVertex(v);
            return depth[v];
        }

        /**
         * Is there a path between the source vertex {@code s} and vertex {@code v}?
         * @param v the vertex
         * @return {@code true} if there is a path, {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public boolean marked(int v) {
            validateVertex(v);
            return marked[v];
        }

        /**
         * Returns the number of vertices connected to the source vertex {@code s}.
         * @return the number of vertices connected to the source vertex {@code s}
         */
        public int count() {
            return count;
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            int V = marked.length;
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
    }

    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        HashSet<Integer> pho = new HashSet<Integer>();
        for (int i = 0; i < m; i++) {
            pho.add(in.nextInt());
        }
        Graph G = o.new Graph(n);
        for (int i = 0; i < n-1; i++) {
            G.addEdge(in.nextInt(), in.nextInt());
        }
        
        int start = pho.iterator().next();
        boolean[] marked = new boolean[G.V()];
        Graph R = o.new Graph(G);
        removeLeaves(G, R, start, pho, marked);
        DepthFirstSearch dfs = o.new DepthFirstSearch(R, start);
        int maxV = start;
        for (int i = 0; i < n; i++) {
            if (dfs.depthOf(i) > dfs.depthOf(maxV)) maxV = i;
        }
        DepthFirstSearch dfs2 = o.new DepthFirstSearch(R, maxV);
        int diameterV = maxV;
        for (int i = 0; i < n; i++) {
            if (dfs2.depthOf(i) > dfs2.depthOf(diameterV)) diameterV = i;
        }
        System.out.println(2*(dfs2.count() - 1) - dfs2.depthOf(diameterV));
        
    }
    
    // depth first search from v
    private static void removeLeaves(Graph G, Graph R, int v, HashSet<Integer> pho, boolean[] marked) {
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                removeLeaves(G, R, w, pho, marked);
            }
        }
        if (R.degree(v) == 1 && !pho.contains(v)) {
            R.removeAllEdges(v);
        }
    }
}
