int setbits(unsigned long long a) {
    return __builtin_popcountll(a);
}
