// http://codeforces.com/problemsets/acmsguru/problem/99999/344
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
}

val In: Reader = Reader(System.`in`)
val Out: PrintWriter = PrintWriter(System.out)
//val In: Reader = Reader(INPUT_FILE_NAME)
//val Out: PrintWriter = PrintWriter(OUTPUT_FILE_NAME)

var NUM_OF_TEST_CASES: Int = 1 // TODO CHANGE NUMBER OF TEST CASES

// TODO CHANGE FILE NAMES
val INPUT_FILE_NAME = "input.txt"
val OUTPUT_FILE_NAME = "output.txt"

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

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var M = In.nextInt()
    var grid = Array(N + 2, {CharArray(M + 2, {'X'})})
    var cnt = Array(N + 2, {IntArray(M + 2, {0})})
    var dir = arrayOf(Pair(0, -1), Pair(0, 1), Pair(-1, 0), Pair(1, 0))
    var ans = 0
    var q: Queue<Pair<Int, Int>> = ArrayDeque<Pair<Int, Int>>()
    for (i in 1..N) {
        var S = In.next()
        for (j in 1..M) {
            grid[i][j] = S[j - 1]
            if (grid[i][j] == 'X') {
                q.offer(Pair(i, j))
                ans++
            }
        }
    }
    while (!q.isEmpty()) {
        var cur = q.poll()
        for (p in dir) {
            var i = cur.first + p.first
            var j = cur.second + p.second
            if (++cnt[i][j] > 1 && grid[i][j] != 'X') {
                grid[i][j] = 'X'
                q.offer(Pair(i, j))
                ans++
            }
        }
    }
    Out.println(ans)
}
