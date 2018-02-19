import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.Stack;

public class DMOPC14C7P6 {
    private static DMOPC14C7P6 o = new DMOPC14C7P6();
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
    
    public class DijkstraSP {
        private double[] timeTo;          // distTo[v] = distance  of shortest s->v path
        private DirectedWeightedEdge[] edgeTo;    // edgeTo[v] = last edge on shortest s->v path
        private IndexMinPQ<Double> pq;    // priority queue of vertices
        private double t;

        /**
         * Computes a shortest-paths tree from the source vertex {@code s} to every other
         * vertex in the edge-weighted digraph {@code G}.
         *
         * @param  G the edge-weighted digraph
         * @param  s the source vertex
         * @throws IllegalArgumentException if an edge weight is negative
         * @throws IllegalArgumentException unless {@code 0 <= s < V}
         */
        public DijkstraSP(WeightedDigraph G, int s, double t) {
            for (DirectedWeightedEdge e : G.edges()) {
                if (e.weight() < 0)
                    throw new IllegalArgumentException("edge " + e + " has negative weight");
            }

            this.t = t;
            timeTo = new double[G.V()];
            edgeTo = new DirectedWeightedEdge[G.V()];

            for (int v = 0; v < G.V(); v++)
                timeTo[v] = Double.POSITIVE_INFINITY;
            
            for (int r = 0; r < sToI.length; r++) {
                HashMap<Integer, Integer> map = sToI[r];
                Integer st = map.get(s);
                if (st != null) {
                    Double next = schedule[r][st].ceiling(t % 1440);
                     if (next == null) next = schedule[r][st].min();
                     double timeAdded = next - t % 1440;
                     if (timeAdded < 0) timeAdded += 1440;
                    timeTo[s] = Double.min(timeTo[s], timeAdded);
                }
            }

            // relax vertices in order of distance from s
            pq = new IndexMinPQ<Double>(G.V());
            pq.insert(s, timeTo[s]);
            while (!pq.isEmpty()) {
                int v = pq.delMin();
                for (DirectedWeightedEdge e : G.adj(v))
                    relax(e);
            }

        }

        // relax edge e and update pq if changed
        private void relax(DirectedWeightedEdge e) {
            int v = e.from(), w = e.to(), r = (int) e.weight(), s = sToI[r].get(w);
            Integer index = tToI[r][sToI[r].get(v)].get((timeTo[v] + t) % 1440);
            Double next = 0.0;
            Double nextDep = 0.0;
            Double wait = 0.0;
            nextDep = schedule[r][sToI[r].get(v)].ceiling((timeTo[v] + t) % 1440);
            if (nextDep == null) nextDep = schedule[r][sToI[r].get(v)].min();
            if ((edgeTo[v] != null && (edgeTo[v].weight() != r) || index == null)) {
                wait = nextDep - (timeTo[v] + t) % 1440;
                if (wait < 0) wait += 1440;
                next = schedule[r][s].ceiling((timeTo[v] + t) % 1440);
                if (next == null) next = schedule[r][s].min();
            } else {
                next = iToT[r][s].get(index);
            }
            double timeAdded = next - nextDep;
            if (timeAdded < 0) timeAdded += 1440;
            timeAdded += wait;
            if (timeTo[w] > timeAdded + timeTo[v]) {
                timeTo[w] = timeAdded + timeTo[v];
                edgeTo[w] = e;
                if (pq.contains(w)) pq.decreaseKey(w, timeTo[w]);
                else                pq.insert(w, timeTo[w]);
            }
        }

        /**
         * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
         * @param  v the destination vertex
         * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
         *         {@code Double.POSITIVE_INFINITY} if no such path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public double timeTo(int v) {
            return timeTo[v];
        }

        /**
         * Returns true if there is a path from the source vertex {@code s} to vertex {@code v}.
         *
         * @param  v the destination vertex
         * @return {@code true} if there is a path from the source vertex
         *         {@code s} to vertex {@code v}; {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public boolean hasPathTo(int v) {
            return timeTo[v] < Double.POSITIVE_INFINITY;
        }

        /**
         * Returns a shortest path from the source vertex {@code s} to vertex {@code v}.
         *
         * @param  v the destination vertex
         * @return a shortest path from the source vertex {@code s} to vertex {@code v}
         *         as an iterable of edges, and {@code null} if no such path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<DirectedWeightedEdge> pathTo(int v) {
            if (!hasPathTo(v)) return null;
            Stack<DirectedWeightedEdge> path = new Stack<DirectedWeightedEdge>();
            for (DirectedWeightedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
                path.push(e);
            }
            return path;
        }
        
        /**
         * Returns a shortest path from the source vertex {@code s} to vertex {@code v}.
         *
         * @param  v the destination vertex
         * @return a shortest path from the source vertex {@code s} to vertex {@code v}
         *         as an ArrayList of edges, and {@code null} if no such path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public ArrayList<DirectedWeightedEdge> pathList(int v) {
            if (!hasPathTo(v)) return null;
            Stack<DirectedWeightedEdge> path = new Stack<DirectedWeightedEdge>();
            for (DirectedWeightedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
                path.push(e);
            }
            ArrayList<DirectedWeightedEdge> list = new ArrayList<DirectedWeightedEdge>();
            while (!path.isEmpty()) {
                list.add(path.pop());
            }
            return list;
        }


        // check optimality conditions:
        // (i) for all edges e:            distTo[e.to()] <= distTo[e.from()] + e.weight()
        // (ii) for all edge e on the SPT: distTo[e.to()] == distTo[e.from()] + e.weight()
        private boolean check(WeightedDigraph G, int s) {

            // check that edge weights are nonnegative
            for (DirectedWeightedEdge e : G.edges()) {
                if (e.weight() < 0) {
                    System.err.println("negative edge weight detected");
                    return false;
                }
            }

            // check that distTo[v] and edgeTo[v] are consistent
            if (timeTo[s] != 0.0 || edgeTo[s] != null) {
                System.err.println("distTo[s] and edgeTo[s] inconsistent");
                return false;
            }
            for (int v = 0; v < G.V(); v++) {
                if (v == s) continue;
                if (edgeTo[v] == null && timeTo[v] != Double.POSITIVE_INFINITY) {
                    System.err.println("distTo[] and edgeTo[] inconsistent");
                    return false;
                }
            }

            // check that all edges e = v->w satisfy distTo[w] <= distTo[v] + e.weight()
            for (int v = 0; v < G.V(); v++) {
                for (DirectedWeightedEdge e : G.adj(v)) {
                    int w = e.to();
                    if (timeTo[v] + e.weight() < timeTo[w]) {
                        System.err.println("edge " + e + " not relaxed");
                        return false;
                    }
                }
            }

            // check that all edges e = v->w on SPT satisfy distTo[w] == distTo[v] + e.weight()
            for (int w = 0; w < G.V(); w++) {
                if (edgeTo[w] == null) continue;
                DirectedWeightedEdge e = edgeTo[w];
                int v = e.from();
                if (w != e.to()) return false;
                if (timeTo[v] + e.weight() != timeTo[w]) {
                    System.err.println("edge " + e + " on shortest path not tight");
                    return false;
                }
            }
            return true;
        }
    }
    
    public class AVLTreeSet<Value extends Comparable<Value>> {

        /**
         * The root node.
         */
        private Node root;

        /**
         * This class represents an inner node of the AVL tree.
         */
        private class Node {
            private Value val;       // the value
            private int height;      // height of the subtree
            private int size;        // number of nodes in subtree
            private Node left;       // left subtree
            private Node right;      // right subtree

            public Node(Value val, int height, int size) {
                this.val = val;
                this.size = size;
                this.height = height;
            }
        }

        /**
         * Initializes an empty symbol table.
         */
        public AVLTreeSet() {
        }

        /**
         * Checks if the symbol table is empty.
         * 
         * @return {@code true} if the symbol table is empty.
         */
        public boolean isEmpty() {
            return root == null;
        }

        /**
         * Returns the number values in the symbol table.
         * 
         * @return the number values pairs in the symbol table
         */
        public int size() {
            return size(root);
        }

        /**
         * Returns the number of nodes in the subtree.
         * 
         * @param x the subtree
         * 
         * @return the number of nodes in the subtree
         */
        private int size(Node x) {
            if (x == null) return 0;
            return x.size;
        }

        /**
         * Returns the height of the internal AVL tree. It is assumed that the
         * height of an empty tree is -1 and the height of a tree with just one node
         * is 0.
         * 
         * @return the height of the internal AVL tree
         */
        public int height() {
            return height(root);
        }

        /**
         * Returns the height of the subtree.
         * 
         * @param x the subtree
         * 
         * @return the height of the subtree.
         */
        private int height(Node x) {
            if (x == null) return -1;
            return x.height;
        }

        /**
         * Checks if the symbol table contains the given value.
         * 
         * @param val the value
         * @return {@code true} if the symbol table contains {@code val}
         *         and {@code false} otherwise
         * @throws IllegalArgumentException if {@code val} is {@code null}
         */
        public boolean contains(Value val) {
            return contains(root, val);
        }

        // auxiliary method for contains
        private boolean contains(Node n, Value val) {
            if (n == null)
                return false;
            else if (val.compareTo(n.val) < 0)
                return contains(n.left, val);
            else if (val.compareTo(n.val) > 0)
                return contains(n.right, val);
            return true;
        }

        /**
         * Inserts the specified value into the symbol table, allowing for duplicates.
         * Deletes the specified values from this symbol table if the specified value is {@code null}.
         * 
         * @param val the value
         * @throws IllegalArgumentException if {@code key} is {@code null}
         */
        public void add(Value val) {
            if (val == null) {
                delete(val);
                return;
            }
            root = add(root, val);
        }
        
        /**
         * Inserts the specified value into the symbol table, allowing for duplicates.
         * Deletes the specified value from this symbol table if the specified value is {@code null}.
         * 
         * @param x the subtree
         * @param val the value
         * @return the subtree
         */
        private Node add(Node x, Value val) {
            if (x == null) return new Node(val, 0, 1);
            int cmp = val.compareTo(x.val);
            if (cmp < 0) {
                x.left = add(x.left, val);
            }
            else {
                x.right = add(x.right, val);
            }
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            return balance(x);
        }

        /**
         * Restores the AVL tree property of the subtree.
         * 
         * @param x the subtree
         * @return the subtree with restored AVL property
         */
        private Node balance(Node x) {
            if (balanceFactor(x) < -1) {
                if (balanceFactor(x.right) > 0) {
                    x.right = rotateRight(x.right);
                }
                x = rotateLeft(x);
            }
            else if (balanceFactor(x) > 1) {
                if (balanceFactor(x.left) < 0) {
                    x.left = rotateLeft(x.left);
                }
                x = rotateRight(x);
            }
            return x;
        }

        /**
         * Returns the balance factor of the subtree. The balance factor is defined
         * as the difference in height of the left subtree and right subtree, in
         * this order. Therefore, a subtree with a balance factor of -1, 0 or 1 has
         * the AVL property since the heights of the two child subtrees differ by at
         * most one.
         * 
         * @param x the subtree
         * @return the balance factor of the subtree
         */
        private int balanceFactor(Node x) {
            return height(x.left) - height(x.right);
        }

        /**
         * Rotates the given subtree to the right.
         * 
         * @param x the subtree
         * @return the right rotated subtree
         */
        private Node rotateRight(Node x) {
            Node y = x.left;
            x.left = y.right;
            y.right = x;
            y.size = x.size;
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            y.height = 1 + Math.max(height(y.left), height(y.right));
            return y;
        }

        /**
         * Rotates the given subtree to the left.
         * 
         * @param x the subtree
         * @return the left rotated subtree
         */
        private Node rotateLeft(Node x) {
            Node y = x.right;
            x.right = y.left;
            y.left = x;
            y.size = x.size;
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            y.height = 1 + Math.max(height(y.left), height(y.right));
            return y;
        }

        /**
         * Removes the specified value from the symbol table
         * 
         * @param val the value
         * @throws IllegalArgumentException if {@code key} is {@code null}
         */
        public void delete(Value val) {
            if (val == null) throw new IllegalArgumentException("argument to delete() is null");
            if (!contains(val)) return;
            root = delete(root, val);
        }

        /**
         * Removes the specified value and its associated value from the given
         * subtree.
         * 
         * @param x the subtree
         * @param val the value
         * @return the updated subtree
         */
        private Node delete(Node x, Value val) {
            int cmp = val.compareTo(x.val);
            if (cmp < 0) {
                x.left = delete(x.left, val);
            }
            else if (cmp > 0) {
                x.right = delete(x.right, val);
            }
            else {
                if (x.left == null) {
                    return x.right;
                }
                else if (x.right == null) {
                    return x.left;
                }
                else {
                    Node y = x;
                    x = min(y.right);
                    x.right = deleteMin(y.right);
                    x.left = y.left;
                }
            }
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            return balance(x);
        }

        /**
         * Removes the smallest value from the symbol table.
         * 
         * @throws NoSuchElementException if the symbol table is empty
         */
        public void deleteMin() {
            if (isEmpty()) throw new NoSuchElementException("called deleteMin() with empty symbol table");
            root = deleteMin(root);
        }

        /**
         * Removes the smallest value from the given subtree.
         * 
         * @param x the subtree
         * @return the updated subtree
         */
        private Node deleteMin(Node x) {
            if (x.left == null) return x.right;
            x.left = deleteMin(x.left);
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            return balance(x);
        }

        /**
         * Removes the largest key and associated value from the symbol table.
         * 
         * @throws NoSuchElementException if the symbol table is empty
         */
        public void deleteMax() {
            if (isEmpty()) throw new NoSuchElementException("called deleteMax() with empty symbol table");
            root = deleteMax(root);
        }

        /**
         * Removes the largest key and associated value from the given subtree.
         * 
         * @param x the subtree
         * @return the updated subtree
         */
        private Node deleteMax(Node x) {
            if (x.right == null) return x.left;
            x.right = deleteMax(x.right);
            x.size = 1 + size(x.left) + size(x.right);
            x.height = 1 + Math.max(height(x.left), height(x.right));
            return balance(x);
        }

        /**
         * Returns the smallest value in the symbol table.
         * 
         * @return the smallest value in the symbol table
         * @throws NoSuchElementException if the symbol table is empty
         */
        public Value min() {
            if (isEmpty()) throw new NoSuchElementException("called min() with empty symbol table");
            return min(root).val;
        }

        /**
         * Returns the node with the smallest value in the subtree.
         * 
         * @param x the subtree
         * @return the node with the smallest value in the subtree
         */
        private Node min(Node x) {
            if (x.left == null) return x;
            return min(x.left);
        }

        /**
         * Returns the largest value in the symbol table.
         * 
         * @return the largest value in the symbol table
         * @throws NoSuchElementException if the symbol table is empty
         */
        public Value max() {
            if (isEmpty()) throw new NoSuchElementException("called max() with empty symbol table");
            return max(root).val;
        }

        /**
         * Returns the node with the largest value in the subtree.
         * 
         * @param x the subtree
         * @return the node with the largest value in the subtree
         */
        private Node max(Node x) {
            if (x.right == null) return x;
            return max(x.right);
        }

        /**
         * Returns the largest value in the symbol table less than or equal to
         * {@code val}.
         * 
         * @param val the value
         * @return the largest value in the symbol table less than or equal to
         *         {@code val}
         * @throws NoSuchElementException if the symbol table is empty
         * @throws IllegalArgumentException if {@code val} is {@code null}
         */
        public Value floor(Value val) {
            if (val == null) throw new IllegalArgumentException("argument to floor() is null");
            if (isEmpty()) throw new NoSuchElementException("called floor() with empty symbol table");
            Node x = floor(root, val);
            if (x == null) return null;
            else return x.val;
        }

        /**
         * Returns the node in the subtree with the largest value less than or equal
         * to the given key.
         * 
         * @param x the subtree
         * @param val the value
         * @return the node in the subtree with the largest value less than or equal
         *         to the given value
         */
        private Node floor(Node x, Value val) {
            if (x == null) return null;
            int cmp = val.compareTo(x.val);
            if (cmp == 0) return x;
            if (cmp < 0) return floor(x.left, val);
            Node y = floor(x.right, val);
            if (y != null) return y;
            else return x;
        }

        /**
         * Returns the smallest value in the symbol table greater than or equal to
         * {@code val}.
         * 
         * @param val the value
         * @return the smallest value in the symbol table greater than or equal to
         *         {@code val}
         * @throws NoSuchElementException if the symbol table is empty
         * @throws IllegalArgumentException if {@code val} is {@code null}
         */
        public Value ceiling(Value val) {
            if (val == null) throw new IllegalArgumentException("argument to ceiling() is null");
            if (isEmpty()) throw new NoSuchElementException("called ceiling() with empty symbol table");
            Node x = ceiling(root, val);
            if (x == null) return null;
            else return x.val;
        }

        /**
         * Returns the node in the subtree with the smallest value greater than or
         * equal to the given value.
         * 
         * @param x the subtree
         * @param val the value
         * @return the node in the subtree with the smallest value greater than or
         *         equal to the given value
         */
        private Node ceiling(Node x, Value val) {
            if (x == null) return null;
            int cmp = val.compareTo(x.val);
            if (cmp == 0) return x;
            if (cmp > 0) return ceiling(x.right, val);
            Node y = ceiling(x.left, val);
            if (y != null) return y;
            else return x;
        }

        /**
         * Returns the kth smallest key in the symbol table.
         * 
         * @param k the order statistic
         * @return the kth smallest key in the symbol table
         * @throws IllegalArgumentException unless {@code k} is between 0 and
         *             {@code size() -1 }
         */
        public Value select(int k) {
            if (k < 0 || k >= size()) throw new IllegalArgumentException("k is not in range 0-" + (size() - 1));
            return select(root, k + 1);
        }

        private Value select(Node x, int k) {
            if (x == null) {
                return null;
            }

            int rank = size(x.left) + 1;

            if (rank == k) {
                return x.val;
            } else if (rank > k) {
                return select(x.left, k);
            } else {
                return select(x.right, k - rank);
            }
        }

        /**
         * Returns the number of values in the symbol table strictly less than
         * {@code val}.
         * 
         * @param val the value
         * @return the number of values in the symbol table strictly less than
         *         {@code val}
         * @throws IllegalArgumentException if {@code val} is {@code null}
         */
        public int rank(Value val) {
            if (val == null) throw new IllegalArgumentException("argument to rank() is null");
            return (rank(root, val)) - 1;
        }

        /**
         * Returns the number of values in the subtree less than val.
         * 
         * @param val the value
         * @param x the subtree
         * @return the number of values in the subtree less than val
         */
        private int rank(Node n, Value val) {
            if (n == null) {
                return 0;
            }

            if (n.val.compareTo(val) == 0) {
                int temp = rank(n.left, val);
                if (temp == 0) {
                    return size(n.left) + 1;
                } else {
                    return temp;
                }
            } else if (val.compareTo(n.val) < 0) {
                return rank(n.left, val);
            } else {
                int temp = rank(n.right, val);
                if (temp == 0) {
                    return temp;
                } else {
                    return size(n.left) + 1 + temp;
                }

            }
        }

        /**
         * Returns all values in the symbol table.
         * 
         * @return all values in the symbol table
         */
        public Iterable<Value> values() {
            return valuesInOrder();
        }

        /**
         * Returns all values in the symbol table following an in-order traversal.
         * 
         * @return all values in the symbol table following an in-order traversal
         */
        public Iterable<Value> valuesInOrder() {
            Queue<Value> queue = new Queue<Value>();
            valuesInOrder(root, queue);
            return queue;
        }

        /**
         * Adds the values in the subtree to queue following an in-order traversal.
         * 
         * @param x the subtree
         * @param queue the queue
         */
        private void valuesInOrder(Node x, Queue<Value> queue) {
            if (x == null) return;
            valuesInOrder(x.left, queue);
            queue.enqueue(x.val);
            valuesInOrder(x.right, queue);
        }

        /**
         * Returns all values in the symbol table following a level-order traversal.
         * 
         * @return all values in the symbol table following a level-order traversal.
         */
        public Iterable<Value> valuesLevelOrder() {
            Queue<Value> queue = new Queue<Value>();
            if (!isEmpty()) {
                Queue<Node> queue2 = new Queue<Node>();
                queue2.enqueue(root);
                while (!queue2.isEmpty()) {
                    Node x = queue2.dequeue();
                    queue.enqueue(x.val);
                    if (x.left != null) {
                        queue2.enqueue(x.left);
                    }
                    if (x.right != null) {
                        queue2.enqueue(x.right);
                    }
                }
            }
            return queue;
        }

        /**
         * Returns all values in the symbol table in the given range.
         * 
         * @param lo the lowest value
         * @param hi the highest value
         * @return all value in the symbol table between {@code lo} (inclusive)
         *         and {@code hi} (exclusive)
         * @throws IllegalArgumentException if either {@code lo} or {@code hi}
         *             is {@code null}
         */
        public Iterable<Value> values(Value lo, Value hi) {
            if (lo == null) throw new IllegalArgumentException("first argument to values() is null");
            if (hi == null) throw new IllegalArgumentException("second argument to values() is null");
            Queue<Value> queue = new Queue<Value>();
            values(root, queue, lo, hi);
            return queue;
        }

        /**
         * Adds the values between {@code lo} and {@code hi} in the subtree
         * to the {@code queue}.
         * 
         * @param x the subtree
         * @param queue the queue
         * @param lo the lowest value
         * @param hi the highest value
         */
        private void values(Node x, Queue<Value> queue, Value lo, Value hi) {
            if (x == null) return;
            int cmplo = lo.compareTo(x.val);
            int cmphi = hi.compareTo(x.val);
            if (cmplo < 0) values(x.left, queue, lo, hi);
            if (cmplo <= 0 && cmphi >= 0) queue.enqueue(x.val);
            if (cmphi > 0) values(x.right, queue, lo, hi);
        }

        /**
         * Returns the number of values in the symbol table in the given range.
         * 
         * @param lo minimum endpoint
         * @param hi maximum endpoint
         * @return the number of values in the symbol table between {@code lo}
         *         (inclusive) and {@code hi} (exclusive)
         * @throws IllegalArgumentException if either {@code lo} or {@code hi}
         *             is {@code null}
         */
        public int size(Value lo, Value hi) {
            if (lo == null) throw new IllegalArgumentException("first argument to size() is null");
            if (hi == null) throw new IllegalArgumentException("second argument to size() is null");
            if (lo.compareTo(hi) > 0) return 0;
            if (contains(hi)) return rank(hi) - rank(lo) + 1;
            else return rank(hi) - rank(lo);
        }

    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    private static AVLTreeSet<Double>[][] schedule;
    private static HashMap<Double, Integer>[][] tToI;
    private static HashMap<Integer, Double>[][] iToT;
    private static HashMap<Integer, Integer>[] sToI;
    
    public static void main(String[] args) throws IOException {
        int S = in.nextInt();
        int R = in.nextInt();
        int U = in.nextInt() - 1;
        int V = in.nextInt() - 1;
        int T = in.nextInt();
        int Q  = 0;
        WeightedDigraph G = o.new WeightedDigraph(S);
        sToI = new HashMap[R];
        schedule = new AVLTreeSet[R][];
        tToI = new HashMap[R][];
        iToT = new HashMap[R][];
        for (int i = 0; i < R; i++) {
            int sr = in.nextInt();
            Q += sr;
            schedule[i] = new AVLTreeSet[sr];
            tToI[i] = new HashMap[sr];
            iToT[i] = new HashMap[sr];
            sToI[i] = new HashMap<Integer, Integer>();
            int last = 0;
            for (int j = 0; j < sr; j++) {
                schedule[i][j] = o.new AVLTreeSet<Double>();
                tToI[i][j] = new HashMap<Double, Integer>();
                iToT[i][j] = new HashMap<Integer, Double>();
                int cur = in.nextInt() - 1;
                sToI[i].put(cur, j);
                if (j != 0) {
                    G.addEdge(o.new DirectedWeightedEdge(last, cur, i));
                }
                last = cur;
            }
        }
        for (int i = 0; i < Q; i++) {
            int r = in.nextInt() - 1;
            int s = sToI[r].get(in.nextInt() - 1);
            int tn = in.nextInt();
            for (int j = 0; j < tn; j++) {
                double t = in.nextDouble();
                schedule[r][s].add(t);
                tToI[r][s].put(t, j);
                iToT[r][s].put(j, t);
            }
        }
        DijkstraSP sp = o.new DijkstraSP(G, U, T);
        double time = sp.timeTo(V);
        if (time >= Integer.MAX_VALUE) out.println("stay home");
        else out.println((int) time);
        out.close();
    }
}
