package ccc01s3_strategic_bombing;

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
import java.util.StringTokenizer;

public class CCC01S3 {
	private static CCC01S3 o = new CCC01S3();
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
	
	public class UF {

	    private int[] parent;  // parent[i] = parent of i
	    private byte[] rank;   // rank[i] = rank of subtree rooted at i (never more than 31)
	    private int count;     // number of components

	    /**
	     * Initializes an empty union–find data structure with {@code n} sites
	     * {@code 0} through {@code n-1}. Each site is initially in its own 
	     * component.
	     *
	     * @param  n the number of sites
	     * @throws IllegalArgumentException if {@code n < 0}
	     */
	    public UF(int n) {
	        if (n < 0) throw new IllegalArgumentException();
	        count = n;
	        parent = new int[n];
	        rank = new byte[n];
	        for (int i = 0; i < n; i++) {
	            parent[i] = i;
	            rank[i] = 0;
	        }
	    }

	    /**
	     * Returns the component identifier for the component containing site {@code p}.
	     *
	     * @param  p the integer representing one site
	     * @return the component identifier for the component containing site {@code p}
	     * @throws IndexOutOfBoundsException unless {@code 0 <= p < n}
	     */
	    public int find(int p) {
	        validate(p);
	        while (p != parent[p]) {
	            parent[p] = parent[parent[p]];    // path compression by halving
	            p = parent[p];
	        }
	        return p;
	    }

	    /**
	     * Returns the number of components.
	     *
	     * @return the number of components (between {@code 1} and {@code n})
	     */
	    public int count() {
	        return count;
	    }
	  
	    /**
	     * Returns true if the the two sites are in the same component.
	     *
	     * @param  p the integer representing one site
	     * @param  q the integer representing the other site
	     * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
	     *         {@code false} otherwise
	     * @throws IndexOutOfBoundsException unless
	     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
	     */
	    public boolean connected(int p, int q) {
	        return find(p) == find(q);
	    }
	    
	    /**
	     * Returns the rank by size of the component containing p
	     * 
	     * @param p the integer representing one site
	     * @return the rank by size of the component containing p
	     */
	    public byte rank(int p) {
	    	return rank[find(p)];
	    }
	  
	    /**
	     * Merges the component containing site {@code p} with the 
	     * the component containing site {@code q}.
	     *
	     * @param  p the integer representing one site
	     * @param  q the integer representing the other site
	     * @throws IndexOutOfBoundsException unless
	     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
	     */
	    public void union(int p, int q) {
	        int rootP = find(p);
	        int rootQ = find(q);
	        if (rootP == rootQ) return;

	        // make root of smaller rank point to root of larger rank
	        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
	        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
	        else {
	            parent[rootQ] = rootP;
	            rank[rootP]++;
	        }
	        count--;
	    }
	    
	    /**
	     * Unmerges the component containing site {@code p} with the 
	     * the component containing site {@code q}.
	     *
	     * @param  p the integer representing one site
	     * @param  q the integer representing the other site
	     * @throws IndexOutOfBoundsException unless
	     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
	     */
	    public void disjoin(int p, int q) {
	        int rootP = find(p);
	        int rootQ = find(q);
	        if (rootP == rootQ) return;

	        // make root of smaller rank point to root of larger rank
	        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootP;
	        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootQ;
	        else {
	            parent[rootQ] = rootP;
	            rank[rootP]--;
	        }
	        count++;
	    }

	    // validate that p is a valid index
	    private void validate(int p) {
	        int n = parent.length;
	        if (p < 0 || p >= n) {
	            throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n-1));  
	        }
	    }
	}
	
	public static class Edge {
		public int v;
		public int w;

		public Edge(int v, int w) {
			this.v = v;
			this.w = w;
		}

		@Override
		public int hashCode() {
			return 31 * v + w;
		}

		@Override
		public boolean equals(Object o) {
			if (o == this) return true;
			if (!(o instanceof Edge)) return false;
			Edge e = (Edge) o;
			return e.v == v && e.w == w;
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	public static void main(String[] args) throws IOException {
		String line = "";
		ArrayList<Edge> edges = new ArrayList<Edge>();
		ArrayList<Edge> disconnected = new ArrayList<Edge>();
		int count = 0;
		while (!(line = in.nextLine()).equals("**")) {
			edges.add(new Edge(line.charAt(0) - 'A', line.charAt(1) - 'A'));
		}
		for (Edge e: edges) {
			UF uf = o.new UF(26);
			for (Edge f: edges) {
				if (e != f) uf.union(f.v, f.w);
			}
			
			if (!uf.connected(0, 1)) {
				count += 1;
				disconnected.add(e);
			}
		}
		for (Edge e: disconnected) {
			out.println((char) (e.v + 'A') + "" + (char) (e.w + 'A'));
		}
		out.println("There are " + count + " disconnecting roads.");
		out.close();
	}
}
