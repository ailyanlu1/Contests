package gfssoc16j4_top_courses;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;

public class GFSSOC16J4 {
    private static GFSSOC16J4 o = new GFSSOC16J4();
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
    
    public static void sort(Course[] a) {
        int max = 0;
        for (Course x : a)
            max = Math.max(max, x.grade);
        int[] count = new int[max + 1];
        for (Course x : a)
            count[x.grade]++;
        for (int i = 1; i < count.length; i++)
            count[i] += count[i - 1];
        Course[] b = new Course[a.length];
        for (int i = 0; i < a.length; i++)
            b[--count[a[i].grade]] = a[i];
        for (int i = 0; i < a.length; i++)
            a[i] = b[i];
    }
    
    public static class Course {
        public String name;
        public int grade;
        public Course(String name, int grade) {
            this.name = name;
            this.grade = grade;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        HashMap<String, Integer> map = new HashMap<String, Integer>();
        HashSet<String> mandatory = new HashSet<String>();
        int N = in.nextInt();
        int C = in.nextInt();
        int M = in.nextInt();
        if (C > N) {
            out.println("Ace is dunzos");
            out.close();
            return;
        }
        Course[] arr = new Course[N];
        for (int i = 0; i < N; i++) {
            String line = in.nextLine();
            String name = line.substring(0, line.lastIndexOf(" "));
            int grade = Integer.parseInt(line.substring(line.lastIndexOf(" ") + 1));
            map.put(name, grade);
            arr[i] = new Course(name, grade);
        }
        double sum = 0;
        for (int i = 0; i < M; i++) {
            String name = in.nextLine();
            Integer grade = map.get(name);
            mandatory.add(name);
            if (grade == null) {
                out.println("Ace is dunzos");
                out.close();
                return;
            } else {
                sum += grade;
            }
        }
        int ind = N;
        sort(arr);
        for (int i = M; i < C; i++) {
            String name;
            do {
                name = arr[--ind].name;
            } while (mandatory.contains(name));
            sum += arr[ind].grade;
        }
        out.printf("%.2f", sum / C);
        out.close();
    }
}
