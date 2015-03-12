#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
/*#include "macro_profiler.h"*/

/**
 * \struct Node
 * \brief Structure representing a Node and a Tree
 *
 * The Node structure represents a function in a "Left son / Right brother" Tree structure
 * Each node possesses a son and a brother (sonL & broR)
 * Initially, the values of sonL and broR are set to NULL
 * The structure also keeps the start, end and call time of each function
 */
typedef struct node {
	char name[50];
	double start, end, callTime;
	struct node *sonL, *broR;
} Node, *Tree;

/**
 * \struct DataFunction
 * \brief Structure representing a specific function for specific uses (like a table)
 *
 * The DataFunction structure represents a function in a table
 * Contrary to the Node structure, each function is unique
 * If a function is called plural times, the number of calls is increased
 * And so is the totalTime, using the callTime value of that same function
 */
typedef struct dataFunction {
	char name[50];
	int nbCall;
	double totalTime;
} DataFunction;

/**
 * \struct TabOfFun
 * \brief Structure representing a table of DataFunction
 *
 * The TabOfFun structure represents a table of DataFunction
 * The tables creates a new entry for each function that appears in the log
 * A function only appears once, even if it's called several times
 */
typedef struct table {
	DataFunction* tab;
	int size;
} TabOfFun;

Node* AllocateNode(char name[], double start);
TabOfFun* AllocateTabOF();
void PrintTree(Node *N);
void FreeTree(Tree *T);
int NbBro(Node *N);
void PrintTime(double time);
void PrintTimeTree(Node *N);
void CallTime(Node *N);
Node* ExploreTree(Tree T);
int LoadFromLog(Tree* T, FILE* log);
int TabFromTree(Tree* N, TabOfFun* tab);
int printTab(TabOfFun* tab);
void quickSortTime(TabOfFun *tab, int debut, int fin);
void quickSortCall(TabOfFun *tab, int debut, int fin);
void quickSortMoy(TabOfFun *tab, int debut, int fin);
void sortChoice(TabOfFun *tab);

#endif
