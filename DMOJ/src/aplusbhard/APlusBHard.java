package aplusbhard;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class APlusBHard {
	private static APlusBHard o = new APlusBHard();
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
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		int n = in.nextInt();
		BigInteger[] sum = new BigInteger[n];
		for (int i = 0; i < n; i++) {
			String a = in.next();
			String b = in.next();
			BigInteger A = null;
			BigInteger B = null;
			byte[] aB;
			byte[] bB;
			if (a.charAt(0) == '-') {
				aB = new byte[a.length() - 1];
				for (int j = 0; j < aB.length; j++) {
					aB[aB.length-1-j] = (byte) Integer.parseInt("" + a.charAt(j+1));
				}
				A = new BigInteger(aB, true);
			} else {
				aB = new byte[a.length()];
				for (int j = 0; j < aB.length; j++) {
					aB[aB.length-1-j] = (byte) Integer.parseInt("" + a.charAt(j));
				}
				A = new BigInteger(aB, false);
			}
			if (b.charAt(0) == '-') {
				bB = new byte[b.length() - 1];
				for (int j = 0; j < bB.length; j++) {
					bB[bB.length-1-j] = (byte) Integer.parseInt("" + b.charAt(j+1));
				}
				B = new BigInteger(bB, true);
			} else {
				bB = new byte[b.length()];
				for (int j = 0; j < bB.length; j++) {
					bB[bB.length-1-j] = (byte) Integer.parseInt("" + b.charAt(j));
				}
				B = new BigInteger(bB, false);
			}
			System.out.println(A + " " + B);
			if (!A.isNegative() && B.isNegative()) {
				sum[i] = A.subtract(B);
			} else if (A.isNegative() && !B.isNegative()) {
				sum[i] = B.subtract(A);
			} else {
				sum[i] = A.add(B);
			}
		}
		for (int i = 0; i < n; i++) {
			System.out.println(sum[i]);
		}
	}
}
