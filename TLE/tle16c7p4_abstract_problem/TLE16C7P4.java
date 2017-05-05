package tle16c7p4_abstract_problem;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class TLE16C7P4 {
	private static TLE16C7P4 o = new TLE16C7P4();
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
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int T = in.nextInt();
		for (int i = 0; i < T; i++) {
			long x = in.nextLong();
			int count = 0;
			while (x != 0) {
				if ((x & 1) != 0) { // same as x % 2 != 0
					if ((x & 2) != 0 && x != 3) {
						x++;
					} else {
						x--;
					}
				} else {
					x = x >> 1; // same as x /= 2
				}
				count++;
			}
			out.println(count);
		}
		out.close();
	}
}
