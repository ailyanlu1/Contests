// http://codeforces.com/problemsets/acmsguru/problem/99999/275
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
val flush: Boolean = false

fun main(args : Array<String>) {
    for (i in 1..NUM_OF_TEST_CASES) {
        run(i)
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var A = LongArray(N)
    for (i in 0 until N) A[i] = In.nextLong()
    var ans = 0L
    var cur = 0L
    for (i in 60 downTo 0) {
        for (j in 0 until N) {
            if (((A[j] shr i) and 1L) == 1L) {
                cur = A[j]
                if (((ans shr i) and 1L) == 0L) ans = ans xor cur
                for (k in 0 until N) if (((A[k] shr i) and 1L) == 1L) A[k] = A[k] xor cur
            }
        }
    }
    Out.println(ans)
}
