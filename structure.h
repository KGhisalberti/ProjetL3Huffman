#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include <string.h>

typedef struct node_tree nTree;

struct node_tree{
  int occ;
  char* letter;
  nTree* nLeft;
  nTree* nRight;
  nTree* nFather;
};

typedef struct node_list nLink;

struct node_list{
	nTree* node;
	nLink* next;
};

typedef struct list list;

struct list{
	int length;
	nLink* head;
};

int search_in_char(char*,char*);

nTree* create_node_tree(int,char);

list* list_of_node(char*);

nLink* fusion(nLink*,nLink*);

list* chain_fusion(list*);

char* code_char(nTree*,char*);

char* chain_code(nTree*,char*);

char* decode_char(nTree*,char*);

char* chain_decode(nTree*,char*);

int occurence(char*,char*);

nLink* create_link(nTree*);

void add_link(nLink*,nLink*);

list* create_list();

void add_to_list(list*,nLink*);

int is_in_list(list,char*);

void tri_list(list*);

void destroy_tree(nTree*);

void destroy_all_link(nLink*);

void destroy_list(list*);

char* print_all_link(list*);

void printDualTree(nTree*,int);

char* print_node_tree(nTree*);
