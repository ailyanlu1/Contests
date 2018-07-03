// http://codeforces.com/problemsets/acmsguru/problem/99999/134
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

fun dfs(N: Int, adj: Array<ArrayList<Int>>, v: Int, prev: Int, centroids: ArrayList<Int>, maxSubtree: ArrayList<Int>): Int {
    var largest = 0
    var treeSize = 1
    for (w in adj[v]) {
        if (w == prev) continue
        var subtreeSize = dfs(N, adj, w, v, centroids, maxSubtree)
        treeSize += subtreeSize
        largest = Math.max(largest, subtreeSize)
    }
    largest = Math.max(largest, N - treeSize)
    if (largest <= N / 2) {
        centroids.add(v)
        maxSubtree.add(largest)
    }
    return treeSize
}

fun run(testCaseNum: Int) {
    var N = In.nextInt()
    var adj = Array(N, { ArrayList<Int>() })
    var centroids = ArrayList<Int>()
    var maxSubtree = ArrayList<Int>()
    for (i in 0 until N - 1) {
        var a = In.nextInt() - 1
        var b = In.nextInt() - 1
        adj[a].add(b)
        adj[b].add(a)
    }
    dfs(N, adj, 0, -1, centroids, maxSubtree)
    var minVal = maxSubtree.fold(Int.MAX_VALUE) { minVal, x -> Math.min(minVal, x) }
    Out.println("${minVal} ${centroids.size}")
    centroids.sort()
    for (v in centroids) Out.print("${v + 1} ")
    Out.println()
}
