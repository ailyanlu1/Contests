// https://open.kattis.com/problems/minspantree
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace MinSpanTree {
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
            for (int i = 1; ; i++) {
                try {
                    if(!run(i)) break;
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
        
        public class UF {
            private int[] par;
            private byte[] rank;
            
            public UF(int N) {
                par = new int[N];
                rank = new byte[N];
                for (int i = 0; i < N; i++) {
                    par[i] = i;
                    rank[i] = 0;
                }
            }
            
            public int find(int p) {
                while (p != par[p]) p = par[p] = par[par[p]];
                return p;
            }
            
            public bool join(int p, int q) {
                p = find(p);
                q = find(q);
                if (p == q) return false;
                if (rank[p] < rank[q]) par[p] = q;
                else if (rank[p] > rank[q]) par[q] = p;
                else {
                    par[q] = p;
                    rank[p]++;
                }
                return true;
            }
        }
        
        public static bool run(int testCaseNum) {
            int N = In.ReadInt(), M = In.ReadInt();
            if (N == 0) return false;
            Tuple<int, int, int>[] edges = new Tuple<int, int, int>[M];
            for (int i = 0; i < M; i++) {
                int u = In.ReadInt(), v = In.ReadInt(), w = In.ReadInt();
                edges[i] = new Tuple<int, int, int>(w, Math.Min(u, v), Math.Max(u, v));
            }
            Array.Sort(edges);
            List<Tuple<int, int>> mst = new List<Tuple<int, int>>();
            int weight = 0;
            UF uf = new UF(N);
            for (int i = 0; i < M && mst.Count() < N - 1; i++) {
                if (uf.join(edges[i].Item2, edges[i].Item3)) {
                    mst.Add(new Tuple<int, int>(edges[i].Item2, edges[i].Item3));
                    weight += edges[i].Item1;
                }
            }
            if (mst.Count() < N - 1) Out.WriteLine("Impossible");
            else {
                Out.WriteLine(weight);
                mst.Sort();
                foreach (Tuple<int, int> e in mst) Out.WriteLine("{0} {1}", e.Item1, e.Item2);
            }
            return true;
        }
    }
}
