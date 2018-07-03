// http://codeforces.com/contest/863/problem/D
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace EduRound29D {
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

        public class Node {
            public int val, size;
            public double priority;
            public bool rev = false;
            public Node left = null, right = null;

            public Node (int val, double priority, int size) {
                this.val = val;
                this.priority = priority;
                this.size = size;
            }
        }

        static int size(Node x) {
            return x == null ? 0 : x.size;
        }

        static void update(Node x) {
            if (x != null) x.size = 1 + size(x.left) + size(x.right);
        }

        static void push(Node x) {
            if (x != null && x.rev) {
                x.rev = false;
                Node temp = x.left;
                x.left = x.right;
                x.right = temp;
                if (x.left != null) x.left.rev = !x.left.rev;
                if (x.right != null) x.right.rev = !x.right.rev;
            }
        }

        static void merge(ref Node x, Node l, Node r) {
            push(l);
            push(r);
            if (l == null || r == null) {
                x = l ?? r;
            } else if (l.priority > r.priority) {
                merge(ref l.right, l.right, r);
                x = l;
            } else {
                merge(ref r.left, l, r.left);
                x = r;
            }
            update(x);
        }

        static void split(Node x, ref Node l, ref Node r, int ind, int add = 0) {
            if (x == null) {
                l = r = null;
                return;
            }
            push(x);
            int curInd = size(x.left) + add;
            if (ind <= curInd) {
                split(x.left, ref l, ref x.left, ind, add);
                r = x;
            } else {
                split(x.right, ref x.right, ref r, ind, curInd + 1);
                l = x;
            }
            update(x);
        }

        static void reverse(Node x, int l, int r) {
            Node left = null, right = null, mid = null;
            split(x, ref left, ref mid, l);
            split(mid, ref mid, ref right, r - l + 1);
            mid.rev = !mid.rev;
            merge(ref x, left, mid);
            merge(ref x, x, right);
        }

        static void rotateRight(Node x, int l, int r) {
            Node left = null, right = null, mid = null, end = null;
            split(x, ref left, ref mid, l);
            split(mid, ref mid, ref right, r - l + 1);
            split(mid, ref mid, ref end, r - l);
            merge(ref x, left, end);
            merge(ref x, x, mid);
            merge(ref x, x, right);
        }

        static int getValue(Node x, int i) {
            Node left = null, right = null, mid = null;
            split(x, ref left, ref mid, i);
            split(mid, ref mid, ref right, 1);
            int ret = mid.val;
            merge(ref x, left, mid);
            merge(ref x, x, right);
            return ret;
        }

        static int N, M, Q;

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            N = In.ReadInt();
            Q = In.ReadInt();
            M = In.ReadInt();
            Random rand = new Random();
            Node root = null;
            for (int i = 0; i < N; i++) {
                Node cur = new Node(In.ReadInt(), rand.NextDouble(), 1);
                merge(ref root, root, cur);
            }
            for (int i = 0; i < Q; i++) {
                if (In.ReadInt() == 1) rotateRight(root, In.ReadInt() - 1, In.ReadInt() - 1);
                else reverse(root, In.ReadInt() - 1, In.ReadInt() - 1);
            }
            for (int i = 0; i < M; i++) Out.Write(getValue(root, In.ReadInt() - 1) + " ");
            Out.WriteLine();
        }
    }
}
