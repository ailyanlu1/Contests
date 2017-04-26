package ccc15s4;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.Stack;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class CCC15S4 {
	private static CCC15S4 o = new CCC15S4();
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
	
	public class WeightedEdge implements Comparable<WeightedEdge> { 

	    private final int v;
	    private final int w;
	    private final double weight;
	    private final double damage;

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
	    public WeightedEdge(int v, int w, double weight, double damage) {
	        if (v < 0) throw new IllegalArgumentException("vertex index must be a nonnegative integer");
	        if (w < 0) throw new IllegalArgumentException("vertex index must be a nonnegative integer");
	        if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
	        this.v = v;
	        this.w = w;
	        this.weight = weight;
	        this.damage = damage;
	    }

	    /**
	     * Returns the weight of this edge.
	     *
	     * @return the weight of this edge
	     */
	    public double weight() {
	        return weight;
	    }
	    
	    public double damage() {
	    	return damage;
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
	}
	
	public class EdgeWeightedGraph {
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
	    public EdgeWeightedGraph(int V) {
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
	    public EdgeWeightedGraph(EdgeWeightedGraph G) {
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
	
	public class DijkstraUndirectedSP {
	    private double[][] distTo;          // distTo[v] = distance  of shortest s->v path
	    private WeightedEdge[] edgeTo;            // edgeTo[v] = last edge on shortest s->v path
	    private IndexMinPQ<Double> pq;    // priority queue of vertices

	    /**
	     * Computes a shortest-paths tree from the source vertex {@code s} to every
	     * other vertex in the edge-weighted graph {@code G}.
	     *
	     * @param  G the edge-weighted digraph
	     * @param  s the source vertex
	     * @throws IllegalArgumentException if an edge weight is negative
	     * @throws IllegalArgumentException unless {@code 0 <= s < V}
	     */
	    public DijkstraUndirectedSP(EdgeWeightedGraph G, int s) {
	        for (WeightedEdge e : G.edges()) {
	            if (e.weight() < 0)
	                throw new IllegalArgumentException("edge " + e + " has negative weight");
	        }

	        distTo = new double[G.V()][K];
	        edgeTo = new WeightedEdge[G.V()];

	        for (int v = 0; v < G.V(); v++)
	        	for (int d = 0; d < K; d++)
	        		distTo[v][d] = Double.POSITIVE_INFINITY;
	        distTo[s][0] = 0.0;

	        // relax vertices in order of distance from s
	        pq = new IndexMinPQ<Double>(G.V());
	        pq.insert(s, distTo[s][0]);
	        while (!pq.isEmpty()) {
	            int v = pq.delMin();
	            for (WeightedEdge e : G.adj(v))
	                relax(e, v);
	        }
	    }

	    // relax edge e and update pq if changed
	    private void relax(WeightedEdge e, int v) {
	        int w = e.other(v);
	        int d = (int) e.damage();
	        for (int i = 0; i + d < K; i++) {
		        if (distTo[w][i + d] > distTo[v][i] + e.weight()) {
		            distTo[w][i + d] = distTo[v][i] + e.weight();
		            edgeTo[w] = e;
		            if (pq.contains(w)) pq.changeKey(w, distTo[w][i + d]);
		            else                pq.insert(w, distTo[w][i + d]);
		        }
	    	}
	    }

	    /**
	     * Returns the length of a shortest path between the source vertex {@code s} and
	     * vertex {@code v}.
	     *
	     * @param  v the destination vertex
	     * @return the length of a shortest path between the source vertex {@code s} and
	     *         the vertex {@code v}; {@code Double.POSITIVE_INFINITY} if no such path
	     * @throws IllegalArgumentException unless {@code 0 <= v < V}
	     */
	    public double[] distTo(int v) {
	        return distTo[v];
	    }
	}
	
	public static int K;
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		K = in.nextInt();
		int N = in.nextInt();
		int M = in.nextInt();
		EdgeWeightedGraph G = o.new EdgeWeightedGraph(N+1);
		for (int i = 0; i < M; i++) {
			G.addEdge(o.new WeightedEdge(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt()));
		}
		int A = in.nextInt();
		int B = in.nextInt();
		DijkstraUndirectedSP sp = o.new DijkstraUndirectedSP(G, A);
		double[] distTo = sp.distTo(B);
		int best = Integer.MAX_VALUE;
		for (int d = 0; d < K; d++) {
			best = Integer.min(best, (int) distTo[d]);
		}
		if (best == Integer.MAX_VALUE) best = -1;
		out.println(best);
		out.close();
	}
}
