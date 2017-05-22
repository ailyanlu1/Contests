package dmpg16b6_counting_money;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMPG16B6 {
	private static DMPG16B6 o = new DMPG16B6();
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
		for (int i = 0; i < N; i++) {
			char c = in.next().charAt(0);
			String val = in.next();
			if (val.equals("0")) out.println(0);
			else if (c == 'A') {
				int pow = 1;
				int ans = 0;
				for (int j = val.length() - 1; j >= 0; j--) {
					ans += pow * (val.charAt(j) - '0');
					pow *= -2;
				}
				out.println(ans);
			} else if (c == 'B') {
				String ans = "";
				long y = Long.parseLong(val);
				while (y != 0) {
					long rem = y % -2;
					y /= -2;
					if (rem < 0) {
						rem += 2;
						y += 1;
					}
					ans = "" + rem + ans;
				}
				out.println(ans);
			}
		}
		out.close();
	}
}