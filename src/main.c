/**
 * \file main.c
 * \brief Main file of the profiler
 * \author Bastien CROCHEZ
 * \author Marwin DAMIS
 * \version 1.1
 * \date December 22th 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/gui.h"
#include "../include/tree.h"
/*#include "../include/macro_profiler.h"*/

/**
 * \fn int main(int argc, char *argv[])
 * \brief Entry
 *
 * \return EXIT_SUCCESS if no errors / exits with EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
	/*PROFILE*/
	if(argc != 2) {
		fprintf(stderr, "$> ./myprofiler file_name.log\n");
		exit(EXIT_FAILURE);
	}
	Tree T = NULL;
	Tree subT = NULL;
	FILE* file;
	
	if((file = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error : file not found\n");
		exit(EXIT_FAILURE);
	}
	
	TabOfFun* tab = AllocateTabOF();
	Color color;
	color.red = 200;
	color.green = 0;
	color.blue = 0;
	color.alpha = 255;
	
	LoadFromLog(&T, file);
	fclose(file);
	printf("Loading Complete\n\n");
	
	TabFromTree(&T, tab);
	sortChoice(tab);
	printTab(tab);
	
	subT = ExploreTree(T);

	MLV_create_window("Profiler", NULL, WIN_W, WIN_H);
	DisplayProfiler(&subT, 0, 0, WIN_W, WIN_H, color, T->callTime);

	MLV_actualise_window();
	MLV_wait_mouse(NULL, NULL);
	
	FreeTree(&T);
	
	return EXIT_SUCCESS;
}
