#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef unsigned long long uint64; // range = [0, 2^64-1]

// ===============================================================
// isPrime(N) function
// arguments: N = number to test for primeness
// returns: 1 for prime and 0 for composite
// ===============================================================
int isPrime(const uint64 N) {
    // testing with prime divisors less than 30 (2*3*5)
    int prime = (N %  2) &&
                (N %  3) &&
                (N %  5) &&
                (N %  7) &&
                (N % 11) &&
                (N % 13) &&
                (N % 17) &&
                (N % 19) &&
                (N % 23) &&
                (N % 29);
    if(prime) { // if indivisible through initial divisors
        // iterate over all divisors from 31 to sqrt(N) in chunks of 30 ...
        // ... but skip multiples of 2, 3 and 5
        const uint64 sqrt_N = (uint64)floor(sqrt((double)N));
        for(uint64 k = 1; (30 * k + 1) <= sqrt_N; k++) {
            // testing with current chunk of divisors
            prime = (N % (30 * k +  1)) &&
                    (N % (30 * k +  7)) &&
                    (N % (30 * k + 11)) &&
                    (N % (30 * k + 13)) &&
                    (N % (30 * k + 17)) &&
                    (N % (30 * k + 19)) &&
                    (N % (30 * k + 23)) &&
                    (N % (30 * k + 29));
            if(!prime) // if divisible, no need to test with further divisors
                break;
        }
    }
    return prime ? 1 : 0;
}

// ===============================================================
//    Main function
// ===============================================================
int main(int argc, char *argv[]) {

// help and usage notes
// ===========================================
    if(argc == 1) {
        fprintf(stderr, "Usage: %s N1 [N2] [N3] ...\n", argv[0]);
        fprintf(stderr, "numbers must be between 2 and %llu ", ULLONG_MAX);
        fprintf(stderr, "(2^64-1 = upper limit of 64 bit unsigned integer)\n");
        return EXIT_FAILURE;
    }

// read command line arguments
// ===========================================
    uint64 *N_arg = (uint64*)malloc((argc-1) * sizeof(uint64));
    if(N_arg == NULL) {
        fprintf(stderr, "%s:%d Error allocating memory\n", __FILE__, __LINE__);
        return EXIT_FAILURE;
    }
    for(int i = 0; i < argc-1; i++)
        sscanf(argv[i+1], "%llu", &N_arg[i]);

// iterate over input numbers
// ===========================================
    for(int i = 0; i < argc-1; i++) {
        const uint64 N = N_arg[i];
        if(!(N >= 2 && N <= ULLONG_MAX)) { // sanitize
            fprintf(stderr, "%llu is not between 2 and %llu\n", N, ULLONG_MAX);
            continue; // discard this number and continue
        }
        // display message to indicate status
        printf("Testing primeness of %llu... ", N); fflush(NULL);
        // display result
        printf("%s\n", isPrime(N) ? "PRIME" : "COMPOSITE");
    }

    free(N_arg);
    return EXIT_SUCCESS;
}
