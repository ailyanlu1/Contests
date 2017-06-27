package coi06p3_sabor;

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

public class COI06P3 {
    private static COI06P3 o = new COI06P3();
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
    
    public static class Queue<Item> implements Iterable<Item> {
        private Node<Item> first;    // beginning of queue
        private Node<Item> last;     // end of queue
        private int n;               // number of elements on queue

        // helper linked list class
        private static class Node<Item> {
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
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    private static int B, S;
    private static int[][] grid;
    private static int[][] adj = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    private static long[] ans = {0, 0};
    private static final int MAXXY = 1000;
    
    public static void main(String[] args) throws IOException {
        B = in.nextInt();
        S = in.nextInt() + 1;
        grid = new int[2 * MAXXY + 1][2 * MAXXY + 1];
        grid[MAXXY][MAXXY] = 1;
        Queue<Integer> qx = new Queue<Integer>();
        Queue<Integer> qy = new Queue<Integer>();
        qx.enqueue(MAXXY);
        qy.enqueue(MAXXY);
        int minx = MAXXY;
        int maxx = MAXXY;
        int miny = MAXXY;
        int maxy = MAXXY;
        for (int i = 0; i < B; i++) {
            int x = in.nextInt();
            int y = in.nextInt();
            x += MAXXY;
            y += MAXXY;
            grid[x][y] = -1;
            minx = Math.min(minx, x);
            maxx = Math.max(maxx, x);
            miny = Math.min(miny, y);
            maxy = Math.max(maxy, y);
        }
        minx--;
        maxx++;
        miny--;
        maxy++;
        while (!qx.isEmpty()) {
            int x = qx.dequeue();
            int y = qy.dequeue();
            ans[(x + y) % 2]++;
            if (grid[x][y] == S) continue;
            if (x == minx || x == maxx) edge(x, y);
            if (y == miny || y == maxy) edge(x, y);
            for (int i = 0; i < adj.length; i++) {
                int x2 = x + adj[i][0];
                int y2 = y + adj[i][1];
                if (x2 < minx || x2 > maxx || y2 < miny || y2 > maxy || grid[x2][y2] != 0) continue;
                grid[x2][y2] = grid[x][y] + 1;
                qx.enqueue(x2);
                qy.enqueue(y2);
            }
        }
        if (grid[minx][miny] > 0) corner(minx, miny);
        if (grid[minx][maxy] > 0) corner(minx, maxy);
        if (grid[maxx][miny] > 0) corner(maxx, miny);
        if (grid[maxx][maxy] > 0) corner(maxx, maxy);
        out.println(ans[0] + " " + ans[1]);
        out.close();
    }
    
    private static void edge(int x, int y) {
        ans[(x + y) % 2] += (long) (S - grid[x][y]) / 2;
        ans[1 - (x + y) % 2] += (long) (S - grid[x][y] + 1) / 2;
    }
    
    private static void corner(int x, int y) {
        ans[(x + y) % 2] += (long) ((S - grid[x][y]) / 2) * ((S - grid[x][y]) / 2);
        ans[1 - (x + y) % 2] += (long) ((S - grid[x][y] + 1) / 2) * ((S - grid[x][y] - 1) / 2);
    }
}
