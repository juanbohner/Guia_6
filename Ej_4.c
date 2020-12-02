#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR			25

typedef enum{
	OK,
	ERROR_NULL_POINTER,
	MAX_ERRORS
}status_t;

status_t ordenar_str(char *argv[], int argc);

status_t make_lower(char *argv[]);


int main (int argc, char *argv[])
{
	status_t st;
	size_t i;

    printf("argc: %d \n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    printf("%d\n", argc);

	st = ordenar_str(argv, argc);
	if(st != OK)
	{
		fprintf(stderr, "Error\n");
		return st;
	}

	for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
	return 0;
}

status_t ordenar_str(char *argv[], int argc)
{
	size_t i, j;
	status_t st;
	char *temp;
	
	if(argv == NULL)
		return ERROR_NULL_POINTER;


	if((st = make_lower(argv)) != OK)
	{
		return st;
	}
	
	
	for ( i = 1; i < argc; i++) 
	{

      for (j = i + 1; j < argc; j++)
         if (strcmp(argv[i], argv[j]) > 0) 
		 {
            temp = argv[i]; 
            argv[i] = argv[j]; 
            argv[j] = temp; 
         }
	}

	return OK;
}


status_t make_lower(char *argv[])
{   
    size_t i, j;
	
	if(argv == NULL)
		return ERROR_NULL_POINTER;

    for ( i = 0; argv[i] != NULL; i++)
	{
        for (j = 0; argv[i][j] != '\0'; j++)
		{
             argv[i][j] = tolower(argv[i][j]);
        }
    }
	return OK;
} 