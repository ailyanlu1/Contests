// http://codeforces.com/problemsets/acmsguru/problem/99999/406
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
    var S = Array(N, {Array<Int>(In.nextInt(), {In.nextInt()})})
    var H = Array(N, {HashSet(Arrays.asList(*S[it]))})
    for (i in 0 until M) {
        var good = ArrayList<Int>()
        var bad = ArrayList<Int>()
        for (j in 0 until In.nextInt()) {
            var x = In.nextInt()
            if (x > 0) good.add(x)
            else bad.add(-x)
        }
        var ans = ArrayList<Int>()
        for (j in 0 until N) if (good.fold(true) { ret, x -> ret && H[j].contains(x) } && bad.fold(true) { ret, x -> ret && !H[j].contains(x) }) ans.add(j)
        Out.println(ans.size)
        for (j in ans) {
            Out.print("${S[j].size} ")
            for (x in S[j]) Out.print("$x ")
            Out.println()
        }
    }
}
