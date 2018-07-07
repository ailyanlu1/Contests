// https://www.hackerearth.com/problem/algorithm/yet-another-xor-problem-338cef44/
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

#define MAXN 50005
#define MAXQ 50005
#define MAXNODES (MAXN + MAXQ)
#define BSZ 800

seed_seq seq {
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};

mt19937 gen(seq);
uniform_real_distribution<double> dis(0.0, 1.0);

int N, Q, L[MAXNODES], R[MAXNODES], VAL[MAXNODES], XOR[MAXNODES], IND[MAXNODES], LZ[MAXNODES], SZ[MAXNODES], curNode = 0, ROOT[MAXNODES / BSZ + 5];
double PRI[MAXNODES];
pii A[MAXN];
char op[16];

int makeNode(int val, int ind) {
    ++curNode;
    assert(curNode < MAXNODES);
    VAL[curNode] = XOR[curNode] = val;
    IND[curNode] = ind;
    LZ[curNode] = 0;
    PRI[curNode] = dis(gen);
    SZ[curNode] = 1;
    L[curNode] = R[curNode] = 0;
    return curNode;
}

int size(int x) {
    return x ? SZ[x] : 0;
}

int Xor(int x) {
    return x ? XOR[x] : 0;
}

void apply(int x, int lz) {
    if (x) {
        IND[x] += lz;
        LZ[x] += lz;
    }
}

void update(int x) {
    if (x) {
        SZ[x] = 1 + size(L[x]) + size(R[x]);
        XOR[x] = VAL[x] ^ Xor(L[x]) ^ Xor(R[x]);
    }
}

void propagate(int x) {
    if (x && LZ[x]) {
        apply(L[x], LZ[x]);
        apply(R[x], LZ[x]);
        LZ[x] = 0;
    }
}

void merge(int &x, int l, int r) {
    propagate(l);
    propagate(r);
    if (!l || !r) {
        x = l ? l : r;
    } else if (PRI[l] > PRI[r]) {
        merge(R[l], R[l], r);
        x = l;
    } else {
        merge(L[r], l, L[r]);
        x = r;
    }
    update(x);
}

void split(int x, int &l, int &r, int ind) {
    if (!x) {
        l = r = 0;
        return;
    }
    propagate(x);
    if (ind <= IND[x]) {
        split(L[x], l, L[x], ind);
        r = x;
    } else {
        split(R[x], R[x], r, ind);
        l = x;
    }
    update(x);
}

void values(int x, vector<int> &vals) {
    if (!x) return;
    values(L[x], vals);
    vals.push_back(VAL[x]);
    values(R[x], vals);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    read(N, Q);
    FOR(i, N) {
        read(A[i].f);
        A[i].s = i;
    }
    sort(A, A + N);
    int lastAns = 0;
    int l, m, r, t, a, b, c, d;
    FOR(i, N) {
        split(ROOT[i / BSZ], l, r, A[i].s);
        merge(ROOT[i / BSZ], l, makeNode(A[i].f, A[i].s));
        merge(ROOT[i / BSZ], ROOT[i / BSZ], r);
    }
    FOR(q, Q) {
        read(t);
        if (t == 1) {
            read(a, b);
            for (int i = 0; i < N; i += BSZ) {
                split(ROOT[i / BSZ], l, r, a);
                apply(r, 1);
                merge(ROOT[i / BSZ], l, r);
            }
            split(ROOT[N / BSZ], l, r, a);
            merge(ROOT[N / BSZ], l, makeNode(b, a));
            merge(ROOT[N / BSZ], ROOT[N / BSZ], r);
            N++;
        } else {
            read(a, b, c, d);
            a = (lastAns ^ a) % N;
            b = (lastAns ^ b) % N;
            if (a > b) swap(a, b);
            c = (lastAns ^ c) % (b - a + 1);
            d = (lastAns ^ d) % (b - a + 1);
            if (c > d) swap(c, d);
            int cnt = 0;
            lastAns = 0;
            for (int i = 0; i < N; i += BSZ) {
                split(ROOT[i / BSZ], l, m, a);
                split(m, m, r, b + 1);
                if ((cnt <= c && cnt + size(m) > c) || (cnt <= d + 1 && cnt + size(m) > d + 1)) {
                    vector<int> vals;
                    values(m, vals);
                    sort(all(vals));
                    for (int v : vals) {
                        if (cnt >= c && cnt <= d) lastAns ^= v;
                        cnt++;
                    }
                } else if (cnt >= c && cnt + size(m) <= d + 1) {
                    lastAns ^= Xor(m);
                    cnt += size(m);
                } else {
                    cnt += size(m);
                }
                merge(ROOT[i / BSZ], l, m);
                merge(ROOT[i / BSZ], ROOT[i / BSZ], r);
                if (cnt >= d + 1) break;
            }
            writeln(lastAns);
        }
    }
    return 0;
}
