/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */


/******************************************************************************/
/*** NOME:                                                                  ***/
/*** COGNOME:                                                               ***/
/*** MATRICOLA:                                                             ***/
/******************************************************************************/


#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h>


/**** BEGIN of EXERCISE #1 ****/

size_t upo_bst_subtree_count_even_impl(upo_bst_node_t *node) {
    if (!node) return 0;
    size_t count = 1;

    if (node->left) {
        count += upo_bst_subtree_count_even_impl(node->left->left)
                + upo_bst_subtree_count_even_impl(node->left->right);
    }
    
    if (node->right) {
        count += upo_bst_subtree_count_even_impl(node->right->left)
                + upo_bst_subtree_count_even_impl(node->right->right);
    }

    return count;
}

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key) {
    if (!bst || upo_bst_is_empty(bst)) return 0;

    upo_bst_node_t *node = bst->root;
    int res;
    int even = 1;

    while (node && (res = bst->key_cmp(node->key, key)) != 0) {
        node = res > 0 ? node->left : node->right;
        even = !even;
    }

    if (!node) return 0;
    if (even) return upo_bst_subtree_count_even_impl(node);

    size_t count = 0;
    if (node->left) { count += upo_bst_subtree_count_even_impl(node->left); } 
    if (node->right) { count += upo_bst_subtree_count_even_impl(node->right); }
    return count;
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/

void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data) {
    if (ht != NULL || ht->slots != NULL) {
        size_t h = ht->key_hash(key, ht->capacity);
        upo_ht_sepchain_list_node_t *n = ht->slots[h].head;
        upo_ht_sepchain_list_node_t *p = NULL;

        while (n != NULL && ht->key_cmp(key, n->key)) {
            p = n;
            n = n->next;
        }

        if (n != NULL) {
            if (p == NULL)
                ht->slots[h].head = n->next;
            else
                p->next = n->next;

            if (destroy_data) {
                free(n->key);
                free(n->value);
            }
            ht->size--;
            free(n);
        }
    }
}

/**** END of EXERCISE #2 ****/
