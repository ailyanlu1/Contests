package ecoo16r2p4_hop_skip_and_jump;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;
import java.util.StringTokenizer;

public class ECOO16R2P4 {
    private static ECOO16R2P4 o = new ECOO16R2P4();
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
    
    public class Digraph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;           // number of vertices in this digraph
        private int E;                 // number of edges in this digraph
        private Bag<Integer>[] adj;    // adj[v] = adjacency list for vertex v
        private int[] indegree;        // indegree[v] = indegree of vertex v
        
        /**
         * Initializes an empty digraph with <em>V</em> vertices.
         *
         * @param  V the number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public Digraph(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices in a Digraph must be nonnegative");
            this.V = V;
            this.E = 0;
            indegree = new int[V];
            adj = (Bag<Integer>[]) new Bag[V];
            for (int v = 0; v < V; v++) {
                adj[v] = new Bag<Integer>();
            }
        }

        /**
         * Initializes a new digraph that is a deep copy of the specified digraph.
         *
         * @param  G the digraph to copy
         */
        public Digraph(Digraph G) {
            this(G.V());
            this.E = G.E();
            for (int v = 0; v < V; v++)
                this.indegree[v] = G.indegree(v);
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
         * Returns the number of vertices in this digraph.
         *
         * @return the number of vertices in this digraph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in this digraph.
         *
         * @return the number of edges in this digraph
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
         * Adds the directed edge v→w to this digraph.
         *
         * @param  v the tail vertex
         * @param  w the head vertex
         * @throws IllegalArgumentException unless both {@code 0 <= v < V} and {@code 0 <= w < V}
         */
        public void addEdge(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            adj[v].add(w);
            indegree[w]++;
            E++;
        }

        /**
         * Returns the vertices adjacent from vertex {@code v} in this digraph.
         *
         * @param  v the vertex
         * @return the vertices adjacent from vertex {@code v} in this digraph, as an iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<Integer> adj(int v) {
            validateVertex(v);
            return adj[v];
        }

        /**
         * Returns the number of directed edges incident from vertex {@code v}.
         * This is known as the <em>outdegree</em> of vertex {@code v}.
         *
         * @param  v the vertex
         * @return the outdegree of vertex {@code v}               
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int outdegree(int v) {
            validateVertex(v);
            return adj[v].size();
        }

        /**
         * Returns the number of directed edges incident to vertex {@code v}.
         * This is known as the <em>indegree</em> of vertex {@code v}.
         *
         * @param  v the vertex
         * @return the indegree of vertex {@code v}               
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int indegree(int v) {
            validateVertex(v);
            return indegree[v];
        }

        /**
         * Returns the reverse of the digraph.
         *
         * @return the reverse of the digraph
         */
        public Digraph reverse() {
            Digraph reverse = new Digraph(V);
            for (int v = 0; v < V; v++) {
                for (int w : adj(v)) {
                    reverse.addEdge(w, v);
                }
            }
            return reverse;
        }

        /**
         * Returns a string representation of the graph.
         *
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,  
         *         followed by the <em>V</em> adjacency lists
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " vertices, " + E + " edges " + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(String.format("%d: ", v));
                for (int w : adj[v]) {
                    s.append(String.format("%d ", w));
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }
    }
    
    public class BreadthFirstDirectedPaths {
        private static final int INFINITY = Integer.MAX_VALUE;
        private boolean[] marked;  // marked[v] = is there an s->v path?
        private int[] edgeTo;      // edgeTo[v] = last edge on shortest s->v path
        private int[] distTo;      // distTo[v] = length of shortest s->v path

        /**
         * Computes the shortest path from {@code s} and every other vertex in graph {@code G}.
         * @param G the digraph
         * @param s the source vertex
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public BreadthFirstDirectedPaths(Digraph G, int s) {
            marked = new boolean[G.V()];
            distTo = new int[G.V()];
            edgeTo = new int[G.V()];
            for (int v = 0; v < G.V(); v++)
                distTo[v] = INFINITY;
            validateVertex(s);
            bfs(G, s);
        }

        /**
         * Computes the shortest path from any one of the source vertices in {@code sources}
         * to every other vertex in graph {@code G}.
         * @param G the digraph
         * @param sources the source vertices
         * @throws IllegalArgumentException unless each vertex {@code v} in
         *         {@code sources} satisfies {@code 0 <= v < V}
         */
        public BreadthFirstDirectedPaths(Digraph G, Iterable<Integer> sources) {
            marked = new boolean[G.V()];
            distTo = new int[G.V()];
            edgeTo = new int[G.V()];
            for (int v = 0; v < G.V(); v++)
                distTo[v] = INFINITY;
            validateVertices(sources);
            bfs(G, sources);
        }

        // BFS from single source
        private void bfs(Digraph G, int s) {
            Queue<Integer> q = new Queue<Integer>();
            marked[s] = true;
            distTo[s] = 0;
            q.enqueue(s);
            while (!q.isEmpty()) {
                int v = q.dequeue();
                for (int w : G.adj(v)) {
                    if (!marked[w]) {
                        edgeTo[w] = v;
                        distTo[w] = distTo[v] + 1;
                        marked[w] = true;
                        q.enqueue(w);
                    }
                }
            }
        }

        // BFS from multiple sources
        private void bfs(Digraph G, Iterable<Integer> sources) {
            Queue<Integer> q = new Queue<Integer>();
            for (int s : sources) {
                marked[s] = true;
                distTo[s] = 0;
                q.enqueue(s);
            }
            while (!q.isEmpty()) {
                int v = q.dequeue();
                for (int w : G.adj(v)) {
                    if (!marked[w]) {
                        edgeTo[w] = v;
                        distTo[w] = distTo[v] + 1;
                        marked[w] = true;
                        q.enqueue(w);
                    }
                }
            }
        }

        /**
         * Is there a directed path from the source {@code s} (or sources) to vertex {@code v}?
         * @param v the vertex
         * @return {@code true} if there is a directed path, {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public boolean hasPathTo(int v) {
            validateVertex(v);
            return marked[v];
        }

        /**
         * Returns the number of edges in a shortest path from the source {@code s}
         * (or sources) to vertex {@code v}?
         * @param v the vertex
         * @return the number of edges in a shortest path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public int distTo(int v) {
            validateVertex(v);
            return distTo[v];
        }

        /**
         * Returns a shortest path from {@code s} (or sources) to {@code v}, or
         * {@code null} if no such path.
         * @param v the vertex
         * @return the sequence of vertices on a shortest path, as an Iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<Integer> pathTo(int v) {
            validateVertex(v);

            if (!hasPathTo(v)) return null;
            Stack<Integer> path = new Stack<Integer>();
            int x;
            for (x = v; distTo[x] != 0; x = edgeTo[x])
                path.push(x);
            path.push(x);
            return path;
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            int V = marked.length;
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertices(Iterable<Integer> vertices) {
            if (vertices == null) {
                throw new IllegalArgumentException("argument is null");
            }
            int V = marked.length;
            for (int v : vertices) {
                if (v < 0 || v >= V) {
                    throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
                }
            }
        }
    }

    private static Reader in = o.new Reader(System.in);
    private static int W = 0;
    private static int H = 0;
    private static char[][] b = new char[H][W];
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run();
        } // for i
    } // main method
    
    public static void run() throws IOException {
        W = in.nextInt();
        H = in.nextInt();
        int h = 0, s = 0, j = 0, C = 0, F = 0, T = 0;
        b = new char[H][W];
        Digraph Hop = o.new Digraph(H*W);
        Digraph Skip = o.new Digraph(H*W);
        Digraph Jump = o.new Digraph(H*W);
        for (int i = 0; i < H; i++) {
            String line = in.next();
            for (int k = 0; k < W; k++) {
                char c = line.charAt(k);
                if (c == 'h') {
                    h = toPoint(i, k);
                    c = '.';
                } else if (c == 's') {
                    s = toPoint(i, k);
                    c = '.';
                } else if (c == 'j') {
                    j = toPoint(i, k);
                    c = '.';
                } else if (c == 'C') {
                    C = toPoint(i, k);
                    c = '.';
                } else if (c == 'F') {
                    F = toPoint(i, k);
                    c = '.';
                } else if (c == 'T') {
                    T = toPoint(i, k);
                    c = '.';
                }
                b[i][k] = c;
            }
        }
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                if (falling(i, k) && isPoint(i+1, k)) { // gravity
                    Hop.addEdge(toPoint(i, k), toPoint(i+1, k));
                    Skip.addEdge(toPoint(i, k), toPoint(i+1, k));
                    Jump.addEdge(toPoint(i, k), toPoint(i+1, k));
                }
                if (b[i][k] == '#' && (isPoint(i-1, k) && b[i-1][k] != '=')) { // up a ladder
                    Hop.addEdge(toPoint(i, k), toPoint(i-1, k));
                    Skip.addEdge(toPoint(i, k), toPoint(i-1, k));
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k));
                }
                if (!falling(i, k) && (isPoint(i+1, k) && b[i+1][k] == '#')) { // down a ladder
                    Hop.addEdge(toPoint(i, k), toPoint(i+1, k));
                    Skip.addEdge(toPoint(i, k), toPoint(i+1, k));
                    Jump.addEdge(toPoint(i, k), toPoint(i+1, k));
                }
                if (!falling(i, k) && (isPoint(i, k+1) && b[i][k+1] != '=')) { // right
                    Hop.addEdge(toPoint(i, k), toPoint(i, k+1));
                    Skip.addEdge(toPoint(i, k), toPoint(i, k+1));
                    Jump.addEdge(toPoint(i, k), toPoint(i, k+1));
                }
                if (!falling(i, k) && (isPoint(i, k-1) && b[i][k-1] != '=')) { // left
                    Hop.addEdge(toPoint(i, k), toPoint(i, k-1));
                    Skip.addEdge(toPoint(i, k), toPoint(i, k-1));
                    Jump.addEdge(toPoint(i, k), toPoint(i, k-1));
                }
                if (!falling(i, k) && (isPoint(i-1, k+1) && b[i-1][k+1] != '=' && b[i-1][k] != '=')) { // hop right
                    Hop.addEdge(toPoint(i, k), toPoint(i-1, k+1));
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k+1));
                }
                if (!falling(i, k) && (isPoint(i-1, k-1) && b[i-1][k-1] != '=' && b[i-1][k] != '=')) { // hop left
                    Hop.addEdge(toPoint(i, k), toPoint(i-1, k-1));
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k-1));
                }
                if (!falling(i, k) && (isPoint(i-1, k) && b[i-1][k] != '=')) { // hop up
                    Hop.addEdge(toPoint(i, k), toPoint(i-1, k));
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k));
                }
                if (!falling(i, k) && (isPoint(i, k+2) && b[i][k+2] != '=' && b[i][k+1] != '=')) { // skip right
                    Skip.addEdge(toPoint(i, k), toPoint(i, k+2));
                    Jump.addEdge(toPoint(i, k), toPoint(i, k+2));
                }
                if (!falling(i, k) && (isPoint(i, k-2) && b[i][k-2] != '=' && b[i][k-1] != '=')) { // skip left
                    Skip.addEdge(toPoint(i, k), toPoint(i, k-2));
                    Jump.addEdge(toPoint(i, k), toPoint(i, k-2));
                }
                if (!falling(i, k) && (isPoint(i, k+3) && b[i][k+3] != '=' && b[i][k+2] != '=' && b[i][k+1] != '=')) { // long jump right
                    Jump.addEdge(toPoint(i, k), toPoint(i, k+3));
                }
                if (!falling(i, k) && (isPoint(i, k-3) && b[i][k-3] != '=' && b[i][k-2] != '=' && b[i][k-1] != '=')) { // long jump left
                    Jump.addEdge(toPoint(i, k), toPoint(i, k-3));
                }
                if (!falling(i, k) && (isPoint(i-1, k+2) && b[i-1][k+2] != '=' && b[i-1][k+1] != '=' && b[i-1][k] != '=' && b[i][k+1] != '=')) { // high jump right
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k+2));
                }
                if (!falling(i, k) && (isPoint(i-1, k-2) && b[i-1][k-2] != '=' && b[i-1][k-1] != '=' && b[i-1][k] != '=' && b[i][k-1] != '=')) { // high jump left
                    Jump.addEdge(toPoint(i, k), toPoint(i-1, k-2));
                }
                if (!falling(i, k) && (isPoint(i-2, k) && b[i-2][k] != '=' && b[i-1][k] != '=')) { // spring jump
                    Jump.addEdge(toPoint(i, k), toPoint(i-2, k));
                }
            }
        }
        BreadthFirstDirectedPaths HopBFS = o.new BreadthFirstDirectedPaths(Hop, h);
        BreadthFirstDirectedPaths SkipBFS = o.new BreadthFirstDirectedPaths(Skip, s);
        BreadthFirstDirectedPaths JumpBFS = o.new BreadthFirstDirectedPaths(Jump, j);
        String hop = "HOP ";
        String skip = "SKIP ";
        String jump = "JUMP ";
        if (HopBFS.hasPathTo(C)) hop += "C";
        if (HopBFS.hasPathTo(F)) hop += "F";
        if (HopBFS.hasPathTo(T)) hop += "T";
        
        if (SkipBFS.hasPathTo(C)) skip += "C";
        if (SkipBFS.hasPathTo(F)) skip += "F";
        if (SkipBFS.hasPathTo(T)) skip += "T";
        
        if (JumpBFS.hasPathTo(C)) jump += "C";
        if (JumpBFS.hasPathTo(F)) jump += "F";
        if (JumpBFS.hasPathTo(T)) jump += "T";
        
        System.out.println(hop.trim());
        System.out.println(skip.trim());
        System.out.println(jump.trim());
        System.out.println();
    } // run method
    
    private static boolean falling(int i, int k) {
        return (b[i][k] == '.' && ((isPoint(i+1, k) && b[i+1][k] == '.') || !isPoint(i+1, k)));
    }
    private static boolean isPoint(int i, int k) {
        return (i >= 0 && i < H && k >= 0 && k < W);
    }
    private static int toPoint(int i, int k) {
        return i*W + k;
    }
} // QuestionFour class
