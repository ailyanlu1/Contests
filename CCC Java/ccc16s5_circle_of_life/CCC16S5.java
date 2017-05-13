package ccc16s5_circle_of_life;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCC16S5 {
	private static CCC16S5 o = new CCC16S5();
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
		int N = in.nextInt();
		long T = in.nextLong();
		int[] cell = new int[N];
		int[] temp = new int[N];
		String line = in.nextLine();
		for (int i = 0; i < N; i++) {
			cell[i] = Integer.parseInt("" + line.charAt(i));
		}
		for (int i = Long.toBinaryString(T).length(); i >= 0; i--) {
			if (((T >> i) & 1) != 0) {
				int p1 = (int) ((1L << i) % N);
				int p2 = (int) (N - p1) % N;
				for (int j = 0; j < N; j++) {
					temp[j] = cell[(p1 + j) % N] ^ cell[(p2 + j) % N];
				}
				System.arraycopy(temp, 0, cell, 0, N);
			}
		}
		for (int i = 0; i < N; i++) {
			out.print(cell[i]);
		}
		out.println();
		out.close();
	}
}
