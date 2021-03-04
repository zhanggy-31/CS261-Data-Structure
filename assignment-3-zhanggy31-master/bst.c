/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:Guangyu Zhang
 * Email:zhangg3@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
    int key;
    void* value;
    struct bst_node* left;
    struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
    struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
    struct bst* bst = malloc(sizeof(struct bst));
    bst->root = NULL;
    return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
    if(bst != NULL){
        bst->root = free_helper(bst->root);
    }
    free(bst->root);
    free(bst);
    return;
}

void* free_helper(struct bst_node* bst_d){
    while(bst_d->left != NULL){
        bst_d->left = free_helper(bst_d->left);
    }
    while(bst_d->right != NULL){
        bst_d->right = free_helper(bst_d->right);
    }
    free(bst_d);
    return NULL;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
    int s = 0;
    size_helper(bst->root,&s);
    return s;
}

void size_helper(struct bst_node* bst_d, int* s){
    if(bst_d){
        size_helper(bst_d->left,s);
        size_helper(bst_d->right,s);
        (*s)++;
    }
    return;
}
/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
    bst->root = insert_helper(bst->root,key,value);
    return;
}


void* insert_helper(struct bst_node* bst_d, int key, void* value){
    struct bst_node* bst_temp = malloc(sizeof(struct bst_node));
    if(bst_d == NULL){
        bst_temp->key = key;
        bst_temp->value = value;
        bst_temp->left = NULL;
        bst_temp->right = NULL;
        return bst_temp;
    }
    else if(bst_d->key > key){
        bst_d->left = insert_helper(bst_d->left,key,value);
    }
    else{
        bst_d->right = insert_helper(bst_d->right,key,value);
    }
    free_helper(bst_temp);
    return bst_d;
}
/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
    bst->root = remove_helper(bst->root,key);
    return;
}
void* remove_helper(struct bst_node* bst_d, int key){
    if(bst_d == NULL){
        return NULL;
    }
    if(bst_d->key > key){
        bst_d->left = remove_helper(bst_d->left,key);
        return bst_d;
    }
    else if(bst_d->key < key){
        bst_d->right = remove_helper(bst_d->right,key);
        return bst_d;
    }
    else{
        if(bst_d->left!=NULL && bst_d->right!=NULL){
            struct bst_node* post_move = bst_d->right;
            struct bst_node* pre_move = bst_d;
            if(post_move->left == NULL){
                post_move = pre_move->left;
                pre_move->key = post_move->key;
                pre_move->value = post_move->value;
                post_move->right = pre_move->right;
                free(pre_move);
                return post_move;
            }
            else{
                while(post_move->left!=NULL){
                    pre_move = post_move;
                    post_move = post_move->left;
                }
                bst_d->key = post_move->key;
                bst_d->value = post_move->value;
                pre_move->left = post_move->right;
                bst_d->right = remove_helper(bst_d->right,post_move->key);
            }
            return bst_d;
        }
        else if(bst_d->left != NULL){
            struct bst_node* left = bst_d->left;
            free(bst_d);
            return left;
        }
        else if(bst_d->right !=NULL){
            struct bst_node* right = bst_d->right;
            free(bst_d);
            return right;
        }
        else{
            free(bst_d);
            return NULL;
        }
    }
}
/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
    return get_helper(bst->root,key);
}

void* get_helper(struct bst_node* bst_d, int key){
    if(bst_d){
        if(bst_d->key==key){
            return bst_d;
        }
        if(bst_d->key > key){
            get_helper(bst_d->left,key);
        }
        else{
            get_helper(bst_d->right,key);
        }
    }
    else{
        return NULL;
    }
}

