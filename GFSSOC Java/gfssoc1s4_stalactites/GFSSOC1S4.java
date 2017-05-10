package gfssoc1s4_stalactites;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class GFSSOC1S4 {
	private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	private static StringTokenizer st;

	public static String next() throws IOException {
		while (st == null || !st.hasMoreTokens()) {
			st = new StringTokenizer(in.readLine().trim());
		} // while
		return st.nextToken();
	} // next method
	
	public static long nextLong() throws IOException {
		return Long.parseLong(next());
	} // nextLong method
	
	public static int nextInt() throws IOException {
		return Integer.parseInt(next());
	} // nextInt method
	
	public static double nextDouble() throws IOException {
		return Double.parseDouble(next());
	} // nextDouble method
	
	public static String nextLine() throws IOException {
		return in.readLine().trim();
	} // nextLine method
	
	private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
	private static long[][][] array;
	private static int N;
	
	public static void main(String[] args) throws IOException {
		N = nextInt();
		array = new long[N + 1][N + 1][N + 1];
		int Q = nextInt();
		long sum = 0L;
		for (int i = 0; i < Q; i++) {
			char c = next().charAt(0);
			if (c == 'C') {
				int x = nextInt();
				int y = nextInt();
				int z = nextInt();
				long value = nextLong() - rsq(x, y, z, x, y, z);
				update(x, y, z, value);
			} else /*if (c == 'S')*/ {
				sum += rsq(nextInt(), nextInt(), nextInt(), nextInt(), nextInt(), nextInt());
			}
		}
		out.println(sum);
		out.close();
	}
	
    /**
     * Range Sum Query
     * <p>
     * Time-Complexity:    O(log(n)^3)
     *
     * @param  indX x index
     * @param  indY y index
     * @param  indZ z index
     * @return sum
     */
    public static long rsq(int indX, int indY, int indZ) {
        long sum = 0L;
        for (int x = indX; x > 0; x -= (x & -x)) {
        	for (int y = indY; y > 0; y -= (y & -y)) {
        		for (int z = indZ; z > 0; z -= (z & -z)) {
        			sum += array[x][y][z];
        		}
        	}
        }
        return sum;
    }

    /**
     * Range Sum Query
     * <p>
     * Time-Complexity:    O(log(n)^3)
     *
     * @param  x1 top index
     * @param  y1 left index
     * @param  z1 from index
     * @param  x2 bottom index
     * @param  y2 right index
     * @param  z2 back index
     * @return sum
     */
    public static long rsq(int x1, int y1, int z1, int x2, int y2, int z2) {
    	x1--;
    	y1--;
    	z1--;
    	return rsq(x2, y2, z2) 
    			- rsq(x1, y2, z2) - rsq(x2, y1, z2) - rsq(x2, y2, z1)
    			+ rsq(x1, y1, z2) + rsq(x1, y2, z1) + rsq(x2, y1, z1)
    			- rsq(x1, y1, z1);
    }

    /**
     * Update the array at [indX][indY][indZ] and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n)^3)
     *
     * @param  indX   x index
     * @param  indY   y index
     * @param  indZ   z index
     * @param  value value
     */
    public static void update(int indX, int indY, int indZ, long value) {
    	for (int x = indX; x <= N; x += (x & -x)) {
    		for (int y = indY; y <= N; y += (y & -y)) {
    			for (int z = indZ; z <= N; z += (z & -z)) {
    				array[x][y][z] += value;
    			}
    		}
    	}
    }
}
