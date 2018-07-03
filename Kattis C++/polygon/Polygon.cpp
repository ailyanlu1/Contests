// https://open.kattis.com/problems/polygon
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

#define Segment pair<pair<pii, pii>, int>
#define PointInfo pair<pii, pii>
#define x first
#define y second
#define P1 first.first
#define P2 first.second

struct ycmp {
    const bool operator ()(const Segment &L1, const Segment &L2) const {
        return L1.P1.y == L2.P1.y ? (L1.P1.x == L2.P1.x ? (L1.P2 == L2.P2 ? L1.s < L2.s : L1.P2 < L2.P2) : L1.P1.x < L2.P1.x) : L1.P1.y < L2.P1.y;
    }
};

int ccw(const pii &a, const pii &b, const pii &c) {
    int area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area2 < 0) return -1;
    else if (area2 > 0) return +1;
    else return 0;
}

bool onSegment(const pii &a, const pii &p, const pii &q) {
    return a.x <= max(p.x, q.x) && a.x >= min(p.x, q.x) && a.y <= max(p.y, q.y) && a.y >= min(p.y, q.y);
}

bool hasLOI(const Segment &L1, const Segment &L2) {
    int A1 = L1.P2.y - L1.P1.y;
    int B1 = L1.P1.x - L1.P2.x;
    int A2 = L2.P2.y - L2.P1.y;
    int B2 = L2.P1.x - L2.P2.x;
    if (A1 * B2 - A2 * B1 != 0) return false;
    if (L1.P1 == L1.P2 || L2.P1 == L2.P2) return false;
    vector<pii> P = {L1.P1, L1.P2, L2.P1, L2.P2};
    sort(all(P));
    return P[1] != P[2];
}

bool intersect(const Segment &L1, const Segment &L2, int N) {
    if ((L1.s + 1) % N == L2.s || (L2.s + 1) % N == L1.s) return hasLOI(L1, L2);
    int o1 = ccw(L1.P1, L1.P2, L2.P1);
    int o2 = ccw(L1.P1, L1.P2, L2.P2);
    int o3 = ccw(L2.P1, L2.P2, L1.P1);
    int o4 = ccw(L2.P1, L2.P2, L1.P2);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(L2.P1, L1.P1, L1.P2)) return true;
    if (o2 == 0 && onSegment(L2.P2, L1.P1, L1.P2)) return true;
    if (o3 == 0 && onSegment(L1.P1, L2.P1, L2.P2)) return true;
    if (o4 == 0 && onSegment(L1.P2, L2.P1, L2.P2)) return true;
    return false;
}
bool solve(int N) {
    vector<Segment> seg(N);
    FOR(i, N) {
        read(seg[i].P1.x, seg[i].P1.y);
        seg[(i + 1) % N].P2 = seg[i].P1;
        seg[i].s = i;
    }
    vector<PointInfo> P(2 * N);
    FOR(h, 2) {
        FOR(i, N) {
            if (h == 0 && seg[i].P1 > seg[i].P2) swap(seg[i].P1, seg[i].P2);
            else if (h == 1 && seg[i].P1 < seg[i].P2) swap(seg[i].P1, seg[i].P2);
            P[i * 2].f = seg[i].P1;
            P[i * 2].s.f = 0;
            P[i * 2].s.s = i;
            P[i * 2 + 1].f = seg[i].P2;
            P[i * 2 + 1].s.f = 1;
            P[i * 2 + 1].s.s = i;
        }
        sort(all(P));
        if (h == 1) reverse(all(P));
        set<Segment, ycmp> S;
        for (PointInfo &p : P) {
            if (p.s.f == 0) {
                auto it = S.insert(seg[p.s.s]).f;
                if (it != S.begin() && intersect(*it, *prev(it), N)) return false;
                auto nextIt = next(it);
                if (nextIt != S.end() && intersect(*it, *nextIt, N)) return false;
            } else {
                auto it = S.find(seg[p.s.s]);
                auto nextIt = next(it);
                if (it != S.begin() && nextIt != S.end() && intersect(*prev(it), *nextIt, N)) return false;
                S.erase(seg[p.s.s]);
            }
        }
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    _iomanager.reset(new IOManager());
    int N;
    for(int i = 1; ; i++) {
        read(N);
        if (N == 0) break;
        else if (solve(N)) writeln("YES");
        else writeln("NO");
    }
    return 0;
}
