package cco13p4_a_romantic_movie_outing;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCO13P4 {
    private static CCO13P4 o = new CCO13P4();
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
    
    public class FenwickTree2D {

        int[][] array;

        public FenwickTree2D(int sizeX, int sizeY) {
            array = new int[sizeX + 1][sizeY + 1];
        }

        /**
         * Range Sum Query
         * <p>
         * Time-Complexity:    O(log(n)^2)
         *
         * @param  indX x index
         * @param  indY y index
         * @return sum
         */
        public int rsq(int indX, int indY) {
            int sum = 0;
            for (int x = indX; x > 0; x -= (x & -x)) {
                for (int y = indY; y > 0; y -= (y & -y)) {
                    sum += array[x][y];
                }
            }
            return sum;
        }

        /**
         * Range Sum Query
         * <p>
         * Time-Complexity:    O(log(n)^2)
         *
         * @param  x1 top index
         * @param  y1 left index
         * @param  x2 bottom index
         * @param  y2 right index
         * @return sum
         */
        public int rsq(int x1, int y1, int x2, int y2) {
            return rsq(x2, y2) + rsq(x1 - 1, y1 - 1) - rsq(x1 - 1, y2) - rsq(x2, y1 - 1);
        }

        /**
         * Update the array at [indX][indY] and all the affected regions above ind.
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n)^2)
         *
         * @param  indX   x index
         * @param  indY   y index
         * @param  value value
         */
        public void update(int indX, int indY, int value) {
            for (int x = indX; x < array.length; x += (x & -x)) {
                for (int y = indY; y < array[x].length; y += (y & -y)) {
                    array[x][y] += value;
                }
            }
        }

        public int sizeX() {
            return array.length - 1;
        }
        
        public int sizeY() {
            return array[0].length - 1;
        }
    }
    
    public static class Seat {
        public int r;
        public int c;
        
        public Seat(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static int L, T, B;
    
    
    public static void main(String[] args) throws IOException {
        L = in.nextInt();
        B = 1500;
        T = in.nextInt();
        FenwickTree2D ft = o.new FenwickTree2D(2 * B + 1, 2 * B + 1);
        boolean[][] taken = new boolean[B + 2][1001];
        for (int i = 0; i < T; i++) {
            char e = in.next().charAt(0);
            int r = in.nextInt();
            int c = in.nextInt();
            Seat s = toSeat(new Seat(r, c));
            if (e == 'E') {
                if (r <= B) {
                    ft.update(s.r, s.c, 1);
                    taken[r][c] = true;
                }
            } else if (e == 'L') {
                if (r <= B) {
                    ft.update(s.r, s.c, -1);
                    taken[r][c] = false;
                }
            } else {
                Seat s2 = toSeat(new Seat(r, c + 1));
                if (taken[r][c] || taken[r][c + 1]) out.println("No");
                else out.println(ft.rsq(s.r, s.c) + ft.rsq(s2.r, s2.c));
            }
        }
        int min = Integer.MAX_VALUE;
        int min2 = Integer.MAX_VALUE;
        for (int r = L + 1; r <= L + 501; r++) {
            for (int c = 1; c <= 1000; c++) {
                Seat s = toSeat(new Seat(r, c));
                if (taken[r][c]) continue;
                int res = ft.rsq(s.r, s.c);
                if (res <= min) {
                    min2 = min;
                    min = res;
                } else if (res < min2) {
                    min2 = res;
                }
            }
        }
        out.println(min + min2);
        out.close();
    }
    
    private static Seat toSeat(Seat s) {
        return new Seat(s.r - s.c + B, s.r + s.c);
    }
}
