package dmpg16s5_pizza_bag;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class DMPG16S5 {
    private static DMPG16S5 o = new DMPG16S5();
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
    
    public class PrefixSumArray {
        private long[] prefixSum;
        
        /**
         * Initializes a prefix sum array for the given {@code array} array.
         * @param array the original array of integers
         */    
        public PrefixSumArray(long[] array) {
            prefixSum = new long[array.length];
            prefixSum[0] = array[0];
            for (int i = 1; i < prefixSum.length; i++) {
                prefixSum[i] = prefixSum[i - 1] + array[i];
            }
        }
        
        /**
         * Returns the cumulative sum from index 0 to <em>end</em>
         * @param end the 0-based end index (inclusive)
         * @return the cumulative sum
         */
        public long query(int end) {
            if (end < 0 || end >= prefixSum.length) throw new ArrayIndexOutOfBoundsException();
            return prefixSum[end];
        }
        
        /**
         * Returns the cumulative sum from index <em>start</em> to <em>end</em>
         * @param start the 0-based start index (inclusive)
         * @param end the 0-based end index (inclusive)
         * @return the cumulative sum
         */
        public long query(int start, int end) {
            if (start < 0 || end < 0 || start >= prefixSum.length || end >= prefixSum.length) throw new ArrayIndexOutOfBoundsException();
            if (end < start) throw new IllegalArgumentException();
            return query(end) - query(start - 1);
        }
    }
    
    public class Deque<Item> implements Iterable<Item> {
        private Node<Item> first;    // beginning of deque
        private Node<Item> last;     // end of deque
        private int n;               // number of elements on deque

        // helper linked list class
        private class Node<Item> {
            private Item item;
            private Node<Item> next;
            private Node<Item> prev;
        }

        /**
         * Initializes an empty deque.
         */
        public Deque() {
            first = null;
            last  = null;
            n = 0;
        }

        /**
         * Returns true if this deque is empty.
         *
         * @return {@code true} if this deque is empty; {@code false} otherwise
         */
        public boolean isEmpty() {
            return n == 0;
        }

        /**
         * Returns the number of items in this deque.
         *
         * @return the number of items in this deque
         */
        public int size() {
            return n;
        }

        /**
         * Returns the item at the front of the deque.
         *
         * @return the item at the front of the deque
         * @throws NoSuchElementException if this deque is empty
         */
        public Item peekFirst() {
            if (isEmpty()) throw new NoSuchElementException("deque underflow");
            return first.item;
        }
        
        /**
         * Returns the item at the end of the deque.
         *
         * @return the item at the end of the deque
         * @throws NoSuchElementException if this deque is empty
         */
        public Item peekLast() {
            if (isEmpty()) throw new NoSuchElementException("deque underflow");
            return last.item;
        }
        
        /**
         * Adds the item to the front of the deque.
         *
         * @param  item the item to add
         */
        public void addFirst(Item item) {
            n++;
            if (first == null) {
                Node<Item> newFirst = new Node<Item>();
                newFirst.item = item;
                first = newFirst;
                last = newFirst;
            } else {
                Node<Item> newFirst = new Node<Item>();
                newFirst.item = item;
                newFirst.next = first;
                first.prev = newFirst;
                first = newFirst;
            }
        }

        /**
         * Adds the item to the end of the deque.
         *
         * @param  item the item to add
         */
        public void addLast(Item item) {
            n++;
            if (last == null) {
                Node<Item> newLast = new Node<Item>();
                newLast.item = item;
                first = newLast;
                last = newLast;
            } else {
                Node<Item> newLast = new Node<Item>();
                newLast.item = item;
                newLast.prev = last;
                last.next = newLast;
                last = newLast;
            }
        }

        /**
         * Removes and returns the item at the front of the deque
         *
         * @return the item on at the front of the deque
         * @throws NoSuchElementException if this deque is empty
         */
        public Item removeFirst() {
            if (isEmpty()) throw new NoSuchElementException("deque underflow");
            n--;
            Item item = first.item;
            first = first.next;
            if (first == null) last = null;
            else first.prev = null;
            return item;
        }
        
        /**
         * Removes and returns the item at the end of the deque
         *
         * @return the item on at the end of the deque
         * @throws NoSuchElementException if this deque is empty
         */
        public Item removeLast() {
            if (isEmpty()) throw new NoSuchElementException("deque underflow");
            n--;
            Item item = last.item;
            last = last.prev;
            if (last == null) first = null;
            else last.next = null;
            return item;
        }

        /**
         * Returns a string representation of this deque.
         *
         * @return the sequence of items from from to back
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
         * Returns an iterator that iterates over the items in this deque from front to back
         *
         * @return an iterator that iterates over the items in this deque from front to back
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
    
    public class Pair<Item, Item2> {
        public Item first;
        public Item2 second;
        
        public Pair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }
    }
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int N = in.nextInt();
        int K = in.nextInt();
        long[] arr = new long[N + K - 1];
        for (int i = 0; i < N; i++) {
            long d = in.nextLong();
            arr[i] = d;
            if (i + N < arr.length) arr[i+N] = d;
        }
        PrefixSumArray psa = o.new PrefixSumArray(arr);
        Deque<Pair<Integer, Long>> dq = o.new Deque<Pair<Integer, Long>>();
        dq.addFirst(o.new Pair<Integer, Long>(-1, 0L));
        long ans = 0;
        for (int i = 0; i < arr.length; i++) {
            Pair<Integer, Long> add = o.new Pair<Integer, Long>(i, psa.query(i));
            while (!dq.isEmpty() && dq.peekLast().second >= psa.query(i)) {
                dq.removeLast();
            }
            dq.addLast(add);
            while (dq.peekFirst().first < i - K) {
                dq.removeFirst();
            }
            ans = Math.max(ans, psa.query(i) - dq.peekFirst().second);
        }
        out.println(ans);
        out.close();
    }
}
