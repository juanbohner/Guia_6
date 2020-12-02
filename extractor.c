/*
Invocacion:
cat archivo.txt|./extractor <posición> <ancho> > campo.txt 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 5
#define CMD_ARG_POS_FIRST_VALUE_TOKEN 1
#define CMD_ARG_FIRST_VALUE_TOKEN "-posicion"
#define CMD_ARG_POS_SECOND_VALUE_TOKEN 3
#define CMD_ARG_SECOND_VALUE_TOKEN "-ancho"

typedef enum{
	OK,
	ERROR_NULL_POINTER			= 1,
	ERROR_INVALID_DATA			= 2,
	ERROR_INVOCATION			= 3,
	MAX_ERRORS
} status_t;

status_t validate_arg_fixed_position(int argc, char *argv[], size_t *a, size_t *b);

int main(int argc, char *argv[])
{
	status_t st;
	size_t a, b, i;
	int c;

	FILE *fp;
	
	st = validate_arg_fixed_position(argc, argv, &a, &b);

	printf("argc: %d \n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    printf("%d\n", argc);

	/*valido e interpetro.*/
    if(st != OK) {
        fprintf(stderr, "%s %s \n", "ERROR:", "Invocacion incorrecta");
        return st;
    }

	printf("a = %ld\tb = %ld\n", a,b);

	/*
	fp=fopen("archivo.txt","r");
	if (!fp){
		printf("Error\n");
		return 1;
	}



	c = fgetc(fp); 

	printf("%c", c);

	fclose(fp);
*/
	return OK;
}

status_t validate_arg_fixed_position(int argc, char *argv[], size_t *a, size_t *b) {
    
    char *tmp;

	/*valido los parametros*/
	if(a == NULL || b == NULL || argv == NULL)
		return ERROR_NULL_POINTER;

	/* validar argc */
    if(argc != MAX_ARGS) 
        return ERROR_INVOCATION;
	
    if(strcmp(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN], CMD_ARG_FIRST_VALUE_TOKEN)) 
        return ERROR_INVOCATION;
	
	*a = strtol(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN + 1], &tmp, 10);

    if(*tmp)
	{
        return ERROR_INVOCATION;
    }


	/*repito lo anterior con b.*/
    if(strcmp(argv[CMD_ARG_POS_SECOND_VALUE_TOKEN], CMD_ARG_SECOND_VALUE_TOKEN)) 
        return ERROR_INVOCATION;

	
    *b = (size_t) strtol(argv[CMD_ARG_POS_SECOND_VALUE_TOKEN + 1], &tmp, 10);
    
	if(*tmp) 
        return ERROR_INVOCATION;

    return OK;
}