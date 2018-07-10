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
        while (st == null || !st!!.hasMoreTokens()) st = StringTokenizer(In.readLine().trim())
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
    fun close(): Unit = In.close()
}

var NUM_OF_TEST_CASES: Int = 1 // TODO CHANGE NUMBER OF TEST CASES

// TODO CHANGE FILE NAMES
val INPUT_FILE_NAME = "input.txt"
val OUTPUT_FILE_NAME = "output.txt"

val crash: Boolean = true
val flush: Boolean = false

val In: Reader = Reader(System.`in`)
val Out: PrintWriter = PrintWriter(System.out)
//val In: Reader = Reader(INPUT_FILE_NAME)
//val Out: PrintWriter = PrintWriter(OUTPUT_FILE_NAME)

fun main(args: Array<String>) {
    for (i in 1..NUM_OF_TEST_CASES) {
        try {
            run(i)
        } catch (e : Exception) {
            System.err.println("Exception thrown on test case $i")
            e.printStackTrace(System.err)
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
    var E = In.nextInt()
    var A = IntArray(N)
    var B = IntArray(N)
    var K = E
    for (i in 1 until N) {
        A[i] = In.nextInt()
        B[i] = In.nextInt()
        K = Math.max(K, A[i] + B[i])
    }
    var dp = Array(2, {IntArray(K + 1, {Math.min(it, E - 1)})})
    for (i in 1 until N)
        for (j in 0..K)
            dp[i % 2][j] = Math.max((if (j >= A[i] + B[i]) dp[1 - i % 2][j] - j
                                     else if (j >= B[i]) dp[1 - i % 2][j - B[i]] + B[i] - j
                                     else Math.max(dp[1 - i % 2][j + A[i]] - j, dp[1 - i % 2][A[i] - 1])) + j,
                                     if (j == 0) 0 else dp[i % 2][j - 1])
    Out.println(dp[(N - 1) % 2][K])
}
