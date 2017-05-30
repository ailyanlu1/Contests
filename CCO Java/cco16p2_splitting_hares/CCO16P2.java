package cco16p2_splitting_hares;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class CCO16P2 {
	private static CCO16P2 o = new CCO16P2();
	public class Reader {
		private BufferedReader in;
		private StringTokenizer st;

		public Reader(InputStream inputStream) {
			in = new BufferedReader(new InputStreamReader(inputStream));
		}

		public Reader(String fileName) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(fileName));
		}

		public String next() throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(in.readLine().trim());
			}
			return st.nextToken();
		}

		public String next(String delim) throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(in.readLine().trim());
			}
			return st.nextToken(delim);
		}

		/*public BigInteger nextBigInteger() throws IOException {
			return new BigInteger(next());
		}*/

		public byte nextByte() throws IOException {
			return Byte.parseByte(next());
		}

		public byte nextByte(String delim) throws IOException {
			return Byte.parseByte(next(delim));
		}

		public char nextChar() throws IOException {
			return next().charAt(0);
		}

		public char nextChar(String delim) throws IOException {
			return next(delim).charAt(0);
		}

		public double nextDouble() throws IOException {
			return Double.parseDouble(next());
		}

		public double nextDouble(String delim) throws IOException {
			return Double.parseDouble(next(delim));
		}

		public float nextFloat() throws IOException {
			return Float.parseFloat(next());
		}

		public float nextFloat(String delim) throws IOException {
			return Float.parseFloat(next(delim));
		}

		public int nextInt() throws IOException {
			return Integer.parseInt(next());
		}

		public int nextInt(String delim) throws IOException {
			return Integer.parseInt(next(delim));
		}

		public long nextLong() throws IOException {
			return Long.parseLong(next());
		}

		public long nextLong(String delim) throws IOException {
			return Long.parseLong(next(delim));
		}

		public short nextShort() throws IOException {
			return Short.parseShort(next());
		}

		public short nextShort(String delim) throws IOException {
			return Short.parseShort(next(delim));
		}

		public String nextLine() throws IOException {
			st = null;
			return in.readLine();
		}
	} // Reader class
	
	public static class ComparablePair<Item extends Comparable<Item>, Item2 extends Comparable<Item2>> implements Comparable<ComparablePair<Item, Item2>> {
		private Item first;
		private Item2 second;

		public ComparablePair(Item first, Item2 second) {
			this.first = first;
			this.second = second;
		}

		public Item getFirst() {
			return this.first;
		}

		public void setFirst(Item first) {
			this.first = first;
		}

		public Item2 getSecond() {
			return this.second;
		}

		public void setSecond(Item2 second) {
			this.second = second;
		}

		public void set(Item first, Item2 second) {
			this.first = first;
			this.second = second;
		}

		@Override
		public int hashCode() {
			return 31 * first.hashCode() + second.hashCode();
		}

		@Override
		public boolean equals(Object o) {
			if (o == this) return true;
			if (!(o instanceof ComparablePair)) return false;
			ComparablePair p = (ComparablePair) o;
			return p.first.equals(first) && p.second.equals(second);
		}

		@Override
		public int compareTo(ComparablePair<Item, Item2> p) {
			if (first.compareTo(p.first) != 0) return first.compareTo(p.first);
			return (second.compareTo(p.second));
		}
	}

	
	public static class WeightedPoint2D {
		public int x;
		public int y;
		public int weight;
		
		public WeightedPoint2D(int x, int y, int weight) {
			this.x = x;
			this.y = y;
			this.weight = weight;
		}
		
		public double atan2(WeightedPoint2D p) {
			return Math.atan2(p.y - y, p.x - x);
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	private static final double EPS = 1e-9;
	
	public static void main(String[] args) throws IOException {
		int N  = in.nextInt();
		int ans = 0;
		WeightedPoint2D[] p = new WeightedPoint2D[N];
		for (int i = 0; i < N; i++) {
			p[i] = new WeightedPoint2D(in.nextInt(), in.nextInt(), in.nextInt());
		}
		for (int i = 0; i < N; i++) {
			ArrayList<ComparablePair<Double, Integer>> list = new ArrayList<ComparablePair<Double, Integer>>();
			for (int j = 0; j < N; j++) {
				if (i != j) {
					list.add(new ComparablePair<Double, Integer>(p[i].atan2(p[j]), p[j].weight));
				}
			}
			Collections.sort(list);
			int cur = 0;
			int k = 0;
			for (int j = 0; j < list.size(); j++) {
				for (; list.get(k % list.size()).getFirst() <= list.get(j).getFirst() + Math.PI * ((k < list.size() ? 1 : -1)); k++) {
					cur += list.get(k % list.size()).getSecond();
				}
				for(; j < list.size() - 1 && Math.abs(list.get(j + 1).getFirst() - list.get(j).getFirst()) < EPS; j++) {
					cur -= list.get(j).getSecond();
				}
				ans = Math.max(ans, cur + Math.max(p[i].weight, 0));
				cur -= list.get(j).getSecond();
			}
		}
		out.println(ans);
		out.close();
	}
}
