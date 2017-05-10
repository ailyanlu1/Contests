package ccoprep16q1_city_game;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Stack;

public class CCOPrep16Q1 {
	private static CCOPrep16Q1 o = new CCOPrep16Q1();
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
	private static int[][] a;
	
	public static void main(String[] args) throws IOException {
		int K = in.nextInt();
		for (int i = 0; i < K; i++) {
			run();
		}
		out.close();
	}
	
	private static void run() throws IOException {
		int M = in.nextInt();
		int N = in.nextInt();
		a = new int[M][N];
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				char c = in.next().charAt(0);
				if (c == 'F') a[i][j] = 0;
				else a[i][j] = 1;
			}
		}
		out.println(getMaxZeroSubmatrix() * 3);
	}
	
	private static int getMaxZeroSubmatrix() {
		int rows = a.length;
		int cols = a[0].length;
		int[][] height = new int[rows][cols];
		Stack<Integer> s = new Stack<Integer>();
		int ret = 0;
		for (int j = 0; j < cols; j++) {
			for (int i = rows - 1; i >= 0; i--) {
				if (a[i][j] == 1)
					height[i][j] = 0;
				else
					height[i][j] = 1 + (i == rows - 1 ? 0 : height[i + 1][j]);
			}
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int minIndex = j;
				while (!s.isEmpty() && height[i][s.peek()] >= height[i][j]) {
					ret = Math.max(ret, (j - s.peek()) * (height[i][s.peek()]));
					minIndex = s.peek();
					height[i][minIndex] = height[i][j];
					s.pop();
				}
				s.push(minIndex);
			}
			while (!s.isEmpty()) {
				ret = Math.max(ret, (cols - s.peek()) * height[i][s.peek()]);
				s.pop();
			}
		}
		return ret;
	}
}
