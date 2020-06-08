#ifndef DISPLAYMAIN_H
#define DISPLAYMAIN_H
#include "core.h"

/* Clears the info box. The cursor is set to the middle of the first line
*/
void clearInfoMsg(void);

/* Displays a centered message in the info box. The cursor is left to the end of the message
*   @param messageLine1[]: the first line of the message to display
*   @param messageLine2[]: the second line of the message to display
*/
void displayInfoMsg(char messageLine1[], char messageLine2[]);

/* Resizes the command prompt window to a given number of lines and columns
*   @param nbOfLines: the number of lines that should be displayed
*   @param nbOfColumns: the number of lines that should be displayed. Microsoft docs recommands a value between 40 and 135
*/
void resizeCmdWindow(int nbOfLines, int nbOfColumns);

#endif // DISPLAYMAIN_H
