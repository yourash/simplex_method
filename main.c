#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"



int obmezhennia;
int count_of_vars;
float *main_coefs;
float **coefs;
float **old_coefs;
int count_of_cols;
int count_of_rows;
int way_to_success;
int *array_of_symbols;

int cozirniy_x=-1;
int cozirniy_y=-1;

int *array_of_answer_rows;



void is_equal(int number)
{

	int a,b;
	count_of_rows+=1;
	obmezhennia+=1;
	int *new_array_of_symbols=calloc(obmezhennia,sizeof(int));
	for (a = 0; a < obmezhennia; ++a)
	{
		new_array_of_symbols[a]=array_of_symbols[a];
	}
	free(array_of_symbols);
	array_of_symbols=calloc(obmezhennia,sizeof(int));
	for (a = 0; a < obmezhennia; ++a)
	{
		array_of_symbols[a]=new_array_of_symbols[a];
	}
	array_of_symbols[number]=0;
	array_of_symbols[number+1]=1;

	int **new_coefs;

	new_coefs=calloc(count_of_rows,sizeof(float*));
	for (a=0; a < count_of_rows; a++)
	{
		new_coefs[a]=calloc(count_of_cols,sizeof(float));
	}
	for (a = 0; a < count_of_rows-1; ++a)
	{
		for (b = 0; b < count_of_cols; ++b)
		{
			new_coefs[a][b]=coefs[a][b];
		}
	}
	free(coefs);
	coefs=calloc(count_of_rows,sizeof(float*));
	for (a=0; a < count_of_rows; a++)
	{
		coefs[a]=calloc(count_of_cols,sizeof(float));
	}
	for (a = 0; a < count_of_rows-1; ++a)
	{
		for (b = 0; b < count_of_cols; ++b)
		{
			coefs[a][b]=new_coefs[a][b];
		}
	}
	free(new_coefs);
	for (a = 0; a < count_of_cols; ++a)
	{
		coefs[number+1][a]=coefs[number][a]*(-1);
	}

	free(old_coefs);
	old_coefs=calloc(count_of_rows,sizeof(float*));
	for (a=0; a < count_of_rows; a++)
	{
		old_coefs[a]=calloc(count_of_cols,sizeof(float));
	}
}

void nedopustima()
{
	printf("\n\n");
	printf(ANSI_COLOR_YELLOW);
	printf("Нема допустимих значень!");
	printf(ANSI_COLOR_RESET);
}

void print_answer()
{
	printf("Відповідь: ");
	int i,j;
	int was_not_here=1;
	for (i = 1; i < count_of_vars+1; ++i)
	{
		for (j = 0; j < obmezhennia; ++j)
		{
			if(array_of_answer_rows[j]==i)
			{
				printf("%f*", coefs[j][count_of_cols-1]);
				was_not_here=0;
			}
		}
		if(was_not_here)
		{
			printf("0.000000*");
		}
		was_not_here=1;
		printf("x%i",i );
		if(i!=count_of_vars)
		{
			printf("+");
		}

	}
	printf("=");
	printf("%f\n",coefs[count_of_rows-1][count_of_cols-1] );
}

void input()
{
	printf("Кількість нерівностей: ");
	while(scanf("%i",&obmezhennia)!=1)
	{
		printf("Неправильний ввід. Заново!\n");
		__fpurge(stdin);
	}
	printf("Кількість змінних: ");
	while(scanf("%i",&count_of_vars)!=1)
	{
		printf("Неправильний ввід. Заново!\n");
		__fpurge(stdin);
	}

	count_of_rows=obmezhennia+1;
	count_of_cols=count_of_vars+1;

	main_coefs=calloc(count_of_vars,sizeof(float));
	coefs=calloc(count_of_rows,sizeof(float*));
	old_coefs=calloc(count_of_rows,sizeof(float*));

	array_of_answer_rows=calloc(obmezhennia,sizeof(int));

	int i;
	for (i = 0; i < obmezhennia; ++i)
	{
		array_of_answer_rows[i]=0;
	}

	printf("Ввід цільової функції:\n");
	int counter=0;
	while(counter<count_of_vars)
	{
		printf("X%i=",counter+1 );
		scanf("%f",&main_coefs[counter]);
		counter+=1;
	}
	printf("-> 0-min 1-max:");
	while(scanf("%i",&way_to_success)!=1 || (way_to_success!=0 && way_to_success!=1))
	{
		printf("Неправильний ввід. Заново!\n");
		__fpurge(stdin);
	}

	for (i=0; i < count_of_rows; i++)
	{
		coefs[i]=calloc(count_of_cols,sizeof(float));
	}
	for (i=0; i < count_of_rows; i++)
	{
		old_coefs[i]=calloc(count_of_cols,sizeof(float));
	}

	array_of_symbols=calloc(obmezhennia,sizeof(int));
	int j;
	for (i = 0; i < obmezhennia; ++i)
	{
		printf("%i умова\n",i+1);
		
		for(j = 0; j < count_of_vars; ++j)
		{
			printf("X%i=",j+1 );
			scanf("%f",&coefs[i][j]);
		}
		printf("знак (0 - <=, 1 - >=, 2 - ==):");
		while(scanf("%i", &array_of_symbols[i])!=1 || (array_of_symbols[i]!=0 && array_of_symbols[i]!=1 && array_of_symbols[i]!=2))
		{
			printf("Неправильний ввід. Заново!\n");
			__fpurge(stdin);
		}
		printf("База=");
		while(scanf("%f",&coefs[i][count_of_cols-1])!=1)
		{
			printf("Неправильний ввід. Заново!\n");
			__fpurge(stdin);
		}
		if(array_of_symbols[i]==2)
		{
			is_equal(i);
			i+=1;
		}
	}
	for (i = 0; i < count_of_vars; ++i)
	{
		coefs[count_of_rows-1][i]=main_coefs[i];
	}
}

void print_table()
{
	int i;
	int j;
	for (i = 0; i < count_of_rows; ++i)
	{
		printf("\n");
		if(i!=count_of_rows-1)
		{
			printf("x%i | ", array_of_answer_rows[i]);
		}
		else
		{
			printf("F  | ");
		}
		for (j = 0; j < count_of_cols; ++j)
		{
			if(cozirniy_x==-1 || cozirniy_y==-1)
			{
				printf("%f  ", coefs[i][j]);
			}
			else if(i==cozirniy_y && j==cozirniy_x)
			{
				printf(ANSI_COLOR_RED);
				printf("%f  ", coefs[i][j]);
				printf(ANSI_COLOR_RESET);
			}
			else
			{
				printf("%f  ", coefs[i][j]);
			}
		}
	}
	printf("\n---------------------------\n");
}

void canonical_table()
{
	int i;
	int j;

	for (i = 0; i < count_of_cols; ++i)
	{
		coefs[count_of_rows-1][i]*=(-1);
	}

	for (i = 0; i < obmezhennia; ++i)
	{
		if(array_of_symbols[i]==1)
		{
			for (j = 0; j < count_of_cols; ++j)
			{
				coefs[i][j]*=(-1);
			}
		}
	}

	if(way_to_success==0)
	{
		printf("We have ->MIN\n");
		for (i = 0; i < count_of_cols; ++i)
		{
			coefs[count_of_rows-1][i]*=(-1);
		}
	}
	else
	{
		printf("We have ->MAX\n");
	}
}



int possibility()
{
	int i;
	for (i = 0; i < count_of_rows-1; ++i)
	{
		if(coefs[i][count_of_cols-1]<0)
		{
			printf("Недопустима\n");
			return 0;
		}
	}
	return 1;
}

void compare()
{
	
}

void recount()
{
	int i,j;
	for (i = 0; i < count_of_rows; ++i)
	{
		for (j = 0; j < count_of_cols; ++j)
		{
			old_coefs[i][j]=coefs[i][j];
		}
	}
	array_of_answer_rows[cozirniy_y]=cozirniy_x;
	coefs[cozirniy_y][cozirniy_x]=1;
	for (i = 0; i < count_of_cols; ++i)
	{
		if(i!=cozirniy_x)
		{
			coefs[cozirniy_y][i]/=old_coefs[cozirniy_y][cozirniy_x];
		}
	}
	for (i = 0; i < count_of_rows; ++i)
	{
		if(i!=cozirniy_y)
		{
			coefs[i][cozirniy_x]=0;
		}
	}
	for (i = 0; i < count_of_rows; ++i)
	{
		for (j = 0; j < count_of_cols; ++j)
		{
			if(i!=cozirniy_y && j!=cozirniy_x)
			{
				coefs[i][j]=old_coefs[i][j]-old_coefs[i][cozirniy_x]*old_coefs[cozirniy_y][j]/old_coefs[cozirniy_y][cozirniy_x];
			}
		}
	}
}

int count_of_iterations=0;
void simplex()
{
	count_of_iterations+=1;
	printf("%i ітерація\n", count_of_iterations);
	int i;
	int j;
	float aim_element=0;
	int is_negative=-1;
	if(possibility()==1)
	{
		for (i = 0; i < count_of_cols-1; ++i)
		{
			if(coefs[count_of_rows-1][i]<0)
			{
				if(coefs[count_of_rows-1][i]<aim_element)
				{
					aim_element=coefs[count_of_rows-1][i];
					cozirniy_x=i;
				}
				for (j = 0; j < count_of_rows; ++j)
				{
					if(coefs[j][i]>0)
						is_negative=0;
				}
				if(is_negative==-1)
				{
					nedopustima();
				}
			}
		}
		if(aim_element==0)
		{
			print_table();
			print_answer();
		}
		else
		{
			float divide_value=999999;
			for (i = 0; i < count_of_rows-1; ++i)
			{
				if(coefs[i][count_of_cols-1]/coefs[i][cozirniy_x]<divide_value && coefs[i][count_of_cols-1]/coefs[i][cozirniy_x]>=0)
				{
					divide_value=coefs[i][count_of_cols-1]/coefs[i][cozirniy_x];
					cozirniy_y=i;
				}
				else if(coefs[i][count_of_cols-1]/coefs[i][cozirniy_x]==divide_value && coefs[i][count_of_cols-1]/coefs[i][cozirniy_x]>=0)
				{
					compare();
				}
			}
			print_table();
			recount();
			if(count_of_iterations<40 && is_negative!=-1)
			{
				array_of_answer_rows[cozirniy_y]=cozirniy_x+1;
				simplex();
			}
		}
	}
	else
	{
		int i;
		float min_min=0;
		for (i = 0; i < count_of_rows-1; ++i)
		{
			if(coefs[i][count_of_cols-1]<min_min)
			{
				min_min=coefs[i][count_of_cols-1];
				cozirniy_y=i;
			}
		}
		min_min=0;
		for (i = 0; i < count_of_cols-1; ++i)
		{
			if(coefs[cozirniy_y][i]<min_min)
			{
				min_min=coefs[cozirniy_y][i];
				cozirniy_x=i;
			}
		}
		if(min_min==0)
		{
			nedopustima();
		}
		else
		{
			print_table();
			recount();
			if(count_of_iterations<40)
			{
				array_of_answer_rows[cozirniy_y]=cozirniy_x+1;
				simplex();
			}
		}
	}
}


int main()
{
	input();
	print_table();
	canonical_table();
	print_table();
	simplex();
	return 0;
}