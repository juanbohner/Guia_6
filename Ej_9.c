/*
argumentos en liea de orden:
• la cantidad de números aleatorios a generar (tamaño del lote)
• límite inferior del intervalo
• límite superior del intervalo 

generar random_vector con valores entre el lim inf y lim sup.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VECTOR									50

#define BASE_10										10

#define CMD_ARG_POS_AMOUNT_VALUE_TOKEN 				1
#define CMD_ARG_AMOUNT_VALUE_TOKEN 					"/amount"

#define CMD_ARG_POS_INFERIOR_LIMIT_VALUE_TOKEN 		3
#define CMD_ARG_INFERIOR_LIMIT_VALUE_TOKEN 			"/inf"

#define CMD_ARG_POS_SUPERIOR_LIMIT_VALUE_TOKEN 		5
#define CMD_ARG_SUPERIOR_LIMIT_VALUE_TOKEN 			"/sup"

/*3 de los argumentos y 3 de los numeros que vamos a obtener*/
#define MAX_ARGS									7


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

/*Funcion para generar un arreglo aleatorio, recibe la cantidad de elementos, el lim superior y el inferior.*/
status_t random_array (int v[], size_t n, int max, int min);


status_t validate_arg_dinamic_position(int argc, char *argv[],size_t *amount, int *inferior_limit, int *superior_limit);

int main(int argc, char *argv[])
{
	status_t st;

	size_t amount, i;
	
	int random_vector[MAX_VECTOR];
	
	int inf, sup; 
	
	
	st = validate_arg_dinamic_position(argc, argv, &amount, &inf, &sup);
	if(st != OK)
	{
		fprintf(stderr, "%s %s\n", MSG_ERROR_TYPE, errors[st]);
		return st;
	}

	if(amount > MAX_VECTOR)
	{
		fprintf(stderr, "%s %s\n", MSG_ERROR_TYPE, errors[ERROR_NOT_ENOUGH_MEMORY]);
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	st = random_array (random_vector, amount, sup, inf);
	if(st != OK)
	{
		fprintf(stderr, "%s %s\n", MSG_ERROR_TYPE, errors[st]);
		return st;
	}

	for( i = 0; i < amount; i++)
		printf("%d\n", random_vector[i]);

	return OK;
}
/*Obtencion de amount, limite inf y limite sup*/
status_t validate_arg_dinamic_position(int argc, char *argv[], size_t *amount, int *inferior_limit, int *superior_limit)
 {

	char *tmp;
	size_t i;
	int args_to_parse;

	/*Validar punteros*/
	if(inferior_limit == NULL || superior_limit == NULL || argv == NULL || amount == NULL)
		return ERROR_NULL_POINTER;
	

	/*Veo si se introdueron la cantidad de argumentos esperados*/
	if(argc != MAX_ARGS)
		return ERROR_INVOCATION;

	/*validar que todos sean parametros validos y distintos.*/
	for(i = 1, args_to_parse = MAX_ARGS - 1; i < argc - 1; i += 2)
	{

		/*checkeo para /amount*/
		if(!strcmp(argv[i], CMD_ARG_AMOUNT_VALUE_TOKEN))
		{
			/* Traducción de los valores*/
			*amount = (size_t) strtol(argv[i + 1], &tmp, BASE_10);

			if(*tmp) 
				return ERROR_INVOCATION;

			args_to_parse -= 2;
		}

		/*checkeo para /inf*/
		if(!strcmp(argv[i], CMD_ARG_INFERIOR_LIMIT_VALUE_TOKEN)) 
		{
			*inferior_limit = (int) strtol(argv[i + 1], &tmp, BASE_10);
			
			if(*tmp) 
				return ERROR_INVOCATION;

			args_to_parse -= 2;
    	}

		/*checkeo para /sup*/
		if(!strcmp(argv[i], CMD_ARG_SUPERIOR_LIMIT_VALUE_TOKEN)) 
		{
			*superior_limit = (int) strtol(argv[i + 1], &tmp, BASE_10);
			
			if(*tmp) 
				return ERROR_INVOCATION;

			args_to_parse -= 2;
    	}
	}
	
	if(args_to_parse != 0) {
		return ERROR_INVOCATION;
	}
	
 return OK;
}


status_t random_array(int v[], size_t n, int max, int min)
{
	size_t i;

	if(v == NULL)
        return ERROR_NULL_POINTER;

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{      
		/*Genera numeros aleatorios entre max y min*/
		v[i] = (int) ((rand() % (max - min + 1)) + min);
	}

	return OK;
}