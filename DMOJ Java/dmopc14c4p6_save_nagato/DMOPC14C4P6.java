import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class DMOPC14C4P6 {
    private static DMOPC14C4P6 o = new DMOPC14C4P6();
    public class DataInputStreamReader {
        private final int BUFFER_SIZE = 1 << 16;
        private int MAX_LENGTH = 64;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public DataInputStreamReader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public DataInputStreamReader(InputStream inputStream, int length) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
            MAX_LENGTH = length;
        }

        public DataInputStreamReader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        
        public DataInputStreamReader(String file_name, int length) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
            MAX_LENGTH = length;
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[MAX_LENGTH];
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n' || c == '\r') break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg) c = read();

            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg) return -ret;
            return ret;
        }
        
        public char nextChar() throws IOException {
            int c = read();
            while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) {
                c = read();
            }
            return (char) c;
        }
        
        public String next() throws IOException {
            byte[] buf = new byte[MAX_LENGTH];
            int cnt = 0, c;
            c = read();
            while(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) {
                c = read();
            }
            buf[cnt++] = (byte) c;
            while ((c = read()) != -1) {
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead) fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null) return;
            din.close();
        }
    }

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
    
    private static DataInputStreamReader in = o.new DataInputStreamReader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    /*
    private static char[][] grid;
    
    private static boolean isPoint(int i, int j) {
        return (i >= 0 && i < grid.length && j >= 0 && j < grid[0].length);
    }
    private static int toPoint(int i, int j) {
        return i * grid[0].length + j;
    }
    */
    
    private static Bag<Integer>[] adj;
    private static int up[], down[];
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        adj = new Bag[N + 1];
        for (int v = 0; v <= N; v++) {
            adj[v] = o.new Bag<Integer>();
        }
        up = new int[N + 1];
        down = new int[N + 1];
        adj[0].add(1);
        for (int i = 0; i < N - 1; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            adj[u].add(v);
            adj[v].add(u);
        }
        down(0, -1);
        up(0, -1);
        for (int i = 1; i <= N; i++) {
            out.println(Math.max(up[i], down[i]));
        }
        out.close();
    }
    
    public static int down(int v, int last) {
        int ret = 1;
        for (int w: adj[v]) {
            if (w == last) continue;
            ret = Math.max(ret, down(w, v) + 1);
        }
        return down[v] = ret;
    }
    
    public static void up(int v, int last) {
        int best1 = 0;
        int best2 = 0;
        for (int w: adj[v]) {
            if (w == last) continue;
            if (down[w] > best1) {
                best2 = best1;
                best1 = down[w];
            } else if (down[w] > best2) {
                best2 = down[w];
            }
        }
        for (int w: adj[v]) {
            if (w == last) continue;
            up[w] = up[v] + 1;
            if (down[w] != best1) {
                up[w] = Math.max(up[w], best1 + 2);
            } else if (best2 != 0) {
                up[w] = Math.max(up[w], best2 + 2);
            }
            up(w, v);
        }
    }
}
