package mmcc14p1_tenri;

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

public class MMCC14P1 {
	private static MMCC14P1 o = new MMCC14P1();
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
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int S = in.nextInt();
		int[] M = new int[N];
		int[][] dp = new int[(1 << N)][S + 1];
		for (int i = 0; i < N; i++) {
			M[i] = in.nextInt();
			for (int j = 0; j <= S; j++) {
				dp[1 << i][j] = (M[i] + j) * (M[i] + j) + j;
			}
		}
		for (int i = 1; i < (1 << N); i++) {
			int count = 0;
			for (int j = 0; j < N; j++) {
				if ((i & (1 << j)) != 0) {
					count++;
				}
			}
			if (count % 2 == 0) continue;
			for (int j = 1; j < i; j++) {
				if ((i & j) == 0) {
					for (int k = 0; k < N; k++) {
						if (((i | j) & (1 << k)) == 0) {
							int ind = i | j | (1 << k);
							int[] temp = new int[S + 1];
							for (int a = 0; a <= S; a++) {
								for (int b = 0; b <= a; b++) {
									temp[a] = Math.max(temp[a], dp[i][b] * dp[j][a - b]);
								}
							}
							for (int a = S; a >= 0; a--) {
								for (int b = 0; b <= a; b++) {
									dp[ind][a] = Math.max(dp[ind][a], Math.min(temp[b], (M[k] + a - b) * (M[k] + a - b)) + a - b);
								}
							}
						}
					}
				}
			}
		}
		out.println(dp[(1 << N) - 1][S]);
		out.close();
	}
}
