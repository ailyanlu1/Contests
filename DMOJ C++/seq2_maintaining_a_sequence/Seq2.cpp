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

#define MAXNODES 5000005

seed_seq seq {
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};

mt19937 gen(seq);
uniform_real_distribution<double> dis(0.0, 1.0);

int N, M, L[MAXNODES], R[MAXNODES], LZ[MAXNODES], VAL[MAXNODES], MX[MAXNODES], SUM[MAXNODES], PRE[MAXNODES], SUF[MAXNODES], MAXSUM[MAXNODES], SZ[MAXNODES], root = 0, curNode = 0;
bool REV[MAXNODES];
double PRI[MAXNODES];
char op[16];

int makeNode(int val) {
    ++curNode;
    assert(curNode < MAXNODES);
    VAL[curNode] = val;
    MX[curNode] = SUM[curNode] = val;
    PRE[curNode] = SUF[curNode] = MAXSUM[curNode] = max(val, 0);
    LZ[curNode] = INT_INF;
    REV[curNode] = 0;
    PRI[curNode] = dis(gen);
    SZ[curNode] = 1;
    L[curNode] = R[curNode] = 0;
    return curNode;
}

int size(int x) {
    return x ? SZ[x] : 0;
}

int max(int x) {
    return x ? MX[x] : -INT_INF;
}

int sum(int x) {
    return x ? SUM[x] : 0;
}

int pre(int x) {
    return x ? PRE[x] : 0;
}

int suf(int x) {
    return x ? SUF[x] : 0;
}

int maxSum(int x) {
    return x ? MAXSUM[x] : 0;
}

void setVal(int x, int val) {
    if (x) {
        MX[x] = VAL[x] = LZ[x] = val;
        SUM[x] = val * size(x);
        PRE[x] = SUF[x] = MAXSUM[x] = max(SUM[x], 0);
    }
}

void reverse(int x) {
    if (x) REV[x] ^= 1;
}

void update(int x) {
    if (x) {
        SZ[x] = 1 + size(L[x]) + size(R[x]);
        MX[x] = max(VAL[x], max(max(L[x]), max(R[x])));
        SUM[x] = VAL[x] + sum(L[x]) + sum(R[x]);
        PRE[x] = max(max(pre(L[x]), max(sum(L[x]) + VAL[x], sum(L[x]) + VAL[x] + pre(R[x]))), 0);
        SUF[x] = max(max(suf(R[x]), max(VAL[x] + sum(R[x]), suf(L[x]) + VAL[x] + sum(R[x]))), 0);
        MAXSUM[x] = max(max(max(suf(L[x]) + VAL[x], VAL[x] + pre(R[x])), max(max(suf(L[x]) + VAL[x] + pre(R[x]), VAL[x]), max(maxSum(L[x]), maxSum(R[x])))), 0);
    }
}

void propagate(int x) {
    if (x) {
        if (REV[x]) {
            reverse(x);
            swap(L[x], R[x]);
            if (L[x]) {
                reverse(L[x]);
                swap(PRE[L[x]], SUF[L[x]]);
            }
            if (R[x]) {
                reverse(R[x]);
                swap(PRE[R[x]], SUF[R[x]]);
            }
        }
        if (LZ[x] != INT_INF) {
            if (L[x]) setVal(L[x], LZ[x]);
            if (R[x]) setVal(R[x], LZ[x]);
            LZ[x] = INT_INF;
        }
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
    if (ind <= size(L[x])) {
        split(L[x], l, L[x], ind);
        r = x;
    } else {
        split(R[x], R[x], r, ind - size(L[x]) - 1);
        l = x;
    }
    update(x);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    read(N, M);
    int l, mid, r, p, len, x;
    FOR(i, N) {
        read(x);
        merge(root, root, makeNode(x));
    }
    FOR(i, M) {
        read(op);
        if (op[0] == 'I') {
            read(p, len);
            mid = 0;
            FOR(j, len) {
                read(x);
                merge(mid, mid, makeNode(x));
            }
            split(root, l, r, p);
            merge(root, l, mid);
            merge(root, root, r);
        } else if (op[0] == 'D') {
            read(p, len);
            split(root, l, mid, p - 1);
            split(mid, mid, r, len);
            merge(root, l, r);
        } else if (op[0] == 'R') {
            read(p, len);
            split(root, l, mid, p - 1);
            split(mid, mid, r, len);
            reverse(mid);
            merge(root, l, mid);
            merge(root, root, r);
        } else if (op[0] == 'G') {
            read(p, len);
            split(root, l, mid, p - 1);
            split(mid, mid, r, len);
            writeln(sum(mid));
            merge(root, l, mid);
            merge(root, root, r);
        } else if (op[0] == 'M' && op[2] == 'K') {
            read(p, len, x);
            split(root, l, mid, p - 1);
            split(mid, mid, r, len);
            setVal(mid, x);
            merge(root, l, mid);
            merge(root, root, r);  
        } else if (op[0] == 'M' && op[2] == 'X') {
            if (max(root) < 0) writeln(max(root));
            else writeln(maxSum(root)); 
        } else {
            i--;
        }
    }
    return 0;
}
