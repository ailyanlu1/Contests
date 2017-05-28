package dmopc14c3p6_not_enough_time;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMOPC14C3P6 {
	private static DMOPC14C3P6 o = new DMOPC14C3P6();
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
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int T = in.nextInt();
		int[][] P = new int[N][3];
		int[][] V = new int[N][3];
		int[] dp = new int[T + 1];
		dp[0] = 0;
		for (int i = 1; i <= T; i++) {
			dp[i] = -1;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 3; j++) {
				P[i][j] = in.nextInt();
				V[i][j] = in.nextInt();
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = T; j >= 0; j--) {
				for (int k = 0; k < 3; k++) {
					if (dp[j] != -1 && j + P[i][k] <= T)
						dp[j + P[i][k]] = Math.max(dp[j + P[i][k]], dp[j] + V[i][k]);
				}
			}
		}
		int max = 0;
		for (int i = 0; i <= T; i++) {
			max = Math.max(max, dp[i]);
		}
		out.println(max);
		out.close();
	}
}
