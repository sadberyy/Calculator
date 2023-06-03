#pragma once
#define max_stack_len 20
#define max_exp_len 200
#define max_word_len 15

void convert(char inp[], char* out, int* size, int* count_v);
void check(char var[], char num[], int* count);
void isE(char num[], double* now, int* flag);
void antiTrash(char num[]);
void change_val(char num1[], char num2[], char symb);
void clearCurr(char* str, int len);
void cleanNull(char num[]);
void calc(char out[], double* res, int size, int count_v, char var[]);
