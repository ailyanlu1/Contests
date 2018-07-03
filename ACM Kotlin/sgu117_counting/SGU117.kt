// http://codeforces.com/problemsets/acmsguru/problem/99999/117
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

fun pow3(base: Int, pow: Int, mod: Int): Int {
    if (pow == 0) return 1
    if (pow == 1) return base
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod)
    return base * pow3(base * base % mod, pow / 2, mod) % mod
}

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var M = In.nextInt()
    var K = In.nextInt()
    var cnt = 0
    for (i in 0 until N) if (pow3(In.nextInt() % K, M, K) == 0) cnt++
    Out.println(cnt)
}
