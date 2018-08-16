using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace APIO14P1 {
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
            for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
                try {
                    run(i);
                } catch (Exception e) {
                    Console.Error.WriteLine("Exception thrown on test case " + i);
                    Console.Error.WriteLine(e.StackTrace);
                    Out.Flush();
                    if (crash) throw new Exception();
                }
                if (flush) Out.Flush();
            }
            In.Close();
            Out.Close();
        }

        static int N, last, K;
        static String S;
        static int[] s, len, link, occ;
        static int[,] to;

        static void init() {
            s = new int[N + 1];
            len = new int[N + 2];
            link = new int[N + 2];
            occ = new int[N + 2];
            to = new int[N + 1, 26];
            s[0] = len[1] = -1;
            link[0] = 1;
            K = 2;
            for (int i = 0; i < N; i++) s[i + 1] = S[i] - 'a';
        }

        static int getLink(int x, int i) {
            while (s[i - 1 - len[x]] != s[i]) x = link[x];
            return x;
        }

        static void compute() {
            for (int i = 1; i <= N; i++) {
                last = getLink(last, i);
                if (to[last, s[i]] == 0) {
                    len[K] = len[last] + 2;
                    link[K] = to[getLink(link[last], i), s[i]];
                    to[last, s[i]] = K++;
                }
                occ[last = to[last, s[i]]]++;
            }
        }

        static long solve() {
            for (int i = K - 1; i >= 2; i--) occ[link[i]] += occ[i];
            long ans = 0;
            for (int i = 2; i < K; i++) ans = Math.Max(ans, (long) occ[i] * len[i]);
            return ans;
        }

        public static void run(int testCaseNum) {
            S = In.ReadToken();
            N = S.Length;
            init();
            compute();
            Out.WriteLine(solve());
        }
    }
}
