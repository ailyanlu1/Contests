import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class IOI01P1 {
    private static IOI01P1 o = new IOI01P1();
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
            int y = indY;
            while (indX > 0) {
               indY = y;
               while (indY > 0) {
                   sum += array[indX][indY];
                   indY -= (indY & -indY);
               }
               indX -= (indX & -indX);
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
            int y = indY;
            while (indX < array.length) {
                indY = y;
                while (indY < array[indX].length) {
                    array[indX][indY] += value;
                    indY += (indY & -indY);
                }
                indX += (indX & -indX);
            }
        }

        public int sizeX() {
            return array.length - 1;
        }
        
        public int sizeY() {
            return array[0].length - 1;
        }
    }

    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int c;
        FenwickTree2D ft = null;
        while((c = in.nextInt()) != 3) {
            if (c == 0) {
                int n = in.nextInt();
                ft = o.new FenwickTree2D(n, n);
            } else if (c == 1) {
                ft.update(in.nextInt() + 1, in.nextInt() + 1, in.nextInt());
            } else /*if (n == 2)*/ {
                out.println(ft.rsq(in.nextInt() + 1, in.nextInt() + 1, in.nextInt() + 1, in.nextInt() + 1));
            }
        }
        out.close();
    }
}
