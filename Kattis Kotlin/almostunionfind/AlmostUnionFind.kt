// https://open.kattis.com/problems/almostunionfind
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
    while (true) {
        try {
            run()
        } catch (e : Exception) {
            break
        }
        if (flush) Out.flush()
    }
    In.close()
    Out.close()
}

class UF {
    private val par: IntArray
    private val cnt: IntArray
    private val sum: LongArray
    
    constructor(N: Int) {
        par = IntArray(2 * N, {if (it < N) it + N else it})
        cnt = IntArray(2 * N, {if (it < N) 0 else 1})
        sum = LongArray(2 * N, {if (it < N) 0L else (it - N).toLong()})
    }
    
    fun find(p: Int): Int {
        var p = p
        while (p != par[p]) {
            par[p] = par[par[p]]
            p = par[p]
        }
        return p
    }
    
    fun join(p: Int, q: Int) {
        var p = find(p)
        var q = find(q)
        if (p == q) return
        if (cnt[p] > cnt[q]) p = q.also { q = p }
        par[p] = q
        cnt[q] += cnt[p]
        sum[q] += sum[p]
    }
    
    fun move(p: Int, q: Int) {
        var pRoot = find(p)
        var qRoot = find(q)
        if (pRoot == qRoot) return
        cnt[pRoot]--
        cnt[qRoot]++
        sum[pRoot] -= p.toLong()
        sum[qRoot] += p.toLong()
        par[p] = qRoot
    }
    
    fun get(p: Int): Pair<Int, Long> {
        var p = find(p)
        return Pair(cnt[p], sum[p])
    }
}

fun run() {
    var N = In.nextInt()
    var M = In.nextInt()
    var uf = UF(N + 1)
    for (i in 0 until M) {
        when (In.nextInt()) {
            1 -> uf.join(In.nextInt(), In.nextInt())
            2 -> uf.move(In.nextInt(), In.nextInt())
            3 -> {
                var ans = uf.get(In.nextInt())
                Out.println("${ans.first} ${ans.second}")
            }
        }
    }
}
