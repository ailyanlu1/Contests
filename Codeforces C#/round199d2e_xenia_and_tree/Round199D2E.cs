// http://codeforces.com/contest/342/problem/E
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Round199D2E {
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

        private static int MEMORY_LIMIT_MB = 200;

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

        static int INF = (int) (0x3f3f3f3f);

        static int N, M, ind;
        static int[] par, head, depth, logTable, best;
        static int[,] rmq;
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

        static void dfs(int v, int prev, int d) {
            depth[v] = d;
            head[v] = ind;
            rmq[0, ind++] = v;
            foreach (int w in adj[v]) {
                if (w == prev) continue;
                dfs(w, v, d + 1);
                rmq[0, ind++] = v;
            }
        }

        static int minDepth(int v, int w) {
            return depth[v] < depth[w] ? v : w;
        }

        static int RMQ(int l, int r) {
            int i = logTable[r - l + 1];
            return minDepth(rmq[i, l], rmq[i, r - (1 << i) + 1]);
        }

        static int lca(int v, int w) {
            return head[v] < head[w] ? RMQ(head[v], head[w]) : RMQ(head[w], head[v]);
        }

        static int dist(int v, int w) {
            return depth[v] + depth[w] - 2 * depth[lca(v, w)];
        }

        static void update(int v) {
            int p = v;
            while (p != -1) {
                best[p] = Math.Min(best[p], dist(p, v));
                p = par[p];
            }
        }

        static int query(int v) {
            int ret = INF;
            int p = v;
            while (p != -1) {
                ret = Math.Min(ret, best[p] + dist(p, v));
                p = par[p];
            }
            return ret;
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            logTable = new int[N * 2];
            logTable[0] = logTable[1] = 0;
            for (int i = 2; i < N * 2; i++) logTable[i] = logTable[i >> 1] + 1;
            adj = new List<int>[N];
            exclude = new bool[N];
            par = new int[N];
            head = new int[N];
            depth = new int[N];
            best = new int[N];
            rmq = new int[logTable[N * 2 - 1] + 1, N * 2 - 1];
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int>();
                head[i] = -1;
                exclude[i] = false;
                best[i] = INF;
            }
            for (int i = 0; i <= logTable[N * 2 - 1]; i++) for (int j = 0; j < N * 2 - 1; j++) rmq[i, j] = 0;
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            Queue<Tuple<int, int>> q = new Queue<Tuple<int, int>>();
            q.Enqueue(new Tuple<int, int>(0, -1));
            while (q.Count() > 0) {
                int v = q.Peek().Item1;
                int c = getCentroid(v, -1, getSize(v, -1));
                par[c] = q.Peek().Item2;
                q.Dequeue();
                exclude[c] = true;
                foreach (int w in adj[c]) if (!exclude[w]) q.Enqueue(new Tuple<int, int>(w, c));
            }
            ind = 0;
            dfs(0, -1, 0);
            for (int i = 0; i < logTable[N * 2 - 1]; i++) {
                for (int j = 0; j < ind; j++) {
                    rmq[i + 1, j] = minDepth(rmq[i, j], rmq[i, Math.Min(j + (1 << i), ind - 1)]);
                }
            }
            update(0);
            for (int i = 0; i < M; i++) {
                if (In.ReadInt() == 1) update(In.ReadInt() - 1);
                else Out.WriteLine(query(In.ReadInt() - 1));
            }
        }
    }
}
