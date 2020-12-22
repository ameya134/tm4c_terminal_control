/* ************************************************
 * This file provides the function decarations for
 * some string operations
 *
 * Engineer: 	Ameya Phadke
 * Date:	16th Dec 2020
 *
 * ***********************************************/

#ifndef _MYSTRING_H
#define _MYSTRING_H


void convertIntToString(uint32_t num, char *retStr);
void reverseString(char * str, uint8_t len);

uint32_t convertStringToInt(char *str);
uint32_t strCmp(char *str1, char *str2);

#endif
