/******************************************************
 * This file implements some string related functions
 *
 * Engineer:	Ameya Phadke
 * Date:	16th Dec 2020
 *
 * ****************************************************/

#include "main.h"
#include "mystring.h"


void convertIntToString(uint32_t num, char *retStr){

	int i=0;

	if(num == 0){
		retStr[0] = '0';
		retStr[1] = '\0';
		
		return;
	}

	while(num !=0){
		retStr[i] = '0' + num%10;
		num /= 10;
		i++;
	}

	reverseString(retStr, i);

	retStr[i] = '\0';

	return;
}

uint32_t convertStringToInt(char *str){

	int i=0;
	uint32_t num=0;

	if((str[i] >= '0') | (str[i] <= '9')){
		return 0;
	}
	
	while(str[i] != '\0'){

		num += str[i] - '0';
		num *= 10;
	}

	return num;
}

void reverseString(char *str, uint8_t len){

	char temp;
	uint8_t i;

	for(i=0;i<len/2;i++){
		temp = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = temp;
	}
}

uint32_t strCmp(char *str1, char *str2){

	int i=0,j;
	while((str1[i] - str2[i]) == 0){
		i++;
	}

	if( (str1[i-1] == '\n') && (str2[i-1] == '\n')){
		return 0;
	}
	else{
		return i;
	}

}
