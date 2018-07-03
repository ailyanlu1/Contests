// http://codeforces.com/contest/985/problem/F
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace EduRound44F {
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

            public string ReadLine() { return reader.ReadLine(); }

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

        private static int STACK_MEMORY_LIMIT_MB = 50; // TODO CHANGE MEMORY LIMIT FOR STACK

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

        static int N, M;
        static string S;
        static long[,] hash1, hash2;
        static long[] pow1, pow2;
        static List<int>[] ind;
        static long BASE1 = 10007, MOD1 = (long) (1e9 + 7), BASE2 = 137, MOD2 = (long) (1e9 + 9);

        static Tuple<long, long> h(int l, int r, int i) {
            return new Tuple<long, long>(((hash1[r, i] - hash1[l - 1, i] * pow1[r - l + 1]) % MOD1 + MOD1) % MOD1,
                ((hash2[r, i] - hash2[l - 1, i] * pow2[r - l + 1]) % MOD2 + MOD2) % MOD2);
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            S = "$" + In.ReadToken();
            hash1 = new long[N + 1, 26];
            hash2 = new long[N + 1, 26];
            pow1 = new long[N + 1];
            pow2 = new long[N + 1];
            ind = new List<int>[26];
            for (int i = 0; i < 26; i++) ind[i] = new List<int>();
            pow1[0] = pow2[0] = 1;
            for (int i = 1; i <= N; i++) {
                pow1[i] = pow1[i - 1] * BASE1 % MOD1;
                pow2[i] = pow2[i - 1] * BASE2 % MOD2;
            }
            for (int i = 1; i <= N; i++) {
                for (int j = 0; j < 26; j++) {
                    hash1[i, j] = hash1[i - 1, j] * BASE1 % MOD1;
                    hash2[i, j] = hash2[i - 1, j] * BASE2 % MOD2;
                }
                ind[S[i] - 'a'].Add(i);
                hash1[i, S[i] - 'a'] = (hash1[i, S[i] - 'a'] + 1) % MOD1;
                hash2[i, S[i] - 'a'] = (hash2[i, S[i] - 'a'] + 1) % MOD2;
            }
            for (int i = 0; i < M; i++) {
                int x = In.ReadInt(), y = In.ReadInt(), L = In.ReadInt();
                bool isomorphic = true;
                for (int j = 0; j < 26; j++) {
                    int lo = 0, hi = ind[j].Count(), mid;
                    while (lo < hi) {
                        mid = lo + (hi - lo) / 2;
                        if (x <= ind[j][mid]) hi = mid;
                        else lo = mid + 1;
                    }
                    if (lo == ind[j].Count() || ind[j][lo] - x >= L) continue;
                    int z = S[y + ind[j][lo] - x] - 'a';
                    if (!h(x, x + L - 1, j).Equals(h(y, y + L - 1, z))) {
                        isomorphic = false;
                        break;
                    }
                }
                Out.WriteLine(isomorphic ? "YES" : "NO");
            }
        }
    }
}
