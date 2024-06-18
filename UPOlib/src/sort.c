/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * - base: pointer to the first element of the array
 * - n: length of the array
 * - size: size of the array's elements
 * - cmp: pointer to comparator function
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort_private.h"

/*** UTILS ***/

void upo_swap(unsigned char *a, unsigned char *b, size_t size) {
    unsigned char *aux = malloc(size);
    assert(aux != NULL);

    memcpy(aux,  a, size);
    memcpy(a, b, size);
    memcpy(b, aux, size);

    free(aux);
}

/*** BEGIN of SORTING ALGORITHMS ***/

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    assert(base != NULL);

    size_t i;
    unsigned char *ptr = base;
    unsigned char *aux = malloc(size);

    assert(aux != NULL);

    for (i = 1; i < n; ++i) {
        size_t j = i;
        memcpy(aux, ptr + i * size, size);

        while (j > 0 && cmp(aux, ptr + (j - 1) * size) < 0) {
            memcpy(ptr + j * size, ptr + (j - 1) * size, size);
            --j;
        }

        memcpy(ptr + j * size, aux, size);
    }

    free(aux);
}

// Note (IT): https://gist.github.com/meltmeltix/82dbaf9d461bc1e69c97d3a88667812b
void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    assert(base != NULL);
    upo_merge_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t mid;

    if (lo >= hi) return;

    mid = lo + (hi - lo) / 2;
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid + 1, hi, size, cmp);
    upo_merge_sort_merge(base, lo, mid, hi, size, cmp);
}

void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    unsigned char *ptr = base;
    unsigned char *aux = NULL;

    size_t n = hi - lo + 1;
    size_t i = 0;
    size_t j = mid + 1 - lo;
    size_t k;

    aux = malloc(n * size);
    if (aux == NULL) {
        perror("Unable to allocate memory for auxiliary vector");
        abort();
    }
    memcpy(aux, ptr + lo * size, n * size);

    for (k = lo; k <= hi; ++k) {
        if (i > (mid - lo)) {
            memcpy(ptr + k * size, aux + j * size, size);
            ++j;
        } else if (j > (hi - lo)) {
            memcpy(ptr + k * size, aux + i * size, size);
            ++i;
        } else if (cmp(aux + j * size, aux + i * size) < 0) {
            memcpy(ptr + k * size, aux + j * size, size);
            ++j;
        } else {
            memcpy(ptr + k * size, aux + i * size, size);
            ++i;
        }
    }

    free(aux);
}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    assert(base != NULL);
    upo_quick_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    if (lo >= hi) return;

    size_t j = upo_quick_sort_partition(base, lo, hi, size, cmp);
    if (j > 0) { upo_quick_sort_rec(base, lo, j - 1, size, cmp); }

    upo_quick_sort_rec(base, j + 1, hi, size, cmp);
}

static size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    unsigned char *ptr = base;
    unsigned char *aux = malloc(size);
    assert(aux != NULL);

    size_t p = lo;
    size_t i = lo;
    size_t j = hi + 1;

    while (1) {
        do { i++; } while(i <= hi && cmp(ptr + i * size, ptr + p * size) <= 0);

        do { j--; } while(j > lo && cmp(ptr + j * size, ptr + p * size) >= 0);

        if (i >= j) break;

        memcpy(aux, ptr + i * size, size);
        memcpy(ptr + i * size, ptr + j * size, size);
        memcpy(ptr + j * size, aux, size);
    }

    memcpy(aux, ptr + p * size, size);
    memcpy(ptr + p * size, ptr + j * size, size);
    memcpy(ptr + j * size, aux, size);

    free(aux);
    return j;
}

/*** BEGIN of MORE EXERCISES ***/

void upo_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    unsigned char *ptr = base;
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < ((n - 1) - i); j++) {
            if (cmp(ptr + j * size, ptr + (j + 1) * size) > 0) {
                upo_swap(ptr + (j + 1) * size, ptr + j * size, size);
            }
        }
    }
}

void upo_quick_sort_median3_cutoff(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    upo_quick_sort_median3_cutoff_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_median3_cutoff_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t pivot;

    if (lo >= hi) return;

    if ((hi - lo) + 1 <= 10) {
        upo_insertion_sort((unsigned char *)base + lo * size, hi - lo + 1, size, cmp);
        return;
    }

    size_t j = upo_quick_sort_median3_cutoff_partition(base, lo, hi, size, cmp);
    if (j > 0)
        upo_quick_sort_median3_cutoff_rec(base, lo, j - 1, size, cmp);
    upo_quick_sort_median3_cutoff_rec(base, j + 1, hi, size, cmp);

    // Partitioning the whole array
    pivot = upo_quick_sort_median3_cutoff_partition(base, lo, hi, size, cmp);
    if (pivot > 0)
        upo_quick_sort_median3_cutoff_rec(base, lo, pivot - 1, size, cmp);
    upo_quick_sort_median3_cutoff_rec(base, pivot + 1, hi, size, cmp);

}

size_t upo_quick_sort_median3_cutoff_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t mid = (hi + lo) / 2;
    unsigned char *ptr = base;
    unsigned char *lo_ptr = ptr + lo * size;
    unsigned char *mid_ptr = ptr + mid * size;
    unsigned char *hi_ptr = ptr + hi * size;

    // Swaps nodes depending on size
    if (cmp(lo_ptr, mid_ptr) > 0) upo_swap(lo_ptr, mid_ptr, size);
    if (cmp(lo_ptr, hi_ptr) > 0) upo_swap(lo_ptr, hi_ptr, size);
    if (cmp(mid_ptr, hi_ptr) > 0) upo_swap(mid_ptr, hi_ptr, size);

    // Check whether these are the only nodes left
    if ((hi - lo) + 1 <= 3) return mid;
    
    upo_swap(mid_ptr, ptr + (lo + 1) * size, size);
    return upo_quick_sort_partition(base, lo + 1, hi - 1, size, cmp);
}