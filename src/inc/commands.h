/* ************************************************
 * This file provides the function decarations for
 * all valid terminal command functions
 *
 * Engineer: 	Ameya Phadke
 * Date:		4th Jan 2021
 *
 * ***********************************************/

#ifndef _COMMANDS_H
#define _COMMANDS_H

#define cmdLen 3

void led2Command(char *arg);
void pwmCommand(char *arg);
void blinkCommand(char *arg);

#endif
