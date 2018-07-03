using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace APIO10P2 {
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

        public static void Main(string[] args) {
            start();
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

        static int N, K;
        static int[] last, to;
        static List<int[]> edges;

        static void dfsDist(int v, int prev, int d, ref int furthestV, ref int furthestDist) {
            if (d > furthestDist) {
                furthestDist = d;
                furthestV = v;
            }
            for (int i = last[v]; i != -1; i = edges[i][2]) {
                if (edges[i][0] == prev) continue;
                to[edges[i][0]] = i;
                dfsDist(edges[i][0], v, d + 1, ref furthestV, ref furthestDist);
            }
        }

        static int dfs(int v, int prev, ref int ans) {
            int best1 = 0, best2 = 0;
            for (int i = last[v]; i != -1; i = edges[i][2]) {
                if (edges[i][0] == prev) continue;
                int best1w = dfs(edges[i][0], v, ref ans);
                if (best1 <= best1w + edges[i][1]) {
                    best2 = best1;
                    best1 = best1w + edges[i][1];
                } else if (best2 <= best1w + edges[i][1]) {
                    best2 = best1w + edges[i][1];
                }
            }
            ans = Math.Max(ans, best1 + best2);
            return best1;
        }

        public static void run(int testCaseNum) {
            N = In.ReadInt();
            K = In.ReadInt();
            last = new int[N];
            to = new int[N];
            edges = new List<int[]>();
            for (int i = 0; i < N; i++) last[i] = -1;
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                edges.Add(new int[3]{b, 0, last[a]});
                last[a] = edges.Count() - 1;
                edges.Add(new int[3]{a, 0, last[b]});
                last[b] = edges.Count() - 1;
            }
            int s = -1, t = -1, d = -1;
            dfsDist(0, -1, 0, ref s, ref d);
            d = -1;
            to[s] = -1;
            dfsDist(s, -1, 0, ref t, ref d);
            if (K == 1) {
                Out.WriteLine(2 * (N - 1) - d + 1);
            } else {
                for (int i = 0; i < edges.Count(); i++) edges[i][1] = 1;
                for (int i = to[t]; i != -1; i = to[edges[i ^ 1][0]]) edges[i][1] = edges[i ^ 1][1] = -1;
                int ans = 0;
                dfs(0, -1, ref ans);
                Out.WriteLine(2 * (N - 1) - d - ans + 2);
            }
        }
    }
}
