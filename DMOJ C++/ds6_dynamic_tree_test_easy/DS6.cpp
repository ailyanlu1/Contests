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
void flush(){_flush();}class IOManager{public:~IOManager(){flush();}};unique_ptr<IOManager>iomanager;

#define MAXN 100005

#define INC 1
#define ASSIGN 2

int N, M, ROOT, VAL[MAXN], MN[MAXN], MX[MAXN], SUM[MAXN], LZ[MAXN], FL[MAXN], SZ[MAXN], L[MAXN], R[MAXN], P[MAXN];
bool REV[MAXN];
vector<int> adj[MAXN];

void makeNode(int vert, int val) {
    FL[vert] = LZ[vert] = L[vert] = R[vert] = P[vert] = 0;
    REV[vert] = false;
    VAL[vert] = SUM[vert] = MN[vert] = MX[vert] = val;
    SZ[vert] = 1;
}

bool isRoot(int x) {
    return !P[x] || (x != L[P[x]] && x != R[P[x]]);
}

int getSize(int x) {
    return x ? SZ[x] : 0;
}

int getMin(int x) {
    return x ? MN[x] : INT_MAX;
}

int getMax(int x) {
    return x ? MX[x] : INT_MIN;
}

int getSum(int x) {
    return x ? SUM[x] : 0;
}

int apply(int val, int lz, int fl) {
    if (fl == ASSIGN) return lz;
    else if (fl == INC) return val + lz;
    else return val;
}

void propagate(int x) {
    if (x) {
        if (REV[x]) {
            REV[x] ^= 1;
            swap(L[x], R[x]);
            if (L[x]) REV[L[x]] ^= 1;
            if (R[x]) REV[R[x]] ^= 1;
        }
        VAL[x] = apply(VAL[x], LZ[x], FL[x]);
        SUM[x] = apply(SUM[x], LZ[x] * SZ[x], FL[x]);
        MN[x] = apply(MN[x], LZ[x], FL[x]);
        MX[x] = apply(MX[x], LZ[x], FL[x]);
        if (L[x]) {
            LZ[L[x]] = apply(LZ[L[x]], LZ[x], FL[x]);
            MAX(FL[L[x]], FL[x]);
        }
        if (R[x]) {
            LZ[R[x]] = apply(LZ[R[x]], LZ[x], FL[x]);
            MAX(FL[R[x]], FL[x]);
        }
        LZ[x] = FL[x] = 0;
    }
}

void update(int x) {
    if (x) {
        SUM[x] = MN[x] = MX[x] = apply(VAL[x], LZ[x], FL[x]);
        SZ[x] = 1;
        if (L[x]) {
            SUM[x] += apply(SUM[L[x]], apply(LZ[L[x]], LZ[x], FL[x]) * SZ[L[x]], max(FL[L[x]], FL[x]));
            MIN(MN[x], apply(MN[L[x]], apply(LZ[L[x]], LZ[x], FL[x]), FL[L[x]]));
            MAX(MX[x], apply(MX[L[x]], apply(LZ[L[x]], LZ[x], FL[x]), FL[L[x]]));
            SZ[x] += SZ[L[x]];
        }
        if (R[x]) {
            SUM[x] += apply(SUM[R[x]], apply(LZ[R[x]], LZ[x], FL[x]) * SZ[R[x]], max(FL[R[x]], FL[x]));
            MIN(MN[x], apply(MN[R[x]], apply(LZ[R[x]], LZ[x], FL[x]), FL[R[x]]));
            MAX(MX[x], apply(MX[R[x]], apply(LZ[R[x]], LZ[x], FL[x]), FL[R[x]]));
            SZ[x] += SZ[R[x]];
        }
    }
}

void connect(int ch, int par, bool hasCh, bool isL) {
    if (ch) P[ch] = par;
    if (hasCh) {
        if (isL) L[par] = ch;
        else R[par] = ch;
    }
}

void rotate(int x) {
    int p = P[x];
    int g = P[p];
    bool isRootP = isRoot(p);
    bool isL = x == L[p];
    connect(isL ? R[x] : L[x], p, true, isL);
    connect(p, x, true, !isL);
    connect(x, g, !isRootP, isRootP ? false : p == L[g]);
    update(p);
}

void splay(int x) {
    while (!isRoot(x)) {
        int p = P[x];
        int g = P[p];
        if (!isRoot(p)) propagate(g);
        propagate(p);
        propagate(x);
        if (!isRoot(p)) rotate((x == L[p]) == (p == L[g]) ? p : x);
        rotate(x);
    }
    propagate(x);
    update(x);
}

int expose(int x) {
    int last = 0;
    for (int y = x; y; y = P[y]) {
        splay(y);
        L[y] = last;
        last = y;
    }
    splay(x);
    return last;
}

void makeRoot(int x) {
    expose(x);
    REV[x] ^= 1;
}

int lca(int x, int y) {
    makeRoot(ROOT);
    expose(x);
    return expose(y);
}

bool link(int x, int y) {
    makeRoot(ROOT);
    expose(x);
    if (R[x]) return false;
    P[x] = y;
    return true;
}

bool cutParent(int x) {
    makeRoot(ROOT);
    expose(x);
    if (!R[x]) return false;
    R[x] = P[R[x]] = 0;
    return true;
}

void update(int from, int to, int val, int fl) {
    makeRoot(from);
    expose(to);
    LZ[to] = apply(LZ[to], val, fl);
    MAX(FL[to], fl);
    update(to);
}

int querySum(int from, int to) {
    makeRoot(from);
    expose(to);
    return getSum(to);
}

int queryMin(int from, int to) {
    makeRoot(from);
    expose(to);
    return getMin(to);
}

int queryMax(int from, int to) {
    makeRoot(from);
    expose(to);
    return getMax(to);
}

void dfs(int v, int prev) {
    for (int w : adj[v]) {
        if (w == prev) continue;
        assert(link(w, v));
        dfs(w, v);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    iomanager.reset(new IOManager());
    read(N, M);
    int a, b, c;
    For(i, 1, N + 1) {
        read(c);
        makeNode(i, c);
    }
    FOR(i, N - 1) {
        read(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    read(ROOT);
    dfs(ROOT, -1);
    int k;
    FOR(i, M) {
        read(k);
        switch(k) {
            case 0:
                read(ROOT);
                break;
            case 1:
                read(a, b, c);
                update(a, b, c, ASSIGN);
                break;
            case 2:
                read(a, b, c);
                update(a, b, c, INC);
                break;
            case 3:
                read(a, b);
                writeln(queryMin(a, b));
                break;
            case 4:
                read(a, b);
                writeln(queryMax(a, b));
                break;
            case 5:
                read(a, b);
                writeln(querySum(a, b));
                break;
            case 6:
                read(a, b);
                if (lca(a, b) != a) {
                    assert(cutParent(a));
                    assert(link(a, b));
                }
                break;
            case 7:
                read(a, b);
                writeln(lca(a, b));
                break;
            default:
                assert(false);
                break;
        }
    }
    return 0;
}
