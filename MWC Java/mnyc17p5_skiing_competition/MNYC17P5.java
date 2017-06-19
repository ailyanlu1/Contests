package mnyc17p5_skiing_competition;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.TreeMap;
import java.util.TreeSet;

public class MNYC17P5 {
    private static MNYC17P5 o = new MNYC17P5();
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
    
    public class MinPQ<Key> implements Iterable<Key> {
        private Key[] pq;                    // store items at indices 1 to n
        private int n;                       // number of items on priority queue
        private Comparator<Key> comparator;  // optional comparator

        /**
         * Initializes an empty priority queue with the given initial capacity.
         *
         * @param  initCapacity the initial capacity of this priority queue
         */
        public MinPQ(int initCapacity) {
            pq = (Key[]) new Object[initCapacity + 1];
            n = 0;
        }

        /**
         * Initializes an empty priority queue.
         */
        public MinPQ() {
            this(1);
        }

        /**
         * Initializes an empty priority queue with the given initial capacity,
         * using the given comparator.
         *
         * @param  initCapacity the initial capacity of this priority queue
         * @param  comparator the order to use when comparing keys
         */
        public MinPQ(int initCapacity, Comparator<Key> comparator) {
            this.comparator = comparator;
            pq = (Key[]) new Object[initCapacity + 1];
            n = 0;
        }

        /**
         * Initializes an empty priority queue using the given comparator.
         *
         * @param  comparator the order to use when comparing keys
         */
        public MinPQ(Comparator<Key> comparator) {
            this(1, comparator);
        }

        /**
         * Initializes a priority queue from the array of keys.
         * <p>
         * Takes time proportional to the number of keys, using sink-based heap construction.
         *
         * @param  keys the array of keys
         */
        public MinPQ(Key[] keys) {
            n = keys.length;
            pq = (Key[]) new Object[keys.length + 1];
            for (int i = 0; i < n; i++)
                pq[i+1] = keys[i];
            for (int k = n/2; k >= 1; k--)
                sink(k);
            // assert isMinHeap();
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
         * Returns the number of keys on this priority queue.
         *
         * @return the number of keys on this priority queue
         */
        public int size() {
            return n;
        }

        /**
         * Returns a smallest key on this priority queue.
         *
         * @return a smallest key on this priority queue
         * @throws NoSuchElementException if this priority queue is empty
         */
        public Key min() {
            if (isEmpty()) throw new NoSuchElementException("Priority queue underflow");
            return pq[1];
        }

        // helper function to double the size of the heap array
        private void resize(int capacity) {
            // assert capacity > n;
            Key[] temp = (Key[]) new Object[capacity];
            for (int i = 1; i <= n; i++) {
                temp[i] = pq[i];
            }
            pq = temp;
        }

        /**
         * Adds a new key to this priority queue.
         *
         * @param  x the key to add to this priority queue
         */
        public void insert(Key x) {
            // double size of array if necessary
            if (n == pq.length - 1) resize(2 * pq.length);

            // add x, and percolate it up to maintain heap invariant
            pq[++n] = x;
            swim(n);
            // assert isMinHeap();
        }

        /**
         * Removes and returns a smallest key on this priority queue.
         *
         * @return a smallest key on this priority queue
         * @throws NoSuchElementException if this priority queue is empty
         */
        public Key delMin() {
            if (isEmpty()) throw new NoSuchElementException("Priority queue underflow");
            exch(1, n);
            Key min = pq[n--];
            sink(1);
            pq[n+1] = null;         // avoid loitering and help with garbage collection
            if ((n > 0) && (n == (pq.length - 1) / 4)) resize(pq.length  / 2);
            // assert isMinHeap();
            return min;
        }


       /***************************************************************************
        * Helper functions to restore the heap invariant.
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
        * Helper functions for compares and swaps.
        ***************************************************************************/
        private boolean greater(int i, int j) {
            if (comparator == null) {
                return ((Comparable<Key>) pq[i]).compareTo(pq[j]) > 0;
            }
            else {
                return comparator.compare(pq[i], pq[j]) > 0;
            }
        }

        private void exch(int i, int j) {
            Key swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
        }

        // is pq[1..N] a min heap?
        private boolean isMinHeap() {
            return isMinHeap(1);
        }

        // is subtree of pq[1..n] rooted at k a min heap?
        private boolean isMinHeap(int k) {
            if (k > n) return true;
            int left = 2*k;
            int right = 2*k + 1;
            if (left  <= n && greater(k, left))  return false;
            if (right <= n && greater(k, right)) return false;
            return isMinHeap(left) && isMinHeap(right);
        }


        /**
         * Returns an iterator that iterates over the keys on this priority queue
         * in ascending order.
         * <p>
         * The iterator doesn't implement {@code remove()} since it's optional.
         *
         * @return an iterator that iterates over the keys in ascending order
         */
        public Iterator<Key> iterator() { return new HeapIterator(); }

        private class HeapIterator implements Iterator<Key> {
            // create a new pq
            private MinPQ<Key> copy;

            // add all items to copy of heap
            // takes linear time since already in heap order so no keys move
            public HeapIterator() {
                if (comparator == null) copy = new MinPQ<Key>(size());
                else                    copy = new MinPQ<Key>(size(), comparator);
                for (int i = 1; i <= n; i++)
                    copy.insert(pq[i]);
            }

            public boolean hasNext()  { return !copy.isEmpty();                     }
            public void remove()      { throw new UnsupportedOperationException();  }

            public Key next() {
                if (!hasNext()) throw new NoSuchElementException();
                return copy.delMin();
            }
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    private static int MAXQ = 50;
    
    private static int N, M, A, B, Q;
    private static int[] dist, min;
    private static Edge[] prev;
    private static ArrayList<ArrayList<Edge>> adj = new ArrayList<ArrayList<Edge>>();

    private static ArrayList<Path> bestPaths = new ArrayList<Path>();
    private static TreeSet<Path> possPaths = new TreeSet<Path>();

    private static TreeMap<Integer, Integer> paths = new TreeMap<Integer, Integer>();
    private static HashSet<Edge> usedEdges = new HashSet<Edge>();
    private static HashSet<Integer> usedVertices = new HashSet<Integer>();
    private static boolean[] vis;

    public static void main(String[] args) throws IOException {
        N = in.nextInt();
        M = in.nextInt();
        A = in.nextInt() - 1;
        B = in.nextInt() - 1;
        Q = in.nextInt();

        for (int i = 0; i < N; i++) {
            adj.add(new ArrayList<Edge>());
        }
        dist = new int[N];
        prev = new Edge[N];
        min = new int[N];
        for (int i = 0; i < M; i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            int c = in.nextInt();
            adj.get(u).add(new Edge(u, v, c));
            adj.get(v).add(new Edge(v, u, c));
        }
        /* SUBTASKS 1 and 2 */
        if (N <= 100) {
            vis = new boolean[N];
            MAXQ = 10;
            vis[A] = true;
            dfs(A, 0, 1 << 30);
            int[] cost = new int[MAXQ], min = new int[MAXQ];
            Arrays.fill(cost, -1);
            Arrays.fill(min, -1);
            int index = 0;

            for (Map.Entry<Integer, Integer> p : paths.entrySet()) {
                cost[index] = p.getKey();
                min[index] = p.getValue();
                index++;
            }

            for (int i = 0; i < Q; i++) {
                int val = in.nextInt() - 1;
                if (cost[val] == -1) out.printf("-1\n");
                else out.printf("%d %d\n", cost[val], min[val]);
            }
            out.close();
            return;
        }
        Path nextPath = shortestPath(A, B);
        /* SUBTASK 3 */
        if (Q == 1) {
            if (nextPath == null) out.println(-1);
            else out.println(nextPath.cost + " " + nextPath.min);
            out.close();
            return;
        }
        /* SUBTASK 4 */
        bestPaths.add(nextPath);
        if (!paths.containsKey(nextPath.cost)) paths.put(nextPath.cost, nextPath.min);
        paths.put(nextPath.cost, Math.min(nextPath.min, paths.get(nextPath.cost)));

        for (int i = 1; paths.size() < MAXQ; i++) {
            for (int j = 0; j < bestPaths.get(i - 1).nodes.size(); j++) {
                int spurNode = bestPaths.get(i - 1).nodes.get(j).from;
                ArrayList<Edge> rootPath = new ArrayList<Edge>(bestPaths.get(i - 1).nodes.subList(0, j));
                usedEdges.clear();
                usedVertices.clear();
                for (Path p : bestPaths) {
                    if (p.nodes.size() < rootPath.size()) continue;
                    ArrayList<Edge> currPath = new ArrayList<Edge>(p.nodes.subList(0, j));
                    if (currPath.equals(rootPath)) {
                        usedEdges.add(p.nodes.get(j));
                        usedEdges.add(p.nodes.get(j).reverse());
                    }
                }
                usedVertices.add(A);
                for (Edge node : rootPath) {
                    usedVertices.add(node.to);
                }
                Path spurPath = shortestPath(spurNode, B);
                if (spurPath == null) continue;
                ArrayList<Edge> totalPath = rootPath;
                totalPath.addAll(spurPath.nodes);
                Path ret = new Path();
                ret.nodes = totalPath;
                ret.compute();
                possPaths.add(ret);
                if (possPaths.size() > MAXQ) possPaths.pollLast();
            }
            if (possPaths.isEmpty()) break;
            nextPath = possPaths.pollFirst();
            bestPaths.add(nextPath);
            if (!paths.containsKey(nextPath.cost)) paths.put(nextPath.cost, nextPath.min);
            paths.put(nextPath.cost, Math.min(nextPath.min, paths.get(nextPath.cost)));
        }

        int[] cost = new int[MAXQ], min = new int[MAXQ];
        Arrays.fill(cost, -1);
        Arrays.fill(min, -1);
        int index = 0;
        for (Map.Entry<Integer, Integer> p : paths.entrySet()) {
            cost[index] = p.getKey();
            min[index] = p.getValue();
            index++;
        }
        for (int i = 0; i < Q; i++) {
            int val = in.nextInt() - 1;
            if (cost[val] == -1) out.println(-1);
            else out.println(cost[val] + " " + min[val]);
        }
        out.close();
    }
    
    private static void dfs(int u, int cost, int min) {
        if (u == B) {
            if (!paths.containsKey(cost)) paths.put(cost, min);
            paths.put(cost, Math.min(min, paths.get(cost)));
            if (paths.size() > 10) paths.pollLastEntry();
            return;
        }
        for (Edge e : adj.get(u)) {
            if (vis[e.to]) continue;
            int nextCost = cost + e.cost;
            int nextMin = Math.min(min, e.cost);
            if (paths.size() == 10 && nextCost > paths.lastEntry().getKey()) continue;
            vis[e.to] = true;
            dfs(e.to, nextCost, nextMin);
            vis[e.to] = false;
        }
    }
    
    private static Path shortestPath(int src, int sink) {
        Arrays.fill(dist, 1 << 30);
        Arrays.fill(prev, null);
        Arrays.fill(min, 1 << 30);
        dist[src] = 0;

        MinPQ<Vertex> pq = o.new MinPQ<Vertex>();
        pq.insert(new Vertex(src, dist[src], min[src]));

        while (!pq.isEmpty()) {
            Vertex curr = pq.delMin();
            for (Edge next : adj.get(curr.index)) {
                if (usedEdges.contains(next)) continue;
                if (usedVertices.contains(next.to)) continue;
                if (next.cost + curr.cost < dist[next.to] || (next.cost + curr.cost == dist[next.to]
                        && Math.min(curr.min, next.cost) < min[next.to])) {
                    int nextCost = next.cost + curr.cost;
                    dist[next.to] = nextCost;
                    prev[next.to] = next;
                    min[next.to] = Math.min(curr.min, next.cost);
                    pq.insert(new Vertex(next.to, dist[next.to], min[next.to]));
                }
            }
        }

        if (prev[sink] == null) return null;

        Path ret = new Path();
        ret.cost = dist[sink];
        ret.min = min[sink];
        int curr = sink;
        while (prev[curr] != null) {
            ret.nodes.add(prev[curr]);
            curr = prev[curr].from;
        }
        Collections.reverse(ret.nodes);
        return ret;
    }

    public static class Vertex implements Comparable<Vertex> {
        public int index, cost, min;

        Vertex(int index, int cost, int min) {
            this.index = index;
            this.cost = cost;
            this.min = min;
        }

        @Override
        public int compareTo(Vertex v) {
            if (cost == v.cost) return min - v.min;
            return cost - v.cost;
        }
    }

    public static class Edge {
        public int from, to, cost;

        public Edge(int from, int to, int cost) {
            this.from = from;
            this.to = to;
            this.cost = cost;
        }

        @Override
        public boolean equals(Object o) {
            if (o instanceof Edge) {
                Edge e = (Edge) o;
                return (from == e.from && to == e.to && cost == e.cost);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return 31 * from + to;
        }

        public Edge reverse() {
            return new Edge(to, from, cost);
        }
    }

    public static class Path implements Comparable<Path> {
        public ArrayList<Edge> nodes = new ArrayList<Edge>();
        public int cost, min;

        @Override
        public int compareTo(Path v) {
            if (cost == v.cost) return min - v.min;
            return cost - v.cost;
        }

        public void compute() {
            cost = 0;
            min = 1 << 30;
            for (Edge edge : nodes) {
                cost += edge.cost;
                min = Math.min(edge.cost, min);
            }
        }
    }
}
