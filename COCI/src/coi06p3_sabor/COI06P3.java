package coi06p3_sabor;

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

public class COI06P3 { // 0/10 TLE, OutOfMemoryErro, Negative ArraySizeException
	private static COI06P3 o = new COI06P3();
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
	
	public class Graph {
	    private final String NEWLINE = System.getProperty("line.separator");

	    private final int V;
	    private int E;
	    private HashSet<Integer>[] adj;
	    
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
	        adj = (HashSet<Integer>[]) new HashSet[V];
	        for (int v = 0; v < V; v++) {
	        	adj[v] = new HashSet<Integer>();
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
	
	public class BreadthFirstPaths {
	    private static final int INFINITY = Integer.MAX_VALUE;
	    private boolean[] marked;  // marked[v] = is there an s-v path
	    private int[] edgeTo;      // edgeTo[v] = previous edge on shortest s-v path
	    private int[] distTo;      // distTo[v] = number of edges shortest s-v path

	    /**
	     * Computes the shortest path between the source vertex {@code s}
	     * and every other vertex in the graph {@code G}.
	     * @param G the graph
	     * @param s the source vertex
	     * @throws IllegalArgumentException unless {@code 0 <= s < V}
	     */
	    public BreadthFirstPaths(Graph G, int s) {
	        marked = new boolean[G.V()];
	        distTo = new int[G.V()];
	        edgeTo = new int[G.V()];
	        validateVertex(s);
	        bfs(G, s);
	    }

	    /**
	     * Computes the shortest path between any one of the source vertices in {@code sources}
	     * and every other vertex in graph {@code G}.
	     * @param G the graph
	     * @param sources the source vertices
	     * @throws IllegalArgumentException unless {@code 0 <= s < V} for each vertex
	     *         {@code s} in {@code sources}
	     */
	    public BreadthFirstPaths(Graph G, Iterable<Integer> sources) {
	        marked = new boolean[G.V()];
	        distTo = new int[G.V()];
	        edgeTo = new int[G.V()];
	        for (int v = 0; v < G.V(); v++)
	            distTo[v] = INFINITY;
	        validateVertices(sources);
	        bfs(G, sources);
	    }

	    // breadth-first search from a single source
	    private void bfs(Graph G, int s) {
	        Queue<Integer> q = new Queue<Integer>();
	        for (int v = 0; v < G.V(); v++)
	            distTo[v] = INFINITY;
	        distTo[s] = 0;
	        marked[s] = true;
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

	    // breadth-first search from multiple sources
	    private void bfs(Graph G, Iterable<Integer> sources) {
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
	     * Is there a path between the source vertex {@code s} (or sources) and vertex {@code v}?
	     * @param v the vertex
	     * @return {@code true} if there is a path, and {@code false} otherwise
	     * @throws IllegalArgumentException unless {@code 0 <= v < V}
	     */
	    public boolean hasPathTo(int v) {
	        validateVertex(v);
	        return marked[v];
	    }

	    /**
	     * Returns the number of edges in a shortest path between the source vertex {@code s}
	     * (or sources) and vertex {@code v}?
	     * @param v the vertex
	     * @return the number of edges in a shortest path
	     * @throws IllegalArgumentException unless {@code 0 <= v < V}
	     */
	    public int distTo(int v) {
	        validateVertex(v);
	        return distTo[v];
	    }

	    /**
	     * Returns a shortest path between the source vertex {@code s} (or sources)
	     * and {@code v}, or {@code null} if no such path.
	     * @param  v the vertex
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

	
	private static int width;
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int B = in.nextInt();
		int S = in.nextInt();
		int max = B + S;
		width = max * 2 + 1;
		int hqX = max; 
		int hqY = max;
		boolean[] obstacle = new boolean[width * width];
		for (int i = 0; i < B; i++) {
			int x = in.nextInt();
			int y = in.nextInt();
			if (isPoint(hqY + y, hqX + x)) obstacle[toPoint(hqY + y, hqX + x)] = true;
		}
		Graph G = o.new Graph(width * width);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < width; j++) {
				if (!obstacle[toPoint(i, j)]) {
					if (isPoint(i, j + 1) && !obstacle[toPoint(i, j + 1)]) G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && !obstacle[toPoint(i, j - 1)]) G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && !obstacle[toPoint(i + 1, j)]) G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && !obstacle[toPoint(i - 1, j)]) G.addEdge(toPoint(i, j), toPoint(i - 1, j));
				}
			}
		}
		BreadthFirstPaths bfs = o.new BreadthFirstPaths(G, toPoint(hqY, hqX));
		int pow = 0;
		int opp = 0;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < width; j++) {
				int point = toPoint(i, j);
				int dist = bfs.distTo(point);
				if (!obstacle[toPoint(i, j)] && dist <= S) {
					if (dist % 2 == 0) pow++;
					else opp++;
				}
			}
		}
		out.println(pow + " " + opp);
		out.close();
	}
	
	private static boolean isPoint(int i, int j) {
		return (i >= 0 && i < width && j >= 0 && j < width);
	}
	private static int toPoint(int i, int j) {
		return i * width + j;
	}
}
