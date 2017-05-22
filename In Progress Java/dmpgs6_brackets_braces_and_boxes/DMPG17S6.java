package dmpgs6_brackets_braces_and_boxes;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class DMPG17S6 { // 30/100 WA
	private static DMPG17S6 o = new DMPG17S6();
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
	
	public class Pair<Item, Item2> {
		private Item first;
		private Item2 second;
		
		public Pair(Item first, Item2 second) {
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
	        if (!(o instanceof Pair)) {
	            return false;
	        }
	        Pair p = (Pair) o;
			return p.first.equals(first) && p.second.equals(second);
		}
	}
	
	private static Reader in = o.new Reader(System.in);
	
	public static void main(String[] args) throws IOException {
		int N = in.nextInt();
		int K = in.nextInt();
		char[] arr = in.nextLine().toCharArray();
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < N; i++) {
			if (arr[i] == '{' || arr[i] == '(' || arr[i] == '[') {
				stack.push(arr[i]);
			} else {
				if (stack.peek() == '{' && arr[i] == '}') {
					stack.pop();
				} else if (stack.peek() == '[' && arr[i] == ']') {
					stack.pop();
				} else if (stack.peek() == '(' && arr[i] == ')') {
					stack.pop();
				} else {
					if (K == 0) {
						System.out.println("impossible");
						return;
					} else if (stack.peek() == '{') {
						arr[i] = '}';
					} else if (stack.peek() == '[') {
						arr[i] = ']';
					} else {
						arr[i] = ')';
					}
					stack.pop();
					K--;
				}
			}
		}
		if (K % 2 != 0 || !stack.isEmpty()) {
			System.out.println("impossible");
			return;
		}
		int x = 0;
		Stack<Pair<Character, Integer>> check = new Stack<Pair<Character, Integer>>();
		while (K > 0) {
			if (arr[x] == '{' || arr[x] == '(' || arr[x] == '[') {
				check.push(o.new Pair<Character, Integer>(arr[x], x));
			} else if (check.peek().getFirst() == '{' && arr[x] == '}') {
				K-=2;
				Pair<Character, Integer> p = check.pop();
				arr[p.getSecond()] = '[';
				arr[x] = ']';
			} else if (check.peek().getFirst() == '[' && arr[x] == ']') {
				K-=2;
				Pair<Character, Integer> p = check.pop();
				arr[p.getSecond()] = '(';
				arr[x] = ')';
			} else if (check.peek().getFirst() == '(' && arr[x] == ')') {
				K-=2;
				Pair<Character, Integer> p = check.pop();
				arr[p.getSecond()] = '{';
				arr[x] = '}';
			}
			x++;
		}
		for (int i = 0; i < N; i++) {
			System.out.print(arr[i]);
		}
		System.out.println();
	}
}
