import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Fibonacci {
    private static Fibonacci o = new Fibonacci();
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
    
    public class Pair<Item, Item2> {
        private Item first;
        private Item2 second;
        
        public Pair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }
        
        public Item getFirst() {
            return this.first;
        }

        public void setFirst(Item first) {
            this.first = first;
        }

        public Item2 getSecond() {
            return this.second;
        }

        public void setSecond(Item2 second) {
            this.second = second;
        }
        
        public void set(Item first, Item2 second) {
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
            if (!(o instanceof Pair)) {
                return false;
            }
            Pair p = (Pair) o;
            return p.first.equals(first) && p.second.equals(second);
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static final BigInteger MOD = new BigInteger("" + 1000000007);
    private static final BigInteger TWO = new BigInteger("" + 2);
    
    public static void main(String[] args) throws IOException {
        BigInteger n = new BigInteger(in.next());
        out.println(fib(n).getFirst().toString());
        out.close();
    }
    
    private static Pair<BigInteger, BigInteger> fib(BigInteger n) {
        if (n.equals(BigInteger.ZERO)) return o.new Pair<BigInteger, BigInteger>(BigInteger.ZERO, BigInteger.ONE);
        Pair<BigInteger, BigInteger> res = fib(n.divide(TWO));
        BigInteger a = res.getFirst().multiply(res.getSecond().multiply(TWO).subtract(res.getFirst()).add(MOD)).mod(MOD);
        BigInteger b = res.getFirst().multiply(res.getFirst()).mod(MOD).add(res.getSecond().multiply(res.getSecond()).mod(MOD)).mod(MOD);
        if (n.mod(TWO).equals(BigInteger.ZERO)) return o.new Pair<BigInteger, BigInteger>(a, b);
        return o.new Pair<BigInteger, BigInteger>(b, a.add(b).mod(MOD));
    }
}
