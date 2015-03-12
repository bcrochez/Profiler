#ifndef __GUI_H__
#define __GUI_H__

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "tree.h"

#define WIN_W 800
#define WIN_H 600
#define MIN 50
#define BORDER 15

/**
 * \struct Color
 * \brief Structure representing a color
 *
 * The Color structure contains 4 int values to represent a color using the rgb system
 * The alpha value is the opacity
 */
typedef struct color {
	int red;
	int green;
	int blue;
	int alpha;
} Color;

int Width(int left, int right);
int Height(int top, int bottom);
void FunctionColor(Color *color, double time, double mainTime);
void DisplayFunction(Tree *T, int left, int top, int right, int bottom, Color color);
void DisplayStopSon(Tree *T, int left, int top, int right, int bottom, Color color);
void DisplayStopBro(Tree *T, int left, int top, int right, int bottom, Color color);
void DisplayProfiler(Tree *T, int left, int top, int right, int bottom, Color color, double mainTime);

#endif
