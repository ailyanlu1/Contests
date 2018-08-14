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
    fun nextLong(): Long = next().toLong()
    fun close(): Unit = In.close()
}

var NUM_OF_TEST_CASES: Int = 10 // TODO CHANGE NUMBER OF TEST CASES

// TODO CHANGE FILE NAMES
val INPUT_FILE_NAME = "input.txt"
val OUTPUT_FILE_NAME = "output.txt"

val stdIn: Boolean = true
val stdOut: Boolean = true
val crash: Boolean = true
val flush: Boolean = false

val In: Reader = if (stdIn) Reader(System.`in`) else Reader(INPUT_FILE_NAME)
val Out: PrintWriter = if (stdOut) PrintWriter(System.out) else PrintWriter(OUTPUT_FILE_NAME)

fun main(args: Array<String>) {
    for (i in 1..NUM_OF_TEST_CASES) {
        try {
            run(i)
        } catch (e: Exception) {
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
    val A = LongArray(N, {In.nextLong()})
    val B = LongArray(N, {In.nextLong()})
    A.sort()
    B.sort()
    fun f(i: Int) = (0 until N).fold(0L) { acc, j -> acc + Math.min(Math.abs(A[j] - B[(i + j) % N]), M - Math.abs(A[j] - B[(i + j) % N]))}
    var lo = 0
    var hi = N / 2
    while (lo < hi) {
        val mid = lo + (hi - lo) / 2
        if (f(mid) < f(mid + 1)) hi = mid
        else lo = mid + 1
    }
    val ans1 = f(lo)
    lo = N / 2
    hi = N
    while (lo < hi) {
        val mid = lo + (hi - lo) / 2
        if (f(mid) < f(mid + 1)) hi = mid
        else lo = mid + 1
    }
    Out.println(Math.min(ans1, f(lo)))
}
