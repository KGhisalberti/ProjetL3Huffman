#include "structure.h"
#include "main.h"

int main(void){
	char *saisie=malloc(100*sizeof(char));
	long x=0;
	while(x==0){
		do{
			printf("Bienvenue dans le programme du codage de Huffman\nQue souhaitez-vous faire ?\n");
			printf("1)Encoder.\n2)Décoder.\n3)Quittez le programme\n");
			read(saisie,2);
			x=strtol(saisie,NULL,10);
			x=check_choice(x,3);
		}while(x==0);
		switch (x){
			case 1:
				do{
					printf("Souhaitez-vous :\n1)Donnez en paramètre un fichier.\n2)Entrer une phrase.\n");
					read(saisie,2);
					x=strtol(saisie,NULL,10);
					x=check_choice(x,2);
				}while(x==0);
				switch(x){
					case 1: ;
						FILE *f_in;
						do{
							printf("Entrer le nom du fichier à prendre en paramètre.\n");
							read(saisie,98);
							f_in=fopen(saisie,"r");
							if(f_in==NULL)
								printf("Impossible de lire le fichier %s !\n",saisie);
							}while(f_in==NULL);
							printf("Ouverture réussie !\n");
							char *cFile=malloc(100000*sizeof(char));
							char *line=malloc(1000*sizeof(char));
							int length;
							while(fgets(line,999,f_in)!=NULL){
								length=strlen(line);
								line[(length-1)]='\0';
								strcat(cFile,line);
							}
							list *lFile=list_of_node(cFile);
							lFile=chain_fusion(lFile);
							nLink *treeFile=lFile->head;
							while(treeFile->next!=NULL)
								treeFile=treeFile->next;
							rewind(f_in);
							char *codeFile=malloc(100000*sizeof(char));
							char *encode;
							while(fgets(line,999,f_in)!=NULL){
								length=strlen(line);
								line[(length-1)]='\0';
								encode=chain_code(treeFile->node,line);
								strcat(codeFile,encode);
								strcat(codeFile,"\n");
							}
							char *sList=print_all_link(lFile);
							printDualTree(treeFile->node,0);
							printf("%s\n",sList);
							do{
								printf("Souhaitez-vous stocker l'encodage dans un fichier ?\n1)Oui\n2)Non\n");
								read(saisie,2);
								x=strtol(saisie,NULL,10);
								x=check_choice(x,2);
							}while(x==0);
							switch(x){
								case 1: ;
									FILE *f_out2;
									f_out2=fopen("resultF.txt","w+");
									fprintf(f_out2,"%s",codeFile);
									fprintf(f_out2,"%s",sList);
									printf("Sauvegarde réussie\n");
									destroy_tree(treeFile->node);
									destroy_list(lFile);
									fclose(f_out2);
									fclose(f_in);
									x=0;
									printf("\n\n");
									break;
								case 2:
									destroy_list(lFile);
									fclose(f_in);
									x=0;
									printf("\n\n");
									break;
								default:
									printf("Pas censer pouvoir atterir là" );
							}

						break;
					case 2:
						printf("Entrez la phrase à encoder.\n");
						char *c=malloc(1000*sizeof(char));
						read(c,998);
						list *l=list_of_node(c);
						l=chain_fusion(l);
						nLink *tree=l->head;
						char *test=print_all_link(l);
						while(tree->next!=NULL)
							tree=tree->next;
						printDualTree(tree->node,0);
						printf("%s\n",test);
						char *code=chain_code(tree->node,c);
						do{
							printf("Souhaitez-vous stocker l'encodage dans un fichier ?\n1)Oui\n2)Non\n");
							read(saisie,2);
							x=strtol(saisie,NULL,10);
							x=check_choice(x,2);
						}while(x==0);
						switch(x){
							case 1: ;
								FILE *f_out;
								f_out=fopen("result.txt","w+");
								fprintf(f_out,"%s\n",code);
								fprintf(f_out,"%s",test);
								printf("Sauvegarde effectuée\n\n");
								destroy_list(l);
								fclose(f_out);
								x=0;
								clearBuffer();
								printf("\n\n");
								break;
							case 2:
								destroy_list(l);
								x=0;
								clearBuffer();
								printf("\n\n");
								break;
							default:
								printf("Je suis pas censé pouvoir atterir là\n");
								break;
						}
						break;
				}
				break;
			case 2: ;
				FILE *f_in2;
				do{
					printf("Entrer le nom du fichier à décoder.\n");
					read(saisie,98);
					f_in2=fopen(saisie,"r");
					if(f_in2==NULL)
						printf("Impossible de lire le fichier %s !\n",saisie);
					}while(f_in2==NULL);
					char *lineTree=malloc(10000*sizeof(char));
					fgets(lineTree,9999,f_in2);
					while(lineTree[0]!='['){
						fgets(lineTree,9999,f_in2);
					}
					printf("%s\n",lineTree);
					int occur;
					char *val=malloc(2*sizeof(char));
					char *it;
					char *it2;
					char *ptrErr=malloc(10*sizeof(char));
					list *lDecode=create_list();
					for(it=strtok(lineTree,"]");it!=NULL;it=strtok(NULL,"]")){
						val[0]=it[1];
						it2=strchr(it,',');
						if(val[0]==',')
							it2=&it2[2];
						else
							it2=&it2[1];
						occur=(int)strtol(it2,&ptrErr,10);
						nTree *nodeD=create_node_tree(occur,val[0]);
						nLink *link=create_link(nodeD);
						add_to_list(lDecode,link);
					}
					lDecode=chain_fusion(lDecode);
					nLink *it3=lDecode->head;
					while(it3->next!=NULL)
						it3=it3->next;
					printDualTree(it3->node,0);
					rewind(f_in2);
					char *decodeChar=malloc(1000000*sizeof(char));
					fgets(lineTree,9999,f_in2);
					while(lineTree[0]!='['){
						if(lineTree[0]=='\n')
							fgets(lineTree,9999,f_in2);
						else{
							char *decode=chain_decode(it3->node,lineTree);
							strcat(decodeChar,decode);
							printf("%s",decode);
							free(decode);
							fgets(lineTree,9999,f_in2);
						}
					}
					FILE *f_out3;
					f_out3=fopen("resultD.txt","w+");
					fprintf(f_out3,"%s",decodeChar);
					printf("Sauvegarde effectuée dans resultD.txt\n");
					free(val);
					free(decodeChar);
					free(lineTree);
					fclose(f_in2);
					fclose(f_out3);
					x=0;
					printf("\n\n");
					break;
			case 3:
				printf("Au revoir !\n");
				free(saisie);
				return 0;
			default:
				printf("Je suis pas censé pouvoir atterir là\n");
				break;
		}
	}
}

int read(char *c,int length){
	char *posEntree = NULL;
    if (fgets(c, length, stdin) != NULL){
        posEntree = strchr(c, '\n');
        if (posEntree != NULL)
            *posEntree = '\0';
		else
			clearBuffer();
        return 1;
    }else{
		clearBuffer();
        return 0;
	}
}

void clearBuffer(){
	int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int check_choice(int x,int nb_Choice){
	if(x>nb_Choice||x<0){
		printf("Saisir une valeur valide !\n");
		clearBuffer();
		x=0;
	}
	return x;
}
