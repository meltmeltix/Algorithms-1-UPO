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

size_t upo_bst_subtree_count_skip_2_impl(upo_bst_node_t *node)
{
    if (!node) { return 0; }
    size_t count = 1;
    if (node->left) {
        count += upo_bst_subtree_count_skip_2_impl(node->left->left)
            + upo_bst_subtree_count_skip_2_impl(node->left->right);
    }
    if (node->right) {
        count += upo_bst_subtree_count_skip_2_impl(node->right->left)
            + upo_bst_subtree_count_skip_2_impl(node->right->right);
    }
    return count;
}

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key)
{
    if (!bst) {
        return 0;
    }
    if (upo_bst_is_empty(bst)) {
        return 0;
    }

    upo_bst_node_t *node = bst->root;
    upo_bst_comparator_t cmp = upo_bst_get_comparator(bst);
    int res;
    int even = 1;
    while (node && (res = cmp(key, node->key)) != 0)
    {
        node = res < 0 ? node->left : node->right;
        even = !even;
    }
    if (!node)
    {
        return 0;
    }
    if (even)
    {
        return upo_bst_subtree_count_skip_2_impl(node);
    }

    size_t count = 0;
    if (node->left) {
        count += upo_bst_subtree_count_skip_2_impl(node->left);
    }
    if (node->right) {
        count += upo_bst_subtree_count_skip_2_impl(node->right);
    }
    return count;
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/

void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{
    if (!ht)
    {
        perror("Uninitialized hash table");
        return;
    }
    upo_ht_hasher_t h = upo_ht_sepchain_get_hasher(ht);
    size_t i = h(key, upo_ht_sepchain_capacity(ht));
    if (ht->slots[i].head)
    {
        upo_ht_comparator_t cmp = upo_ht_sepchain_get_comparator(ht);
        upo_ht_sepchain_list_node_t **before = &ht->slots[i].head;
        while (*before && cmp((*before)->key, key) != 0)
        {
            before = &(*before)->next;
        }
        if (*before)
        {
            upo_ht_sepchain_list_node_t *next = (*before)->next;
            if (destroy_data)
            {
                free((*before)->key);
                free((*before)->value);
            }
            free(*before);
            *before = next;
            --ht->size;
        }
    }
}

/**** END of EXERCISE #2 ****/
