// http://www.spoj.com/problems/QTREE3/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace QTREE3 {
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

        static int N, Q, chainNum, curInd;
        static List<int>[] adj;
        static bool[] color;
        static int[] T, dep, par, size, ind, chain, head;

        static int minDep(int a, int b) {
            return dep[a] < dep[b] ? a : b;
        }

        static void initSegTree() {
            T = new int[2 * N];
            for (int i = 1; i < 2 * N; i++) T[i] = N;
        }

        static void updateSegTree(int i, int v) {
            for (T[i += (N - 1)] = v; (i >>= 1) != 0;) T[i] = minDep(T[i << 1], T[i << 1 | 1]);
        }

        static int querySegTree(int l, int r) {
            int q = N;
            for (l += (N - 1), r += (N - 1); l <= r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) q = minDep(q, T[l++]);
                if ((r & 1) == 0) q = minDep(T[r--], q);
            }
            return q;
        }

        static void dfs(int v, int prev, int curDep) {
            dep[v] = curDep;
            par[v] = prev;
            size[v] = 1;
            foreach (int w in adj[v]) {
                if (w == prev) continue;
                dfs(w, v, curDep + 1);
                size[v] += size[w];
            }
        }

        static void hld(int v, int prev) {
            if (head[chainNum] == -1) head[chainNum] = v;
            chain[v] = chainNum;
            ind[v] = curInd++;
            int maxInd = -1;
            foreach (int w in adj[v]) {
                if (w != prev && (maxInd == -1 || size[maxInd] < size[w])) maxInd = w;
            }
            if (maxInd != -1) hld(maxInd, v);
            foreach (int w in adj[v]) {
                if (w == prev || w == maxInd) continue;
                chainNum++;
                hld(w, v);
            }
        }

        static void initHLD() {
            chainNum = 0;
            curInd = 1;
            for (int i = 0; i < N; i++) head[i] = -1;
            dfs(0, -1, 0);
            hld(0, -1);
            initSegTree();
        }
        static int queryUp(int v, int w) {
            int ret = N;
            while (chain[v] != chain[w]) {
                ret = minDep(ret, querySegTree(ind[head[chain[v]]], ind[v]));
                v = par[head[chain[v]]];
            }
            return minDep(ret, querySegTree(ind[w], ind[v]));
        }

        static void toggle(int v) {
            color[v] ^= true;
            if (color[v]) updateSegTree(ind[v], v);
            else updateSegTree(ind[v], N);
        }

        static int query(int v) {
            return queryUp(v, 0);
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            Q = In.ReadInt();
            adj = new List<int>[N];
            dep = new int[N + 1];
            dep[N] = N;
            par = new int[N];
            size = new int[N];
            ind = new int[N];
            chain = new int[N];
            head = new int[N];
            color = new bool[N];
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int>();
                color[i] = false;
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            initHLD();
            for (int i = 0; i < Q; i++) {
                int t = In.ReadInt();
                int v = In.ReadInt() - 1;
                if (t == 0) toggle(v);
                else {
                    int ans = query(v);
                    Out.WriteLine(ans == N ? -1 : ans + 1);
                }
            }
        }
    }
}
