
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class MultiTestCaseFileTemplate {
	private static MultiTestCaseFileTemplate o = new MultiTestCaseFileTemplate();
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
	
	private static Reader in;
	private static PrintWriter out;
	
	private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
	
	// TODO CHANGE FILE NAMES
	private static final String input = "input.txt";
	private static final String output = "output.txt";
	
	public static void main(String[] args) throws IOException {
		String packageName = "";
		try {
			packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
		} catch (NullPointerException e) {}
		in = o.new Reader(packageName + input);
		out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + output)));
		// in = o.new Reader(System.in);
		// out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run();
		}
		out.close();
	}
	
	public static void run() throws IOException {
		// TODO INSERT CODE HERE
	}
}
