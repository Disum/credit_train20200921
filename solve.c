#include <stdio.h>
#include <string.h>
#include "solve.h"
#include "heapsort.h"
int charcmp(char a, char b);
int check(char *buff, char *s, char *t, int t_len, int (*wordcmp)(int));
int find(char a, char *t, int t_len, int *index);
int wordcmp1(int res_cmp);
int wordcmp2(int res_cmp);
int wordcmp3(int res_cmp);
int wordcmp4(int res_cmp);
int wordcmp5(int res_cmp);
int wordcmp6(int res_cmp);
#define MAX_LEN 1024

int sovle(char *a, char *b, char *s, char *t, char *x)
{
	FILE *input, *output;
	char buff[MAX_LEN];
	int result = 0, t_len = strlen(t);
	int (*wordcmp)(int) = 0;

	if( strcmp(x, "<")==0 )
		wordcmp = wordcmp1;
	if( strcmp(x, ">")==0 )
		wordcmp = wordcmp2;
	if( strcmp(x, "<=")==0 )
		wordcmp = wordcmp3;
	if( strcmp(x, ">=")==0 )
		wordcmp = wordcmp4;
	if( strcmp(x, "==")==0 )
		wordcmp = wordcmp5;
	if( strcmp(x, "!=")==0 )
		wordcmp = wordcmp6;
	if( !wordcmp )
		return ERR_CMP;

	if( !(input = fopen(a, "r")) )
		return ERR_OPEN;
	if( !(output = fopen(b, "w")) )
	{
		fclose(input);
		return ERR_OPEN;
	}

	heapsort(t, t_len, &charcmp);

	while( fgets(buff, MAX_LEN, input) )
		if( check(buff, s, t, t_len, wordcmp) )
		{
			fprintf(output, "%s\n", buff);
			result++;
		}

	fclose(output);
	if( !feof(input) )
	{
		fclose(input);
		return ERR_READ;
	}
	fclose(input);
	return result;
}

int check(char *buff, char *s, char *t, int t_len, int (*wordcmp)(int))
{
	char *word = buff;
	int i, j;

	for( i = 0; buff[i]!='\0' && buff[i]!='\n'; i++ )
		if( find(buff[i], t, t_len, &j) )
		{
			buff[i] = '\0';
			if( !wordcmp(strcmp(word, s)) )
				return 0;
			buff[i] = t[j];
			word = buff + i + 1;
		}
	buff[i] = '\0';
	if( !wordcmp(strcmp(word, s)) )
		return 0;

	return 1;
}

int find(char a, char *t, int t_len, int *index)
{
	int left, right, middle, res_cmp;

	res_cmp = charcmp(a, t[t_len - 1]);
	if( res_cmp>0 )
		return 0;
	if( res_cmp==0 )
	{
		*index = t_len - 1;
		return 1;
	}
	res_cmp = charcmp(a, t[0]);
	if( res_cmp<0 )
		return 0;
	if( res_cmp==0 )
	{
		*index = 0;
		return 1;
	}

	left = 0;
	right = t_len;
	while( left<right )
	{
		middle = (int)( (right + left)/2 );
		res_cmp = charcmp(a, t[middle]);
		if( res_cmp==0 )
		{
			*index = middle;
			return 1;
		}
		if( res_cmp>0 )
			left = middle + 1;
		else
			right = middle;
	}

	return 0;
}

int charcmp(char a, char b)
{
	if( a>b )
		return 1;
	if( a<b )
		return -1;
	return 0;
}

int wordcmp1(int res_cmp)
{
	if( res_cmp>0 )
		return 1;
	return 0;
}
int wordcmp2(int res_cmp)
{
	if( res_cmp<0 )
		return 1;
	return 0;
}
int wordcmp3(int res_cmp)
{
	if( res_cmp>=0 )
		return 1;
	return 0;
}
int wordcmp4(int res_cmp)
{
	if( res_cmp<=0 )
		return 1;
	return 0;
}
int wordcmp5(int res_cmp)
{
	if( res_cmp==0 )
		return 1;
	return 0;
}
int wordcmp6(int res_cmp)
{
	if( res_cmp!=0 )
		return 1;
	return 0;
}
