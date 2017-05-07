package ecoo13r1p3_hexudoku;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class ECOO13R1P3 {
	private static ECOO13R1P3 o = new ECOO13R1P3();
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
	private static final int NUM_OF_TEST_CASES = 10;
	private static char[][][][] board = new char[4][4][4][4];
	private static char[] digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	private static int count = 0;
	
	public static void main(String[] args) throws IOException {
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run();
		}
		out.close();
	}
	
	public static void run() throws IOException {
		count = 0;
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				String line = in.nextLine();
				int cur = 0;
				for (int j = 0; j < 4; j++) {
					board[i][j][k] = line.substring(cur, cur + 4).toCharArray();
					cur += 4;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				for (int j = 0; j < 4; j++) {
					for (int m = 0; m < 4; m++) {
						if (board[i][j][k][m] == '-') {
							check(i, j, k, m);
						}
					}
				}
			}
		}
		out.println(count);
	}
	
	private static void check(int I, int J, int K, int M) {
		for (int h = 0; h < digits.length; h++) {
			boolean esc = false;
			for (int k = 0; k < 4; k++) {
				for (int m = 0; m < 4; m++) {
					if (board[I][J][k][m] == digits[h]) {
						esc = true;
						break;
					}
				}
				if (esc) break;
			}
			if (esc) continue;
			esc = false;
			for (int j = 0; j < 4; j++) {
				for (int m = 0; m < 4; m++) {
					if (board[I][j][K][m] == digits[h]) {
						esc = true;
						break;
					}
				}
				if (esc) break;
			}
			if (esc) continue;
			esc = false;
			for (int i = 0; i < 4; i++) {
				for (int k = 0; k < 4; k++) {
					if (board[i][J][k][M] == digits[h]) {
						esc = true;
						break;
					}
				}
				if (esc) break;
			}
			if (esc) continue;
			board[I][J][K][M] = digits[h];
			count++;
			return;
		}
	}
}
