package ecoo17r3p4_ice_cream_beach;

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

public class ECOO17R3P4 {
	private static ECOO17R3P4 o = new ECOO17R3P4();
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
	
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
	
	public static void main(String[] args) throws IOException {
		for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
			run(i);
			out.flush();
		}
		out.close();
	}
	
	private static long C[][];
	private static final long MOD = (long) (1e9 + 7);
	
	public static void run(int testCaseNum) throws IOException {
		int N = in.nextInt();
		int M = in.nextInt();
		long[] X = new long[N + 1];
		long[] F = new long[N + 1];
		C = new long[N + 1][N + 1];
		long[][] D = new long[N + 1][N + 1];
		long[][] dp = new long[N + 1][M + 1];
		
		for (int i = 1; i <= N; i++) {
			X[i] = in.nextInt();
			F[i] = in.nextInt();
		}
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				C[i][j] = F[i] * Math.abs(X[i] - X[j]) + C[i - 1][j];
			}
		}
		
		for (int i = 1; i <= N; i++) {
			for (int j = i; j <= N; j++) {
				D[i][j] = f(i, j);
			}
		}
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (i <= j) {
					dp[i][j] = 0;
				} else {
					dp[i][j] = Long.MAX_VALUE;
				}
			}
		}
		
		for (int i = 1; i <= N; i++) {
			dp[i][1] = f(1, i);
		}

		for (int i = 2; i <= N; i++) {
			for (int j = 2; j <= M; j++) {
				for (int k = 2; k <= i; k++) {
					dp[i][j] = Math.min(dp[i][j], dp[k - 1][j - 1] + D[k][i]);
				}
			}
		}
		out.println(dp[N][M] % MOD);
	}
	
	private static long f(int L, int R) {
		long ret = c(L, R, L);

		int l = L + 1;
		int r = R;
		int m = l + (r - l) / 2;
		while (l <= r) {
			if (c(L, R, m) < c(L, R, m - 1)) l = m + 1;
			else r = m - 1;
			m = l + (r - l) / 2;
		}
		return Math.min(ret, c(L, R, r));
	}
	
	private static long c(int l, int r, int j) {
		return C[r][j] - C[l - 1][j];
	}
}
