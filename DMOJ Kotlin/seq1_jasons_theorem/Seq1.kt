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

var MOD = 1000000007.toBigInteger()
var ZERO = 0.toBigInteger()
var ONE = 1.toBigInteger()
var TWO = 2.toBigInteger()
var THREE = 3.toBigInteger()

fun pow2(base: BigInteger, exp: BigInteger): BigInteger {
    var ret = ONE
    var base = base
    var exp = exp
    while (exp > ZERO) {
        if (exp % TWO == ONE) ret = ret * base % MOD
        exp /= TWO
        base = base * base % MOD
    }
    return ret
} 

fun run(testCaseNum: Int) {
    Out.println((pow2(TWO, In.nextLong().toBigInteger() + THREE) - 5.toBigInteger() + MOD) % MOD)   
}
