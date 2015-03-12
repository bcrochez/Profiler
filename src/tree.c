#include "../include/tree.h"
/*#include "../include/macro_profiler.h"*/

/**
 * \fn Node* AllocateNode(char name[], double start)
 * \brief Function allocating and creating a new Node* representing a function
 *
 * \param name Name of the function
 * \param start Start time of the function
 * \return A new allocated Node*
 */
Node* AllocateNode(char name[], double start) {
	/*PROFILE*/
	Node* new;
	if((new = malloc(sizeof(Node))) == NULL) {
		fprintf(stderr, "malloc - allocNode\n");
		exit(EXIT_FAILURE);
	}
	strcpy(new->name, name);
	new->start = start;
	new->end = 0;
	new->callTime = 0;
	new->sonL = NULL;
	new->broR = NULL;
	return new; 
}

/**
 * \fn TabOfFun* AllocateTabOF()
 * \brief Function allocating and creating a new TabOfFun
 *
 * \return A new allocated TabOfFun
 */
TabOfFun* AllocateTabOF() {
	/*PROFILE*/
	TabOfFun *new = malloc(sizeof(TabOfFun*));
	if(new == NULL) {
		fprintf(stderr, "malloc - tabOfFun\n");
		exit(EXIT_FAILURE);
	}
	new->size = 0;
	new->tab = malloc(sizeof(DataFunction));
	if(new->tab == NULL) {
		fprintf(stderr, "malloc - dataFunction\n");
		exit(EXIT_FAILURE);
	}
	return new;
}

/**
 * \fn void PrintTree(Node *N)
 * \brief Function printing the tree on the standard output
 *
 * \param N Current node of the tree
 */
void PrintTree(Node *N) {
	/*PROFILE*/
	printf("%s\n", N->name);
	if(N->sonL != NULL)
		PrintTree(N->sonL);
	if(N->broR != NULL)
		PrintTree(N->broR);
	return;
}

/**
 * \fn int NbBro(Node *N)
 * \brief Function counting the number of broR of the node N
 *
 * \param N Current Node of the tree
 * \return An int value of the number of broR
 */
int NbBro(Node *N) {
	/*PROFILE*/
	if(N->broR == NULL)
		return 1;
	return NbBro(N->broR) + 1;
}

/**
 * \fn void FreeTree(Tree *T)
 * \brief Function free liberating the memory used by a tree
 *
 * \param T Tree to free
 */
void FreeTree(Tree *T) {
	if(*T == NULL)
		return;
	FreeTree(&(*T)->sonL);
	FreeTree(&(*T)->broR);
	free(*T);
}

/**
 * \fn void PrintTime(double time)
 * \brief Function printing a time
 *
 * \param time Time to print on the standard output
 */
void PrintTime(double time) {
	/*PROFILE*/
	printf("%.6lfs\n", time);
	return;
}

/**
 * \fn void PrintTree(Node *N)
 * \brief Function printing the tree with the call time of each node on the standard output
 *
 * \param N Current Node of the tree
 */
void PrintTimeTree(Node *N) {
	/*PROFILE*/
	printf("%s : callTime :", N->name);
	PrintTime(N->callTime);
	if(N->sonL != NULL)
		PrintTimeTree(N->sonL);
	if(N->broR != NULL)
		PrintTimeTree(N->broR);
	return;
}

/**
 * \fn void CallTime(Node *N)
 * \brief Function calculating the callTime of a function using the start and end values of the node
 *
 * \param N Current Node of the tree
 */
void CallTime(Node *N) {
	/*PROFILE*/
	N->callTime = N->end - N->start;
	return;
}

/**
 * \fn int TabFromTree(Tree* T, TabOfFun* tab)
 * \brief Function creating a TabOfFun from a Tree
 *
 * \param T Tree used to build the tab
 * \param tab TabOfFun created based on the tree
 * \return 1 if success / exit with EXIT_FAILURE
 */
int TabFromTree(Tree* T, TabOfFun* tab) {
	/*PROFILE*/
	int i;
	for(i=0; i<tab->size; i++) {
		if(strcmp((*T)->name, (tab->tab[i]).name) == 0) {
			tab->tab[i].nbCall++;
			tab->tab[i].totalTime += (*T)->callTime;
			if((*T)->sonL != NULL)
				TabFromTree(&(*T)->sonL, tab);
			if((*T)->broR != NULL)
				TabFromTree(&(*T)->broR, tab);
			return 1;
		}
	}
	tab->size++;
	tab->tab = realloc(tab->tab, sizeof(DataFunction)*tab->size);
	if(tab->tab == NULL) {
		fprintf(stderr, "realloc - tabOfFun\n");
		exit(EXIT_FAILURE);
	}
	strcpy(tab->tab[tab->size-1].name, (*T)->name);
	tab->tab[tab->size-1].nbCall = 1;
	tab->tab[tab->size-1].totalTime += (*T)->callTime;
	if((*T)->sonL != NULL)
		TabFromTree(&(*T)->sonL, tab);
	if((*T)->broR != NULL)
		TabFromTree(&(*T)->broR, tab);
	return 1;
}

/**
 * \fn int printTab(TabOfFun* tab)
 * \brief Function printing a TabOfFun with the number of calls, the total time, and the average time for each function
 *
 * \param tab The TabOfFun to print
 * \return 1 for success
 */
int printTab(TabOfFun* tab) {
	/*PROFILE*/
	int i;
	for(i=0; i<tab->size; i++) {
		printf("Function: %s\nNumber of calls = %d\tTotal time = %lfs\tAverage time = %lfs\n", tab->tab[i].name, tab->tab[i].nbCall, tab->tab[i].totalTime, tab->tab[i].totalTime/tab->tab[i].nbCall);
	}
	return 1;
}

/**
 * \fn Node* ExploreTree(Tree T)
 * \brief Function creating Sub-Tree of a Tree by exploring its sonL and broR
 *
 * \param T Tree to explore
 * \return A Sub-Tree of T
 */
Node* ExploreTree(Tree T) {
	/*PROFILE*/
	Tree subT = T;
	char c;
	printf("\n\nExploring the Tree\n");
	printf("Commands :\ns -> sonL\nb -> broR\nPress o if you're done\nPress r if you want to restart the exploration\nPress h for help\n"); 
	printf("Current position : %s\n", subT->name);
	do {
		scanf("%c", &c);
		switch(c) {
			case 's':
				if(subT->sonL == NULL)
					printf("This node does not have a sonL\n");
				else
					subT = subT->sonL;
				printf("Current position : %s\n", subT->name);
				break;
			case 'b':
				if(subT->broR == NULL)
					printf("This node does not have a broR\n");
				else
					subT = subT->broR;
				printf("Current position : %s\n", subT->name);
				break;
			case 'o':
				subT = subT;
				break;
			case 'r':
				subT = T;
				printf("Current position : %s\n", subT->name);
				break;
			case 'h':
				printf("Commands :\ns -> sonL\nb -> broR\nPress o if you're done\nPress r if you want to restart the exploration\nPress h for help\n");
				break;
			default:
				break;
		}
		
	} while(c != 'o');
	
	return subT;
}

/**
 * \fn int LoadFromLog(Tree* T, FILE* log)
 * \brief Function creating a tree based on a .log file
 *
 * \param T Tree created
 * \param log File used to build the tree
 * \return 1 if success / exit with EXIT_FAILURE
 */
int LoadFromLog(Tree* T, FILE* log) {
	/*PROFILE*/

	char name[50];
	double time;

	while(fscanf(log, "%s -- time : %lfs\n", name, &time) != EOF) {

		if(strcmp("END", name) != 0) {
			Node* new = AllocateNode(name, time);
			
			if(new == NULL) {
				fprintf(stderr, "Error - AllocateNode\n");
				exit(EXIT_FAILURE);
			}
	
			if(*T == NULL) {
				*T = new;
			}
			else {
				if((*T)->sonL == NULL) {
					(*T)->sonL = new;
					LoadFromLog(&(*T)->sonL, log);
				}
				else {
					Node* tmp;
					tmp = (*T)->sonL;
					while(tmp->broR != NULL)
						tmp = tmp->broR;
					tmp->broR = new;
					LoadFromLog(&new, log);
				}
			}
		}
		else {
			(*T)->end = time;
			CallTime(*T);
			break;
		}
	}
	return 1;
}

/**
 * \fn void swap(DataFunction *a, DataFunction *b)
 * \brief Function swaping 2 DataFunction structures
 *
 * \param a First DataFunction to swap
 * \param b Second DataFunction to swap
 */
void swap(DataFunction *a, DataFunction *b) {
	/*PROFILE*/
	DataFunction c = *a;
	*a = *b;
	*b = c;
	return;
}

/**
 * \fn void quickSortTime(TabOfFun *tab, int debut, int fin)
 * \brief Function sorting a TabOfFun by the total time of each function
 *
 * \param tab The TabOfFun to sort
 * \param debut The left end of the tab
 * \param fin The right end of the tab
 */
void quickSortTime(TabOfFun *tab, int debut, int fin) {
	/*PROFILE*/
	int gauche = debut-1;
	int droite = fin+1;
	float pivot = tab->tab[debut].totalTime;
	if(debut >= fin)
		return;
	while(1) {
		do {
			droite--;
		} while(droite > debut && tab->tab[droite].totalTime < pivot);
		do {
			gauche++;
		} while(gauche < fin && tab->tab[gauche].totalTime > pivot);
		if(gauche < droite)
			swap(&tab->tab[gauche], &tab->tab[droite]);
		else break;
	}
	quickSortTime(tab, debut, droite);
	quickSortTime(tab, droite+1, fin);
	return;
}

/**
 * \fn void quickSortCall(TabOfFun *tab, int debut, int fin)
 * \brief Function sorting a TabOfFun by the number of calls of each function
 *
 * \param tab The TabOfFun to sort
 * \param debut The left end of the tab
 * \param fin The right end of the tab
 */
void quickSortCall(TabOfFun *tab, int debut, int fin) {
	/*PROFILE*/
	int gauche = debut-1;
	int droite = fin+1;
	float pivot = tab->tab[debut].nbCall;
	if(debut >= fin)
		return;
	while(1) {
		do {
			droite--;
		} while(droite > debut && tab->tab[droite].nbCall < pivot);
		do {
			gauche++;
		} while(gauche < fin && tab->tab[gauche].nbCall > pivot);
		if(gauche < droite)
			swap(&tab->tab[gauche], &tab->tab[droite]);
		else break;
	}
	quickSortCall(tab, debut, droite);
	quickSortCall(tab, droite+1, fin);
	return;
}

/**
 * \fn void quickSortMoy(TabOfFun *tab, int debut, int fin)
 * \brief Function sorting a TabOfFun by the average time of each function
 *
 * \param tab The TabOfFun to sort
 * \param debut The left end of the tab
 * \param fin The right end of the tab
 */
void quickSortMoy(TabOfFun *tab, int debut, int fin) {
	/*PROFILE*/
	int gauche = debut-1;
	int droite = fin+1;
	float pivot = (float)(tab->tab[debut].totalTime/tab->tab[debut].nbCall);
	if(debut >= fin)
		return;
	while(1) {
		do {
			droite--;
		} while(droite > debut && (float)(tab->tab[droite].totalTime/tab->tab[droite].nbCall) < pivot);
		do {
			gauche++;
		} while(gauche < fin && (float)(tab->tab[gauche].totalTime/tab->tab[gauche].nbCall) > pivot);
		if(gauche < droite)
			swap(&tab->tab[gauche], &tab->tab[droite]);
		else break;
	}
	quickSortMoy(tab, debut, droite);
	quickSortMoy(tab, droite+1, fin);
	return;
}

/**
 * \fn void sortChoice(TabOfFun *tab)
 * \brief Function sorting the TabOfFun depending on the user's choice
 *
 * \param tab The TabOfFun to sort
 */
void sortChoice(TabOfFun *tab) {
	/*PROFILE*/
	char c;
	printf("Type of sort:\n");
	printf("-Press 'c' to sort by number of calls\n");
	printf("-Press 't' to sort by total time\n");
	printf("-Press 'a' to sort by average time per call\n");
	while(1) {
		scanf("%c", &c);
		switch(c) {
			case 'c':
				printf("\nSort by calls:\n");
				quickSortCall(tab, 0, tab->size-1);
				return;
			case 'a':
				printf("\nSort by average time per call:\n");
				quickSortMoy(tab, 0, tab->size-1);
				return;
			case 't':
				printf("\nSort by total time:\n");
				quickSortTime(tab, 0, tab->size-1);
				return;
			default:
				break;
		}
	}
	return;
}
