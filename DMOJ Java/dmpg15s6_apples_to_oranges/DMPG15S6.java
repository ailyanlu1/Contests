import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;
import java.util.StringTokenizer;

public class DMPG15S6 {
    private static DMPG15S6 o = new DMPG15S6();
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
    
    public class DirectedWeightedEdge { 
        private final int v;
        private final int w;
        private final double weight;

        /**
         * Initializes a directed edge from vertex {@code v} to vertex {@code w} with
         * the given {@code weight}.
         * @param v the tail vertex
         * @param w the head vertex
         * @param weight the weight of the directed edge
         * @throws IllegalArgumentException if either {@code v} or {@code w}
         *    is a negative integer
         * @throws IllegalArgumentException if {@code weight} is {@code NaN}
         */
        public DirectedWeightedEdge(int v, int w, double weight) {
            if (v < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
            if (w < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
            if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
            this.v = v;
            this.w = w;
            this.weight = weight;
        }

        /**
         * Returns the tail vertex of the directed edge.
         * @return the tail vertex of the directed edge
         */
        public int from() {
            return v;
        }

        /**
         * Returns the head vertex of the directed edge.
         * @return the head vertex of the directed edge
         */
        public int to() {
            return w;
        }

        /**
         * Returns the weight of the directed edge.
         * @return the weight of the directed edge
         */
        public double weight() {
            return weight;
        }

        /**
         * Returns a string representation of the directed edge.
         * @return a string representation of the directed edge
         */
        public String toString() {
            return v + "->" + w + " " + String.format("%5.2f", weight);
        }
        
        @Override
        public int hashCode() {
            return toString().hashCode();
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof DirectedWeightedEdge)) {
                return false;
            }
            DirectedWeightedEdge e = (DirectedWeightedEdge) o;
            return e.from() == v && e.to() == w && e.weight() == weight;
        }
    }
    
    public class WeightedDigraph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;                // number of vertices in this digraph
        private int E;                      // number of edges in this digraph
        private Bag<DirectedWeightedEdge>[] adj;    // adj[v] = adjacency list for vertex v
        private int[] indegree;             // indegree[v] = indegree of vertex v
        
        /**
         * Initializes an empty edge-weighted digraph with {@code V} vertices and 0 edges.
         *
         * @param  V the number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public WeightedDigraph(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices in a Digraph must be nonnegative");
            this.V = V;
            this.E = 0;
            this.indegree = new int[V];
            adj = (Bag<DirectedWeightedEdge>[]) new Bag[V];
            for (int v = 0; v < V; v++)
                adj[v] = new Bag<DirectedWeightedEdge>();
        }

        /**
         * Initializes a new edge-weighted digraph that is a deep copy of {@code G}.
         *
         * @param  G the edge-weighted digraph to copy
         */
        public WeightedDigraph(WeightedDigraph G) {
            this(G.V());
            this.E = G.E();
            for (int v = 0; v < G.V(); v++)
                this.indegree[v] = G.indegree(v);
            for (int v = 0; v < G.V(); v++) {
                // reverse so that adjacency list is in same order as original
                Stack<DirectedWeightedEdge> reverse = new Stack<DirectedWeightedEdge>();
                for (DirectedWeightedEdge e : G.adj[v]) {
                    reverse.push(e);
                }
                for (DirectedWeightedEdge e : reverse) {
                    adj[v].add(e);
                }
            }
        }

        /**
         * Returns the number of vertices in this edge-weighted digraph.
         *
         * @return the number of vertices in this edge-weighted digraph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in this edge-weighted digraph.
         *
         * @return the number of edges in this edge-weighted digraph
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
         * Adds the directed edge {@code e} to this edge-weighted digraph.
         *
         * @param  e the edge
         * @throws IllegalArgumentException unless endpoints of edge are between {@code 0}
         *         and {@code V-1}
         */
        public void addEdge(DirectedWeightedEdge e) {
            int v = e.from();
            int w = e.to();
            validateVertex(v);
            validateVertex(w);
            adj[v].add(e);
            indegree[w]++;
            E++;
        }


        /**
         * Returns the directed edges incident from vertex {@code v}.
         *
         * @param  v the vertex
         * @return the directed edges incident from vertex {@code v} as an Iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<DirectedWeightedEdge> adj(int v) {
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
         * Returns all directed edges in this edge-weighted digraph.
         * To iterate over the edges in this edge-weighted digraph, use foreach notation:
         * {@code for (DirectedEdge e : G.edges())}.
         *
         * @return all edges in this edge-weighted digraph, as an iterable
         */
        public Iterable<DirectedWeightedEdge> edges() {
            Bag<DirectedWeightedEdge> list = new Bag<DirectedWeightedEdge>();
            for (int v = 0; v < V; v++) {
                for (DirectedWeightedEdge e : adj(v)) {
                    list.add(e);
                }
            }
            return list;
        } 

        /**
         * Returns a string representation of this edge-weighted digraph.
         *
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
         *         followed by the <em>V</em> adjacency lists of edges
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " " + E + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(v + ": ");
                for (DirectedWeightedEdge e : adj[v]) {
                    s.append(e + "  ");
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    private static double[] cost;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        WeightedDigraph G = o.new WeightedDigraph(N);
        HashMap<String, Integer> sToV = new HashMap<String, Integer>();
        for (int i = 0; i < N; i++) {
            sToV.put(in.next(), i);
        }
        for (int i = 0; i < M; i++) {
            DirectedWeightedEdge e = o.new DirectedWeightedEdge(sToV.get(in.next()), sToV.get(in.next()), in.nextDouble());
            G.addEdge(e);
        }
        cost = new double[N];
        int s = sToV.get("APPLES");
        cost[s] = 1.0;
        bfs(G, s);
        out.close();
    }
    
    private static void bfs(WeightedDigraph G, int s) {
        Queue<Integer> q = o.new Queue<Integer>();
        q.enqueue(s);
        while (!q.isEmpty()) {
            int v = q.dequeue();
            if (v == s) {
                if (cost[v] - 1.0 > 1e-6) {
                    out.println("YA");
                    return;
                }
            }
            for (DirectedWeightedEdge e: G.adj(v)) {
                int w = e.to();
                if (cost[v] * e.weight() > cost[w]) {
                    cost[w] = cost[v] * e.weight();
                    q.enqueue(w);
                }
            }
        }
        out.println("NAW");
    }
}
