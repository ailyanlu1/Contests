using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace NCCO4D2P1 {
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

        private static int STACK_MEMORY_LIMIT_MB = 1; // TODO CHANGE MEMORY LIMIT FOR STACK

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
        
        static int INF = (int) 0x3f3f3f3f;
        
        public static void run(int testCaseNum) {
            int N = In.ReadInt(), M = In.ReadInt(), W = In.ReadInt();
            Tuple<int, int, int>[] edges = new Tuple<int, int, int>[2 * M + W];
            for (int i = 0; i < M + W; i++) {
                int a = In.ReadInt() - 1, b = In.ReadInt() - 1, c = In.ReadInt();
                if (i < M) {
                    edges[i] = new Tuple<int, int, int>(a, b, c);
                    edges[M + W + i] = new Tuple<int, int, int>(b, a, c);
                } else {
                    edges[i] = new Tuple<int, int, int>(a, b, -c);
                }
            }
            int[] dist = new int[N];
            for (int i = 0; i < N; i++) dist[i] = INF;
            dist[0] = 0;
            for (int i = 0; i < N - 1; i++) {
                foreach (Tuple<int, int, int> e in edges) {
                   if (dist[e.Item1] == INF) continue;
                    dist[e.Item2] = Math.Min(dist[e.Item2], dist[e.Item1] + e.Item3);
                }
            }
            foreach (Tuple<int, int, int> e in edges) {
               if (dist[e.Item1] != INF && dist[e.Item2] > dist[e.Item1] + e.Item3) {
                   Out.WriteLine("YES");
                   return;
               }
            }
            Out.WriteLine("NO");
        }
    }
}
