package ccc09s5_wireless;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCC09S5 {
	private static CCC09S5 o = new CCC09S5();
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
	
	public static void main(String[] args) throws IOException {
		int M = in.nextInt();
		int N = in.nextInt();
		int K = in.nextInt();
		int[][] grid = new int[N + 1][M];
		for (int i = 0; i < K; i++) {
			int x = in.nextInt() - 1;
			int y = in.nextInt() - 1;
			int r = in.nextInt();
			int b = in.nextInt();
			for (int j = Math.max(0, y - r); j <= Math.min(M - 1, y + r); j++) {
				int dist = (int) Math.sqrt(r * r - (y - j) * (y - j));
				int left = Math.max(0, x - dist);
				int right = Math.min(N - 1, x + dist);
				grid[left][j] += b;
				grid[right + 1][j] -= b;
			}
		}
		int max = 0;
		int count = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (i > 0) grid[i][j] += grid[i - 1][j];
				if (grid[i][j] > max) {
					max = grid[i][j];
					count = 1;
				} else if (grid[i][j] == max) {
					count++;
				}
			}
		}
		out.println(max);
		out.println(count);
		out.close();
	}
}
