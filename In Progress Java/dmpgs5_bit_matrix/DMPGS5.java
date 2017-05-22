package dmpgs5_bit_matrix;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class DMPGS5 { // 20/100 WA (Long Integer Overflow)
	private static DMPGS5 o = new DMPGS5();
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
		int M = in.nextInt();
		long[][] arr = new long[N][M];
		arr[N - 1][M - 1] = (1L << (N + M - 2)) - 1;
		for (int i = M - 2; i >= 0; i--) {
			arr[N - 1][i] = arr[N - 1][i + 1] >> 1;
		}
		long shift = 1L;
		for (int i = N - 2; i >= 0; i--) {
			arr[i][M - 1] = arr[i + 1][M - 1] - shift;
			shift = shift << 1;
		}
		for (int i = N - 2; i >= 0; i--) {
			for (int j = M - 2; j >= 0; j--) {
				arr[i][j] = arr[i + 1][j] & arr[i][j + 1];
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
	}
}
