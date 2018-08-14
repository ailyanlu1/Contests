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
    val X = In.nextInt()
    val Y = In.nextInt()
    val Z = In.nextInt()
    fun modify(s: String): String {
        val sb = StringBuilder()
        for (c in s) {
            val i = c - '0'
            if (i == 0) sb.append(Z)
            else if (i % 2 == 0) sb.append(i + X)
            else sb.append(Math.max(0, i - Y))
        }
        return sb.toString()
    }
    val S = Array(N, {modify(In.next())})
    In.next()
    val fail = ArrayList<Int>()
    for (i in 0 until N) if (In.next() != S[i]) fail.add(i + 1)
    if (fail.size == 0) Out.println("MATCH")
    else {
        Out.print("FAIL: ")
        for (i in 0 until fail.size) Out.print("${fail[i]}" + if (i == fail.size - 1) "\n" else ",")
    }
    In.next()
}
