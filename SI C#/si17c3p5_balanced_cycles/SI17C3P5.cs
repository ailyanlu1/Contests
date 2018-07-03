using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace SI17C3P5 {
    public class Program {
        public class Reader {
            private TextReader reader;
            private string[] tokens;
            private int currentToken;

            public Reader(Stream s) {
                reader = new StreamReader(s);
                tokens = new string[0];
                currentToken = 0;
            }

            public Reader(string file) {
                reader = new StreamReader(file);
                tokens = new string[0];
                currentToken = 0;
            }

            public string ReadLine() { return reader.ReadLine();  }

            public string ReadToken() {
                while (currentToken == tokens.Length) {
                    tokens = ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries);
                    currentToken = 0;
                }
                return tokens[currentToken++];
            }

            public char ReadChar() { return ReadToken()[0]; }
            public int ReadInt() { return int.Parse(ReadToken()); }
            public long ReadLong() { return long.Parse(ReadToken()); }
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

        static int N;
        static List<int[]>[] adj;
        static bool[] exclude;
        static List<int> small, toRemove;
        static int[] large;

        static int getSize(int v, int prev) {
            int size = 1;
            foreach (int[] e in adj[v]) if (e[0] != prev && !exclude[e[0]]) size += getSize(e[0], v);
            return size;
        }

        static int getCentroid(int v, int prev, int treeSize) {
            int n = treeSize;
            int size = 1;
            bool hasCentroid = true;
            foreach (int[] e in adj[v]) {
                if (e[0] == prev || exclude[e[0]]) continue;
                int ret = getCentroid(e[0], v, treeSize);
                if (ret >= 0) return ret;
                hasCentroid &= -ret <= n / 2;
                size += -ret;
            }
            hasCentroid &= n - size <= n / 2;
            return hasCentroid ? v : -size;
        }
        
        static void dfs(int v, int prev, int d) {
            small.Add(d);
            foreach (int[] e in adj[v]) if (e[0] != prev && !exclude[e[0]]) dfs(e[0], v, d + e[1]);
        }
        
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            adj = new List<int[]>[N];
            exclude = new bool[N];
            small = new List<int>();
            toRemove = new List<int>();
            large = new int[2 * N + 1];
            for (int i = 0; i < N; i++) {
                adj[i] = new List<int[]>();
                exclude[i] = false;
            }
            for (int i = 0; i < N - 1; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1, c = In.ReadChar() == 'r' ? -1 : 1;
                adj[a].Add(new int[2]{b, c});
                adj[b].Add(new int[2]{a, c});
            }
            Queue<int> q = new Queue<int>();
            q.Enqueue(0);
            long ans = 0;
            while (q.Count() > 0) {
                int v = q.Dequeue();
                int c = getCentroid(v, -1, getSize(v, -1));
                foreach (int[] e in adj[c]) {
                    if (exclude[e[0]]) continue;
                    small.Clear();
                    dfs(e[0], c, e[1]);
                    for (int i = 0; i < small.Count(); i++) {
                        int x = small[i];
                        ans += large[N - x - 1] + large[N - x + 1] + (Math.Abs(x) == 1 && i > 0 ? 1 : 0);
                    }
                    foreach (int x in small) {
                        large[N + x]++;
                        toRemove.Add(x);
                    }
                }
                foreach (int x in toRemove) large[N + x] = 0;
                toRemove.Clear();
                exclude[c] = true;
                foreach (int[] e in adj[c]) if (!exclude[e[0]]) q.Enqueue(e[0]);
            }
            Out.WriteLine(ans);
        }
    }
}
