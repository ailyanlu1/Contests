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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

template <class T> struct is_iterator {
  template <class U, typename enable_if<!is_convertible<U, const char*>::value, int>::type = 0>
  constexpr static auto has_indirection(int) -> decltype(*declval<U>(), bool()) { return true; }
  template <class> constexpr static bool has_indirection(long) { return false; }
  constexpr static bool value = has_indirection<T>(0);
};

using uint = unsigned int;
// Buffer size should be 2^12 or 2^13 for optimal performance with files.
const uint BUFFER_SIZE = 1 << 12;
// Maximum possible length of a string representing primitive type
// assuming we won't encounter huge double values.
const uint MAX_LENGTH = 1 << 7;

namespace Detail {
  struct Width { uint value; };
  struct Fill { char value; };
  struct Base { uint value; };
  struct Precision { uint value; };
  struct Delimiter { const char* value; };
}  // namespace Detail

Detail::Width setWidth(uint value = 0) { return {value}; }
Detail::Fill setFill(char value = ' ') { return {value}; }
Detail::Base setBase(uint value = 10) { assert(2 <= value && value <= 36); return {value}; }
Detail::Precision setPrecision(uint value = 9) { assert(value < MAX_LENGTH); return {value}; }
Detail::Delimiter setDelimiter(const char* value = " ") { return {value}; }

/******************************* input classes ********************************/
class InputDevice {
protected:
  const char* head;
  const char* tail;

  InputDevice(const char* head, const char* tail) : head(head), tail(tail), base(setBase().value) {}

  virtual void fillInput() = 0;

  inline char nextChar() {
    if (__builtin_expect(head >= tail, false)) fillInput();
    return *head++;
  }

  template <class I> int readUnsignedIntGeneral(I& arg, char c) {
    I value = 0;
    int length = 0;
    for (;; ++length, c = nextChar()) {
      if (isDigit(c)) c -= '0';
      else if (isUpper(c)) c -= 'A' - 10;
      else if (isLower(c)) c -= 'a' - 10;
      else c = base;
      if ((uint) c >= base) break;
      value = base * value + c;
    }
    arg = value;
    return --head, length;
  }

  template <class I> inline int readUnsignedInt(I& arg, char c) {
    if (__builtin_expect(base > 10, false)) return readUnsignedIntGeneral(arg, c);
    I value = 0;
    int length = 0;
    for (; static_cast<unsigned char>(c - '0') < base; ++length, c = nextChar())
      value = base * value + c - '0';
    arg = value;
    return --head, length;
  }

  template <class I> inline bool readSignedInt(I& arg, char c) {
    bool negative = c == '-';
    if (negative) c = nextChar();
    typename make_unsigned<I>::type unsignedArg;
    if (readUnsignedInt(unsignedArg, c) == 0) return false;
    arg = negative ? ~static_cast<I>(unsignedArg - 1) : static_cast<I>(unsignedArg);
    return true;
  }

  template <class F> bool readFloatingPoint(F& arg, char c) {
    bool negative = c == '-';
    if (negative) c = nextChar();
    unsigned long long integerPart;
    if (readUnsignedInt(integerPart, c) == 0) return false;
    arg = static_cast<F>(integerPart);
    if (nextChar() == '.') {
      unsigned long long fractionalPart = 0;
      int fractionalLength = readUnsignedInt(fractionalPart, nextChar());
      if (fractionalLength > 0) {
        unsigned long long basePower = 1;
        for (; fractionalLength; --fractionalLength) basePower *= base;
        arg += static_cast<F>(fractionalPart) / basePower;
      }
    } else --head;
    if (negative) arg = -arg;
    return true;
  }

public:
  uint base;

  InputDevice(InputDevice const&) = delete;
  InputDevice& operator = (InputDevice const&) = delete;

  static inline bool isSpace(char c) { return static_cast<unsigned char>(c - '\t') < 5 || c == ' '; }
  static inline bool isDigit(char c) { return static_cast<unsigned char>(c - '0') < 10; }
  static inline bool isUpper(char c) { return static_cast<unsigned char>(c - 'A') < 26; }
  static inline bool isLower(char c) { return static_cast<unsigned char>(c - 'a') < 26; }
  static inline bool isOneOf(char c, const char* str) { return strchr(str, c) != nullptr; }

  void putBack() { --head; }  // can be called only once directly after successfully reading a character

  inline bool readChar(char& arg) {
    if (__builtin_expect(head >= tail, false)) {
      fillInput();
      if (__builtin_expect(head >= tail, false)) return arg = '\0', false;
    }
    return arg = *head++, true;
  }

  template <class UnaryPredicate>
  inline char skipCharacters(UnaryPredicate isSkipped) {
    char c;
    do { c = nextChar(); } while (isSkipped(c));
    return c;
  }
  inline char skipCharacters() { return skipCharacters(isSpace); }

  template <class UnaryPredicate>
  inline int readString(char* arg, int limit, UnaryPredicate isTerminator) {
    skipCharacters(isTerminator);
    // put back first non-skipped character, reserve space for null character
    int charsRead = 0;
    for (--head, --limit; head < tail; fillInput()) {
      ptrdiff_t chunkSize = find_if(head, min(tail, head + limit - charsRead), isTerminator) - head;
      arg = copy_n(head, chunkSize, arg);
      head += chunkSize;
      charsRead += chunkSize;
      if (chunkSize == 0 || head < tail) break;
    }
    return *arg = '\0', charsRead;
  }

  inline int readString(char* arg, int limit, const char* terminators) {
    if (!*terminators) return readString(arg, limit, InputDevice::isSpace);
    return readString(arg, limit, [terminators](char c) { return InputDevice::isOneOf(c, terminators); });
  }

  // property setters
  inline bool read(Detail::Base newBase) { base = newBase.value; return true; }
  // primitive types
  inline bool read() { return true; }
  inline bool read(char& arg) { return readChar(arg); }
  template <class I> inline typename enable_if<is_integral<I>::value && is_unsigned<I>::value,
  bool>::type read(I& arg) { return readUnsignedInt(arg, skipCharacters()) > 0; }
  template <class I> inline typename enable_if<is_integral<I>::value && is_signed<I>::value,
  bool>::type read(I& arg) { return readSignedInt(arg, skipCharacters()); }
  template <class F> inline typename enable_if<is_floating_point<F>::value,
  bool>::type read(F& arg) { return readFloatingPoint(arg, skipCharacters()); }
  // characters skip
  inline bool read(const char& arg) { skipCharacters([arg](char c) { return arg != c; }); return true; }
  inline bool read(const char* arg) {
    if (*arg) skipCharacters([arg](char c) { return InputDevice::isOneOf(c, arg); });
    else skipCharacters();
    return putBack(), true;
  }
  inline bool read(bool (*isSkipped)(char)) { skipCharacters(isSkipped); putBack(); return true; }
  // strings
  template <class I, class Terminator, class... Ts> inline typename enable_if<is_integral<I>::value,
  bool>::type read(char* arg, I limit, Terminator terminator, Ts&&... args) {
    readString(arg, static_cast<int>(limit), terminator);
    return read(forward<Ts>(args)...);
  }
  template <class I> inline typename enable_if<is_integral<I>::value,
  bool>::type read(char* arg, I limit) { return read(arg, limit, ""); }
  template <class... Ts>
  inline bool read(char* first, char* last, Ts&&... args) {
    return read(first, static_cast<int>(last - first), forward<Ts>(args)...);
  }
  template <int N, class... Ts>
  inline bool read(char (&arg)[N], Ts&&... args) { return read(static_cast<char*>(arg), N, forward<Ts>(args)...); }
  template <class Terminator, class... Ts>
  inline bool read(string& arg, Terminator terminator, Ts&&... args) {
    for (int length = 16, last = 0;; last += length, length <<= 1) {
      arg.resize(last + length);
      int charsRead = readString(&arg[last], length + 1, terminator);
      if (charsRead < length) {
        arg.resize(last + charsRead);
        return read(forward<Ts>(args)...);
      }
    }
  }
  inline bool read(string& arg) { return read(arg, ""); }
  // complex types and ranges
  template <class T1, class T2>
  inline bool read(pair<T1, T2>& arg) { return read(arg.first, arg.second); }
  template <class T>
  inline bool read(complex<T>& arg) {
    T real, imag;
    if (!read(real, imag)) return false;
    arg.real(real), arg.imag(imag);
    return true;
  }
  template <class T>
  inline bool read(vector<T>& arg) {
    uint n;
    if (!read(n)) return false;
    arg.resize(n);
    return read(arg.begin(), arg.end());
  }
  template <class Iterator, class... Ts> inline typename enable_if<is_iterator<Iterator>::value,
  bool>::type read(Iterator first, Iterator last, Ts&&... args) {
    for (; first != last; ++first) if (!read(*first)) return false;
    return read(forward<Ts>(args)...);
  }
  template <class Iterator, class I, class... Ts>
  inline typename enable_if<is_iterator<Iterator>::value && is_integral<I>::value,
  bool>::type read(Iterator first, I count, Ts&&... args) { return read(first, first + count, forward<Ts>(args)...); }
  // generic forwarding
  template <class T>
  inline auto read(T& arg) -> decltype(arg.read(*this)) { return arg.read(*this); }
  template <class T0, class T1, class... Ts>
  inline typename enable_if<!is_iterator<T0>::value && !is_convertible<T0, char*>::value,
  bool>::type read(T0&& arg0, T1&& arg1, Ts&&... args) {
    return read(forward<T0>(arg0)) && read(forward<T1>(arg1), forward<Ts>(args)...);
  }
};

class InputFile : public InputDevice {
  FILE* file;
  bool lineBuffered;
  bool owner;
  char buffer[BUFFER_SIZE];

  void fillInput() override {
    head = buffer;
    *buffer = '\0';
    if (__builtin_expect(!lineBuffered, true)) {
      tail = head + fread(buffer, 1, BUFFER_SIZE, file);
    } else {
      tail = head;
      if (fgets(buffer, BUFFER_SIZE, file)) while (*tail) ++tail;
    }
  }

public:
  InputFile(FILE* file = stdin, bool lineBuffered = true, bool takeOwnership = false)
  : InputDevice(buffer, buffer) , file(file), lineBuffered(lineBuffered), owner(takeOwnership) {}
  InputFile(const char* fileName) : InputFile(fopen(fileName, "r"), false, true) {}
  ~InputFile() { if (owner) fclose(file); }
};

// Picks up data appended to the string but doesn't handle reallocation.
class InputString : public InputDevice {
  void fillInput() override { while (*tail) ++tail; }

public:
  InputString(const string& s) : InputDevice(s.data(), s.data() + s.size()) {}
  InputString(const char* s) : InputDevice(s, s + strlen(s)) {}
};

/******************************* output classes *******************************/
class OutputDevice {
protected:
  char buffer[BUFFER_SIZE + MAX_LENGTH];
  char* output;
  char* end;
  bool separate;

  OutputDevice() : output(buffer), end(buffer + BUFFER_SIZE + MAX_LENGTH), separate(false)
  , width(setWidth().value), fill(setFill().value), base(setBase().value), precision(setPrecision().value)
  , delimiter(setDelimiter().value) { computeBasePower(); }

  virtual void writeToDevice(uint count) = 0;

  inline void flushMaybe() {
    if (__builtin_expect(output >= buffer + BUFFER_SIZE, false)) {
      writeToDevice(BUFFER_SIZE);
      output = copy(buffer + BUFFER_SIZE, output, buffer);
    }
  }

  void computeBasePower() {
    basePower = 1;
    for (uint i = 0; i < precision; ++i) basePower *= base;
  }

  template <class I> inline char* writeUnsignedInt(I arg, char* last) {
    if (__builtin_expect(arg == 0, false)) *--last = '0';
    if (__builtin_expect(base == 10, true)) {
      for (; arg; arg /= 10) *--last = '0' + arg % 10;
    } else for (; arg; arg /= base) {
      I digit = arg % base;
      *--last = digit < 10 ? '0' + digit : 'A' - 10 + digit;
    }
    return last;
  }

  template <class I> inline char* writeSignedInt(I arg, char* last) {
    auto unsignedArg = static_cast<typename make_unsigned<I>::type>(arg);
    if (arg < 0) {
      last = writeUnsignedInt(~unsignedArg + 1, last);
      *--last = '-';
      return last;
    }
    return writeUnsignedInt(unsignedArg, last);
  }

  template <class F> char* writeFloatingPoint(F arg, char* last) {
    bool negative = signbit(arg);
    if (negative) arg = -arg;
    if (isnan(arg)) for (int i = 0; i < 3; ++i) *--last = i["NaN"];
    else if (isinf(arg)) for (int i = 0; i < 3; ++i) *--last = i["fnI"];
    else {
      auto integerPart = static_cast<unsigned long long>(arg);
      auto fractionalPart = static_cast<unsigned long long>((arg - integerPart) * basePower + F(0.5));
      if (fractionalPart >= basePower) ++integerPart, fractionalPart = 0;
      char* point = last - precision;
      if (precision > 0) {
        ::fill(point, writeUnsignedInt(fractionalPart, last), '0');
        *--point = '.';
      }
      last = writeUnsignedInt(integerPart, point);
    }
    if (negative) *--last = '-';
    return last;
  }

  inline int writeT(char* first) {
    int delimiterLenght = separate ? writeDelimiter() : 0;
    separate = true;
    uint charsWritten = static_cast<uint>(end - first);
    if (__builtin_expect(charsWritten < width, false))
      charsWritten += writeFill(width - charsWritten);
    output = copy(first, end, output);
    flushMaybe();
    return delimiterLenght + static_cast<int>(charsWritten);
  }

  inline int writeFill(uint count) {
    int charsWritten = static_cast<int>(count);
    if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
      if (count == 1) *output++ = fill;
      else output = fill_n(output, count, fill);
    } else for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
      if (chunkSize > count) chunkSize = count;
      output = fill_n(output, chunkSize, fill);
      flushMaybe();
      if ((count -= chunkSize) == 0) break;
    }
    return charsWritten;
  }

public:
  uint width;
  char fill;
  uint base;
  uint precision;
  unsigned long long basePower;
  string delimiter;

  OutputDevice(OutputDevice const&) = delete;
  OutputDevice& operator = (OutputDevice const&) = delete;
  virtual ~OutputDevice() {};

  inline int writeChar(char arg) { separate = false; *output++ = arg; flushMaybe(); return 1; }

  inline int writeString(const char* arg, size_t length, bool checkWidth = true) {
    separate = false;
    uint count = static_cast<uint>(length);
    int charsWritten = static_cast<int>(count) + (checkWidth && count < width ? writeFill(width - count) : 0);
    if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
      if (count == 1) *output++ = *arg;
      else output = copy_n(arg, count, output);
    } else for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
      if (chunkSize > count) chunkSize = count;
      output = copy_n(arg, chunkSize, output);
      flushMaybe();
      if ((count -= chunkSize) == 0) break;
      arg += chunkSize;
    }
    return charsWritten;
  }

  inline int writeDelimiter() { return writeString(delimiter.c_str(), delimiter.size(), false); }

  inline void flush() {
    writeToDevice(static_cast<uint>(output - buffer));
    output = buffer;
  }

  // property setters
  inline int write(Detail::Width newWidth) { width = newWidth.value; return 0; }
  inline int write(Detail::Fill newFill) { fill = newFill.value; return 0; }
  inline int write(Detail::Base newBase) { base = newBase.value; computeBasePower(); return 0; }
  inline int write(Detail::Precision newPrecision) {
    precision = newPrecision.value; computeBasePower(); return 0;
  }
  inline int write(Detail::Delimiter newDelimiter) { delimiter = newDelimiter.value; return 0; }
  // primitive types
  inline int write() { return 0; }
  inline int write(char arg) { return writeChar(arg); }
  template <class I> inline typename enable_if<is_integral<I>::value && is_unsigned<I>::value,
  int>::type write(I arg) { return writeT(writeUnsignedInt(arg, end)); }
  template <class I> inline typename enable_if<is_integral<I>::value && is_signed<I>::value,
  int>::type write(I arg) { return writeT(writeSignedInt(arg, end)); }
  template <class F> inline typename enable_if<is_floating_point<F>::value,
  int>::type write(F arg) { return writeT(writeFloatingPoint(arg, end)); }
  // complex types
  inline int write(const char* arg) { return writeString(arg, strlen(arg)); }
  template <int N>
  inline int write(char (&arg)[N]) { return writeString(arg, strlen(arg)); }
  inline int write(const string& arg) { return writeString(arg.c_str(), arg.size()); }
  template <class T1, class T2>
  inline int write(const pair<T1, T2>& arg) {
    int charsWritten = write(arg.first);
    charsWritten += writeDelimiter();
    return charsWritten + write(arg.second);
  }
  template <class T>
  inline int write(const complex<T>& arg) { return write(real(arg), imag(arg)); }
  // ranges
  template <class Iterator, class... Ts> inline typename enable_if<is_iterator<Iterator>::value,
  int>::type write(Iterator first, Iterator last, Ts&&... args) {
    int charsWritten = 0;
    for (; first != last; charsWritten += ++first == last ? 0 : writeDelimiter()) charsWritten += write(*first);
    return charsWritten + write(forward<Ts>(args)...);
  }
  template <class Iterator, class I, class... Ts>
  inline typename enable_if<is_iterator<Iterator>::value && is_integral<I>::value,
  int>::type write(Iterator first, I count, Ts&&... args) { return write(first, first + count, forward<Ts>(args)...); }
  // generic forwarding
  template <class T>
  inline auto write(const T& arg) -> decltype(arg.write(*this)) { return arg.write(*this); }
  template <class T0, class T1, class... Ts> inline typename enable_if<!is_iterator<T0>::value,
  int>::type write(T0&& arg0, T1&& arg1, Ts&&... args) {
    int charsWritten = write(forward<T0>(arg0));
    return charsWritten + write(forward<T1>(arg1), forward<Ts>(args)...);
  }
};

class OutputFile : public OutputDevice {
  FILE* file;
  bool owner;

  void writeToDevice(uint count) override {
    fwrite(buffer, 1, count, file);
    fflush(file);
  }

public:
  OutputFile(FILE* file = stdout, bool takeOwnership = false) : file(file), owner(takeOwnership) {}
  OutputFile(const char* fileName) : OutputFile(fopen(fileName, "w"), true) {}
  ~OutputFile() override { flush(); if (owner) fclose(file); }
};

class OutputString : public OutputDevice {
  string& str;

  void writeToDevice(uint count) override { str.append(buffer, count); }

public:
  OutputString(string& str) : OutputDevice(), str(str) {}
  ~OutputString() override { flush(); }
};

unique_ptr<InputDevice> input;
unique_ptr<OutputDevice> output;

template <class... Ts> inline bool read(Ts&&... args) { return input->read(forward<Ts>(args)...); }
template <class... Ts> inline int write(Ts&&... args) { return output->write(forward<Ts>(args)...); }
template <class... Ts> inline int writeln(Ts&&... args) { return write(forward<Ts>(args)..., '\n'); }
void flush() { output->flush(); }

/*******************************************************************************
 * Read returns true if all the arguments were successfully read. Parameters:
 * - setBase(uint): base for integer and floating point numbers
 * Single variable of one of the following types:
 * - char, standard integer and floating point types
 * - pair, complex
 * - vector (size and then the elements)
 * Characters skip:
 * - char: skip until the given character is encountered and read it
 * - const char*: skip all the characters from the string
 * - predicate: skip all the characters satisfying the predicate
 * Strings: read until character limit is reached or termination character is found
 *   (one of the characters in a given string or defined by predicate, isspace by default)
 * - char (&)[N], terminator
 * - char*, int limit, terminator
 * - string&, terminator
 * Ranges:
 * - Iterator first, Iterator last
 * - Iterator first, int count
 *******************************************************************************
 * Write returns number of characters written. Parameters:
 * - setWidth(uint): minimum width of a single element to write (except character)
 * - setFill(char): character prepended to an element until set width is reached
 * - setBase(uint): base for integer and floating point numbers
 * - setPrecision(uint): number of digits after the decimal point
 * - setDelimiter(const char*): delimiter automatically inserted between elements
 *   that are not strings or characters
 * Single variable of one of the following types:
 * - char, standard integer and floating point types
 * - string, const char*
 * - pair, complex
 * Ranges:
 * - Iterator first, Iterator last
 * - Iterator first, int count
 ******************************************************************************/

#define MAXNM 100005
#define BSZ 150

#define NONE 0
#define ASSIGN 1
#define INC 2

int N, M, ROOT, chainNum, curInd, A[MAXNM], DEP[MAXNM], PAR[MAXNM], CHAIN[MAXNM], SZ[MAXNM], HEAD[MAXNM], PRE[MAXNM], POST[MAXNM], VERT[MAXNM]; // HLD
int COMP[MAXNM], COMPROOT[BSZ + 10], curComp; // CONNECTED COMPONENT
bool vis[MAXNM]; // DFS CONNECTED COMPONENT
pii EDGETO[BSZ + 10]; // DFS CONNECTED COMPONENT
int H, Min[MAXNM * 2], Max[MAXNM * 2], Sum[MAXNM * 2], lazy[MAXNM], lazyFlag[MAXNM]; // SEG TREE
int QT[MAXNM], QA[MAXNM], QB[MAXNM], QC[MAXNM], curM; // QUERIES
uset<pii, pair_hash<int, int>> removed; // edges that are to be removed in block
vector<pii> dotted; // edges that are currently in the graph at the beginning of the block, and a removed later
uset<int> adj[MAXNM]; // current graph
uset<pii, pair_hash<int, int>> adj2[BSZ + 10]; // component graph

void apply(int i, int v, int k, int flag) {
    if (flag == ASSIGN) {
        Min[i] = Max[i] = v;
        Sum[i] = v * k;
        if (i < N) {
            lazy[i] = v;
            lazyFlag[i] = ASSIGN;
        }
    } else if (flag == INC) {
        Min[i] += v;
        Max[i] += v;
        Sum[i] += v * k;
        if (i < N) {
            lazy[i] += v;
            lazyFlag[i] = INC;
        }
    }
}

int getSegmentMin(int i) {
    if (lazyFlag[i] == ASSIGN) return lazy[i];
    else if (lazyFlag[i] == INC) return min(Min[i << 1], Min[i << 1 | 1]) + lazy[i];
    else return min(Min[i << 1], Min[i << 1 | 1]);
}

int getSegmentMax(int i) {
    if (lazyFlag[i] == ASSIGN) return lazy[i];
    else if (lazyFlag[i] == INC) return max(Max[i << 1], Max[i << 1 | 1]) + lazy[i];
    else return max(Max[i << 1], Max[i << 1 | 1]);
}

int getSegmentSum(int i, int k) {
    if (lazyFlag[i] == ASSIGN) return lazy[i] * k;
    else if (lazyFlag[i] == INC) return Sum[i << 1] + Sum[i << 1 | 1] + lazy[i] * k;
    else return Sum[i << 1] + Sum[i << 1 | 1];
}

void pushup(int i) {
    for (int k = 2; i > 1; k <<= 1) {
        i >>= 1;
        Min[i] = getSegmentMin(i);
        Max[i] = getSegmentMax(i);
        Sum[i] = getSegmentSum(i, k);
    }
}

void propagate(int i) {
    for (int h = H, k = 1 << (H - 1); h > 0; h--, k >>= 1) {
        int ii = i >> h;
        if (lazyFlag[ii] != NONE) {
            apply(ii << 1, lazy[ii], k, lazyFlag[ii]);
            apply(ii << 1 | 1, lazy[ii], k, lazyFlag[ii]);
            lazyFlag[ii] = NONE;
            lazy[ii] = 0;
        }
    }
}

void build() {
    H = 0;
    for (int i = 1; i <= N; H++) i <<= 1;
    for (int i = 0; i < N; i++) {
        Min[N + i] = Max[N + i] = Sum[N + i] = A[VERT[i + 1]];
        lazy[i] = 0;
        lazyFlag[i] = NONE;
    }
    for (int i = N - 1; i > 0; i--) {
        Min[i] = min(Min[i << 1], Min[i << 1 | 1]);
        Max[i] = max(Max[i << 1], Max[i << 1 | 1]);
        Sum[i] = Sum[i << 1] + Sum[i << 1 | 1];
    }
}

void update(int l, int r, int v, int flag) {
    l += N - 1;
    r += N - 1;
    propagate(l);
    propagate(r);
    int l0 = l, r0 = r, k = 1;
    for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
        if ((l & 1) == 1) apply(l++, v, k, flag);
        if ((r & 1) == 0) apply(r--, v, k, flag);
    }
    pushup(l0);
    pushup(r0);
}

int queryMin(int l, int r) {
    l += N - 1;
    r += N - 1;
    propagate(l);
    propagate(r);
    int ret = INT_MAX;
    for (; l <= r; l >>= 1, r >>= 1) {
        if ((l & 1) == 1) ret = min(ret, Min[l++]);
        if ((r & 1) == 0) ret = min(ret, Min[r--]);
    }
    return ret;
}

int queryMax(int l, int r) {
    l += N - 1;
    r += N - 1;
    propagate(l);
    propagate(r);
    int ret = INT_MIN;
    for (; l <= r; l >>= 1, r >>= 1) {
        if ((l & 1) == 1) ret = max(ret, Max[l++]);
        if ((r & 1) == 0) ret = max(ret, Max[r--]);
    }
    return ret;
}

int querySum(int l, int r) {
    l += N - 1;
    r += N - 1;
    propagate(l);
    propagate(r);
    int ret = 0;
    for (; l <= r; l >>= 1, r >>= 1) {
        if ((l & 1) == 1) ret += Sum[l++];
        if ((r & 1) == 0) ret += Sum[r--];
    }
    return ret;
}

int lca(int v, int w) {
    while (CHAIN[v] != CHAIN[w]) {
        if (DEP[HEAD[CHAIN[v]]] < DEP[HEAD[CHAIN[w]]]) w = PAR[HEAD[CHAIN[w]]];
        else v = PAR[HEAD[CHAIN[v]]];
    }
    if (DEP[v] < DEP[w]) return v;
    return w;
}

// is w in the subtree of v
bool inSubtree(int v, int w) {
    return PRE[v] <= PRE[w] && POST[v] >= POST[w];
}

// finds the direct child of v that is the root of the subtree containing w
int findDirectChild(int v, int w) {
    int prev = -1;
    while (CHAIN[w] != CHAIN[v]) {
        prev = w;
        w = PAR[HEAD[CHAIN[w]]];
    }
    if (v == w) return HEAD[CHAIN[prev]];
    else return VERT[PRE[v] + 1];
}

// is w in the subtree of v, with the whole tree rooted at r
bool inSubtree(int r, int v, int w) {
    if (inSubtree(v, r)) return !inSubtree(findDirectChild(v, r), w);
    else return inSubtree(v, w);
}

// finds the parent of v if the tree is rooted at r
int findParent(int r, int v) {
    if (inSubtree(v, r)) return findDirectChild(v, r);
    else return PAR[v];
}

void updateSubtree(int r, int v, int val, int flag) {
    if (v == r) {
        update(PRE[COMPROOT[COMP[r]]], POST[COMPROOT[COMP[r]]], val, flag);
    } else if (inSubtree(v, r)) {
        int w = findDirectChild(v, r);
        update(PRE[COMPROOT[COMP[r]]], PRE[w] - 1, val, flag);
        update(POST[w] + 1, POST[COMPROOT[COMP[r]]], val, flag);
    } else {
        update(PRE[v], POST[v], val, flag);
    }
}

int querySubtreeMin(int r, int v) {
    if (v == r) {
        return queryMin(PRE[COMPROOT[COMP[r]]], POST[COMPROOT[COMP[r]]]);
    } else if (inSubtree(v, r)) {
        int w = findDirectChild(v, r);
        return min(queryMin(PRE[COMPROOT[COMP[r]]], PRE[w] - 1), queryMin(POST[w] + 1, POST[COMPROOT[COMP[r]]]));
    } else {
        return queryMin(PRE[v], POST[v]);
    }
}

int querySubtreeMax(int r, int v) {
    if (v == r) {
        return queryMax(PRE[COMPROOT[COMP[r]]], POST[COMPROOT[COMP[r]]]);
    } else if (inSubtree(v, r)) {
        int w = findDirectChild(v, r);
        return max(queryMax(PRE[COMPROOT[COMP[r]]], PRE[w] - 1), queryMax(POST[w] + 1, POST[COMPROOT[COMP[r]]]));
    } else {
        return queryMax(PRE[v], POST[v]);
    }
}

int querySubtreeSum(int r, int v) {
    if (v == r) {
        return querySum(PRE[COMPROOT[COMP[r]]], POST[COMPROOT[COMP[r]]]);
    } else if (inSubtree(v, r)) {
        int w = findDirectChild(v, r);
        return querySum(PRE[COMPROOT[COMP[r]]], PRE[w] - 1) + querySum(POST[w] + 1, POST[COMPROOT[COMP[r]]]);
    } else {
        return querySum(PRE[v], POST[v]);
    }
}

void updateUp(int v, int w, int val, int flag, bool includeW) {
    while (CHAIN[v] != CHAIN[w]) {
        update(PRE[HEAD[CHAIN[v]]], PRE[v], val, flag);
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (includeW || v != w) update(PRE[w] + (includeW ? 0 : 1), PRE[v], val, flag);
}

void updatePath(int v, int w, int val, int flag) {
    int LCA = lca(v, w);
    updateUp(v, LCA, val, flag, true);
    updateUp(w, LCA, val, flag, false);
}

int queryUpMin(int v, int w, bool includeW) {
    int ret = INT_MAX;
    while (CHAIN[v] != CHAIN[w]) {
        MIN(ret, queryMin(PRE[HEAD[CHAIN[v]]], PRE[v]));
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (includeW || v != w) MIN(ret, queryMin(PRE[w] + (includeW ? 0 : 1), PRE[v]));
    return ret;
}

int queryPathMin(int v, int w) {
    int LCA = lca(v, w);
    return min(queryUpMin(v, LCA, true), queryUpMin(w, LCA, false));
}

int queryUpMax(int v, int w, bool includeW) {
    int ret = INT_MIN;
    while (CHAIN[v] != CHAIN[w]) {
        MAX(ret, queryMax(PRE[HEAD[CHAIN[v]]], PRE[v]));
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (includeW || v != w) MAX(ret, queryMax(PRE[w] + (includeW ? 0 : 1), PRE[v]));
    return ret;
}

int queryPathMax(int v, int w) {
    int LCA = lca(v, w);
    return max(queryUpMax(v, LCA, true), queryUpMax(w, LCA, false));
}

int queryUpSum(int v, int w, bool includeW) {
    int ret = 0;
    while (CHAIN[v] != CHAIN[w]) {
        ret += querySum(PRE[HEAD[CHAIN[v]]], PRE[v]);
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (includeW || v != w) ret += querySum(PRE[w] + (includeW ? 0 : 1), PRE[v]);
    return ret;
}

int queryPathSum(int v, int w) {
    int LCA = lca(v, w);
    return queryUpSum(v, LCA, true) + queryUpSum(w, LCA, false);
}

void dfs(int v, int prev, int dep, int comp) {
    DEP[v] = dep;
    PAR[v] = prev;
    SZ[v] = 1;
    COMP[v] = comp;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs(w, v, dep + 1, comp);
        SZ[v] += SZ[w];
    }
}

void hld(int v, int prev) {
    if (HEAD[chainNum] == -1) HEAD[chainNum] = v;
    CHAIN[v] = chainNum;
    PRE[v] = ++curInd;
    VERT[curInd] = v;
    int maxIndex = -1;
    for (int w : adj[v]) if (w != prev && (maxIndex == -1 || SZ[maxIndex] < SZ[w])) maxIndex = w;
    if (maxIndex != -1) hld(maxIndex, v);
    for (int w : adj[v]) {
        if (w == prev || w == maxIndex) continue;
        chainNum++;
        hld(w, v);
    }
    POST[v] = curInd;
}

void initHLDandCOMP() {
    for (int i = 1; i <= N; i++) PAR[i] = HEAD[i] = -1;
    curComp = chainNum = curInd = 0;
    for (int i = 1; i <= N; i++) {
        if (PAR[i] != -1) continue;
        COMPROOT[++curComp] = i;
        dfs(i, -1, 0, curComp);
        hld(i, -1);
    }
}

void dfsUpdateSubtree(int v, int t, int prev, int val, int flag, bool found) {
    if (found) updateSubtree(v, v, val, flag);
    else if (COMP[v] == COMP[t]) {
        found = true;
        updateSubtree(v, t, val, flag);
    }
    for (pii e : adj2[COMP[v]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        dfsUpdateSubtree(e.s, t, v, val, flag, found);
    }
}

int dfsQuerySubtreeMin(int v, int t, int prev, int val, bool found) {
    if (found) MIN(val, querySubtreeMin(v, v));
    else if (COMP[v] == COMP[t]) {
        found = true;
        MIN(val, querySubtreeMin(v, t));
    }
    for (pii e : adj2[COMP[v]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        MIN(val, dfsQuerySubtreeMin(e.s, t, v, val, found));
    }
    return val;
}

int dfsQuerySubtreeMax(int v, int t, int prev, int val, bool found) {
    if (found) MAX(val, querySubtreeMax(v, v));
    else if (COMP[v] == COMP[t]) {
        found = true;
        MAX(val, querySubtreeMax(v, t));
    }
    for (pii e : adj2[COMP[v]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        MAX(val, dfsQuerySubtreeMax(e.s, t, v, val, found));
    }
    return val;
}

int dfsQuerySubtreeSum(int v, int t, int prev, int val, bool found) {
    if (found) val += querySubtreeSum(v, v);
    else if (COMP[v] == COMP[t]) {
        found = true;
        val += querySubtreeSum(v, t);
    }
    for (pii e : adj2[COMP[v]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        val += dfsQuerySubtreeSum(e.s, t, v, val, found);
    }
    return val;
}

void dfsGetPath(int v, int prev) {
    for (pii e : adj2[COMP[v]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        EDGETO[COMP[e.s]] = e;
        dfsGetPath(e.s, v);
    }
}

// returns true if t is in the subtree of s with the entire tree rooted at r
bool dfsInSubtree(int r, int s, int t, int prev, bool found) {
    if (found) {
        if (COMP[r] == COMP[t]) return true;
    } else if (COMP[r] == COMP[s]) {
        found = true;
        if (COMP[s] == COMP[t]) return inSubtree(r, s, t);
    }
    for (pii e : adj2[COMP[r]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        if (dfsInSubtree(e.s, s, t, e.f, found)) return true;
    }
    return false;
}

int dfsFindParent(int r, int s, int prev) {
    if (COMP[r] == COMP[s]) return prev;
    for (pii e : adj2[COMP[r]]) {
        if (COMP[e.s] == COMP[prev]) continue;
        int p = dfsFindParent(e.s, s, e.f);
        if (p != -1) return p;
    }
    return -1;
}

void dfsRebuild(int v) {
    vis[v] = true;
    for (int w : adj[v]) {
        if (vis[w]) continue;
        if (removed.count({v, w})) dotted.push_back({v, w});
        else dfsRebuild(w);
    }
}

void solveQueries(int i) {
    for (int w = 1; w <= N; w++) vis[w] = false;
    for (int w = 1; w <= N; w++) if (!vis[w]) dfsRebuild(w);
    for (pii e : removed) adj[e.f].erase(e.s);
    removed.clear();
    initHLDandCOMP();
    build();
    for (pii e: dotted) {
        adj2[COMP[e.f]].insert({e.f, e.s});
        adj2[COMP[e.s]].insert({e.s, e.f});
    }
    dotted.clear();
    int v, p, val;
    for (; curM <= i; curM++) {
        switch (QT[curM]) {
        case 0:
            dfsUpdateSubtree(ROOT, QA[curM], ROOT, QB[curM], ASSIGN, false);
            break;
        case 1:
            ROOT = QA[curM];
            break;
        case 2:
            dfsGetPath(QA[curM], QA[curM]);
            for (v = QB[curM]; COMP[QA[curM]] != COMP[v]; v = EDGETO[COMP[v]].f) updatePath(v, EDGETO[COMP[v]].s, QC[curM], ASSIGN);
            updatePath(QA[curM], v, QC[curM], ASSIGN);
            break;
        case 3:
            writeln(dfsQuerySubtreeMin(ROOT, QA[curM], ROOT, INT_MAX, false));
            break;
        case 4:
            writeln(dfsQuerySubtreeMax(ROOT, QA[curM], ROOT, INT_MIN, false));
            break;
        case 5:
            dfsUpdateSubtree(ROOT, QA[curM], ROOT, QB[curM], INC, false);
            break;
        case 6:
            dfsGetPath(QA[curM], QA[curM]);
            for (v = QB[curM]; COMP[QA[curM]] != COMP[v]; v = EDGETO[COMP[v]].f) updatePath(v, EDGETO[COMP[v]].s, QC[curM], INC);
            updatePath(QA[curM], v, QC[curM], INC);
            break;
        case 7:
            dfsGetPath(QA[curM], QA[curM]);
            val = INT_MAX;
            for (v = QB[curM]; COMP[QA[curM]] != COMP[v]; v = EDGETO[COMP[v]].f) MIN(val, queryPathMin(v, EDGETO[COMP[v]].s));
            MIN(val, queryPathMin(QA[curM], v));
            writeln(val);
            break;
        case 8:
            dfsGetPath(QA[curM], QA[curM]);
            val = INT_MIN;
            for (v = QB[curM]; COMP[QA[curM]] != COMP[v]; v = EDGETO[COMP[v]].f) MAX(val, queryPathMax(v, EDGETO[COMP[v]].s));
            MAX(val, queryPathMax(QA[curM], v));
            writeln(val);
            break;
        case 9:
            if (!dfsInSubtree(ROOT, QA[curM], QB[curM], ROOT, false)) {
                p = dfsFindParent(ROOT, QA[curM], ROOT);
                adj2[COMP[p]].erase({p, QA[curM]});
                adj2[COMP[QA[curM]]].erase({QA[curM], p});
                adj2[COMP[QB[curM]]].insert({QB[curM], QA[curM]});
                adj2[COMP[QA[curM]]].insert({QA[curM], QB[curM]});
                adj[p].erase(QA[curM]);
                adj[QA[curM]].erase(p);
                adj[QB[curM]].insert(QA[curM]);
                adj[QA[curM]].insert(QB[curM]);
            } else if (QA[curM] != ROOT) {
                adj[QA[curM]].insert(QC[curM]);
                adj[QC[curM]].insert(QA[curM]);
            }
            break;
        case 10:
            dfsGetPath(QA[curM], QA[curM]);
            val = 0;
            for (v = QB[curM]; COMP[QA[curM]] != COMP[v]; v = EDGETO[COMP[v]].f) val += queryPathSum(v, EDGETO[COMP[v]].s);
            val += queryPathSum(QA[curM], v);
            writeln(val);
            break;
        case 11:
            writeln(dfsQuerySubtreeSum(ROOT, QA[curM], ROOT, 0, false));
            break;
        }
    }
    for (int w = 1; w <= N; w++) A[w] = querySum(PRE[w], PRE[w]);
    for (int w = 1; w <= curComp; w++) adj2[w].clear();
}

int main() {
//    input.reset(new InputFile("in.txt"));
//    output.reset(new OutputFile("out.txt"));
    input.reset(new InputFile());
    output.reset(new OutputFile());
    read(N, M);
    int a, b;
    FOR(i, N - 1) {
        read(a, b);
        adj[a].insert(b);
        adj[b].insert(a);
    }
    read(A + 1, A + N + 1);
    cin >> ROOT;
    initHLDandCOMP();
    curM = 1;
    int cc = 0, curRoot = ROOT;
    For(i, 1, M + 1) {
        read(QT[i]);
        switch (QT[i]) {
        case 0:
            read(QA[i], QB[i]);
            break;
        case 1:
            read(QA[i]);
            curRoot = QA[i];
            break;
        case 2:
            read(QA[i], QB[i], QC[i]);
            break;
        case 3:
            read(QA[i]);
            break;
        case 4:
            read(QA[i]);
            break;
        case 5:
            read(QA[i], QB[i]);
            break;
        case 6:
            read(QA[i], QB[i], QC[i]);
            break;
        case 7:
            read(QA[i], QB[i]);
            break;
        case 8:
            read(QA[i], QB[i]);
            break;
        case 9:
            read(QA[i], QB[i]);
            if (QA[i] != curRoot) {
                QC[i] = findParent(curRoot, QA[i]);
                removed.insert({QA[i], QC[i]});
                removed.insert({QC[i], QA[i]});
                cc++;
            }
            break;
        case 10:
            read(QA[i], QB[i]);
            break;
        case 11:
            read(QA[i]);
            break;
        default:
            i--;
            break;
        }
        if (i >= cc || i == M) {
            cc = 0;
            solveQueries(i);
            initHLDandCOMP();
        }
    }
    return 0;
}

//int main() {
////    input.reset(new InputFile("in.txt"));
////    output.reset(new OutputFile("out.txt"));
//    input.reset(new InputFile());
//    output.reset(new OutputFile());
//    // 1527134630
//    int seed = time(0);
//    writeln(seed);
//    flush();
//    mt19937 rng(seed);
//    N = 2000;
//    M = 2000;
//    int a, b;
//    FOR(i, N - 1) {
//        a = i + 2;
//        b = rng() % (i + 1) + 1;
//        adj[a].insert(b);
//        adj[b].insert(a);
//    }
//    For(i, 1, N + 1) A[i] = rng() % N;
//    ROOT = 1;
//    initHLDandCOMP();
//    curM = 1;
//    int cc = 0, curRoot = ROOT;
//    For(i, 1, M + 1) {
//        QT[i] = rng() % 12;
//        switch (QT[i]) {
//        case 0:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            break;
//        case 1:
//            QA[i] = rng() % N + 1;
//            curRoot = QA[i];
//            break;
//        case 2:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            QC[i] = rng() % N + 1;
//            break;
//        case 3:
//            QA[i] = rng() % N + 1;
//            break;
//        case 4:
//            QA[i] = rng() % N + 1;
//            break;
//        case 5:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            break;
//        case 6:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            QC[i] = rng() % N + 1;
//            break;
//        case 7:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            break;
//        case 8:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            break;
//        case 9:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            if (QA[i] != curRoot) {
//                QC[i] = findParent(curRoot, QA[i]);
//                removed.insert({QA[i], QC[i]});
//                removed.insert({QC[i], QA[i]});
//                cc++;
//            }
//            break;
//        case 10:
//            QA[i] = rng() % N + 1;
//            QB[i] = rng() % N + 1;
//            break;
//        case 11:
//            QA[i] = rng() % N + 1;
//            break;
//        default:
//            i--;
//            break;
//        }
//        if (i >= cc || i == M) {
//            cc = 0;
//            solveQueries(i);
//            initHLDandCOMP();
//        }
//    }
//    return 0;
//}

