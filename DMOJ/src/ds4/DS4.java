package ds4;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class DS4 {

	private static DS4 o = new DS4();
	
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
	
	public class AVLTreeSet {
		// root of the tree
		private Node root;
		
		public AVLTreeSet() {
			this.root = null;
		}
		
		// object representing the nodes of the tree
		private class Node {
			long value, height, size;
			Node left, right;

			Node(long value) {
				this.value = value;
				this.height = 1L;
				this.size = 1L;
				this.left = null;
				this.right = null;
			}

		}

		// methods to reset and get the height of a node
		private void reset(Node n) {
			n.height = Math.max(getHeight(n.left) + 1L, getHeight(n.right) + 1L);
			n.size = getSize(n.left) + 1L + getSize(n.right);
		}

		private long getHeight(Node n) {
			return n == null ? 0L : n.height;
		}
		
	    private long getSize(Node n) {
	    	return (n == null) ? 0L : n.size;
	    }

		public String toString() {
			return toString(root);
		}

		private String toString(Node n) {
		    if (n == null) return "";
		    return toString(n.left).trim() + " " + n.value + " " + toString(n.right).trim();
		}

		public boolean contains(long v) {
			return contains(root, v);
		}

		// auxiliary method for contains
		private boolean contains(Node n, long v) {
			if (n == null)
				return false;
			else if (v < n.value)
				return contains(n.left, v);
			else if (v > n.value)
				return contains(n.right, v);
			return true;
		}

		public void remove(long v) {
			this.root = remove(root, v);
		}

		// auxiliary method for move
		private Node remove(Node n, long v) {
			if (n == null) {
				return n;
			}
			if (v < n.value) {
		        n.left = remove(n.left, v);
		    }
			if (v > n.value) {
		        n.right = remove(n.right, v);
		    }
			if (v == n.value) {
				if (n.left == null && n.right == null) {
					return null;
				} else if (n.left == null) {
					n = n.right;
				} else if (n.right == null) {
					n = n.left;
				} else {
					Node replace = minV(n.right);
					n.value = replace.value;
					n.right = remove(n.right, replace.value);
				}
			}
			return balance(n);
		}

		private Node minV(Node n) {
			while (n.left != null)
				n = n.left;
			return n;
		}

		public void add(long v) {
			this.root = add(root, v);
		}

		// auxiliary method for add
		private Node add(Node n, long v) {
		    if (n == null) {
		        return new Node(v);
		    } else if (v >= n.value) {
		        n.right = add(n.right, v);
		    }

		    if (v < n.value) {
		        n.left = add(n.left, v);
		    }
			return balance(n);
		}
		
		private long balanceFactor(Node n) {
		    if (n == null) {
		        return 0;
		    }

		    return getHeight(n.left) - getHeight(n.right);
		}

		// auxiliary function to rebalance the tree
		private Node balance(Node n) {
			reset(n);
			// Left Left Case
		    if (balanceFactor(n) > 1 && balanceFactor(n.left) >= 0) {
		        return rotateRight(n);
		    }

		    // Left Right Case
		    if (balanceFactor(n) > 1 && balanceFactor(n.left) < 0) {
		        n.left =  rotateLeft(n.left);
		        return rotateRight(n);
		    }

		    // Right Right Case
		    if (balanceFactor(n) < -1 && balanceFactor(n.right) <= 0) {
		        return rotateLeft(n);
		    }

		    // Right Left Case
		    if (balanceFactor(n) < -1 && balanceFactor(n.right) > 0) {
		        n.right = rotateRight(n.right);
		        return rotateLeft(n);
		    }
			return n;
		}

		// rotate left
		private Node rotateLeft(Node x) {
			Node y = x.right;
			Node z = y.left;
			y.left = x;
			x.right = z;
			reset(x);
			reset(y);
			return y;
		}

		// rotate right
		private Node rotateRight(Node y) {
			Node x = y.left;
			Node z = x.right;
			x.right = y;
			y.left = z;
			reset(y);
			reset(x);
			return x;
		}
		
		public long select(long v) {
			return select(root, v);
		}
		
		private long select(Node n, long v) {
		    if (n == null) {
		        return 0L;
		    }

		    long rank = getSize(n.left) + 1;

		    if (rank == v) {
		        return n.value;
		    } else if (rank > v) {
		        return select(n.left, v);
		    } else {
		        return select(n.right, v - rank);
		    }
		}
	    
	    public long rank(long v) {
	    	return rank(root, v);
	    }
	    
	    private long rank(Node n, long v) {

	        if (n == null) {
	            return -1L;
	        }

	        if (n.value == v) {
	            long temp = rank(n.left, v);
	            if (temp == -1) {
	                return getSize(n.left) + 1;
	            } else {
	                return temp;
	            }
	        } else if (v < n.value) {
	            return rank(n.left, v);
	        } else {
	            long temp = rank(n.right, v);
	            if (temp == -1) {
	                return temp;
	            } else {
	                return getSize(n.left) + 1 + temp;
	            }

	        }
	    }
	}
	
	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader(System.in);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int n = in.nextInt();
		int m = in.nextInt();
		AVLTreeSet tree = o.new AVLTreeSet();
		for (int i = 0; i < n; i++) {
			long x = in.nextLong();
			tree.add(x);
		}
		long lastAns = 0;
		for (int i = 0; i < m; i++) {
			String op = in.next();
			long x = in.nextLong() ^ lastAns;
			if (op.equals("I")) {
				tree.add(x);
			} else if (op.equals("R")) {
				tree.remove(x);
			} else if (op.equals("S")) {
				lastAns = tree.select(x);
				out.println(lastAns);
			} else /*if (op.equals("L"))*/{
				lastAns = tree.rank(x);
				out.println(lastAns);
			}
		}
		out.println(tree.toString());
		out.close();
	}
}
