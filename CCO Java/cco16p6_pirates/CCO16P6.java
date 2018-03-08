import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class CCO16P6 {
    private static CCO16P6 o = new CCO16P6();
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
    
    public class AVLTree {

        /**
         * The root node.
         */
        private Node root;

        /**
         * This class represents an inner node of the AVL tree.
         */
        private class Node {
            private final long key;   // the key
            private int val;       // the associated value
            private int height;      // height of the subtree
            private int size;        // number of nodes in subtree
            private int weight;
            private long sum;
            private Node left;       // left subtree
            private Node right;      // right subtree

            public Node(long key, int val, int height, int size, int weight, long sum) {
                this.key = key;
                this.val = val;
                this.size = size;
                this.height = height;
                this.weight = weight;
                this.sum = sum;
            }
        }

        /**
         * Initializes an empty symbol table.
         */
        public AVLTree() {
        }

        /**
         * Checks if the symbol table is empty.
         * 
         * @return {@code true} if the symbol table is empty.
         */
        public boolean isEmpty() {
            return root == null;
        }

        /**
         * Returns the number key-value pairs in the symbol table.
         * 
         * @return the number key-value pairs in the symbol table
         */
        public int size() {
            return size(root);
        }

        /**
         * Returns the number of nodes in the subtree.
         * 
         * @param x the subtree
         * 
         * @return the number of nodes in the subtree
         */
        private int size(Node x) {
            if (x == null) return 0;
            return x.size;
        }

        /**
         * Returns the height of the internal AVL tree. It is assumed that the
         * height of an empty tree is -1 and the height of a tree with just one node
         * is 0.
         * 
         * @return the height of the internal AVL tree
         */
        public int height() {
            return height(root);
        }

        /**
         * Returns the height of the subtree.
         * 
         * @param x the subtree
         * 
         * @return the height of the subtree.
         */
        private int height(Node x) {
            if (x == null) return -1;
            return x.height;
        }
        
        public int weight() {
            return weight(root);
        }
        
        private int weight(Node x) {
            if (x == null) return 0;
            return x.weight;
        }
        
        public long sum() {
            return sum(root);
        }
        
        private long sum(Node x) {
            if (x == null) return 0;
            return x.sum;
        }

        /**
         * Returns the value associated with the given key.
         * 
         * @param key the key
         * @return the value associated with the given key if the key is in the
         *         symbol table and {@code null} if the key is not in the
         *         symbol table
         * @throws IllegalArgumentException if {@code key} is {@code null}
         */
        public int get(long key) {
            Node x = get(root, key);
            if (x == null) return -1;
            return x.val;
        }

        /**
         * Returns value associated with the given key in the subtree or
         * {@code null} if no such key.
         * 
         * @param x the subtree
         * @param key the key
         * @return value associated with the given key in the subtree or
         *         {@code null} if no such key
         */
        private Node get(Node x, long key) {
            if (x == null) return null;
            if (key < x.key) return get(x.left, key);
            else if (key > x.key) return get(x.right, key);
            else return x;
        }

        /**
         * Checks if the symbol table contains the given key.
         * 
         * @param key the key
         * @return {@code true} if the symbol table contains {@code key}
         *         and {@code false} otherwise
         * @throws IllegalArgumentException if {@code key} is {@code null}
         */
        public boolean contains(long key) {
            return get(key) != -1;
        }

        /**
         * Inserts the specified key-value pair into the symbol table, overwriting
         * the old value with the new value if the symbol table already contains the
         * specified key. Deletes the specified key (and its associated value) from
         * this symbol table if the specified value is {@code null}.
         * 
         * @param key the key
         * @param val the value
         * @throws IllegalArgumentException if {@code key} is {@code null}
         */
        public void put(long key, int val) {
            root = put(root, key, val);
        }

        /**
         * Inserts the key-value pair in the subtree. It overrides the old value
         * with the new value if the symbol table already contains the specified key
         * and deletes the specified key (and its associated value) from this symbol
         * table if the specified value is {@code null}.
         * 
         * @param x the subtree
         * @param key the key
         * @param val the value
         * @return the subtree
         */
        private Node put(Node x, long key, int val) {
            if (x == null) return new Node(key, val, 0, 1, val, key * val);
            if (key < x.key) {
                x.left = put(x.left, key, val);
            }
            else if (key > x.key) {
                x.right = put(x.right, key, val);
            }
            else {
                x.val += val;
                x.weight += val;
                x.sum += key * val;
                return x;
            }
            return balance(x);
        }

        /**
         * Restores the AVL tree property of the subtree.
         * 
         * @param x the subtree
         * @return the subtree with restored AVL property
         */
        private Node balance(Node x) {
            if (x == null) return x;
            if (balanceFactor(x) < -1) {
                if (balanceFactor(x.right) > 0) {
                    x.right = rotateRight(x.right);
                }
                x = rotateLeft(x);
            }
            else if (balanceFactor(x) > 1) {
                if (balanceFactor(x.left) < 0) {
                    x.left = rotateLeft(x.left);
                }
                x = rotateRight(x);
            }
            update(x);
            return x;
        }

        /**
         * Returns the balance factor of the subtree. The balance factor is defined
         * as the difference in height of the left subtree and right subtree, in
         * this order. Therefore, a subtree with a balance factor of -1, 0 or 1 has
         * the AVL property since the heights of the two child subtrees differ by at
         * most one.
         * 
         * @param x the subtree
         * @return the balance factor of the subtree
         */
        private int balanceFactor(Node x) {
            return height(x.left) - height(x.right);
        }

        /**
         * Rotates the given subtree to the right.
         * 
         * @param x the subtree
         * @return the right rotated subtree
         */
        private Node rotateRight(Node x) {
            Node y = x.left;
            x.left = y.right;
            y.right = x;
            y.size = x.size;
            x.size = 1 + size(x.left) + size(x.right);
            update(x);
            update(y);
            return y;
        }

        /**
         * Rotates the given subtree to the left.
         * 
         * @param x the subtree
         * @return the left rotated subtree
         */
        private Node rotateLeft(Node x) {
            Node y = x.right;
            x.right = y.left;
            y.left = x;
            y.size = x.size;
            x.size = 1 + size(x.left) + size(x.right);
            update(x);
            update(y);
            return y;
        }
        
        private void update(Node x) {
            if (x != null) {
                x.size = 1 + size(x.left) + size(x.right);
                x.height = 1 + Math.max(height(x.left), height(x.right));
                x.weight = weight(x.left) + weight(x.right) + x.val;
                x.sum = sum(x.left) + sum(x.right) + x.key * x.val;
            }
        }

        /**
         * Removes the largest key and associated value from the symbol table.
         * 
         * @throws NoSuchElementException if the symbol table is empty
         */
        public void deleteMax(int n) {
            if (isEmpty()) throw new NoSuchElementException("called deleteMax() with empty symbol table");
            root = deleteMax(root, n);
        }

        /**
         * Removes the largest key and associated value from the given subtree.
         * 
         * @param x the subtree
         * @return the updated subtree
         */
        private Node deleteMax(Node x, int n) {
            if (x.right == null) {
                if (x.val > n) {
                    x.val -= n;
                    update(x);
                    return x;
                }
                else {
                    return balance(x.left);
                }
            }
            x.right = deleteMax(x.right, n);
            return balance(x);
        }

        /**
         * Returns the kth smallest key in the symbol table.
         * 
         * @param k the order statistic
         * @return the kth smallest key in the symbol table
         * @throws IllegalArgumentException unless {@code k} is between 0 and
         *             {@code size() -1 }
         */
        public long select(int k) {
            return select(root, k);
        }

        /**
         * Returns the node with key the kth smallest key in the subtree.
         * 
         * @param x the subtree
         * @param k the kth smallest key in the subtree
         * @return the node with key the kth smallest key in the subtree
         */
        private long select(Node x, int k) {
            if (k == 0) return 0;
            else if (weight(x.left) >= k) return select(x.left, k);
            else if (weight(x.left) >= (k - x.val)) return sum(x.left) + x.key * (k - weight(x.left));
            else return sum(x.left) + x.key * x.val + select(x.right, k - weight(x.left) - x.val);
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        long K = in.nextLong();
        int inc = 0;
        AVLTree tree = o.new AVLTree();
        for (int i = 0; i < N; i++) {
            int V = in.nextInt() - 1;
            long pay = tree.select(V) + (long) V * (inc + 1);
            if (pay <= K) {
                inc++;
                while (tree.weight() > V) {
                    tree.deleteMax(tree.weight() - V);
                }
                tree.put(-inc, i - V);
                tree.put(K - pay - inc, 1);
                out.println(K - pay);
            } else {
                tree.put(-inc - 1, 1);
                out.println(-1);
            }
        }
        out.close();
    }
}
