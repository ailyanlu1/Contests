package fhc15c2p2_all_critical;

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

public class FHC15C2P2 {
	private static FHC15C2P2 o = new FHC15C2P2();
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

		/*public BigInteger nextBigInteger() throws IOException {
			return new BigInteger(next());
		}*/

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
	
	private static int B = 20;
	private static int[][] bars = new int[B + 1][B + 1];
	
	private static void pre() {
		for (int i = 0; i <= B; i++) {
			for (int j = 0; j <= B; j++) {
				if (i == j || j == 0) bars[i][j] = 1;
				else if (j > i) bars[i][j] = 0;
				else bars[i][j] = bars[i - 1][j - 1] + bars[i - 1][j];
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		pre();
		int T = in.nextInt();
		for (int i = 1; i <= T; i++) {
			run(i);
		}
		out.close();
	}
	
	public static void run(int testCaseNum) throws IOException {
		double p = in.nextDouble();
		double[][] prob = new double[2000][B + 1];
		for (int i = 0; i < prob.length; i++) {
			for (int j = 0; j <= B; j++) {
				if (i == 0) {
					if (j == 0) prob[i][j] = 1;
					else prob[i][j] = 0;
				} else {
					for (int k = 0; k <= j; k++) {
						prob[i][j] += prob[i-1][k] * pow(p, j-k) * pow(1-p, B-j) * bars[B-k][j-k];
					}
				}
			}
		}
		double ans = 0;
		for (int i = 1; i < prob.length; i++) {
			ans += i * (prob[i][20] - prob[i - 1][20]);
		}
		out.printf("Case #%d: %.5f\n", testCaseNum, ans);
	}
	
	public static double pow(double base, long pow) {
		if (pow == 0)
			return 1;
		if (pow == 1)
			return base;
		if (pow % 2 == 0)
			return pow(base * base, pow / 2);
		return base * pow(base * base, pow / 2);
	}
}
