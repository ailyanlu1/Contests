// https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/modulo-fermats-theorem-728658be/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;
 
namespace JulyCircuits18P3 {
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
 
        private static int STACK_MEMORY_LIMIT_MB = 10; // TODO CHANGE MEMORY LIMIT FOR STACK
 
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
        
        static long powMod(long b, int pow, int mod) {
            long ret = 1;
            while (pow > 0) {
                if (pow % 2 == 1) ret = ret * b % mod;
                pow /= 2;
                b = b * b % mod;
            }
            return ret;
        }
 
        public static void run(int testCaseNum) {
            int P = In.ReadInt();
            long L = In.ReadLong();
            int sqrtP = (int) Math.Sqrt(P);
            int[] cnt = new int[P], S = new int[P + 1], prime = new int[P];
            for (int i = 1; i < P - 1; i++) cnt[i] = 1;
            for (int i = 2; i < P - 1; i++) {
                if (cnt[i] == 1 && (P - 1) % i == 0) {
                    S[1] = i;
                    for (int j = 2; j < P; j++) {
                        if (P <= 10000 || prime[j] != i) {
                            int x = (int) powMod(j, i, P);
                            S[x] = i;
                            if ((x > 1 && S[x - 1] == i) || S[x + 1] == i) break;
                            if (P > 10000 && j <= sqrtP) {
                                bool esc = false;
                                for (int k = j * j; k < P; k += j) prime[k] = i;
                                if (esc) break;
                            }
                        }
                        if (j == P - 1) for (int k = i; k < P - 1; k += i) cnt[k] = 0;
                    }
                }
                cnt[i] += cnt[i - 1];
            }
            Out.WriteLine(cnt[(int) (L % (P - 1))] + L / (P - 1) * cnt[P - 2]);
        }
    }
}
