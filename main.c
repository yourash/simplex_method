#include "stdio.h"
#include <stdlib.h>


int obmezhennia;
int count_of_vars;
float *main_coefs;
float **coefs;
int count_of_cols;
int count_of_rows;
int way_to_success;
int *array_of_symbols;


int input()
{
	printf("Кількість нерівностей: ");
	if(scanf("%i",&obmezhennia)!=1)
	{
		return 1;
	}
	printf("Кількість змінних: ");
	if(scanf("%i",&count_of_vars)!=1)
	{
		return 1;
	}

	count_of_rows=obmezhennia+1;
	count_of_cols=count_of_vars+obmezhennia+1;

	main_coefs=calloc(count_of_vars,sizeof(float));
	coefs=calloc(count_of_cols,sizeof(float*));

	printf("Ввід цільової функції:\n");
	int counter=0;
	while(counter<count_of_vars)
	{
		printf("X%i=",counter+1 );
		scanf("%f",&main_coefs[counter]);
		counter+=1;
	}
	printf("-> 0-min 1-max:");
	if(scanf("%i",&way_to_success)!=1 || (way_to_success!=0 && way_to_success!=1))
	{
		return 1;
	}

	int i;
	for (i=0; i < count_of_cols; i++)
	{
		coefs[i]=calloc(count_of_rows,sizeof(float));
	}

	array_of_symbols=calloc(obmezhennia,sizeof(float));
	int j;
	for (i = 0; i < obmezhennia; ++i)
	{
		printf("%i умова\n",i+1);
		
		for ( j = 0; j < count_of_vars; ++j)
		{
			printf("X%i=",j+1 );
			scanf("%f",&coefs[i][j+1]);
		}
		printf("знак (0 - <=, 1 - >=):");
		if(scanf("%i", &array_of_symbols[i])!=1 || (array_of_symbols[i]!=0 && array_of_symbols[i]!=1))
		{
			return 1;
		}
		printf("База=");
		if(scanf("%f",&coefs[i][0])!=1)
		{
			return 1;
		}
	}
	for (i = 0; i < count_of_vars; ++i)
	{
		coefs[count_of_rows-1][i+1]=main_coefs[i];
	}
	return 0;
}

int main()
{
	while(input()!=0)
	{
		//fpurge(stdin);
		printf("Неправильний ввід. Заново!\n");
	}

	int i;
	int j;
	for (i = 0; i < count_of_rows; ++i)
	{
		printf("\n");
		for (j = 0; j < count_of_cols; ++j)
		{
			printf("%f  ", coefs[i][j]);
		}
	}
	printf("\n---------------------------\n");
	for (i = 0; i < obmezhennia; ++i)
	{
		printf("%i ",array_of_symbols[i]);
	}
	return 0;
}