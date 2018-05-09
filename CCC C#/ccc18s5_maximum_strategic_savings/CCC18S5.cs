using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using static System.Diagnostics.Debug;

namespace CCC18S5 {
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

        public class Edge : IComparable<Edge> {
            public int a, b;
            public long c;
            public bool type;

            public Edge(int a, int b, long c, bool type) {
                this.a = a;
                this.b = b;
                this.c = c;
                this.type = type;
            }

            public int CompareTo(Edge e) {
                if (c != e.c) return c.CompareTo(e.c);
                if (type && !e.type) return 1;
                if (!type && e.type) return -1;
                if (a != e.a) return a.CompareTo(e.a);
                if (b != e.b) return b.CompareTo(e.b);
                return 0;
            }
        }

        public class UF {
            public int[] par;
            public char[] rank;
            public int cnt;

            public UF(int N) {
                par = new int[N];
                rank = new char[N];
                cnt = N;
                for (int i = 0; i < N; i++) {
                    par[i] = i;
                    rank[i] = '\0';
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
                cnt--;
                return true;
            }
        }

        static int N, M, P, Q;
        static Edge[] edges;

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            P = In.ReadInt();
            Q = In.ReadInt();
            edges = new Edge[P + Q];
            long tot = 0;
            for (int i = 0; i < P; i++) {
                int a = In.ReadInt();
                int b = In.ReadInt();
                long c = In.ReadLong();
                tot += c * N;
                edges[i] = new Edge(a - 1, b - 1, c, false);
            }
            for (int i = 0; i < Q; i++) {
                int a = In.ReadInt();
                int b = In.ReadInt();
                long c = In.ReadLong();
                tot += c * M;
                edges[P + i] = new Edge(a - 1, b - 1, c, true);
            }
            Out.WriteLine(tot - mst());
        }

        static long mst() {
            long weight = 0;
            Array.Sort(edges);
            UF cities = new UF(M);
            UF planets = new UF(N);
            for (int i = 0; i < edges.Length && (cities.cnt > 1 || planets.cnt > 1); i++) {
                Edge e = edges[i];
                if (e.type) {
                    if (planets.join(e.a, e.b)) weight += cities.cnt * e.c;
                } else {
                    if (cities.join(e.a, e.b)) weight += planets.cnt * e.c;
                }
            }
            return weight;
        }

        static long mst2() {
            long weight = 0;
            SortedDictionary<Edge, int> dict = new SortedDictionary<Edge, int>();
            foreach (Edge e in edges) {
                if (dict.ContainsKey(e)) dict[e]++;
                else dict[e] = 1;
            }
            UF cities = new UF(M);
            UF planets = new UF(N);
            while (dict.Count() > 0 && (cities.cnt > 1 || planets.cnt > 1)) {
                KeyValuePair<Edge, int> p = dict.First();
                Edge e = p.Key;
                if (e.type) {
                    if (planets.join(e.a, e.b)) weight += cities.cnt * e.c;
                } else {
                    if (cities.join(e.a, e.b)) weight += planets.cnt * e.c;
                }
                if (p.Value == 1) dict.Remove(e);
                else dict[e]--;
            }
            return weight;
        }
    }
}
