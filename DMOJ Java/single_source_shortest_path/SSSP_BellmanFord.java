package single_source_shortest_path;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.Stack;

public class SSSP_BellmanFord {
    
    private static SSSP_BellmanFord o = new SSSP_BellmanFord();
    
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
    
    public class DirectedWeightedEdge implements Comparable<DirectedWeightedEdge> { 
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
        
        /**
         * Compares two edges by weight.
         * Note that {@code compareTo()} is not consistent with {@code equals()},
         * which uses the reference equality implementation inherited from {@code Object}.
         *
         * @param  that the other edge
         * @return a negative integer, zero, or positive integer depending on whether
         *         the weight of this is less than, equal to, or greater than the
         *         argument edge
         */
        @Override
        public int compareTo(DirectedWeightedEdge that) {
            return Double.compare(this.weight, that.weight);
        }
        
        @Override
        public int hashCode() {
            int result = 31 * v + w;
            result = 31 * result + ((Double) weight).hashCode();
            return result;
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof DirectedWeightedEdge)) return false;
            DirectedWeightedEdge e = (DirectedWeightedEdge) o;
            return e.from() == v && e.to() == w && e.weight() == weight;
        }
    }
    
    public class BellmanFordDirectedSP {
        private double[] distTo;          // distTo[v] = distance  of shortest s->v path
        private DirectedWeightedEdge[] edgeTo;    // edgeTo[v] = last edge on shortest s->v path
        
        /**
         * Computes a shortest-paths tree from the source vertex {@code s} to every other
         * vertex in the edge list.
         *
         * @param  V the number of verticies
         * @param  edges the edge list
         * @param  s the source vertex
         * @throws IllegalArgumentException unless {@code 0 <= s < V}
         * @throws IllegalArgumentException if there is a negative cycle
         */
        public BellmanFordDirectedSP(int V, DirectedWeightedEdge[] edges, int s) {
            distTo = new double[V];
            edgeTo = new DirectedWeightedEdge[V];

            validateVertex(s);

            for (int v = 0; v < V; v++)
                distTo[v] = Double.POSITIVE_INFINITY;
            distTo[s] = 0.0;

            for (int i = 0; i < V - 1; i++) {
                for (DirectedWeightedEdge e : edges) {
                    int v = e.from();
                    int w = e.to();
                    if (distTo[w] > distTo[v] + e.weight()) {
                        distTo[w] = distTo[v] + e.weight();
                        edgeTo[w] = e;
                    }
                }
            }
            
            for (DirectedWeightedEdge e : edges) {
                if (distTo[e.to()] > distTo[e.from()] + e.weight()) throw new IllegalArgumentException("Graph has a negative cycle.");
            }
        }

        /**
         * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
         * @param  v the destination vertex
         * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
         *         {@code Double.POSITIVE_INFINITY} if no such path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public double distTo(int v) {
            validateVertex(v);
            return distTo[v];
        }

        /**
         * Returns true if there is a path from the source vertex {@code s} to vertex {@code v}.
         *
         * @param  v the destination vertex
         * @return {@code true} if there is a path from the source vertex
         *         {@code s} to vertex {@code v}; {@code false} otherwise
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public boolean hasPathTo(int v) {
            validateVertex(v);
            return distTo[v] < Double.POSITIVE_INFINITY;
        }

        /**
         * Returns a shortest path from the source vertex {@code s} to vertex {@code v}.
         *
         * @param  v the destination vertex
         * @return a shortest path from the source vertex {@code s} to vertex {@code v}
         *         as an iterable of edges, and {@code null} if no such path
         * @throws IllegalArgumentException unless {@code 0 <= v < V}
         */
        public Iterable<DirectedWeightedEdge> pathTo(int v) {
            validateVertex(v);
            if (!hasPathTo(v)) return null;
            Stack<DirectedWeightedEdge> path = new Stack<DirectedWeightedEdge>();
            for (DirectedWeightedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
                path.push(e);
            }
            return path;
        }

        // throw an IllegalArgumentException unless {@code 0 <= v < V}
        private void validateVertex(int v) {
            int V = distTo.length;
            if (v < 0 || v >= V)
                throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
        }
    }
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        DirectedWeightedEdge[] edges = new DirectedWeightedEdge[m * 2];
        for (int i = 0; i < m; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            int w = in.nextInt();
            edges[i * 2] = o.new DirectedWeightedEdge(u, v, w);
            edges[i * 2 + 1] = o.new DirectedWeightedEdge(v, u, w);
        }
        BellmanFordDirectedSP sp = o.new BellmanFordDirectedSP(n + 1, edges, 1);
        for (int i = 1; i <= n; i++) {
            if (sp.hasPathTo(i)) System.out.println((int) sp.distTo(i));
            else System.out.println(-1);
        }
    }
}
