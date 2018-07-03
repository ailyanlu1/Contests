using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Year2017P7 {
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

        private static int STACK_MEMORY_LIMIT_MB = 150; // TODO CHANGE MEMORY LIMIT FOR STACK

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

        static int N, LGN, H, C, cur;
        static int[] pre, post, vertex, depth;
        static int[,] parent;
        static long[] delay, dist, T, L;
        static List<Tuple<int, int>>[] adj;

        static void apply(int i, long v) {
            T[i] += v;
            if (i < N) L[i] += v;
        }

        static void pushup(int i) {
            while (i > 1) {
                i >>= 1;
                T[i] = Math.Max(T[i << 1], T[i << 1 | 1]) + L[i];
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
            T = new long[2 * N];
            L = new long[N];
            H = 0;
            for (int i = 1; i <= N; H++) i <<= 1;
            for (int i = 0; i < N; i++) {
                T[N + i] = depth[vertex[i + 1]];
                L[i] = 0;
            }
            for (int i = N - 1; i > 0; i--) T[i] = Math.Max(T[i << 1], T[i << 1 | 1]);
        }

        static void update(int l, int r, int v) {
            l += (N - 1);
            r += (N - 1);
            int l0 = l, r0 = r;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) apply(l++, v);
                if ((r & 1) == 0) apply(r--, v);
            }
            pushup(l0);
            pushup(r0);
        }

        static long query(int l, int r) {
            l += (N - 1);
            r += (N - 1);
            propagate(l);
            propagate(r);
            long q = 0;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) q = Math.Max(q, T[l++]);
                if ((r & 1) == 0) q = Math.Max(T[r--], q);
            }
            return q;
        }

        static void dfs(int v, int prev, int d, long dd) {
            depth[v] = d;
            dist[v] = dd;
            pre[v] = ++cur;
            vertex[cur] = v;
            foreach (Tuple<int, int> e in adj[v]) dfs(e.Item1, v, d + 1, dd + e.Item2);
            post[v] = cur;
        }

        static int search(int v, long t) {
            for (int j = LGN - 1; j >= 0; j--) {
                if (parent[v, j] != -1 && dist[parent[v, j]] >= t) v = parent[v, j];
            }
            return v;
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt() + 1;
            LGN = (int) Math.Ceiling(Math.Log(N) / Math.Log(2)) + 1;
            pre = new int[N];
            post = new int[N];
            vertex = new int[N + 1];
            depth = new int[N];
            delay = new long[N];
            parent = new int[N, LGN];
            dist = new long[N];
            adj = new List<Tuple<int, int>>[N];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < LGN; j++) parent[i, j] = -1;
                adj[i] = new List<Tuple<int, int>>();
            }
            for (int i = 1; i < N; i++) delay[i] = In.ReadInt();
            parent[0, 0] = -1;
            for (int i = 1; i < N; i++) {
                int p = In.ReadInt();
                int d = In.ReadInt();
                adj[p].Add(new Tuple<int, int>(i, d));
                parent[i, 0] = p;
            }
            dfs(0, -1, 0, 0);
            for (int j = 1; j < LGN; j++) {
                 for (int i = 0; i < N; i++) {
                    if (parent[i, j - 1] != -1) parent[i, j] = parent[parent[i, j - 1], j - 1];
                }
            }
            build();
            for (int i = 1; i < N; i++) {
                if (dist[i] < delay[i]) continue;
                int v = search(i, delay[i]);
                update(pre[v], post[v], -N);
            }
            C = In.ReadInt();
            for (int i = 0; i < C; i++) {
                int v = In.ReadInt();
                int d = In.ReadInt();
                if (dist[v] >= delay[v]) {
                    int w = search(v, delay[v]);
                    update(pre[w], post[w], N);
                }
                delay[v] = d;
                if (dist[v] >= delay[v]) {
                    int w = search(v, delay[v]);
                    update(pre[w], post[w], -N);
                }
                Out.WriteLine(query(pre[0], post[0]));
            }
        }
    }
}
