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

var grid = IntArray(90)
var adj = Array(90, {ArrayList<Int>()})
var revAdj = Array(90, {ArrayList<Int>()})
var vis = BooleanArray(90, {false})
var postOrder = ArrayList<Int>()

fun dfs(v: Int, t: Int): Boolean {
    vis[v] = true
    var ret = false
    for (w in revAdj[v]) {
        if (!vis[w]) ret = ret or dfs(w, t)
        else if (w == t) return true
    }
    return ret
}

fun postOrderDfs(v: Int) {
    if (vis[v] || grid[v] == -1) return
    vis[v] = true
    for (w in adj[v]) postOrderDfs(w)
    postOrder.add(v)
}

fun run(testCaseNum: Int) {
    for (i in 0 until 90) {
        var s = In.next()
        if (s[0].isDigit()) grid[i] = s.toInt()
        else {
            grid[i] = 0
            var cells = s.split('+')
            for (cell in cells) {
                var j = (cell[0] - 'A').toInt() * 9 + (cell[1] - '1').toInt()
                adj[j].add(i)
                revAdj[i].add(j)
            }
        }
    }
    for (i in 0 until 90) {
        for (j in 0 until 90) vis[j] = false
        if (dfs(i, i)) grid[i] = -1
    }
    for (i in 0 until 90) vis[i] = false
    for (i in 0 until 90) if (!vis[i]) postOrderDfs(i)
    postOrder.reverse()
    var q: Queue<Int> = ArrayDeque<Int>()
    for (i in 0 until 90) vis[i] = false
    for (i in 0 until 90) {
        if (grid[i] == -1) {
            q.offer(i)
            vis[i] = true
        }
    }
    while (!q.isEmpty()) {
        var v = q.poll()
        for (w in adj[v]) {
            if (vis[w]) continue
            grid[w] = -1
            vis[w] = true
            q.offer(w)
        }
    }
    for (v in postOrder) if (grid[v] != -1) for (w in adj[v]) if (grid[w] != -1) grid[w] = grid[w] + grid[v]
    for (i in 0 until 90) {
        Out.print(if (grid[i] == -1) "*" else "${grid[i]}")
        if (i % 9 == 8) Out.println()
        else Out.print(' ')
    }
}
