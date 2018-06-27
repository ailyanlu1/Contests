using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace NCCO4D1P2 {
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
        
        static int MOD = 100000000;

        public static void run(int testCaseNum) {
            int R = In.ReadInt(), C = In.ReadInt();
            int[] row = new int[R];
            List<int> check = new List<int>();
            for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (In.ReadInt() == 1) row[i] |= 1 << j;
            for (int i = 0; i < (1 << C); i++) {
                if (C == 1) check.Add(i);
                for (int j = 1; j < C; j++) {
                    if (((i >> j) & 1) == 1 && ((i >> (j - 1)) & 1) == 1) break;
                    if (j == C - 1) check.Add(i);
                }
            }
            int[,] dp = new int[2, check.Count()];
            for (int j = 0; j < check.Count(); j++) dp[0, j] = (check[j] & row[0]) == check[j] ? 1 : 0;
            for (int i = 1; i < R; i++) for (int j = 0; j < check.Count() && (dp[i % 2, j] = 0) == 0; j++) if ((check[j] & row[i]) == check[j])
                for (int k = 0; k < check.Count(); k++) if ((check[j] & check[k]) == 0) dp[i % 2, j] = (dp[i % 2, j] + dp[1 - i % 2, k]) % MOD;
            int ans = 0;
            for (int j = 0; j < check.Count(); j++) ans = (ans + dp[(R - 1) % 2, j]) % MOD;
            Out.WriteLine(ans);
        }
    }
}
