package ccc12s4_a_coin_game;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.StringTokenizer;

public class CCC12S4 {
	private static CCC12S4 o = new CCC12S4();
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
		int n;
		while ((n = in.nextInt()) != 0) {
			int[] coins = new int[n];
			for (int i = 0; i < n; i++) {
				coins[in.nextInt() - 1] = i;
			}
			int start = 0;
			int end = 0;
			for (int i = 0; i < n; i++) {
				start |= coins[i] << (3 * i);
				end |= i << (3 * i);
			}
			byte[] moves = new byte[1 << 24];
			for (int i = 0; i < (1 << 24); i++) {
				moves[i] = Byte.MAX_VALUE;
			}
			moves[start] = 0;
			Queue<Integer> q = new ArrayDeque<Integer>();
			q.offer(start);
			while (!q.isEmpty()) {
				int c = q.poll();
				int[] stack = new int[n];
				for (int i = 0; i < n; i++) {
					stack[i] = Integer.MAX_VALUE;
				}
				for (int i = n - 1; i >= 0; i--) {
					stack[(c >> (3 * i)) % 8] = i;
				}
				for (int i = 0; i < n - 1; i++) {
					for (int j = 0; j < 2; j++) {
						if (stack[i + j] < stack[i - j + 1]) {
							int next = c & ~(7 << (3 * stack[i+j])) | (i - j + 1) << (3 * stack[i+j]);
							if (moves[c] + 1 < moves[next]) {
								moves[next] = (byte) (moves[c] + 1);
								q.offer(next);
							}
						}
					}
				}
			}
			if (moves[end] == Byte.MAX_VALUE) out.println("IMPOSSIBLE");
			else out.println(moves[end]);
		}		
		out.close();
	}
}
