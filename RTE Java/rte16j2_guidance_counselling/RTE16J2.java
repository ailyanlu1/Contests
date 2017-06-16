package rte16j2_guidance_counselling;

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
import java.util.StringTokenizer;

public class RTE16J2 {
    private static RTE16J2 o = new RTE16J2();
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
            assert isMinHeap();
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
            assert capacity > n;
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
            assert isMinHeap();
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
            assert isMinHeap();
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
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static class Student implements Comparable<Student> {
        public int c, m;
        
        public Student(int c, int m) {
            this.c = c;
            this.m = m;
        }

        @Override
        public int compareTo(Student s) {
            if (c != s.c) return c - s.c;
            return m - s.m;
        }        
    }
    
    public static void main(String[] args) throws IOException {
        int Q = in.nextInt();
        MinPQ<Student> pq = o.new MinPQ<Student>();
        int i = 0;
        for (int q = 0; q < Q; q++) {
            String o = in.next();
            if (o.equals("ADD")) {
                String C = in.next().trim();
                int c = 0;
                if (C.equals("PINK")) c = 1;
                else if (C.equals("GREEN")) c = 2;
                int m = in.nextInt();
                pq.insert(new Student(c, m));
            } else if (o.equals("NEXT")){
                if (pq.isEmpty()) {
                    out.println("NONE");
                    continue;
                }
                Student s = pq.delMin();
                if (s.c == 0) {
                    out.println("BLUE " + s.m);
                } else if (s.c == 1) {
                    out.println("PINK " + s.m);
                } else {
                    out.println("GREEN " + s.m);
                }
            } else {
                q--;
            }
        }
        out.close();
    }
}
