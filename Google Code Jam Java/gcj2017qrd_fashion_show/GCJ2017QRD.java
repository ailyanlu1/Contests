package gcj2017qrd_fashion_show;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

// https://code.google.com/codejam/contest/dashboard?c=3264486#s=p3&a=0
public class GCJ2017QRD {
    private static GCJ2017QRD o = new GCJ2017QRD();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken();
        }

        public String next(String delim) throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken(delim);
        }

        /*
        public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }
        */

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public byte nextByte(String delim) throws IOException {
            return Byte.parseByte(next(delim));
        }

        public char nextChar() throws IOException {
            return next().charAt(0);
        }

        public char nextChar(String delim) throws IOException {
            return next(delim).charAt(0);
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public double nextDouble(String delim) throws IOException {
            return Double.parseDouble(next(delim));
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }

        public float nextFloat(String delim) throws IOException {
            return Float.parseFloat(next(delim));
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public int nextInt(String delim) throws IOException {
            return Integer.parseInt(next(delim));
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public long nextLong(String delim) throws IOException {
            return Long.parseLong(next(delim));
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public short nextShort(String delim) throws IOException {
            return Short.parseShort(next(delim));
        }

        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }
    } // Reader class
    
    private static Reader in;
    private static PrintWriter out;
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "D-large-practice.in";
    private static final String OUTPUT_FILE_NAME = "D-large-practice.out";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    
    public static void main(String[] args) throws IOException {
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = o.new Reader(System.in);
        else in = o.new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
        int T = in.nextInt();
        for (int i = 1; i <= T; i++) {
            run(i);
            out.flush();
        }
        out.close();
    }
    
    private static int N;
    
    public static void run(int testCaseNum) throws IOException {
        N = in.nextInt();
        int M = in.nextInt();
        boolean[][] originalRooks = new boolean[N][N];
        boolean[][] originalBishops = new boolean[N][N];
        boolean[][] fullRooks = new boolean[N][N];
        boolean[][] fullBishops = new boolean[N][N];
        for (int m = 0; m < M; m++) {
            char type = in.next().charAt(0);
            int r = in.nextInt() - 1;
            int c = in.nextInt() - 1;
            boolean isRook = type == 'x' || type == 'o';
            boolean isBishop = type == '+' || type == 'o';
            if (isRook) {
                originalRooks[r][c] = true;
                fullRooks[r][c] = true;
            }
            if (isBishop) {
                originalBishops[r][c] = true;
                fullBishops[r][c] = true;
            }
        }
        fillRooks(fullRooks);
        fillBishops(fullBishops);
        int points = 0;
        int modifications = 0;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (fullRooks[r][c]) points++;
                if (fullBishops[r][c]) points++;
                if (fullRooks[r][c] != originalRooks[r][c] || fullBishops[r][c] != originalBishops[r][c]) modifications++;
            }
        }
        out.println("Case #" + testCaseNum + ": " + points + " " + modifications);
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (fullRooks[r][c] != originalRooks[r][c] || fullBishops[r][c] != originalBishops[r][c]) {
                    out.println(getChar(fullRooks[r][c], fullBishops[r][c]) + " " + (r + 1) + " " + (c + 1));
                }
            }
        }
    }

    private static char getChar(boolean isRook, boolean isBishop) {
        if (isRook) {
            if (isBishop) {
                return 'o'; // queen
            } else {
                return 'x'; // rook
            }
        } else {
            if (isBishop) {
                return '+'; // bishop
            } else {
                return '.'; // not used
            }
        }
    }

    private static void fillRooks(boolean[][] rooks) {
        boolean[] columnTaken = new boolean[N];
        boolean[] rowTaken = new boolean[N];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (rooks[r][c]) {
                    columnTaken[c] = true;
                    rowTaken[r] = true;
                }
            }
        }
        for (int r = 0; r < N; r++) {
            if (rowTaken[r]) continue;
            for (int c = 0; c < N; c++) {
                if (columnTaken[c]) continue;
                rooks[r][c] = true;
                rowTaken[r] = true;
                columnTaken[c] = true;
                break;
            }
        }
    }

    private static void fillBishops(boolean[][] bishops) {
        int diagCount = (N * 2) - 1;
        boolean[] majDiagTaken = new boolean[diagCount];
        boolean[] minDiagTaken = new boolean[diagCount];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (bishops[r][c]) {
                    int majDiag = majDiag(r, c);
                    int minDiag = minDiag(r, c);
                    majDiagTaken[majDiag] = true;
                    minDiagTaken[minDiag] = true;
                }
            }
        }
        for (int startR = 0, startC = N - 1; startR < N; startR++, startC--) {
            for (int[] startSpot : new int[][] {{startR, 0}, {N - 1, startC}}) {
                int r = startSpot[0];
                int c = startSpot[1];
                while (r >= 0 && c < N) {
                    int majDiag = majDiag(r, c);
                    int minDiag = minDiag(r, c);
                    if (!(majDiagTaken[majDiag] || minDiagTaken[minDiag])) {
                        majDiagTaken[majDiag] = true;
                        minDiagTaken[minDiag] = true;
                        bishops[r][c] = true;
                    }
                    r--;
                    c++;
                }
            }
        }
    }

    private static int majDiag(int r, int c) {
        return (r - ((N - 1) - c)) + N - 1;
    }

    private static int minDiag(int r, int c) {
        return (r - c) + N - 1;
    }
}
