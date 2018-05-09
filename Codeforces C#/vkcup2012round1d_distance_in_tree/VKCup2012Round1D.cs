// http://codeforces.com/contest/161/problem/D
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace VKCup2012Round1D {
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

        public static void Main(string[] args) {
            Runner R = new Runner();
            R.start();
        }

        public class Runner {
            public void start() {
                Thread T = new Thread(new ThreadStart(runnerMain), 1 << 28);
                T.Start();
            }

            static int N, K;
            static long ans;
            static List<int>[] adj;
            static bool[] exclude;
            static int[] cnt;
            static List<int> toInsert, toErase;

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

            static void dfs(int v, int prev, int dist) {
                if (dist > K) return;
                ans += cnt[K - dist];
                foreach (int w in adj[v]) if (w != prev && !exclude[w]) dfs(w, v, dist + 1);
                toInsert.Add(dist);
            }

            public static void runnerMain() {
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

            public static void run(int testCaseNum) {
                N = In.ReadInt();
                K = In.ReadInt();
                adj = new List<int>[N];
                exclude = new bool[N];
                ans = 0;
                cnt = new int[K + 1];
                toInsert = new List<int>();
                toErase = new List<int>();
                for (int i = 0; i <= K; i++) cnt[K] = 0;
                for (int i = 0; i < N; i++) {
                    adj[i] = new List<int>();
                    exclude[i] = false;
                }
                for (int i = 0; i < N - 1; i++) {
                    int a = In.ReadInt() - 1, b = In.ReadInt() - 1;
                    adj[a].Add(b);
                    adj[b].Add(a);
                }
                Queue<int> q = new Queue<int>();
                q.Enqueue(0);
                while (q.Count() > 0) {
                    int v = q.Dequeue();
                    int c = getCentroid(v, -1, getSize(v, -1));
                    toErase.Clear();
                    cnt[0] = 1;
                    toErase.Add(0);
                    foreach (int w in adj[c]) {
                        if (exclude[w]) continue;
                        toInsert.Clear();
                        dfs(w, c, 1);
                        foreach (int d in toInsert) {
                            cnt[d]++;
                            toErase.Add(d);
                        }
                    }
                    foreach (int d in toErase) cnt[d] = 0;
                    exclude[c] = true;
                    foreach (int w in adj[c]) if (!exclude[w]) q.Enqueue(w);
                }
                Out.WriteLine(ans);
            }
        }
    }
}
