package cco15p4_cars_on_ice;

import java.io.DataInputStream;
import java.io.IOException;

public class CCO15P4 { // 80/100 points (TLE)
	
	private static CCO15P4 o = new CCO15P4();
	
	public class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
 
        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
 
        public String nextLine() throws IOException
        {
            byte[] buf = new byte[2000]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1)
            {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }
 
        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do
            {
                ret = ret * 10 + c - '0';
            }  while ((c = read()) >= '0' && c <= '9');
 
            if (neg)
                return -ret;
            return ret;
        }
 
        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }
 
        public double nextDouble() throws IOException
        {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
 
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
 
            if (c == '.')
            {
                while ((c = read()) >= '0' && c <= '9')
                {
                    ret += (c - '0') / (div *= 10);
                }
            }
 
            if (neg)
                return -ret;
            return ret;
        }
 
        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }
 
        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }
 
        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
    }
	
	public static int N;
	public static int M;
	public static char[][] grid;

	public static void main(String[] args) throws IOException {
		Reader in = o.new Reader();
		N = in.nextInt();
		M = in.nextInt();
		grid = new char[N][M];
		for (int i = 0; i < N; i++) {
			grid[i] = in.nextLine().toCharArray();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (grid[i][j] != '.') {
					check(i, j);
				}
			}
		}
	}
	
	private static void check(int i, int j) {
		try {
			if (grid[i][j] == 'N') {
				for (int k = i - 1; k >= 0; k--) {
					if (grid[k][j] != '.') {
						check(k, j);
					}
				}
			} else if (grid[i][j] == 'S') {
				for (int k = i + 1; k < N; k++) {
					if (grid[k][j] != '.') {
						check(k, j);
					}
				}
			} else if (grid[i][j] == 'E') {
				for (int k = j + 1; k < M; k++) {
					if (grid[i][k] != '.') {
						check(i, k);
					}
				}
			} else {
				for (int k = j - 1; k >= 0; k--) {
					if (grid[i][k] != '.') {
						check(i, k);
					}
				}
			}
			grid[i][j] = '.';
			System.out.println("(" + i + "," + j + ")");
		} catch (StackOverflowError e) {
			return;
		}
	}
}
