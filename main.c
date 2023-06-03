#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include "head.h"


int main() {
	char input[max_exp_len];
	char var[max_exp_len];
	printf("Enter an expression without spaces and '=':\n");
	scanf("%s", input);
	char out[max_exp_len] = "";
	int size = 0, flag_v = 0;
	convert(input, out, &size,&flag_v);
	if (flag_v) {
		printf("And enter the values of the variables without spaces using quotation marks:\n");
		scanf("%s", var);
	}
	printf("Reverse postfix notation: \n");
	for (int l = 0; l < size; l++)
		printf("%c ", out[l]);
	printf("\n");

	double res;
	calc(out, &res, size, flag_v, var);
	printf("Answer = %f", res);
}
