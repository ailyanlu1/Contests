// http://codeforces.com/contest/208/problem/E
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Round130D2E {
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

        private static int MEMORY_LIMIT_MB = 180;

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

        static int N, LGN, M;
        static int[] size, dep, cnt, ans;
        static int[,] par;
        static bool[] isHeavy;
        static List<int>[] adj;
        static List<int[]>[] queries;

        static void getSize(int v, int prev, int d) {
            size[v] = 1;
            dep[v] = d;
            foreach (int w in adj[v]) {
                if (w == prev) continue;
                getSize(w, v, d + 1);
                size[v] += size[w];
            }
        }

        static void add(int v, int prev, int delta) {
            cnt[dep[v]] += delta;
            foreach (int w in adj[v]) if (w != prev && !isHeavy[w]) add(w, v, delta);
        }

        static void dfs(int v, int prev, bool keep = false) {
            int maxSize = -1, heavyInd = -1;
            foreach (int w in adj[v]) {
                if (w != prev && size[w] > maxSize) {
                    maxSize = size[w];
                    heavyInd = w;
                }
            }
            foreach (int w in adj[v]) if (w != prev && w != heavyInd) dfs(w, v, false);
            if (heavyInd != -1) {
                dfs(heavyInd, v, true);
                isHeavy[heavyInd] = true;
            }
            add(v, prev, 1);
            foreach (int[] q in queries[v]) ans[q[1]] = dep[v] + q[0] >= N ? 0 : Math.Max(cnt[dep[v] + q[0]] - 1, 0);
            if (heavyInd != -1) isHeavy[heavyInd] = false;
            if (!keep) add(v, prev, -1);
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt() + 1;
            LGN = (int) (Math.Ceiling(Math.Log(N) / Math.Log(2)) + 1);
            size = new int[N];
            dep = new int[N];
            cnt = new int[N];
            par = new int[N, LGN];
            isHeavy = new bool[N];
            adj = new List<int>[N];
            queries = new List<int[]>[N];
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int>();
                queries[i] = new List<int[]>();
                isHeavy[i] = false;
                cnt[i] = 0;
            }
            par[0, 0] = -1;
            for (int i = 1; i < N; i++) {
                par[i, 0] = In.ReadInt();
                adj[par[i, 0]].Add(i);
            }
            getSize(0, -1, 0);
            for (int j = 1; j < LGN; j++) {
                for (int i = 0; i < N; i++) {
                    if (par[i, j - 1] != -1) par[i, j] = par[par[i, j - 1], j - 1];
                }
            }
            M = In.ReadInt();
            ans = new int[M];
            for (int i = 0; i < M; i++) {
                int v = In.ReadInt();
                int p = In.ReadInt();
                if (dep[v] <= p) {
                    ans[i] = 0;
                } else {
                    int target = dep[v] - p;
                    for (int j = LGN - 1; j >= 0; j--) {
                        if (par[v, j] != -1 && dep[par[v, j]] >= target) {
                            v = par[v, j];
                        }
                    }
                    queries[v].Add(new int[2] { p, i });
                }
            }
            dfs(0, -1, false);
            for (int i = 0; i < M; i++) Out.Write(ans[i] + " ");
            Out.WriteLine();
        }
    }
}
