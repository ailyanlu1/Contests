package stringfindinghard;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.Random;
import java.util.StringTokenizer;

public class StringFindingHard {
	private static StringFindingHard o = new StringFindingHard();
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
	
	public class RabinKarpStringSearch {
	    private String pat;      // the pattern  // needed only for Las Vegas
	    private long patHash;    // pattern hash value
	    private int m;           // pattern length
	    private long q;          // a large prime, small enough to avoid long overflow
	    private int R;           // radix
	    private long RM;         // R^(M-1) % Q

	    /**
	     * Preprocesses the pattern string.
	     *
	     * @param pattern the pattern string
	     * @param R the alphabet size
	     */
	    public RabinKarpStringSearch(char[] pattern, int R) {
	        this.pat = String.valueOf(pattern);
	        this.R = R;        
	        throw new UnsupportedOperationException("Operation not supported yet");
	    }

	    /**
	     * Preprocesses the pattern string.
	     *
	     * @param pat the pattern string
	     */
	    public RabinKarpStringSearch(String pat) {
	        this.pat = pat;      // save pattern (needed only for Las Vegas)
	        R = 256;
	        m = pat.length();
	        q = longRandomPrime();

	        // precompute R^(m-1) % q for use in removing leading digit
	        RM = 1;
	        for (int i = 1; i <= m-1; i++)
	            RM = (R * RM) % q;
	        patHash = hash(pat, m);
	    } 

	    // Compute hash for key[0..m-1]. 
	    private long hash(String key, int m) { 
	        long h = 0; 
	        for (int j = 0; j < m; j++) 
	            h = (R * h + key.charAt(j)) % q;
	        return h;
	    }

	    // Las Vegas version: does pat[] match txt[i..i-m+1] ?
	    private boolean check(String txt, int i) {
	        for (int j = 0; j < m; j++) 
	            if (pat.charAt(j) != txt.charAt(i + j)) 
	                return false; 
	        return true;
	    }

	    // Monte Carlo version: always return true
	    // private boolean check(int i) {
	    //    return true;
	    //}
	 
	    /**
	     * Returns the index of the first occurrrence of the pattern string
	     * in the text string.
	     *
	     * @param  txt the text string
	     * @return the index of the first occurrence of the pattern string
	     *         in the text string; n if no such match
	     */
	    public int search(String txt) {
	        int n = txt.length(); 
	        if (n < m) return -1;
	        long txtHash = hash(txt, m); 

	        // check for match at offset 0
	        if ((patHash == txtHash) && check(txt, 0))
	            return 0;

	        // check for hash match; if hash match, check for exact match
	        for (int i = m; i < n; i++) {
	            // Remove leading digit, add trailing digit, check for match. 
	            txtHash = (txtHash + q - RM*txt.charAt(i-m) % q) % q; 
	            txtHash = (txtHash*R + txt.charAt(i)) % q; 

	            // match
	            int offset = i - m + 1;
	            if ((patHash == txtHash) && check(txt, offset))
	            	return offset;
	        }

	        // no match
	        return -1;
	    }


	    // a random 31-bit prime
	    private long longRandomPrime() {
	        BigInteger prime = BigInteger.probablePrime(31, new Random());
	        return prime.longValue();
	    }
	}
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		String str = in.nextLine();
		String find = in.nextLine();
		RabinKarpStringSearch s = o.new RabinKarpStringSearch(find);
		System.out.println(s.search(str));
	}
}
