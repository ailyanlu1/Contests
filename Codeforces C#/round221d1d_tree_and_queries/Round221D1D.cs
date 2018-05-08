// http://codeforces.com/contest/375/problem/D
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Round221D1D {
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

        static int MAXC = 100005;

        static int N, M;
        static int[] color, cnt, size;
        static int[] ans;
        static bool[] isHeavy;
        static List<int>[] adj;
        static List<int[]>[] queries;
        static FenwickTree ft;

        static void getSize(int v, int prev) {
            size[v] = 1;
            foreach (int w in adj[v]) {
                if (w == prev) continue;
                getSize(w, v);
                size[v] += size[w];
            }
        }

        static void add(int v, int prev, int delta) {
            if (cnt[color[v]] > 0) ft.update(cnt[color[v]], -1);
            cnt[color[v]] += delta;
            if (cnt[color[v]] > 0) ft.update(cnt[color[v]], 1);
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
            foreach (int[] q in queries[v]) ans[q[1]] = ft.rsq(Math.Min(q[0], N), N);
            if (heavyInd != -1) isHeavy[heavyInd] = false;
            if (!keep) add(v, prev, -1);
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            ft = new FenwickTree(N);
            color = new int[N];
            cnt = new int[MAXC];
            for (int i = 0; i < MAXC; i++) cnt[i] = 0;
            size = new int[N];
            isHeavy = new bool[N];
            adj = new List<int>[N];
            queries = new List<int[]>[N];
            ans = new int[M];
            for (int i = 0; i < N; i++) {
                color[i] = In.ReadInt();
                isHeavy[i] = false;
                adj[i] = new List<int>();
                queries[i] = new List<int[]>();
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            for (int i = 0; i < M; i++) queries[In.ReadInt() - 1].Add(new int[2] { In.ReadInt(), i });
            getSize(0, -1);
            dfs(0, -1);
            for (int i = 0; i < M; i++) Out.WriteLine(ans[i]);
        }
    }
}
