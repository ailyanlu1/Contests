using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using static System.Diagnostics.Debug;

namespace CCC18S3 {
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

        static int[,] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            int N = In.ReadInt();
            int M = In.ReadInt();
            bool[,] vis = new bool[N, M];
            char[,] grid = new char[N, M];
            int[,] dist = new int[N, M];
            Tuple<int, int> start = new Tuple<int, int>(0, 0);
            for (int i = 0; i < N; i++) {
                string s = In.ReadLine();
                for (int j = 0; j < M; j++) {
                    grid[i, j] = s[j];
                    if (grid[i, j] == 'S') {
                        start = new Tuple<int, int>(i, j);
                        grid[i, j] = '.';
                    }
                    dist[i, j] = -1;
                    vis[i, j] = false;
                }
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (grid[i, j] == 'C') {
                        for (int k = i + 1; k < N; k++) {
                            if (grid[k, j] == 'W') break;
                            if (grid[k, j] == '.') {
                                grid[k, j] = 'X';
                                vis[k, j] = true;
                            }
                        }
                        for (int k = i - 1; k >= 0; k--) {
                            if (grid[k, j] == 'W') break;
                            if (grid[k, j] == '.') {
                                grid[k, j] = 'X';
                                vis[k, j] = true;
                            }
                        }
                        for (int k = j + 1; k < M; k++) {
                            if (grid[i, k] == 'W') break;
                            if (grid[i, k] == '.') {
                                grid[i, k] = 'X';
                                vis[i, k] = true;
                            }
                        }
                        for (int k = j - 1; k >= 0; k--) {
                            if (grid[i, k] == 'W') break;
                            if (grid[i, k] == '.') {
                                grid[i, k] = 'X';
                                vis[i, k] = true;
                            }
                        }
                        vis[i, j] = true;
                    } else if (grid[i, j] == 'W') {
                        vis[i, j] = true;
                    }
                }
            }
            Queue<Tuple<int, int>> q = new Queue<Tuple<int, int>>();
            dist[start.Item1, start.Item2] = 0;
            vis[start.Item1, start.Item2] = true;
            q.Enqueue(start);
            while (q.Count() > 0) {
                Tuple<int, int> cur = q.Dequeue();
                if (grid[cur.Item1, cur.Item2] == '.') {
                    for (int i = 0; i < 4; i++) {
                        Tuple<int, int> next = new Tuple<int, int>(cur.Item1 + dir[i, 0], cur.Item2 + dir[i, 1]);
                        bool loop = false;
                        HashSet<Tuple<int, int>> vis2 = new HashSet<Tuple<int, int>>();
                        while (grid[next.Item1, next.Item2] != '.') {
                            if (vis2.Contains(next)) {
                                loop = true;
                                break;
                            }
                            vis2.Add(new Tuple<int, int>(next.Item1, next.Item2));
                            int r = next.Item1, c = next.Item2;
                            switch (grid[r, c]) {
                                case 'U':
                                    r--;
                                    break;
                                case 'D':
                                    r++;
                                    break;
                                case 'L':
                                    c--;
                                    break;
                                case 'R':
                                    c++;
                                    break;
                            }
                            next = new Tuple<int, int>(r, c);
                        }
                        if (!vis[next.Item1, next.Item2] && !loop) {
                            dist[next.Item1, next.Item2] = dist[cur.Item1, cur.Item2] + 1;
                            vis[next.Item1, next.Item2] = true;
                            q.Enqueue(new Tuple<int, int>(next.Item1, next.Item2));
                        }
                    }
                }
            }
            grid[start.Item1, start.Item2] = 'S';
            for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) if (grid[i, j] == '.' || grid[i, j] == 'X') Out.WriteLine(dist[i, j]);
        }
    }
}
