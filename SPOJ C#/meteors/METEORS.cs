// http://www.spoj.com/problems/METEORS/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace METEORS {
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

        private static int STACK_MEMORY_LIMIT_MB = 500; // TODO CHANGE MEMORY LIMIT FOR STACK

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

        public class FenwickTreeRangePoint {
            private int size;
            private long[] array;
            public FenwickTreeRangePoint(int size) {
                this.size = size;
                array = new long[size + 1];
                for (int i = 0; i <= size; i++) {
                    array[i] = 0;
                }
            }

            public long getValue(int ind) {
                long sum = 0;
                for (int x = ind; x > 0; x -= (x & -x)) {
                    sum += array[x];
                }
                return sum;
            }

            public void update(int ind, long value) {
                for (int x = ind; x <= size; x += (x & -x)) {
                    array[x] += value;
                }
            }

            public void update(int a, int b, long value) {
                update(a, value);
                update(b + 1, -value);
            }
        };

        static int N, M, K;
        static int[] ans;
        static List<int>[] stations;
        static long[] target;
        static Tuple<int, int, long>[] A;
        static FenwickTreeRangePoint ft;

        static void solve(ref List<Tuple<int, long>> ind, int cL, int cR) {
            if (cL == cR) {
                foreach (Tuple<int, long> T in ind) ans[T.Item1] = cL;
                return;
            }
            int m = cL + (cR - cL) / 2;
            List<Tuple<int, long>> left = new List<Tuple<int, long>>(), right = new List<Tuple<int, long>>();
            for (int i = cL; i <= m; i++) {
                if (A[i].Item1 <= A[i].Item2) ft.update(A[i].Item1, A[i].Item2, A[i].Item3);
                else {
                    ft.update(A[i].Item1, M, A[i].Item3);
                    ft.update(1, A[i].Item2, A[i].Item3);
                }
            }
            foreach (Tuple<int, long> T in ind) {
                long curSum = T.Item2;
                foreach (int i in stations[T.Item1]) {
                    curSum += ft.getValue(i);
                    if (curSum >= target[T.Item1]) {
                        left.Add(new Tuple<int, long>(T.Item1, T.Item2));
                        break;
                    }
                }
                if (curSum < target[T.Item1]) right.Add(new Tuple<int, long>(T.Item1, curSum));
            }
            for (int i = cL; i <= m; i++) {
                if (A[i].Item1 <= A[i].Item2) ft.update(A[i].Item1, A[i].Item2, -A[i].Item3);
                else {
                    ft.update(A[i].Item1, M, -A[i].Item3);
                    ft.update(1, A[i].Item2, -A[i].Item3);
                }
            }
            solve(ref left, cL, m);
            solve(ref right, m + 1, cR);
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            stations = new List<int>[N + 1];
            target = new long[N + 1];
            ans = new int[N + 1];
            ft = new FenwickTreeRangePoint(M);
            for (int i = 1; i <= N; i++) stations[i] = new List<int>();
            for (int i = 1; i <= M; i++) stations[In.ReadInt()].Add(i);
            for (int i = 1; i <= N; i++) target[i] = In.ReadLong();
            K = In.ReadInt();
            A = new Tuple<int, int, long>[K + 1];
            for (int i = 1; i <= K; i++) A[i] = new Tuple<int, int, long>(In.ReadInt(), In.ReadInt(), In.ReadLong());
            List<Tuple<int, long>> toCheck = new List<Tuple<int, long>>();
            for (int i = 1; i <= K; i++) {
                if (A[i].Item1 <= A[i].Item2) ft.update(A[i].Item1, A[i].Item2, A[i].Item3);
                else {
                    ft.update(A[i].Item1, M, A[i].Item3);
                    ft.update(1, A[i].Item2, A[i].Item3);
                }
            }
            for (int i = 1; i <= N; i++) {
                long curSum = 0;
                foreach (int j in stations[i]) {
                    curSum += ft.getValue(j);
                    if (curSum >= target[i]) {
                        toCheck.Add(new Tuple<int, long>(i, 0));
                        break;
                    }
                }
                if (curSum < target[i]) ans[i] = -1;
            }
            for (int i = 1; i <= K; i++) {
                if (A[i].Item1 <= A[i].Item2) ft.update(A[i].Item1, A[i].Item2, -A[i].Item3);
                else {
                    ft.update(A[i].Item1, M, -A[i].Item3);
                    ft.update(1, A[i].Item2, -A[i].Item3);
                }
            }
            solve(ref toCheck, 1, K);
            for (int i = 1; i <= N; i++) {
                if (ans[i] == -1) Out.WriteLine("NIE");
                else Out.WriteLine(ans[i]);
            }
        }
    }
}
