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

val BND1 = 1e6.toInt() + 5
val BND2 = 1e18.toLong() + 5
val isPrime = BooleanArray(BND1, {it >= 2})
val SPF = IntArray(BND1)
val primes = ArrayList<Int>()

fun sieve() {
    for (i in 2 until BND1) {
        if (isPrime[i]) {
            primes.add(i)
            SPF[i] = i
        }
        for (j in primes) {
            if (i * j >= BND1 || j > SPF[i]) break
            isPrime[i * j] = false
            SPF[i * j] = j
        }
    }
}

fun run(testCaseNum: Int) {
    if (testCaseNum == 1) sieve()
    val K = In.nextInt()
    val M = In.nextLong()
    val factors = ArrayList<Pair<Int, Long>>()
    var k = K
    var cnt = 0L
    var last = 0
    while (k != 1) {
        if (SPF[k] != last) {
            if (last != 0) factors.add(Pair(last, cnt * M))
            last = SPF[k]
            cnt = 0
        }
        cnt++
        k /= SPF[k]
    }
    if (last != 0) factors.add(Pair(last, cnt * M))
    fun f(N: Long): Boolean {
        for (p in factors) {
            var cur = p.first.toLong()
            var cnt = 0L
            while (cnt < p.second && cur <= N) {
                cnt += N / cur
                cur *= p.first
            }
            if (cnt < p.second) return false
        }
        return true
    }
    var lo = 0L
    var hi = BND2
    while (lo < hi) {
        val mid = lo + (hi - lo) / 2
        if (f(mid)) hi = mid
        else lo = mid + 1
    }
    Out.println(lo)
}
