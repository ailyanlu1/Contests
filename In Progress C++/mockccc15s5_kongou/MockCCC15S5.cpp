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
#define MAXT 200005
#define MAXM 100005

int N, M, T, A[MAXT], ans[MAXT];
vector<int> mods, verts, resetVerts;
vector<pii> concat[MAXM], edges[MAXM];

struct Node {
    int i, val, sum, l, r, p;
    bool lz, rev, keep, mod;

    void MOD() {
        if (keep && !mod) {
            mod = true;
            mods.pb(i);
        }
    }
};

int cnt = 0, cur = 0, keepCnt = 0, keepCur = 0;
Node keeps[MAXN + MAXM], LCT[MAXN + MAXM], resets[MAXN];

int makeNode(bool keep, int val) {
    ++cur;
    LCT[cur].i = cur;
    LCT[cur].l = LCT[cur].r = LCT[cur].p = LCT[cur].lz = LCT[cur].rev = LCT[cur].mod = 0;
    LCT[cur].val = LCT[cur].sum = val;
    LCT[cur].keep = keep;
    return cur;
}

void save() {
    keepCnt = cnt;
    keepCur = cur;
    for (int i : verts) {
        LCT[i].mod = false;
        keeps[i] = LCT[i];
    }
    verts.clear();
}

void saveReset() {
    for (int i : verts) {
        resetVerts.pb(i);
        LCT[i].mod = false;
        resets[i] = LCT[i];
    }
    verts.clear();
}

void revert() {
    for (int i : mods) LCT[i] = keeps[i];
    mods.clear();
    cnt = keepCnt;
    cur = keepCur;
}

void reset() {
    for (int i : resetVerts) LCT[i] = resets[i];
    resetVerts.clear();
    cnt = keepCnt = 0;
    cur = keepCur = N;
}

bool isRoot(int x) {
    return !LCT[x].p || (x != LCT[LCT[x].p].l && x != LCT[LCT[x].p].r);
}

void propagate(int x) {
    if (x) {
        LCT[x].MOD();
        if (LCT[x].l) LCT[LCT[x].l].MOD();
        if (LCT[x].r) LCT[LCT[x].r].MOD(); 
        if (LCT[x].rev) {
            LCT[x].rev ^= 1;
            swap(LCT[x].l, LCT[x].r);
            if (LCT[x].l) LCT[LCT[x].l].rev ^= 1;
            if (LCT[x].r) LCT[LCT[x].r].rev ^= 1;
        }
        LCT[x].val = LCT[x].lz ? 0 : LCT[x].val;
        LCT[x].sum = LCT[x].lz ? 0 : LCT[x].sum;
        if (LCT[x].l) LCT[LCT[x].l].lz |= LCT[x].lz;
        if (LCT[x].r) LCT[LCT[x].r].lz |= LCT[x].lz;
        LCT[x].lz = 0;
    }
}

void update(int x) {
    if (x) {
        LCT[x].MOD();
        LCT[x].sum = LCT[x].lz ? 0 : LCT[x].val;
        if (LCT[x].l) LCT[x].sum += LCT[LCT[x].l].lz || LCT[x].lz ? 0 : LCT[LCT[x].l].sum;
        if (LCT[x].r) LCT[x].sum += LCT[LCT[x].r].lz || LCT[x].lz ? 0 : LCT[LCT[x].r].sum;
    }
}

void connect(int ch, int par, bool hasCh, bool isL) {
    if (ch) {
        LCT[ch].p = par;
        LCT[ch].MOD();
    }
    if (hasCh) {
        if (isL) LCT[par].l = ch;
        else LCT[par].r = ch;
        LCT[par].MOD();
    }
}

void rotate(int x) {
    int p = LCT[x].p;
    int g = LCT[p].p;
    bool isRootP = isRoot(p);
    bool isL = x == LCT[p].l;
    connect(isL ? LCT[x].r : LCT[x].l, p, true, isL);
    connect(p, x, true, !isL);
    connect(x, g, !isRootP, isRootP ? false : p == LCT[g].l);
    update(p);
}

void splay(int x) {
    while (!isRoot(x)) {
        int p = LCT[x].p;
        int g = LCT[p].p;
        if (!isRoot(p)) propagate(g);
        propagate(p);
        propagate(x);
        if (!isRoot(p)) rotate((x == LCT[p].l) == (p == LCT[g].l) ? p : x);
        rotate(x);
    }
    propagate(x);
    update(x);
}

int expose(int x) {
    int last = 0;
    for (int y = x; y; y = LCT[y].p) {
        splay(y);
        LCT[y].l = last;
        LCT[y].MOD();
        last = y;
    }
    splay(x);
    LCT[x].MOD();
    return last;
}

void makeRoot(int x) {
    expose(x);
    LCT[x].rev ^= 1;
    LCT[x].MOD();
}

bool connected(int x, int y) {
    if (x == y) return true;
    expose(x);
    expose(y);
    return LCT[x].p;
}

void link(int x, int y) {
    makeRoot(x);
    LCT[x].p = y;
    LCT[x].MOD();
}

int modify(int a, int b) {
    makeRoot(a);
    expose(b);
    int old = LCT[b].sum;
    LCT[b].lz |= 1;
    update(b);
    return LCT[b].sum - old;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    iomanager.reset(new IOManager());
    // mt19937 rng(time(0));
    // N = 100000;
    // M = 300;
    // T = 200000;
    // FOR(i, T + 1) A[i] = rng() % M + 1;
    // int K, a, b;
    // For(i, 1, M + 1) {
        // K = 200000 / M;
        // FOR(j, K) {
            // a = rng() % N + 1;
            // do {
                // b = rng() % N + 1;
            // } while (a == b);
            // edges[i].eb(a, b);
        // }
    // }
    read(N, M, T);
    FOR(i, T + 1) read(A[i]);
    int K, a, b;
    For(i, 1, M + 1) {
        read(K);
        FOR(j, K) {
            read(a, b);
            edges[i].eb(a, b);
        }
    }
    FOR(i, T) concat[sz(edges[A[i]]) > sz(edges[A[i + 1]]) ? A[i] : A[i + 1]].eb(sz(edges[A[i]]) > sz(edges[A[i + 1]]) ? A[i + 1] : A[i], i);
    For(i, 1, N + 1) makeNode(true, 0);
    For(i, 1, M + 1) {
        if (sz(concat[i]) == 0) continue;
        sort(all(concat[i]));
        for (pii e : edges[i]) {
            verts.pb(e.f);
            verts.pb(e.s);
        }
        saveReset();
        for (pii e : edges[i]) {
            verts.pb(e.f);
            verts.pb(e.s);
            if (connected(e.f, e.s)) {
                cnt += modify(e.f, e.s);
            } else {
                int t = makeNode(true, 1);
                verts.pb(t);
                cnt++;
                link(e.f, t);
                link(e.s, t);
            }
        }
        pii last = {-1, -1};
        for (pii j : concat[i]) {
            if (j.f == i || j.f == last.f) continue;
            for (pii e : edges[j.f]) {
                verts.pb(e.f);
                verts.pb(e.s);
            }
            last = j;
        }
        save();
        last = {-1, -1};
        for (pii j : concat[i]) {
            if (j.f == last.f) {
                ans[j.s] = ans[last.s];
                continue;
            }
            if (j.f == i) {
                ans[j.s] = 0;
                continue;
            }
            for (pii e : edges[j.f]) {
                if (connected(e.f, e.s)) {
                    cnt += modify(e.f, e.s);
                } else {
                    int t = makeNode(false, 1);
                    cnt++;
                    link(e.f, t);
                    link(e.s, t);
                }
            }
            ans[j.s] = cnt;
            last = j;
            revert();
        }
        reset();
    }
    FOR(i, T) writeln(ans[i]);
    return 0;
}
