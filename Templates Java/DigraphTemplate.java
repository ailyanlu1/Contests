
import java.io.BufferedReader;
import java.io.BufferedWriter;
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
import java.util.Stack;
import java.util.StringTokenizer;

public class DigraphTemplate {
	private static DigraphTemplate o = new DigraphTemplate();
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

		/*public BigInteger nextBigInteger() throws IOException {
			return new BigInteger(next());
		}*/

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
	     * Returns the rank by size of the component containing p
	     * 
	     * @param p the integer representing one site
	     * @return the rank by size of the component containing p
	     */
	    public byte rank(int p) {
	    	return rank[find(p)];
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
	    
	    /**
	     * Unmerges the component containing site {@code p} with the 
	     * the component containing site {@code q}.
	     *
	     * @param  p the integer representing one site
	     * @param  q the integer representing the other site
	     * @throws IndexOutOfBoundsException unless
	     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
	     */
	    public void disjoin(int p, int q) {
	        int rootP = find(p);
	        int rootQ = find(q);
	        if (rootP == rootQ) return;

	        // make root of smaller rank point to root of larger rank
	        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootP;
	        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootQ;
	        else {
	            parent[rootQ] = rootP;
	            rank[rootP]--;
	        }
	        count++;
	    }

	    // validate that p is a valid index
	    private void validate(int p) {
	        int n = parent.length;
	        if (p < 0 || p >= n) {
	            throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n-1));  
	        }
	    }
	}
	
	public class Digraph {
	    private final String NEWLINE = System.getProperty("line.separator");

	    private final int V;           // number of vertices in this digraph
	    private int E;                 // number of edges in this digraph
	    private HashSet<Integer>[] adj;    // adj[v] = adjacency list for vertex v
	    private HashSet<DirectedEdge> removed;
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
	        adj = (HashSet<Integer>[]) new HashSet[V];
	        removed = new HashSet<DirectedEdge>();
	        for (int v = 0; v < V; v++) {
	            adj[v] = new HashSet<Integer>();
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
	     * Removes the directed edge from {@code e} from this edge-weighted digraph.
	     *
	     * @param  v the start vertex in the edge
	     * @param  w the end vertex in the edge
	     * @throws IllegalArgumentException unless endpoints of edge are between {@code 0}
	     *         and {@code V-1}
	     */
	    public void removeEdge(int v, int w) {
	        validateVertex(v);
	        validateVertex(w);
	        removed.add(new DirectedEdge(v, w));
	        adj[v].remove(w);
	        indegree[w]--;
	        E--;
	    }
	    
	    /**
	     * Restores all the edges removed from this edge-weighted digraph.
	     */
	    public void restoreEdges() {
	    	for (DirectedEdge e: removed) {
	            addEdge(e.from, e.to);
	    	}
	    	removed.clear();
	    }
	    
	    /**
	     * Clears the edges removed from this digraph so they can no longer
	     * be restored
	     */
	    public void clearRemoved() {
	    	removed.clear();
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
	    
		public class DirectedEdge {
			public int from;
			public int to;

			public DirectedEdge(int v, int w) {
				this.from = v;
				this.to = w;
			}

			@Override
			public int hashCode() {
				return 31 * from + to;
			}

			@Override
			public boolean equals(Object o) {
				if (o == this) return true;
				if (!(o instanceof DirectedEdge)) return false;
				DirectedEdge e = (DirectedEdge) o;
				return e.from == from && e.to == to;
			}
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	public static void main(String[] args) throws IOException {
		// TODO INSERT CODE HERE
		out.close();
	}
}
