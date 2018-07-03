using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace CCO18P4 {
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

        // TODO CODE GOES IN THIS METHOD
        public static void run(int testCaseNum) {
            int R = In.ReadInt(), C = In.ReadInt(), K = In.ReadInt();
            int loR = 1, hiR = R, midR, loC = 1, hiC = C, midC, cnt = 0, aVal, bVal, cVal, ans = int.MaxValue;
            Tuple<int, int> aKey, bKey, cKey;
            Dictionary<Tuple<int, int>, int> dict = new Dictionary<Tuple<int, int>, int>();
            while (loR < hiR || loC < hiC) {
                midR = loR + (hiR - loR) / 2;
                midC = loC + (hiC - loC) / 2;
                aKey = new Tuple<int, int>(midR, midC);
                if (dict.ContainsKey(aKey)) {
                    aVal = dict[aKey];
                } else {
                    if (++cnt > K) throw new Exception(); 
                    Out.WriteLine("? {0} {1}", midR, midC);
                    Out.Flush();
                    dict[aKey] = aVal = In.ReadInt();
                }
                if (midR < hiR) {
                    bKey = new Tuple<int, int>(midR + 1, midC);
                    if (dict.ContainsKey(bKey)) {
                        bVal = dict[bKey];
                    } else {
                        if (++cnt > K) throw new Exception();
                        Out.WriteLine("? {0} {1}", midR + 1, midC);
                        Out.Flush();
                        dict[bKey] = bVal = In.ReadInt();
                    }
                } else {
                    bVal = int.MaxValue;
                }
                if (midC < hiC) {
                    cKey = new Tuple<int, int>(midR, midC + 1);
                    if (dict.ContainsKey(cKey)) {
                        cVal = dict[cKey];
                    } else {
                        if (++cnt > K) throw new Exception();
                        Out.WriteLine("? {0} {1}", midR, midC + 1);
                        Out.Flush();
                        dict[cKey] = cVal = In.ReadInt();
                    }
                } else {
                    cVal = int.MaxValue;
                }
                ans = Math.Min(ans, Math.Min(aVal, Math.Min(bVal, cVal)));
                if (aVal == bVal && bVal == cVal) break;
                if (aVal >= bVal) loR = midR + 1;
                else hiR = midR;
                if (aVal >= cVal) loC = midC + 1;
                else hiC = midC;
            }
            aKey = new Tuple<int, int>(loR, loC);
            if (!dict.ContainsKey(aKey)) {
                if (++cnt > K) throw new Exception();
                Out.WriteLine("? {0} {1}", loR, loC);
                Out.Flush();
                dict[aKey] = In.ReadInt();
            }
            ans = Math.Min(ans, dict[aKey]);
            Out.WriteLine("! {0}", ans);
        }
    }
}
