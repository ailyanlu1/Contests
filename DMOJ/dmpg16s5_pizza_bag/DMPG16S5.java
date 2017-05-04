package dmpg16s5_pizza_bag;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.StringTokenizer;

public class DMPG16S5 {
	private static DMPG16S5 o = new DMPG16S5();
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
	
	public class PrefixSumArray {
		private long[] prefixSum;
		
		/**
	     * Initializes a prefix sum array for the given {@code array} array.
	     * @param array the original array of integers
	     */	
		public PrefixSumArray(long[] array) {
			prefixSum = new long[array.length];
			prefixSum[0] = array[0];
			for (int i = 1; i < prefixSum.length; i++) {
				prefixSum[i] = prefixSum[i - 1] + array[i];
			}
		}
		
		/**
	     * Returns the cumulative sum from index 0 to <em>end</em>
	     * @param end the 0-based end index (inclusive)
	     * @return the cumulative sum
	     */
		public long query(int end) {
			if (end < 0 || end >= prefixSum.length) throw new ArrayIndexOutOfBoundsException();
			return prefixSum[end];
		}
		
		/**
	     * Returns the cumulative sum from index <em>start</em> to <em>end</em>
	     * @param start the 0-based start index (inclusive)
	     * @param end the 0-based end index (inclusive)
	     * @return the cumulative sum
	     */
		public long query(int start, int end) {
			if (start < 0 || end < 0 || start >= prefixSum.length || end >= prefixSum.length) throw new ArrayIndexOutOfBoundsException();
			if (end < start) throw new IllegalArgumentException();
			return query(end) - query(start - 1);
		}
	}

	
	public class Pair<Item, Item2> {
		public Item first;
		public Item2 second;
		
		public Pair(Item first, Item2 second) {
			this.first = first;
			this.second = second;
		}
	}
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int N = in.nextInt();
		int K = in.nextInt();
		long[] arr = new long[N + K - 1];
		for (int i = 0; i < N; i++) {
			long d = in.nextLong();
			arr[i] = d;
			if (i + N < arr.length) arr[i+N] = d;
		}
		PrefixSumArray psa = o.new PrefixSumArray(arr);
		Deque<Pair<Integer, Long>> dq = new ArrayDeque<Pair<Integer, Long>>();
		dq.addFirst(o.new Pair<Integer, Long>(-1, 0L));
		long ans = 0;
		for (int i = 0; i < arr.length; i++) {
			Pair<Integer, Long> add = o.new Pair<Integer, Long>(i, psa.query(i));
			while (!dq.isEmpty() && dq.getLast().second >= psa.query(i)) {
				dq.removeLast();
			}
			dq.addLast(add);
			while (dq.getFirst().first < i - K) {
				dq.removeFirst();
			}
			ans = Math.max(ans, psa.query(i) - dq.getFirst().second);
		}
		out.println(ans);
		out.close();
	}
}
