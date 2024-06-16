/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/******************************************************************************/
/*** NOME:                                                                  ***/
/*** COGNOME:                                                               ***/
/*** MATRICOLA:                                                             ***/
/******************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/sort.h>

/**** BEGIN of EXERCISE #1 ****/

static const void *upo_bst_predeccessor_impl(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
    if (!node) return NULL; 
    if (cmp(key, node->key) <= 0) return upo_bst_predeccessor_impl(node->left, key, cmp);
    else {
        const void *right = upo_bst_predeccessor_impl(node->right, key, cmp);
        return right ? right : node->key;
    }
}

const void *upo_bst_predecessor(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return NULL;
    return upo_bst_predeccessor_impl(bst->root, key, upo_bst_get_comparator(bst));
}

/**** END of EXERCISE #1 ****/

/**** BEGIN of EXERCISE #2 ****/

void upo_swap(unsigned char *a, unsigned char *b, size_t size) {
    unsigned char *aux = malloc(size);
    assert(aux != NULL);

    memcpy(aux,  a, size);
    memcpy(a, b, size);
    memcpy(b, aux, size);

    free(aux);
}

void upo_bidi_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    assert(base != NULL);

    unsigned char *ptr = base;
    bool swapped = false;

    do {
        swapped = false;

        // From left to right
        for (size_t i = 0; i < n - 1; ++i)
            if (cmp(ptr + i * size, ptr + (i + 1) * size) > 0) { 
                upo_swap(ptr + i * size, ptr + (i + 1) * size, size);
                swapped = true;
            }

        // From right to left
        for (size_t i = n - 1; i > 1; --i)
            if (cmp(ptr + i * size, ptr + (i - 1) * size) < 0) { 
                upo_swap(ptr + i * size, ptr + (i - 1) * size, size);
                swapped = true;
            }
    } while(swapped);
}

/**** END of EXERCISE #2 ****/
