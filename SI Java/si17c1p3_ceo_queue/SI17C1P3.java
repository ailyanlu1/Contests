import java.io.*;
import java.math.*;
import java.util.*;

public class SI17C1P3 {
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 16;
        private int LENGTH = -1;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte b = read();
            while (b <= ' ') b = read();
            boolean neg = (b == '-');
            if (neg) b = read();
            do {
                ret = ret * 10 + b - '0';
            } while ((b = read()) >= '0' && b <= '9');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte b = read();
            while (b <= ' ') b = read();
            boolean neg = (b == '-');
            if (neg) b = read();
            do {
                ret = ret * 10 + b - '0';
            } while ((b = read()) >= '0' && b <= '9');
            if (neg) return -ret;
            return ret;
        }
        
        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte b = read();
            while (b <= ' ') b = read();
            boolean neg = (b == '-');
            if (neg) b = read();
            do {
                ret = ret * 10 + b - '0';
            } while ((b = read()) >= '0' && b <= '9');
            if (b == '.') while ((b = read()) >= '0' && b <= '9') ret += (b - '0') / (div *= 10);
            if (neg) return -ret;
            return ret;
        }

        public char nextChar() throws IOException {
            byte b;
            do {
                b = read();
            } while (b == ' ' || b == '\n' || b == '\r' || b == '\t' || b == -1);
            return (char) b;
        }

        public String next() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, b;
            b = read();
            while (b == ' ' || b == '\n' || b == '\r' || b == '\t' || b == -1) b = read();
            buf[cnt++] = (byte) b;
            while ((b = read()) != -1) {
                if (b == ' ' || b == '\n' || b == '\r' || b == '\t' || b == -1) break;
                buf[cnt++] = (byte) b;
            }
            return new String(buf, 0, cnt);
        }
        
        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, b;
            while ((b = read()) != -1) {
                if (b == '\n' || b == '\r') break;
                buf[cnt++] = (byte) b;
            }
            return new String(buf, 0, cnt);
        }
        
        public void setLength(int length) {
            LENGTH = length;
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
    
    private static Reader in;
    private static PrintWriter out;
    
    private static int NUM_OF_TEST_CASES = 1; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "input.txt";
    private static final String OUTPUT_FILE_NAME = "output.txt";
    
    private static boolean stdIn = true;
    private static boolean stdOut = true;
    private static boolean crash = true;
    private static boolean flush = false;
    
    public static void main(String[] args) throws Exception {
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME)));
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            try {
                run(i);
            } catch (Exception e) {
                out.println("Exception thrown on test case " + i);
                e.printStackTrace(out);
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
    }

    public static class Pair<Item1 extends Comparable<Item1>, Item2 extends Comparable<Item2>> implements Comparable<Pair<Item1, Item2>> {
        public Item1 first;
        public Item2 second;

        public Pair(Item1 first, Item2 second) {
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
            return first.equals(p.first) && second.equals(p.second);
        }

        @Override
        public int compareTo(Pair<Item1, Item2> p) {
            if (first.compareTo(p.first) != 0) return first.compareTo(p.first);
            return (second.compareTo(p.second));
        }
        
        @Override
        public String toString() {
            return "(" + first.toString() + ", " + second.toString() + ")";
        }
    }

    static int N, W, cnt = 0;
    static int[] R;
    static TreeMap<Integer, Pair<Integer, Integer>> ratings = new TreeMap<Integer, Pair<Integer, Integer>>();
    static TreeMap<Pair<Integer, Pair<Integer, Integer>>, Pair<Integer, Integer>> times = new TreeMap<Pair<Integer, Pair<Integer, Integer>>, Pair<Integer, Integer>>();
    static Map.Entry<Integer, Pair<Integer, Integer>> a, x, b;
    static Pair<Integer, Pair<Integer, Integer>> y;
    static Map.Entry<Pair<Integer, Pair<Integer, Integer>>, Pair<Integer, Integer>> cur;

    static void remove() {
        if (a != null) {
            times.remove(new Pair<Integer, Pair<Integer, Integer>>(Math.min(x.getValue().second, a.getValue().second) + x.getKey() - a.getKey(),
                new Pair<Integer, Integer>(Math.min(a.getValue().second, x.getValue().second), Math.max(a.getValue().second, x.getValue().second))));
        }
        if (b != null) {
            times.remove(new Pair<Integer, Pair<Integer, Integer>>(Math.min(b.getValue().second, x.getValue().second) + b.getKey() - x.getKey(),
                new Pair<Integer, Integer>(Math.min(x.getValue().second, b.getValue().second), Math.max(x.getValue().second, b.getValue().second))));
        }
        if (a != null && b != null) {
            times.put(new Pair<Integer, Pair<Integer, Integer>>(Math.min(b.getValue().second, a.getValue().second) + b.getKey() - a.getKey(),
                new Pair<Integer, Integer>(Math.min(a.getValue().second, b.getValue().second), Math.max(a.getValue().second, b.getValue().second))),
                new Pair<Integer, Integer>(a.getValue().second < b.getValue().second ? a.getValue().first : b.getValue().first,
                    a.getValue().second < b.getValue().second ? b.getValue().first : a.getValue().first));
        }
        ratings.remove(x.getKey());
    }

    static void insert() {
        if (a != null && b != null) {
            times.remove(new Pair<Integer, Pair<Integer, Integer>>(Math.min(b.getValue().second, a.getValue().second) + b.getKey() - a.getKey(),
                new Pair<Integer, Integer>(Math.min(a.getValue().second, b.getValue().second), Math.max(a.getValue().second, b.getValue().second))));
        }
        if (a != null) {
            times.put(new Pair<Integer, Pair<Integer, Integer>>(Math.min(y.second.second, a.getValue().second) + y.first - a.getKey(),
                new Pair<Integer, Integer>(Math.min(a.getValue().second, y.second.second), Math.max(a.getValue().second, y.second.second))),
                new Pair<Integer, Integer>(a.getValue().second < y.second.second ? a.getValue().first : y.second.first,
                    a.getValue().second < y.second.second ? y.second.first : a.getValue().first));
        }
        if (b != null) {
            times.put(new Pair<Integer, Pair<Integer, Integer>>(Math.min(b.getValue().second, y.second.second) + b.getKey() - y.first,
                new Pair<Integer, Integer>(Math.min(y.second.second, b.getValue().second), Math.max(y.second.second, b.getValue().second))),
                new Pair<Integer, Integer>(y.second.second < b.getValue().second ? y.second.first : b.getValue().first,
                    y.second.second < b.getValue().second ? b.getValue().first : y.second.first));
        }
        ratings.put(y.first, y.second);
    }

    static void removePrior(int tt) {
        while ((cur = times.firstEntry()) != null && cur.getKey().first <= tt) {
            int k1 = R[cur.getValue().first];
            int k2 = R[cur.getValue().second];
            int t = cur.getKey().first;
            x = ratings.ceilingEntry(k1);
            if (t - x.getValue().second >= W) cnt++;
            a = ratings.lowerEntry(x.getKey());
            b = ratings.higherEntry(x.getKey());
            remove();
            x = ratings.ceilingEntry(k2);
            if (t - x.getValue().second >= W) cnt++;
            a = ratings.lowerEntry(x.getKey());
            b = ratings.higherEntry(x.getKey());
            remove();
        }
    }

    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        W = in.nextInt();
        R = new int[N];
        cnt = 0;
        for (int i = 0; i < N; i++) {
            int q = in.nextInt();
            R[i] = in.nextInt();
            removePrior(q - 1);
            boolean checkTie = false;
            Pair<Integer, Integer> tiePair = new Pair<Integer, Integer>(0, 0);
            if ((cur = times.firstEntry()) != null && cur.getKey().first == q) {
                checkTie = true;
                tiePair.first = ratings.ceilingEntry(R[cur.getValue().first]).getValue().second;
                tiePair.second = ratings.ceilingEntry(R[cur.getValue().second]).getValue().second;
            }
            a = ratings.lowerEntry(R[i]);
            b = ratings.higherEntry(R[i]);
            if (a == null && b == null) {
                
            } else if (a == null && b != null) {
                if (b.getKey() - R[i] <= q - b.getValue().second && checkTie) {
                    Pair<Integer, Integer> p = new Pair<Integer, Integer>(b.getValue().second, R[i]);
                    if (tiePair.compareTo(p) < 0) removePrior(q);
                }
            } else if (a != null && b == null) {
                if (R[i] - a.getKey() <= q - a.getValue().second && checkTie) {
                    Pair<Integer, Integer> p = new Pair<Integer, Integer>(a.getValue().second, R[i]);
                    if (tiePair.compareTo(p) < 0) removePrior(q);
                }
            } else if (R[i] - a.getKey() <= q - a.getValue().second && (b.getKey() - R[i] > q - b.getValue().second || a.getValue().second < b.getValue().second)) {
                Pair<Integer, Integer> p = new Pair<Integer, Integer>(a.getValue().second, R[i]);
                if (tiePair.compareTo(p) < 0) removePrior(q);
            } else if (b.getKey() - R[i] <= q - b.getValue().second && (R[i] - a.getKey() > q - a.getValue().second || b.getValue().second < a.getValue().second)) {
                Pair<Integer, Integer> p = new Pair<Integer, Integer>(b.getValue().second, R[i]);
                if (tiePair.compareTo(p) < 0) removePrior(q);
            } 
            a = ratings.lowerEntry(R[i]);
            b = ratings.higherEntry(R[i]);
            if (a == null && b == null) {
                ratings.put(R[i], new Pair<Integer, Integer>(i, q));
            } else if (a == null && b != null) {
                if (b.getKey() - R[i] <= q - b.getValue().second) {
                    if (q - b.getValue().second >= W) cnt++;
                    x = b;
                    b = ratings.higherEntry(x.getKey());
                    remove();
                } else {
                    y = new Pair<Integer, Pair<Integer, Integer>>(R[i], new Pair<Integer, Integer>(i, q));
                    insert();
                }
            } else if (a != null && b == null) {
                if (R[i] - a.getKey() <= q - a.getValue().second) {
                    if (q - a.getValue().second >= W) cnt++;
                    x = a;
                    a = ratings.lowerEntry(x.getKey());
                    remove();
                } else {
                    y = new Pair<Integer, Pair<Integer, Integer>>(R[i], new Pair<Integer, Integer>(i, q));
                    insert();
                }
            } else if (R[i] - a.getKey() <= q - a.getValue().second && (b.getKey() - R[i] > q - b.getValue().second || a.getValue().second < b.getValue().second)) {
                if (q - a.getValue().second >= W) cnt++;
                if (W == 0) cnt++;
                x = a;
                a = ratings.lowerEntry(x.getKey());
                b = ratings.higherEntry(x.getKey());
                remove();
            } else if (b.getKey() - R[i] <= q - b.getValue().second && (R[i] - a.getKey() > q - a.getValue().second || b.getValue().second < a.getValue().second)) {
                if (q - b.getValue().second >= W) cnt++;
                if (W == 0) cnt++;
                x = b;
                a = ratings.lowerEntry(x.getKey());
                b = ratings.higherEntry(x.getKey());
                remove();
            } else {
                y = new Pair<Integer, Pair<Integer, Integer>>(R[i], new Pair<Integer, Integer>(i, q));
                insert();
            }
        }
        while ((cur = times.firstEntry()) != null && cur.getKey().first < Integer.MAX_VALUE) {
            int k1 = R[cur.getValue().first];
            int k2 = R[cur.getValue().second];
            int t = cur.getKey().first;
            x = ratings.ceilingEntry(k1);
            if (t - x.getValue().second >= W) cnt++;
            a = ratings.lowerEntry(x.getKey());
            b = ratings.higherEntry(x.getKey());
            remove();
            x = ratings.ceilingEntry(k2);
            if (t - x.getValue().second >= W) cnt++;
            a = ratings.lowerEntry(x.getKey());
            b = ratings.higherEntry(x.getKey());
            remove();
        }
        out.println(cnt + ratings.size());
    }
}
