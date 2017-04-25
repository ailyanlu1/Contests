package cco10p3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

public class CCO10P3_with_FenwickTree { // 4/12 TLE
	private static CCO10P3_with_FenwickTree o = new CCO10P3_with_FenwickTree();
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
	
	public class FenwickTree {

	    int[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

	    public FenwickTree(int size) {
	        array = new int[size + 1];
	    }

	    /**
	     * Range Sum query from 1 to ind
	     * ind is 1-indexed
	     * <p>
	     * Time-Complexity:    O(log(n))
	     *
	     * @param  ind index
	     * @return sum
	     */
	    public int rsq(int ind) {
	        int sum = 0;
	        while (ind > 0) {
	            sum += array[ind];
	            //Extracting the portion up to the first significant one of the binary representation of 'ind' and decrementing ind by that number
	            ind -= ind & (-ind);
	        }

	        return sum;
	    }

	    /**
	     * Range Sum Query from a to b.
	     * Search for the sum from array index from a to b
	     * a and b are 1-indexed
	     * <p>
	     * Time-Complexity:    O(log(n))
	     *
	     * @param  a left index
	     * @param  b right index
	     * @return sum
	     */
	    public int rsq(int a, int b) {
	        return rsq(b) - rsq(a - 1);
	    }

	    /**
	     * Update the array at ind and all the affected regions above ind.
	     * ind is 1-indexed
	     * <p>
	     * Time-Complexity:    O(log(n))
	     *
	     * @param  ind   index
	     * @param  value value
	     */
	    public void update(int ind, int value) {
	        while (ind < array.length) {
	            array[ind] += value;
	            //Extracting the portion up to the first significant one of the binary representation of 'ind' and incrementing ind by that number
	            ind += ind & (-ind);
	        }
	    }

	    public int size() {
	        return array.length - 1;
	    }
	}

	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		HashMap<Integer, Integer> idToRating = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> ratingToId = new HashMap<Integer, Integer>();
		int N = in.nextInt();
		int num = 0;
		FenwickTree ft = o.new FenwickTree(10000002);
		for (int i = 0; i < N; i++) {
			String c = in.next();
			if (c.equals("N")) {
				int X = in.nextInt();
				int R = in.nextInt();
				idToRating.put(X, R);
				ratingToId.put(R, X);
				ft.update(R, 1);
				num++;
			} else if (c.equals("M")) {
				int X = in.nextInt();
				int R = in.nextInt();
				ft.update(idToRating.get(X), -1);
				idToRating.put(X, R);
				ratingToId.put(R, X);
				ft.update(R, 1);
			} else /*if (c.equals("Q"))*/ {
				int K = in.nextInt();
				int lo = 1;
				int hi = ft.size();
				while (lo <= hi) {
					int mid = lo + (hi - lo) / 2;
					if (ft.rsq(mid) > num - K) {
						hi = mid - 1;
					} else {
						lo = mid + 1;
					}
				}
				out.println(ratingToId.get(lo));
			}
		}
		out.close();
	}
}
