package bf2hard_lexicographically_least_substring;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class BF2Hard { // PARTIAL POINTS (56/100)
	private static BF2Hard o = new BF2Hard();
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
	
	public class SuffixArrayX {
	    private static final int CUTOFF =  5;   // cutoff to insertion sort (any value between 0 and 12)

	    public final char[] text;
	    public final int[] index;   // index[i] = j means text.substring(j) is ith largest suffix
	    public final int n;         // number of characters in text

	    /**
	     * Initializes a suffix array for the given {@code text} string.
	     * @param text the input string
	     */
	    public SuffixArrayX(String text) {
	        n = text.length();
	        text = text + '\0';
	        this.text = text.toCharArray();
	        this.index = new int[n];
	        for (int i = 0; i < n; i++)
	            index[i] = i;

	        sort(0, n-1, 0);
	    }

	    // 3-way string quicksort lo..hi starting at dth character
	    private void sort(int lo, int hi, int d) { 

	        // cutoff to insertion sort for small subarrays
	        if (hi <= lo + CUTOFF) {
	            insertion(lo, hi, d);
	            return;
	        }

	        int lt = lo, gt = hi;
	        char v = text[index[lo] + d];
	        int i = lo + 1;
	        while (i <= gt) {
	            char t = text[index[i] + d];
	            if      (t < v) exch(lt++, i++);
	            else if (t > v) exch(i, gt--);
	            else            i++;
	        }

	        // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]. 
	        sort(lo, lt-1, d);
	        if (v > 0) sort(lt, gt, d+1);
	        sort(gt+1, hi, d);
	    }

	    // sort from a[lo] to a[hi], starting at the dth character
	    private void insertion(int lo, int hi, int d) {
	        for (int i = lo; i <= hi; i++)
	            for (int j = i; j > lo && less(index[j], index[j-1], d); j--)
	                exch(j, j-1);
	    }

	    // is text[i+d..n) < text[j+d..n) ?
	    private boolean less(int i, int j, int d) {
	        if (i == j) return false;
	        i = i + d;
	        j = j + d;
	        while (i < n && j < n) {
	            if (text[i] < text[j]) return true;
	            if (text[i] > text[j]) return false;
	            i++;
	            j++;
	        }
	        return i > j;
	    }

	    // exchange index[i] and index[j]
	    private void exch(int i, int j) {
	        int swap = index[i];
	        index[i] = index[j];
	        index[j] = swap;
	    }

	    /**
	     * Returns the length of the input string.
	     * @return the length of the input string
	     */
	    public int length() {
	        return n;
	    }


	    /**
	     * Returns the index into the original string of the <em>i</em>th smallest suffix.
	     * That is, {@code text.substring(sa.index(i))} is the <em>i</em> smallest suffix.
	     * @param i an integer between 0 and <em>n</em>-1
	     * @return the index into the original string of the <em>i</em>th smallest suffix
	     * @throws java.lang.IndexOutOfBoundsException unless {@code 0 <=i < n}
	     */
	    public int index(int i) {
	        if (i < 0 || i >= n) throw new IndexOutOfBoundsException();
	        return index[i];
	    }

	    /**
	     * Returns the length of the longest common prefix of the <em>i</em>th
	     * smallest suffix and the <em>i</em>-1st smallest suffix.
	     * @param i an integer between 1 and <em>n</em>-1
	     * @return the length of the longest common prefix of the <em>i</em>th
	     * smallest suffix and the <em>i</em>-1st smallest suffix.
	     * @throws java.lang.IndexOutOfBoundsException unless {@code 1 <= i < n}
	     */
	    public int lcp(int i) {
	        if (i < 1 || i >= n) throw new IndexOutOfBoundsException();
	        return lcp(index[i], index[i-1]);
	    }

	    // longest common prefix of text[i..n) and text[j..n)
	    private int lcp(int i, int j) {
	        int length = 0;
	        while (i < n && j < n) {
	            if (text[i] != text[j]) return length;
	            i++;
	            j++;
	            length++;
	        }
	        return length;
	    }

	    /**
	     * Returns the <em>i</em>th smallest suffix as a string.
	     * @param i the index
	     * @return the <em>i</em> smallest suffix as a string
	     * @throws java.lang.IndexOutOfBoundsException unless {@code 0 <= i < n}
	     */
	    public String select(int i) {
	        if (i < 0 || i >= n) throw new IndexOutOfBoundsException();
	        return new String(text, index[i], n - index[i]);
	    }

	    /**
	     * Returns the number of suffixes strictly less than the {@code query} string.
	     * We note that {@code rank(select(i))} equals {@code i} for each {@code i}
	     * between 0 and <em>n</em>-1. 
	     * @param query the query string
	     * @return the number of suffixes strictly less than {@code query}
	     */
	    public int rank(String query) {
	        int lo = 0, hi = n - 1;
	        while (lo <= hi) {
	            int mid = lo + (hi - lo) / 2;
	            int cmp = compare(query, index[mid]);
	            if      (cmp < 0) hi = mid - 1;
	            else if (cmp > 0) lo = mid + 1;
	            else return mid;
	        }
	        return lo;
	    } 

	    // is query < text[i..n) ?
	    private int compare(String query, int i) {
	        int m = query.length();
	        int j = 0;
	        while (i < n && j < m) {
	            if (query.charAt(j) != text[i]) return query.charAt(j) - text[i];
	            i++;
	            j++;

	        }
	        if (i < n) return -1;
	        if (j < m) return +1;
	        return 0;
	    }
	}
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		String str = in.nextLine();
		int k = in.nextInt();
		SuffixArrayX sa = o.new SuffixArrayX(str);
		for (int i = 0; i < sa.length(); i++) {
			if (sa.n - sa.index[i] >= k) {
				System.out.println(str.substring(sa.index[i], sa.index[i] + k));
				break;
			}
		}
	}
}
