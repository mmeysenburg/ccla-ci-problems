#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include "BucketSort.h"
#include "../1-SearchNSort/SearchNSort.h"

/**
 * @brief Comparator function for quickSort.
 * 
 * @param x Item 1 to compare
 * 
 * @param y Item 2 to compare
 * 
 * @return -1 if x < y, 1 if x > y, 0 if x == y
 */
int compare(const double &x, const double &y) { 
    if(x < y) {
        return -1;
    } else if(x > y) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Fill an array of doubles.
 * 
 * @param pArr Pointer to array to fill
 * 
 * @param n Number of elements in the array
 */
void fill(double *pArr, unsigned n) {
    std::mt19937_64 prng(time(0));
    std::uniform_real_distribution<double> dist;

    for(unsigned i = 0; i < n; i++) {
        pArr[i] = dist(prng);
    }
}

/**
 * @brief Randomly shuffle and array of doubles
 * 
 * @param pArr Pointer to array to shuffle
 * 
 * @param n Number of elements in the array
 */
void shuffle(double *pArr, unsigned n) { 
    std::mt19937_64 prng(time(0));
    std::uniform_int_distribution<unsigned> dist(0, n - 1u);

    for(unsigned i = 0; i < n; i++) {
        std::swap(pArr[i], pArr[dist(prng)]);
    }
}

/**
 * @brief Determine if an array is sorted
 * 
 * @param pArr Pointer to array to check
 * 
 * @param n Number of elements in the array
 * 
 * @return true if the array is sorted ascending, false otherwise
 */
bool isSorted(double *pArr, unsigned n) {
    for(unsigned i = 0; i < n - 1; i++) {
        if(pArr[i] > pArr[i + 1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Application entry point
 * 
 * @param argc Number of command-line arguments
 * 
 * @param ppszArgs Array of command-line argument strings
 */
int main(int argc, char **ppszArgs) {
    // command-line argument sanity check
    if(argc != 2) {
        fprintf(stderr, "Usage: ./bucketSort maxPower\n");
    }
    int powerCap = atoi(ppszArgs[1]);

    unsigned n = 256;

    printf("%8s,%12s,%12s\n", "n" ,"bs" ,"qs");
    for(int power = 8; power <= powerCap; power++) {
        double *pArr = new double[n];
        fill(pArr, n);

        printf("%8d, ", n);

        // bucketsort tests
        long double dur = 0;
        for(int i = 0; i < 10; i++) {
            shuffle(pArr, n);
            auto begin = std::chrono::high_resolution_clock::now();
            bucketSort(pArr, n);
            auto end = std::chrono::high_resolution_clock::now();

            if(!isSorted(pArr, n)) {
                fprintf(stderr, "BUCKETSORT FAILURE!\n");
                return EXIT_FAILURE;
            }
            dur += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        dur /= 10.0;
        printf("%0.5LE, ", dur);

        // quicksort tests
        dur = 0;
        for(int i = 0; i < 10; i++) {
            shuffle(pArr, n);
            auto begin = std::chrono::high_resolution_clock::now();
            SearchNSort<double>::quickSort(pArr, n, compare);
            auto end = std::chrono::high_resolution_clock::now();

            if(!isSorted(pArr, n)) {
                fprintf(stderr, "QUICKSORT FAILURE!\n");
                return EXIT_FAILURE;
            }
            dur += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }
        dur /= 10.0;
        printf("%0.5LE\n", dur);

        delete [] pArr;

        n *= 2;
    }

    return EXIT_SUCCESS;
}
