package cchange;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCHANGE {
	private static CCHANGE o = new CCHANGE();
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
	
	public static class MinimumCoinChange {
		// This class should not be instantiated
		private MinimumCoinChange() {}
		
		/**
		 * Static method to determine the minimum number of coins to make change
		 * for {@code N} dollars given the coin values specified in the
		 * {@code coins} array. Each coin can be used an infinite amount
		 * of times.
		 * 
		 * Take time proportional to <em>NM</em> where <em>N</em> is the
		 * amount of dollars and <em>M</em> is the number of different
		 * coin values.
		 * 
		 * Take space proportional to <em>N</em>.
		 * 
		 * @param N      dollars
		 * @param coins  array of coin values
		 * @return       the minimum number of coins to make change
		 */
		public static int solve(int N, int[] coins) {
			int[] dp = new int[N + 1];
			dp[0] = 0;
			for (int i = 1; i <= N; i++) {
				dp[i] = Integer.MAX_VALUE;
			}
			for (int i = 1; i <= N; i++) {
				for (int j = 0; j < coins.length; j++) {
					if (coins[j] <= i) {
						int prev = dp[i - coins[j]];
						if (prev != Integer.MAX_VALUE && prev + 1 < dp[i]) dp[i] = prev + 1;
					}
				}
			}
			return dp[N];
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int x = in.nextInt();
		int n = in.nextInt();
		int[] coins = new int[n];
		for (int i = 0; i < n; i++) {
			coins[i] = in.nextInt();
		}
		out.println(MinimumCoinChange.solve(x, coins));
		out.close();
	}
}
