package dmpg17s4_artillery_battery;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.StringTokenizer;

public class DMPG17S4 {
    private static DMPG17S4 o = new DMPG17S4();
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
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static class State {
        int r, c, k, m;
        public State(int r, int c, int k, int m) {
            this.r = r;
            this.c = c;
            this.k = k;
            this.m = m;
        }
    }
    
    private static int[][] grid = new int[10][9];
    private static int E = 0;
    private static int maxK = 0;
    private static int minM = 0;
    private static int[][][] vis = new int[10][9][1 << 15];
    private static Queue<State> q = new ArrayDeque<State>();
    
    public static void main(String[] args) throws IOException {
        for (int i = 0; i < 10; i++) {
            String s = in.nextLine();
            for (int j = 0; j < 9; j++) {
                if (s.charAt(j) == 'C') {
                    q.offer(new State(i, j, 0, 0));
                } else if (s.charAt(j) == 'E') {
                    grid[i][j] = 1 << E;
                    E++;
                }
            }
        }
        int INF = 1 << 30;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < (1 << 15); k++) {
                    vis[i][j][k] = INF;
                }
            }
        }
        while (!q.isEmpty()) {
            State s = q.poll();
            int r = s.r;
            int c = s.c;
            int k = s.k;
            int m = s.m;
            
            if (vis[r][c][k] <= m) continue;

            vis[r][c][k] = m;

            int kills = Integer.bitCount(k);
            if (kills > maxK) {
                maxK = kills;
                minM = m;
            } else if (kills == maxK) {
                minM = Math.min(minM, m);
            }

            if (kills == E - 1) break;

            for (int i = r - 1; i >= 0; i--) {
                if (grid[i][c] != 0 && (grid[i][c] & k) == 0) {
                    for (int j = i - 1; j >= 0; j--) {
                        if (grid[j][c] != 0 && (grid[j][c] & k) == 0) {
                            q.offer(new State(j, c, k | grid[j][c], m + 1));
                            break;
                        }
                    }
                    break;
                }
                if (vis[i][c][k] > m + 1) {
                    q.offer(new State(i, c, k, m + 1));
                }
            }
            for (int i = r + 1; i < 10; i++) {
                if (grid[i][c] != 0 && (grid[i][c] & k) == 0) {
                    for (int j = i + 1; j < 10; j++) {
                        if (grid[j][c] != 0 && (grid[j][c] & k) == 0) {
                            q.offer(new State(j, c, k | grid[j][c], m + 1));
                            break;
                        }
                    }
                    break;
                }
                if (vis[i][c][k] > m + 1) {
                    q.offer(new State(i, c, k, m + 1));
                }
            }
            for (int i = c - 1; i >= 0; i--) {
                if (grid[r][i] != 0 && (grid[r][i] & k) == 0) {
                    for (int j = i - 1; j >= 0; j--) {
                        if (grid[r][j] != 0 && (grid[r][j] & k) == 0) {
                            q.offer(new State(r, j, k | grid[r][j], m + 1));
                            break;
                        }
                    }
                    break;
                }
                if (vis[r][i][k] > m + 1) {
                    q.offer(new State(r, i, k, m + 1));
                }
            }
            for (int i = c + 1; i < 9; i++) {
                if (grid[r][i] != 0 && (grid[r][i] & k) == 0) {
                    for (int j = i + 1; j < 9; j++) {
                        if (grid[r][j] != 0 && (grid[r][j] & k) == 0) {
                            q.offer(new State(r, j, k | grid[r][j], m + 1));
                            break;
                        }
                    }
                    break;
                }
                if (vis[r][i][k] > m + 1) {
                    q.offer(new State(r, i, k, m + 1));
                }
            }
        }
        out.println(maxK + " " + minM);
        out.close();
    }
}
