#pragma once

#include <algorithm>
#include <vector>

/**
 * @brief Bucketsort algorithm for array of doubles
 * 
 * Our bucketsort for doubles in the range [0, 1) works like this:
 * 
 *   - create 10 buckets
 * 
 *   - distribute the elements from pArr into the buckets like this:
 * 
 *     -- bucket 0 gets numbers in the range [0.0, 0.1)
 * 
 *     -- bucket 1 gets numbers in the range [0.1, 0.2)
 * 
 *     -- bucket 2 gets numbers in the range [0.2, 0.3)
 * 
 *     -- ...
 * 
 *     -- bucket 9 gets numbers in the range [0.9, 1)
 * 
 *   - sort each bucket using an efficient sort algorithm
 * 
 *   - place elements from the buckets back into pArr: bucket 0 first, then
 *   bucket 1, then bucket 2, and so on
 * 
 * This algorithm uses the std::vector class as buckets, and the std::sort()
 * algorithm to sort the buckets. Overall, the bucketsort will be faster
 * than quicksort. 
 * 
 * @param pArr Pointer to the array to be sorted
 * 
 * @param n Number of elements in the array
 */
void bucketSort(double *pArr, unsigned n) {

    // buckets is a vector of vector<double> -- vector of vectors
    std::vector<std::vector<double>> buckets;

    // TODO: add 10 vector<double>'s to buckets, and reserve slightly more
    // than n / 10 space in each. Reserving enough space at the outset
    // prevents multiple resizing operations

    // TODO: add each array element to the correct bucket

    // TODO: sort each bucket, using the STL std::sort() algorithm

    // TODO: place elements from the buckets back in the original array
}