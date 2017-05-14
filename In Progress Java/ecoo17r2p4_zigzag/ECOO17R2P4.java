package ecoo17r2p4_zigzag;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Iterator;
import java.util.StringTokenizer;

public class ECOO17R2P4 { // TLE 40/100
	private static ECOO17R2P4 o = new ECOO17R2P4();
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
	
	public class JohnsonTrotterPermIterator implements Iterator<int[]> {
		private int[] next = null;
		private final int n;
		private int[] perm;
		private int[] dirs;

		public JohnsonTrotterPermIterator(int size) {
			n = size;
			if (n <= 0) {
				perm = (dirs = null);
			} else {
				perm = new int[n];
				dirs = new int[n];
				for (int i = 0; i < n; i++) {
					perm[i] = i;
					dirs[i] = -1;
				}
				dirs[0] = 0;
			}
			next = perm;
		}

		@Override
		public int[] next() {
			int[] r = makeNext();
			next = null;
			return r;
		}

		@Override
		public boolean hasNext() {
			return (makeNext() != null);
		}

		private int[] makeNext() {
			if (next != null)
				return next;
			if (perm == null)
				return null;

			// find the largest element with != 0 direction
			int i = -1, e = -1;
			for (int j = 0; j < n; j++)
				if ((dirs[j] != 0) && (perm[j] > e)) {
					e = perm[j];
					i = j;
				}

			if (i == -1) // no such element -> no more premutations
				return (next = (perm = (dirs = null))); // no more permutations

			// swap with the element in its direction
			int k = i + dirs[i];
			swap(i, k, dirs);
			swap(i, k, perm);
			// if it's at the start/end or the next element in the direction
			// is greater, reset its direction.
			if ((k == 0) || (k == n - 1) || (perm[k + dirs[k]] > e))
				dirs[k] = 0;

			// set directions to all greater elements
			for (int j = 0; j < n; j++)
				if (perm[j] > e)
					dirs[j] = (j < k) ? +1 : -1;

			return (next = perm);
		}

		private void swap(int i, int j, int[] arr) {
			int v = arr[i];
			arr[i] = arr[j];
			arr[j] = v;
		}
	}
	
	public static int MOD = 1000000007;
	
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
	public static void main(String[] args) throws IOException {
		Reader f = o.new Reader(System.in);
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(f);
		} // for i
	} // main method
	
	public static void run(Reader f) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
		int N = f.nextInt();
		JohnsonTrotterPermIterator iter = o.new JohnsonTrotterPermIterator(N);
		int count = 0;
		while (iter.hasNext()) {
			if (isZigZag(iter.next())) count = (count + 1) % MOD;
		}
		System.out.println(count);
	} // run method
	
	private static boolean isZigZag(int[] arr) {
		for (int i = 1; i < arr.length; i++) {
			if (i % 2 == 0 && arr[i] > arr[i - 1]) return false;
			if (i % 2 == 1 && arr[i - 1] > arr[i]) return false;
		}
		return true;
	}
} // QuestionFour class
