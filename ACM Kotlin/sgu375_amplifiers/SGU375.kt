// https://codeforces.com/problemsets/acmsguru/problem/99999/375
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

    fun hasNext(): Boolean {
        while (peek() > -1 && peek() <= 32) read()
        return peek() > -1
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

    private fun peek(): Byte {
        if (bufferPointer == bytesRead) fillBuffer()
        return buffer[bufferPointer]
    }

    fun close() {
        din.close()
    }
}

var NUM_OF_TEST_CASES: Int = 1 // TODO CHANGE NUMBER OF TEST CASES

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
    fun dfs(n: Int, m: Int) {
        if (n == 1) {
            Out.println(m)
            return
        }
        dfs(if ((n - 1) % 4 < 2) (n + 1) / 2 else (n - 1) / 2, m + 1)
        Out.print("${((n - 1) % 4) / 2 + 1} ")
    }
    val N = In.nextInt()
    if (N % 2 == 0) Out.println("No solution")
    else {
        dfs(N, 0);
        Out.println()
    }
}
