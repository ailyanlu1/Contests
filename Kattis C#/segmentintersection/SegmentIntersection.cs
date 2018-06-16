// https://open.kattis.com/problems/segmentintersection
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace SegmentIntersection {
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
        
        public static double EPS = 1e-9;
        
        public class Point : IComparable<Point> {
            public double x, y;
            
            public Point(double x, double y) {
                this.x = x;
                this.y = y;
            }

            public int CompareTo(Point other) {
                return x == other.x ? y.CompareTo(other.y) : x.CompareTo(other.x);
            }
            
            public double distTo(Point other) {
                double dx = x - other.x, dy = y - other.y;
                return Math.Sqrt(dx * dx + dy * dy);
            }

            public static int ccw(Point a, Point b, Point c) {
                double area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
                if (area2 < -EPS) return -1;
                else if (area2 > EPS) return +1;
                else return  0;
            }
            
            public bool onSegment(Point p, Point q) {
                return x <= Math.Max(p.x, q.x) + EPS && x >= Math.Min(p.x, q.x) - EPS && y <= Math.Max(p.y, q.y) + EPS && y >= Math.Min(p.y, q.y) - EPS;
            }
            
            public static bool intersects(Point p1, Point q1, Point p2, Point q2) {
                int o1 = ccw(p1, q1, p2);
                int o2 = ccw(p1, q1, q2);
                int o3 = ccw(p2, q2, p1);
                int o4 = ccw(p2, q2, q1);
                if (o1 != o2 && o3 != o4) return true;
                if (o1 == 0 && p2.onSegment(p1, q1)) return true;
                if (o2 == 0 && q2.onSegment(p1, q1)) return true;
                if (o3 == 0 && p1.onSegment(p2, q2)) return true;
                if (o4 == 0 && q1.onSegment(p2, q2)) return true;
                return false;
            }
            
            public static Point intersection(Point p1, Point q1, Point p2, Point q2) {
                double A1 = q1.y - p1.y;
                double B1 = p1.x - q1.x;
                double C1 = A1 * p1.x + B1 * p1.y;
                double A2 = q2.y - p2.y;
                double B2 = p2.x - q2.x;
                double C2 = A2 * p2.x + B2 * p2.y;
                double det = A1 * B2 - A2 * B1;
                if (Math.Abs(det) <= EPS) return null;
                return new Point((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);
            }
        }
        
        public static void run(int testCaseNum) {
            Point[] P = new Point[4];
            for (int i = 0; i < 4; i++) P[i] = new Point(In.ReadInt(), In.ReadInt());
            if (!Point.intersects(P[0], P[1], P[2], P[3])) Out.WriteLine("none");
            else {
                Point ans = Point.intersection(P[0], P[1], P[2], P[3]);
                if (ans == null) {
                    if (P[0].distTo(P[1]) <= EPS) Out.WriteLine("{0:F2} {1:F2}", P[0].x, P[0].y);
                    else if (P[2].distTo(P[3]) <= EPS) Out.WriteLine("{0:F2} {1:F2}", P[1].x, P[1].y);
                    else {
                        Array.Sort(P); 
                        Out.Write("{0:F2} {1:F2}", P[1].x, P[1].y);
                        if (P[1].distTo(P[2]) > EPS) Out.Write(" {0:F2} {1:F2}", P[2].x, P[2].y);
                        Out.WriteLine();
                    }
                } else {
                    Out.WriteLine("{0:F2} {1:F2}", ans.x, ans.y);
                }
            }
        }
    }
}
