package cco13p2_tourney;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCO13P2 {
	private static CCO13P2 o = new CCO13P2();
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
	
	public class Player {
		public int pos;
		public int skill;
		public Player(int pos, int skill) {
			this.pos = pos;
			this.skill = skill;
		}
	}
	
	private static Player[] heap;
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int N = in.nextInt();
		int M = in.nextInt();
		heap = new Player[(int) Math.pow(2, N + 1)];
		for (int i = 0; i < heap.length/2; i++) {
			heap[i + heap.length/2] = o.new Player(i + 1, in.nextInt());
		}
		for (int i = heap.length/2 - 1; i >= 1; i--) {
			update(i, i);
		}
		for (int i = 0; i < M; i++) {
			char c = in.next().charAt(0);
			if (c == 'R') {
				int pos = in.nextInt();
				int skill = in.nextInt();
				int index = posToIndex(pos);
				heap[index] = o.new Player(pos, skill);
				update(index/2, 1);
			} else if (c == 'W') {
				out.println(heap[1].pos);
			} else {
				int pos = in.nextInt();
				int index = posToIndex(pos) / 2;
				int wins = 0;
				while(index >= 1 && heap[index].pos == pos) {
					wins++;
					index /= 2;
				}
				out.println(wins);
			}
		}
		out.close();
	}
	
	private static int posToIndex(int pos) {
		return pos + heap.length/2 - 1;
	}
	
	private static void update(int index, int end) {
		if (heap[index * 2].skill > (heap[index * 2 + 1]).skill) heap[index] = o.new Player(heap[index * 2].pos, heap[index * 2].skill);
		else heap[index] = o.new Player(heap[index * 2 + 1].pos, heap[index * 2 + 1].skill);
		if (index == end) return;
		update(index / 2, end);
	}
}
