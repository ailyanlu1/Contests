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

        static int N, chainNum, curInd;
        static List<int[]>[] adj;
        static int[] dep, dist, par, size, vert, ind, chain, head;

        static void dfs(int v, int prev, int curDep, int curDist) {
            dep[v] = curDep;
            dist[v] = curDist;
            par[v] = prev;
            size[v] = 1;
            foreach (int[] e in adj[v]) {
                if (e[0] == prev) continue;
                dfs(e[0], v, curDep + 1, curDist + e[1]);
                size[v] += size[e[0]];
            }
        }

        static void hld(int v, int prev) {
            if (head[chainNum] == -1) head[chainNum] = v;
            chain[v] = chainNum;
            ind[v] = curInd;
            vert[curInd++] = v;
            int maxInd = -1;
            foreach (int[] e in adj[v]) {
                if (e[0] != prev && (maxInd == -1 || size[maxInd] < size[e[0]])) maxInd = e[0];
            }
            if (maxInd != -1) hld(maxInd, v);
            foreach (int[] e in adj[v]) {
                if (e[0] == prev || e[0] == maxInd) continue;
                chainNum++;
                hld(e[0], v);
            }
        }

        static void initHLD() {
            chainNum = 0;
            curInd = 1;
            for (int i = 0; i < N; i++) head[i] = -1;
            dfs(0, -1, 0, 0);
            hld(0, -1);
        }

        static int lca(int v, int w) {
            while (chain[v] != chain[w]) {
                if (dep[head[chain[v]]] < dep[head[chain[w]]]) w = par[head[chain[w]]];
                else v = par[head[chain[v]]];
            }
            return dep[v] < dep[w] ? v : w;
        }

        static int queryUp(int v, int w, int k) {
            while (chain[v] != chain[w]) {
                if (ind[v] - ind[head[chain[v]]] >= k) return vert[ind[v] - k];
                k -= ind[v] - ind[head[chain[v]]] + 1;
                v = par[head[chain[v]]];
            }
            return vert[ind[v] - k];
        }

        static int queryPath(int v, int w, int k) {
            int LCA = lca(v, w);
            if (dep[v] - dep[LCA] >= k) return queryUp(v, LCA, k);
            else return queryUp(w, LCA, dep[v] + dep[w] - 2 * dep[LCA] - k);
        }

        static int queryDist(int v, int w) {
            int LCA = lca(v, w);
            return dist[v] + dist[w] - 2 * dist[LCA];
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            adj = new List<int[]>[N];
            dep = new int[N];
            dist = new int[N];
            par = new int[N];
            size = new int[N];
            vert = new int[N + 1];
            ind = new int[N];
            chain = new int[N];
            head = new int[N];
            for (int i = 0; i < N; i++) adj[i] = new List<int[]>();
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1, c = In.ReadInt();
                adj[a].Add(new int[2] { b, c });
                adj[b].Add(new int[2] { a, c });
            }
            initHLD();
            string cmd;
            while (!(cmd = In.ReadToken()).Equals("DONE")) {
                if (cmd.Equals("DIST")) Out.WriteLine(queryDist(In.ReadInt() - 1, In.ReadInt() - 1));
                else if (cmd.Equals("KTH")) Out.WriteLine(queryPath(In.ReadInt() - 1, In.ReadInt() - 1, In.ReadInt() - 1) + 1);
            }
        }
    }
}
