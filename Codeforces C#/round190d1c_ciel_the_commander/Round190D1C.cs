// http://codeforces.com/contest/321/problem/C
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Round190D1C {
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

            public string ReadLine() { return reader.ReadLine();  }

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

        public static void Main(string[] args) {
            Thread T = new Thread(new ThreadStart(start), 1 << 27);
            T.Start();
        }

        static int N;
        static char[] ans;
        static List<int>[] adj;
        static bool[] exclude;

        static int getSize(int v, int prev) {
            int size = 1;
            foreach (int w in adj[v]) if (w != prev && !exclude[w]) size += getSize(w, v);
            return size;
        }

        static int getCentroid(int v, int prev, int treeSize) {
            int n = treeSize;
            int size = 1;
            bool hasCentroid = true;
            foreach (int w in adj[v]) {
                if (w == prev || exclude[w]) continue;
                int ret = getCentroid(w, v, treeSize);
                if (ret >= 0) return ret;
                hasCentroid &= -ret <= n / 2;
                size += -ret;
            }
            hasCentroid &= n - size <= n / 2;
            return hasCentroid ? v : -size;
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

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            adj = new List<int>[N];
            exclude = new bool[N];
            ans = new char[N];
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int>();
                exclude[i] = false;
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            Queue<Tuple<int, char>> q = new Queue<Tuple<int, char>>();
            q.Enqueue(new Tuple<int, char>(0, 'A'));
            while (q.Count() > 0) {
                int v = q.Peek().Item1;
                int c = getCentroid(v, -1, getSize(v, -1));
                ans[c] = q.Peek().Item2;
                q.Dequeue();
                exclude[c] = true;
                foreach (int w in adj[c]) if (!exclude[w]) q.Enqueue(new Tuple<int, char>(w, (char) (ans[c] + 1)));
            }
            for (int i = 0; i < N; i++) Out.Write(ans[i] + " ");
            Out.WriteLine();
        }
    }
}
