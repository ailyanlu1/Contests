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

class Yodeller(val id: Int, var score: Int, var worstRank: Int)

fun run(testCaseNum: Int) {
    val N = In.nextInt()
    val K = In.nextInt()
    var Y = Array(N, {Yodeller(it, 0, 0)})
    for (i in 0 until K) {
        var round = IntArray(N, {In.nextInt()})
        for (j in 0 until N) Y[j].score += round[Y[j].id]
        Y.sortWith(compareByDescending<Yodeller>{it.score}.thenBy{it.id})
        var curRank = 0
        for (j in 0 until N) {
            if (j == 0 || Y[j].score != Y[j - 1].score) curRank = j
            Y[j].worstRank = Math.max(Y[j].worstRank, curRank)
        }
    }
    for (i in 0 until N) {
        if (i == 0 || Y[i].score == Y[i - 1].score) Out.println("Yodeller ${Y[i].id + 1} is the TopYodeller: score ${Y[i].score}, worst rank ${Y[i].worstRank + 1}")
        else break
    }
}
