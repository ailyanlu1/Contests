package rte16s2_fire_evacuation_plan;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.StringTokenizer;

public class RTE16S2 {
    private static RTE16S2 o = new RTE16S2();
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
            if (!(o instanceof Pair)) return false;
            Pair p = (Pair) o;
            return p.first.equals(first) && p.second.equals(second);
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        String[] code = new String[4];
        for (int i = 0; i < code.length; i++) {
            code[i] = in.nextLine().trim();
        }
        String str = in.nextLine().trim();
        HashSet<Pair<Integer, Integer>>[] dest = new HashSet[str.length()];
        for (int i = 0; i < str.length(); i++) {
            dest[i] = new HashSet<Pair<Integer, Integer>>();
        }
        for (int i = 0; i < str.length(); i++) {
            String sub = str.substring(0, i+1);
            for (int j = 0; j < code.length; j++) {
                int index = sub.length() - code[j].length();
                if (index >= 0 && sub.substring(index).equals(code[j])) {
                    if (index - 1 == -1) {
                        if (j == 0) dest[i].add(new Pair<Integer, Integer>(0, 1));
                        else if (j == 1) dest[i].add(new Pair<Integer, Integer>(0, -1));
                        else if (j == 2) dest[i].add(new Pair<Integer, Integer>(1, 0));
                        else dest[i].add(new Pair<Integer, Integer>(-1, 0));
                    } else {
                        for (Pair<Integer, Integer> check: dest[index - 1]) {
                            Pair<Integer, Integer> cur;
                            if (j == 0) cur = new Pair<Integer, Integer>(check.first, check.second + 1);
                            else if (j == 1) cur = new Pair<Integer, Integer>(check.first, check.second - 1);
                            else if (j == 2) cur = new Pair<Integer, Integer>(check.first + 1, check.second);
                            else cur = new Pair<Integer, Integer>(check.first - 1, check.second);
                            dest[i].add(cur);
                        }
                    }
                }
            }
        }
        out.println(dest[str.length() - 1].size());
        out.close();
    }
}
