package mockecoo14p1_do_you_want_to_build_a_snowman;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class MockECOO14P1 {
	private static MockECOO14P1 o = new MockECOO14P1();
	private static final int NUM_OF_TEST_CASES = 5; // TODO CHANGE THIS TO THE NUMBER OF TEST CASES FOR THE QUESTION
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
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
		Reader in = o.new Reader(System.in); // TODO REMEMBER TO CHANGE THE FILE NAME
		for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
			run(in);
		} // for i
		out.close();
	} // main method
	
	public static void run(Reader in) throws IOException { // if you change the method of reading input, then the parameter type may have to be changed
		int N = in.nextInt();
		int width = Integer.max(22, ((N * 2) + 2) * N / 2 + 11);
		int height = (N + 7) * N / 2 + 14;
		int middle = (width - 1) / 2;
		char[][] snow = new char[height][width];
		// TWIGS
		snow[0] = new char[middle + 1];
		snow[0][middle] = '|';
		snow[1] = new char[middle + 4];
		snow[1][middle - 3] = '\\';
		snow[1][middle] = '|';
		snow[1][middle + 3] = '/';
		snow[2] = new char[middle + 3];
		snow[2][middle - 2] = '\\';
		snow[2][middle] = '|';
		snow[2][middle + 2] = '/';
		snow[3] = new char[middle + 2];
		snow[3][middle - 1] = '\\';
		snow[3][middle] = '|';
		snow[3][middle + 1] = '/';
		// HEAD
		String line = "XXXXXXX";
		for (int i = 0; i < middle - 3; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[4] = line.toCharArray();
		line = "X       X";
		for (int i = 0; i < middle - 4; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[5] = line.toCharArray();
		line = "X  O   O  X";
		for (int i = 0; i < middle - 5; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[6] = line.toCharArray();
		line = "X     V     X";
		for (int i = 0; i < middle - 6; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[7] = line.toCharArray();
		line = "X  X     X  X";
		for (int i = 0; i < middle - 6; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[8] = line.toCharArray();
		line = "X  XXXXX  X";
		for (int i = 0; i < middle - 5; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[9] = line.toCharArray();
		line = "X       X";
		for (int i = 0; i < middle - 4; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[10] = line.toCharArray();
		line = "XXXXXXX";
		for (int i = 0; i < middle - 3; i ++) {
			line = " " + line + " ";
		}
		line += " ";
		snow[11] = line.toCharArray();
		// BODY
		int tW = 9;
		int bW = 11;
		int sH = 12;
		for (int i = 1; i <= N; i++) { // each section
			for (int j = 1; j <= i + 2; j++) { // each line
				if (j == 1 || j == i + 2) line = " ";
				else line = "O";
				for (int k = 0; k < (((tW - 2) / 2) + (j - 1)); k++) {
					line = " " + line + " ";
				}
				line = "X" + line + "X";
				for (int k = 0; k < middle - (((tW - 2) / 2) + (j)); k++) {
					line = " " + line + " ";
				}
				line += " ";
				snow[sH++] = line.toCharArray();
			}
			line = "";
			for (int j = 0; j < bW; j++) {
				line += "X";
			}
			for (int j = 0; j < middle - bW / 2; j++) {
				line = " " + line + " ";
			}
			line += " ";
			snow[sH++] = line.toCharArray();
			tW = bW;
			bW = (((i + 1) * 2) + 2) * (i + 1) / 2 + 9;
		}
		// LEGS
		for (int i = 1; i <= 2; i ++) {
			line = "OOOO OOOO";
			for (int j = 0; j < middle - 4; j++) {
				line = " " + line + " ";
			}
			line += " ";
			snow[snow.length - i] = line.toCharArray();
		}
		// RIGHT ARM
		snow[12][middle + 5] = '-';
		snow[12][middle + 6] = '-';
		snow[12][middle + 7] = '-';
		snow[13][middle + 8] = '\\';
		snow[14][middle + 9] = '\\';
		snow[15][middle + 10] = '\\';
		snow[16][middle + 11] = 'M';
		// LEFT ARM
		snow[12][middle - 6] = '\\';
		snow[11][middle - 7] = '\\';
		snow[10][middle - 8] = '\\';
		snow[9][middle - 9] = '\\';
		snow[8][middle - 10] = 'W';
		for (int i = 0; i < snow.length; i++) {
			line = "";
			for (int j = 0; j < snow[i].length; j++) {
				if (snow[i][j] != '\u0000') line += snow[i][j];
				else line += " ";
			}
			out.println(line.replaceFirst("\\s++$", ""));
		}
		out.println(" ");
	} // run method
}