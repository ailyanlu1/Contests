// https://www.hackerearth.com/practice/algorithms/graphs/minimum-cost-maximum-flow/practice-problems/algorithm/isomorphic-tree-70be4549/
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
#define nl '\n'
#define sp ' '
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

#define MAXNM 55

int N, M, rows, cols, dim, totalCost;
int costMatrix[MAXNM][MAXNM], labelByWorker[MAXNM], labelByJob[MAXNM], minSlackWorkerByJob[MAXNM], minSlackValueByJob[MAXNM], matchJobByWorker[MAXNM], matchWorkerByJob[MAXNM], parentWorkerByCommittedJob[MAXNM];
bool committedWorkers[MAXNM];
vector<int> G[MAXNM], H[MAXNM];

void match(int w, int j) {
    matchJobByWorker[w] = j;
    matchWorkerByJob[j] = w;
}

void updateLabeling(int slack) {
    for (int w = 0; w < dim; w++) {
        if (committedWorkers[w]) labelByWorker[w] += slack;
    }
    for (int j = 0; j < dim; j++) {
        if (parentWorkerByCommittedJob[j] != -1) labelByJob[j] -= slack;
        else minSlackValueByJob[j] -= slack;
    }
}

void reduce() {
    for (int w = 0; w < dim; w++) {
        int minCost = INT_INF;
        for (int j = 0; j < dim; j++) {
            minCost = min(minCost, costMatrix[w][j]);
        }
        for (int j = 0; j < dim; j++) {
            costMatrix[w][j] -= minCost;
        }
    }
    for (int j = 0; j < dim; j++) {
        int minCost = INT_INF;
        for (int w = 0; w < dim; w++) {
            minCost = min(minCost, costMatrix[w][j]);
        }
        for (int w = 0; w < dim; w++) {
            costMatrix[w][j] -= minCost;
        }
    }
}

void computeInitialSolution() {
    for (int j = 0; j < dim; j++) {
        labelByJob[j] = INT_INF;
    }
    for (int w = 0; w < dim; w++) {
        for (int j = 0; j < dim; j++) {
            if (costMatrix[w][j] < labelByJob[j]) {
                labelByJob[j] = costMatrix[w][j];
            }
        }
    }
}

void greedyMatch() {
    for (int w = 0; w < dim; w++) {
        for (int j = 0; j < dim; j++) {
            if (matchJobByWorker[w] == -1 && matchWorkerByJob[j] == -1 && costMatrix[w][j] - labelByWorker[w] - labelByJob[j] <= 0) match(w, j);
        }
    }
}

int getUnmatchedWorker() {
    for (int w = 0; w < dim; w++) {
        if (matchJobByWorker[w] == -1) return w;
    }
    return dim;
}

void initialize(int w) {
    for (int i = 0; i < dim; i++) {
        committedWorkers[i] = false;
        parentWorkerByCommittedJob[i] = -1;
    }
    committedWorkers[w] = true;
    for (int j = 0; j < dim; j++) {
        minSlackValueByJob[j] = costMatrix[w][j] - labelByWorker[w] - labelByJob[j];
        minSlackWorkerByJob[j] = w;
    }
}

void execute() {
    while (true) {
        int minSlackWorker = -1;
        int minSlackJob = -1;
        int minSlackValue = INT_INF;
        for (int j = 0; j < dim; j++) {
            if (parentWorkerByCommittedJob[j] == -1) {
                if (minSlackValueByJob[j] < minSlackValue) {
                    minSlackValue = minSlackValueByJob[j];
                    minSlackWorker = minSlackWorkerByJob[j];
                    minSlackJob = j;
                }
            }
        }
        if (minSlackValue > 0) updateLabeling(minSlackValue);
        parentWorkerByCommittedJob[minSlackJob] = minSlackWorker;
        if (matchWorkerByJob[minSlackJob] == -1) {
            int committedJob = minSlackJob;
            int parentWorker = parentWorkerByCommittedJob[committedJob];
            while (true) {
                int temp = matchJobByWorker[parentWorker];
                match(parentWorker, committedJob);
                committedJob = temp;
                if (committedJob == -1) break;
                parentWorker = parentWorkerByCommittedJob[committedJob];
            }
            return;
        } else {
            int worker = matchWorkerByJob[minSlackJob];
            committedWorkers[worker] = true;
            for (int j = 0; j < dim; j++) {
                if (parentWorkerByCommittedJob[j] == -1) {
                    int slack = costMatrix[worker][j] - labelByWorker[worker] - labelByJob[j];
                    if (minSlackValueByJob[j] > slack) {
                        minSlackValueByJob[j] = slack;
                        minSlackWorkerByJob[j] = worker;
                    }
                }
            }
        }
    }
}

void HungarianAlgorithm(vector<vector<int>> &matrix, int workers, int jobs) {
    dim = max(workers, jobs);
    rows = workers;
    cols = jobs;
    for (int w = 0; w < dim; w++) {
        if (w < rows) {
            for (int j = 0; j < dim; j++) {
                if (j < cols) costMatrix[w][j] = matrix[w][j];
                else costMatrix[w][j] = 0;
            }
        } else {
            for (int j = 0; j < dim; j++) {
                costMatrix[w][j] = 0;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        labelByWorker[i] = 0;
        labelByJob[i] = 0;
        minSlackWorkerByJob[i] = 0;
        minSlackValueByJob[i] = 0;
        matchJobByWorker[i] = -1;
        matchWorkerByJob[i] = -1;
        parentWorkerByCommittedJob[i] = -1;
        committedWorkers[i] = false;
    }
    reduce();
    computeInitialSolution();
    greedyMatch();
    int w = getUnmatchedWorker();
    while (w < dim) {
        initialize(w);
        execute();
        w = getUnmatchedWorker();
    }
    for (w = 0; w < rows; w++) {
        if (matchJobByWorker[w] >= cols) matchJobByWorker[w] = -1;
    }
    for (int j = 0; j < cols; j++) {
        if (matchWorkerByJob[j] >= rows) matchWorkerByJob[j] = -1;
    }
    totalCost = 0;
    for (int w = 0; w < rows; w++) {
        if (matchJobByWorker[w] != -1) totalCost += matrix[w][matchJobByWorker[w]];
    }
}

int dfs(int n, int m, int prevn, int prevm) {
    vector<vector<int>> mat;
    for (int v : G[n]) {
        if (v == prevn) continue;
        mat.eb();
        for (int w : H[m]) {
            if (w == prevm) continue;
            mat.back().pb(-dfs(v, w, n, m));
        }
    }
    if (sz(mat) == 0 || sz(mat[0]) == 0) return 1;
    HungarianAlgorithm(mat, mat.size(), mat[0].size());
    return 1 - totalCost;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    iomanager.reset(new IOManager());
    read(N, M);
    int a, b;
    FOR(i, N - 1) {
        read(a, b);
        G[--a].pb(--b);
        G[b].pb(a);
    }
    FOR(i, M - 1) {
        read(a, b);
        H[--a].pb(--b);
        H[b].pb(a);
    }
    setDelimiter("");
    FOR(i, N) FOR(j, M) write(N + M - 2 * dfs(i, j, -1, -1), " \n"[j == M - 1]);
    return 0;
}
