package utso15p5_distribution_channel;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;
import java.util.StringTokenizer;

public class UTSO15P5 {
    private static UTSO15P5 o = new UTSO15P5();
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
            int result = 31 * v + w;
            result = 31 * result + (int) (new Double(weight).hashCode() ^ (new Double(weight).hashCode() >>> 32));
            return result;
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof WeightedEdge)) return false;
            WeightedEdge e = (WeightedEdge) o;
            return e.v == v && e.w == w && e.weight() == weight;
        }
    }
    
    public class WeightedGraph {
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
        public WeightedGraph(int V) {
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
        public WeightedGraph(WeightedGraph G) {
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
         * Adds the undirected weighted edge {@code e} to this edge-weighted graph.
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
         * Returns the weighted edges incident on vertex {@code v}.
         *
         * @param  v the vertex
         * @return the weighted edges incident on vertex {@code v} as an Iterable
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
         * {@code for (WeightedEdge e : G.edges())}.
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
    
    public class KruskalMST {
        private static final double FLOATING_POINT_EPSILON = 1E-12;

        private double weight;     
        private WeightedGraph mst;
        public UF uf;
        private Queue<WeightedEdge> unused = new Queue<WeightedEdge>();  // edges in MST

        /**
         * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
         * @param G the edge-weighted graph
         */
        public KruskalMST(WeightedGraph G) {
            // more efficient to build heap by passing array of edges
            MinPQ<WeightedEdge> pq = new MinPQ<WeightedEdge>();
            for (WeightedEdge e : G.edges()) {
                pq.insert(e);
            }
            mst = new WeightedGraph(G.V());
            // run greedy algorithm
            uf = new UF(G.V());
            while (!pq.isEmpty()) {
                WeightedEdge e = pq.delMin();
                int v = e.either();
                int w = e.other(v);
                if (!uf.connected(v, w)) { // v-w does not create a cycle
                    uf.union(v, w);  // merge v and w components
                    mst.addEdge(e);  // add edge e to mst
                    weight += e.weight();
                } else {
                    unused.enqueue(e);
                }
            }
        }

        /**
         * Returns the edges in a minimum spanning tree (or forest).
         * @return the edges in a minimum spanning tree (or forest) as
         *    an iterable of edges
         */
        public WeightedGraph mst() {
            return mst;
        }
        
        public Queue<WeightedEdge> unsed() {
            return unused;
        }

        /**
         * Returns the sum of the edge weights in a minimum spanning tree (or forest).
         * @return the sum of the edge weights in a minimum spanning tree (or forest)
         */
        public double weight() {
            return weight;
        }
    }
    
    public class WeightedLCA {
        private int[] depth, parent, chain, size, head, base, val;
        private int chainNum, baseNum;
        private SegmentTree st;
        
        public WeightedLCA(WeightedGraph G) {
            depth = new int[G.V()];
            parent = new int[G.V()];
            chain = new int[G.V()];
            size = new int[G.V()];
            head = new int[G.V()];
            base = new int[G.V()];
            val = new int[G.V()];
            for (int i = 0; i < G.V(); i++) {
                head[i] = -1;
            }
            dfs(G, 0, 0, -1);
            hld(G, 0, -1, -1);
            st = new SegmentTree(baseNum - 1, val, true);
        }
        
        private void dfs(WeightedGraph G, int v, int d, int prev) {
            depth[v] = d;
            parent[v] = prev;
            size[v] = 1;
            for (WeightedEdge e: G.adj(v)) {
                int w = e.other(v);
                if (w != prev) {
                    dfs(G, w, d + 1, v);
                    size[v] += size[w];
                }
            }
        }
        
        private void hld(WeightedGraph G, int v, int prev, int weight) {
            if (head[chainNum] == -1) head[chainNum] = v;
            chain[v] = chainNum;
            base[v] = baseNum;
            val[baseNum++] = weight;
            int maxIndex = -1;
            int maxWeight = -1;
            for (WeightedEdge e: G.adj(v)) {
                int w = e.other(v);
                if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) {
                    maxIndex = w;
                    maxWeight = (int) e.weight();
                }
            }
            if (maxIndex != -1) hld(G, maxIndex, v, maxWeight);
            for (WeightedEdge e: G.adj(v)) {
                int w = e.other(v);
                if (w != prev && w != maxIndex) {
                    chainNum++;
                    hld(G, w, v, (int) e.weight());
                }
            }
        }
        
        /**
         * Returns the lowest common ancestor of vertex {@code v} and {@code w}.
         * 
         * @param v the first vertex
         * @param w the first vertex
         * @return the lowest common ancestor of vertex {@code v} and {@code w}
         */
        public int lca(int v, int w) {
            validateVertex(v);
            validateVertex(w);
            while (chain[v] != chain[w]) {
                if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
                else v = parent[head[chain[v]]];
            }
            if (depth[v] < depth[w]) return v;
            return w;
        }
        
        private int queryUp(int v, int w) {
            int ans = -1;
            while (chain[v] != chain[w]) {
                ans = Math.max(ans, st.rMaxQ(base[head[chain[v]]], base[v]));
                v = parent[head[chain[v]]];
            }      
            if (v == w) return ans;
            return Math.max(ans, st.rMaxQ(base[w] + 1, base[v]));
        }
        
        public int queryPath(int v, int w) {
            int lca = lca(v, w);
            return Math.max(queryUp(v, lca), queryUp(w, lca));
        }
        
        private void validateVertex(int v) {
            int V = size.length;
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
    }
    
    public class SegmentTree {
        private Node[] tree;
        private int[] array;
        private int N;
        
        private class Node {
            public int val;
            public Node(int val) {
                this.val = val;
            }
            
            public Node(Node left, Node right) {
                this.val = Math.max(left.val, right.val);
            }
        }
        
        public SegmentTree(int size, int[] arr, boolean oneIndexed) {
            array = new int[size + 1];
            for (int i = 1; i <= size ; i++) {
                array[i] = arr[i - (oneIndexed ? 0 : 1)];
            }
            tree = new Node[4 * size];
            build(1, 1, size);
            N = size;
        }

        public SegmentTree(int size) {
            array = new int[size + 1];
            tree = new Node[4 * size];
            build(1, 1, size);
            N = size;
        }
        

        private void build(int cur, int cL, int cR) {
            if (cL == cR) {
                tree[cur] = new Node(array[cL]);
                return;
            }
            int m = cL + (cR - cL) / 2;
            build(cur * 2, cL , m);
            build(cur * 2 + 1, m + 1, cR);
            tree[cur] = new Node(tree[cur * 2], tree[cur * 2 + 1]);
        }

        private void update(int cur, int cL, int cR, int ind, int val) {
            if (cL > ind || cR < ind) return;
            int m = cL + (cR - cL) / 2;
            update(cur * 2, cL, m, ind, val);
            update(cur * 2 + 1, m + 1, cR, ind, val);
            tree[cur].val = Math.max(tree[cur * 2].val, tree[cur * 2 + 1].val);
        }
        
        public void update(int ind, int val) {
            update(1, 1, N, ind, val);
        }

        private int rMaxQ(int cur, int cL, int cR, int l, int r) {
            if (cL > r || cR < l) return Integer.MIN_VALUE;
            if (cL >= l && cR <= r) return tree[cur].val;
            int m = cL + (cR - cL) / 2;
            int left = rMaxQ(cur * 2, cL, m, l, r);
            int right = rMaxQ(cur * 2 + 1, m + 1, cR, l, r);
            return Math.max(left, right);
        }

        public int rMaxQ(int l, int r) {
            return rMaxQ(1, 1, N, l, r);
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
    private static int getI(int point) {
        return point / grid[0].length;
    }
    private static int getJ(int point) {
        return point % grid[0].length;
    }
    */
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        int best = Integer.MAX_VALUE;
        WeightedGraph G = o.new WeightedGraph(N);
        for (int i = 0; i < M; i++) {
            G.addEdge(o.new WeightedEdge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt()));
        }
        KruskalMST mst = o.new KruskalMST(G);
        if (mst.unsed().isEmpty()) {
            out.println(-1);
            out.close();
            return;
        }
        for (int i = 0; i < N; i++) {
            if (!mst.uf.connected(0, i)) {
                out.println(-1);
                out.close();
                return;
            }
        }
        WeightedLCA lca = o.new WeightedLCA(mst.mst());
        for (WeightedEdge e: mst.unused) {
            int query = lca.queryPath(e.either(), e.other(e.either()));
            if ((int) e.weight() == query) continue;
            best = Math.min(best, (int) mst.weight() + (int) e.weight() - query);
        }
        if (best == Integer.MAX_VALUE) out.println(-1);
        else out.println(best);
        out.close();
    }
}
