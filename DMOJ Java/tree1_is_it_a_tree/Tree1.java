import java.io.BufferedReader;
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

import java.util.Stack;

public class Tree1 {
    private static Tree1 o = new Tree1();
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
    
    public class Bag<Item> implements Iterable<Item> {
        private Node<Item> first;    // beginning of bag
        private int n;               // number of elements in bag

        // helper linked list class
        private class Node<Item> {
            private Item item;
            private Node<Item> next;
        }

        /**
         * Initializes an empty bag.
         */
        public Bag() {
            first = null;
            n = 0;
        }

        /**
         * Returns true if this bag is empty.
         *
         * @return {@code true} if this bag is empty;
         *         {@code false} otherwise
         */
        public boolean isEmpty() {
            return first == null;
        }

        /**
         * Returns the number of items in this bag.
         *
         * @return the number of items in this bag
         */
        public int size() {
            return n;
        }

        /**
         * Adds the item to this bag.
         *
         * @param  item the item to add to this bag
         */
        public void add(Item item) {
            Node<Item> oldfirst = first;
            first = new Node<Item>();
            first.item = item;
            first.next = oldfirst;
            n++;
        }


        /**
         * Returns an iterator that iterates over the items in this bag in arbitrary order.
         *
         * @return an iterator that iterates over the items in this bag in arbitrary order
         */
        public Iterator<Item> iterator()  {
            return new ListIterator<Item>(first);  
        }

        // an iterator, doesn't implement remove() since it's optional
        private class ListIterator<Item> implements Iterator<Item> {
            private Node<Item> current;

            public ListIterator(Node<Item> first) {
                current = first;
            }

            public boolean hasNext()  { return current != null;                     }
            public void remove()      { throw new UnsupportedOperationException();  }

            public Item next() {
                if (!hasNext()) throw new NoSuchElementException();
                Item item = current.item;
                current = current.next; 
                return item;
            }
        }
    }
    
    public class Queue<Item> implements Iterable<Item> {
        private Node<Item> first;    // beginning of queue
        private Node<Item> last;     // end of queue
        private int n;               // number of elements on queue

        // helper linked list class
        private class Node<Item> {
            private Item item;
            private Node<Item> next;
        }

        /**
         * Initializes an empty queue.
         */
        public Queue() {
            first = null;
            last  = null;
            n = 0;
        }

        /**
         * Returns true if this queue is empty.
         *
         * @return {@code true} if this queue is empty; {@code false} otherwise
         */
        public boolean isEmpty() {
            return first == null;
        }

        /**
         * Returns the number of items in this queue.
         *
         * @return the number of items in this queue
         */
        public int size() {
            return n;
        }

        /**
         * Returns the item least recently added to this queue.
         *
         * @return the item least recently added to this queue
         * @throws NoSuchElementException if this queue is empty
         */
        public Item peek() {
            if (isEmpty()) throw new NoSuchElementException("Queue underflow");
            return first.item;
        }

        /**
         * Adds the item to this queue.
         *
         * @param  item the item to add
         */
        public void enqueue(Item item) {
            Node<Item> oldlast = last;
            last = new Node<Item>();
            last.item = item;
            last.next = null;
            if (isEmpty()) first = last;
            else           oldlast.next = last;
            n++;
        }

        /**
         * Removes and returns the item on this queue that was least recently added.
         *
         * @return the item on this queue that was least recently added
         * @throws NoSuchElementException if this queue is empty
         */
        public Item dequeue() {
            if (isEmpty()) throw new NoSuchElementException("Queue underflow");
            Item item = first.item;
            first = first.next;
            n--;
            if (isEmpty()) last = null;   // to avoid loitering
            return item;
        }

        /**
         * Returns a string representation of this queue.
         *
         * @return the sequence of items in FIFO order, separated by spaces
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            for (Item item : this) {
                s.append(item);
                s.append(' ');
            }
            return s.toString();
        } 

        /**
         * Returns an iterator that iterates over the items in this queue in FIFO order.
         *
         * @return an iterator that iterates over the items in this queue in FIFO order
         */
        public Iterator<Item> iterator()  {
            return new ListIterator<Item>(first);  
        }

        // an iterator, doesn't implement remove() since it's optional
        private class ListIterator<Item> implements Iterator<Item> {
            private Node<Item> current;

            public ListIterator(Node<Item> first) {
                current = first;
            }

            public boolean hasNext()  { return current != null;                     }
            public void remove()      { throw new UnsupportedOperationException();  }

            public Item next() {
                if (!hasNext()) throw new NoSuchElementException();
                Item item = current.item;
                current = current.next; 
                return item;
            }
        }
    }
    
    public class UF {

        private int[] parent;  // parent[i] = parent of i
        private byte[] rank;   // rank[i] = rank of subtree rooted at i (never more than 31)
        private int count;     // number of components

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
            count = n;
            parent = new int[n];
            rank = new byte[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
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
         * Returns the number of components.
         *
         * @return the number of components (between {@code 1} and {@code n})
         */
        public int count() {
            return count;
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
        public void union(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if (rootP == rootQ) return;

            // make root of smaller rank point to root of larger rank
            if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
            else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
            else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
            count--;
        }

        // validate that p is a valid index
        private void validate(int p) {
            int n = parent.length;
            if (p < 0 || p >= n) {
                throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n-1));  
            }
        }
    }

    public class Graph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private Bag<Integer>[] adj;
        
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
            adj = (Bag<Integer>[]) new Bag[V];
            for (int v = 0; v < V; v++) {
                adj[v] = new Bag<Integer>();
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
    
    public class Cycle {
        private boolean[] marked;
        private int[] edgeTo;
        private Stack<Integer> cycle;

        /**
         * Determines whether the undirected graph {@code G} has a cycle and,
         * if so, finds such a cycle.
         *
         * @param G the undirected graph
         */
        public Cycle(Graph G) {
            if (hasSelfLoop(G)) return;
            if (hasParallelEdges(G)) return;
            marked = new boolean[G.V()];
            edgeTo = new int[G.V()];
            for (int v = 0; v < G.V(); v++)
                if (!marked[v])
                    dfs(G, -1, v);
        }


        // does this graph have a self loop?
        // side effect: initialize cycle to be self loop
        private boolean hasSelfLoop(Graph G) {
            for (int v = 0; v < G.V(); v++) {
                for (int w : G.adj(v)) {
                    if (v == w) {
                        cycle = new Stack<Integer>();
                        cycle.push(v);
                        cycle.push(v);
                        return true;
                    }
                }
            }
            return false;
        }

        // does this graph have two parallel edges?
        // side effect: initialize cycle to be two parallel edges
        private boolean hasParallelEdges(Graph G) {
            marked = new boolean[G.V()];

            for (int v = 0; v < G.V(); v++) {

                // check for parallel edges incident to v
                for (int w : G.adj(v)) {
                    if (marked[w]) {
                        cycle = new Stack<Integer>();
                        cycle.push(v);
                        cycle.push(w);
                        cycle.push(v);
                        return true;
                    }
                    marked[w] = true;
                }

                // reset so marked[v] = false for all v
                for (int w : G.adj(v)) {
                    marked[w] = false;
                }
            }
            return false;
        }

        /**
         * Returns true if the graph {@code G} has a cycle.
         *
         * @return {@code true} if the graph has a cycle; {@code false} otherwise
         */
        public boolean hasCycle() {
            return cycle != null;
        }

         /**
         * Returns a cycle in the graph {@code G}.
         * @return a cycle if the graph {@code G} has a cycle,
         *         and {@code null} otherwise
         */
        public Iterable<Integer> cycle() {
            return cycle;
        }

        private void dfs(Graph G, int u, int v) {
            marked[v] = true;
            for (int w : G.adj(v)) {

                // short circuit if cycle already found
                if (cycle != null) return;

                if (!marked[w]) {
                    edgeTo[w] = v;
                    dfs(G, v, w);
                }

                // check for cycle (but disregard reverse of edge leading to v)
                else if (w != u) {
                    cycle = new Stack<Integer>();
                    for (int x = v; x != w; x = edgeTo[x]) {
                        cycle.push(x);
                    }
                    cycle.push(w);
                    cycle.push(v);
                }
            }
        }
    }
    
    public class ConnectedComponents {
        private boolean[] marked;   // marked[v] = has vertex v been marked?
        private int[] id;           // id[v] = id of connected component containing v
        private int[] size;         // size[id] = number of vertices in given component
        private int count;          // number of connected components

        /**
         * Computes the connected components of the undirected graph {@code G}.
         *
         * @param G the undirected graph
         */
        public ConnectedComponents(Graph G) {
            marked = new boolean[G.V()];
            id = new int[G.V()];
            size = new int[G.V()];
            for (int v = 0; v < G.V(); v++) {
                if (!marked[v]) {
                    dfs(G, v);
                    count++;
                }
            }
        }

        // depth-first search for a Graph
        private void dfs(Graph G, int v) {
            marked[v] = true;
            id[v] = count;
            size[count]++;
            for (int w : G.adj(v)) {
                if (!marked[w]) {
                    dfs(G, w);
                }
            }
        }


        /**
         * Returns the component id of the connected component containing vertex {@code v}.
         *
         * @param  v the vertex
         * @return the component id of the connected component containing vertex {@code v}
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int id(int v) {
            validateVertex(v);
            return id[v];
        }

        /**
         * Returns the number of vertices in the connected component containing vertex {@code v}.
         *
         * @param  v the vertex
         * @return the number of vertices in the connected component containing vertex {@code v}
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int size(int v) {
            validateVertex(v);
            return size[id[v]];
        }

        /**
         * Returns the number of connected components in the graph {@code G}.
         *
         * @return the number of connected components in the graph {@code G}
         */
        public int count() {
            return count;
        }

        /**
         * Returns true if vertices {@code v} and {@code w} are in the same
         * connected component.
         *
         * @param  v one vertex
         * @param  w the other vertex
         * @return {@code true} if vertices {@code v} and {@code w} are in the same
         *         connected component; {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         * @throws IllegalArgumentException unless {@code 0 <= w < V}
         */
        public boolean connected(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            return id(v) == id(w);
        }

        /**
         * Returns true if vertices {@code v} and {@code w} are in the same
         * connected component.
         *
         * @param  v one vertex
         * @param  w the other vertex
         * @return {@code true} if vertices {@code v} and {@code w} are in the same
         *         connected component; {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         * @throws IllegalArgumentException unless {@code 0 <= w < V}
         * @deprecated Replaced by {@link #connected(int, int)}.
         */
        @Deprecated
        public boolean areConnected(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            return id(v) == id(w);
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            int V = marked.length;
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int N = 4;
        Graph G = o.new Graph(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int a = in.nextInt();
                if (j >= i && a == 1) G.addEdge(i, j);
            }
        }
        if (G.V() - G.E() != 1) {
            out.println("No");
            out.close();
            return;
        }
        ConnectedComponents cc = o.new ConnectedComponents(G);
        if (cc.count() != 1) {
            out.println("No");
            out.close();
            return;
        }
        Cycle cycle = o.new Cycle(G);
        if (cycle.hasCycle()) {
            out.println("No");
            out.close();
            return;
        }
        out.println("Yes");
        out.close();
    }
}
