package coci07c1p4_zapis;

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

public class COCI07C1P4 {
	private static COCI07C1P4 o = new COCI07C1P4();
	public class Reader {
		private BufferedReader in;
		private StringTokenizer st;

		public Reader(InputStream inputStream) {
			in = new BufferedReader(new InputStreamReader(inputStream));
		}

		public Reader(String fileName) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(fileName));
		}

		public String next() throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(in.readLine().trim());
			}
			return st.nextToken();
		}

		public String next(String delim) throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(in.readLine().trim());
			}
			return st.nextToken(delim);
		}

		/*
		public BigInteger nextBigInteger() throws IOException {
			return new BigInteger(next());
		}
		*/

		public byte nextByte() throws IOException {
			return Byte.parseByte(next());
		}

		public byte nextByte(String delim) throws IOException {
			return Byte.parseByte(next(delim));
		}

		public char nextChar() throws IOException {
			return next().charAt(0);
		}

		public char nextChar(String delim) throws IOException {
			return next(delim).charAt(0);
		}

		public double nextDouble() throws IOException {
			return Double.parseDouble(next());
		}

		public double nextDouble(String delim) throws IOException {
			return Double.parseDouble(next(delim));
		}

		public float nextFloat() throws IOException {
			return Float.parseFloat(next());
		}

		public float nextFloat(String delim) throws IOException {
			return Float.parseFloat(next(delim));
		}

		public int nextInt() throws IOException {
			return Integer.parseInt(next());
		}

		public int nextInt(String delim) throws IOException {
			return Integer.parseInt(next(delim));
		}

		public long nextLong() throws IOException {
			return Long.parseLong(next());
		}

		public long nextLong(String delim) throws IOException {
			return Long.parseLong(next(delim));
		}

		public short nextShort() throws IOException {
			return Short.parseShort(next());
		}

		public short nextShort(String delim) throws IOException {
			return Short.parseShort(next(delim));
		}

		public String nextLine() throws IOException {
			st = null;
			return in.readLine();
		}
	} // Reader class
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	private static int N;
	private static char[] str;
	private static char[] open = {'(', '[', '{'};
	private static char[] closed = {')', ']', '}'};
	private static long[][] dp;
	private static final long MOD = 100000;
	
	public static void main(String[] args) throws IOException {
		N = in.nextInt();
		str = in.next().toCharArray();
		dp = new long[N][N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dp[i][j] = -1;
			}
		}
		long ans = solve(0, N - 1);
		if (ans < MOD) out.println(ans);
		else out.printf("%05d", ans % MOD);
		out.close();
	}
	
	private static long solve(int lo, int hi) {
		if (lo > hi) return 1;
		if (dp[lo][hi] != -1) return dp[lo][hi];
		long ret = 0;
		for (int mid = lo + 1; mid <= hi; mid += 2) {
			for (int i = 0; i < 3; i++) {
				if ((str[lo] == open[i] || str[lo] == '?') && (str[mid] == closed[i] || str[mid] == '?')) {
					ret = mod(ret + solve(lo + 1, mid - 1) * solve(mid + 1, hi));
				}
			}
		}
		return dp[lo][hi] = ret;
	}
	
	private static long mod(long a) {
		if (a >= MOD) return a % MOD + MOD;
		else return a;
	}
}
