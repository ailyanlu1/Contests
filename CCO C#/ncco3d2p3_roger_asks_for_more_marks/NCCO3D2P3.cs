using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace NCCO3D2P3 {
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

        public class Point : IComparable<Point> {
            public long x, y;

            public Point(long x, long y) {
                this.x = x;
                this.y = y;
            }

            public static Point operator + (Point a, Point b) {
                return new Point(a.x + b.x, a.y + b.y);
            }

            public static Point operator - (Point a, Point b) {
                return new Point(a.x - b.x, a.y - b.y);
            }

            public static long operator * (Point a, Point b) {
                return a.x * b.y - a.y * b.x;
            }

            public static long area2(Point a, Point b, Point c) {
                return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
            }

            public int CompareTo(Point p) {
                long a2 = p.x * y - p.y * x;
                if (a2 > 0) return 1;
                else if (a2 < 0) return -1;
                return 0;
            }
        }

        public static void run(int testCaseNum) {
            int N = In.ReadInt();
            Point[] P = new Point[N];
            Point[] H = new Point[N];
            Point[] lo = new Point[N];
            Point all = new Point(0, 0);
            List<int> ans = new List<int>();
            for (int i = 0; i < N; i++) {
                int y = In.ReadInt(), x = In.ReadInt();
                all += (P[i] = new Point(x, y));
            }
            Array.Sort(P);
            int j = 0;
            Point cur = new Point(0, 0);
            for (int i = N - 1; i > 0; i--) {
                while (j > 0 && H[j - 1].y <= P[i].y) j--;
                while (j >= 2 && Point.area2(H[j - 2], H[j - 1], P[i]) >= 0) j--;
                cur += (H[j++] = P[i]);
                while (j >= 2 && cur * (H[j - 2] - H[j - 1]) <= 0) j--;
                lo[i - 1] = H[j - 1];
            }
            cur = all;
            j = 0;
            for (int i = 0; i < N - 1; i++) {
                while (j > 0 && H[j - 1].x >= P[i].x) j--;
                while (j >= 2 && Point.area2(H[j - 2], H[j - 1], P[i]) >= 0) j--;
                cur -= (H[j++] = P[i]);
                while (j >= 2 && cur * (H[j - 2] - H[j - 1]) >= 0) j--;
                if (cur * (lo[i] - H[j - 1]) < 0) ans.Add(i);
            }
            Out.WriteLine(ans.Count());
            foreach (int i in ans) Out.WriteLine(i + 1);
        }
    }
}
