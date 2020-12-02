/*
En este ejercicio, es similar al anterior, para comprar dos cadenas de caracteres, va a ser necesario que el usuario pase las cadenas entre "".
porque si no lo hace, se van a considerar cada palabra de cada cadena como un str por separado.
*/

/*Preguntar como hago para validar el tema de que quiero comparar */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

			
#define MSG_STR_LEN			"el largo de la cadena es:"
#define MSG_STR_COMPARE		"La comparacion de las cadenas dio:"
#define MSG_STR_IGUALES			"cadenas iguales"
#define MSG_STR_DIFERENTES		"cadenas diferentes"


#define MSG_ERROR_NULL_POINTER				"Puntero NULL"
#define MSG_OK								"OK"
#define MSG_ERROR_EMPTY_STR					"No se introdujo dos cadenas de caracteres"
#define MSG_ERROR_INVALID_AUMOUNT_OF_STR 	"Se ingreso mas de 2 cadenas de caracteres"


#define MAX_STR 			2

typedef enum {
				OK,
				ERROR_NULL_POINTER					= 1,  
				ERROR_EMPTY_STR						= 2,
				ERROR_INVALID_AUMOUNT_OF_STR		= 3,
				MAX_ERRORS
} status_t;

const char *errors [MAX_ERRORS] = {MSG_OK, MSG_ERROR_NULL_POINTER, MSG_ERROR_EMPTY_STR, MSG_ERROR_INVALID_AUMOUNT_OF_STR};

status_t compare_string(char *argv[], int argc, int *compare);

int main (int argc, char * argv[])
{

	status_t st;
	int compare;
	
	size_t i;
    printf("argc: %d \n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    printf("%d\n", argc);
	
	st = compare_string( argv, argc, &compare);

	if(st != OK)
	{
		fprintf(stderr, "%s%s\n", "ERROR:", errors[st]);
		return st;
	}

	if (compare != 0) 
	{
		printf("%s %s\n", MSG_STR_COMPARE, MSG_STR_DIFERENTES);
		return OK;
	}
	printf("%s %s\n", MSG_STR_COMPARE, MSG_STR_IGUALES);
	
	return OK;
}

status_t compare_string(char *argv[], int argc, int * compare)
{
	size_t i = 1;


	if (argc == 0)
		return ERROR_EMPTY_STR;

	if (argc > MAX_STR + 1)
		return ERROR_INVALID_AUMOUNT_OF_STR;

	if (argv == NULL || compare == NULL)
		return ERROR_NULL_POINTER;
	

	*compare = strcmp(argv[i], argv[i+1] );

	return OK;
}