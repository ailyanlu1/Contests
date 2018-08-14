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
    val N = In.nextInt()
    val M = In.nextInt()
    class Edge(val a: Int, val b: Int, val c: Double)
    val dist = DoubleArray(N, {Double.POSITIVE_INFINITY})
    dist[0] = -Math.log10(In.nextDouble())
    val E = Array(M, {Edge(In.nextInt() - 1, In.nextInt() - 1, Math.log10(In.nextDouble()))})
    for (i in 0 until N - 1) for (e in E) if (dist[e.a] < Double.POSITIVE_INFINITY) dist[e.b] = Math.min(dist[e.b], dist[e.a] + e.c)
    var inCycle = true
    while (inCycle) {
        inCycle = false
        for (e in E) {
            if (dist[e.a] < Double.POSITIVE_INFINITY && dist[e.b] > Double.NEGATIVE_INFINITY && dist[e.b] > dist[e.a] + e.c) {
                dist[e.b] = Double.NEGATIVE_INFINITY
                inCycle = true
            }
        }
    }
    if (dist[N - 1] <= -9) Out.println("Billionaire!")
    else Out.printf("%.2f\n", Math.pow(10.0, -dist[N - 1]))
}
