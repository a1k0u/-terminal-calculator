#pragma once

typedef struct STRING
{
	char* word;
	int len;
} STR;

STR* init_str();
STR* del_str(STR* str);
void push_str(STR* str, char letter);
STR* strip_str(STR* str);
STR* input_str();
