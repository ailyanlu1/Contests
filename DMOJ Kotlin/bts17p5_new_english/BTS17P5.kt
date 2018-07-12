import java.io.*
import java.math.*
import java.util.*

class Reader {
    private val BUFFER_SIZE: Int = 1 shl 12
    private var LENGTH: Int = -1
    private val din: DataInputStream 
    private val buffer: ByteArray = ByteArray(BUFFER_SIZE)
    private var bufferPointer: Int = 0
    private var bytesRead: Int = 0

    constructor(inputStream: InputStream) {
        din = DataInputStream(inputStream)
    }

    constructor(fileName: String) {
        din = DataInputStream(FileInputStream(fileName))
    }

    fun nextInt(): Int {
        var ret: Int = 0
        var c: Byte
        do {
            c = read()
        } while (c <= 32)
        var neg: Boolean = c == 45.toByte()
        if (neg) c = read()
        do {
            ret = ret * 10 + c - 48
            c = read()
        } while (c >= 48)
        if (neg) return -ret
        return ret
    }

    fun nextLong(): Long {
        var ret: Long = 0L
        var c: Byte
        do {
            c = read()
        } while (c <= 32)
        var neg: Boolean = c == 45.toByte()
        if (neg) c = read()
        do {
            ret = ret * 10 + c - 48
            c = read()
        } while (c >= 48)
        if (neg) return -ret
        return ret
    }

    fun nextDouble(): Double {
        var ret: Double = 0.0
        var div: Double = 1.0
        var c: Byte
        do {
            c = read()
        } while (c <= 32)
        var neg: Boolean = c == 45.toByte()
        if (neg) c = read()
        do {
            ret = ret * 10 + c - 48
            c = read()
        } while (c >= 48)
        if (c == 46.toByte()) {
            c = read()
            while (c >= 48) {
                div *= 10
                ret += (c - 48) / div
                c = read()
            }
        }
        if (neg) return -ret
        return ret
    }

    fun nextChar(): Char {
        var c: Byte
        do {
            c = read()
        } while (c <= 32)
        return c.toChar()
    }

    fun next(): String {
        val buf: CharArray = CharArray(LENGTH)
        var c: Byte
        var cnt: Int = 0
        do {
            c = read()
        } while (c <= 32)
        do {
            buf[cnt++] = c.toChar()
            c = read()
        } while (c > 32)
        return String(buf, 0, cnt)
    }

    fun nextLine(): String {
        val buf: CharArray = CharArray(LENGTH)
        var c: Byte
        var cnt: Int = 0
        do {
            c = read()
        } while (c <= 32)
        do {
            buf[cnt++] = c.toChar()
            c = read()
        } while (c >= 32)
        return String(buf, 0, cnt)
    }

    fun setLength(length: Int) {
        LENGTH = length
    }

    private fun fillBuffer() {
        bufferPointer = 0
        bytesRead = din.read(buffer, bufferPointer, BUFFER_SIZE)
        if (bytesRead == -1) buffer[0] = -1
    }

    private fun read(): Byte {
        if (bufferPointer == bytesRead) fillBuffer()
        return buffer[bufferPointer++]
    }

    fun close() {
        din.close()
    }
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
    class Query(val c: Char, val x: Int, val y: Int)
    val N = In.nextInt()
    val M = In.nextInt()
    var Q = Array(M, {Query(In.nextChar(), In.nextInt(), In.nextInt())})
    var S = CharArray(N, {' '})
    var cnt = IntArray(26, {0})
    var last = IntArray(26, {-1})
    var good = TreeSet<Int>(List(N + 1, {it}))
    Q.sortWith(compareBy{it.y})
    var rem = N
    for (q in Q) {
        if (cnt[q.c - 'a'] > q.x) {
            Out.println(-1)
            return
        }
        for (i in cnt[q.c - 'a'] until q.x) {
            var j = good.ceiling(last[q.c - 'a'])
            if (j >= q.y) {
                Out.println(-1)
                return
            }
            S[j] = q.c
            cnt[q.c - 'a']++
            rem--
            good.remove(j)
        }
        last[q.c - 'a'] = q.y
    }
    Q.sortWith(compareByDescending{it.y})
    for (i in 0 until 26) cnt[i] = 0
    var i = N - 1
    var j = 0
    for (q in Q) {
        while(i >= q.y) {
            if (S[i] == ' ') {
                S[i] = 'a' + j
                rem--
            }
            i--
        }
        if (rem == 0) break
        cnt[q.c - 'a']++
        while (j < 26 && cnt[j] > 0) j++
        if (j == 26) {
            Out.println(-1)
            return
        }
    }
    while (i >= 0) {
        if (S[i] == ' ') {
            S[i] = 'a' + j
            rem--
        }
        i--
    }
    if (rem != 0) throw Exception()
    Out.println(S)
}
