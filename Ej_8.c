#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARGS 3
#define CMD_ARG_POS_FIRST_VALUE_TOKEN 2
#define CMD_ARG_MAYUSC_VALUE_TOKEN "/M"
#define CMD_ARG_LOWER_CASE_VALUE_TOKEN "/m"


#define MSG_ERROR_TYPE								"Error del tipo:"
#define MSG_ERROR_NULL_POINTER						"Puntero a NULL"
#define MSG_ERROR_INVOCATION						"Invocacion invalida"
#define MSG_ERROR_NOT_ENOUGH_MEMORY					"Insuficiente memoria"

typedef enum
{
	OK,
	ERROR_NULL_POINTER			= 1,
	ERROR_INVOCATION			= 2,
	ERROR_NOT_ENOUGH_MEMORY		= 3,
	MAX_ERRORS
} status_t;

const char *errors[MAX_ERRORS] = {MSG_ERROR_TYPE, MSG_ERROR_NULL_POINTER, MSG_ERROR_INVOCATION, MSG_ERROR_NOT_ENOUGH_MEMORY};


status_t validate_arg_fixed_position_upper_or_lower_case(int argc, char *argv[]);

void make_lower(char *argv[]);

void make_upper(char *argv[]);

int main (int argc, char *argv[]){

    status_t st;
	size_t i;

	printf("%s\n", "Original:");

	for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }

	/*Entrada viene por lo argumentos de liena de orden. Aca hacemos la traaduccion.*/
    st = validate_arg_fixed_position_upper_or_lower_case(argc, argv);

	/*valido e interpetro.*/
    if(st != OK) {
        fprintf(stderr, "%s %s \n", "ERROR:", "Invocacion incorrecta");
        return st;
    }

	printf("%s\n", "Cambiado:");
	for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    
    return EXIT_SUCCESS;
}

/*Esta mal poner a las funciones de pasar a minuscula y a mayusucla adento de esta funcion?*/
status_t validate_arg_fixed_position_upper_or_lower_case(int argc, char *argv[]) 
{

	/*valido los parametros*/
	if( argv == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	/* Siempre validar argc */
    if(argc != MAX_ARGS) 
	{
        return ERROR_INVOCATION;
    }


	/* Validación de /M */
    if(strcmp(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN], CMD_ARG_MAYUSC_VALUE_TOKEN) == 0) 
	{
		make_upper(argv);
		return OK;
    }

	/*repito lo anterior con /m*/
    if(strcmp(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN], CMD_ARG_LOWER_CASE_VALUE_TOKEN) == 0) 
	{
		make_lower(argv);
        return OK;
    }

    return ERROR_INVOCATION;
}





void make_lower(char *argv[])
{   
    size_t i, j;

    for ( i = 0; argv[i] != NULL; i++)
	{
        for (j = 0; argv[i][j] != '\0'; j++)
		{
             argv[i][j] = tolower(argv[i][j]);
        }
    }

	return ;
} 





void make_upper(char *argv[])
{   
    size_t i, j;

	for ( i = 0; argv[i] != NULL; i++)
	{
        for (j = 0; argv[i][j] != '\0'; j++)
		{
             argv[i][j] = toupper(argv[i][j]);
        }
    }
	return ;
} 