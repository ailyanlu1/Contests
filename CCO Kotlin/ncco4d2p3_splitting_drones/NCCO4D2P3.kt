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

var N = 20005
var K = N
var A = IntArray(N)
val BASE = 10007L
val MOD = (1e9 + 7).toLong()

fun powMod(base: Long, pow: Int): Long {
    var ret = 1L
    var b = base
    var p = pow
    while (p > 0) {
        if (p % 2 == 1) ret = ret * b % MOD;
        p /= 2
        b = b * b % MOD;
    }
    return ret
}

fun check(L: Int): Boolean {
    var hash = 0L
    var H = HashMap<Long, Int>()
    for (i in 1..N) {
        hash = (hash * BASE + A[i]) % MOD
        if (i >= L) {
            hash -= A[i - L] * powMod(BASE, L) % MOD
            if (hash < 0) hash += MOD
            var x: Int? = H[hash]
            if (x == null) H[hash] = 1
            else {
                if (x + 1 >= K) return true
                H[hash] = x + 1
            }
        }
    }
    return false
}

fun run(testCaseNum: Int) {
    N = In.nextInt()
    K = In.nextInt()
    for (i in 1..N) A[i] = In.nextInt()
    var lo = 1
    var hi = N
    while (lo <= hi) {
        var mid = lo + (hi - lo) / 2
        if (check(mid)) lo = mid + 1
        else hi = mid - 1
    }
    Out.println(lo - 1)
}
