/*
 * APlusB2.cpp
 *
 *  Created on: May 10, 2017
 *      Author: Wesley Leung
 */


#include <bits/stdc++.h>

using namespace std;

class UnsignedBigInt
{
    const static int base = 1000 * 1000 * 1000;
    std::vector<int> value;
    int length;

    void normalize();
    static long long strToLl(std::string initValue);
    static std::string llToStr(long long initValue);

public:
    UnsignedBigInt();
    UnsignedBigInt(long long initValue);
    UnsignedBigInt(std::string initValue);
    UnsignedBigInt(const UnsignedBigInt & b);

    string makeStr();

    template<class T> bool operator < (T curB);
    template<class T> bool operator <= (T curB);
    template<class T> bool operator == (T curB);
    template<class T> bool operator > (T curB);
    template<class T> bool operator >= (T curB);
    template<class T> bool operator != (T curB);

    UnsignedBigInt operator + (int b);
    UnsignedBigInt operator - (int b);
    UnsignedBigInt operator * (int b);
    UnsignedBigInt operator / (int b);
    UnsignedBigInt operator % (int b);
    UnsignedBigInt operator /= (int b);
    UnsignedBigInt operator %= (int b);
    UnsignedBigInt operator + (long long b);
    UnsignedBigInt operator - (long long b);
    UnsignedBigInt operator * (long long b);
    UnsignedBigInt operator / (long long b);
    UnsignedBigInt operator % (long long b);
    UnsignedBigInt operator /= (long long b);
    UnsignedBigInt operator %= (long long b);
    UnsignedBigInt operator + (UnsignedBigInt b);
    UnsignedBigInt operator - (UnsignedBigInt b);
    UnsignedBigInt operator * (UnsignedBigInt b);
    UnsignedBigInt operator / (UnsignedBigInt b);
    UnsignedBigInt operator % (UnsignedBigInt b);
    UnsignedBigInt operator /= (UnsignedBigInt b);
    UnsignedBigInt operator %= (UnsignedBigInt b);
    template<class T> UnsignedBigInt operator += (T b);
    template<class T> UnsignedBigInt operator *= (T b);
    template<class T> UnsignedBigInt operator -= (T b);

    static UnsignedBigInt power(UnsignedBigInt a, long long n);
    static UnsignedBigInt power(UnsignedBigInt a, UnsignedBigInt n);
    static UnsignedBigInt powerDigits(UnsignedBigInt a, long long n, int countDigits); //returns last countDigits digits of the power
    static UnsignedBigInt powerDigits(UnsignedBigInt a, UnsignedBigInt n, int countDigits);

    friend istream & operator >> (istream & is, UnsignedBigInt & b);
    friend ostream & operator << (ostream & os, UnsignedBigInt b);
};

istream & operator >> (istream & is, UnsignedBigInt & b)
{
    string temp;
    is >> temp;
    b = UnsignedBigInt(temp);
    return is;
}

ostream & operator << (ostream & os, UnsignedBigInt b)
{
    string temp = b.makeStr();
    os << temp;
    return os;
}

void UnsignedBigInt::normalize()
{
    while (length > 1 && value[length - 1] == 0)
    {
        value.pop_back();
        --length;
    }
}

string UnsignedBigInt::llToStr(long long initValue)
{
    string res = "";
    if (initValue == 0)
        return "0";
    while (initValue)
    {
        res = char(initValue % 10 + '0') + res;
        initValue /= 10;
    }
    return res;
}

long long UnsignedBigInt::strToLl(string initValue)
{
    long long res = 0;
    for (int i = 0; i < initValue.length(); ++i)
    {
        res *= 10ll;
        res += (int)initValue[i] - '0';
    }
    return res;
}

string UnsignedBigInt::makeStr()
{
    string res = "";
    res += llToStr(value.back());
    for (int i = length - 2; i >= 0; --i)
    {
        string cur = llToStr(value[i]);
        for (int j = 0; j < 9 - (int)cur.length(); ++j)
            res += '0';
        res += cur;
    }
    return res;
}

UnsignedBigInt::UnsignedBigInt()
{
    length = 1;
    value.assign(1, 0);
}

UnsignedBigInt::UnsignedBigInt(string initValue)
{
    value.clear();
    length = (int)initValue.length() / 9;
    if ((int)initValue.length() % 9)
        ++length;
    value.resize(length);
    int initLength = initValue.length();
    int left = max(0, initLength - 9);
    int right = initLength - 1;
    for (int i = 0; i < length; i++)
    {
        value[i] = strToLl(initValue.substr(left, right - left + 1));
        left = max(left - 9, 0);
        right -= 9;
    }
    normalize();
}

UnsignedBigInt::UnsignedBigInt(long long initValue)
{
    string temp = llToStr(initValue);
    *this = UnsignedBigInt(temp);
}

UnsignedBigInt::UnsignedBigInt(const UnsignedBigInt & b)
{
    *this = b;
}

template<class T>
bool UnsignedBigInt::operator < (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    normalize();
    b.normalize();
    if (length < b.length)
        return true;
    if (length > b.length)
        return false;
    for (int i = length - 1; i >= 0; --i)
    {
        if (value[i] > b.value[i])
            return false;
        if (value[i] < b.value[i])
            return true;
    }
    return false;
}

template<class T>
bool UnsignedBigInt::operator == (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    normalize();
    b.normalize();
    if (length != b.length)
        return false;
    for (int i = 0; i < length; ++i)
    {
        if (value[i] != b.value[i])
            return false;
    }
    return true;
}

template<class T>
bool UnsignedBigInt::operator <= (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    return *this < b || *this == b;
}

template<class T>
bool UnsignedBigInt::operator > (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    return b < *this;
}

template<class T>
bool UnsignedBigInt::operator >= (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    return b == *this || b < *this;
}

template<class T>
bool UnsignedBigInt::operator != (T curB)
{
    UnsignedBigInt b = UnsignedBigInt(curB);
    return !(*this == b);
}


UnsignedBigInt UnsignedBigInt::operator + (UnsignedBigInt b)
{
    UnsignedBigInt result;
    result.length = max(length + 1, b.length + 1);
    result.value.assign(result.length, 0);
    long long carry = 0;
    for (int i = 0; i < result.length; ++i)
    {
        long long cur = carry;
        if (i < length)
            cur += value[i];
        if (i < b.length)
            cur += b.value[i];
        if (cur < base)
        {
            carry = 0;
            result.value[i] = cur;
        }
        else
        {
            carry = 1;
            result.value[i] = cur - base;
        }
    }
    result.normalize();
    return result;
}

UnsignedBigInt UnsignedBigInt::operator - (UnsignedBigInt b)
{
    UnsignedBigInt result;
    result.length = length;
    result.value.assign(length, 0);
    long long carry = 0;
    for (int i = 0; i < length; ++i)
    {
        long long cur = carry + value[i];
        if (i < b.length)
            cur -= b.value[i];
        if (cur < 0)
        {
            carry = -1;
            result.value[i] = cur + base;
        }
        else
        {
            carry = 0;
            result.value[i] = cur;
        }
    }
    result.normalize();
    return result;
}

UnsignedBigInt UnsignedBigInt::operator * (UnsignedBigInt b)
{
    UnsignedBigInt result;
    result.length = length + b.length + 2;
    result.value.assign(result.length, 0);
    for (int i = 0; i < b.length; ++i)
    {
        long long carry = 0;
        for (int j = 0; j < length || carry; ++j)
        {
            long long cur = carry + b.value[i] * 1ll * (j < length ? value[j] : 0);
            cur += 0ll + result.value[i + j];
            result.value[i + j] = cur % base;
            carry = cur / base;
        }
    }
    result.normalize();
    return result;
}

UnsignedBigInt UnsignedBigInt::operator / (int b)
{
    if (b >= base)
        return *this / UnsignedBigInt(b);
    long long carry = 0;
    UnsignedBigInt result;
    result.length = length;
    result.value.assign(result.length, 0);
    for (int i = length - 1; i >= 0; --i)
    {
        long long cur = carry * base + value[i];
        result.value[i] = cur / b;
        carry = cur % b;
    }
    return result;
}

UnsignedBigInt UnsignedBigInt::operator % (int b)
{
    if (b >= base)
        return *this % UnsignedBigInt(b);
    long long carry = 0;
    UnsignedBigInt result;
    result.length = length;
    result.value.assign(result.length, 0);
    for (int i = length - 1; i >= 0; --i)
    {
        long long cur = carry * base + value[i];
        result.value[i] = cur / b;
        carry = cur % b;
    }
    return UnsignedBigInt(carry);
}

UnsignedBigInt UnsignedBigInt::operator / (UnsignedBigInt b)
{
    UnsignedBigInt low = UnsignedBigInt(0);
    UnsignedBigInt high = *this;
    while (low < high)
    {
        UnsignedBigInt middle = (low + high + UnsignedBigInt(1)) / 2;
        if (middle * b > *this)
            high = middle - UnsignedBigInt(1);
        else
            low = middle;
    }
    return low;
}

UnsignedBigInt UnsignedBigInt::operator % (UnsignedBigInt b)
{
    return *this - (*this / b) * b;
}

UnsignedBigInt UnsignedBigInt::operator + (int b)
{
    return *this + UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator - (int b)
{
    return *this - UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator * (int b)
{
    return *this * UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator + (long long b)
{
    return *this + UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator - (long long b)
{
    return *this - UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator * (long long b)
{
    return *this * UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator / (long long b)
{
    return *this / UnsignedBigInt(b);
}

UnsignedBigInt UnsignedBigInt::operator % (long long b)
{
    return *this % UnsignedBigInt(b);
}

template<class T>
UnsignedBigInt UnsignedBigInt::operator *= (T b)
{
    *this = *this * UnsignedBigInt(b);
    return *this;
}

template<class T>
UnsignedBigInt UnsignedBigInt::operator += (T b)
{
    *this = *this + UnsignedBigInt(b);
    return *this;
}

template<class T>
UnsignedBigInt UnsignedBigInt::operator -= (T b)
{
    *this = *this - UnsignedBigInt(b);
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator /= (int b)
{
    *this = *this / b;
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator %= (int b)
{
    *this = *this % b;
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator /= (long long b)
{
    *this = *this / UnsignedBigInt(b);
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator %= (long long b)
{
    *this = *this % UnsignedBigInt(b);
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator /= (UnsignedBigInt b)
{
    *this = *this / b;
    return *this;
}

UnsignedBigInt UnsignedBigInt::operator %= (UnsignedBigInt b)
{
    *this = *this % b;
    return *this;
}

UnsignedBigInt UnsignedBigInt::power(UnsignedBigInt a, long long n)
{
    UnsignedBigInt result = UnsignedBigInt(1);
    while (n > 0)
    {
        if (n % 2 != 0)
            result *= a;
        a *= a;
        n /= 2;
    }
    return result;
}

UnsignedBigInt UnsignedBigInt::power(UnsignedBigInt a, UnsignedBigInt n)
{
    UnsignedBigInt result = UnsignedBigInt(1);
    while (n > 0)
    {
        if (n % 2 != 0)
            result *= a;
        a *= a;
        n /= 2;
    }
    return result;
}

UnsignedBigInt UnsignedBigInt::powerDigits(UnsignedBigInt a, long long n, int countDigits)
{
    UnsignedBigInt result = UnsignedBigInt(1);
    int maxSize = countDigits / 9 + 1;
    while (n > 0)
    {
        if (n % 2 != 0)
        {
            result *= a;
            while (result.length > maxSize)
            {
                result.length--;
                result.value.pop_back();
            }
        }
        n /= 2;
        a *= a;
        while (a.length > maxSize)
        {
            a.length--;
            a.value.pop_back();
        }
    }
    UnsignedBigInt mod = UnsignedBigInt::power(10, countDigits);
    result %= mod;
    return result;
}

UnsignedBigInt UnsignedBigInt::powerDigits(UnsignedBigInt a, UnsignedBigInt n, int countDigits)
{
    UnsignedBigInt result = UnsignedBigInt(1);
    int maxSize = countDigits / 9 + 1;
    while (n > 0)
    {
        if (n % 2 != 0)
        {
            result *= a;
            while (result.length > maxSize)
            {
                result.length--;
                result.value.pop_back();
            }
        }
        n /= 2;
        a *= a;
        while (a.length > maxSize)
        {
            a.length--;
            a.value.pop_back();
        }
    }
    UnsignedBigInt mod = UnsignedBigInt::power(10, countDigits);
    result %= mod;
    return result;
}

int N;
string a, b, ans;
bool aNeg, bNeg;
UnsignedBigInt A, B;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        aNeg = false;
        bNeg = false;
        cin >> a >> b;
        if (a[0] == '-') {
            aNeg = true;
            a = a.substr(1, a.length() - 1);
        }
        if (b[0] == '-') {
            bNeg = true;
            b = b.substr(1, b.length() - 1);
        }
        A = UnsignedBigInt(a);
        B = UnsignedBigInt(b);
        if (!aNeg && !bNeg) {
            ans = (A + B).makeStr();
        } else if (aNeg && bNeg) {
            ans = "-" + (A + B).makeStr();
        } else if (!aNeg && bNeg) {
            if (A >= B) {
                ans = (A - B).makeStr();
            } else {
                ans = "-" + (B - A).makeStr();
            }
        } else {
            if (B >= A) {
                ans = (B - A).makeStr();
            } else {
                ans = "-" + (A - B).makeStr();
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
