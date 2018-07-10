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
    val N = In.nextInt()
    val M = In.nextInt()
    val A = IntArray(M)
    val B = IntArray(M)
    val X = BooleanArray(M)
    fun eval(k: Int): Boolean {
        for (i in 0 until M) X[i] = !((if (A[i] < 0) A[i] + N >= k else X[A[i]]) && (if (B[i] < 0) B[i] + N >= k else X[B[i]]))
        return X[M - 1]
    }
    for (i in 0 until M) {
        A[i] = In.nextInt() - N - 1
        B[i] = In.nextInt() - N - 1
    }
    val target = eval(0)
    if (target == eval(N)) {
        for (i in 0 until N) Out.print(0)
        Out.println()
        return
    }
    var lo = 0
    var hi = N
    while (lo < hi) {
        var mid = lo + (hi - lo) / 2
        if (eval(mid) == target) lo = mid + 1
        else hi = mid
    }
    for (i in 0 until lo - 1) Out.print(0)
    if (lo > 0 && lo <= N) Out.print('x')
    for (i in lo until N) Out.print(1)
    Out.println()
}
