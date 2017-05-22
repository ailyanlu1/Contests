package dmpg17s3_black_and_white_iii;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMPG17S3 {
	private static DMPG17S3 o = new DMPG17S3();
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
	private static final long MOD = (long) (1e9 + 7);
	
	public static void main(String[] args) throws IOException {
		int K = in.nextInt();
		int M = in.nextInt();
		int L = 1 << K;
		int count = 0;
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < L; j++) {
				if (in.next().equals("#")) count++;
			}
		}
		long p = 2;
		for (int i = 1; i <= M; i++) {
			p = pow(p, 4, MOD);
		}
		out.println(pow(p - 1, count, MOD));
		out.close();
	}
	
	public static long pow(long base, long pow, long mod) {
		if (pow == 0)
			return 1;
		if (pow == 1)
			return base;
		if (pow % 2 == 0)
			return pow(base * base % mod, pow / 2, mod);
		return base * pow(base * base % mod, pow / 2, mod) % mod;
	}
}
