package cco14p2_king_gruff;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.Stack;

public class CCO14P2 {
	private static CCO14P2 o = new CCO14P2();
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
	
	public class DirectedWeightedEdge { 
	    private final int v;
	    private final int w;
	    private final double weight;
	    private final int cost;

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
	    public DirectedWeightedEdge(int v, int w, double weight, int cost) {
	        if (v < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
	        if (w < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
	        if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
	        this.v = v;
	        this.w = w;
	        this.weight = weight;
	        this.cost = cost;
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
	    
	    public int cost() {
	    	return cost;
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
	
	public class DijkstraSP {
	    private double[] distTo;          // distTo[v] = distance  of shortest s->v path
	    private DirectedWeightedEdge[] edgeTo;    // edgeTo[v] = last edge on shortest s->v path
	    private IndexMinPQ<Double> pq;    // priority queue of vertices

	    /**
	     * Computes a shortest-paths tree from the source vertex {@code s} to every other
	     * vertex in the edge-weighted digraph {@code G}.
	     *
	     * @param  G the edge-weighted digraph
	     * @param  s the source vertex
	     * @throws IllegalArgumentException if an edge weight is negative
	     * @throws IllegalArgumentException unless {@code 0 <= s < V}
	     */
	    public DijkstraSP(WeightedDigraph G, int s) {
	        for (DirectedWeightedEdge e : G.edges()) {
	            if (e.weight() < 0)
	                throw new IllegalArgumentException("edge " + e + " has negative weight");
	        }

	        distTo = new double[G.V()];
	        edgeTo = new DirectedWeightedEdge[G.V()];

	        validateVertex(s);

	        for (int v = 0; v < G.V(); v++)
	            distTo[v] = 1e9;
	        distTo[s] = 0.0;

	        // relax vertices in order of distance from s
	        pq = new IndexMinPQ<Double>(G.V());
	        pq.insert(s, distTo[s]);
	        while (!pq.isEmpty()) {
	            int v = pq.delMin();
	            for (DirectedWeightedEdge e : G.adj(v))
	                relax(e);
	        }

	    }

	    // relax edge e and update pq if changed
	    private void relax(DirectedWeightedEdge e) {
	        int v = e.from(), w = e.to();
	        if (distTo[w] > distTo[v] + e.weight()) {
	            distTo[w] = distTo[v] + e.weight();
	            edgeTo[w] = e;
	            if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
	            else                pq.insert(w, distTo[w]);
	        }
	    }

	    /**
	     * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
	     * @param  v the destination vertex
	     * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
	     *         {@code Double.POSITIVE_INFINITY} if no such path
	     * @throws IllegalArgumentException unless {@code 0 <= v < V}
	     */
	    public double distTo(int v) {
	        validateVertex(v);
	        return distTo[v];
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
	        validateVertex(v);
	        return distTo[v] < 1e9;
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
	        validateVertex(v);
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
	        validateVertex(v);
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
	        if (distTo[s] != 0.0 || edgeTo[s] != null) {
	            System.err.println("distTo[s] and edgeTo[s] inconsistent");
	            return false;
	        }
	        for (int v = 0; v < G.V(); v++) {
	            if (v == s) continue;
	            if (edgeTo[v] == null && distTo[v] != 1e9) {
	                System.err.println("distTo[] and edgeTo[] inconsistent");
	                return false;
	            }
	        }

	        // check that all edges e = v->w satisfy distTo[w] <= distTo[v] + e.weight()
	        for (int v = 0; v < G.V(); v++) {
	            for (DirectedWeightedEdge e : G.adj(v)) {
	                int w = e.to();
	                if (distTo[v] + e.weight() < distTo[w]) {
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
	            if (distTo[v] + e.weight() != distTo[w]) {
	                System.err.println("edge " + e + " on shortest path not tight");
	                return false;
	            }
	        }
	        return true;
	    }

	    // throw an IllegalArgumentException unless {@code 0 <= v < V}
	    private void validateVertex(int v) {
	        int V = distTo.length;
	        if (v < 0 || v >= V)
	            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
	    }
	}
	
	public class ComparablePair<Item extends Comparable<Item>, Item2 extends Comparable<Item2>> implements Comparable<ComparablePair<Item, Item2>>{
		private Item first;
		private Item2 second;
		
		public ComparablePair(Item first, Item2 second) {
			this.first = first;
			this.second = second;
		}
		
		public Item getFirst() {
			return this.first;
		}

		public void setFirst(Item first) {
			this.first = first;
		}

		public Item2 getSecond() {
			return this.second;
		}

		public void setSecond(Item2 second) {
			this.second = second;
		}
		
		public void set(Item first, Item2 second) {
			this.first = first;
			this.second = second;
		}
		
	    @Override
	    public int hashCode() {
	        return 31 * (first.hashCode() + second.hashCode());
	    }
		
	    @Override
		public boolean equals(Object o) {
	    	if (o == this) return true;
	        if (!(o instanceof ComparablePair)) {
	            return false;
	        }
	        ComparablePair p = (ComparablePair) o;
			return p.first.equals(first) && p.second.equals(second);
		}

		@Override
		public int compareTo(ComparablePair<Item, Item2> p) {
			if (first.compareTo(p.first) != 0) return first.compareTo(p.first);
			return (second.compareTo(p.second));
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int M = in.nextInt();
		int A = in.nextInt() - 1;
		int B = in.nextInt() - 1;
		WeightedDigraph GA = o.new WeightedDigraph(N);
		WeightedDigraph GB = o.new WeightedDigraph(N);
		ArrayList<ComparablePair<Integer, Integer>> all = new ArrayList<ComparablePair<Integer, Integer>>();
		for (int i = 0; i < M; i++) {
			int x = in.nextInt() - 1;
			int y = in.nextInt() - 1;
			int l = in.nextInt();
			int c = in.nextInt();
			GA.addEdge(o.new DirectedWeightedEdge(x, y, l, c));
			GB.addEdge(o.new DirectedWeightedEdge(y, x, l, c));
		}
		DijkstraSP SPA = o.new DijkstraSP(GA, A);
		DijkstraSP SPB = o.new DijkstraSP(GB, B);
		all.add(o.new ComparablePair<Integer, Integer>(0, 0));
		for (int i = 0; i < N; i++) {
			for (DirectedWeightedEdge e: GA.adj(i)) {
				all.add(o.new ComparablePair<Integer, Integer>((int) SPA.distTo(i) + (int) e.weight() + (int) SPB.distTo(e.to()), e.cost()));
			}
		}
		Collections.sort(all);
		for (int i = 1; i < all.size(); i++) {
			all.get(i).second += all.get(i - 1).second;
		}
		int Q = in.nextInt();
		for (int i = 0; i < Q; i++) {
			int D = in.nextInt();
			int low = 0;
			int high = all.size() - 1;
			while (low <= high) {
				int mid = (low + high) / 2;
				if (all.get(mid).first <= D) {
					low = mid + 1;
				} else {
					high = mid - 1;
				}
			}
			if (all.get(high).first < 1e9) {
				out.println(all.get(high).second);
			} else {
				out.println(0);
			}
		}
		out.close();
	}
}
