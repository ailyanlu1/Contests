// http://codeforces.com/problemsets/acmsguru/problem/99999/549
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


fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var K = In.nextInt()
    var costs = Array(4005, { ArrayList<Int>() })
    for (i in 0 until N) costs[In.nextInt()].add(In.nextInt())
    costs.sortWith(compareBy{ -it.size })
    var numSets = costs[K - 1].size
    var sum = ArrayList<Int>()
    for (i in 0 until costs.size) {
        if (costs[i].size < numSets) break
        costs[i].sortDescending()
        sum.add(0)
        for (j in 0 until numSets) sum[i] += costs[i][j]
    }
    sum.sortDescending()
    var maxCost = 0
    for (i in 0 until K) maxCost += sum[i]
    Out.println("$numSets $maxCost")
}
