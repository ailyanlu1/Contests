// http://codeforces.com/contest/893/problem/F
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace EduRound33F {
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

            public string ReadLine() { return reader.ReadLine();  }

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

        private static int MEMORY_LIMIT_MB = 450;

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

        public class Node {
            public Node left, right;
            public int val;

            public Node(int val) {
                this.val = val;
                this.left = null;
                this.right = null;
            }
            
            public Node(Node l, Node r) {
                this.left = l;
                this.right = r;
                this.val = Math.Min(l.val, r.val);
            }
        }

        static Node build(int cL, int cR) {
            if (cL == cR) return new Node(int.MaxValue);
            int m = cL + (cR - cL) / 2;
            return new Node(build(cL, m), build(m + 1, cR));
        }

        static Node update(Node cur, int cL, int cR, int ind, int val) {
            if (cL > ind || cR < ind) return cur;
            if (cL == cR) return new Node(val);
            int m = cL + (cR - cL) / 2;
            return new Node(update(cur.left, cL, m, ind, val), update(cur.right, m + 1, cR, ind, val));
        }

        static int query(Node cur, int cL, int cR, int l, int r) {
            if (cL > r || cR < l) return int.MaxValue;
            if (cL >= l && cR <= r) return cur.val;
            int m = cL + (cR - cL) / 2;
            return Math.Min(query(cur.left, cL, m, l, r), query(cur.right, m + 1, cR, l, r));
        }

        static int N, R, M, cur, curDep, lastAns;
        static List<int>[] adj;
        static List<Node> rev;
        static int[] A, depOrd, pre, post, depth;

        static void dfs(int v, int prev, int d) {
            depth[v] = d;
            pre[v] = ++cur;
            foreach (int w in adj[v]) if (w != prev) dfs(w, v, d + 1);
            post[v] = cur;
        }

        public class DepthComparer : IComparer<int> {
            public int Compare(int a, int b) {
                return depth[a].CompareTo(depth[b]);
            }
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            R = In.ReadInt() - 1;
            cur = 0;
            A = new int[N];
            depOrd = new int[N];
            pre = new int[N];
            post = new int[N];
            depth = new int[N];
            rev = new List<Node>();
            adj = new List<int>[N];
            for (int i = 0; i < N; i++) {
                A[i] = In.ReadInt();
                adj[i] = new List<int>();
                depOrd[i] = i;
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                adj[a].Add(b);
                adj[b].Add(a);
            }
            rev.Add(build(1, N));
            dfs(R, -1, 0);
            Array.Sort(depOrd, new DepthComparer());
            curDep = 0;
            for (int i = 0; i < N; i++) {
                Node x = update(rev.Last(), 1, N, pre[depOrd[i]], A[depOrd[i]]);
                if (depth[depOrd[i]] > curDep) {
                    rev.Add(x);
                    curDep++;
                } else {
                    rev[rev.Count() - 1] = x;
                }
            }
            M = In.ReadInt();
            lastAns = 0;
            for (int i = 0; i < M; i++) {
                int a = (In.ReadInt() + lastAns) % N;
                int b = (In.ReadInt() + lastAns) % N;
                lastAns = query(rev[Math.Min(depth[a] + b, curDep)], 1, N, pre[a], post[a]);
                Out.WriteLine(lastAns);
            }
        }
    }
}
