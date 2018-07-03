// http://codeforces.com/problemsets/acmsguru/problem/99999/155
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

var N = 50005
var LGN = Math.floor(Math.log(N.toDouble()) / Math.log(2.0) + 1).toInt()
var KEY = IntArray(N)
var AUX = IntArray(N)
var IND = Array<Int>(N, { it })
var P = IntArray(N)
var L = IntArray(N)
var R = IntArray(N)
var ST = Array<IntArray>(LGN, { IntArray(N) })

fun build(l: Int, r: Int, p: Int): Int {
    if (l > r) return -1
    var i = Math.floor(Math.log((r - l + 1).toDouble()) / Math.log(2.0)).toInt()
    var j = if (AUX[IND[ST[i][l]]] < AUX[IND[ST[i][r - (1 shl i) + 1]]]) ST[i][l] else ST[i][r - (1 shl i) + 1]
    P[IND[j]] = p
    L[IND[j]] = build(l, j - 1, IND[j])
    R[IND[j]] = build(j + 1, r, IND[j])
    return IND[j]
}

fun run(testCaseNum: Int) {
    N = In.nextInt()
    LGN = Math.floor(Math.log(N.toDouble()) / Math.log(2.0) + 1).toInt()
    for (i in 0 until N) {
        KEY[i] = In.nextInt()
        AUX[i] = In.nextInt()
        ST[0][i] = i
    }
    Arrays.sort(IND, 0, N) { a, b -> KEY[a] - KEY[b] }
    for (i in 0 until LGN - 1) {
        for (j in 0 until N - (1 shl i)) {
            ST[i + 1][j] = if (AUX[IND[ST[i][j]]] < AUX[IND[ST[i][j + (1 shl i)]]]) ST[i][j] else ST[i][j + (1 shl i)]
        }
    }
    build(0, N - 1, -1)
    Out.println("YES")
    for (i in 0 until N) Out.println("${P[i] + 1} ${L[i] + 1} ${R[i] + 1}")
}
