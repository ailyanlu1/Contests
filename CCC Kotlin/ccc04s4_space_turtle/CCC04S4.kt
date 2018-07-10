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
            System.err.println("Exception thrown on test case ")
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
    var sx = In.nextInt()
    var sy = In.nextInt()
    var sz = In.nextInt()
    var dx = In.nextInt() - sx
    var dy = In.nextInt() - sy
    var dz = In.nextInt() - sz
    var ans = dx * dx + dy * dy + dz * dz
    while (true) {
        var d = dx - In.nextInt()
        var c = In.nextChar()
        if (d * dx < 0) ans = Math.min(ans, dy * dy + dz * dz)
        else ans = Math.min(ans, d * d + dy * dy + dz * dz)
        if (c == 'E') break
        var temp = d
        if (c == 'L') {
            dx = dy
            dy = -temp
        } else if (c == 'R') {
            dx = -dy
            dy = temp
        } else if (c == 'U') {
            dx = dz
            dz = -temp
        } else if (c == 'D') {
            dx = -dz
            dz = temp
        }
    }
    Out.printf("%.2f\n", Math.sqrt(ans.toDouble()))
}
