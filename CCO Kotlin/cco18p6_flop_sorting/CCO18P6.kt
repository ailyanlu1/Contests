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
    var N = In.nextInt()
    var A = IntArray(N, {In.nextInt()})
    var ans = ArrayList<Pair<Int, Int>>()
    var ANS = ArrayList<Pair<Int, Int>>()
    fun swap(i: Int, j: Int) {
        A[i] = A[j].also{A[j] = A[i]}
        ans.add(Pair(i, j))
    }
    fun reverse(L: Int, R: Int) {
        var l = L
        var r = R
        while (l < r) swap(l++, r--)
    }
    fun merge(L: Int, M: Int, R: Int) {
        if (L > M || M + 1 > R) return
        var i = L
        var j = M + 1
        for (k in 0 until M - L + 1) {
            if (i > M) j++
            else if (j > R) i++
            else if (A[j] < A[i]) j++
            else i++
        }
        reverse(i, M)
        reverse(M + 1, j - 1)
        reverse(i, j - 1)
        merge(L, i - 1, M)
        merge(M + 1, j - 1, R)
    }
    fun sort(L: Int, R: Int) {
        if (L >= R) return
        var M = L + (R - L) / 2
        sort(L, M)
        sort(M + 1, R)
        merge(L, M, R)
    }
    sort(0, N - 1)
    for (i in 1 until N) if (A[i - 1] > A[i]) throw Exception()
    ANS.addAll(ans)
    ans.clear()
    A = IntArray(N, {In.nextInt()})
    sort(0, N - 1)
    for (i in 1 until N) if (A[i - 1] > A[i]) throw Exception()
    ANS.addAll(ans.reversed())
    Out.println("${ANS.size}")
    for (p in ANS) Out.println("${p.first + 1} ${p.second + 1}")
}
