package ccc13s4_who_is_taller;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class CCC13S4 {
    private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    private static StringTokenizer st;
    public static void main(String[] args) throws IOException {
        int n = nextInt();
        int m = nextInt();
        ArrayList<Integer>[] adj = new ArrayList[n+1];
        for (int v = 0; v < n+1; v++) {
            adj[v] = new ArrayList<Integer>();
        }
        for (int i = 0; i < m; i++) {
            adj[nextInt()].add(nextInt());
        }
        int p = nextInt();
        int q = nextInt();
        
        boolean[] marked = new boolean[adj.length];
        Queue<Integer> qu = new LinkedList<Integer>();
        marked[p] = true;
        qu.offer(p);
        while (!qu.isEmpty()) {
            int v = qu.poll();
            if (v == q) {
                System.out.println("yes");
                return;
            }
            for (int i = 0; i < adj[v].size(); i++) {
                int w = adj[v].get(i);
                if (!marked[w]) {
                    if (w == q) {
                        System.out.println("yes");
                        return;
                    }
                    marked[w] = true;
                    qu.offer(w);
                }
            }
        }
        marked = new boolean[adj.length];
        qu = new LinkedList<Integer>();
        marked[q] = true;
        qu.offer(q);
        while (!qu.isEmpty()) {
            int v = qu.poll();
            if (v == p) {
                System.out.println("no");
                return;
            }
            for (int i = 0; i < adj[v].size(); i++) {
                int w = adj[v].get(i);
                if (!marked[w]) {
                    if (w == p) {
                        System.out.println("no");
                        return;
                    }
                    marked[w] = true;
                    qu.offer(w);
                }
            }
        }
        System.out.println("unknown");
    } // main method
    
    private static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine().trim());
        } // while
        return st.nextToken();
    } // next method

    private static long nextLong() throws IOException {
        return Long.parseLong(next());
    } // nextLong method

    private static int nextInt() throws IOException {
        return Integer.parseInt(next());
    } // nextInt method

    private static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    } // nextDouble method
    
    private static String nextLine() throws IOException {
        return in.readLine().trim();
    } // nextLine method
} // CCC13S4 class
