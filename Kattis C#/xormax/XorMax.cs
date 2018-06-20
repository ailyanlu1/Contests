// https://open.kattis.com/problems/xormax
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace XorMax {
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
        
        public static long[] shift = {1L << 1, 1L << 2, 1L << 4, 1L << 8, 1L << 16, 1L << 32};
        
        public static int bitLength(long x) {
            if (x == 0) return 0;
            int ret = 1;
            for (int i = shift.Length - 1, j = 32; i >= 0; i--, j /= 2) {
                if (x / shift[i] > 0) {
                    x /= shift[i];
                    ret += j;
                }
            }
            return ret;
        }

        public static void run(int testCaseNum) {
            int N = In.ReadInt();
            List<long>[] len = new List<long>[64];
            for (int i = 0; i < 64; i++) len[i] = new List<long>();
            for (int i = 0; i < N; i++) {
                long a = In.ReadLong();
                len[bitLength(a)].Add(a);
            }
            List<long> check = new List<long>();
            for (int i = 63; i >= 0; i--) {
                if (len[i].Count() == 0) continue;
                long x = len[i][0];
                for (int j = 1; j < len[i].Count(); j++) {
                    long y = x ^ len[i][j];
                    if (y > 0) len[bitLength(y)].Add(y);
                }
                check.Add(x);
            }
            long ans = 0;
            foreach (long x in check) ans = Math.Max(ans, ans ^ x);
            Out.WriteLine(ans);
        }
    }
}
