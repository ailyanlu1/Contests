package dp1p1_maximum_sum;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DP1P1 {
	private static DP1P1 o = new DP1P1();
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
	
	public static class MaximumNonConsecutiveSubsequence {
		
		private MaximumNonConsecutiveSubsequence() {}
		
		/** 
		 * Static method for determining the maximum value of a non consecutive subsequence
		 * (no 2 elements chosen may be next to each other.
		 * 
		 * Take time proportional to <em>N</em> where N is the length of the original
		 * sequence.
		 * 
		 * Take space proportional to <em>N</em>.
		 * 
		 * @param sequence the array of integers to check
		 * @return the maximum value of a non consecutive subsequence
		 */
		public static int solve(int[] sequence) {
			int[] dp = new int[sequence.length];	// the dp array that stores the solutions
			// 2 initial cases
			dp[0] = sequence[0]; // if there is only 1 value, then then that value is the solution
			dp[1] = Integer.max(dp[0], sequence[1]); // if there are 2 values, then the maximum of the 2 is the solution
			for (int i = 2; i < sequence.length; i++) { // we start at 2 since 0 and 1 have been solved
				dp[i] = Integer.max(dp[i-2] + sequence[i], dp[i-1]);	// the solutions is the maximum of either the value at index i
																		// plus the solution at i-2, but if the solution at i-1 is greater,
																		// then we should skip index i and use i-1 instead
			} // for i
			return dp[sequence.length-1];
		} // OptimiseDonationsDP method
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int[] arr = new int[N];
		for (int i = 0; i < N; i++) {
			arr[i] = in.nextInt();
		}
		out.println(MaximumNonConsecutiveSubsequence.solve(arr));
		out.close();
	}
}
