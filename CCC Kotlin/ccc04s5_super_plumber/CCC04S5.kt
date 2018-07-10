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
    var i = 1
    while (true) {
        try {
            if (!run(i++)) break
        } catch (e : Exception) {
            System.err.println("Exception thrown on test case ")
            e.printStackTrace(System.err)
            Out.flush()
            if (crash) throw Exception()
        }
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

fun run(testCaseNum: Int): Boolean {
    var M = In.nextInt()
    var N = In.nextInt()
    if (M == 0 && N == 0) return false
    var grid = Array(M, {IntArray(N)})
    var dp = Array(M, {IntArray(N, {-1})})
    for (i in 0 until M) {
        var S = In.next()
        for (j in 0 until N) grid[i][j] = if (S[j] == '.') 0 else if (S[j] == '*') -1 else S[j] - '0'
    }
    dp[M - 1][0] = grid[M - 1][0]
    for (i in M - 2 downTo 0) dp[i][0] = dp[i + 1][0] + grid[i][0]
    for (j in 1 until N) {
        for (i in 0 until M) {
            if (dp[i][j - 1] != -1) {
                var cur = dp[i][j - 1]
                for (k in i until M) {
                    if (grid[k][j] == -1) break
                    cur += grid[k][j]
                    dp[k][j] = Math.max(dp[k][j], cur)
                }
            }
        }
        for (i in M - 1 downTo 0) {
            if (dp[i][j - 1] != -1) {
                var cur = dp[i][j - 1]
                for (k in i downTo 0) {
                    if (grid[k][j] == -1) break
                    cur += grid[k][j]
                    dp[k][j] = Math.max(dp[k][j], cur)
                }
            }
        }
    }
    Out.println(dp[M - 1][N - 1])
    return true
}
