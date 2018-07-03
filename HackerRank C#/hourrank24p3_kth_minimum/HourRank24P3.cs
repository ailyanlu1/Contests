using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace HourRank24P3 {
    public class Program {
        public class Reader {
            private TextReader reader;
            private string[] tokens;
            private int currentToken;

            public Reader(Stream s) {
                reader = new StreamReader(s);
                tokens = new string[0];
                currentToken = 0;
            }

            public Reader(string file) {
                reader = new StreamReader(file);
                tokens = new string[0];
                currentToken = 0;
            }

            public string ReadLine() { return reader.ReadLine();  }

            public string ReadToken() {
                while (currentToken == tokens.Length) {
                    tokens = ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries);
                    currentToken = 0;
                }
                return tokens[currentToken++];
            }

            public char ReadChar() { return ReadToken()[0]; }
            public int ReadInt() { return int.Parse(ReadToken()); }
            public long ReadLong() { return long.Parse(ReadToken()); }
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

        private static int STACK_MEMORY_LIMIT_MB = 10; // TODO CHANGE MEMORY LIMIT FOR STACK

        public static void Main(string[] args) {
            Thread T = new Thread(new ThreadStart(start), STACK_MEMORY_LIMIT_MB * 1000000);
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

        static int N, M, X;
        static long K;
        static int[] A, B;
        static long[] BIT;
        static int MAXV = 200005;

        static void update(int i, long v) {
            for (; i < BIT.Length; i += i & -i) BIT[i] += v;
        }

        static long rsq(int i) {
            long sum = 0;
            for (; i > 0; i -= i & -i) sum += BIT[i];
            return sum;
        }

        static long rsq(int a, int b) {
            return rsq(b) - rsq(a - 1);
        }

        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            X = In.ReadInt();
            K = In.ReadLong();
            A = new int[N];
            B = new int[M];
            for (int i = 0; i < N; i++) A[i] = In.ReadInt();
            for (int i = 0; i < M; i++) B[i] = In.ReadInt();
            long lo = -0x3f3f3f3f3f3f3f3f, hi = 0x3f3f3f3f3f3f3f3f, mid;
            while (lo < hi) {
                mid = lo + (hi - lo) / 2;
                long res = 0;
                BIT = new long[MAXV * 2];
                int j = M;
                for (int i = N - 1; i >= 0; i--) {
                    while (j - 1 >= i + X) update(B[--j] + MAXV, 1);
                    if (A[i] > 0) {
                        long bound = mid / A[i];
                        while (A[i] * bound > mid) bound--;
                        while (A[i] * (bound + 1) <= mid) bound++;
                        bound = Math.Min(bound, MAXV - 1);
                        if (bound >= -MAXV) res += rsq((int) bound + MAXV);
                    } else if (A[i] < 0) {
                        long bound = mid / A[i];
                        while (A[i] * bound > mid) bound++;
                        while (A[i] * (bound - 1) <= mid) bound--;
                        bound = Math.Max(bound, 1 - MAXV);
                        if (bound < MAXV) res += rsq((int) bound + MAXV, BIT.Length - 1);
                    } else if (mid >= 0) {
                        res += rsq(BIT.Length - 1);
                    }
                }
                if (res >= K) hi = mid;
                else lo = mid + 1;
            }
            Out.WriteLine(lo);
        }
    }
}
