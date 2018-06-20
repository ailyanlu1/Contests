// https://open.kattis.com/problems/shortestpath3
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace ShortestPath3 {
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
        
        public static bool run(int testCaseNum) {
            int N = In.ReadInt(), M = In.ReadInt(), Q = In.ReadInt(), S = In.ReadInt();
            if (N == 0) return false;
            Tuple<int, int, int>[] edges = new Tuple<int, int, int>[M];
            int[] dist = new int[N];
            for (int i = 0; i < N; i++) dist[i] = 0x3f3f3f3f;
            for (int i = 0; i < M; i++) edges[i] = new Tuple<int, int, int>(In.ReadInt(), In.ReadInt(), In.ReadInt());
            dist[S] = 0;
            for (int i = 0; i < N - 1; i++) foreach (Tuple<int, int, int> e in edges) if (dist[e.Item1] < 0x3f3f3f3f) dist[e.Item2] = Math.Min(dist[e.Item2], dist[e.Item1] + e.Item3);
            bool inCycle = true;
            while (inCycle) {
                inCycle = false;
                foreach (Tuple<int, int, int> e in edges) {
                    if (dist[e.Item1] < 0x3f3f3f3f && dist[e.Item2] > -0x3f3f3f3f && dist[e.Item2] > dist[e.Item1] + e.Item3) {
                        dist[e.Item2] = -0x3f3f3f3f;
                        inCycle = true;
                    }
                }
            }
            for (int i = 0; i < Q; i++) {
                int v = In.ReadInt();
                if (dist[v] == 0x3f3f3f3f) Out.WriteLine("Impossible");
                else if (dist[v] == -0x3f3f3f3f) Out.WriteLine("-Infinity");
                else Out.WriteLine(dist[v]);
            }
            Out.WriteLine();
            return true;
        }
    }
}
