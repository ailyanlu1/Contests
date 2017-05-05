package dmpg15s2_mmorpg;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;

public class DMPG15S2 {
	private static DMPG15S2 o = new DMPG15S2();
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
	
	public class Area {
		public int x1;
		public int y1;
		public int x2;
		public int y2;
		public Area (int x1, int y1, int x2, int y2){
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
		}
	}
	
	public static void main(String[] args) throws IOException {
		int R = in.nextInt();
		int N = in.nextInt();
		HashSet<Area> areas = new HashSet<Area>();
		for (int i = 0; i < R; i++) {
			int x1 = in.nextInt();
			int y1 = in.nextInt();
			int x2 = x1 + in.nextInt() - 1;
			int y2 = y1 + in.nextInt() - 1;
			areas.add(o.new Area(x1, y1, x2, y2));
		}
		int count = 0;
		for (int i = 0; i < N; i++) {
			ArrayList<Area> rem = new ArrayList<Area>();
			int x = in.nextInt();
			int y = in.nextInt();
			for (Area a: areas) {
				if (x >= a.x1 && x <= a.x2 && y >= a.y1 && y <= a.y2) {
					count++;
					rem.add(a);
				}
			}
			areas.removeAll(rem);
		}
		out.println(count);
		out.close();
	}
}
