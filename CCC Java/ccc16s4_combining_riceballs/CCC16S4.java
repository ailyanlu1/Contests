package ccc16s4_combining_riceballs;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class CCC16S4 {
	private static CCC16S4 o = new CCC16S4();
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
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	private static int rbPrefix[];
	private static int dp[][];
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int largest = 0;
		rbPrefix = new int[N + 1];
		dp = new int[N + 1][N + 1];
		for (int i = 0; i <= N; i++) {
			Arrays.fill(dp[i], -1);
		}
		for (int i = 1; i <= N; i++) {
			rbPrefix[i] = in.nextInt();
			largest = Math.max(largest, rbPrefix[i]);
			rbPrefix[i] += rbPrefix[i - 1];
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				largest = Math.max(largest, comb(i, j) * get(i, j));
			}
		}
		out.println(largest);
		out.close();
	}
	
	private static int comb(int i, int j) {
		if (dp[i][j] != -1) return dp[i][j];
		if (i >= j) return dp[i][j] = 1;
		int ret = 0;
		int b = j;
		for (int a = i; a < j; a++) {
			while (b > i && get(i, a) > get(b, j)) {
				b--;
			}
			if (get (i, a) == get (b, j)) {
				ret = Math.max(ret, comb(i, a) * comb(a + 1, b - 1) * comb(b, j));
			}
		}
		return dp[i][j] = ret;
	}
	
	private static int get(int a, int b) {
		return rbPrefix[b] - rbPrefix[a - 1];
	}
}
