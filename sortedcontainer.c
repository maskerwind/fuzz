#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortedcontainer.h"

int data_compare(data* d1, data* d2) {
    assert(d1);
    assert(d2);
    if(d1->age < d2->age) return -1;
    if(d1->age > d2->age) return 1;
    return strcmp(d1->name, d2->name);
}

// Do not change
void data_print(data* d, FILE* f) {
    fprintf(f, "%i %s", d->age, d->name);
}

data* data_new(int age, char const* name) {
    data* d = (data*)malloc(sizeof(data));
    d->age = age;
    strncpy(d->name, name, NAME_LENGTH);
    return d;
}

void data_delete(data* d) {
    free(d);
}

node* node_new(data* d) {
    // Implement this
    if (d == NULL){
        return NULL;
    }
    node* n = (node*)malloc(sizeof(node));
    n->data = d;
    n->left = n->right = NULL;
    return n;
}

void node_delete(node* n) {
    // Implement this
    if (n != NULL) free(n);
}

sortedcontainer* sortedcontainer_new() {
    sortedcontainer* d = (sortedcontainer*)malloc(sizeof(sortedcontainer));
    d->root = NULL;
    return d;
}

void sortedcontainer_insert(sortedcontainer* sc, data* data) {
    node* n = node_new(data);
    // Implement this
    if (n == NULL) return;
    if (sc == NULL){ 
		sc = sortedcontainer_new();
		sc->root = n;
		return;
	}
	if (sc->root ==NULL){
		sc->root = n;
		return;
	}

	node* head = sc->root;
	node* parent;
	while(head){
		parent = head;
		if (data_compare(head->data, data) == 1){
			head = head->left;
		}
		else if (data_compare(head->data, data) == -1){
			head = head->right;
		}
		else return;
	}
	
	if (data_compare(parent->data, data) == 1){
		parent->left = node_new(data);
	}
	else if (data_compare(parent->data, data) == -1){
		parent->right = node_new(data);
	}
	else return;
}

int sortedcontainer_erase(sortedcontainer* sc, data* data) {
    // Implement this
    if (sc == NULL || data == NULL){
        return 0;
    }
    if (sc->root ==NULL){
        return 0;
    }

	node* head = sc->root;
	node* parent;
	node* parent_replacement;
	node* replacement;
	node* child_ptr;

	int is_left = 0;
	parent = NULL;
	while(head){ // Find the data to be erased.
		if (data_compare(head->data,data)==0){
			break;
		}
		else if (data_compare(head->data,data)==1){
			parent = head;
			is_left = 1;
			head = head->left;
		}
		else{
            parent = head;
            is_left = 0;
            head = head->right;
		}
	}

	if (head == NULL)  return 0;

	if ((head->left == NULL) && (head->right == NULL)){
		if (parent == NULL){
			assert(head == sc->root);
			free(head);
			sc->root = NULL;
		}
		else{
			free(head);
			if (is_left) parent->left = NULL;
			else parent->right = NULL;
		}
	}
	else if ((head->left == NULL) || (head->right == NULL)){
		if (head->left != NULL) {child_ptr = head->left;}
                else {child_ptr = head->right;}
            if (parent == NULL){
        	assert(head == sc->root);
                sc->root = child_ptr;
                free(head);
		}
        else{
           if (is_left)  parent->left = child_ptr;
           else  parent->right =  child_ptr;
           free(head);
        }
    }
	else{
		parent_replacement = head;
                replacement = head->left;
		is_left = 1;
		while(replacement->right != NULL){
			parent_replacement = replacement;
			replacement = replacement->right;
			is_left = 0;
		}
		head->data = replacement->data;
		if(is_left){
			assert(replacement->right == NULL);
			head->left = replacement->left;
			free(replacement);
		}
		else{
			parent_replacement->right = replacement->left;
			free(replacement);
		}
	}
	return 1;
}

int sortedcontainer_contains(sortedcontainer* sc, data* data) {
    // Implement this
    if (sc == NULL || data == NULL){
        return 0;
    }
    if (sc->root ==NULL){
        return 0;
    }

	node* head = sc->root;
	while(head){
		if ( data_compare(head->data,data) == 0){
			return 1;
		}
		else if (data_compare(head->data,data) == 1){
			head = head->left;
		}
		else head = head->right;
	}
    return 0;
}

// Do not change
static void node_printtree(node* n, int level, FILE* printFile) {
    fprintf(printFile, "%*s ", level, "");
    if(n) {
        data_print(n->data, printFile);
        fprintf(printFile, "\n");
        node_printtree(n->left, level+1, printFile);
        node_printtree(n->right, level+1, printFile);
    } else {
        fprintf(printFile, "(nil)\n");
    }
}

// Do not change
void sortedcontainer_print(sortedcontainer* sc, FILE* printFile) {
    node_printtree(sc->root, 0, printFile);
}

static void node_deletetree(node* n) {
    if(n) {
        node* left = n->left;
        node* right = n->right;
        node_delete(n);
        node_deletetree(left);
        node_deletetree(right);
    }
}

void sortedcontainer_delete(sortedcontainer* sc) {
    node_deletetree(sc->root);
    free(sc);
}
