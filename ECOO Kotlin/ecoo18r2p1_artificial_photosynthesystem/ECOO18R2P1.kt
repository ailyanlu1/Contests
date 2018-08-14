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
    var C = In.nextInt()
    var O = In.nextInt()
    var W = In.nextInt()
    var S = In.nextInt()
    var Ci = In.nextInt()
    var Wi = In.nextInt()
    var So = In.nextInt()
    var Oo = In.nextInt()
    var Si = In.nextInt()
    var Oi = In.nextInt()
    var Co = In.nextInt()
    var Wo = In.nextInt()
    var vis = Array(50, {Array(50, {Array(50, {BooleanArray(50, {false})})})})
    fun solve(c: Int, o: Int, w: Int, s: Int): Int {
        if (c < 0 || o < 0 || w < 0 || s < 0) return 0
        if (vis[c][o][w][s]) return o
        vis[c][o][w][s] = true
        return Math.max(o, Math.max(solve(c - Ci, o + Oo, w - Wi, s + So), solve(c + Co, o - Oi, w + Wo, s - Si)))
    }
    Out.println(solve(C, O, W, S))
}
