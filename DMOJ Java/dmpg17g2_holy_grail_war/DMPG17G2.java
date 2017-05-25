package dmpg17g2_holy_grail_war;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMPG17G2 {
	private static DMPG17G2 o = new DMPG17G2();
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
	
	public class SegmentTree {
		private Node[] heap;
		
		public SegmentTree(int N) {
			heap = new Node[3 * N];
			for (int i = 0; i < heap.length; i++) {
				heap[i] = new Node();
			}
		}
		
		private Node propagate(Node l, Node r) {
			if (l.sum == Integer.MIN_VALUE) return r;
			if (r.sum == Integer.MIN_VALUE) return l;
			Node ret = new Node();
			ret.sum = l.sum + r.sum;
			ret.lv = Math.max(l.lv, l.sum + r.lv);
			ret.rv = Math.max(r.rv, r.sum + l.rv);
			ret.mv = Math.max(ret.lv, Math.max(ret.rv, Math.max(ret.sum, Math.max(l.rv + r.lv, Math.max(l.mv, r.mv)))));
			return ret;
		}
		
		public void update(int l, int r, long v) {
			update(1, l, r, v);
		}
		
		private void update(int i, int l, int r, long v) {
			if (l > v || r < v) return;
			if (l == r) {
				heap[i].sum = heap[i].lv = heap[i].rv = heap[i].mv = arr[l];
				return;
			}
			int m = (l + r) / 2;
			update(i * 2, l, m, v);
			update(i * 2 + 1, m + 1, r, v);
			heap[i] = propagate(heap[i * 2], heap[i * 2 + 1]);
		}
		
		public long query(int l, int r) {
			return query(1, 1, N, l, r).mv;
		}
		
		private Node query(int i, int cL, int cR, int l, int r) {
			if (cL > r || cR < l) {
				Node ret = new Node();
				ret.lv = Integer.MIN_VALUE;
				ret.rv = Integer.MIN_VALUE;
				ret.mv = Integer.MIN_VALUE;
				ret.sum = Integer.MIN_VALUE;
				return ret;
			}
			if (cL >= l && cR <= r) return heap[i];
			int m = (cL + cR) / 2;
			return propagate(query(i * 2, cL, m, l, r), query(i * 2 + 1, m + 1, cR, l, r));
		}
		
		public class Node {
			public long lv, rv, mv, sum;
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	private static int[] arr;
	private static int N;
	
	public static void main(String[] args) throws IOException {
		N = in.nextInt();
		int Q = in.nextInt();
		arr = new int[N + 1];
		SegmentTree st = o.new SegmentTree(N);
		for (int i = 1; i <= N; i++) {
			arr[i] = in.nextInt();
			st.update(1, N, i);
		}
		for (int q = 0; q < Q; q++) {
			char c = in.next().charAt(0);
			if (c == 'S') {
				int i = in.nextInt();
				int x = in.nextInt();
				arr[i] = x;
				st.update(1, N, i);
			} else if (c == 'Q') {
				out.println(st.query(in.nextInt(), in.nextInt()));
			}
		}
		out.close();
	}
}
