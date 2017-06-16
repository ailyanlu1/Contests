package ccc09j5_degrees_of_separation;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.Stack;

public class CCC09J5 {
    private static CCC09J5 o = new CCC09J5();
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
    
    public class VariableGraph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private HashSet<Integer>[] adj;
        private HashSet<Edge> removed;
        
        /**
         * Initializes an empty graph with {@code V} vertices and 0 edges.
         * param V the number of vertices
         *
         * @param  V number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public VariableGraph(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices must be nonnegative");
            this.V = V;
            this.E = 0;
            adj = (HashSet<Integer>[]) new HashSet[V];
            removed = new HashSet<Edge>();
            for (int v = 0; v < V; v++) {
                adj[v] = new HashSet<Integer>();
            }
        }

        /**
         * Initializes a new graph that is a deep copy of {@code G}.
         *
         * @param  G the graph to copy
         */
        public VariableGraph(VariableGraph G) {
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
         * Removes the edge from from this graph.
         *
         * @param  v one vertex in the edge
         * @param  w the other vertex in the edge
         * @throws IllegalArgumentException unless endpoints of edge are between {@code 0}
         *         and {@code V-1}
         */
        public void removeEdge(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            removed.add(new Edge(v, w));
            adj[v].remove(w);
            adj[w].remove(v);
            E--;
        }
        
        /**
         * Restores all the edges removed from this edge-weighted graph.
         */
        public void restoreEdges() {
            for (Edge e: removed) {
                addEdge(e.v, e.w);
            }
            removed.clear();
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
        
        public class Edge {
            public int v;
            public int w;
            
            public Edge(int v, int w) {
                this.v = Math.min(v, w);
                this.w = Math.max(v, w);
            }
            
            @Override
            public int hashCode() {
                return 31 * v + w;
            }
                
            @Override
            public boolean equals(Object o) {
                if (o == this) return true;
                if (!(o instanceof Edge)) {
                    return false;
                }
                Edge e = (Edge) o;
                return e.v == v && e.w == w;
            }
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    private static VariableGraph G;
    
    public static void main(String[] args) throws IOException {
        char c;
        G = o.new VariableGraph(50);
        setup();
        while((c = in.next().charAt(0)) != 'q') {
            if (c == 'i') {
                G.addEdge(in.nextInt(), in.nextInt());
            } else if (c == 'd') {
                G.removeEdge(in.nextInt(), in.nextInt());
            } else if (c == 'n') {
                out.println(G.degree(in.nextInt()));
            } else if (c == 'f') {
                HashSet<Integer> fOfF = new HashSet<Integer>();
                HashSet<Integer> friends = new HashSet<Integer>();
                int x = in.nextInt();
                friends.add(x);
                for (int v: G.adj(x)) {
                    friends.add(v);
                    fOfF.remove(v);
                    for (int w: G.adj(v)) {
                        if (!friends.contains(w)) fOfF.add(w);
                    }
                }
                out.println(fOfF.size());
            } else /*if (c == 's')*/ {
                bfs(in.nextInt(), in.nextInt());
            }
        }
        out.close();
    }
    
    private static void setup() {
        G.addEdge(1, 6);
        G.addEdge(2, 6);
        G.addEdge(3, 4);
        G.addEdge(3, 5);
        G.addEdge(3, 6);
        G.addEdge(3, 15);
        G.addEdge(4, 5);
        G.addEdge(4, 6);
        G.addEdge(5, 6);
        G.addEdge(6, 7);
        G.addEdge(7, 8);
        G.addEdge(8, 9);
        G.addEdge(9, 10);
        G.addEdge(9, 12);
        G.addEdge(10, 11);
        G.addEdge(11, 12);
        G.addEdge(12, 13);
        G.addEdge(13, 14);
        G.addEdge(13, 15);
        G.addEdge(16, 17);
        G.addEdge(16, 18);
        G.addEdge(17, 18);
    }
    
    private static void bfs(int s, int f) {
        boolean[] marked = new boolean[G.V()];
        int[] distTo = new int[G.V()];
        Queue<Integer> q = o.new Queue<Integer>();
        for (int v = 0; v < G.V(); v++)
            distTo[v] = Integer.MAX_VALUE;
        distTo[s] = 0;
        marked[s] = true;
        q.enqueue(s);

        while (!q.isEmpty()) {
            int v = q.dequeue();
            if (v == f) {
                out.println(distTo[f]);
                return;
            }
            for (int w : G.adj(v)) {
                if (!marked[w]) {
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.enqueue(w);
                }
            }
        }
        out.println("Not connected");
    }
}
