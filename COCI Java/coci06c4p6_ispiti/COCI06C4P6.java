package coci06c4p6_ispiti;

import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;

public class COCI06C4P6 {
	private static COCI06C4P6 o = new COCI06C4P6();
	public class DataInputStreamReader {
		final private int BUFFER_SIZE = 1 << 16;
		private DataInputStream din;
		private byte[] buffer;
		private int bufferPointer, bytesRead;

		public DataInputStreamReader(InputStream inputStream) {
			din = new DataInputStream(inputStream);
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		public DataInputStreamReader(String file_name) throws IOException {
			din = new DataInputStream(new FileInputStream(file_name));
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		public String nextLine() throws IOException {
			byte[] buf = new byte[64]; // line length
			int cnt = 0, c;
			while ((c = read()) != -1) {
				if (c == '\n') break;
				buf[cnt++] = (byte) c;
			}
			return new String(buf, 0, cnt);
		}

		public int nextInt() throws IOException {
			int ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg) c = read();
			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');

			if (neg) return -ret;
			return ret;
		}

		public long nextLong() throws IOException {
			long ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg) c = read();
			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');
			if (neg) return -ret;
			return ret;
		}

		public double nextDouble() throws IOException {
			double ret = 0, div = 1;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg) c = read();

			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');

			if (c == '.') {
				while ((c = read()) >= '0' && c <= '9') {
					ret += (c - '0') / (div *= 10);
				}
			}

			if (neg) return -ret;
			return ret;
		}
		
		public char nextChar() throws IOException {
			int c = read();
			while (c == ' ' || c == '\n') {
				c = read();
			}
			return (char) c;
		}

		private void fillBuffer() throws IOException {
			bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
			if (bytesRead == -1) buffer[0] = -1;
		}

		private byte read() throws IOException {
			if (bufferPointer == bytesRead) fillBuffer();
			return buffer[bufferPointer++];
		}

		public void close() throws IOException {
			if (din == null) return;
			din.close();
		}
	}
	
	private static DataInputStreamReader in = o.new DataInputStreamReader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	public class Student {
		public int a, b, ind, sortedInd;
		
		public Student(int a, int b, int ind) {
			this.a = a;
			this.b = b;
			this.ind = ind;
		}
	}
	
	public class StudentPairComparator implements Comparator<Student> {
		@Override
		public int compare(Student s1, Student s2) {
			if (s1.b != s2.b) return s1.b - s2.b;
			return s1.a - s2.a;
		}
	}
	
	public class StudentIndexComparator implements Comparator<Student> {
		@Override
		public int compare(Student s1, Student s2) {
			return s1.ind - s2.ind;
		}
	}
	
	public class Event {
		int ind, type;
		public Event(int ind, int type) {
			this.ind = ind;
			this.type = type;
		}
	}
	
	public class TournamentTree {
		private int[] tree;
		
		public TournamentTree(int size) {
			tree = new int[size * 3];
			for (int i = 0; i < size * 3; i++) {
				tree[i] = -1;
			}
		}
		
		public void update(int cur, int l, int r, int i) {
			if (l > S[i].sortedInd || r < S[i].sortedInd) return;
			if (l == r) {
				tree[cur] = i;
				return;
			}
			int m = (l + r) >> 1;
			update(2 * cur, l, m, i);
			update(2 * cur + 1, m + 1, r, i);
			if (tree[2 * cur] == -1) tree[cur] = tree[2 * cur + 1];
			else if (tree[2 * cur + 1] == -1) tree[cur] = tree[2 * cur];
			else if (S[tree[2 * cur]].a < S[tree[2 * cur + 1]].a) tree[cur] = tree[2 * cur + 1];
			else tree[cur] = tree[2 * cur];
		}
		
		public int query(int cur, int l, int r, int i) {
			if (r <= S[i].sortedInd || tree[cur] == -1 || S[tree[cur]].a < S[i].a) return -1;
			if (l == r) return tree[cur];
			int m = (l + r) >> 1;
			int left = query(2 * cur, l, m, i);
			if (left != -1) return left;
			else return query(2 * cur + 1, m + 1, r, i);
		}
	}
	
	private static Student[] S;
	private static Event[] E;
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		S = new Student[N];
		E = new Event[N];
		int j = 0;
		for (int i = 0; i < N; i++) {
			char c = in.nextChar();
			if (c == 'D') {
				S[j] = o.new Student(in.nextInt(), in.nextInt(), j);
				E[i] = o.new Event(j++, 1);
			} else if (c == 'P') {
				E[i] = o.new Event(in.nextInt() - 1, 2);
			} else {
				i--;
			}
		}
		Arrays.sort(S, 0, j, o.new StudentPairComparator());
		for (int i = 0; i < j; i++) {
			S[i].sortedInd = i;
		}
		Arrays.sort(S, 0, j, o.new StudentIndexComparator());
		TournamentTree tree = o.new TournamentTree(N);
		for (int i = 0; i < N; i++) {
			if (E[i].type == 1) {
				tree.update(1, 0, j - 1, E[i].ind);
			} else {
				int q = tree.query(1, 0, j - 1, E[i].ind);
				if (q == -1) out.println("NE");
				else out.println(q + 1);
			}
		}
		out.close();
	}
}
