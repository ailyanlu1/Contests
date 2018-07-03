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
void write(int x){wi(x);}void write(uint x){wi(x);}void write(ll x){wll(x);}void write(ull x){wll(x);}void write(double x){wd(x);}void write(ld x){wld(x);}
void write(char x){wc(x);}void write(char*x){wcs(x);}void write(const char*x){wcs(x);}void write(string&x){ws(x);}
template<typename T,typename...Ts>void write(T&&x,Ts&&...xs){write(x);for(const char*_p=_delimiter;*_p;_putchar(*_p++));write(forward<Ts>(xs)...);}
void writeln(){_putchar('\n');}template<typename...Ts>void writeln(Ts&&...xs){write(forward<Ts>(xs)...);_putchar('\n');}
void flush(){_flush();}class IOManager{public:~IOManager(){flush();}};unique_ptr<IOManager>_iomanager;

struct FenwickTree {
private:
    int N, LGN;
    vector<int> cntBIT, cntA;
    vector<ll> sumBIT, sumA;
    int totalCnt;
    ll totalSum;

public:
    FenwickTree(int N): N(N), LGN(31 - __builtin_clz(N)), cntBIT(N + 1), cntA(N + 1), sumBIT(N + 1), sumA(N + 1), totalCnt(0), totalSum(0) {
        fill(all(sumBIT), 0);
        fill(all(sumA), 0);
        fill(all(cntBIT), 0);
        fill(all(cntA), 0);
    }

    int rsqCnt(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += cntBIT[i];
        return sum;
    }

    ll rsqSum(int i) {
        ll sum = 0;
        for (; i > 0; i -= i & -i) sum += sumBIT[i];
        return sum;
    }

    void update(int i, ll v, int delta) {
        totalCnt += delta;
        totalSum += v;
        cntA[i] += delta;
        sumA[i] += v;
        for (; i <= N; i += i & -i) {
            cntBIT[i] += delta;
            sumBIT[i] += v;
        }
    }

    int lower_bound_cnt(int v) {
        int ind = 0, i = 0;
        int sum = 0;
        for (int x = LGN; x >= 0; x--) {
            i = ind | (1 << x);
            if (i > N) continue;
            if (sum + cntBIT[i] < v) {
                ind = i;
                sum += cntBIT[i];
            }
        }
        return ind + 1;
    }

    int getCnt(int i) {
        return cntA[i];
    }

    int getTotalCnt() {
        return totalCnt;
    }

    ll getSum(int i) {
        return sumA[i];
    }

    ll getTotalSum() {
        return totalSum;
    }
};

#define MAXN 100005

int K, N, B[MAXN * 2];

struct House {
    char z1, z2;
    int b1, b2, c1, c2;
} H[MAXN];

bool cmpHouse(const int &a, const int &b) {
    return H[a].b1 + H[a].b2 < H[b].b1 + H[b].b2;
}

ll getPairingValue(FenwickTree &ft) {
    ll ret = 0;
    if (ft.getTotalCnt() > 1) {
        int medianInd = ft.lower_bound_cnt(ft.getTotalCnt() / 2);
        ll medianVal = ft.getSum(medianInd) / ft.getCnt(medianInd);
        ret += ft.getTotalSum() - 2 * (ft.rsqSum(medianInd - 1) + ((ft.getTotalCnt() / 2) - ft.rsqCnt(medianInd - 1)) * medianVal);
        if (ft.getTotalCnt() % 2 == 1) ret += medianVal;
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    read(K, N);
    FOR(i, N) {
        read(H[i].z1, H[i].b1, H[i].z2, H[i].b2);
        B[i * 2] = H[i].b1;
        B[i * 2 + 1] = H[i].b2;
    }
    sort(B, B + N * 2);
    int M = unique(B, B + N * 2) - B;
    FOR(i, N) {
        H[i].c1 = lower_bound(B, B + M, H[i].b1) - B + 1;
        H[i].c2 = lower_bound(B, B + M, H[i].b2) - B + 1;
    }
    if (K == 1) {
        ll ans = 0;
        FenwickTree ft(M);
        for (int i = 0; i < N; i++) {
            if (H[i].z1 == H[i].z2) ans += abs(H[i].b1 - H[i].b2);
            else {
                ft.update(H[i].c1, H[i].b1, 1);
                ft.update(H[i].c2, H[i].b2, 1);
            }
        }
        ans += getPairingValue(ft) + ft.getTotalCnt() / 2;
        writeln(ans);
    } else {
        ll ans = 0;
        FenwickTree ft1(M);
        FenwickTree ft2(M);
        vector<int> ind;
        for (int i = 0; i < N; i++) {
            if (H[i].z1 == H[i].z2) ans += abs(H[i].b1 - H[i].b2);
            else {
                ft1.update(H[i].c1, H[i].b1, 1);
                ft1.update(H[i].c2, H[i].b2, 1);
                ind.pb(i);
            }
        }
        if (!ind.empty()) {
            ll add = LL_INF;
            sort(all(ind), cmpHouse);
            for (int i : ind) {
                ft1.update(H[i].c1, -H[i].b1, -1);
                ft1.update(H[i].c2, -H[i].b2, -1);
                ft2.update(H[i].c1, H[i].b1, 1);
                ft2.update(H[i].c2, H[i].b2, 1);
                MIN(add, getPairingValue(ft1) + getPairingValue(ft2));
            }
            ans += add + (ft1.getTotalCnt() + ft2.getTotalCnt()) / 2;
        }
        writeln(ans);
    }
    return 0;
}
