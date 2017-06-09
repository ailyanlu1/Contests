package cco14p3_werewolf;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;
import java.util.StringTokenizer;

public class CCO14P3 {
	private static CCO14P3 o = new CCO14P3();
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
	
	public class DirectedWeightedEdge { 
	    private final int v;
	    private final int w;
	    private final char op;

	    public DirectedWeightedEdge(int v, int w, char op) {
	        this.v = v;
	        this.w = w;
	        this.op = op;
	    }

	    public int from() {
	        return v;
	    }

	    public int to() {
	        return w;
	    }
	    
	    public char op() {
	        return op;
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
	     * Adds the directed weighted edge {@code e} to this edge-weighted digraph.
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
	     * Returns the directed weighted edges incident from vertex {@code v}.
	     *
	     * @param  v the vertex
	     * @return the directed weighted edges incident from vertex {@code v} as an Iterable
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
	     * Returns all directed weighted edges in this edge-weighted digraph.
	     * To iterate over the edges in this edge-weighted digraph, use foreach notation:
	     * {@code for (DirectedWeightedEdge e : G.edges())}.
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
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	/*
	private static char[][] grid;
	
	private static boolean isPoint(int i, int j) {
		return (i >= 0 && i < grid.length && j >= 0 && j < grid[0].length);
	}
	private static int toPoint(int i, int j) {
		return i * grid[0].length + j;
	}
	*/
	
	private static int N, W, M;
	private static WeightedDigraph G;
	private static boolean[] vis;
	private static long[][][] dp;
	private static final long MOD = (long) (1e9 + 7);
	
	public static void main(String[] args) throws IOException {
		N = in.nextInt();
		W = in.nextInt();
		M = in.nextInt();
		vis = new boolean[N + 1];
		dp = new long[N + 1][W + 1][2];
		G = o.new WeightedDigraph(N + 1);
		for (int i = 0; i < M; i++) {
			char op = in.nextChar();
			int a = in.nextInt();
			int b = in.nextInt();
			G.addEdge(o.new DirectedWeightedEdge(a, b, op));
		}
		for (int i = 1; i <= N; i++) {
			if (G.indegree(i) == 0) {
				G.addEdge(o.new DirectedWeightedEdge(0, i, ' '));
			}
		}
		dfs(0, -1);
		out.println(dp[0][W][0] % MOD);
		out.close();
	}
	
	private static void dfs(int v, int prev) {
		if (vis[v]) return;
		vis[v] = true;
		dp[v][0][0] = 1;
		if (W > 0) dp[v][1][1] = 1;
		for (DirectedWeightedEdge e: G.adj(v)) {
			int w = e.to();
			if (w == prev) continue;
			dfs(w, v);
			for (int i = W; i >= 0; i--) {
				long isW = 0;
				long notW = 0;
				for (int j = 0; j <= i; j++) {
					notW += dp[v][i - j][0] * (dp[w][j][0] + dp[w][j][1]);
					if (e.op() == 'A') isW += dp[w][j][0] * dp[v][i - j][1];
					else isW += dp[w][j][1] * dp[v][i - j][1];
					isW %= MOD;
					notW %= MOD;
				}
				dp[v][i][0] = notW;
				dp[v][i][1] = isW;
			}
		}
	}
}
