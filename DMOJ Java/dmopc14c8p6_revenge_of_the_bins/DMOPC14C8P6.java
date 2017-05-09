package dmopc14c8p6_revenge_of_the_bins;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DMOPC14C8P6 {
	private static DMOPC14C8P6 o = new DMOPC14C8P6();
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
	        heap = new Node[N * 4];
	        build(1, 1, N);
	    }

	    private void build(int v, int from, int to) {
	        heap[v] = new Node(from, to);
	        if (from == to) return;
	        int mid = (from + to) / 2;
	        build(2 * v, from, mid);
	        build(2 * v + 1, mid + 1, to);
	    }

	    public void update(int from, int to, int value) {
	        update(1, from, to, value);
	    }

	    private void update(int v, int from, int to, int value) {

	    	Node n = heap[v];
	        
	        if (heap[v].from == from && heap[v].to == to) {
	        	change(n, value);
	        	return;
	        }
	        if (heap[v].perm != 0) {
	        	propagate(v, heap[v].perm);
	        }
	        int mid = (heap[v].from + heap[v].to) / 2;
	        if (to <= mid) update(2 * v, from, to, value);
	        else if (from > mid) update (2 * v + 1, from, to, value);
	        else {
	        	update(2 * v, from, mid, value);
	        	update(2 * v + 1, mid + 1, to, value);
	        }
	        heap[v].min = Math.min(heap[2 * v].min, heap[2 * v + 1].min);
	    }

	    private void propagate(int v, int value) {
	    	change(heap[2 * v], value);
	        change(heap[2 * v + 1], value);
	        heap[v].perm = 0;
	    }

	    private void change(Node n, int value) {
	        n.min += value;
	        n.perm += value;
	    }

	    class Node {
	        int min;
	        int perm;
	        int from;
	        int to;

	        Node (int from, int to) {
	        	this.from = from;
	        	this.to = to;
	        }
	    }
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int[] a = new int[N];
		for (int i = 0; i < N; i++) {
			a[i] = in.nextInt();
		}
		int ans = 0;
		SegmentTree st = o.new SegmentTree(N);
		for(int i = 0; i < N/2; i++) {
			st.update(1, a[i], 2);
			st.update(1,  a[i * 2], -1);
			st.update(1, a[i * 2 + 1], -1);
			int minimum = st.heap[1].min;
			if (minimum < 0) continue;
			ans = i + 1;
			
		}
		out.println(ans);
		out.close();
	}
}
