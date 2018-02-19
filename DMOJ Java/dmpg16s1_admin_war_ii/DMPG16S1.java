import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class DMPG16S1 {
    private static DMPG16S1 o = new DMPG16S1();
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
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        Long[] f = new Long[N];
        Long[] x = new Long[N];
        for (int i = 0; i < N; i++) {
            f[i] = in.nextLong();
        }
        for (int i = 0; i < N; i++) {
            x[i] = in.nextLong();
        }
        Arrays.sort(f);
        Arrays.sort(x);
        int countF = 0;
        int iF = N - 1;
        int iX = N - 1;
        while (iX >= 0) {
            if (f[iF] > x[iX]) {
                countF++;
                iF--;
                iX--;
            } else {
                iX--;
            }
        }
        int countX = 0;
        iF = N - 1;
        iX = N - 1;
        while (iF >= 0) {
            if (x[iX] > f[iF]) {
                countX++;
                iX--;
                iF--;
            } else {
                iF--;
            }
        }
        out.println(countF);
        out.println(countX);
        out.close();
    }
}
