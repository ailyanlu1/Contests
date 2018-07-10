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
    class Query(val c: Char, val x: Int, val y: Int)
    val N = In.nextInt()
    val M = In.nextInt()
    var Q = Array(M, {Query(In.nextChar(), In.nextInt(), In.nextInt())})
    var S = CharArray(N, {' '})
    var cnt = IntArray(26, {0})
    var last = IntArray(26, {-1})
    var good = TreeSet<Int>(List(N + 1, {it}))
    Q.sortWith(compareBy{it.y})
    var rem = N
    for (q in Q) {
        if (cnt[q.c - 'a'] > q.x) {
            Out.println(-1)
            return
        }
        for (i in cnt[q.c - 'a'] until q.x) {
            var j = good.ceiling(last[q.c - 'a'])
            if (j >= q.y) {
                Out.println(-1)
                return
            }
            S[j] = q.c
            cnt[q.c - 'a']++
            rem--
            good.remove(j)
        }
        last[q.c - 'a'] = q.y
    }
    Q.sortWith(compareByDescending{it.y})
    for (i in 0 until 26) cnt[i] = 0
    var i = N - 1
    var j = 0
    for (q in Q) {
        while(i >= q.y) {
            if (S[i] == ' ') {
                S[i] = 'a' + j
                rem--
            }
            i--
        }
        if (rem == 0) break
        cnt[q.c - 'a']++
        while (j < 26 && cnt[j] > 0) j++
        if (j == 26) {
            Out.println(-1)
            return
        }
    }
    while (i >= 0) {
        if (S[i] == ' ') {
            S[i] = 'a' + j
            rem--
        }
        i--
    }
    if (rem != 0) throw Exception()
    Out.println(S)
}
