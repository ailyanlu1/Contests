// https://codeforces.com/contest/1017/problem/G
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
#define nl '\n'
#define sp ' '
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long
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
void flush(){_flush();}class IOManager{public:~IOManager(){flush();}};unique_ptr<IOManager>iomanager;

#define MAXN 100005

int N, Q, PAR[MAXN], CHAIN[MAXN], SZ[MAXN], HEAD[MAXN], PRE[MAXN], POST[MAXN], cur = 0, chainNum = 0;
pll T[MAXN * 4];
bool LZ[MAXN * 4];
vector<int> adj[MAXN];

void dfs(int v, int d) {
    SZ[v] = 1;
    for (int w : adj[v]) {
        dfs(w, d + 1);
        SZ[v] += SZ[w];
    }
}

void hld(int v) {
    if (HEAD[chainNum] == -1) HEAD[chainNum] = v;
    CHAIN[v] = chainNum;
    PRE[v] = ++cur;
    int maxInd = -1;
    for (int w : adj[v]) if (maxInd == -1 || SZ[maxInd] < SZ[w]) maxInd = w;
    if (maxInd != -1) hld(maxInd);
    for (int w : adj[v]) {
        if (w == maxInd) continue;
        chainNum++;
        hld(w);
    }
    POST[v] = cur;
}

pll merge(const pll &a, const pll &b) {
    return {max(a.f + b.s, b.f), a.s + b.s};
}

void build(int cur, int cL, int cR) {
    if (cL == cR) {
        T[cur] = {-1, -1};
        LZ[cur] = 0;
        return;
    }
    int m = cL + (cR - cL) / 2;
    build(cur * 2, cL, m);
    build(cur * 2 + 1, m + 1, cR);
    T[cur] = merge(T[cur * 2], T[cur * 2 + 1]);
}

void propagate(int cur, int cL, int cR) {
    if (LZ[cur]) {
        int m = cL + (cR - cL) / 2;
        T[cur * 2] = {-1, -(m - cL + 1)};
        T[cur * 2 + 1] = {-1, -(cR - m)};
        LZ[cur * 2] = LZ[cur * 2 + 1] = 1;
        LZ[cur] = 0;
    }
}

void reset(int cur, int cL, int cR, int l, int r) {
    if (cL > r || cR < l) return;
    if (cL != cR) propagate(cur, cL, cR);
    if (cL >= l && cR <= r) {
        T[cur] = {-1, -(cR - cL + 1)};
        LZ[cur] = 1;
        return;
    }
    int m = cL + (cR - cL) / 2;
    reset(cur * 2, cL, m, l, r);
    reset(cur * 2 + 1, m + 1, cR, l, r);
    T[cur] = merge(T[cur * 2], T[cur * 2 + 1]);
}

void inc(int cur, int cL, int cR, int ind, ll val) {
    if (cL > ind || cR < ind) return;
    if (cL != cR) propagate(cur, cL, cR);
    if (cL == cR) {
        T[cur].f += val;
        T[cur].s += val;
        return;
    }
    int m = cL + (cR - cL) / 2;
    inc(cur * 2, cL, m, ind, val);
    inc(cur * 2 + 1, m + 1, cR, ind, val);
    T[cur] = merge(T[cur * 2], T[cur * 2 + 1]);
}

pll query(int cur, int cL, int cR, int l, int r) {
    if (cL != cR) propagate(cur, cL, cR);
    if (cL > r || cR < l) return {-LL_INF, 0};
    if (cL >= l && cR <= r) return T[cur];
    int m = cL + (cR - cL) / 2;
    return merge(query(cur * 2, cL, m, l, r), query(cur * 2 + 1, m + 1, cR, l, r));
}

ll queryUp(int v) {
    pll ret = {-LL_INF, 0};
    while (v != 0) {
        ret = merge(query(1, 1, N, PRE[HEAD[CHAIN[v]]], PRE[v]), ret);
        v = PAR[HEAD[CHAIN[v]]];
    }
    return ret.f;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    iomanager.reset(new IOManager());
    read(N, Q);
    int t, v;
    PAR[1] = 0;
    For(i, 2, N + 1) {
        read(PAR[i]);
        adj[PAR[i]].pb(i);
    }
    FOR(i, N) HEAD[i] = -1;
    dfs(1, 0);
    hld(1);
    build(1, 1, N);
    FOR(i, Q) {
        read(t, v);
        if (t == 1) inc(1, 1, N, PRE[v], 1);
        else if (t == 2) {
            reset(1, 1, N, PRE[v], POST[v]);
            if (PAR[v] != 0) {
                ll x = queryUp(PAR[v]);
                if (x > 0) inc(1, 1, N, PRE[v], -x);
            }
        } else writeln(queryUp(v) >= 0 ? "black" : "white");
    }
    return 0;
}