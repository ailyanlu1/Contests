import java.io.*
import java.math.*
import java.util.*

class Reader {
    private val In: BufferedReader
    private var st: StringTokenizer? = null
    constructor(inputStream: InputStream) {
        In = BufferedReader(InputStreamReader(inputStream))
    }
    fun next(): String {
        while (st == null || !st!!.hasMoreTokens()) st = StringTokenizer(In.readLine().trim())
        return st!!.nextToken()
    }
    fun nextInt(): Int = next().toInt()
    fun close(): Unit = In.close()
}

val In: Reader = Reader(System.`in`)
val Out: PrintWriter = PrintWriter(System.out)

fun main(args: Array<String>) {
    val rng = Random(System.currentTimeMillis())
    class Edge(var a: Int, var b: Int)
    val N = In.nextInt()
    val M = In.nextInt()
    val Q = In.nextInt()
    val PRE = IntArray(N + 1, {it})
    val POST = IntArray(N + 1, {N + it})
    val VERT = IntArray(2 * N + 1, {if (it > N) it - N else it})
    val L = IntArray(2 * N + 1, {0})
    val R = IntArray(2 * N + 1, {0})
    val P = IntArray(2 * N + 1, {0})
    val PRI = DoubleArray(2 * N + 1, {rng.nextDouble()})
    val SZ = IntArray(2 * N + 1, {if (it == 0) 0 else 1})
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
    fun min(x: Int): Int {
        var y = x
        while (L[y] != 0) y = L[y]
        return y
    }
    fun root(x: Int): Int {
        var y = x
        while (P[y] != 0) y = P[y]
        return y
    }
    fun treeRoot(v: Int): Int = VERT[min(root(PRE[v]))]
    fun index(x: Int): Int {
        var y = x
        var ind = SZ[L[y]]
        while (P[y] != 0) {
            if (L[P[y]] != y) ind += 1 + SZ[L[P[y]]]
            y = P[y]
        }
        return ind
    }
    fun update(x: Int) {
        if (x != 0) {
            SZ[x] = 1 + SZ[L[x]] + SZ[R[x]]
            if (L[x] != 0) P[L[x]] = x
            if (R[x] != 0) P[R[x]] = x
        }
    }
    fun merge(l: Int, r: Int): Int {
        val x: Int
        if (l == 0) x = r
        else if (r == 0) x = l
        else if (PRI[l] > PRI[r]) {
            R[l] = merge(R[l], r)
            x = l
        } else {
            L[r] = merge(l, L[r])
            x = r
        }
        update(x)
        return x
    }
    fun split(x: Int, ind: Int): Pair<Int, Int> {
        val l: Int
        val r: Int
        if (x == 0) return Pair(0, 0)
        P[x] = 0
        if (ind <= SZ[L[x]]) {
            val ret = split(L[x], ind)
            l = ret.first
            L[x] = ret.second
            r = x
        } else {
            val ret = split(R[x], ind - SZ[L[x]] - 1)
            R[x] = ret.first
            r = ret.second
            l = x
        }
        update(x)
        return Pair(l, r)
    }
    for (i in 1..N) merge(PRE[i], POST[i])
    fun link(v: Int, w: Int) {
        val p = split(root(PRE[v]), index(PRE[v]) + 1)
        merge(merge(p.first, root(PRE[w])), p.second)
    }
    fun cutParent(v: Int) {
        val l = split(root(PRE[v]), index(PRE[v]))
        val r = split(l.second, index(POST[v]) + 1)
        merge(l.first, r.second)
    }
    for (i in 0 until M) {
        val j = In.nextInt() - 1
        if (active[j]) {
            last[E[j].b] = cnt[treeRoot(E[j].a)]
            cutParent(E[j].b)
            cnt[E[j].b] = last[E[j].b]
        } else {
            cnt[treeRoot(E[j].a)] += cnt[E[j].b] - last[E[j].b]
            link(E[j].a, E[j].b)
        }
        active[j] = !active[j]
    }
    for (i in 0 until Q) Out.println(cnt[treeRoot(In.nextInt())])
    In.close()
    Out.close()
}
