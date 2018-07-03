// https://open.kattis.com/problems/segmentdistance
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace SegmentDistance {
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
        
        public class Point {
            public double x, y;
            
            public Point(double x, double y) {
                this.x = x;
                this.y = y;
            }
        }
        
        public static int ccw(Point a, Point b, Point c) {
            double area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
            if (area2 < -EPS) return -1;
            else if (area2 > EPS) return +1;
            else return  0;
        }
        
        public static bool onSegment(Point a, Point p, Point q) {
            return a.x <= Math.Max(p.x, q.x) + EPS && a.x >= Math.Min(p.x, q.x) - EPS && a.y <= Math.Max(p.y, q.y) + EPS && a.y >= Math.Min(p.y, q.y) - EPS;
        }
        
        public static bool intersects(Point p1, Point q1, Point p2, Point q2) {
            int o1 = ccw(p1, q1, p2);
            int o2 = ccw(p1, q1, q2);
            int o3 = ccw(p2, q2, p1);
            int o4 = ccw(p2, q2, q1);
            if (o1 != o2 && o3 != o4) return true;
            if (o1 == 0 && onSegment(p2, p1, q1)) return true;
            if (o2 == 0 && onSegment(q2, p1, q1)) return true;
            if (o3 == 0 && onSegment(p1, p2, q2)) return true;
            if (o4 == 0 && onSegment(q1, p2, q2)) return true;
            return false;
        }
        
        public static double dist(Point a, Point p, Point q) {
            double dxap = a.x - p.x;
            double dyap = a.y - p.y;
            double dxpq = q.x - p.x;
            double dypq = q.y - p.y;
            double dot = dxap * dxpq + dyap * dypq;
            double len = dxpq * dxpq + dypq * dypq;
            double d = -1;
            if (len > EPS) d = dot / len;
            double xx, yy;
            if (d < 0) {
                xx = p.x;
                yy = p.y;
            } else if (d > 1) {
                xx = q.x;
                yy = q.y;
            } else {
                xx = p.x + d * dxpq;
                yy = p.y + d * dypq;
            }
            double dx = a.x - xx;
            double dy = a.y - yy;
            return Math.Sqrt(dx * dx + dy * dy);
        }

        public static void run(int testCaseNum) {
            Point[] P = new Point[4];
            for (int i = 0; i < 4; i++) P[i] = new Point(In.ReadInt(), In.ReadInt());
            if (intersects(P[0], P[1], P[2], P[3])) Out.WriteLine("0.00");
            else Out.WriteLine("{0:F2}", Math.Min(Math.Min(dist(P[0], P[2], P[3]), dist(P[1], P[2], P[3])), Math.Min(dist(P[2], P[0], P[1]), dist(P[3], P[0], P[1]))));
        }
    }
}