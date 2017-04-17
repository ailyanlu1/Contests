package bf4hard;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class BF4Hard {
	private static BF4Hard o = new BF4Hard();
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
	
	public class BoyerMooreStringSearch {
	    private final int R;     // the radix
	    private int[] right;     // the bad-character skip array

	    private char[] pattern;  // store the pattern as a character array
	    private String pat;      // or as a string

	    /**
	     * Preprocesses the pattern string.
	     *
	     * @param pat the pattern string
	     */
	    public BoyerMooreStringSearch(String pat) {
	        this.R = 256;
	        this.pat = pat;

	        // position of rightmost occurrence of c in the pattern
	        right = new int[R];
	        for (int c = 0; c < R; c++)
	            right[c] = -1;
	        for (int j = 0; j < pat.length(); j++)
	            right[pat.charAt(j)] = j;
	    }

	    /**
	     * Preprocesses the pattern string.
	     *
	     * @param pattern the pattern string
	     * @param R the alphabet size
	     */
	    public BoyerMooreStringSearch(char[] pattern, int R) {
	        this.R = R;
	        this.pattern = new char[pattern.length];
	        for (int j = 0; j < pattern.length; j++)
	            this.pattern[j] = pattern[j];

	        // position of rightmost occurrence of c in the pattern
	        right = new int[R];
	        for (int c = 0; c < R; c++)
	            right[c] = -1;
	        for (int j = 0; j < pattern.length; j++)
	            right[pattern[j]] = j;
	    }

	    /**
	     * Returns the index of the first occurrrence of the pattern string
	     * in the text string.
	     *
	     * @param  txt the text string
	     * @return the index of the first occurrence of the pattern string
	     *         in the text string; n if no such match
	     */
	    public int search(String txt) {
	        int m = pat.length();
	        int n = txt.length();
	        int skip;
	        for (int i = 0; i <= n - m; i += skip) {
	            skip = 0;
	            for (int j = m-1; j >= 0; j--) {
	                if (pat.charAt(j) != txt.charAt(i+j)) {
	                    skip = Math.max(1, j - right[txt.charAt(i+j)]);
	                    break;
	                }
	            }
	            if (skip == 0) return i;    // found
	        }
	        return -1;                       // not found
	    }


	    /**
	     * Returns the index of the first occurrrence of the pattern string
	     * in the text string.
	     *
	     * @param  text the text string
	     * @return the index of the first occurrence of the pattern string
	     *         in the text string; n if no such match
	     */
	    public int search(char[] text) {
	        int m = pattern.length;
	        int n = text.length;
	        int skip;
	        for (int i = 0; i <= n - m; i += skip) {
	            skip = 0;
	            for (int j = m-1; j >= 0; j--) {
	                if (pattern[j] != text[i+j]) {
	                    skip = Math.max(1, j - right[text[i+j]]);
	                    break;
	                }
	            }
	            if (skip == 0) return i;    // found
	        }
	        return -1;                       // not found
	    }
	}
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		String str = in.nextLine();
		String find = in.nextLine();
		BoyerMooreStringSearch s = o.new BoyerMooreStringSearch(find);
		System.out.println(s.search(str));
	}
}
