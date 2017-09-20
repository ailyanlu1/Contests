#include <stdio.h>
// #include <math.h>

int main(void) {
    int n, t;
    int sum;
    scanf("%d", &t);
    for (int tt = 0; tt < t; tt++) {
        sum = 0;
        scanf("%d", &n);
        // only need to go up to sqrt(n) since the other divisors will be n / i, where i is a divisor
        for (int i = 1; i * i <= n; i++) {
            // if the remainder is 0, then add the divisor to the sum
            if (n % i == 0) {
                sum += i;
                // if i == 1, then don't add the other divisor (since it must be n)
                // if i == n / i, then the 2 divisors are the same and should not be added twice
                if (i != 1 && i != n / i) sum += n / i;
            } // if
        } // for i
        if (sum > n) printf("%d is an abundant number.\n", n);
        else if (sum < n) printf("%d is a deficient number.\n", n);
        else printf("%d is a perfect number.\n", n);
    }
    return 0;
} // main function
