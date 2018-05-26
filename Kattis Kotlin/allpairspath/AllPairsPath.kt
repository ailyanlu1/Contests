// https://open.kattis.com/problems/allpairspath
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

val INF = 0x3f3f3f3f.toInt()

fun run(testCaseNum: Int) {
    while (true) {
        var N = In.nextInt()
        var M = In.nextInt()
        var Q = In.nextInt()
        if (N == 0) return
        var dist = Array<IntArray>(N, {IntArray(N, {INF})})
        for (i in 0 until N) dist[i][i] = 0
        for (i in 0 until M) {
            var u = In.nextInt()
            var v = In.nextInt()
            var w = In.nextInt()
            dist[u][v] = Math.min(dist[u][v], w)
        }
        for (i in 0 until N) for (j in 0 until N) for (k in 0 until N) if (dist[j][k] > dist[j][i] + dist[i][k] && dist[j][i] < INF && dist[i][k] < INF) dist[j][k] = dist[j][i] + dist[i][k]
        for (i in 0 until N) for (j in 0 until N) for (k in 0 until N) if (dist[k][k] < 0 && dist[i][k] != INF && dist[k][j] != INF) {
            dist[i][j] = -INF
            break
        }
        for (i in 0 until Q) {
            var u = In.nextInt()
            var v = In.nextInt()
            if (dist[u][v] == INF) Out.println("Impossible")
            else if (dist[u][v] == -INF) Out.println("-Infinity")
            else Out.println(dist[u][v])
        }
        Out.println()
    }
}
