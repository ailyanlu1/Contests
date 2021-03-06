#include <bits/stdc++.h>
using namespace std;
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define uint unsigned int
#define ull unsigned long long
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;
template<typename T1,typename T2,typename H1=hash<T1>,typename H2=hash<T2>>struct pair_hash{size_t operator()(const pair<T1,T2>&p)const{return 31*H1{}(p.first)+H2{}(p.second);}};

#define _bufferSize 4096
#define _maxNumLength 128
char _inputBuffer[_bufferSize+1],*_inputPtr=_inputBuffer,_outputBuffer[_bufferSize],_c,_sign,*_tempInputBuf=nullptr,_numBuf[_maxNumLength],_tempOutputBuf[_maxNumLength],_fill=' ';
const char*_delimiter=" ";int _cur,_outputPtr=0,_numPtr=0,_precision=6,_width=0,_tempOutputPtr=0,_cnt;ull _precisionBase=1000000;
#define _getchar() (*_inputPtr?*_inputPtr++:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr++))
#define _readSignAndNum(x) do{(x)=_getchar();}while((x)<=' ');_sign=(x)=='-';if(_sign)(x)=_getchar();for((x)-='0';(_c=_getchar())>='0';(x)=(x)*10+_c-'0')
#define _readFloatingPoint(x,T) for(T _div=1.0;(_c=_getchar())>='0';(x)+=(_c-'0')/(_div*=10))
#define rc(x) do{do{(x)=_getchar();}while((x)<=' ');}while(0)
#define ri(x) do{_readSignAndNum(x);if(_sign)(x)=-(x);}while(0)
#define rd(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,double);if(_sign)(x)=-(x);}while(0)
#define rld(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,ld);if(_sign)(x)=-(x);}while(0)
#define rcs(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>' ');(x)[_cur]='\0';}while(0)
#define rs(x) do{if(!_tempInputBuf)assert(0);rcs(_tempInputBuf);(x)=string(_tempInputBuf,_cur);}while(0)
#define rcln(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>=' ');(x)[_cur]='\0';}while(0)
#define rln(x) do{if(!_tempInputBuf)assert(0);rcln(_tempInputBuf);(x)=string(_tempInputBuf,_cur);}while(0)
#define setLength(x) do{if(_tempInputBuf)delete[](_tempInputBuf);_tempInputBuf=new char[(x)+1];}while(0)
void read(int&x){ri(x);}void read(uint&x){ri(x);}void read(ll&x){ri(x);}void read(ull&x){ri(x);}void read(double&x){rd(x);}void read(ld&x){rld(x);}
void read(char&x){rc(x);}void read(char*x){rcs(x);}void read(string&x){rs(x);}
template<typename T,typename...Ts>void read(T&&x,Ts&&...xs){read(x);read(forward<Ts>(xs)...);}
#define _flush() do{_flushBuf();fflush(stdout);}while(0)
#define _flushBuf() (fwrite(_outputBuffer,1,_outputPtr,stdout),_outputPtr=0)
#define _putchar(x) (_outputBuffer[_outputPtr==_bufferSize?_flushBuf():_outputPtr]=(x),_outputPtr++)
#define _writeTempBuf(x) (_tempOutputBuf[_tempOutputPtr++]=(x))
#define _writeOutput() for(int _i=0;_i<_tempOutputPtr;_putchar(_tempOutputBuf[_i++]));_tempOutputPtr=0
#define _writeNum(x,T,digits) _cnt=0;for(T _y=(x);_y;_y/=10,_cnt++)_numBuf[_numPtr++]='0'+_y%10;for(;_cnt<digits;_cnt++)_numBuf[_numPtr++]='0';_flushNumBuf();
#define _writeFloatingPoint(x,T) ull _I=(ull)(x);ull _F=((x)-_I)*_precisionBase+(T)(0.5);if(_F>=_precisionBase){_I++;_F=0;}_writeNum(_I,ull,1);_writeTempBuf('.');_writeNum(_F,ull,_precision)
#define _checkFinite(x) if(std::isnan(x)){wcs("NaN");}else if(std::isinf(x)){wcs("Inf");}
#define _flushNumBuf() for(;_numPtr;_writeTempBuf(_numBuf[--_numPtr]))
#define _fillBuf(x) for(int _i=0;_i<(x);_i++)_putchar(_fill)
#define _flushTempBuf() int _tempLen=_tempOutputPtr;_fillBuf(_width-_tempLen);_writeOutput();_fillBuf(-_width-_tempLen)
#define wb(x) do{if(x)_writeTempBuf('1');else _writeTempBuf('0');_flushTempBuf();}while(0)
#define wc(x) do{_writeTempBuf(x); _flushTempBuf();}while(0)
#define wi(x) do{if((x)<0){_writeTempBuf('-');_writeNum(-(x),uint,1);}else{_writeNum(x,uint,1);}_flushTempBuf();}while(0)
#define wll(x) do{if((x)<0){_writeTempBuf('-');_writeNum(-(x),ull,1);}else{_writeNum(x,ull,1);}_flushTempBuf();}while(0)
#define wd(x) do{_checkFinite(x)else if((x)<0){_writeTempBuf('-');_writeFloatingPoint(-(x),double);}else{_writeFloatingPoint(x,double);}_flushTempBuf();}while(0)
#define wld(x) do{_checkFinite(x)else if((x)<0){_writeTempBuf('-');_writeFloatingPoint(-(x),ld);}else{_writeFloatingPoint(x,ld);}_flushTempBuf();}while(0)
#define wcs(x) do{int _slen=strlen(x);_fillBuf(_width-_slen);for(const char*_p=(x);*_p;_putchar(*_p++));_fillBuf(-_width-_slen);}while(0)
#define ws(x) do{_fillBuf(_width-(int)(x).length());for(int _i=0;_i<(int)(x).length();_putchar(x[_i++]));_fillBuf(-_width-(int)(x).length());}while(0)
#define setPrecision(x) do{_precision=(x);_precisionBase=1;for(int _i=0;_i<(x);_i++,_precisionBase*=10);}while(0)
#define setDelimiter(x) do{_delimiter=(x);}while(0)
#define setWidth(x) do{_width=(x);}while(0)
#define setFill(x) do{_fill=(x);}while(0)
void write(bool x){wb(x);}void write(int x){wi(x);}void write(uint x){wi(x);}void write(ll x){wll(x);}void write(ull x){wll(x);}void write(double x){wd(x);}void write(ld x){wld(x);}
void write(char x){wc(x);}void write(char*x){wcs(x);}void write(const char*x){wcs(x);}void write(string&x){ws(x);}
template<typename T,typename...Ts>void write(T&&x,Ts&&...xs){write(x);for(const char*_p=_delimiter;*_p;_putchar(*_p++));write(forward<Ts>(xs)...);}
void writeln(){_putchar('\n');}template<typename...Ts>void writeln(Ts&&...xs){write(forward<Ts>(xs)...);_putchar('\n');}
void flush(){_flush();}class IOManager{public:~IOManager(){flush();}};unique_ptr<IOManager>_iomanager;

typedef int flowUnit;
typedef int costUnit;
const flowUnit FLOW_INF = 1 << 30;
const flowUnit FLOW_EPS = 0;
const costUnit COST_INF = 1 << 30;

class MaxFlowMinCost {
private:
    struct Edge {
        int from, to;
        costUnit origCost, cost;
        flowUnit cap;
        int next;
        Edge(int from, int to, costUnit cost, flowUnit cap, int next) : from(from), to(to), origCost(cost), cost(cost), cap(cap), next(next) {}
    };

    int N, src = 0, sink = 0;
    vector<Edge> e;
    vector<int> last, prev, index;
    vector<costUnit> phi, dist;

    bool dijkstra() {
        fill(dist.begin(), dist.end(), COST_INF);
        fill(prev.begin(), prev.end(), -1);
        fill(index.begin(), index.end(), -1);
        dist[src] = 0;
        priority_queue<pair<costUnit, int>, vector<pair<costUnit, int>>, greater<pair<costUnit, int>>> PQ;
        PQ.push({dist[src], src});
        while (!PQ.empty()) {
            pair<costUnit, int> v = PQ.top();
            PQ.pop();
            if (v.first > dist[v.second]) continue;
            for (int next = last[v.second]; next != -1; next = e[next].next) {
                if (abs(e[next].cap) <= FLOW_EPS) continue;
                costUnit d = dist[v.second] + e[next].cost + phi[v.second] - phi[e[next].to];
                if (dist[e[next].to] <= d) continue;
                dist[e[next].to] = d;
                prev[e[next].to] = v.second;
                index[e[next].to] = next;
                PQ.push({dist[e[next].to], e[next].to});
            }
        }
        return dist[sink] != COST_INF;
    }

public:
    MaxFlowMinCost(int N) : N(N), last(N, -1), prev(N), index(N), phi(N), dist(N) {}

    void addEdge(int u, int v, flowUnit flow, costUnit cost) {
        e.push_back({u, v, cost, flow, last[u]});
        last[u] = (int) e.size() - 1;
        e.push_back({v, u, -cost, 0, last[v]});
        last[v] = (int) e.size() - 1;
    }

    pair<flowUnit, costUnit> getMaxFlowMinCost(int src, int sink, flowUnit maxFlow) {
        this->src = src;
        this->sink = sink;
        flowUnit flow = 0;
        costUnit cost = 0;
        fill(phi.begin(), phi.end(), 0);
        while (flow < maxFlow && dijkstra()) {
            flowUnit aug = maxFlow - flow;
            int cur = sink;
            while (prev[cur] != -1) {
                aug = min(aug, e[index[cur]].cap);
                cur = prev[cur];
            }
            flow += aug;
            cur = sink;
            while (prev[cur] != -1) {
                e[index[cur]].cap -= aug;
                e[index[cur] ^ 1].cap += aug;
                cost += aug * e[index[cur]].origCost;
                cur = prev[cur];
            }
            for (int v = 0; v < N; v++) if (dist[v] != COST_INF) phi[v] += dist[v];
        }
        return {flow, cost};
    }
};

int N, M, K, T;
vector<pii> edges;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    read(N, M, K, T);
    int a, b;
    FOR(i, M) {
        read(a, b);
        edges.eb(a, b);
    }
    int lo = 1, hi = K, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        MaxFlowMinCost mfmc(N);
        for (pii &e : edges) {
            mfmc.addEdge(e.f, e.s, mid, 0);
            mfmc.addEdge(e.s, e.f, mid, 0);
            mfmc.addEdge(e.f, e.s, T, 1);
            mfmc.addEdge(e.s, e.f, T, 1);
        }
        pair<flowUnit, costUnit> res = mfmc.getMaxFlowMinCost(0, N - 1, K);
        if (res.f >= K && res.s <= T) hi = mid - 1;
        else lo = mid + 1;
    }
    writeln(lo - 1);
    return 0;
}
