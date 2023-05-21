#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "head.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



int isOper(char s) {
	char operations[] = "+-*/^()";
	for (int i = 0; i < strlen(operations); i++) {
		if (s == operations[i])
			return 1;
	}
	return 0;
}

int priority(char s) {
	switch (s) {
	case '+': return 2;
	case '-': return 2;
	case '*': return 4;
	case '/': return 4;
	case '^': return 5;
	case '(': return -1;
	case ')': return -1;
	default:
		printf("Your operation is incomprehensible");
		exit(1);
	}
}


void convert(char input[], char* out, int* size) {
	char stack[max_stack_len] = "";
	char result[max_exp_len] = "";
	char tmp[max_stack_len] = "";
	int t = 0, k = 0, p = 0;
	int num_flag = 0, unary_minus = 0;
	for (int i = 0; i < strlen(input); i++) {

		if (isOper(input[i])) {
			if (num_flag) {
				result[p++] = ' ';
				num_flag = 0;
				if (unary_minus) {
					result[p++] = '-';
					result[p++] = ' ';
					unary_minus = 0;
				}
			}

			if (!strlen(result) && input[i] == '-') {
				result[p++] = '0';
				result[p++] = ' ';
				unary_minus = 1;
				continue;
			}

			if (input[i - 1] == '(' && input[i] == '-') {
				result[p++] = '0';
				result[p++] = ' ';
				unary_minus = 1;
				continue;
			}

			if (input[i] == '(') {
				stack[k++] = input[i];
				continue;
			}

			if (input[i] == ')') {
				stack[k] = input[i];
				int j = k - 1;
				int count_del = 0;
				int flag = 0;
				while (stack[j] != '(') {
					result[p++] = stack[j];
					result[p++] = ' ';
					stack[j] = NULL;
					count_del++;
					j--;
				}
				stack[j] = NULL;
				stack[k] = NULL;
				k = k - count_del - 1;
				continue;
			}

			if (!strlen(stack)) {
				stack[k++] = input[i];
				continue;
			}

			if (stack[k - 1] != '(' && priority(input[i]) <= priority(stack[k - 1])) {
				int top = k - 1;
				while (top != (-1) && (priority(input[i]) <= priority(stack[top]))) {
					result[p++] = stack[top];
					result[p++] = ' ';
					stack[top] = NULL;
					top--;
				}
				k = top + 1;
			}
			stack[k++] = input[i];
		}

		else {
			result[p++] = input[i];
			num_flag = 1;
		}
	}

	if (unary_minus) {
		result[p++] = '-';
		result[p++] = ' ';
	}

	for (int i = max_stack_len - 1; i >= 0; i--) {
		if (isOper(stack[i])) {
			result[p++] = stack[i];
			result[p++] = ' ';
		}
	}

	p++;
	memmove(out, result, p);
	*size = p - 1;
}

void check(char num[]) {
	if (memcmp(num, "abc", 3) == 0)
		_gcvt(5.34, 4, num);

	else if (memcmp(num, "xxx", 3) == 0)
		_gcvt(-97.12, 6, num);

	else if (memcmp(num, "z", 1) == 0)
		_gcvt(23.23, 5, num);

	else if (memcmp(num, "asd", 3) == 0)
		_gcvt(-2.5, 4, num);

	else if (isalpha(num[0])) {
		printf("I don't know such a variable that you entered");
		exit(1);
	}
}

isE(char num[], double* now, int* flag) {
	char so_small_big[max_exp_len] = "";
	char sign[1];
	char power[max_word_len - 1] = "";
	int c = 0, p = 0, pow_num = 0;
	int flag_e = 0, symb = 0;
	for (int j = 0; j < max_exp_len - 3; j++) {
		if (num[j] == ' ' || num[j] == NULL)
			break;

		if (flag_e && isOper(num[j])) {
			sign[0] = num[j];
			symb = 1;
		}

		else if (flag_e && symb)
			power[p++] = num[j];

		else if (num[j] == 'e')
			flag_e = 1;

		else if (isdigit(num[j]) || num[j] == '.')
			so_small_big[c++] = num[j];
	}

	if (flag_e) {
		*flag = 1;
		*now = atof(so_small_big);
		pow_num = atoi(power);

		if (sign[0] == '+')
			*now = (*now) * pow(10, pow_num);
		else
			*now = (*now) * pow(10, (-pow_num));

		*now = (round((*now) * 100000)) / 100000;
		_gcvt((*now), max_word_len - 3, num);
	}
}

void antiTrash(char num[]) {
	int pos = max_word_len;

	for (int j = 0; j < max_word_len - 2; j++) {
		if (num[j] == '.') {
			pos = j;
			continue;
		}
		if (j - pos > 4)
			num[j] = NULL;
	}

	double now = atof(num);
	now = (round(now * 10000)) / 10000;
	_gcvt(now, max_word_len - 3, num);
}


void change_val(char num1[], char num2[], char symb) {
	double new = 0;

	if (symb == '-')
		new = atof(num1) - atof(num2);
	else if (symb == '+')
		new = atof(num1) + atof(num2);
	else if (symb == '*')
		new = atof(num1) * atof(num2);
	else if (symb == '/')
		new = atof(num1) / atof(num2);
	else if (symb == '^')
		new = pow(atof(num1), atof(num2));

	for (int j = 0; j < strlen(num1); j++)
		num1[j] = NULL;

	char tmp[max_exp_len] = "";
	_gcvt(new, max_exp_len - 7, tmp);
	int f = 0;
	isE(tmp, &new, &f);
	if (f)
		memmove(num1, tmp, max_word_len - 3);
	else {
		_gcvt(new, max_word_len - 3, num1);
		antiTrash(num1);
	}
}

void clearCurr(char* str, int len) {
	for (int j = 0; j < len; j++)
		str[j] = NULL;
}

void cleanNull(char num[]) {
	int count_nl = 0;
	for (int r = 0; r < strlen(num); r++) {
		if (num[r] == '0')
			count_nl++;
		else
			break;
	int j = 0;
	while (j != (strlen(num) - count_nl)) {
		num[j] = num[j + count_nl];
		j++;
	}
}

void calc(char out[], double* res, int size) {
	char num1[max_word_len] = "";
	char num2[max_word_len] = "";
	char end[max_word_len] = "";
	char tmp[max_exp_len] = "";
	int flag = 1, flag_oper = 0;
	int k = 0, p = 0, t = 0;
	int from = 0, to = 0;
	for (int i = 0; i < max_exp_len - 3; i++) {
		if (out[i] != ' ') {
			if (isOper(out[i])) {
				flag_oper = 1;
				to = i;
				for (int j = to - 1; j >= 0; j--) {
					if (out[j] == ' ')
						continue;
					else if (flag) {
						num2[k++] = out[j];
						out[j] = ' ';
						if (out[j - 1] == ' ')
							flag = 0;
						continue;
					}
					else if (!flag) {
						num1[p++] = out[j];
						out[j] = ' ';
						if (out[j - 1] == ' ') {
							from = j;
							break;
						}
					}
				}

				_strrev(num1);
				_strrev(num2);
				cleanNull(num1);
				cleanNull(num2);
				check(num1);
				check(num2);
				change_val(num1, num2, out[i]);
				out[i] = ' ';

				if ((to - from + 1) <= strlen(num1)) {
					for (int j = 0; j <= size; j++) {
						if (j != from)
							tmp[t++] = out[j];
						else {
							while ((to - from + 1) <= strlen(num1)) {
								tmp[t++] = ' ';
								to++;
							}
						}
					}

					memmove(out, tmp, max_exp_len - 3);
					t = 0;
				}
				to = i;

				k = 0;
				for (int j = from; j < from + strlen(num1); j++)
					out[j] = num1[k++];

				memmove(end, num1, max_word_len - 3);

				clearCurr(num1, strlen(num1));
				clearCurr(num2, strlen(num2));

				k = 0;
				p = 0;
				flag = 1;
				i = to;
			}
		}
	}

	if (!flag_oper) {

		for (int i = 0; i < max_exp_len - 2; i++) {
			if (isalnum(out[i]) || out[i] == '.')
				num1[i] = out[i];
		}
		check(num1);
		for (int i = 0; i < strlen(num1); i++)
			printf("%c", num1[i]);
		exit(0);
	}

	*res = atof(end);
}
