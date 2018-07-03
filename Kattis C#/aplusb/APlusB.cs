// https://open.kattis.com/problems/aplusb
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace APlusB {
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

        private static int STACK_MEMORY_LIMIT_MB = 500; // TODO CHANGE MEMORY LIMIT FOR STACK

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

        public class Complex {
            private double _real;
            private double _imag;

            public Complex(double real = 0.0, double imag = 0.0) {
                _real = real;
                _imag = imag;
            }

            public Complex(Complex c) {
                _real = c._real;
                _imag = c._imag;
            }

            public double real() {
                return _real;
            }

            public double imag() {
                return _imag;
            }

            public double norm() {
                return _real * _real + _imag * _imag;
            }

            public double abs() {
                return Math.Sqrt(_real * _real + _imag * _imag);
            }

            public Complex conj() {
                return new Complex(_real, -_imag);
            }

            public static Complex operator +(Complex a) {
                return new Complex(a._real, a._imag);
            }
            public static Complex operator -(Complex a) {
                return new Complex(-a._real, -a._imag);
            }

            public static Complex operator + (Complex a, Complex b) {
                return new Complex(a._real + b._real, a._imag + b._imag);
            }

            public static Complex operator -(Complex a, Complex b) {
                return new Complex(a._real - b._real, a._imag - b._imag);
            }

            public static Complex operator *(Complex c, double a) {
                return new Complex(a * c._real, a * c._imag);
            }

            public static Complex operator *(double a, Complex c) {
                return new Complex(a * c._real, a * c._imag);
            }

            public static Complex operator *(Complex a, Complex b) {
                return new Complex(a._real * b._real - a._imag * b._imag, a._real * b._imag + a._imag * b._real);
            }

            public static Complex operator /(Complex c, double a) {
                return new Complex(c._real / a, c._imag / a);
            }

            public static Complex operator /(Complex a, Complex b) {
                double normB = b._real * b._real + b._imag * b._imag;
                return new Complex((a._real * b._real + a._imag * b._imag) / normB, (a._imag * b._real - a._real * b._imag) / normB);
            }

            public static bool operator ==(Complex a, Complex b) {
                return a._real == b._real && a._imag == b._imag;
            }

            public static bool operator !=(Complex a, Complex b) {
                return a._real != b._real || a._imag != b._imag;
            }

            public override bool Equals(object obj) {
                Complex c = obj as Complex;
                if (c == null) return false;
                return _real == c._real && _imag == c._imag;
            }

            public override int GetHashCode() {
                return _real.GetHashCode() * 31 + _imag.GetHashCode();
            }

            public override string ToString() {
                return "(" + _real + ", " + _imag + ")";
            }
        }

        static void fft(List<Complex> a, bool invert) {
            int N = a.Count();
            for (int i = 1, j = 0; i < N; i++) {
                int bit = N >> 1;
                for (; j >= bit; bit >>= 1) j -= bit;
                j += bit;
                if (i < j) {
                    Complex temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
            for (int len = 2; len <= N; len <<= 1) {
                double angle = 2 * Math.PI / len * (invert ? -1 : 1);
                Complex wlen = new Complex(Math.Cos(angle), Math.Sin(angle));
                for (int i = 0; i < N; i += len) {
                    Complex w = new Complex(1);
                    for (int j = 0; j < len / 2; j++) {
                        Complex u = a[i + j];
                        Complex v = a[i + j + len / 2] * w;
                        a[i + j] = u + v;
                        a[i + j + len / 2] = u - v;
                        w *= wlen;
                    }
                }
            }
            if (invert) for (int i = 0; i < N; i++) a[i] /= N;
        }

        static void multiplyPolynomial(List<long> a, List<long> b, out List<long> res) {
            int N = a.Count() + b.Count() - 1;
            while ((N & (N - 1)) != 0) N++;
            List<Complex> fa = new List<Complex>(N), fb = new List<Complex>(N);
            for (int i = 0; i < a.Count(); i++) fa.Add(new Complex(a[i]));
            for (int i = a.Count(); i < N; i++) fa.Add(new Complex(0, 0));
            for (int i = 0; i < b.Count(); i++) fb.Add(new Complex(b[i]));
            for (int i = b.Count(); i < N; i++) fb.Add(new Complex(0, 0));
            fft(fa, false);
            fft(fb, false);
            for (int i = 0; i < N; i++) fa[i] *= fb[i];
            fft(fa, true);
            res = new List<long>(N);
            for (int i = 0; i < N; i++) res.Add((long) Math.Round(fa[i].real()));
            while (res.Count() > 1 && res.Last() == 0) res.RemoveAt(res.Count() - 1);
        }

        public static int MAXA = 50000;

        public static void run(int testCaseNum) {
            int N = In.ReadInt();
            List<long> freq = new List<long>();
            for (int i = 0; i < MAXA * 2 + 1; i++) freq.Add(0);
            long cntZeros = 0;
            for (int i = 0; i < N; i++) {
                int a = In.ReadInt();
                if (a == 0) cntZeros++;
                else freq[a + MAXA]++;
            }
            List<long> freqSq;
            multiplyPolynomial(freq, freq, out freqSq);
            long ans = 0;
            for (int i = 0; i <= MAXA * 2; i++) {
                if (freq[i] == 0) continue;
                long add = 0;
                if (i % 2 == 0) {
                    int half = (i - MAXA) / 2 + MAXA;
                    if (half >= 0 && half <= MAXA * 2) add -= freq[half];
                }
                if (i + MAXA < freqSq.Count()) add += freqSq[i + MAXA];
                ans += add * freq[i];
            }
            if (cntZeros > 0) {
                for (int i = 0; i < MAXA; i++) ans += 2 * cntZeros * (freq[i] * (freq[i] - 1) + freq[2 * MAXA - i] * (freq[2 * MAXA - i] - 1) + freq[i] * freq[2 * MAXA - i]);
                ans += cntZeros * (cntZeros - 1) * (cntZeros - 2);
            }
            Out.WriteLine(ans);
        }
    }
}
