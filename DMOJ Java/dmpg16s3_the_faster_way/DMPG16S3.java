package dmpg16s3_the_faster_way;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.StringTokenizer;

public class DMPG16S3 {
    private static DMPG16S3 o = new DMPG16S3();
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
    
    public static void main(String[] args) throws IOException {
        Reader in = o.new Reader(System.in);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int N = in.nextInt();
        int R = in.nextInt();
        int M = in.nextInt();
        HashSet<Integer> stops = new HashSet<Integer>();
        for (int i = 0; i < R; i++) {
            stops.add(in.nextInt());
        }
        int rocket = 0;
        int regular = 0;
        for (int i = 0; i < M; i++) {
            if (stops.contains(in.nextInt())) rocket++;
            else regular++;
        }
        if (rocket > regular) {
            regular = M/2;
            rocket = M - regular;
        }
        System.out.println((rocket * (rocket + 1) / 2) + (regular * (regular + 1) / 2));
        out.close();
    }
}
