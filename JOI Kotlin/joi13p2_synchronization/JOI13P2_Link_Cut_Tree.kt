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
    class Edge(var a: Int, var b: Int)
    val N = In.nextInt()
    val M = In.nextInt()
    val Q = In.nextInt()
    val L = IntArray(N + 1, {0})
    val R = IntArray(N + 1, {0})
    val P = IntArray(N + 1, {0})
    val active = BooleanArray(N - 1, {false})
    val adj = Array(N + 1, {ArrayList<Int>()})
    val E = Array(N - 1, {Edge(In.nextInt(), In.nextInt())})
    val cnt = IntArray(N + 1, {1})
    val last = IntArray(N + 1, {0})
    for (i in 0 until N - 1) {
        adj[E[i].a].add(i)
        adj[E[i].b].add(i)
    }
    fun dfs(v: Int, prev: Int) {
        for (i in adj[v]) {
            if (E[i].a == prev || E[i].b == prev) continue
            if (E[i].b == v) E[i].b = E[i].a.also { E[i].a = E[i].b }
            dfs(E[i].b, v)
        }
    }
    dfs(1, 0)
    fun isRoot(x: Int): Boolean {
        return P[x] == 0 || (x != L[P[x]] && x != R[P[x]])
    }
    fun connect(ch: Int, par: Int, hasCh: Boolean, isL: Boolean) {
        if (ch != 0) P[ch] = par
        if (hasCh) {
            if (isL) L[par] = ch
            else R[par] = ch
        }
    }
    fun rotate(x: Int) {
        val p = P[x]
        val g = P[p]
        val isRootP = isRoot(p)
        val isL = x == L[p]
        connect(if (isL) R[x] else L[x], p, true, isL)
        connect(p, x, true, !isL)
        connect(x, g, !isRootP, if (isRootP) false else p == L[g])
    }
    fun splay(x: Int) {
        while (!isRoot(x)) {
            val p = P[x]
            val g = P[p]
            if (!isRoot(p)) rotate(if ((x == L[p]) == (p == L[g])) p else x)
            rotate(x)
        }
    }
    fun expose(x: Int) {
        var last = 0
        var y = x
        while (y != 0) {
            splay(y)
            L[y] = last
            last = y
            y = P[y]
        }
        splay(x)
    }
    fun findRoot(x: Int): Int {
        var y = x
        expose(y)
        while (R[y] != 0) y = R[y]
        splay(y)
        return y
    }
    fun link(par: Int, ch: Int) {
        expose(ch)
        P[ch] = par
    }
    fun cutParent(ch: Int) {
        expose(ch)
        P[R[ch]] = 0
        R[ch] = 0
    }
    for (i in 0 until M) {
        val j = In.nextInt() - 1
        if (active[j]) {
            last[E[j].b] = cnt[findRoot(E[j].a)]
            cutParent(E[j].b)
            cnt[E[j].b] = last[E[j].b]
        } else {
            cnt[findRoot(E[j].a)] += cnt[E[j].b] - last[E[j].b]
            link(E[j].a, E[j].b)
        }
        active[j] = !active[j]
    }
    for (i in 0 until Q) Out.println(cnt[findRoot(In.nextInt())])
}
