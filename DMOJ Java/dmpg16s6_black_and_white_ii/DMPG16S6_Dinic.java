import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class DMPG16S6_Dinic {
    private static DMPG16S6_Dinic o = new DMPG16S6_Dinic();
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
    
    public class FlowEdge {
        // to deal with floating-point roundoff errors
        private static final double FLOATING_POINT_EPSILON = 1E-10;

        private final int v;             // from
        private final int w;             // to 
        private final double capacity;   // capacity
        private double flow;             // flow

        /**
         * Initializes an edge from vertex {@code v} to vertex {@code w} with
         * the given {@code capacity} and zero flow.
         * @param v the tail vertex
         * @param w the head vertex
         * @param capacity the capacity of the edge
         * @throws IllegalArgumentException if either {@code v} or {@code w}
         *    is a negative integer
         * @throws IllegalArgumentException if {@code capacity < 0.0}
         */
        public FlowEdge(int v, int w, double capacity) {
            if (v < 0) throw new IllegalArgumentException("vertex index must be a non-negative integer");
            if (w < 0) throw new IllegalArgumentException("vertex index must be a non-negative integer");
            if (!(capacity >= 0.0)) throw new IllegalArgumentException("Edge capacity must be non-negative");
            this.v         = v;
            this.w         = w;  
            this.capacity  = capacity;
            this.flow      = 0.0;
        }

        /**
         * Initializes an edge from vertex {@code v} to vertex {@code w} with
         * the given {@code capacity} and {@code flow}.
         * @param v the tail vertex
         * @param w the head vertex
         * @param capacity the capacity of the edge
         * @param flow the flow on the edge
         * @throws IllegalArgumentException if either {@code v} or {@code w}
         *    is a negative integer
         * @throws IllegalArgumentException if {@code capacity} is negative
         * @throws IllegalArgumentException unless {@code flow} is between 
         *    {@code 0.0} and {@code capacity}.
         */
        public FlowEdge(int v, int w, double capacity, double flow) {
            if (v < 0) throw new IllegalArgumentException("vertex index must be a non-negative integer");
            if (w < 0) throw new IllegalArgumentException("vertex index must be a non-negative integer");
            if (!(capacity >= 0.0))  throw new IllegalArgumentException("edge capacity must be non-negative");
            if (!(flow <= capacity)) throw new IllegalArgumentException("flow exceeds capacity");
            if (!(flow >= 0.0))      throw new IllegalArgumentException("flow must be non-negative");
            this.v         = v;
            this.w         = w;  
            this.capacity  = capacity;
            this.flow      = flow;
        }

        /**
         * Initializes a flow edge from another flow edge.
         * @param e the edge to copy
         */
        public FlowEdge(FlowEdge e) {
            this.v         = e.v;
            this.w         = e.w;
            this.capacity  = e.capacity;
            this.flow      = e.flow;
        }

        /**
         * Returns the tail vertex of the edge.
         * @return the tail vertex of the edge
         */
        public int from() {
            return v;
        }  

        /**
         * Returns the head vertex of the edge.
         * @return the head vertex of the edge
         */
        public int to() {
            return w;
        }  

        /**
         * Returns the capacity of the edge.
         * @return the capacity of the edge
         */
        public double capacity() {
            return capacity;
        }

        /**
         * Returns the flow on the edge.
         * @return the flow on the edge
         */
        public double flow() {
            return flow;
        }

        /**
         * Returns the endpoint of the edge that is different from the given vertex
         * (unless the edge represents a self-loop in which case it returns the same vertex).
         * @param vertex one endpoint of the edge
         * @return the endpoint of the edge that is different from the given vertex
         *   (unless the edge represents a self-loop in which case it returns the same vertex)
         * @throws IllegalArgumentException if {@code vertex} is not one of the endpoints
         *   of the edge
         */
        public int other(int vertex) {
            if      (vertex == v) return w;
            else if (vertex == w) return v;
            else throw new IllegalArgumentException("invalid endpoint");
        }

        /**
         * Returns the residual capacity of the edge in the direction
         *  to the given {@code vertex}.
         * @param vertex one endpoint of the edge
         * @return the residual capacity of the edge in the direction to the given vertex
         *   If {@code vertex} is the tail vertex, the residual capacity equals
         *   {@code capacity() - flow()}; if {@code vertex} is the head vertex, the
         *   residual capacity equals {@code flow()}.
         * @throws IllegalArgumentException if {@code vertex} is not one of the endpoints of the edge
         */
        public double residualCapacityTo(int vertex) {
            if      (vertex == v) return flow;              // backward edge
            else if (vertex == w) return capacity - flow;   // forward edge
            else throw new IllegalArgumentException("invalid endpoint");
        }

        /**
         * Increases the flow on the edge in the direction to the given vertex.
         *   If {@code vertex} is the tail vertex, this increases the flow on the edge by {@code delta};
         *   if {@code vertex} is the head vertex, this decreases the flow on the edge by {@code delta}.
         * @param vertex one endpoint of the edge
         * @param delta amount by which to increase flow
         * @throws IllegalArgumentException if {@code vertex} is not one of the endpoints
         *   of the edge
         * @throws IllegalArgumentException if {@code delta} makes the flow on
         *   on the edge either negative or larger than its capacity
         * @throws IllegalArgumentException if {@code delta} is {@code NaN}
         */
        public void addResidualFlowTo(int vertex, double delta) {
            if (!(delta >= 0.0)) throw new IllegalArgumentException("Delta must be nonnegative");

            if      (vertex == v) flow -= delta;           // backward edge
            else if (vertex == w) flow += delta;           // forward edge
            else throw new IllegalArgumentException("invalid endpoint");

            // round flow to 0 or capacity if within floating-point precision
            if (Math.abs(flow) <= FLOATING_POINT_EPSILON)
                flow = 0;
            if (Math.abs(flow - capacity) <= FLOATING_POINT_EPSILON)
                flow = capacity;

            if (!(flow >= 0.0))      throw new IllegalArgumentException("Flow is negative");
            if (!(flow <= capacity)) throw new IllegalArgumentException("Flow exceeds capacity");
        }


        /**
         * Returns a string representation of the edge.
         * @return a string representation of the edge
         */
        public String toString() {
            return v + "->" + w + " " + flow + "/" + capacity;
        }
    }
    
    public class FlowNetwork {
        private final String NEWLINE = System.getProperty("line.separator");

        private final int V;
        private int E;
        private ArrayList<FlowEdge>[] adj;
        
        /**
         * Initializes an empty flow network with {@code V} vertices and 0 edges.
         * @param V the number of vertices
         * @throws IllegalArgumentException if {@code V < 0}
         */
        public FlowNetwork(int V) {
            if (V < 0) throw new IllegalArgumentException("Number of vertices in a Graph must be nonnegative");
            this.V = V;
            this.E = 0;
            adj = (ArrayList<FlowEdge>[]) new ArrayList[V];
            for (int v = 0; v < V; v++)
                adj[v] = new ArrayList<FlowEdge>();
        }

        /**
         * Returns the number of vertices in the edge-weighted graph.
         * @return the number of vertices in the edge-weighted graph
         */
        public int V() {
            return V;
        }

        /**
         * Returns the number of edges in the edge-weighted graph.
         * @return the number of edges in the edge-weighted graph
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
         * Adds the edge {@code e} to the network.
         * @param e the edge
         * @throws IndexOutOfBoundsException unless endpoints of edge are between
         *         {@code 0} and {@code V-1}
         */
        public void addEdge(FlowEdge e) {
            int v = e.from();
            int w = e.to();
            validateVertex(v);
            validateVertex(w);
            adj[v].add(e);
            adj[w].add(e);
            E++;
        }

        /**
         * Returns the edges incident on vertex {@code v} (includes both edges pointing to
         * and from {@code v}).
         * @param v the vertex
         * @return the edges incident on vertex {@code v} as an Iterable
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public ArrayList<FlowEdge> adj(int v) {
            validateVertex(v);
            return adj[v];
        }

        // return list of all edges - excludes self loops
        public ArrayList<FlowEdge> edges() {
            ArrayList<FlowEdge> list = new ArrayList<FlowEdge>();
            for (int v = 0; v < V; v++)
                for (FlowEdge e : adj(v)) {
                    if (e.to() != v)
                        list.add(e);
                }
            return list;
        }


        /**
         * Returns a string representation of the flow network.
         * This method takes time proportional to <em>E</em> + <em>V</em>.
         * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,  
         *    followed by the <em>V</em> adjacency lists
         */
        public String toString() {
            StringBuilder s = new StringBuilder();
            s.append(V + " " + E + NEWLINE);
            for (int v = 0; v < V; v++) {
                s.append(v + ":  ");
                for (FlowEdge e : adj[v]) {
                    if (e.to() != v) s.append(e + "  ");
                }
                s.append(NEWLINE);
            }
            return s.toString();
        }
    }
    
    public class DinicMaxFlow {
        private final int V;
        private double value;
        private int[] level;
        private int[] start;
        
        /**
         * Compute a maximum flow and minimum cut in the network {@code G}
         * from vertex {@code s} to vertex {@code t}.
         *
         * @param  G the flow network
         * @param  s the source vertex
         * @param  t the sink vertex
         * @throws IllegalArgumentException unless {@code 0 <= s < V}
         * @throws IllegalArgumentException unless {@code 0 <= t < V}
         * @throws IllegalArgumentException if {@code s == t}
         */
        public DinicMaxFlow(FlowNetwork G, int s, int t) {
            V = G.V();
            validate(s);
            validate(t);
            if (s == t) throw new IllegalArgumentException("Source equals sink");
            level = new int[V];
            start = new int[V];
            while (hasAugmentingPath(G, s, t)) {
                for (int v = 0; v < V; v++) {
                    start[v] = 0;
                }
                double flow;
                while ((flow = sendFlow(G, s, t, start, Double.POSITIVE_INFINITY)) > 0) {
                    value += flow;
                }
            }
        }
        
        /**
         * Returns the value of the maximum flow.
         *
         * @return the value of the maximum flow
         */
        public double value()  {
            return value;
        }

        /**
         * Returns true if the specified vertex is on the {@code s} side of the mincut.
         *
         * @param  v vertex
         * @return {@code true} if vertex {@code v} is on the {@code s} side of the micut;
         *         {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public boolean inCut(int v)  {
            validate(v);
            return level[v] != -1;
        }
        
        // throw an IllegalArgumentException if v is outside prescribed range
        private void validate(int v)  {
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
        
        // is there an augmenting path? 
        // this implementation finds a shortest augmenting path (fewest number of edges)
        private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {
            for (int v = 0; v < V; v++) {
                level[v] = -1;
            }
            level[s] = 0;
            Queue<Integer> queue = new Queue<Integer>();
            queue.enqueue(s);
            while (!queue.isEmpty()) {
                int v = queue.dequeue();
                for (FlowEdge e : G.adj(v)) {
                    int w = e.other(v);
                    if (level[w] < 0 && e.residualCapacityTo(w) > 0) {
                        level[w] = level[v] + 1;
                        queue.enqueue(w);
                    }
                }
            }
            return level[t] < 0 ? false : true;
        }
        
        // v : current vertex
        // t : sink
        // start : start[v] stores the number of edges that have been explored from v
        // flow : current flow sent from parent
        private double sendFlow(FlowNetwork G, int v, int t, int[] start, double flow) {
            if (v == t) return flow;
            for ( ; start[v] < G.adj(v).size(); start[v]++) {
                FlowEdge e = G.adj(v).get(start[v]);
                int w = e.other(v);
                if (level[w] == level[v] + 1 && e.residualCapacityTo(w) > 0) {
                    double curFlow = Math.min(flow, e.residualCapacityTo(w));
                    double tempFlow = sendFlow(G, w, t, start, curFlow);
                    if (tempFlow > 0) {
                        e.addResidualFlowTo(w, tempFlow);
                        return tempFlow;
                    }
                }
            }
            return 0.0;
        }
    }


    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    private static int M;
    private static int N;
    
    public static void main(String[] args) throws IOException {
        M = in.nextInt();
        N = in.nextInt();
        int superSource = 0;
        int superSink = N * M * 2 + 1;
        char[][] grid = new char[N][M];
        for (int i = 0; i < N; i++) {
            grid[i] = in.nextLine().toCharArray();
        }
        FlowNetwork G = o.new FlowNetwork(N * M * 2 + 2);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == '#') continue;
                G.addEdge(o.new FlowEdge(getIn(i, j), getOut(i, j), 1));
                // Stay
                if (grid[(i + 1) % N][j] == '.') G.addEdge(o.new FlowEdge(getOut(i, j), getIn((i + 1) % N, j), Integer.MAX_VALUE));
                // Down
                if (grid[(i + 2) % N][j] == '.') G.addEdge(o.new FlowEdge(getOut(i, j), getIn((i + 2) % N, j), Integer.MAX_VALUE));
                // Left
                if (j > 0 && grid[(i + 1) % N][j - 1] == '.') G.addEdge(o.new FlowEdge(getOut(i, j), getIn((i + 1) % N, j - 1), Integer.MAX_VALUE));
                // Right
                if (j < M - 1 && grid[(i + 1) % N][j + 1] == '.') G.addEdge(o.new FlowEdge(getOut(i, j), getIn((i + 1) % N, j + 1), Integer.MAX_VALUE));
                // Up
            }
        }
        for (int i = 0; i < N; i++) {
            G.addEdge(o.new FlowEdge(superSource, getIn(i, 0), Integer.MAX_VALUE));
            G.addEdge(o.new FlowEdge(getOut(i, M-1), superSink, Integer.MAX_VALUE));
        }
        DinicMaxFlow mf = o.new DinicMaxFlow(G, superSource, superSink);
        out.println((int) mf.value());
        out.close();
    }
    
    private static int getIn(int i, int j) {
        return (i * M + j) * 2 + 1;
    }
    
    private static int getOut(int i, int j) {
        return (i * M + j) * 2 + 2;
    }   
}
