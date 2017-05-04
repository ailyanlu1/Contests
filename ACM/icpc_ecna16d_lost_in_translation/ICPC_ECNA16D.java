package icpc_ecna16d_lost_in_translation;

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

public class ICPC_ECNA16D {
	private static ICPC_ECNA16D o = new ICPC_ECNA16D();
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

	    /**
	     * Adds the undirected edge {@code e} to this edge-weighted graph.
	     *
	     * @param  e the edge
	     * @throws IllegalArgumentException unless both endpoints are between {@code 0} and {@code V-1}
	     */
	    public void addEdge(WeightedEdge e) {
	        int v = e.either();
	        int w = e.other(v);
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
	
	public class BreadthFirstPaths {
	    private static final int INFINITY = Integer.MAX_VALUE;
	    private int[] distTo;      // distTo[v] = number of edges shortest s-v path
	    private int[] degrees;

	    public BreadthFirstPaths(EdgeWeightedGraph G, int s) {
	        distTo = new int[G.V()];
	        degrees = new int[G.V()];
	        bfs(G, s);
	    }

	    // breadth-first search from a single source
	    private void bfs(EdgeWeightedGraph G, int s) {
	        Queue<Integer> q = new Queue<Integer>();
	        for (int v = 0; v < G.V(); v++) {
	            distTo[v] = INFINITY;
	            degrees[v] = INFINITY;
	        }
	        distTo[s] = 0;
	        degrees[s] = 0;
	        q.enqueue(s);

	        while (!q.isEmpty()) {
	            int v = q.dequeue();
	            for (WeightedEdge e : G.adj(v)) {
	            	int w = e.other(v);
	                if (degrees[v] < degrees[w]) {
	                    distTo[w] = Integer.min(distTo[w], (int) e.weight());
	                    degrees[w] = degrees[v] + 1;
	                    q.enqueue(w);
	                }
	            }
	        }
	    }

	    public int distTo(int v) {
	        return distTo[v];
	    }
	}


	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		HashMap<Integer, String> iToS = new HashMap<Integer, String>();
		HashMap<String, Integer> sToI = new HashMap<String, Integer>();
		int n = in.nextInt();
		int m = in.nextInt();
		iToS.put(0, "English");
		sToI.put("English", 0);
		for (int i = 1; i <= n; i++) {
			String lang = in.next();
			iToS.put(i, lang);
			sToI.put(lang, i);
		}
		EdgeWeightedGraph G = o.new EdgeWeightedGraph(n + 1);
		for (int i = 0; i < m; i++) {
			String a = in.next();
			String b = in.next();
			int c = in.nextInt();
			G.addEdge(o.new WeightedEdge(sToI.get(a), sToI.get(b), c));
		}
		BreadthFirstPaths bfs = o.new BreadthFirstPaths(G, sToI.get("English"));
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			int dist = bfs.distTo(i);
			if (dist != Integer.MAX_VALUE) sum += bfs.distTo(i);
			else {
				sum = -1;
				break;
			}
		}
		if (sum != -1) System.out.println(sum);
		else System.out.println("Impossible");
		out.close();
	}
}
