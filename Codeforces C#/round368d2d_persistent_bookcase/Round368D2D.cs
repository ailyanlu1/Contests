// http://codeforces.com/contest/707/problem/D
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace Round368D2D {
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

        private static int MEMORY_LIMIT_MB = 10;

        public static void Main(string[] args) {
            Thread T = new Thread(new ThreadStart(start), MEMORY_LIMIT_MB * 1000000);
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

        static int N, M, K, Q;

        class Node {
            public Node left = null, right = null;
            public int val = 0;
            public bool flip = false;

            public Node() { }

            public Node(Node n) {
                left = n.left;
                right = n.right;
                val = n.val;
                flip = n.flip;
            }
        }

        static Node[] nodes;

        static Node build(int cL, int cR) {
            if (cL == cR) return new Node();
            int m = cL + (cR - cL) / 2;
            Node ret = new Node();
            ret.left = build(cL, m);
            ret.right = build(m + 1, cR);
            return ret;
        }

        static Node update(Node cur, int cL, int cR, int ind, int val, bool flip) {
            if (cL > ind || cR < ind) return cur;
            flip ^= cur.flip;
            Node ret = new Node(cur);
            if (cL == cR) {
                if (flip) ret.val = 1 - val;
                else ret.val = val;
                return ret;
            }
            int m = cL + (cR - cL) / 2;
            if (ret.left == null) ret.left = new Node();
            if (ret.right == null) ret.right = new Node();
            ret.left = update(ret.left, cL, m, ind, val, flip);
            ret.right = update(ret.right, m + 1, cR, ind, val, flip);
            ret.val = 0;
            if (ret.left.flip) ret.val += (m - cL + 1) - ret.left.val;
            else ret.val += ret.left.val;
            if (ret.right.flip) ret.val += (cR - m) - ret.right.val;
            else ret.val += ret.right.val;
            return ret;
        }

        static Node flipRange(Node cur, int cL, int cR, int l, int r) {
            if (cL > r || cR < l) return cur;
            Node ret = new Node(cur);
            if (cL >= l && cR <= r) {
                ret.flip = !ret.flip;
                return ret;
            }
            int m = cL + (cR - cL) / 2;
            if (ret.left == null) ret.left = new Node();
            if (ret.right == null) ret.right = new Node();
            ret.left = flipRange(ret.left, cL, m, l, r);
            ret.right = flipRange(ret.right, m + 1, cR, l, r);
            ret.val = 0;
            if (ret.left.flip) ret.val += (m - cL + 1) - ret.left.val;
            else ret.val += ret.left.val;
            if (ret.right.flip) ret.val += (cR - m) - ret.right.val;
            else ret.val += ret.right.val;
            return ret;
        }

        static int query(Node root, int cL, int cR) {
            if (root.flip) return (cR - cL + 1) - root.val;
            else return root.val;
        }

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            M = In.ReadInt();
            Q = In.ReadInt();
            K = N * M;
            nodes = new Node[Q + 1];
            nodes[0] = build(0, K - 1);
            for (int i = 1; i <= Q; i++) {
                int t = In.ReadInt();
                if (t == 1) {
                    int ind = (In.ReadInt() - 1) * M + (In.ReadInt() - 1);
                    nodes[i] = update(nodes[i - 1], 0, K - 1, ind, 1, false);
                } else if (t == 2) {
                    int ind = (In.ReadInt() - 1) * M + (In.ReadInt() - 1);
                    nodes[i] = update(nodes[i - 1], 0, K - 1, ind, 0, false);
                } else if (t == 3) {
                    int l = (In.ReadInt() - 1) * M;
                    int r = l + M - 1;
                    nodes[i] = flipRange(nodes[i - 1], 0, K - 1, l, r);
                } else {
                    nodes[i] = nodes[In.ReadInt()];
                }
                Out.WriteLine(query(nodes[i], 0, K - 1));
            }
        }
    }
}
