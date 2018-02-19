import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Stack;
import java.util.StringTokenizer;

public class DMPG17S6 {
    private static DMPG17S6 o = new DMPG17S6();
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
    
    public static class Pair<Item, Item2> {
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
            return first.equals(p.first) && second.equals(p.second);
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static char[] lb = {'(', '[', '{'}, rb = {')', ']', '}'};
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int K = in.nextInt();
        int l = 0, r = 0;
        Stack<Pair<Character, Integer>> s = new Stack<Pair<Character, Integer>>();
        String str = in.nextLine();
        int[] match = new int[str.length()];
        char[] ori = str.toCharArray();
        char[] arr = str.toCharArray();
        outer : for (int i = 0; i < N; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i] == lb[j]) {
                    s.push(new Pair<Character, Integer>(arr[i], i));
                    continue outer;
                }
            }
            if (s.isEmpty()) {
                out.println("impossible");
                out.close();
                return;
            }
            match[i] = s.peek().second;
            for (int j = 0; j < 3; j++) {
                if (lb[j] == s.peek().first) l = j;
                if (rb[j] == arr[i]) r = j;
            }
            s.pop();
            if (l != r) {
                if (K == 0) {
                    out.println("impossible");
                    out.close();
                    return;
                }
                K--;
                arr[i] = rb[l];
            }
        }
        outer : for (int i = 0; i < N; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i] == lb[j]) continue outer;
            }
            if (K >= 2) {
                for (int j = 0; j < 3; j++) {
                    if (lb[j] == ori[match[i]]) l = j;
                    if (rb[j] == ori[i]) r = j;
                }
                if (l == r) {
                    arr[match[i]] = lb[(l + 1) % 3];
                    arr[i] = rb[(r + 1) % 3];
                    K -= 2;
                }
            }
        }
        outer : for (int i = 0; i < N; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i] == lb[j]) continue outer;
            }
            if (K >= 1) {
                for (int j = 0; j < 3; j++) {
                    if (lb[j] == ori[match[i]]) l = j;
                    if (rb[j] == ori[i]) r = j;
                }
                if (l != r) {
                    boolean[] keep = new boolean[3];
                    for (int j = 0; j < 3; j++) {
                        if (lb[j] == ori[match[i]] || rb[j] == ori[i]) keep[j] = true;
                    }
                    for (int j = 0; j < 3; j++) {
                        if (!keep[j]) {
                            arr[match[i]] = lb[j];
                            arr[i] = rb[j];
                        }
                    }
                    K--;
                }
            }
        }
        if (K == 0) {
            for (int i = 0; i < N; i++) {
                out.print(arr[i]);
            }
            out.println();
        } else {
            out.println("impossible");
        }
        out.close();
    }
}
