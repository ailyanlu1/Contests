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
    NUM_OF_TEST_CASES = In.nextInt()
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
    var x = In.nextLong()
    Out.println(if (x and (x - 1) == 0L) "T" else "F")
}
