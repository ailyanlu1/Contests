// http://codeforces.com/problemsets/acmsguru/problem/99999/115
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
val flush: Boolean = false

fun main(args : Array<String>) {
    for (i in 1..NUM_OF_TEST_CASES) {
        run(i)
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

fun run(testCaseNum: Int) {
    var year = 2001
    var day = In.nextInt()
    var month = In.nextInt()
    if (month !in 1..12) {
        Out.println("Impossible")
        return
    }
    when (month) {
        1, 3, 5, 7, 8, 10, 12 -> {
            if (day !in 1..31) {
                Out.println("Impossible")
                return
            }
        }
        2 -> {
            if (day !in 1..28) {
                Out.println("Impossible")
                return
            }
        }
        else -> {
            if (day !in 1..30) {
                Out.println("Impossible")
                return
            }
        }
    }
    if (month <= 2) {
        month += 12;
        year--;
    }
    Out.println((day + (13 * (month + 1) / 5) + year + year / 4 - year / 100 + year / 400 + 5) % 7 + 1)
}
