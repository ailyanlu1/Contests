// http://codeforces.com/problemset/problem/961/E
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace EduRound41E {
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

        private static int MEMORY_LIMIT_MB = 150;

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

        public class FenwickTree {
            private int size;
            private int[] arr;

            public FenwickTree(int size) {
                this.size = size;
                arr = new int[size + 1];
                for (int i = 0; i <= size; i++) arr[i] = 0;
            }

            public int rsq(int ind) {
                int sum = 0;
                for (int x = ind; x > 0; x -= (x & -x)) sum += arr[x];
                return sum;
            }

            public int rsq(int a, int b) {
                return rsq(b) - rsq(a - 1);
            }

            public void update(int ind, int val) {
                for (int x = ind; x <= size; x += (x & -x)) arr[x] += val;
            }
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            int N = In.ReadInt();
            int[] A = new int[N + 1];
            List<int>[] adj = new List<int>[N + 1];
            FenwickTree ft = new FenwickTree(N);
            for (int i = 1; i <= N; i++) adj[i] = new List<int>();
            for (int i = 1; i <= N; i++) {
                A[i] = In.ReadInt();
                if (A[i] <= N) adj[A[i]].Add(i);
                ft.update(i, 1);
            }
            long ans = 0;
            for (int i = 1; i <= N; i++) {
                ans += ft.rsq(Math.Min(N, A[i]));
                foreach (int a in adj[i]) ft.update(a, -1);
            }
            for (int i = 1; i <= N; i++) if (i <= A[i]) ans--;
            Out.WriteLine(ans / 2);
        }
    }
}
