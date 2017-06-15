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
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class MNYC17P5 { // 60/100 TLE
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
	
	public class Stack<Item> implements Iterable<Item> {
	    private Node<Item> first;     // top of stack
	    private int n;                // size of the stack

	    // helper linked list class
	    private class Node<Item> {
	        private Item item;
	        private Node<Item> next;
	    }

	    /**
	     * Initializes an empty stack.
	     */
	    public Stack() {
	        first = null;
	        n = 0;
	    }

	    /**
	     * Returns true if this stack is empty.
	     *
	     * @return true if this stack is empty; false otherwise
	     */
	    public boolean isEmpty() {
	        return first == null;
	    }

	    /**
	     * Returns the number of items in this stack.
	     *
	     * @return the number of items in this stack
	     */
	    public int size() {
	        return n;
	    }

	    /**
	     * Adds the item to this stack.
	     *
	     * @param  item the item to add
	     */
	    public void push(Item item) {
	        Node<Item> oldfirst = first;
	        first = new Node<Item>();
	        first.item = item;
	        first.next = oldfirst;
	        n++;
	    }

	    /**
	     * Removes and returns the item most recently added to this stack.
	     *
	     * @return the item most recently added
	     * @throws NoSuchElementException if this stack is empty
	     */
	    public Item pop() {
	        if (isEmpty()) throw new NoSuchElementException("Stack underflow");
	        Item item = first.item;        // save item to return
	        first = first.next;            // delete first node
	        n--;
	        return item;                   // return the saved item
	    }


	    /**
	     * Returns (but does not remove) the item most recently added to this stack.
	     *
	     * @return the item most recently added to this stack
	     * @throws NoSuchElementException if this stack is empty
	     */
	    public Item peek() {
	        if (isEmpty()) throw new NoSuchElementException("Stack underflow");
	        return first.item;
	    }

	    /**
	     * Returns a string representation of this stack.
	     *
	     * @return the sequence of items in this stack in LIFO order, separated by spaces
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
	     * Returns an iterator to this stack that iterates through the items in LIFO order.
	     *
	     * @return an iterator to this stack that iterates through the items in LIFO order
	     */
	    public Iterator<Item> iterator() {
	        return new ListIterator<Item>(first);
	    }

	    // an iterator, doesn't implement remove() since it's optional
	    private class ListIterator<Item> implements Iterator<Item> {
	        private Node<Item> current;

	        public ListIterator(Node<Item> first) {
	            current = first;
	        }

	        public boolean hasNext() {
	            return current != null;
	        }

	        public void remove() {
	            throw new UnsupportedOperationException();
	        }

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
	    	int result = 31 * v + w;
	    	result = 31 * result + (int) (new Double(weight).hashCode() ^ (new Double(weight).hashCode() >>> 32));
	    	return result;
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
	
	public class WeightedPath implements Comparable<WeightedPath>, Iterable<WeightedEdge>{
		private ArrayList<WeightedEdge> list;
		private double length;
		private double longest;
		private double shortest;
		
		public WeightedPath() {
			list = new ArrayList<WeightedEdge>();
			length = 0;
			longest = 0;
			shortest = Double.MAX_VALUE;
		}
		
		public WeightedPath(Iterable<WeightedEdge> iter) {
			list = new ArrayList<WeightedEdge>();
			length = 0;
			longest = 0;
			shortest = Double.MAX_VALUE;
			if (iter == null) return;
			for (WeightedEdge e: iter) {
				list.add(e);
				length += e.weight();
				shortest = Double.min(shortest, e.weight());
				longest = Double.max(longest, e.weight());
			}
		}
		
		public double length() {
			return length;
		}
		
		public int size() {
			return list.size();
		}
		
		public double longest() {
			return longest;
		}
		
		public double shortest() {
			return shortest;
		}
		
		public WeightedEdge get(int i) {
			if (i < 0 || i >= list.size()) throw new IndexOutOfBoundsException("Index is not between 0 and " + (list.size()-1));
			return list.get(i);
		}
		
		public void add(WeightedEdge e) {
			list.add(e);
			length += e.weight();
			shortest = Double.min(shortest, e.weight());
			longest = Double.max(longest, e.weight());
		}
		
		public void addAll(Iterable<WeightedEdge> iter) {
			if (iter == null) return;
			for (WeightedEdge e: iter) {
				list.add(e);
				length += e.weight();
				shortest = Double.min(shortest, e.weight());
				longest = Double.max(longest, e.weight());
			}
		}
		
		public void addAll(WeightedPath path) {
			if (path == null) return;
			for (WeightedEdge e: path) {
				list.add(e);
				length += e.weight();
				shortest = Double.min(shortest, e.weight());
				longest = Double.max(longest, e.weight());
			}
		}

		@Override
		public int compareTo(WeightedPath p) {
			if (length > p.length) return 1;
			else if (length < p.length) return -1;
			if (shortest > p.shortest) return 1;
			else if (shortest < p.shortest) return -1;
			return 0;
		}

		@Override
		public Iterator<WeightedEdge> iterator() {
			return list.iterator();
		}
		
		@Override
		public boolean equals(Object o){
			if (o == this) return true;
	        if (!(o instanceof WeightedPath)) {
	            return false;
	        }
	        WeightedPath p = (WeightedPath) o;
	        return list.equals(p.list);
		}
	}
	
	public class YenKSP {
		private final int source;
		private final int sink;
		private WeightedGraph G;
		private final int V;
		private ArrayList<WeightedPath> paths;
		private MinPQ<WeightedPath> pq;
		private HashSet<WeightedEdge> removedEdges = new HashSet<WeightedEdge>();
		HashSet<Integer> removedVerticies = new HashSet<Integer>();
		private double[] distTo;
		private WeightedEdge[] edgeTo;
		private IndexMinPQ<Double> ipq;
		
		public YenKSP(WeightedGraph G, int source, int sink) {
			this.G = G;
			this.V = G.V();
			validateVertex(source);
			validateVertex(sink);
			this.source = source;
			this.sink = sink;
			this.paths = new ArrayList<WeightedPath>();
			pq = new MinPQ<WeightedPath>();
			paths.add(dijkstraSP(source, sink));
			noDup.put((int) paths.get(0).length(), (int) paths.get(0).shortest());
		}
		
		private boolean find(int k) {
			if (paths.get(k - 1) == null || paths.get(k - 1).size() == 0) {
				paths.add(new WeightedPath());
				return true;
			}
			int spurNode = source;
			for (int i = 0; i < paths.get(k - 1).size(); i++) {
				WeightedPath rootPath = new WeightedPath();
				removedEdges.clear();
				removedVerticies.clear();
				for (int j = 0; j < i; j++) {
					rootPath.add(paths.get(k - 1).get(j));
				}
				for (WeightedPath p: paths) {
					if (p.size() < rootPath.size()) continue;
					WeightedPath pPath = new WeightedPath();
					for (int j = 0; j < i && j < p.size(); j++) {
						pPath.add(p.get(j));
					}
					if (rootPath.equals(pPath) || rootPath.size() == 0) {
						removedEdges.add(p.get(i));
					}
				}
				int last = source;
				removedVerticies.add(source);
				for (WeightedEdge e: rootPath) {
					removedVerticies.add(e.other(last));
					last = e.other(last);
				}
				WeightedPath spurPath = dijkstraSP(spurNode, sink);
				WeightedPath totalPath = new WeightedPath();
				totalPath.addAll(rootPath);
				totalPath.addAll(spurPath);
				if (totalPath.length() > 0 && spurPath != null) pq.insert(totalPath);
				spurNode = paths.get(k - 1).get(i).other(spurNode);
			}
			if (pq.isEmpty()) return true;
			WeightedPath next = pq.delMin();
			paths.add(next);
			if (!noDup.containsKey((int) next.length())) {
				noDup.put((int) next.length(), (int) next.shortest());
			}
			noDup.put((int) next.length(), Math.min((int) next.shortest, noDup.get((int) next.length())));
			return false;
		}
		
		public WeightedPath KSP(int K) {
			if (K >= paths.size()) {
				for (int k = paths.size(); noDup.size() < K; k++) {
					if (find(k)) return null;
				}
			}
			return paths.get(K);
		}
		
		private WeightedPath dijkstraSP(int s, int t) {
			distTo = new double[G.V()];
	        edgeTo = new WeightedEdge[G.V()];

	        validateVertex(s);

	        for (int v = 0; v < G.V(); v++)
	            distTo[v] = Double.POSITIVE_INFINITY;
	        distTo[s] = 0.0;

	        // relax vertices in order of distance from s
	        ipq = new IndexMinPQ<Double>(G.V());
	        ipq.insert(s, distTo[s]);
	        while (!ipq.isEmpty()) {
	            int v = ipq.delMin();
	            for (WeightedEdge e : G.adj(v)) {
	            	if (removedEdges.contains(e) || removedVerticies.contains(e.other(v))) continue;
	            	relax(e, v);
	            }
	        }
	        if(edgeTo[t] == null) return null;
	        Stack<WeightedEdge> path = new Stack<WeightedEdge>();
	        int x = t;
	        for (WeightedEdge e = edgeTo[t]; e != null; e = edgeTo[x]) {
	            path.push(e);
	            x = e.other(x);
	        }
	        WeightedPath ret = new WeightedPath();
	        while (!path.isEmpty()) {
	        	ret.add(path.pop());
	        }
	        return ret;
		}
		
	    private void relax(WeightedEdge e, int v) {
	        int w = e.other(v);
	        if (distTo[w] > distTo[v] + e.weight()) {
	            distTo[w] = distTo[v] + e.weight();
	            edgeTo[w] = e;
	            if (ipq.contains(w)) ipq.decreaseKey(w, distTo[w]);
	            else                ipq.insert(w, distTo[w]);
	        }
	    }
		
		
		
	    // throw an IllegalArgumentException unless {@code 0 <= v < V}
	    private void validateVertex(int v) {
	        if (v < 0 || v >= V)
	            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
	    }
	}
	
	private static TreeMap<Integer, Integer> noDup = new TreeMap<Integer, Integer>();
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    	int N = in.nextInt();
    	int M = in.nextInt();
    	int A = in.nextInt() - 1;
    	int B = in.nextInt() - 1;
    	int Q = in.nextInt();
    	int[] k = new int[Q];
    	WeightedGraph G = o.new WeightedGraph(N);
    	for (int i = 0; i < M; i++) {
    		G.addEdge(o.new WeightedEdge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt()));
    	}
    	YenKSP ksp = o.new YenKSP(G, A, B);
    	int max = 0;
    	for (int i = 0; i < Q; i++) {
    		k[i] = in.nextInt() - 1;
    		max = Integer.max(max, k[i]);
    	}
    	int[] length = new int[max + 1];
    	int[] shortest = new int[max + 1];
    	ksp.KSP(max);
    	int ind = 0;
    	Arrays.fill(length, -1);
    	Arrays.fill(shortest, -1);
    	for (Map.Entry<Integer, Integer> p: noDup.entrySet()) {
    		length[ind] = p.getKey();
    		shortest[ind] = p.getValue();
    		ind++;
    	}
    	for (int i = 0; i < k.length; i++) {
    		if (length[k[i]] == -1) {
    			System.out.println(-1);
    		} else {
    			System.out.println(length[k[i]] + " " + shortest[k[i]]);
    		}
    	}
		out.close();
	}
}
