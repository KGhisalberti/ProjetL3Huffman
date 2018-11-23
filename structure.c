#include "structure.h"
#include <string.h>

int search_in_char(char *c1,char*c2){      /*Fonction booléenne de recherche de la présence d'un char dans une liste de char*/
	for (unsigned int i=0;i<strlen(c1);i++){
		if(c1[i]==c2[0])
			return 1;
	}
	return 0;
}

nTree* create_node_tree(int valeur,char c){    /*fonction de création d'un noeud d'arbre*/
  nTree *node=malloc(sizeof( struct node_tree));
  node->occ=valeur;
	node->letter=malloc(2*sizeof(char));
  sprintf(node->letter,"%c",c);
  node->nLeft=NULL;
  node->nRight=NULL;
  node->nFather=NULL;
  return node;
}

list* list_of_node(char* c){         /*Fonction de création d'une liste avec les feuilles primaires*/
	int occ=0;
	list *l=create_list();
	for(unsigned int i=0;i<strlen(c);i++){
		char *it=malloc(2*sizeof(char));
		sprintf(it,"%c",c[i]);
		if(is_in_list(*l,it)==0){
			occ=occurence(c,it);
			nTree* node=create_node_tree(occ,it[0]);
			nLink *link=create_link(node);
			add_to_list(l,link);
		}
	}
	tri_list(l);
	return l;
}

nLink* fusion(nLink* link1,nLink* link2){
  int somme=(link1->node)->occ+(link2->node)->occ;
  nTree *node3=create_node_tree(somme,' ');
  node3->nLeft=link1->node;
  node3->nRight=link2->node;
  (link1->node)->nFather=node3;
  (link2->node)->nFather=node3;
  node3->letter = malloc((strlen((link1->node)->letter) + strlen((link2->node)->letter) + 2) * sizeof(char));
  sprintf(node3->letter, "%s%s", (link1->node)->letter,(link2->node)->letter);
  nLink *link_fusion=create_link(node3);
  return link_fusion;
}

list* chain_fusion(list* l){   /*Fonction  de création de l'arbre en fin de liste*/
	int nbOpe=l->length-1;
	nLink *link1=l->head;
	nLink *link2=l->head->next;
	for (int i=0;i<nbOpe;i++){
		nLink *fusion_link=fusion(link1,link2);
		add_to_list(l,fusion_link);
		tri_list(l);
		link1=link2->next;
		link2=link1->next;
	}
	return l;
}

char* code_char(nTree* root,char *c){          /*Fonction d'encodage d'un char*/
	char *code=malloc(50*sizeof(char));
	nTree *it=root;
	while(it->nLeft!=NULL){
		if(search_in_char((it->nLeft)->letter,c)){
			it=it->nLeft;
			code=strcat(code,"0");
		}else{
			it=it->nRight;
			code=strcat(code,"1");
		}
	}
	return code;
}

char* chain_code(nTree *root,char *c){  /*Fonction d'encodage d'une ligne de texte*/
	char *code=malloc(10000*sizeof(char));
	code[0]='\0';
	for(unsigned int i=0;i<strlen(c);i++){
		if(i==strlen(c)-1){
			char *first=malloc(2*sizeof(char));
			sprintf(first,"%c",c[i]);
			code=strcat(code,code_char(root,first));
			/*free(first);*/
		}else{
			char *first=malloc(2*sizeof(char));
			sprintf(first,"%c",c[i]);
			code=strcat(code,code_char(root,first));
			code=strcat(code," ");
			/*free(first);*/
		}
	}
	return code;
}

char* decode_char(nTree* root,char *c){
	for(unsigned int i=0;i<strlen(c);i++){
		if(c[i]=='0')
			root=root->nLeft;
		else if(c[i]=='1')
			root=root->nRight;
		else
			return "Erreur dans le code, il n'y pas que 0 ou 1";
	}
	return root->letter;
}

char* chain_decode(nTree *root,char *c){  /*Fonction de décodage d'une ligne de texte*/
	char *decode=malloc(10000*sizeof(char));
	char *ptr=strchr(c,'\n');
	if(ptr!=NULL && ptr[0]=='\n')
		*ptr='\0';
	for(char *it=strtok(c," ");it!=NULL;it=strtok(NULL," ")){
		decode=strcat(decode,decode_char(root,it));
	}
	decode=strcat(decode,"\n");
	free(ptr);
	return decode;
}

int occurence(char* c1,char* c2){
	int occ=0;
	for(unsigned int i=0;i<strlen(c1);i++){
		if(c1[i]==c2[0])
			occ++;
	}
	return occ;
}

void destroy_tree(nTree* node){
	if(node->nLeft==NULL){
		free(node->letter);
		free(node);
	}else{
		destroy_tree(node->nLeft);
		destroy_tree(node->nRight);
	}
}

char* print_node_tree(nTree *node){  //fonction d'affichage d'un noeud de l'arbre
	char* c=malloc(100*sizeof(char));
	sprintf(c,"[%s,%d]",node->letter,node->occ);
	return c;
}

nLink* create_link(nTree* node_tree){    /*Creation d'un maillon de liste*/
	nLink* link=malloc(sizeof(nTree));
	link->node=node_tree;
	link->next=NULL;
	return link;
}


void add_link(nLink* link,nLink* link2){    /*Ajout d'un maillon à la fin de la chaîne*/
	while(link->next!=NULL)
		link=link->next;
	link->next=link2;
}

void destroy_all_link(nLink *link){
nLink *ptr=link;
	if(link->next!=NULL){
			link=link->next;
			free(ptr);
	}
}

list* create_list(){               /*Creation de la liste*/
	list *l=malloc(sizeof(struct list));
	l->length=0;
	l->head=NULL;
	return l;
}

void add_to_list(list* l,nLink* link){   /*Ajout d'un noeud à la fin de la liste*/
	if(l->length==0){                          /*Si liste est vide ajout au début et mise en place de la tête*/
		l->head=link;
		l->length++;
	}else{
		add_link(l->head,link);
		l->length++;
	}
}

int is_in_list(list l,char* c){     /*Cherche un élément dans la liste en comparant le charactère stocké*/
	if(l.head==NULL){
		return 0;
	}else{
		while(l.head!=NULL){
			if( (l.head)->node->letter[0]==c[0]){;
				return 1;		         /*Retourne vrai si l'élément est dans la liste*/
			}else{
				l.head=(l.head)->next;
			}
		}
	}
	return 0;                                        /*Sinon retourne faux*/
}

void tri_list(list* l){
	nLink* temp=NULL;
	nLink* temp2=NULL;
	nLink* temp3=NULL;
	nTree* min=NULL;
	for(temp=l->head;temp!=NULL;temp=temp->next){
		temp3=temp;
		min=temp->node;
		for(temp2=temp->next;temp2!=NULL;temp2=temp2->next){
			if((min->occ)>((temp2->node)->occ)){
				temp3=temp2;
				min=temp3->node;
			}
		}
		temp3->node=temp->node;
		temp->node=min;
	}
}

void destroy_list(list* l){
	destroy_all_link(l->head);
	free(l);
}

char* print_all_link(list* l){  /*Affichage de toute la liste de noeud*/
	nLink* link=l->head;
	char* c=malloc(100*sizeof(char));
	while(link!=NULL){
		if((link->node)->nLeft==NULL){
			char *clink=print_node_tree(link->node);
			strcat(c,clink);
			link=link->next;
		}else{
			link=link->next;
		}
	}
	return c;
}

void printDualTree(nTree *root,int lvl){
	if(root==NULL)
		return;
	lvl+=5;
	printDualTree(root->nRight,lvl);
	printf("\n");
	for(int i=5;i<lvl-5;i++)
		printf(" ");
	if((lvl-5)>0){
		for(int i=lvl-5;i<lvl;i++)
			printf("-");
	}
	printf("[%s,%d]\n",root->letter,root->occ);
	printDualTree(root->nLeft,lvl);
}
