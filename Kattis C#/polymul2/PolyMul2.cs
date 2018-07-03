// https://open.kattis.com/problems/polymul2
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using static System.Diagnostics.Debug;

namespace PolyMul2 {
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

        static void multiplyPolynomial(List<int> a, List<int> b, out List<int> res) {
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
            res = new List<int>(N);
            for (int i = 0; i < N; i++) res.Add((int) Math.Round(fa[i].real()));
            while (res.Count() > 1 && res.Last() == 0) res.RemoveAt(res.Count() - 1);
        }

        public static void run(int testCaseNum) {
            List<int> A = new List<int>();
            List<int> B = new List<int>();
            List<int> res;
            int N = In.ReadInt();
            for (int i = 0; i <= N; i++) A.Add(In.ReadInt());
            int M = In.ReadInt();
            for (int i = 0; i <= M; i++) B.Add(In.ReadInt());
            multiplyPolynomial(A, B, out res);
            Out.WriteLine(res.Count() - 1);
            for (int i = 0; i < res.Count(); i++) {
                if (i > 0) Out.Write(" ");
                Out.Write(res[i]);
            }
            Out.WriteLine();
        }
    }
}
