package ccoqr16p1_stupendous_bowties;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.StringTokenizer;

public class CCOQR16P1 {
	private static CCOQR16P1 o = new CCOQR16P1();
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
		int[] x = new int[N];
		int[] y = new int[N];
		ArrayList<Integer>[] X = new ArrayList[N];
		ArrayList<Integer>[] Y = new ArrayList[N];
		HashMap<Integer, Integer> xInd = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> yInd = new HashMap<Integer, Integer>();
		for (int i = 0; i < N; i++) {
			X[i] = new ArrayList<Integer>();
			Y[i] = new ArrayList<Integer>();
		}
		int xCount = 0;
		int yCount = 0;
		for (int i = 0; i < N; i++) {
			x[i] = in.nextInt();
			y[i] = in.nextInt();
			if (xInd.get(x[i]) == null) xInd.put(x[i], xCount++);
			if (yInd.get(y[i]) == null) yInd.put(y[i], yCount++);
			X[xInd.get(x[i])].add(y[i]);
			Y[yInd.get(y[i])].add(x[i]);
		}
		for (int i = 0; i < N; i++) {
			Collections.sort(X[i]);
			Collections.sort(Y[i]);
		}
		
		long ans = 0;
		for (int i = 0; i < N; i++) {
			long x1 = Collections.binarySearch(Y[yInd.get(y[i])], x[i]);
			long y1 = Collections.binarySearch(X[xInd.get(x[i])], y[i]);
			long x2 = Y[yInd.get(y[i])].size() - x1 - 1;
			long y2 = X[xInd.get(x[i])].size() - y1 - 1;
			ans += (x1 * y1) * (x2 * y2) + (x1 * y2) * (x2 * y1);
		}
		out.println(ans);
		out.close();
	}
}
