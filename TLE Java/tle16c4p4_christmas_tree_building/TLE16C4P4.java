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

public class TLE16C4P4 {
    private static TLE16C4P4 o = new TLE16C4P4();
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
    
    public class IndexMinPQ<Key extends Comparable<Key>> implements Iterable<Integer> {
        private int maxN;        // maximum number of elements on PQ
        private int n;           // number of elements on PQ
        private int[] pq;        // binary heap using 1-based indexing
        private int[] qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
        private Key[] keys;      // keys[i] = priority of i

        /**
         * Initializes an empty indexed priority queue with indices between {@code 0}
         * and {@code maxN - 1}.
         * @param  maxN the keys on this priority queue are index from {@code 0}
         *         {@code maxN - 1}
         * @throws IllegalArgumentException if {@code maxN < 0}
         */
        public IndexMinPQ(int maxN) {
            if (maxN < 0) throw new IllegalArgumentException();
            this.maxN = maxN;
            n = 0;
            keys = (Key[]) new Comparable[maxN + 1];    // make this of length maxN??
            pq   = new int[maxN + 1];
            qp   = new int[maxN + 1];                   // make this of length maxN??
            for (int i = 0; i <= maxN; i++)
                qp[i] = -1;
        }

        /**
         * Returns true if this priority queue is empty.
         *
         * @return {@code true} if this priority queue is empty;
         *         {@code false} otherwise
         */
        public boolean isEmpty() {
            return n == 0;
        }

        /**
         * Is {@code i} an index on this priority queue?
         *
         * @param  i an index
         * @return {@code true} if {@code i} is an index on this priority queue;
         *         {@code false} otherwise
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         */
        public boolean contains(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            return qp[i] != -1;
        }

        /**
         * Returns the number of keys on this priority queue.
         *
         * @return the number of keys on this priority queue
         */
        public int size() {
            return n;
        }

        /**
         * Associates key with index {@code i}.
         *
         * @param  i an index
         * @param  key the key to associate with index {@code i}
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if there already is an item associated
         *         with index {@code i}
         */
        public void insert(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (contains(i)) throw new IllegalArgumentException("index is already in the priority queue");
            n++;
            qp[i] = n;
            pq[n] = i;
            keys[i] = key;
            swim(n);
        }

        /**
         * Returns an index associated with a minimum key.
         *
         * @return an index associated with a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public int minIndex() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return pq[1];
        }

        /**
         * Returns a minimum key.
         *
         * @return a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public Key minKey() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return keys[pq[1]];
        }

        /**
         * Removes a minimum key and returns its associated index.
         * @return an index associated with a minimum key
         * @throws NoSuchElementException if this priority queue is empty
         */
        public int delMin() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            int min = pq[1];
            exch(1, n--);
            sink(1);
            assert min == pq[n+1];
            qp[min] = -1;        // delete
            keys[min] = null;    // to help with garbage collection
            pq[n+1] = -1;        // not needed
            return min;
        }

        /**
         * Returns the key associated with index {@code i}.
         *
         * @param  i the index of the key to return
         * @return the key associated with index {@code i}
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public Key keyOf(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            else return keys[i];
        }

        /**
         * Change the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to change
         * @param  key change the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void changeKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            keys[i] = key;
            swim(qp[i]);
            sink(qp[i]);
        }

        /**
         * Change the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to change
         * @param  key change the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @deprecated Replaced by {@code changeKey(int, Key)}.
         */
        @Deprecated
        public void change(int i, Key key) {
            changeKey(i, key);
        }

        /**
         * Decrease the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to decrease
         * @param  key decrease the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if {@code key >= keyOf(i)}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void decreaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) <= 0)
                throw new IllegalArgumentException("Calling decreaseKey() with given argument would not strictly decrease the key");
            keys[i] = key;
            swim(qp[i]);
        }

        /**
         * Increase the key associated with index {@code i} to the specified value.
         *
         * @param  i the index of the key to increase
         * @param  key increase the key associated with index {@code i} to this key
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws IllegalArgumentException if {@code key <= keyOf(i)}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void increaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) >= 0)
                throw new IllegalArgumentException("Calling increaseKey() with given argument would not strictly increase the key");
            keys[i] = key;
            sink(qp[i]);
        }

        /**
         * Remove the key associated with index {@code i}.
         *
         * @param  i the index of the key to remove
         * @throws IndexOutOfBoundsException unless {@code 0 <= i < maxN}
         * @throws NoSuchElementException no key is associated with index {@code i}
         */
        public void delete(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            int index = qp[i];
            exch(index, n--);
            swim(index);
            sink(index);
            keys[i] = null;
            qp[i] = -1;
        }


       /***************************************************************************
        * General helper functions.
        ***************************************************************************/
        private boolean greater(int i, int j) {
            return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
        }

        private void exch(int i, int j) {
            int swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }


       /***************************************************************************
        * Heap helper functions.
        ***************************************************************************/
        private void swim(int k) {
            while (k > 1 && greater(k/2, k)) {
                exch(k, k/2);
                k = k/2;
            }
        }

        private void sink(int k) {
            while (2*k <= n) {
                int j = 2*k;
                if (j < n && greater(j, j+1)) j++;
                if (!greater(k, j)) break;
                exch(k, j);
                k = j;
            }
        }


       /***************************************************************************
        * Iterators.
        ***************************************************************************/

        /**
         * Returns an iterator that iterates over the keys on the
         * priority queue in ascending order.
         * The iterator doesn't implement {@code remove()} since it's optional.
         *
         * @return an iterator that iterates over the keys in ascending order
         */
        public Iterator<Integer> iterator() { return new HeapIterator(); }

        private class HeapIterator implements Iterator<Integer> {
            // create a new pq
            private IndexMinPQ<Key> copy;

            // add all elements to copy of heap
            // takes linear time since already in heap order so no keys move
            public HeapIterator() {
                copy = new IndexMinPQ<Key>(pq.length - 1);
                for (int i = 1; i <= n; i++)
                    copy.insert(pq[i], keys[pq[i]]);
            }

            public boolean hasNext()  { return !copy.isEmpty();                     }
            public void remove()      { throw new UnsupportedOperationException();  }

            public Integer next() {
                if (!hasNext()) throw new NoSuchElementException();
                return copy.delMin();
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

    public class WeightedEdge implements Comparable<WeightedEdge> { 

        private final int v;
        private final int w;
        private final double weight;

        /**
         * Initializes an edge between vertices {@code v} and {@code w} of
         * the given {@code weight}.
         *
         * @param  v one vertex
         * @param  w the other vertex
         * @param  weight the weight of this edge
         * @throws IllegalArgumentException if either {@code v} or {@code w} 
         *         is a negative integer
         * @throws IllegalArgumentException if {@code weight} is {@code NaN}
         */
        public WeightedEdge(int v, int w, double weight) {
            if (v < 0) throw new IllegalArgumentException("vertex index must be a nonnegative integer");
            if (w < 0) throw new IllegalArgumentException("vertex index must be a nonnegative integer");
            if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
            this.v = v;
            this.w = w;
            this.weight = weight;
        }

        /**
         * Returns the weight of this edge.
         *
         * @return the weight of this edge
         */
        public double weight() {
            return weight;
        }

        /**
         * Returns either endpoint of this edge.
         *
         * @return either endpoint of this edge
         */
        public int either() {
            return v;
        }

        /**
         * Returns the endpoint of this edge that is different from the given vertex.
         *
         * @param  vertex one endpoint of this edge
         * @return the other endpoint of this edge
         * @throws IllegalArgumentException if the vertex is not one of the
         *         endpoints of this edge
         */
        public int other(int vertex) {
            if      (vertex == v) return w;
            else if (vertex == w) return v;
            else throw new IllegalArgumentException("Illegal endpoint");
        }

        /**
         * Compares two edges by weight.
         * Note that {@code compareTo()} is not consistent with {@code equals()},
         * which uses the reference equality implementation inherited from {@code Object}.
         *
         * @param  that the other edge
         * @return a negative integer, zero, or positive integer depending on whether
         *         the weight of this is less than, equal to, or greater than the
         *         argument edge
         */
        @Override
        public int compareTo(WeightedEdge that) {
            return Double.compare(this.weight, that.weight);
        }

        /**
         * Returns a string representation of this edge.
         *
         * @return a string representation of this edge
         */
        public String toString() {
            return String.format("%d-%d %.5f", v, w, weight);
        }
        
        @Override
        public int hashCode() {
            return toString().hashCode();
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof WeightedEdge)) {
                return false;
            }
            WeightedEdge e = (WeightedEdge) o;
            return e.v == v && e.w == w && e.weight() == weight;
        }
    }

    public class WeightedGraph {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private Bag<WeightedEdge>[] adj;
        
        /**
         * Initializes an empty edge-weighted graph with {@code V} vertices and 0 edges.
         *
         * @param  V the number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public WeightedGraph(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices must be nonnegative");
            this.V = V;
            this.E = 0;
            adj = (Bag<WeightedEdge>[]) new Bag[V];
            for (int v = 0; v < V; v++) {
                adj[v] = new Bag<WeightedEdge>();
            }
        }

        /**
         * Initializes a new edge-weighted graph that is a deep copy of {@code G}.
         *
         * @param  G the edge-weighted graph to copy
         */
        public WeightedGraph(WeightedGraph G) {
            this(G.V());
            this.E = G.E();
            for (int v = 0; v < G.V(); v++) {
                // reverse so that adjacency list is in same order as original
                Stack<WeightedEdge> reverse = new Stack<WeightedEdge>();
                for (WeightedEdge e : G.adj[v]) {
                    reverse.push(e);
                }
                for (WeightedEdge e : reverse) {
                    adj[v].add(e);
                }
            }
        }


        /**
         * Returns the number of vertices in this edge-weighted graph.
         *
         * @return the number of vertices in this edge-weighted graph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in this edge-weighted graph.
         *
         * @return the number of edges in this edge-weighted graph
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
         * Adds the undirected edge {@code e} to this edge-weighted graph.
         *
         * @param  e the edge
         * @throws IllegalArgumentException unless both endpoints are between {@code 0} and {@code V-1}
         */
        public void addEdge(WeightedEdge e) {
            int v = e.either();
            int w = e.other(v);
            validateVertex(v);
            validateVertex(w);
            adj[v].add(e);
            adj[w].add(e);
            E++;
        }

        /**
         * Returns the edges incident on vertex {@code v}.
         *
         * @param  v the vertex
         * @return the edges incident on vertex {@code v} as an Iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<WeightedEdge> adj(int v) {
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
         * Returns all edges in this edge-weighted graph.
         * To iterate over the edges in this edge-weighted graph, use foreach notation:
         * {@code for (Edge e : G.edges())}.
         *
         * @return all edges in this edge-weighted graph, as an iterable
         */
        public Iterable<WeightedEdge> edges() {
            Bag<WeightedEdge> list = new Bag<WeightedEdge>();
            for (int v = 0; v < V; v++) {
                int selfLoops = 0;
                for (WeightedEdge e : adj(v)) {
                    if (e.other(v) > v) {
                        list.add(e);
                    }
                    // only add one copy of each self loop (self loops will be consecutive)
                    else if (e.other(v) == v) {
                        if (selfLoops % 2 == 0) list.add(e);
                        selfLoops++;
                    }
                }
            }
            return list;
        }

        /**
         * Returns a string representation of the edge-weighted graph.
         * This method takes time proportional to <em>E</em> + <em>V</em>.
         *
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
         *         followed by the <em>V</em> adjacency lists of edges
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " " + E + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(v + ": ");
                for (WeightedEdge e : adj[v]) {
                    s.append(e + "  ");
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }
    }
    
    public class Vertex {
        public int v;
        public long cost;
        
        public Vertex(int v, long cost) {
            this.v = v;
            this.cost = cost;
        }
    }
    
    private static Vertex dfsTree(int v, int last, long cost) {
        Vertex longest = o.new Vertex(v, cost);
        visited[v] = true;
        for (WeightedEdge e: G.adj(v)) {
            if (e.other(v) == last) continue;
            Vertex w = dfsTree(e.other(v), v, cost + (long) e.weight());
            if (w.cost > longest.cost) longest = w;
        }
        return longest;
    }
    
    private static long dist(int v, int last, long cost) {
        dist[v] = cost;
        long maxDist = 0;
        for (WeightedEdge e: G.adj(v)) {
            if (e.other(v) == last) continue;
            maxDist = Math.max(maxDist, (long) e.weight() + dist(e.other(v), v, cost + (long) e.weight()));
            dist[v] = Math.max(dist[v], maxDist);
        }
        return maxDist;
    }
    
    private static void mark(int v, int last, long cost, long maxDist) {
        if (cost == maxDist) {
            marked[v] = true;
        }
        for (WeightedEdge e: G.adj(v)) {
            if (e.other(v) == last) continue;
            mark(e.other(v), v, cost + (long) e.weight(), maxDist);
            if (marked[e.other(v)]) {
                marked[v] = true;
            }
        }
    }
    
    private static int getRadiusVertex(int v, int last) {
        int vertex = v;
        for (WeightedEdge e: G.adj(v)) {
            if (e.other(v) == last || !marked[e.other(v)]) continue;
            int w = getRadiusVertex(e.other(v), v);
            if (dist[w] < dist[vertex]) {
                vertex = w;
            }
        }
        return vertex;
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    private static WeightedGraph G;
    private static boolean[] visited, marked;
    private static long dist[];
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        int Q = in.nextInt();
        G = o.new WeightedGraph(N);
        visited = new boolean[N];
        marked = new boolean[N];
        dist = new long[N];
        for (int i = 0; i < M; i++) {
            G.addEdge(o.new WeightedEdge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt()));
        }
        if (Q == 1) {
            long ans = -1;
            for (int i = 0; i < N; i++) {
                if (!visited[i]) {
                    Vertex longest = dfsTree(i, -1, 0);
                    longest = dfsTree(longest.v, -1, 0);
                    ans += longest.cost + 1;
                }
            }
            out.println(ans);
        } else {
            long ans = 0;
            long radius1 = 0;
            long radius2 = 0;
            for (int i = 0; i < N; i++) {
                if (!visited[i]) {
                    Vertex longest = dfsTree(i, -1, 0);
                    long maxDist = dfsTree(longest.v, -1, 0).cost;
                    dist(longest.v, -1, 0);
                    mark(longest.v, -1, 0, maxDist);
                    int v = getRadiusVertex(longest.v, -1);
                    if (dist[v] > radius1) {
                        radius2 = radius1;
                        radius1 = dist[v];
                    } else if (dist[v] > radius2) {
                        radius2 = dist[v];
                    }
                }
            }
            ans = Math.max(radius1, radius2 + 1);
            out.println(ans);
        }
        out.close();
    }
}
