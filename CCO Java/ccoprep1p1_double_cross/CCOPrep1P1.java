package ccoprep1p1_double_cross;

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
import java.util.StringTokenizer;

public class CCOPrep1P1 {
    private static CCOPrep1P1 o = new CCOPrep1P1();
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
    
    public class Pair<Item, Item2> {
        public Item first;
        public Item2 second;

        public Pair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int hashCode() {
            return 31 * first.hashCode() + second.hashCode();
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return p.first.equals(first) && p.second.equals(second);
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
    
    public class FenwickTree {

        long[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

        public FenwickTree(int size) {
            array = new long[size + 1];
        }

        /**
         * Range Sum query from 1 to ind
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind index
         * @return sum
         */
        public long rsq(int ind) {
            // assert ind > 0;
            long sum = 0;
            for (int x = ind; x > 0; x -= (x & -x)) {
                sum = (sum + array[x]) % MOD;
            }
            return sum;
        }

        /**
         * Range Sum Query from a to b.
         * Search for the sum from array index from a to b
         * a and b are 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  a left index
         * @param  b right index
         * @return sum
         */
        public long rsq(int a, int b) {
            // assert b >= a && a > 0 && b > 0;
            return rsq(b) - rsq(a - 1);
        }

        /**
         * Update the array at ind and all the affected regions above ind.
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind   index
         * @param  value value
         */
        public void update(int ind, long value) {
            // assert ind > 0;
            for (int x = ind; x < array.length; x += (x & -x)) {
                array[x] = (array[x] + value) % MOD;
            }
        }

        public int size() {
            return array.length - 1;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    private static Queue<Pair<Integer, Integer>> added = o.new Queue<Pair<Integer, Integer>>();
    private static FenwickTree count, add, sub;
    private static final long MOD = (long) (1e9 + 9);
    private static final int SIZE = 10000;
    
    public static void main(String[] args) throws IOException {
        int R = in.nextInt();
        int C = in.nextInt();
        int[][] left = new int[R + 2][C + 2];
        int[][] right = new int[R + 2][C + 2];
        int[][] up = new int[R + 2][C + 2];
        int[][] down = new int[R + 2][C + 2];
        boolean[][] grid = new boolean[R + 2][C + 2];
        for (int i = 0; i < R + 2; i++) {
            for (int j = 0; j < C + 2; j++) {
                grid[i][j] = true;
            }
        }
        int N = in.nextInt();
        count = o.new FenwickTree(SIZE);
        add = o.new FenwickTree(SIZE);
        sub = o.new FenwickTree(SIZE);
        for (int i = 0; i < N; i++) {
            grid[in.nextInt()][in.nextInt()] = false;
        }
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (grid[i][j]) left[i][j] = left[i][j - 1] + 1;
                else left[i][j] = 0;
            }
            for (int j = C; j >= 1; j--) {
                if (grid[i][j]) right[i][j] = right[i][j + 1] + 1;
                else right[i][j] = 0;
            }
        }
        for (int j = 1; j <= C; j++) {
            for (int i = 1; i <= R; i++) {
                if (grid[i][j]) up[i][j] = up[i - 1][j] + 1;
                else up[i][j] = 0;
            }
            for (int i = R; i >= 1; i--) {
                if (grid[i][j]) down[i][j] = down[i + 1][j] + 1;
                else down[i][j] = 0;
            }
        }
        long ans = 0;
        for (int j = 1; j <= C; j++) {
            int prev = 0;
            int prevUp = 0;
            int cur = 0;
            for (int i = 1; i <= R; i++) {
                if (!grid[i][j]) {
                    prev = prevUp = cur = 0;
                    while (!added.isEmpty()) {
                        remove(added.dequeue());
                    }
                } else {
                    cur = Math.min(left[i][j], right[i][j]) - 1;
                    if (cur > 1) {
                        long total = 0;
                        total += count.rsq(cur - 1, SIZE) * cur * (cur - 1) / 2 + add.rsq(cur - 2) * cur - sub.rsq(cur - 2);
                        ans = (ans + total * down[i + 1][j] % MOD) % MOD;
                    }
                }
                add(prev, prevUp);
                prev = cur;
                prevUp = up[i - 1][j];
            }
            while (!added.isEmpty()) {
                remove(added.dequeue());
            }
        }
        out.println(ans);
        out.close();
    }
    
    private static void add(int prev, int prevUp) {
        if (prev == 0 || prevUp == 0) return;
        added.enqueue(o.new Pair<Integer, Integer>(prev, prevUp));
        count.update(prev, prevUp);
        add.update(prev, prev * prevUp);
        sub.update(prev, prev * (prev + 1) / 2 * prevUp);
    }
    
    private static void remove(Pair<Integer, Integer> p) {
        count.update(p.first, -p.second);
        add.update(p.first, p.first * -p.second);
        sub.update(p.first, p.first * (p.first + 1) / 2 * -p.second);
    }
}
