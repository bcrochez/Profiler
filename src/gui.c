#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/tree.h"
#include "../include/gui.h"
/*#include "../include/macro_profiler.h"*/

/**
 * \fn int Width(int left, int right)
 * \brief Function calculating the width between the left and right borders
 *
 * \param left The left border
 * \param right The right border
 * \return An int value of the calculated width
 */
int Width(int left, int right) {
	/*PROFILE*/
	return right - left;
}

/**
 * \fn int Height(int top, int bottom)
 * \brief Function calculating the height between the top and bottom borders
 *
 * \param top The top border
 * \param bottom The bottom border
 * \return An int value of the calculated height
 */
int Height(int top, int bottom) {
	/*PROFILE*/
	return bottom - top;
}

/**
 * \fn void FunctionColor(Color *color, double time, double mainTime)
 * \brief Function using the time of a function to calculate its color in the GUI
 *
 * \param color The color of the rectangle
 * \param time The time of the current function
 * \param mainTime The Time of the "main" function used as a base for the color
 */
void FunctionColor(Color *color, double time, double mainTime) {
	/*PROFILE*/
	color->red = time * 255 / mainTime;
	color->green = 255 - color->red;
	return;
}

/**
 * \fn void DisplayFunction(Tree *T, int left, int top, int right, int bottom, Color color)
 * \brief Function drawing a rectangle for the function pointed by T using the borders left, top, right and bottom
 *
 * \param T The Tree pointing the current function to draw
 * \param left The left border
 * \param top The top border
 * \param right The right border
 * \param bottom The bottom border
 * \param color The color of the rectangle
 */
void DisplayFunction(Tree *T, int left, int top, int right, int bottom, Color color) {
	/*PROFILE*/
	int width = Width(left, right), height = Height(top, bottom);
	
	MLV_draw_filled_rectangle(left, top, width, height,
		MLV_rgba(color.red, color.green, color.blue, color.alpha)
	);
	
	MLV_draw_text_box(left+1, top+1, width-1, BORDER-2, (*T)->name, 0, 
		MLV_rgba(color.red, color.green, color.blue, color.alpha),
		MLV_COLOR_BLACK,
		MLV_rgba(color.red, color.green, color.blue, color.alpha),
		MLV_TEXT_CENTER, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER
	);
	
	MLV_draw_rectangle(left, top, width, height, MLV_COLOR_BLACK);
	return;
}

/**
 * \fn void DisplayStopSon(Tree *T, int left, int top, int right, int bottom, Color color)
 * \brief Function drawing a text box containing "S" if there is not enough space to display the function's sonL
 *
 * \param T The Tree pointing the current function
 * \param left The left border
 * \param top The top border
 * \param right The right border
 * \param bottom The bottom border
 * \param color The color of the rectangle
 */
void DisplayStopSon(Tree *T, int left, int top, int right, int bottom, Color color) {
	/*PROFILE*/
	int width = Width(left, right), height = Height(top, bottom);
	
	MLV_draw_text_box(left, top, width, height, "S", 0,
		MLV_COLOR_BLACK, MLV_COLOR_BLACK,
		MLV_rgba(color.red, color.green, color.blue, color.alpha),
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	
	return;
}

/**
 * \fn void DisplayStopBro(Tree *T, int left, int top, int right, int bottom, Color color)
 * \brief Function drawing a text box containing "B" if there is not enough space to display the function's broR
 *
 * \param T The Tree pointing the current function
 * \param left The left border
 * \param top The top border
 * \param right The right border
 * \param bottom The bottom border
 * \param color The color of the rectangle
 */
void DisplayStopBro(Tree *T, int left, int top, int right, int bottom, Color color) {
	/*PROFILE*/
	int width = Width(left, right), height = Height(top, bottom);
	
	MLV_draw_text_box(left, top, width, height, "B", 0,
		MLV_COLOR_BLACK, MLV_COLOR_BLACK,
		MLV_rgba(color.red, color.green, color.blue, color.alpha),
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	
	return;
}

/**
 * \fn void DisplayProfiler(Tree *T, int left, int top, int right, int bottom, Color color, double mainTime)
 * \brief Function drawing the tree representing the profiled log
 *
 * \param T The Tree pointing the current function
 * \param left The left border
 * \param top The top border
 * \param right The right border
 * \param bottom The bottom border
 * \param color The color of the rectangle
 * \param mainTime The Time of the "main" function used as a base for the color
 */
void DisplayProfiler(Tree *T, int left, int top, int right, int bottom, Color color, double mainTime) {
	/*PROFILE*/
	if(*T == NULL)
		return;	
	
	int nbBro, newRight, width;

	left += BORDER;
	top += BORDER;
	right -= BORDER;
	bottom -= BORDER;
	
	if(Width(left, right) < MIN || (Height(top, bottom) < MIN))
		return;
	
	nbBro = NbBro(*T);
	width = Width(left, right)/nbBro;
	newRight = left + width;
	
	FunctionColor(&color, (*T)->callTime, mainTime);
	
	if(nbBro > 1)
		DisplayFunction(T, left+1, top, newRight-1, bottom, color);
	else
		DisplayFunction(T, left, top, newRight, bottom, color);
	
	if(&(*T)->sonL != NULL) {
		if(Width(left+BORDER, newRight-BORDER) < MIN || (Height(top+BORDER, bottom-BORDER) < MIN)) {
			if(nbBro > 1)
				DisplayStopSon(T, left+1, top, newRight-1, bottom, color);
			else
				DisplayStopSon(T, left, top, newRight, bottom, color);
		}	
		else
			DisplayProfiler(&(*T)->sonL, left, top, newRight, bottom, color, mainTime);
	}
	
	if(nbBro > 1) {
		if(Width(newRight, right) < MIN || (Height(top, bottom) < MIN))
			DisplayStopBro(T, newRight+1, top, right-1, bottom, color);
		else
			DisplayProfiler(&(*T)->broR, newRight-BORDER, top-BORDER, right+BORDER, bottom+BORDER, color, mainTime);
	}
	return;
}
