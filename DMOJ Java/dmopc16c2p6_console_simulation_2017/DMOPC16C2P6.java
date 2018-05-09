import java.io.*;
import java.math.*;
import java.util.*;

public class DMOPC16C2P6 {
    private static DMOPC16C2P6 o = new DMOPC16C2P6();
    public static class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) { in = new BufferedReader(new InputStreamReader(inputStream)); }

        public Reader(String fileName) throws FileNotFoundException { in = new BufferedReader(new FileReader(fileName)); }

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
        
        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }

        // public BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }

        public byte nextByte() throws IOException { return Byte.parseByte(next()); }
        public byte nextByte(String delim) throws IOException { return Byte.parseByte(next(delim)); }
        public char nextChar() throws IOException { return next().charAt(0); }
        public char nextChar(String delim) throws IOException { return next(delim).charAt(0); }
        public double nextDouble() throws IOException { return Double.parseDouble(next()); }
        public double nextDouble(String delim) throws IOException { return Double.parseDouble(next(delim)); }
        public float nextFloat() throws IOException { return Float.parseFloat(next()); }
        public float nextFloat(String delim) throws IOException { return Float.parseFloat(next(delim)); }
        public int nextInt() throws IOException { return Integer.parseInt(next()); }
        public int nextInt(String delim) throws IOException { return Integer.parseInt(next(delim)); }
        public long nextLong() throws IOException { return Long.parseLong(next()); }
        public long nextLong(String delim) throws IOException { return Long.parseLong(next(delim)); }
        public short nextShort() throws IOException { return Short.parseShort(next()); }
        public short nextShort(String delim) throws IOException { return Short.parseShort(next(delim)); }
    } // Reader class
    
    private static Reader in;
    private static PrintWriter out;
    
    private static int NUM_OF_TEST_CASES = 1; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "input.txt";
    private static final String OUTPUT_FILE_NAME = "output.txt";
    
    private static boolean stdIn = true;
    private static boolean stdOut = true;
    private static boolean crash = true;
    
    public static void main(String[] args) throws Exception {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            try {
                run(i);
            } catch (Exception e) {
                out.println("Exception thrown on test case " + i);
                e.printStackTrace(out);
                if (crash) throw new Exception();
            }
            out.flush();
        }
        out.close();
    }
    
    public static class Folder {
        String name;
        int depth;
        HashMap<String, Folder> subdir;
        HashMap<String, File> files;
        
        public Folder(String name, int depth) {
            this.name = name;
            this.depth = depth;
            this.subdir = new HashMap<String, Folder>();
            this.files = new HashMap<String, File>();
        }
        
        public Folder mkdir(String name) {
            Folder f = new Folder(name, depth + 1);
            subdir.put(name, f);
            return f;
        }
        
        public File touch(String name) {
            File f = new File(name, depth + 1);
            files.put(name, f);
            return f;
        }
    }
    
    public static class File {
        String name;
        int depth;
        
        public File(String name, int depth) {
            this.name = name;
            this.depth = depth;
        }
    }
    
    public static class Pattern {
        private String pat;
        private int[] LCP;

        public Pattern(String pat) {
            this.pat = pat;
            LCP = new int[pat.length() + 1];
            LCP[0] = -1;
            for (int i = 0, j = -1; i < pat.length(); i++, j++, LCP[i] = j) {
                while (j >= 0 && pat.charAt(i) != pat.charAt(j) && pat.charAt(i) != '/' && pat.charAt(j) != '/') j = LCP[j];
            }
        }

        public boolean contains(String txt) {
            for (int i = 0, j = 0; i < txt.length(); i++, j++) {
                while (j >= 0 && txt.charAt(i) != pat.charAt(j) && pat.charAt(j) != '/') j = LCP[j];
                if (j == pat.length() - 1) return true;
            }
            return false;
        }

        public boolean isPrefix(String txt) {
            if (pat.length() > txt.length()) return false;
            for (int i = 0; i < pat.length(); i++) {
                if (pat.charAt(i) != txt.charAt(i) && pat.charAt(i) != '/') return false;
            }
            return true;
        }

        public boolean isSuffix(String txt) {
            if (pat.length() > txt.length()) return false;
            for (int i = 0; i < pat.length(); i++) {
                if (pat.charAt(pat.length() - i - 1) != txt.charAt(txt.length() - i - 1) && pat.charAt(pat.length() - i - 1) != '/') return false;
            }
            return true;
        }
        
        public boolean equals(String txt) {
            if (pat.length() != txt.length()) return false;
            for (int i = 0; i < pat.length(); i++) {
                if (pat.charAt(i) != txt.charAt(i) && pat.charAt(i) != '/') return false;
            }
            return true;
        }
    }
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt();
        Folder root = new Folder("~", -1);
        Stack<Folder> cur = new Stack<Folder>();
        cur.push(root);
        for (int i = 0; i < N; i++) {
            int depth = in.nextInt();
            String name = in.next();
            while (cur.peek().depth >= depth) cur.pop();
            Pattern p = new Pattern(name);
            if (p.contains(".")) cur.peek().touch(name);
            else cur.push(cur.peek().mkdir(name));
        }
        cur.clear();
        cur.push(root);
        String line;
        while (!(line = in.nextLine()).equals("exit")) {
            StringTokenizer st = new StringTokenizer(line);
            String cmd = st.nextToken();
            if (cmd.equals("pwd")) {
                for (Folder f : cur) out.print(f.name + "/");
                out.println();
                out.println();
            } else if (cmd.equals("mkdir")) {
                cur.peek().mkdir(st.nextToken());
            } else if (cmd.equals("touch")) {
                cur.peek().touch(st.nextToken());
            } else if (cmd.equals("cd")) {
                String dir = st.nextToken();
                if (dir.charAt(0) == '~') {
                    cur.clear();
                    cur.push(root);
                    if (dir.length() > 2) {
                        StringTokenizer d = new StringTokenizer(dir.substring(2, dir.length()), "/");
                        while (d.hasMoreTokens()) cur.push(cur.peek().subdir.get(d.nextToken()));
                    }
                } else {
                    StringTokenizer d = new StringTokenizer(dir, "/");
                    while (d.hasMoreTokens()) cur.push(cur.peek().subdir.get(d.nextToken()));
                }
            } else if (cmd.equals("ls")) {
                ArrayList<String> output = new ArrayList<String>();
                if (st.hasMoreTokens()) {
                    String s = st.nextToken();
                    if (s.equals("-r")) {
                        if (st.hasMoreTokens()) {
                            st.nextToken();
                            st.nextToken();
                            s = st.nextToken();
                            boolean equal = false, start = false, end = false;
                            StringBuilder ss = new StringBuilder();
                            if (s.charAt(0) == '^' && s.charAt(s.length() - 1) == '$') {
                                equal = true;
                                s = s.substring(1, s.length() - 1);
                            } else if (s.charAt(0) == '^') {
                                start = true;
                                s = s.substring(1);
                            } else if (s.charAt(s.length() - 1) == '$') {
                                end = true;
                                s = s.substring(0, s.length() - 1);
                            }
                            for (int i = 0; i < s.length(); i++) {
                                if (s.charAt(i) == '\\') {
                                    ss.append(s.charAt(i + 1));
                                    i++;
                                } else if (s.charAt(i) == '.') {
                                    ss.append('/');
                                } else {
                                    ss.append(s.charAt(i));
                                }
                            }
                            s = new String(ss);
                            if (equal) {
                                dfsEq(cur.peek(), new Pattern(s), output);
                            } else if (start) {
                                dfsSt(cur.peek(), new Pattern(s), output);
                            } else if (end) {
                                dfsEn(cur.peek(), new Pattern(s), output);
                            } else {
                                dfsC(cur.peek(), new Pattern(s), output);
                            }
                        } else {
                            dfs(cur.peek(), output);
                        }
                    } else if (s.equals("|")) {
                        st.nextToken();
                        s = st.nextToken();
                        boolean equal = false, start = false, end = false;
                        StringBuilder ss = new StringBuilder();
                        if (s.charAt(0) == '^' && s.charAt(s.length() - 1) == '$') {
                            equal = true;
                            s = s.substring(1, s.length() - 1);
                        } else if (s.charAt(0) == '^') {
                            start = true;
                            s = s.substring(1);
                        } else if (s.charAt(s.length() - 1) == '$') {
                            end = true;
                            s = s.substring(0, s.length() - 1);
                        }
                        for (int i = 0; i < s.length(); i++) {
                            if (s.charAt(i) == '\\') {
                                ss.append(s.charAt(i + 1));
                                i++;
                            } else if (s.charAt(i) == '.') {
                                ss.append('/');
                            } else {
                                ss.append(s.charAt(i));
                            }
                        }
                        s = new String(ss);
                        Pattern p = new Pattern(s);
                        if (equal) {
                            for (String t : cur.peek().subdir.keySet()) {
                                if (p.equals(t)) output.add(t);
                            }
                            for (String t : cur.peek().files.keySet()) {
                                if (p.equals(t)) output.add(t);
                            }
                        } else if (start) {
                            for (String t : cur.peek().subdir.keySet()) {
                                if (p.isPrefix(t)) output.add(t);
                            }
                            for (String t : cur.peek().files.keySet()) {
                                if (p.isPrefix(t)) output.add(t);
                            }
                        } else if (end) {
                            for (String t : cur.peek().subdir.keySet()) {
                                if (p.isSuffix(t)) output.add(t);
                            }
                            for (String t : cur.peek().files.keySet()) {
                                if (p.isSuffix(t)) output.add(t);
                            }
                        } else {
                            for (String t : cur.peek().subdir.keySet()) {
                                if (p.contains(t)) output.add(t);
                            }
                            for (String t : cur.peek().files.keySet()) {
                                if (p.contains(t)) output.add(t);
                            }
                        }
                    } else {
                        throw new Exception();
                    }
                } else {
                    for (String s : cur.peek().subdir.keySet()) output.add(s);
                    for (String s : cur.peek().files.keySet()) output.add(s);
                }
                Collections.sort(output);
                for (String s : output) out.println(s);
                if (output.isEmpty()) out.println();
                out.println();
            } else {
                throw new Exception();
            }
        }
    }
    
    static void dfs(Folder f, ArrayList<String> output) {
        for (String s : f.files.keySet()) output.add(s);
        for (Map.Entry<String, Folder> e : f.subdir.entrySet()) {
            output.add(e.getKey());
            dfs(e.getValue(), output);
        }
    }
    
    static void dfsEq(Folder f, Pattern p, ArrayList<String> output) {
        for (String s : f.files.keySet()) if (p.equals(s)) output.add(s);
        for (Map.Entry<String, Folder> e : f.subdir.entrySet()) {
            if (p.equals(e.getKey())) output.add(e.getKey());
            dfsEq(e.getValue(), p, output);
        }
    }
    
    static void dfsSt(Folder f, Pattern p, ArrayList<String> output) {
        for (String s : f.files.keySet()) if (p.isPrefix(s)) output.add(s);
        for (Map.Entry<String, Folder> e : f.subdir.entrySet()) {
            if (p.isPrefix(e.getKey())) output.add(e.getKey());
            dfsSt(e.getValue(), p, output);
        }
    }
    
    static void dfsEn(Folder f, Pattern p, ArrayList<String> output) {
        for (String s : f.files.keySet()) if (p.isSuffix(s)) output.add(s);
        for (Map.Entry<String, Folder> e : f.subdir.entrySet()) {
            if (p.isSuffix(e.getKey())) output.add(e.getKey());
            dfsEn(e.getValue(), p, output);
        }
    }
    
    static void dfsC(Folder f, Pattern p, ArrayList<String> output) {
        for (String s : f.files.keySet()) if (p.contains(s)) output.add(s);
        for (Map.Entry<String, Folder> e : f.subdir.entrySet()) {
            if (p.contains(e.getKey())) output.add(e.getKey());
            dfsC(e.getValue(), p, output);
        }
    }
}
