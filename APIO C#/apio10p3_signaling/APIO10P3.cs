using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace APIO10P3 {
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

        public class Point : IComparable<Point> {
            public double x, y, polarAngle;

            public Point(double x, double y) {
                this.x = x;
                this.y = y;
                this.polarAngle = Math.Atan2(y, x);
                if (this.polarAngle < 0) this.polarAngle += 2 * Math.PI;
            }

            public int CompareTo(Point p) {
                return polarAngle.CompareTo(p.polarAngle);
            }

            public static Point operator - (Point a, Point b) {
                return new Point(a.x - b.x, a.y - b.y);
            }

            public static double operator * (Point a, Point b) {
                return a.x * b.y - a.y * b.x;
            }
        }

        public static void run(int testCaseNum) {
            int N;
            N = In.ReadInt();
            Point[] P = new Point[N];
            Point[] Q = new Point[N - 1];
            long ans = 0;
            for (int i = 0; i < N; i++) P[i] = new Point(In.ReadInt(), In.ReadInt());
            for (int i = 0; i < N; i++) {
                Point temp = P[0];
                P[0] = P[i];
                P[i] = temp;
                for (int j = 0; j < N - 1; j++) Q[j] = P[j + 1] - P[0];
                Array.Sort(Q);
                int k = 0;
                for (int j = 0; j < N - 1; j++) {
                    k = Math.Max(k, j + 1);
                    while (k < 2 * (N - 1) && Q[j] * Q[k % (N - 1)] > 0) k++;
                    ans += (k - j - 1) * (k - j - 2) / 2;
                }
            }
            ans -= 1L * N * (N - 1) * (N - 2) * (N - 3) / 12;
            Out.WriteLine("{0:F3}", 6.0 * ans / (1L * N * (N - 1) * (N - 2)) + 3);
        }
    }
}
