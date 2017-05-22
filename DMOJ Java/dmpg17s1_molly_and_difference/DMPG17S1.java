package dmpg17s1_molly_and_difference;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class DMPG17S1 {
	private static DMPG17S1 o = new DMPG17S1();
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
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		long[] arr = new long[N];
		for (int i = 0; i < N; i++) {
			arr[i] = in.nextLong();
		}
		Arrays.sort(arr);
		long min = Long.MAX_VALUE;
		for (int i = 1; i < N; i++) {
			min = Math.min(Math.abs(arr[i] - arr[i - 1]), min);
		}
		System.out.println(min);
	}
}
