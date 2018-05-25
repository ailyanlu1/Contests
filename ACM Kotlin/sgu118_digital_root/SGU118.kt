// http://codeforces.com/problemsets/acmsguru/problem/99999/118
import java.io.*
import java.math.*
import java.util.*

class Reader {
    private val In: BufferedReader
    private var st: StringTokenizer? = null
    constructor(inputStream: InputStream) {
        In = BufferedReader(InputStreamReader(inputStream))
    }
    constructor(fileName: String) {
        In = BufferedReader(FileReader(fileName))
    }
    fun next(): String {
        while (st == null || !st!!.hasMoreTokens()) {
            st = StringTokenizer(In.readLine().trim())
        }
        return st!!.nextToken()
    }
    fun nextLine(): String {
        st = null
        return In.readLine()
    }
    fun nextChar(): Char = next()[0]
    fun nextDouble(): Double = next().toDouble()
    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long  = next().toLong()
    fun close() : Unit = In.close();
} // Reader class

val INPUT_FILE_NAME = "input.txt"
val OUTPUT_FILE_NAME = "output.txt"

val In: Reader = Reader(System.`in`)
val Out: PrintWriter = PrintWriter(System.out)
//val In: Reader = Reader(INPUT_FILE_NAME)
//val Out: PrintWriter = PrintWriter(OUTPUT_FILE_NAME)

var NUM_OF_TEST_CASES: Int = 1
val flush: Boolean = false

fun main(args : Array<String>) {
    NUM_OF_TEST_CASES = In.nextInt()
    for (i in 1..NUM_OF_TEST_CASES) {
        run(i)
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

tailrec fun f(n: Int): Int {
    if (n < 10) return n;
    var sum = 0
    var cur = n
    while (cur > 0) {
        sum += cur % 10
        cur /= 10
    }
    return f(sum)
}

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var A = IntArray(N)
    var ans = 0
    for (i in 0 until N) A[i] = In.nextInt()
    for (i in N-1 downTo 0) ans = f((ans + 1) * f(A[i]))
    Out.println(ans)
}
