// https://www.spoj.com/problems/GOT/
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
#define _peekchar() (*_inputPtr?*_inputPtr:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr))
#define _getchar() (*_inputPtr?*_inputPtr++:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr++))
#define _hasNext() (*_inputPtr||!feof(stdin))
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
void read(char&x){rc(x);}void read(char*x){rcs(x);}void read(string&x){rs(x);}bool hasNext(){while(_hasNext()&&_peekchar()<=' ')_getchar();return _hasNext();}
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

#define MAXM 200005
#define MAXN 100005

int N, M, curInd, chainNum, C[MAXN], dep[MAXN], par[MAXN], chain[MAXN], size[MAXN], head[MAXN], ind[MAXN], T[MAXN * 2];
bool ans[MAXM];
pii CC[MAXN];
pair<pii, pii> Q[MAXM];
vector<int> adj[MAXN];

void build() {
    FOR(i, 2 * N) T[i] = -1;
}

void update(int i, int v) {
    for (T[i += (N - 1)] = v; i >>= 1;) T[i] = max(T[i << 1], T[i << 1 | 1]);
}

int query(int l, int r) {
    int ret = -1;
    for (l += (N - 1), r += (N - 1); l <= r; l >>= 1, r >>= 1) {
        if (l & 1) MAX(ret, T[l++]);
        if (!(r & 1)) MAX(ret, T[r--]);
    }
    return ret;
}

void dfs(int v, int d, int prev) {
    dep[v] = d;
    par[v] = prev;
    size[v] = 1;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs(w, d + 1, v);
        size[v] += size[w];
    }
}

void hld(int v, int prev) {
    if (head[chainNum] == -1) head[chainNum] = v;
    chain[v] = chainNum;
    ind[v] = curInd++;
    int maxIndex = -1;
    for (int w : adj[v]) if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
    if (maxIndex != -1) hld(maxIndex, v);
    for (int w : adj[v]) {
        if (w == prev || w == maxIndex) continue;
        chainNum++;
        hld(w, v);
    }
}

int lca(int v, int w) {
    while (chain[v] != chain[w]) {
        if (dep[head[chain[v]]] < dep[head[chain[w]]]) w = par[head[chain[w]]];
        else v = par[head[chain[v]]];
    }
    if (dep[v] < dep[w]) return v;
    return w;
}

int queryUp(int v, int w, int c) {
    int ret = -1;
    while (chain[v] != chain[w]) {
        MAX(ret, query(ind[head[chain[v]]], ind[v]));
        v = par[head[chain[v]]];
    }
    return max(ret, query(ind[w], ind[v]));
}

int queryPath(int v, int w, int c) {
    int lcaVertex = lca(v, w);
    return max(queryUp(v, lcaVertex, c), queryUp(w, lcaVertex, c));
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    while (hasNext()) {
        read(N, M);
        FOR(i, N) {
            adj[i].clear();
            head[i] = -1;
            read(C[i]);
            CC[i] = {C[i], i};
        }
        int a, b;
        FOR(i, N - 1) {
            read(a, b);
            adj[--a].pb(--b);
            adj[b].pb(a);
        }
        FOR(i, M) {
            read(Q[i].s.f, Q[i].s.s, Q[i].f.f);
            Q[i].s.f--;
            Q[i].s.s--;
            Q[i].f.s = i;
        }
        chainNum = 0;
        curInd = 1;
        dfs(0, 0, -1);
        hld(0, -1);
        sort(CC, CC + N);
        sort(Q, Q + M);
        int j = 0, k = 0;
        build();
        FOR(i, N + 1) {
            while (j < N && i == CC[j].f) {
                update(ind[CC[j].s], CC[j].f);
                j++;
            }
            while (k < M && i == Q[k].f.f) {
                ans[Q[k].f.s] = queryPath(Q[k].s.f, Q[k].s.s, Q[k].f.f) == Q[k].f.f;
                k++;
            }
        }
        FOR(i, M) writeln(ans[i] ? "Find" : "NotFind");
    }
    return 0;
}
