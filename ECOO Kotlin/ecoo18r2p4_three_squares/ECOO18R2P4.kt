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

val INF = 0x3f3f3f3f.toLong()

fun run(testCaseNum: Int) {
    val N = In.nextInt()
    val P = Array(N, {Pair(In.nextLong(), In.nextLong())}).toCollection(ArrayList())
    fun check(L: Long, P: ArrayList<Pair<Long, Long>>, cnt: Int): Boolean {
        val bnd = arrayOf(arrayOf(INF, -INF), arrayOf(INF, -INF))
        for (p in P) {
            bnd[0][0] = Math.min(bnd[0][0], p.first)
            bnd[0][1] = Math.max(bnd[0][1], p.first)
            bnd[1][0] = Math.min(bnd[1][0], p.second)
            bnd[1][1] = Math.max(bnd[1][1], p.second)
        }
        if (bnd[0][1] - bnd[0][0] <= L && bnd[1][1] - bnd[1][0] <= L) return true
        if (cnt == 3) return false
        bnd[0][1] -= L
        bnd[1][1] -= L
        val Q = ArrayList<Pair<Long, Long>>()
        for (i in 0..1) {
            for (j in 0..(if(cnt == 1) 1 else 0)) {
                Q.clear()
                for (p in P) if (bnd[0][i] > p.first || p.first > bnd[0][i] + L || bnd[1][j] > p.second || p.second > bnd[1][j] + L) Q.add(p)
                if (check(L, Q, cnt + 1)) return true
            }
        }
        return false
    }
    var lo = 1L
    var hi = 2e9.toLong() + 5
    while (lo < hi) {
        val mid = lo + (hi - lo) / 2
        if (check(mid, P, 1)) hi = mid
        else lo = mid + 1
    }
    Out.println(lo)
}
