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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

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

const int MIN_GALLOP = 7;
const int MIN_MERGE = 32;
const int AUX_SIZE = 256;
const int SMALL_STACK_SIZE = 10;
const int MEDIUM_STACK_SIZE = 20;
const int LARGE_STACK_SIZE = 40;

template <typename T> inline void exch(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T> void expand(T *&arr, int &curSize, int minSize, int maxSize) {
    if (curSize < minSize) {
        int newSize = minSize;
        newSize |= newSize >> 1;
        newSize |= newSize >> 2;
        newSize |= newSize >> 4;
        newSize |= newSize >> 8;
        newSize |= newSize >> 16;
        newSize++;
        if (newSize < 0) newSize = minSize;
        else newSize = min(newSize, maxSize);
        T *newArr = new T[newSize];
        T *temp = arr;
        arr = newArr;
        delete[] (temp);
        curSize = newSize;
    }
}

template <typename It, typename Comparator> int count_run_and_make_ascending(It st, It en, Comparator cmp) {
    int n = en - st;
    int i = 1;
    if (i == n) return 1;
    if (cmp(st[i++], st[0])) {
        while (i < n && cmp(st[i], st[i - 1])) i++;
        for (int lo = 0, hi = i - 1; lo < hi; lo++, hi--) exch(st + lo, st + hi);
    } else {
        while (i < n && !cmp(st[i], st[i - 1])) i++;
    }
    return i;
}

template <typename It, typename Comparator> void binary_insertion_sort(It st, It en, It ind, Comparator cmp) {
    typedef typename std::iterator_traits<It>::value_type T;
    if (ind - st == 0) ind++;
    for ( ; ind < en; ind++) {
        T pivot = *ind;
        It left = st, right = ind, mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (cmp(pivot, *mid)) right = mid;
            else left = mid + 1;
        }
        memmove(left + 1, left, (ind - left) * sizeof(T));
        *left = pivot;
    }
}

template <typename T, typename It, typename Comparator> int gallop_left(T key, It st, It en, It hint, Comparator cmp) {
    int ofs = 1, lastOfs = 0;
    if (cmp(*hint, key)) {
        int maxOfs = en - hint;
        while (ofs < maxOfs && cmp(*(hint + ofs), key)) {
            lastOfs=  ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        lastOfs += hint - st;
        ofs += hint - st;
    } else {
        int maxOfs = hint - st + 1;
        while (ofs < maxOfs && !cmp(*(hint - ofs), key)) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        int temp = lastOfs;
        lastOfs = hint - st - ofs;
        ofs = hint - st - temp;
    }
    lastOfs++;
    while (lastOfs < ofs) {
        int m = lastOfs + (ofs - lastOfs) / 2;
        if (cmp(*(st + m), key)) lastOfs = m + 1;
        else ofs = m;
    }
    return ofs;
}

template <typename T, typename It, typename Comparator> int gallop_right(T key, It st, It en, It hint, Comparator cmp) {
    int ofs = 1, lastOfs = 0;
    if (cmp(key, *hint)) {
        int maxOfs = hint - st + 1;
        while (ofs < maxOfs && cmp(key, *(hint - ofs))) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        int temp = lastOfs;
        lastOfs = hint - st - ofs;
        ofs = hint - st - temp;
    } else {
        int maxOfs = en - hint;
        while (ofs < maxOfs && !cmp(key, *(hint + ofs))) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        lastOfs += hint - st;
        ofs += hint - st;
    }
    lastOfs++;
    while (lastOfs < ofs) {
        int m = lastOfs + (ofs - lastOfs) / 2;
        if (cmp(key, *(st + m))) ofs = m;
        else lastOfs = m + 1;
    }
    return ofs;
}

template <typename T, typename It, typename Comparator> void merge_lo(It st1, It en1, It st2, It en2, Comparator cmp, T *&aux, int &auxSize, int maxSize) {
    int len1 = en1 - st1, len2 = en2 - st2;
    expand(aux, auxSize, len1, maxSize);
    memmove(aux, st1, len1 * sizeof(T));
    T *cur1 = aux, *cur2 = st2, *dest = st1;
    *(dest++) = *(cur2++);
    if (--len2 == 0) {
        memmove(dest, cur1, len1 * sizeof(T));
        return;
    }
    if (len1 == 1) {
        memmove(dest, cur2, len2 * sizeof(T));
        *(dest + len2) = *(cur1);
        return;
    }
    int minGallop = MIN_GALLOP;
    while (true) {
        bool flag = false;
        int cnt1 = 0, cnt2 = 0;
        do {
            if (cmp(*cur2, *cur1)) {
                *(dest++) = *(cur2++);
                cnt2++;
                cnt1 = 0;
                if (--len2 == 0) {
                    flag = true;
                    break;
                }
            } else {
                *(dest++) = *(cur1++);
                cnt1++;
                cnt2 = 0;
                if (--len1 == 1) {
                    flag = true;
                    break;
                }
            }
        } while ((cnt1 | cnt2) < minGallop);
        if (flag) break;
        do {
            cnt1 = gallop_right(*cur2, cur1, cur1 + len1, cur1, cmp);
            if (cnt1 != 0) {
                memmove(dest, cur1, cnt1 * sizeof(T));
                dest += cnt1;
                cur1 += cnt1;
                len1 -= cnt1;
                if (len1 <= 1) {
                    flag = true;
                    break;
                }
            }
            *(dest++) = *(cur2++);
            if (--len2 == 0) {
                flag = true;
                break;
            }
            cnt2 = gallop_left(*cur1, cur2, cur2 + len2, cur2, cmp);
            if (cnt2 != 0) {
                memmove(dest, cur2, cnt2 * sizeof(T));
                dest += cnt2;
                cur2 += cnt2;
                len2 -= cnt2;
                if (len2 == 0) {
                    flag = true;
                    break;
                }
            }
            *(dest++) = *(cur1++);
            if (--len1 == 1) {
                flag = true;
                break;
            }
            minGallop--;
        } while (cnt1 >= minGallop || cnt2 >= minGallop);
        if (flag) break;
        minGallop = max(minGallop, 0);
        minGallop += 2;
    }
    minGallop = minGallop < 1 ? 1 : minGallop;
    if (len1 == 1) {
        memmove(dest, cur2, len2 * sizeof(T));
        *(dest + len2) = *(cur1);
    } else if (len1 == 0) {
        throw runtime_error("Something wrong with the comparison function.");
    } else if (len2 == 0) {
        memmove(dest, cur1, len1 * sizeof(T));
    } else {
        throw runtime_error("Something wrong with the comparison function.");
    }
}

template <typename T, typename It, typename Comparator> void merge_hi(It st1, It en1, It st2, It en2, Comparator cmp, T *&aux, int &auxSize, int maxSize) {
    int len1 = en1 - st1, len2 = en2 - st2;
    expand(aux, auxSize, len2, maxSize);
    memmove(aux, st2, len2 * sizeof(T));
    T *cur1 = st1 + len1 - 1, *cur2 = aux + len2 - 1, *dest = st2 + len2 - 1;
    *(dest--) = *(cur1--);
    if (--len1 == 0) {
        memmove(dest - len2 + 1, aux, len2 * sizeof(T));
        return;
    }
    if (len2 == 1) {
        dest -= len1;
        cur1 -= len1;
        memmove(dest + 1, cur1 + 1, len1 * sizeof(T));
        *dest = *cur2;
        return;
    }
    int minGallop = MIN_GALLOP;
    while (true) {
        bool flag = false;
        int cnt1 = 0, cnt2 = 0;
        do {
            if (cmp(*cur2, *cur1)) {
                *(dest--) = *(cur1--);
                cnt1++;
                cnt2 = 0;
                if (--len1 == 0) {
                    flag = true;
                    break;
                }
            } else {
                *(dest--) = *(cur2--);
                cnt2++;
                cnt1 = 0;
                if (--len2 == 1) {
                    flag = true;
                    break;
                }
            }
        } while ((cnt1 | cnt2) < minGallop);
        if (flag) break;
        do {
            cnt1 = len1 - gallop_right(*cur2, st1, st1 + len1, st1 + len1 - 1, cmp);
            if (cnt1 != 0) {
                dest -= cnt1;
                cur1 -= cnt1;
                len1 -= cnt1;
                memmove(dest + 1, cur1 + 1, cnt1 * sizeof(T));
                if (len1 == 0) {
                    flag = true;
                    break;
                }
            }
            *(dest--) = *(cur2--);
            if (--len2 == 1) {
                flag = true;
                break;
            }
            cnt2 = len2 - gallop_left(*cur1, aux, aux + len2, aux + len2 - 1, cmp);
            if (cnt2 != 0) {
                dest -= cnt2;
                cur2 -= cnt2;
                len2 -= cnt2;
                memmove(dest + 1, cur2 + 1, cnt2 * sizeof(T));
                if (len2 <= 1) {
                    flag = true;
                    break;
                }
            }
            *(dest--) = *(cur1--);
            if (--len1 == 0) {
                flag = true;
                break;
            }
            minGallop--;
        } while (cnt1 >= minGallop || cnt2 >= minGallop);
        if (flag) break;
        minGallop = max(minGallop, 0);
        minGallop += 2;
    }
    minGallop = minGallop < 1 ? 1 : minGallop;
    if (len2 == 1) {
        dest -= len1;
        cur1 -= len1;
        memmove(dest + 1, cur1 + 1, len1 * sizeof(T));
        *dest = *cur2;
    } else if (len2 == 0) {
        throw runtime_error("Something wrong with the comparison function.");
    } else if (len1 == 0) {
        memmove(dest - len2 + 1, aux, len2 * sizeof(T));
    } else {
        throw runtime_error("Something wrong with the comparison function.");
    }
}

template <typename T, typename It, typename Comparator> void merge_runs(It st, It en, Comparator cmp, int *runBase, int *runLen, int &stackSize, int i, T *&aux, int &auxSize, int maxSize) {
    int base1 = runBase[i];
    int len1 = runLen[i];
    int base2 = runBase[i + 1];
    int len2 = runLen[i + 1];
    runLen[i] = len1 + len2;
    if (i == stackSize - 3) {
        runBase[i + 1] = runBase[i + 2];
        runLen[i + 1] = runLen[i + 2];
    }
    stackSize--;
    int k = gallop_right(st[base2], st + base1, st + base1 + len1, st + base1, cmp);
    base1 += k;
    len1 -= k;
    if (len1 == 0) return;
    len2 = gallop_left(st[base1 + len1 - 1], st + base2, st + base2 + len2, st + base2 + len2 - 1, cmp);
    if (len2 == 0) return;
    if (len1 <= len2) merge_lo(st + base1, st + base1 + len1, st + base2, st + base2 + len2, cmp, aux, auxSize, maxSize);
    else merge_hi(st + base1, st + base1 + len1, st + base2, st + base2 + len2, cmp, aux, auxSize, maxSize);
}

template <typename It, typename Comparator> void tim_sort(It st, It en, Comparator cmp) {
    typedef typename std::iterator_traits<It>::value_type T;
    int n = en - st;
    int maxSize = n / 2;
    if (n <= 1) return;
    if (n < MIN_MERGE) {
        int initRunLen = count_run_and_make_ascending(st, en, cmp);
        binary_insertion_sort(st, en, st + initRunLen, cmp);
        return;
    }
    int auxSize = n < 2 * AUX_SIZE ? n / 2 : AUX_SIZE;
    T *aux = new T[auxSize];
    int maxStackSize = (n < 1000 ? SMALL_STACK_SIZE : (n < 100000 ? MEDIUM_STACK_SIZE : LARGE_STACK_SIZE));
    int *runBase = new int[maxStackSize];
    int *runLen = new int[maxStackSize];
    int stackSize = 0;
    int nn = n, r = 0;
    while (nn >= MIN_MERGE) {
        r |= (nn & 1);
        nn >>= 1;
    }
    int minRun = nn + r;
    int i = 0;
    do {
        int curRunLen = count_run_and_make_ascending(st + i, en, cmp);
        if (curRunLen < minRun) {
            int force = min(n, minRun);
            binary_insertion_sort(st + i, st + i + force, st + i + curRunLen, cmp);
            curRunLen = force;
        }
        runBase[stackSize] = i;
        runLen[stackSize] = curRunLen;
        stackSize++;
        while (stackSize > 1) {
            int k = stackSize - 2;
            if (k > 0 && runLen[k - 1] <= runLen[k] + runLen[k + 1]) {
                if (runLen[k - 1] < runLen[k + 1]) k--;
                merge_runs(st, en, cmp, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
            } else if (runLen[k] <= runLen[k + 1]) {
                merge_runs(st, en, cmp, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
            } else {
                break;
            }
        }
        i += curRunLen;
        n -= curRunLen;
    } while (n > 0);
    while (stackSize > 1) {
        int k = stackSize - 2;
        if (k > 0 && runLen[k - 1] < runLen[k + 1]) k--;
        merge_runs(st, en, cmp, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
    }
    delete[] (aux);
    delete[] (runBase);
    delete[] (runLen);
}

struct Point2D {
public:
    ll x, y;

    Point2D() {}

    Point2D(ll x, ll y) : x(x), y(y) {}

    ll distSq(Point2D &that) {
        ll dx = x - that.x;
        ll dy = y - that.y;
        return dx * dx + dy * dy;
    }

    bool operator == (const Point2D &other) const {
        return x == other.x && y == other.y;
    }

    bool operator != (const Point2D &other) const {
        return x != other.x || y != other.y;
    }

    static bool xOrderLt(Point2D &p, Point2D &q) { return p.x < q.x; }

    static bool yOrderLt(Point2D &p, Point2D &q) { return p.y < q.y; }
};

struct Rectangle {
public:
    ll xmin, ymin, xmax, ymax;

    Rectangle() {}

    Rectangle(ll xmin, ll ymin, ll xmax, ll ymax) : xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax) {}

    bool contains(Point2D *p) {
        return p->x >= xmin && p->x <= xmax && p->y >= ymin && p->y <= ymax;
    }

    ll distSq(Point2D *p) {
        ll dx = 0, dy = 0;
        if (p->x < xmin) dx = p->x - xmin;
        else if (p->x > xmax) dx = p->x - xmax;
        if (p->y < ymin) dy = p->y - ymin;
        else if (p->y > ymax) dy = p->y - ymax;
        return dx * dx + dy + dy;
    }
};

struct KdTree {
private:
    bool VERTICAL = false, HORIZONTAL = true;
    ll XMIN, YMIN, XMAX, YMAX;

    struct Node {
        Point2D *p;
        Node *leftUp, *rightDown;
        Rectangle *r;

        Node(Point2D *p, Rectangle *r) {
            this->p = p;
            this->r = r;
            this->leftUp = nullptr;
            this->rightDown = nullptr;
        }
    };

    int cnt;
    Node *root;

    Node *construct(Node *n, Point2D *points, int lo, int hi, bool partition, ll xmin, ll ymin, ll xmax, ll ymax) {
        if (lo > hi) return nullptr;
        if (partition == VERTICAL) tim_sort(points + lo, points + hi + 1, Point2D::xOrderLt);
        else tim_sort(points + lo, points + hi + 1, Point2D::yOrderLt);
        int mid = lo + (hi - lo) / 2;
        Point2D *p = &points[mid];
        n = new Node(p, new Rectangle(xmin, ymin, xmax, ymax));
        if (partition == VERTICAL) {
            n->leftUp = construct(n->leftUp, points, lo, mid - 1, !partition, xmin, ymin, n->p->x, ymax);
            n->rightDown = construct(n->rightDown, points, mid + 1, hi, !partition, n->p->x, ymin, xmax, ymax);
        } else {
            n->leftUp = construct(n->leftUp, points, lo, mid - 1, !partition, xmin, ymin, xmax, n->p->y);
            n->rightDown = construct(n->rightDown, points, mid + 1, hi, !partition, xmin, n->p->y, xmax, ymax);
        }
        return n;
    }

    pair<Point2D*, int> findNearest(Node *n, Point2D *p, pair<Point2D*, int> nearest) {
        if (nullptr == n) return nearest;
        if (nullptr == nearest.f) {
            nearest.f = n->p;
            nearest.s = 1;
        } else if (nearest.f->distSq(*p) == n->p->distSq(*p)) {
            nearest.s++;
        } else if (nearest.f->distSq(*p) > n->p->distSq(*p)) {
            nearest.f = n->p;
            nearest.s = 1;
        } else if (nearest.f->distSq(*p) < n->r->distSq(p)) {
            return nearest;
        }
        if (nullptr != n->leftUp && n->leftUp->r->contains(p)) {
            nearest = findNearest(n->leftUp, p, nearest);
            nearest = findNearest(n->rightDown, p, nearest);
        } else {
            nearest = findNearest(n->rightDown, p, nearest);
            nearest = findNearest(n->leftUp, p, nearest);
        }
        return nearest;
    }

public:
    KdTree(ll xmin, ll ymin, ll xmax, ll ymax, Point2D *points, int N) {
        cnt = N;
        XMIN = xmin;
        YMIN = ymin;
        XMAX = xmax;
        YMAX = ymax;
        root = construct(root, points, 0, N - 1, VERTICAL, XMIN, YMIN, XMAX, YMAX);
    }

    bool isEmpty() {
        return cnt == 0;
    }

    int size() {
        return cnt;
    }

    pair<Point2D*, int> findNearest(Point2D *p) {
        return findNearest(root, p, {nullptr, 0});
    }
};

const ll MAXXY = (ll) (1e9 + 1);

int N, Q;
Point2D *P;
KdTree *tree;

int main() {
    input.reset(new InputFile());
    output.reset(new OutputFile());
    read(N);
    P = new Point2D[N];
    ll x, y;
    FOR(i, N) {
        read(x, y);
        P[i].x = x;
        P[i].y = y;
    }
    tree = new KdTree(-MAXXY, -MAXXY, MAXXY, MAXXY, P, N);
    cin >> Q;
    FOR(i, Q) {
        Point2D q;
        read(x, y);
        q.x = x;
        q.y = y;
        pair<Point2D*, int> nearest = tree->findNearest(&q);
        writeln(nearest.f->distSq(q), nearest.s);
    }
    return 0;
}
