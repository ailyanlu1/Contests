using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace WeekOfCode14P4 {
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

        private static int STACK_MEMORY_LIMIT_MB = 100; // TODO CHANGE MEMORY LIMIT FOR STACK

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

        static int N, Q, H, chainNum, curInd;
        static List<int>[] adj;
        static int[] depth, parent, chain, size, head, pre, post, T, L;

        static void apply(int i, int v) {
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
            T = new int[2 * N];
            L = new int[N];
            H = 0;
            for (int i = 1; i <= N; H++) i <<= 1;
            for (int i = 0; i < N; i++) {
                T[N + i] = 0;
                L[i] = 0;
            }
            for (int i = N - 1; i > 0; i--) T[i] = Math.Max(T[i << 1], T[i << 1 | 1]);
        }

        static void update(int l, int r, int v) {
            l += N - 1;
            r += N - 1;
            int l0 = l, r0 = r;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) apply(l++, v);
                if ((r & 1) == 0) apply(r--, v);
            }
            pushup(l0);
            pushup(r0);
        }

        static int query(int l, int r) {
            l += N - 1;
            r += N - 1;
            propagate(l);
            propagate(r);
            int ret = int.MinValue;
            for (; l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) ret = Math.Max(ret, T[l++]);
                if ((r & 1) == 0) ret = Math.Max(ret, T[r--]);
            }
            return ret;
        }

        static void dfs(int v, int d, int prev) {
            depth[v] = d;
            parent[v] = prev;
            size[v] = 1;
            foreach (int w in adj[v]) {
                if (w != prev) {
                    dfs(w, d + 1, v);
                    size[v] += size[w];
                }
            }
        }

        static void hld(int v, int prev) {
            if (head[chainNum] == -1) head[chainNum] = v;
            chain[v] = chainNum;
            pre[v] = ++curInd;
            int maxIndex = -1;
            foreach (int w in adj[v]) {
                if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
            }
            if (maxIndex != -1) hld(maxIndex, v);
            foreach (int w in adj[v]) {
                if (w != prev && w != maxIndex) {
                    chainNum++;
                    hld(w, v);
                }
            }
            post[v] = curInd;
        }

        static int lca(int v, int w) {
            while (chain[v] != chain[w]) {
                if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
                else v = parent[head[chain[v]]];
            }
            if (depth[v] < depth[w]) return v;
            return w;
        }

        static void updateSubtree(int v, int val) {
            update(pre[v], post[v], val);
        }

        static int queryUp(int v, int w, bool includeW) {
            int ret = int.MinValue;
            while (chain[v] != chain[w]) {
                ret = Math.Max(ret, query(pre[head[chain[v]]], pre[v]));
                v = parent[head[chain[v]]];
            }
            if (includeW || v != w) ret = Math.Max(ret, query(pre[w] + (includeW ? 0 : 1), pre[v]));
            return ret;
        }

        static int queryPath(int v, int w) {
            int LCA = lca(v, w);
            return Math.Max(queryUp(v, LCA, true), queryUp(w, LCA, false));
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            adj = new List<int>[N];
            depth = new int[N];
            parent = new int[N];
            chain = new int[N];
            size = new int[N];
            head = new int[N];
            pre = new int[N];
            post = new int[N];
            chainNum = 0;
            curInd = 0;
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int>();
                head[i] = -1;
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            dfs(0, 0, -1);
            hld(0, -1);
            build();
            Q = In.ReadInt();
            for (int i = 0; i < Q; i++) {
                string cmd = In.ReadToken();
                if (cmd.Equals("add")) updateSubtree(In.ReadInt() - 1, In.ReadInt());
                else if (cmd.Equals("max")) Out.WriteLine(queryPath(In.ReadInt() - 1, In.ReadInt() - 1));
                else i--;
            }
        }
    }
}
