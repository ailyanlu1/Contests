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

public class ECOO17R2P2 { 
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
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    public static void main(String[] args) throws IOException {
        Reader f = o.new Reader(System.in);
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(f);
        } // for i
    } // main method
    
    private static int N;
    private static boolean[] marked;  // marked[v] = is there an s->v path?
    private static HashSet<Integer>[] adj;
    private static Queue<Integer> q;
    private static HashSet<Integer> rem;
    
    public static void run(Reader f) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
        N = f.nextInt();
        char[][] grid = new char[N][N];
        for (int i = 0; i < N; i++) {
            grid[i] = f.next().toCharArray();
        }
        HashSet<Integer> keys = new HashSet<Integer>();
        HashSet<Integer> treasure = new HashSet<Integer>();
        HashMap<Integer, Integer> doors = new HashMap<Integer, Integer>();
        adj = new HashSet[N * N];
        for (int i = 0; i < N * N; i++) {
            adj[i] = new HashSet<Integer>();
        }
        int source = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '#') {
                    continue;
                } else if (grid[i][j] == '.') {
                    if (isPoint(i, j + 1) && grid[i][j + 1] != '#') addEdge(toPoint(i, j), toPoint(i, j + 1));
                    if (isPoint(i, j - 1) && grid[i][j - 1] != '#') addEdge(toPoint(i, j), toPoint(i, j - 1));
                    if (isPoint(i + 1, j) && grid[i + 1][j] != '#') addEdge(toPoint(i, j), toPoint(i + 1, j));
                    if (isPoint(i - 1, j) && grid[i - 1][j] != '#') addEdge(toPoint(i, j), toPoint(i - 1, j));
                } else if (grid[i][j] == 'K') {
                    keys.add(toPoint(i, j));
                    if (isPoint(i, j + 1) && grid[i][j + 1] != '#') addEdge(toPoint(i, j), toPoint(i, j + 1));
                    if (isPoint(i, j - 1) && grid[i][j - 1] != '#') addEdge(toPoint(i, j), toPoint(i, j - 1));
                    if (isPoint(i + 1, j) && grid[i + 1][j] != '#') addEdge(toPoint(i, j), toPoint(i + 1, j));
                    if (isPoint(i - 1, j) && grid[i - 1][j] != '#') addEdge(toPoint(i, j), toPoint(i - 1, j));
                } else if (grid[i][j] == 'T') {
                    treasure.add(toPoint(i, j));
                    if (isPoint(i, j + 1) && grid[i][j + 1] != '#') addEdge(toPoint(i, j), toPoint(i, j + 1));
                    if (isPoint(i, j - 1) && grid[i][j - 1] != '#') addEdge(toPoint(i, j), toPoint(i, j - 1));
                    if (isPoint(i + 1, j) && grid[i + 1][j] != '#') addEdge(toPoint(i, j), toPoint(i + 1, j));
                    if (isPoint(i - 1, j) && grid[i - 1][j] != '#') addEdge(toPoint(i, j), toPoint(i - 1, j));
                } else if (grid[i][j] == 'S') {
                    source = toPoint(i, j);
                    if (isPoint(i, j + 1) && grid[i][j + 1] != '#') addEdge(toPoint(i, j), toPoint(i, j + 1));
                    if (isPoint(i, j - 1) && grid[i][j - 1] != '#') addEdge(toPoint(i, j), toPoint(i, j - 1));
                    if (isPoint(i + 1, j) && grid[i + 1][j] != '#') addEdge(toPoint(i, j), toPoint(i + 1, j));
                    if (isPoint(i - 1, j) && grid[i - 1][j] != '#') addEdge(toPoint(i, j), toPoint(i - 1, j));
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
            rem = new HashSet<Integer>();
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
                    if (isPoint(i, j + 1) && grid[i][j + 1] != '#') addEdge(toPoint(i, j), toPoint(i, j + 1));
                    if (isPoint(i, j - 1) && grid[i][j - 1] != '#') addEdge(toPoint(i, j), toPoint(i, j - 1));
                    if (isPoint(i + 1, j) && grid[i + 1][j] != '#') addEdge(toPoint(i, j), toPoint(i + 1, j));
                    if (isPoint(i - 1, j) && grid[i - 1][j] != '#') addEdge(toPoint(i, j), toPoint(i - 1, j));
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
    
    private static void addEdge(int v, int w) {
        adj[v].add(w);
    }
    
    private static void bfs(int s) {
        marked = new boolean[N * N];
        q = o.new Queue<Integer>();
        marked[s] = true;
        q.enqueue(s);
        while (!q.isEmpty()) {
            int v = q.dequeue();
            for (int w : adj[v]) {
                if (!marked[w]) {
                    marked[w] = true;
                    q.enqueue(w);
                }
            }
        }
    }
}
