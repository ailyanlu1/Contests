import java.io.BufferedInputStream;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class ECOO13R1P1 {
    private static final int NUM_OF_TEST_CASES = 1; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
    
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
    
    private static ECOO13R1P1 o = new ECOO13R1P1();
    
    public static void main(String[] args) {
        Scanner fileScanner = new Scanner(new BufferedInputStream(System.in));
        for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
            run(fileScanner);
        } // for i
    } // main method
    
    public static void run(Scanner f) { // if you change the method of reading input, then the parameter type may have to be changed
        String line;
        Queue<Integer> q = o.new Queue<Integer>();
        int lateToday = 0;
        int next = f.nextInt();
        f.nextLine();
        while (!(line = f.nextLine()).equals("EOF")) {
            if (line.trim().equals("TAKE")) {
                lateToday++;
                q.enqueue(next++);
                if (next == 1000) {
                    next = 1;
                }
            } else if (line.trim().equals("SERVE")) {
                q.dequeue();
            } else {
                System.out.println(lateToday + " " + q.size() + " " + next);
                lateToday = 0;
                q = o.new Queue<Integer>();
            }
        }
    } // run method
}
