// https://open.kattis.com/problems/trainsorting
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
    fun close() : Unit = In.close()
} // Reader class

val INPUT_FILE_NAME = "input.txt"
val OUTPUT_FILE_NAME = "output.txt"

val In: Reader = Reader(System.`in`)
val Out: PrintWriter = PrintWriter(System.out)
//val In: Reader = Reader(INPUT_FILE_NAME)
//val Out: PrintWriter = PrintWriter(OUTPUT_FILE_NAME)

var NUM_OF_TEST_CASES: Int = 1
val crash: Boolean = true
val flush: Boolean = false

fun main(args: Array<String>) {
    for (i in 1..NUM_OF_TEST_CASES) {
        try {
            run(i)
        } catch (e : Exception) {
            Out.println("Exception thrown on test case $i")
            e.printStackTrace(Out)
            Out.flush()
            if (crash) throw Exception()
        }
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var A = IntArray(N, {In.nextInt()})
    var dp = Array<IntArray>(2, {IntArray(N)})
    for (i in (N - 1) downTo 0) {
        dp[0][i] = 1
        for (j in i + 1 until N) if (A[i] < A[j]) dp[0][i] = Math.max(dp[0][i], dp[0][j] + 1)
    }
    for (i in (N - 1) downTo 0) {
        dp[1][i] = 1
        for (j in i + 1 until N) if (A[i] > A[j]) dp[1][i] = Math.max(dp[1][i], dp[1][j] + 1)
    }
    Out.println((0 until N).fold(0) { ans, i -> Math.max(ans, dp[0][i] + dp[1][i] - 1)})
}
