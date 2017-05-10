package ecoo17r2p2_treasure_hunt;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.Stack;

public class ECOO17R2P2 { // MLE
	private static ECOO17R2P2 o = new ECOO17R2P2();
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
	
	public class Digraph {
	    private final String NEWLINE = System.getProperty("line.separator");

	    private final int V;           // number of vertices in this digraph
	    private int E;                 // number of edges in this digraph
	    private Bag<Integer>[] adj;    // adj[v] = adjacency list for vertex v
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
	        adj = (Bag<Integer>[]) new Bag[V];
	        for (int v = 0; v < V; v++) {
	            adj[v] = new Bag<Integer>();
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
	}
	
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
	public static void main(String[] args) throws IOException {
		Reader f = o.new Reader(System.in);
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(f);
		} // for i
	} // main method
	
	private static int N;
	private static boolean[] marked;  // marked[v] = is there an s->v path?
    private static int[] edgeTo;      // edgeTo[v] = last edge on shortest s->v path
    private static int[] distTo;      // distTo[v] = length of shortest s->v path
    private static Digraph G;
	
	public static void run(Reader f) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
		N = f.nextInt();
		char[][] grid = new char[N][N];
		for (int i = 0; i < N; i++) {
			grid[i] = f.next().toCharArray();
		}
		HashSet<Integer> keys = new HashSet<Integer>();
		HashSet<Integer> treasure = new HashSet<Integer>();
		HashMap<Integer, Integer> doors = new HashMap<Integer, Integer>();
		G = o.new Digraph(N * N);
		int source = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (grid[i][j] == '#') {
					continue;
				} else if (grid[i][j] == '.') {
					if (isPoint(i, j + 1) && grid[i][j + 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && grid[i][j - 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && grid[i + 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && grid[i - 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i - 1, j));
				} else if (grid[i][j] == 'K') {
					keys.add(toPoint(i, j));
					if (isPoint(i, j + 1) && grid[i][j + 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && grid[i][j - 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && grid[i + 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && grid[i - 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i - 1, j));
				} else if (grid[i][j] == 'T') {
					treasure.add(toPoint(i, j));
					if (isPoint(i, j + 1) && grid[i][j + 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && grid[i][j - 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && grid[i + 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && grid[i - 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i - 1, j));
				} else if (grid[i][j] == 'S') {
					source = toPoint(i, j);
					if (isPoint(i, j + 1) && grid[i][j + 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && grid[i][j - 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && grid[i + 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && grid[i - 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i - 1, j));
				} else {
					doors.put(toPoint(i, j), Integer.parseInt("" + grid[i][j]));
				}
			}
		}
        int k = 0;
        int t = 0;
        while(true) {
	        int temp = 0;
	        bfs(source);
	        HashSet<Integer> rem = new HashSet<Integer>();
			for (int keyLoc: keys) {
				if (marked[keyLoc]) {
					temp++;
					rem.add(keyLoc);
				}
			}
			for (int keyLoc: rem) {
				keys.remove(keyLoc);
			}
			if (temp == 0) {
				break;
			} else {
				k += temp;
			}
			rem = new HashSet<Integer>();
			for (int doorLoc: doors.keySet()) {
				if (doors.get(doorLoc) <= k) {
					int i = doorLoc / N;
					int j = doorLoc % N;
					if (isPoint(i, j + 1) && grid[i][j + 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j + 1));
					if (isPoint(i, j - 1) && grid[i][j - 1] != '#') G.addEdge(toPoint(i, j), toPoint(i, j - 1));
					if (isPoint(i + 1, j) && grid[i + 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i + 1, j));
					if (isPoint(i - 1, j) && grid[i - 1][j] != '#') G.addEdge(toPoint(i, j), toPoint(i - 1, j));
					rem.add(doorLoc);
				}
			}
			for (int doorLoc: rem) {
				doors.remove(doorLoc);
			}
			bfs(source);
			rem = new HashSet<Integer>();
			for (int tLoc: treasure) {
				if (marked[tLoc]) {
					t++;
					rem.add(tLoc);
				}
			}
			for (int tLoc: rem) {
				treasure.remove(tLoc);
			}
        }
        System.out.println(t);
	} // run method
	
	private static boolean isPoint(int i, int j) {
		return (i >= 0 && i < N && j >= 0 && j < N);
	}
	private static int toPoint(int i, int j) {
		return i * N + j;
	}
	
    private static void bfs(int s) {
    	marked = new boolean[G.V()];
        distTo = new int[G.V()];
        edgeTo = new int[G.V()];
        for (int v = 0; v < G.V(); v++) {
            distTo[v] = Integer.MAX_VALUE;
        }
        Queue<Integer> q = o.new Queue<Integer>();
        marked[s] = true;
        distTo[s] = 0;
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
} // QuestionTwo class
