// http://codeforces.com/contest/52/problem/C
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace TestingRound1C {
    public class Program {
        public class Reader {
            private TextReader reader;
            private Queue<string> tokens;

            public Reader(Stream s) {
                reader = new StreamReader(s);
                tokens = new Queue<string>();
            }

            public Reader(string file) {
                reader = new StreamReader(file);
                tokens = new Queue<string>();
            }

            public string ReadLine() { return reader.ReadLine(); }

            public string ReadToken() {
                while (tokens.Count() == 0) tokens = new Queue<string>(ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries));
                return tokens.Dequeue();
            }

            public char ReadChar() { return ReadToken()[0]; }
            public sbyte ReadByte() { return sbyte.Parse(ReadToken()); }
            public short ReadShort() { return short.Parse(ReadToken()); }
            public int ReadInt() { return int.Parse(ReadToken()); }
            public long ReadLong() { return long.Parse(ReadToken()); }
            public float ReadFloat() { return float.Parse(ReadToken(), CultureInfo.InvariantCulture); }
            public double ReadDouble() { return double.Parse(ReadToken(), CultureInfo.InvariantCulture); }
            public decimal ReadDecimal() { return decimal.Parse(ReadToken(), CultureInfo.InvariantCulture); }
            public void Close() { reader.Close(); }
        }

        private static Reader In;
        private static TextWriter Out;

        private static int NUM_OF_TEST_CASES = 1; // TODO CHANGE NUMBER OF TEST CASES

        // TODO CHANGE FILE NAMES
        private static string INPUT_FILE_NAME = "input.txt";
        private static string OUTPUT_FILE_NAME = "output.txt";

        private static bool stdIn = true;
        private static bool stdOut = true;
        private static bool crash = true;
        private static bool flush = false;

        private static int MEMORY_LIMIT_MB = 100;

        public static void Main(string[] args) {
            Thread T = new Thread(new ThreadStart(start), MEMORY_LIMIT_MB * 1000000);
            T.Start();
        }

        public static void start() {
            if (stdIn) In = new Reader(Console.OpenStandardInput());
            else In = new Reader(INPUT_FILE_NAME);
            if (stdOut) Out = new StreamWriter(Console.OpenStandardOutput());
            else Out = new StreamWriter(OUTPUT_FILE_NAME);
            for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
                try {
                    run(i);
                } catch (Exception e) {
                    Out.WriteLine("Exception thrown on test case " + i);
                    Out.WriteLine(e.StackTrace);
                    Out.Flush();
                    if (crash) throw new Exception();
                }
                if (flush) Out.Flush();
            }
            In.Close();
            Out.Close();
        }

        static int N, M, H;
        static int[] A, T, L;

        static void apply(int i, int v) {
            T[i] += v;
            if (i < N) L[i] += v;
        }

        static void pushup(int i) {
            while (i > 1) {
                i >>= 1;
                T[i] = Math.Min(T[i << 1], T[i << 1 | 1]) + L[i];
            }
        }

        static void propagate(int i) {
            for (int h = H; h > 0; h--) {
                int ii = i >> h;
                if (L[ii] != 0) {
                    apply(ii << 1, L[ii]);
                    apply(ii << 1 | 1, L[ii]);
                    L[ii] = 0;
                }
            }
        }

        static void build() {
            T = new int[2 * N];
            L = new int[N];
            H = 0;
            for (int i = 1; i <= N; H++) i <<= 1;
            for (int i = 0; i < N; i++) {
                T[N + i] = A[i + 1];
                L[i] = 0;
            }
            for (int i = N - 1; i > 0; i--) T[i] = Math.Min(T[i << 1], T[i << 1 | 1]);
        }

        static void update(int l, int r, int v) {
            l += (N - 1);
            r += (N - 1);
            int l0 = l, r0 = r;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) != 0) apply(l++, v);
                if ((r & 1) == 0) apply(r--, v);
            }
            pushup(l0);
            pushup(r0);
        }

        static int query(int l, int r) {
            l += (N - 1);
            r += (N - 1);
            propagate(l);
            propagate(r);
            int q = int.MaxValue;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) != 0) q = Math.Min(q, T[l++]);
                if ((r & 1) == 0) q = Math.Min(T[r--], q);
            }
            return q;
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            A = new int[N + 1];
            for (int i = 1; i <= N; i++) A[i] = In.ReadInt();
            build();
            M = In.ReadInt();
            for (int i = 0; i < M; i++) {
                String[] line = In.ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries);
                if (line.Length == 2) {
                    int l = int.Parse(line[0]) + 1, r = int.Parse(line[1]) + 1;
                    if (l <= r) Out.WriteLine(query(l, r));
                    else Out.WriteLine(Math.Min(query(1, r), query(l, N)));
                } else {
                    int l = int.Parse(line[0]) + 1, r = int.Parse(line[1]) + 1, v = int.Parse(line[2]);
                    if (l <= r) update(l, r, v);
                    else {
                        update(1, r, v);
                        update(l, N, v);
                    }
                }
            }
        }
    }
}
