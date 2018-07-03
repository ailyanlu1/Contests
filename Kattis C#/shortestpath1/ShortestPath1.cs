// https://open.kattis.com/problems/shortestpath1
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace ShortestPath1 {
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
        
        public class IndexMinPQ<Key> where Key : IComparable<Key> {
            private int maxN;
            private int n;
            private int[] pq;
            private int[] qp;
            private Key[] keys;
        
            public IndexMinPQ(int maxN) {
                if (maxN < 0) throw new Exception("maxN cannot be negative");
                this.maxN = maxN;
                n = 0;
                keys = new Key[maxN];
                pq = new int[maxN + 1];
                qp = new int[maxN];
                for (int i = 0; i < maxN; i++) qp[i] = -1;
            }
        
            public bool isEmpty() {
                return n == 0;
            }
        
            public bool contains(int i) {
                if (i < 0 || i >= maxN) throw new IndexOutOfRangeException();
                return qp[i] != -1;
            }
        
            public int size() {
                return n;
            }
            
            public void insert(int i, Key key) {
                if (i < 0 || i >= maxN) throw new IndexOutOfRangeException();
                if (contains(i)) throw new Exception("index is already in the priority queue");
                n++;
                qp[i] = n;
                pq[n] = i;
                keys[i] = key;
                swim(n);
            }
        
            public int minIndex() {
                if (n == 0) throw new Exception("Priority queue underflow");
                return pq[1];
            }
        
            public Key minKey() {
                if (n == 0) throw new Exception("Priority queue underflow");
                return keys[pq[1]];
            }
        
            public int delMin() {
                if (n == 0) throw new Exception("Priority queue underflow");
                int min = pq[1];
                exch(1, n--);
                sink(1);
                qp[min] = -1;
                pq[n + 1] = -1;
                return min;
            }
        
            public Key keyOf(int i) {
                if (i < 0 || i >= maxN) throw new IndexOutOfRangeException();
                if (!contains(i)) throw new Exception("index is not in the priority queue");
                else return keys[i];
            }
        
            public void changeKey(int i, Key key) {
                if (i < 0 || i >= maxN) throw new IndexOutOfRangeException();
                if (!contains(i)) throw new Exception("index is not in the priority queue");
                Key old = keys[i];
                keys[i] = key;
                if (old.CompareTo(key) < 0) swim(qp[i]);
                else if (old.CompareTo(key) > 0) sink(qp[i]);
            }
        
            public void delete(int i) {
                if (i < 0 || i >= maxN) throw new IndexOutOfRangeException();
                if (!contains(i)) throw new Exception("index is not in the priority queue");
                int index = qp[i];
                exch(index, n--);
                swim(index);
                sink(index);
                qp[i] = -1;
            }
        
            private bool greater(int i, int j) {
                return keys[pq[i]].CompareTo(keys[pq[j]]) > 0;
            }
        
            private void exch(int i, int j) {
                int swap = pq[i];
                pq[i] = pq[j];
                pq[j] = swap;
                qp[pq[i]] = i;
                qp[pq[j]] = j;
            }
        
            private void swim(int k) {
                while (k > 1 && greater(k / 2, k)) {
                    exch(k, k / 2);
                    k = k / 2;
                }
            }
        
            private void sink(int k) {
                while (2 * k <= n) {
                    int j = 2 * k;
                    if (j < n && greater(j, j + 1)) j++;
                    if (!greater(k, j)) break;
                    exch(k, j);
                    k = j;
                }
            }
        }

        public static bool run(int testCaseNum) {
            int N = In.ReadInt(), M = In.ReadInt(), Q = In.ReadInt(), S = In.ReadInt();
            if (N == 0) return false;
            List<int[]>[] adj = new List<int[]>[N];
            IndexMinPQ<int> PQ = new IndexMinPQ<int>(N);
            int[] dist = new int[N];
            for (int i = 0; i < N; i++) {
                dist[i] = 0x3f3f3f3f;
                adj[i] = new List<int[]>();
            }
            for (int i = 0; i < M; i++) adj[In.ReadInt()].Add(new int[2]{In.ReadInt(), In.ReadInt()});
            dist[S] = 0;
            PQ.insert(S, 0);
            while (!PQ.isEmpty()) {
                int v = PQ.delMin();
                foreach (int[] e in adj[v]) {
                    if (dist[e[0]] > dist[v] + e[1]) {
                        dist[e[0]] = dist[v] + e[1];
                        if (PQ.contains(e[0])) PQ.changeKey(e[0], dist[e[0]]);
                        else PQ.insert(e[0], dist[e[0]]);
                    }
                }
            }
            for (int i = 0; i < Q; i++) {
                int v = In.ReadInt();
                if (dist[v] == 0x3f3f3f3f) Out.WriteLine("Impossible");
                else Out.WriteLine(dist[v]);
            }
            Out.WriteLine();
            return true;
        }
    }
}
