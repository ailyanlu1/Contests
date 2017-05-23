package rgpc17p2_cubes_are_life;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

public class RGPC17P2 {
	private static RGPC17P2 o = new RGPC17P2();
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
		public PrefixSumArray(int[] array) {
			prefixSum = new long[array.length + 1];
			for (int i = 1; i < prefixSum.length; i++) {
				prefixSum[i] = prefixSum[i - 1] + array[i - 1];
			}
		}
		
		/**
	     * Returns the cumulative sum from index 1 to <em>end</em>
	     * @param end the 1-based end index (inclusive)
	     * @return the cumulative sum
	     */
		public long query(int end) {
			return prefixSum[end];
		}
		
		/**
	     * Returns the cumulative sum from index <em>start</em> to <em>end</em>
	     * @param start the 1-based start index (inclusive)
	     * @param end the 1-based end index (inclusive)
	     * @return the cumulative sum
	     */
		public long query(int start, int end) {
			if (end < start) throw new IllegalArgumentException();
			return query(end) - query(start - 1);
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int M = in.nextInt();
		int Q = in.nextInt();
		int[] arr = new int[N];
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		for (int i = 0; i < N; i++) {
			arr[i] = in.nextInt();
			map.put(arr[i], i + 1);
		}
		PrefixSumArray psa = o.new PrefixSumArray(arr);
		for (int i = 0; i < Q; i++) {
			if (psa.query(map.get(in.nextInt()), map.get(in.nextInt())) >= M * 2) out.println("Enough");
			else out.println("Not enough");
		}
		out.close();
	}
}
