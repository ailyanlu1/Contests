package halloween14p2_cat_girls;

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

public class Halloween14P2 {
	private static Halloween14P2 o = new Halloween14P2();
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
		long W = in.nextLong();
		long[] c = new long[N + 1];
		long[] w = new long[N + 1];
		long[] max = new long[N + 1];
		int i = 1;
		for (int n = 0; n < N; n++) {
			char ch = in.next().charAt(0);
			if (ch == 'A') {
				w[i] = in.nextLong() + w[i - 1];
				c[i] = in.nextLong() + c[i - 1];
				int low = 0;
				int high = i;
				while (low <= high) {
					int mid = low + (high - low) / 2;
					if (w[i] - w[mid] <= W) {
						high = mid - 1;
					} else {
						low = mid + 1;
					}
				}
				max[i] = Math.max(max[i - 1], c[i] - c[low]);
				out.println(max[i]);
				i++;
			} else if (ch == 'D') {
				i--;
			}
		}
		out.close();
	}
}
