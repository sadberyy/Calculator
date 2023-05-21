#pragma once
#define max_stack_len 20
#define max_exp_len 200
#define max_word_len 15

void convert(char inp[], char* out, int* size);
void check(char num[]);
void antiTrash(char num[]);
void change_val(char num1[], char num2[], char symb);
void clearCurr(char* str, int len);
void cleanNull(char num[]);
void calc(char out[], double* res, int size);
