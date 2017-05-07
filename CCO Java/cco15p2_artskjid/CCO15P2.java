package cco15p2_artskjid;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class CCO15P2 {
	private static CCO15P2 o = new CCO15P2();
	private static int n, m;
	private static int[][] adj;
	private static int[][] dp;
	
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
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		n = in.nextInt();
		m = in.nextInt();
		adj = new int[n][n];
		dp = new int[1 << 18][19];
		for (int i = 0; i < m; i++) {
			adj[in.nextInt()][in.nextInt()] = in.nextInt();
		}
		for (int i = 0; i < (1 << 18); i++) {
			for (int j = 0; j < 18; j++) {
				dp[i][j] = -1;
			}
		}
		System.out.println(dp(1, 0, 0));
	}
	
	private static int dp(int s, int c, int x) {
		if (dp[s][c] != -1) return dp[s][c];
		else if (c == n-1) return dp[s][c] = 0;
		int ans = -1 << 30;
		for (int i = 0; i < n; i++) {
			if (adj[c][i] == 0 || (s & 1 << i) > 0) continue;
			ans = Math.max(ans, adj[c][i] + dp(s | 1 << i, i, x+1));
		}
		return dp[s][c] = ans;
	}
}
