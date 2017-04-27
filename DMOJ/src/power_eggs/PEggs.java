package power_eggs;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class PEggs {
	
	private static PEggs o = new PEggs();
	
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
		Reader keyboard = o.new Reader(System.in);		
		// pre-processing
		int n = 32;
		int k = 32;
		long[][] dp = new long[n+1][k+1];
		for (int i = 0; i <= n; i++) {
			dp[0][i] = 1;
			dp[i][0] = 1;
		}
		
		for (int i = 1; i < dp.length; i++) {
			for (int j = 1; j < dp[i].length; j++) {
				dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
			}
		}
		int T = keyboard.nextInt();
		for (int i = 0; i < T; i++) {
			int F = keyboard.nextInt();
			int E = keyboard.nextInt();
			int low = 0;
			int high = n;
			while (low <= high) {
				int mid = (low + high)/2;
				if (dp[mid][E] - 1 < F) low = mid + 1;
				else high = mid - 1;
			}
			if (low <= 32) System.out.println(low);
			else System.out.println("Impossible");
		}
	}
}
