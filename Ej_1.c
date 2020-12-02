#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Para calcular la longitud de por ejemplo 2 * 4 = 8, hay que escribirlo entre comillas. "2 * 4 = 8".
Si no ingresamos las "", lo que vamos a calcular la lngitud de la cadena, pero sin considerar los espacios entre las palabras. ya que argv va a guardar cada palabra en una posicion distina del arreglo de cadenas de caracteres. Usando las "", podemos hacer que guarde varias palabreas en una unica posicion y ahi si estariamos considerando los espacios.
*/
			
#define MSG_STR_LEN			"el largo de la cadena es:"


#define MSG_NULL_POINTER	"Puntero NULL"
#define MSG_OK				"OK"


typedef enum {OK, ERROR_NULL_POINTER, ERROR_INVOCATION, MAX_ERRORS} status_t;

const char *errors [MAX_ERRORS] = {MSG_OK, MSG_NULL_POINTER};

status_t calculate_str_length(char *argv[], int argc, size_t * len);

int main (int argc, char * argv[])
{

	status_t st;
	size_t len = 0;
	
	size_t i;
    printf("argc: %d \n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    printf("%d\n", argc);
	
	st = calculate_str_length( argv, argc, &len);

	if(st != OK)
	{
		fprintf(stderr, "%s%s\n", "ERROR:", errors[st]);
		return st;
	}

	printf("%s\t%ld\n", MSG_STR_LEN, len);
	return OK;
}

status_t calculate_str_length(char *argv[], int argc, size_t * len)
{
	size_t i;


	if (argc == 0)
		return OK;

	if (argv == NULL || len == NULL)
		return ERROR_NULL_POINTER;

	for ( i = 1; i < argc; i++)
	{
		*len += strlen(*(argv + i));
	}

	return OK;
}
