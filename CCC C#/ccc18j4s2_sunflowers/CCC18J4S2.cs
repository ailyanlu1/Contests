using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using static System.Diagnostics.Debug;

namespace CCC18J4S2 {
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

        static int N;
        static int[,] A;

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            A = new int[N, N];
            for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) A[i, j] = In.ReadInt();
            for (int k = 0; k < 4; k++) {
                rotate();
                if (check()) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) Out.Write(A[i, j] + " ");
                        Out.WriteLine();
                    }
                }
            }
        }

        static void rotate() {
            for (int i = 0; i < N / 2; i++) {
                for (int j = i; j < N - i - 1; j++) {
                    int temp = A[i, j];
                    A[i, j] = A[j, N - i - 1];
                    A[j, N - i - 1] = A[N - i - 1, N - j - 1];
                    A[N - i - 1, N - j - 1] = A[N - j - 1, i];
                    A[N - j - 1, i] = temp;
                }
            }
        }

        static bool check() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (i > 0 && A[i, j] <= A[i - 1, j]) return false;
                    if (j > 0 && A[i, j] <= A[i, j - 1]) return false;
                }
            }
            return true;
        }
    }
}
