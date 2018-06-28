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
            Out.println("Exception thrown on test case ")
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
    fun area2(a: Pair<Double, Double>, b: Pair<Double, Double>, c: Pair<Double, Double>) : Double = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first)
    fun dist(a: Pair<Double, Double>, b: Pair<Double, Double>) : Double = Math.sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second))
    fun perimeter(a: Pair<Double, Double>, b: Pair<Double, Double>, c: Pair<Double, Double>) : Double = dist(a, b) + dist(b, c) + dist(a, c)
    for (i in 0 until N) {
        var P = Array<Pair<Double, Double>>(3, {Pair(In.nextDouble(), In.nextDouble())})
        Out.println("%.2f %.2f".format(Math.abs(area2(P[0], P[1], P[2])) / 2.0, perimeter(P[0], P[1], P[2])))
    }
}
