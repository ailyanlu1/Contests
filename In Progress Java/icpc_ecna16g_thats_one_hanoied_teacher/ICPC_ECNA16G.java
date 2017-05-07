package icpc_ecna16g_thats_one_hanoied_teacher;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class ICPC_ECNA16G { // 20/280 TLE and WA
	private static ICPC_ECNA16G o = new ICPC_ECNA16G();
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
	
	private static int[][] config = new int[3][53];
	private static int[][] towers = new int[3][53];
	private static int count = -1;
	private static boolean start = false;
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int max = 0;
		for (int i = 0; i < config.length; i++) {
			int h = in.nextInt();
			config[i][0] = h;
			for (int j = 1; j <= h; j++) {
				int disk = in.nextInt();
				max = Integer.max(disk, max);
				config[i][j] = disk;
			}
		}
		towers[0][0] = max;
		for (int i = 1; i <= max; i++) {
			towers[0][i] = max - i + 1;
		}
		move(max, 0, 1, 2);
		if (count == -1) out.println("No");
		else out.println(count);
		out.close();
	}
	
	public static void move (int n, int s, int t, int e) {
		if (n > 0) {
			move(n - 1, s, e, t);
			towers[e][++towers[e][0]] = towers[s][towers[s][0]];
			towers[s][towers[s][0]--] = 0;
			if (Arrays.toString(towers[0]).equals(Arrays.toString(config[0])) && Arrays.toString(towers[1]).equals(Arrays.toString(config[1]))
					&& Arrays.toString(towers[2]).equals(Arrays.toString(config[2]))) start = true;
			if (start) count++;
			move(n - 1, t, s, e);
		}
	}
}
