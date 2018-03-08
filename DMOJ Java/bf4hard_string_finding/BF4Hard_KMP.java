import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class BF4Hard_KMP {
    private static BF4Hard_KMP o = new BF4Hard_KMP();
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
    
    public class KMPFastStringSearch {
        private int[] LCP;

        private char[] pattern;    // either the character array for the pattern
        private String pat;        // or the pattern string

        /**
         * Preprocesses the pattern string.
         *
         * @param pat the pattern string
         */
        public KMPFastStringSearch(String pat) {
            this.pat = pat;
            int m = pat.length();
            LCP = new int[m + 1];
            LCP[0] = -1;
            for (int i = 0, j = -1; i < m; i++, j++, LCP[i] = j) {
                while (j >= 0 && pat.charAt(i) != pat.charAt(j)) {
                    j = LCP[j];
                }
            }
        } 

        /**
         * Preprocesses the pattern string.
         *
         * @param pattern the pattern string
         * @param m the length of the pattern
         */
        public KMPFastStringSearch(char[] pattern) {
            this.pattern = pattern;
            int m = pattern.length;
            LCP = new int[m + 1];
            LCP[0] = -1;
            for (int i = 0, j = -1; i < m; i++, j++, LCP[i] = j) {
                while (j >= 0 && pattern[i] != pattern[j]) {
                    j = LCP[j];
                }
            }
        } 

        /**
         * Returns the index of the first occurrrence of the pattern string
         * in the text string.
         *
         * @param  txt the text string
         * @return the index of the first occurrence of the pattern string
         *         in the text string; -1 if no such match
         */
        public int search(String txt) {
            int m = pat.length();
            int n = txt.length();
            for (int i = 0, j = 0; i < n; i++, j++) {
                while (j >= 0 && txt.charAt(i) != pat.charAt(j)) {
                    j = LCP[j];
                }
                if (j == m - 1) {
                    return i - j;
                }
            }
            return -1;
        }

        /**
         * Returns the index of the first occurrence of the pattern string
         * in the text string.
         *
         * @param  text the text string
         * @return the index of the first occurrence of the pattern string
         *         in the text string; -1 if no such match
         */
        public int search(char[] text) {
            int m = pattern.length;
            int n = text.length;
            for (int i = 0, j = 0; i < n; i++, j++) {
                while (j >= 0 && text[i] != pattern[j]) {
                    j = LCP[j];
                }
                if (j == m - 1) {
                    return i - j;
                }
            }
            return -1;
        }
    }
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        String str = in.nextLine();
        String find = in.nextLine();
        KMPFastStringSearch s = o.new KMPFastStringSearch(find);
        System.out.println(s.search(str));
    }
}
