import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class ECOO15R2P4 {
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    private static ECOO15R2P4 o = new ECOO15R2P4();
    
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
    
    public class Rectangle {
        public int a;
        public int b;
        public int id;
        public Rectangle(int a, int b, int id) {
            this.a = Integer.min(a, b);
            this.b = Integer.max(a, b);
            this.id = id;
        }
        @Override
        public int hashCode() {
            return a+b+id;
        }
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Rectangle)) {
                return false;
            }
            Rectangle r = (Rectangle) o;
            return a == r.a && b == r.b && id == r.id;
        }
    }
    
    public static void main(String[] args) throws IOException {
        Reader file = o.new Reader(System.in); // TODO REMEMBER TO CHANGE THE FILE NAME
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(file);
        } // for i
    } // main method
    
    public static void run(Reader in) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
        int N = in.nextInt();
        Queue<Rectangle> q = o.new Queue<Rectangle>();
        HashSet<Rectangle>[] rectangles = new HashSet[32];
        HashSet<Rectangle> done = new HashSet<Rectangle>();
        for (int i = 0; i < rectangles.length; i++) {
            rectangles[i] = new HashSet<Rectangle>();
        }
        for (int i = 0; i < N; i++) {
            int a = in.nextInt();
            int b = in.nextInt();
            Rectangle r = o.new Rectangle(a, b, 1 << i);
            rectangles[a].add(r);
            rectangles[b].add(r);
            q.enqueue(r);
        }
        int ans = -1;
        while (!q.isEmpty()) {
            Rectangle r = q.dequeue();
            if (r.id == (1 << N) - 1) {
                ans = Integer.max(ans, r.a * 2 + r.b * 2);
                continue;
            }
            if (done.contains(r)) continue;
            done.add(r);
            HashSet<Rectangle> check = new HashSet<Rectangle>();
            check.addAll(rectangles[r.a]);
            check.addAll(rectangles[r.b]);
            for (Rectangle c: check) {
                if ((c.id & r.id) != 0)
                    continue;
                if (c.a == r.a) {
                    Rectangle next = o.new Rectangle(r.a, r.b + c.b, c.id | r.id);
                    q.enqueue(next);
                    rectangles[next.a].add(next);
                    rectangles[next.b].add(next);
                }
                if (c.b == r.b) {
                    Rectangle next = o.new Rectangle(r.a + c.a, r.b, c.id | r.id);
                    q.enqueue(next);
                    rectangles[next.a].add(next);
                    rectangles[next.b].add(next);
                }
                if (c.b == r.a) {
                    Rectangle next = o.new Rectangle(r.a, r.b + c.a, c.id | r.id);
                    q.enqueue(next);
                    rectangles[next.a].add(next);
                    rectangles[next.b].add(next);
                }
                if (c.a == r.b) {
                    Rectangle next = o.new Rectangle(r.a + c.b, r.b, c.id | r.id);
                    q.enqueue(next);
                    rectangles[next.a].add(next);
                    rectangles[next.b].add(next);
                }
            }
        }
        if (ans == -1) System.out.println("Not Possible");
        else System.out.println(ans);
    } // run method
} // ECOO15R2P4 class
