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

fun run(testCaseNum: Int) {
    val C = In.nextInt()
    var N = 0
    val BIT = LongArray(C + 1, {0L})
    fun update(i : Int, v: Long) {
        var x = i
        while (x <= C) {
            BIT[x] += v
            x += x and -x
        }
    }
    fun rsq(i: Int): Long {
        var x = i
        var sum = 0L
        while (x > 0) {
            sum += BIT[x]
            x -= x and -x
        }
        return sum
    }
    fun rsq(a: Int, b: Int): Long {
        return rsq(b) - rsq(a - 1)
    }
    val hs = HashMap<String, Int>()
    val R = Array<String>(C, {""})
    val ind = IntArray(C + 1, {0})
    val mass = LongArray(C + 1, {0L})
    for (i in 0 until C) {
        var op = In.nextChar()
        when (op) {
            'A' -> {
                R[i] = In.next()
                if (hs.containsKey(R[i])) {
                    Out.println("Can't add ${R[i]}")
                } else {
                    ind[++N] = i
                    hs.put(R[i], N)
                    mass[N] = R[i].fold(0L){sum, c -> sum + (c - 'a').toLong() + 1L}
                    update(N, mass[N])
                }
            }
            'S' -> {
                val x = hs.get(In.next()) ?: -1
                val y = hs.get(In.next()) ?: -1
                update(x, mass[y] - mass[x])
                update(y, mass[x] - mass[y])
                hs.put(R[ind[x]], y)
                hs.put(R[ind[y]], x)
                ind[x] = ind[y].also{ind[y] = ind[x]}
                mass[x] = mass[y].also{mass[y] = mass[x]}
            }
            'M' -> {
                val x = hs.get(In.next()) ?: -1
                val y = hs.get(In.next()) ?: -1
                Out.println(rsq(Math.min(x, y), Math.max(x, y)))
            }
            'R' -> {
                var x = hs.get(In.next()) ?: -1
                hs.remove(R[ind[x]])
                R[i] = In.next()
                ind[x] = i
                hs.put(R[i], x)
                val newMass = R[i].fold(0L){sum, c -> sum + (c - 'a').toLong() + 1L}
                update(x, newMass - mass[x])
                mass[x] = newMass
            }
            'N' -> Out.println(N)
        }
    }
}
