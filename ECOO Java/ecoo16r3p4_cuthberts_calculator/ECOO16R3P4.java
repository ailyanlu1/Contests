package ecoo16r3p4_cuthberts_calculator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class ECOO16R3P4 {
    private static ECOO16R3P4 o = new ECOO16R3P4();
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
    
    private static class Pair {
        public int num;
        String op;
        
        public Pair(int num, String op) {
            this.num = num;
            this.op = op;
        }
        
        @Override
        public int hashCode() {
            return new Integer(num).hashCode();
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return num == p.num;
        }
    }
    
    private static Reader in;
    private static PrintWriter out;
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "DATA41.txt";
    private static final String OUTPUT_FILE_NAME = "OUTPUT41.txt";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    
    private static final int MAXN = 1000;
    
    public static void main(String[] args) throws IOException {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = o.new Reader(System.in);
        else in = o.new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            run(i);
            out.flush();
        }
        out.close();
    }
    
    private static char[] buttons;
    private static HashMap<Integer, String> used = new HashMap<Integer, String>();
    private static HashMap<Integer, String> base = new HashMap<Integer, String>();
    
    public static void run(int testCaseNum) throws IOException {
        buttons = in.nextLine().toCharArray();
        int N = in.nextInt();
        used.clear();
        base.clear();
        String binaryOp = "";
        boolean negate = false;
        Queue<Pair> q = o.new Queue<Pair>();
        for (int i = 0; i < buttons.length; i++) {
            if ('0' <= buttons[i] && buttons[i] <= '9') {
                Pair p = new Pair(buttons[i] - '0', "" + buttons[i]);
                q.enqueue(p);
                used.put(p.num, p.op);
                base.put(p.num, p.op);
            } else if (buttons[i] == '+' || buttons[i] == '-' || buttons[i] == '*') {
                binaryOp += buttons[i];
            } else if (buttons[i] == 'n') {
                negate = true;
            }
        }
        while (!q.isEmpty()) {
            Pair cur = q.dequeue();
            for (int i = 0; i < buttons.length; i++) {
                if ('0' <= buttons[i] && buttons[i] <= '9') {
                    Pair p = new Pair(cur.num * 10 + buttons[i] - '0', cur.op + " " + buttons[i]);
                    if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                        q.enqueue(p);
                        used.put(p.num, p.op);
                        base.put(p.num, p.op);
                    }
                }
            }
        }
        for (Map.Entry<Integer, String> e: base.entrySet()) {
            q.enqueue(new Pair(e.getKey(), e.getValue()));
        }
        while (!q.isEmpty()) {
            if (used.containsKey(N)) break;
            Pair cur = q.dequeue();
            for (int i = 0; i < buttons.length; i++) {
                if (buttons[i] == 's' && binaryOp.length() == 0) {
                    Pair p = new Pair(cur.num * cur.num, cur.op + " s");
                    if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                        q.enqueue(p);
                        used.put(p.num, p.op);
                    }
                } else if (buttons[i] == '+') {
                    for (Map.Entry<Integer, String> e: base.entrySet()) {
                        Pair p = new Pair(cur.num + e.getKey(), cur.op + " + " + e.getValue());
                        if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                            q.enqueue(p);
                            used.put(p.num, p.op);
                        }
                        if (negate) {
                            p = new Pair(cur.num - e.getKey(), cur.op + " + " + e.getValue() + " n");
                            if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                                q.enqueue(p);
                                used.put(p.num, p.op);
                            }
                        }
                    }
                } else if (buttons[i] == '-') {
                    for (Map.Entry<Integer, String> e: base.entrySet()) {
                        Pair p = new Pair(cur.num - e.getKey(), cur.op + " - " + e.getValue());
                        if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                            q.enqueue(p);
                            used.put(p.num, p.op);
                        }
                        if (negate) {
                            p = new Pair(cur.num + e.getKey(), cur.op + " - " + e.getValue() + " n");
                            if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                                q.enqueue(p);
                                used.put(p.num, p.op);
                            }
                        }
                    }
                } else if (buttons[i] == '*') {
                    for (Map.Entry<Integer, String> e: base.entrySet()) {
                        Pair p = new Pair(cur.num * e.getKey(), cur.op + " * " + e.getValue());
                        if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                            q.enqueue(p);
                            used.put(p.num, p.op);
                        }
                        if (negate) {
                            p = new Pair(cur.num * -e.getKey(), cur.op + " * " + e.getValue() + " n");
                            if (Math.abs(p.num) <= MAXN && !base.containsKey(p.num)) {
                                q.enqueue(p);
                                used.put(p.num, p.op);
                            }
                        }
                    }
                } // if else
            } // for i
        } // while
        out.print(used.get(N));
        if (binaryOp.length() > 0) out.print(" " + binaryOp.charAt(0));
        out.println();
    } // run method
}
