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

val MOD = 1e9.toLong() + 7
val MAXN = 1e6.toInt() + 5
val fact = LongArray(MAXN * 2)

fun run(testCaseNum: Int) {
    fun calc() {
        fact[0] = 1L
        for (i in 1 until fact.size) fact[i] = fact[i - 1] * i % MOD
    }
    if (testCaseNum == 1) calc()
    val B = In.nextInt()
    val G = In.nextInt()
    if (G < 2) {
        Out.println(0)
        return
    }
    var sub = 0L
    var cur = 0L
    while (cur * (G - 1) <= B) {
        sub = (sub + (B - cur * (G - 1) + 1)) % MOD
        cur += 2
    }
    sub = sub * fact[B] % MOD * fact[G] % MOD
    Out.println((fact[B + G] - sub + MOD) % MOD)
}
