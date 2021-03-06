﻿// http://codeforces.com/contest/620/problem/E
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace EduRound6E {
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

        static int N, H, M, cur;
        static List<int>[] adj;
        static int[] pre, post, vert, color;
        static long[] T, L;

        static void apply(int i, long v) {
            T[i] = v;
            if (i < N) L[i] = v;
        }

        static void pushup(int i) {
            while (i > 1) {
                i >>= 1;
                T[i] = L[i] == 0 ? T[i << 1] | T[i << 1 | 1] : L[i];
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
                T[N + i] = 1L << color[vert[i + 1]];
                L[i] = 0;
            }
            for (int i = N - 1; i > 0; i--) T[i] = T[i << 1] | T[i << 1 | 1];
        }

        static void update(int l, int r, long v) {
            l += N - 1;
            r += N - 1;
            propagate(l);
            propagate(r);
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
                if ((l & 1) == 1) q |= T[l++];
                if ((r & 1) == 0) q |= T[r--];
            }
            return q;
        }

        static void dfs(int v, int prev) {
            pre[v] = ++cur;
            vert[cur] = v;
            foreach (int w in adj[v]) if (w != prev) dfs(w, v);
            post[v] = cur;
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            color = new int[N];
            pre = new int[N];
            post = new int[N];
            vert = new int[N + 1];
            adj = new List<int>[N];
            for (int i = 0; i < N; i++) {
                color[i] = In.ReadInt() - 1;
                adj[i] = new List<int>();
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            cur = 0;
            dfs(0, -1);
            build();
            for (int i = 0; i < M; i++) {
                int t = In.ReadInt();
                if (t == 1) {
                    int v = In.ReadInt() - 1;
                    int c = In.ReadInt() - 1;
                    update(pre[v], post[v], 1L << c);
                } else {
                    int v = In.ReadInt() - 1;
                    long q = query(pre[v], post[v]);
                    long ans = 0;
                    for (int k = 0; k < 60; k++) ans += (q >> k) & 1;
                    Out.WriteLine(ans);
                }
            }
        }
    }
}
