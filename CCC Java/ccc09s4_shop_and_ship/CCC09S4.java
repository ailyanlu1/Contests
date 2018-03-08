import java.io.DataInputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;

public class CCC09S4 { // Barely finishes in time (sometimes)
    private static final int BUFFER_SIZE = 1 << 16;
    private static DataInputStream din = new DataInputStream(System.in);;
    private static byte[] buffer = new byte[BUFFER_SIZE];;
    private static int bufferPointer = 0, bytesRead = 0;

    public static String nextLine() throws IOException
    {
        byte[] buf = new byte[64]; // line length
        int cnt = 0, c;
        while ((c = read()) != -1)
        {
            if (c == '\n')
                break;
            buf[cnt++] = (byte) c;
        }
        return new String(buf, 0, cnt);
    }

    public static int nextInt() throws IOException
    {
        int ret = 0;
        byte c = read();
        while (c <= ' ')
            c = read();
        boolean neg = (c == '-');
        if (neg)
            c = read();
        do
        {
            ret = ret * 10 + c - '0';
        } while ((c = read()) >= '0' && c <= '9');

        if (neg)
            return -ret;
        return ret;
    }

    public static long nextLong() throws IOException
    {
        long ret = 0;
        byte c = read();
        while (c <= ' ')
            c = read();
        boolean neg = (c == '-');
        if (neg)
            c = read();
        do {
            ret = ret * 10 + c - '0';
        }
        while ((c = read()) >= '0' && c <= '9');
        if (neg)
            return -ret;
        return ret;
    }

    public static double nextDouble() throws IOException
    {
        double ret = 0, div = 1;
        byte c = read();
        while (c <= ' ')
            c = read();
        boolean neg = (c == '-');
        if (neg)
            c = read();

        do {
            ret = ret * 10 + c - '0';
        }
        while ((c = read()) >= '0' && c <= '9');

        if (c == '.')
        {
            while ((c = read()) >= '0' && c <= '9')
            {
                ret += (c - '0') / (div *= 10);
            }
        }

        if (neg)
            return -ret;
        return ret;
    }

    private static void fillBuffer() throws IOException
    {
        bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
        if (bytesRead == -1)
            buffer[0] = -1;
    }

    private static byte read() throws IOException
    {
        if (bufferPointer == bytesRead)
            fillBuffer();
        return buffer[bufferPointer++];
    }

    public static void close() throws IOException
    {
        if (din == null)
            return;
        din.close();
    }
    
    public static class Edge {
        public int to;
        public int cost;
        public Edge(int t, int c) {
            to = t;
            cost = c;
        }
    }
    
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int N = nextInt();
        int T = nextInt();
        // GRAPH
        ArrayList<Edge>[] adj = new ArrayList[N];
        for (int v = 0; v < N; v++) {
            adj[v] = new ArrayList<Edge>();
        }
        
        for (int i = 0; i < T; i++) {
            int from = nextInt() - 1;
            int to = nextInt() - 1;
            int cost = nextInt();
            adj[from].add(new Edge(to, cost));
            adj[to].add(new Edge(from, cost));
        }
        int[] distTo = new int[N];
        for (int v = 0; v < N; v++) {
            distTo[v] = Integer.MAX_VALUE;
        }
        int K = nextInt();
        for (int i = 0; i < K; i++) {
            int z = nextInt() - 1;
            int pz = nextInt();
            distTo[z] = pz;
        }
        int D = nextInt() - 1;
        // DIJKSTRA
        
        boolean[] v = new boolean[N];

        // relax vertices in order of distance from s
        for (int i = 0; i < N - 1; i++) {
            int minIndex = -1;
            for (int j = 0; j < N; j++)
                if (!v[j] && (minIndex == -1 || distTo[minIndex] > distTo[j]))
                    minIndex = j;
            if (minIndex == D) break;
            v[minIndex] = true;
            for (Edge e : adj[minIndex])
                distTo[e.to] = Math.min(distTo[e.to], distTo[minIndex] + e.cost);
        }
        out.println(distTo[D]);
        out.close();
    }
}
