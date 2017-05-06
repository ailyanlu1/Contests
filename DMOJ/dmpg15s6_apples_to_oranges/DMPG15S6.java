package dmpg15s6_apples_to_oranges;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;

public class DMPG15S6 {
	private static DMPG15S6 o = new DMPG15S6();
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
	
	public class DirectedWeightedEdge { 
	    private final int v;
	    private final int w;
	    private final double weight;

	    /**
	     * Initializes a directed edge from vertex {@code v} to vertex {@code w} with
	     * the given {@code weight}.
	     * @param v the tail vertex
	     * @param w the head vertex
	     * @param weight the weight of the directed edge
	     * @throws IllegalArgumentException if either {@code v} or {@code w}
	     *    is a negative integer
	     * @throws IllegalArgumentException if {@code weight} is {@code NaN}
	     */
	    public DirectedWeightedEdge(int v, int w, double weight) {
	        if (v < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
	        if (w < 0) throw new IllegalArgumentException("Vertex names must be nonnegative integers");
	        if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
	        this.v = v;
	        this.w = w;
	        this.weight = weight;
	    }

	    /**
	     * Returns the tail vertex of the directed edge.
	     * @return the tail vertex of the directed edge
	     */
	    public int from() {
	        return v;
	    }

	    /**
	     * Returns the head vertex of the directed edge.
	     * @return the head vertex of the directed edge
	     */
	    public int to() {
	        return w;
	    }

	    /**
	     * Returns the weight of the directed edge.
	     * @return the weight of the directed edge
	     */
	    public double weight() {
	        return weight;
	    }

	    /**
	     * Returns a string representation of the directed edge.
	     * @return a string representation of the directed edge
	     */
	    public String toString() {
	        return v + "->" + w + " " + String.format("%5.2f", weight);
	    }
	    
	    @Override
	    public int hashCode() {
	    	return toString().hashCode();
	    }
	    
	    @Override
		public boolean equals(Object o) {
	    	if (o == this) return true;
	        if (!(o instanceof DirectedWeightedEdge)) {
	            return false;
	        }
	        DirectedWeightedEdge e = (DirectedWeightedEdge) o;
			return e.from() == v && e.to() == w && e.weight() == weight;
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int M = in.nextInt();
		ArrayList<DirectedWeightedEdge> edges = new ArrayList<DirectedWeightedEdge>();
		double[] cost = new double[N];
		HashMap<String, Integer> sToV = new HashMap<String, Integer>();
		for (int i = 0; i < N; i++) {
			sToV.put(in.next(), i);
		}
		for (int i = 0; i < M; i++) {
			edges.add(o.new DirectedWeightedEdge(sToV.get(in.next()), sToV.get(in.next()), in.nextDouble()));
		}
		int s = sToV.get("APPLES");
		cost[s] = 1.0;
		for (int i = 0; i < N; i++) {
			for (DirectedWeightedEdge e: edges) {
				cost[e.to()] = Math.max(cost[e.to()], cost[e.from()] * e.weight());
			}
		}
		double temp = cost[s];
		for (int i = 0; i < N; i++) {
			for (DirectedWeightedEdge e: edges) {
				cost[e.to()] = Math.max(cost[e.to()], cost[e.from()] * e.weight());
			}
		}
		if (cost[s] - temp > 0.001) out.println("YA");
		else out.println("NAW");
		out.close();
	}
}
