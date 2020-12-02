#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 3
#define CMD_ARG_POS_FIRST_VALUE_TOKEN 1
#define CMD_ARG_FIRST_VALUE_TOKEN "-fact"
#define CMD_ARG_POS_SECOND_VALUE_TOKEN 3

/*
    ./cla_validations -a 1 -b 2	
	Estrategia de posiciones fijas. Asume que cada parametro esta en una posicion fija. Si el usuario ingresa los parametros en orden que no le corresponde, se interpreta un error de invocacion.


		./cla_validations -b 1 -a 1
		Las posiciones son variables.
*/

typedef enum {OK, ERROR_NULL_POINTER, ERROR_INVOCATION} status_t;

status_t validate_arg_fixed_position(int argc, char *argv[], size_t *a);

long calulate_factorial(size_t num);

int main (int argc, char *argv[]){

    size_t num;
	long factorial = 1;
    status_t st;

	size_t i;

    printf("argc: %d \n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("argv[%ld] = %s \n", i, argv[i]);
    }
    printf("%d\n", argc);

	/*Entrada viene por lo argumentos de liena de orden. Aca hacemos la traaduccion.*/
    st = validate_arg_fixed_position(argc, argv, &num);

	/*valido e interpetro.*/
    if(st != OK) {
        fprintf(stderr, "%s %s \n", "ERROR:", "Invocacion incorrecta");
        return st;
    }

	/*Aca hago el procesamiento. Obtengo el factorial.*/
	factorial = calulate_factorial(num);

	printf("%s%ld\n", "El factorial es: ", factorial);
    
    return EXIT_SUCCESS;
}


/*A a y b los tengo que pasar como punteros. hay que validar como uso punteros.*/
status_t validate_arg_fixed_position(int argc, char *argv[], size_t *a) {
    
    char *tmp;

	/*valido los parametros*/
	if(a == NULL || argv == NULL){
			return ERROR_NULL_POINTER;
	}

		/* Siempre validar argc */
    if(argc != MAX_ARGS) {
        return ERROR_INVOCATION;
    }
		/* Validación de las banderas de la opción */
		/*strcmp se fija si en la primera posicion tengo la a.
		comparamos lo que tego enla posicion 1, con lo que deberia ser.*/
    if(strcmp(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN], CMD_ARG_FIRST_VALUE_TOKEN)) {
        return ERROR_INVOCATION;
    }
		/* Traducción de los valores.*/
    *a = (size_t) strtol(argv[CMD_ARG_POS_FIRST_VALUE_TOKEN + 1], &tmp, 10);
	
	/*valido que el puntero temporal sea distinto de \0. strtoxxx deja en el puntero final lo que apunta. */
    if(*tmp) {
        return ERROR_INVOCATION;
    }

    return OK;
}

long calulate_factorial(size_t n)
{ 
	
	size_t i;
	long fact = 1;

	for (i = 1; i <= n; ++i)
            fact *= i;

	return fact;
} 