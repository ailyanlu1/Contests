// http://www.spoj.com/problems/QTREE2/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace QTREE2 {
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
            NUM_OF_TEST_CASES = In.ReadInt();
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

        static int N, LGN;
        static List<int[]>[] adj;
        static int[] dep, dist;
        static int[,] par;

        static void dfs(int v, int prev, int curDep, int curDist) {
            dep[v] = curDep;
            dist[v] = curDist;
            par[0, v] = prev;
            foreach (int[] e in adj[v]) if (e[0] != prev) dfs(e[0], v, curDep + 1, curDist + e[1]);
        }

        static int lca(int v, int w) {
            if (dep[v] < dep[w]) {
                int temp = v;
                v = w;
                w = temp;
            }
            for (int i = LGN - 1; i >= 0; i--) if (par[i, v] != -1 && dep[par[i, v]] >= dep[w]) v = par[i, v];
            if (v == w) return v;
            for (int i = LGN - 1; i >= 0; i--) {
                if (par[i, v] != par[i, w]) {
                    v = par[i, v];
                    w = par[i, w];
                }
            }
            return par[0, w];
        }

        static int queryUp(int v, int k) {
            for (int i = LGN - 1; i >= 0; i--) {
                if ((1 << i) <= k) {
                    k -= (1 << i);
                    v = par[i, v];
                }
            }
            return v;
        }

        static int queryKth(int v, int w, int k) {
            int LCA = lca(v, w);
            if (dep[v] - dep[LCA] >= k) return queryUp(v, k);
            else return queryUp(w, dep[v] + dep[w] - 2 * dep[LCA] - k);
        }

        static int queryDist(int v, int w) {
            int LCA = lca(v, w);
            return dist[v] + dist[w] - 2 * dist[LCA];
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            LGN = (int) (Math.Ceiling(Math.Log(N) / Math.Log(2)) + 1);
            adj = new List<int[]>[N];
            dep = new int[N];
            dist = new int[N];
            par = new int[LGN, N];
            for (int i = 0; i < N; i++) adj[i] = new List<int[]>();
            for (int i = 0; i < LGN; i++) for (int j = 0; j < N; j++) par[i, j] = -1;
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1, c = In.ReadInt();
                adj[a].Add(new int[2] { b, c });
                adj[b].Add(new int[2] { a, c });
            }
            dfs(0, -1, 0, 0);
            for (int i = 1; i < LGN; i++) {
                for (int j = 0; j < N; j++) {
                    if (par[i - 1, j] != -1) par[i, j] = par[i - 1, par[i - 1, j]];
                }
            }
            string cmd;
            while (!(cmd = In.ReadToken()).Equals("DONE")) {
                if (cmd.Equals("DIST")) Out.WriteLine(queryDist(In.ReadInt() - 1, In.ReadInt() - 1));
                else if (cmd.Equals("KTH")) Out.WriteLine(queryKth(In.ReadInt() - 1, In.ReadInt() - 1, In.ReadInt() - 1) + 1);
            }
        }
    }
}
