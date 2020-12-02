/*sampler –alfa <α> -amp <A> -frec <f> -start <T1> -end <T2> -points <N> 
tabular la función dentro del intervalo
[T1,T2) utilizando N puntos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DECIMAL_BASE					10

#define PI								3.1415926536

#define MAX_ARGS 						13

#define CMD_ARG_ALFA_TOKEN 				"-alfa"
#define CMD_ARG_AMPLITUDE_TOKEN 		"-amp"
#define CMD_ARG_FRECUENCY_TOKEN 		"-frec"
#define CMD_ARG_START_TIME_TOKEN 		"-start"
#define CMD_ARG_END_TIME_TOKEN 			"-end"
#define CMD_ARG_POINTS_TOKEN 			"-points"

#define MSG_ERROR						"ERRROR del tipo:"
#define MSG_ERROR_NULL_POINTER			"Puntero a NULL"
#define MSG_ERROR_INVALID_INVOCATION	"Invocacion erronea"


typedef enum
{
	OK,
	ERROR_NULL_POINTER					= 1,
	ERROR_INVALID_INVOCATION			= 2,
	MAX_ERRORS
} status_t;

const char *errors[MAX_ERRORS] = { MSG_ERROR, MSG_ERROR_NULL_POINTER, MSG_ERROR_INVALID_INVOCATION};

status_t validate_arg_dinamic_position(int argc, char *argv[], float *alfa, float *A, float *frecuency, size_t *start_time, size_t * end_time, size_t * points);

double calculate_wave_form(float alfa, float A, float frecuency, double t, double val);

int main (int argc, char *argv[])
{	
	status_t st;

	float alfa, A, f;
	size_t start_time, end_time, points;

	double growth_rate, i, val;

	if((st = validate_arg_dinamic_position(argc, argv, &alfa, &A, &f, &start_time, &end_time, &points)) != OK)
	{
		fprintf(stderr, "%s %s\n", MSG_ERROR, errors[st]);
		return st;
	}

	
	growth_rate = (double) (end_time - start_time) / points;
	val = PI/180;

	for(i = start_time; i < end_time; i += growth_rate)
	{
		printf("%lf\n", calculate_wave_form(alfa, A, f, i, val));
	}
	return OK;
}

/*Validacion de los token ingresados y obtencion del valor de los parametros*/
status_t validate_arg_dinamic_position(int argc, char *argv[], float *alfa, float *A, float *f, size_t *s_t, size_t * e_t, size_t * p)
{
	char *tmp;
	size_t i;
	int args_to_parse;


	if(argv == NULL || alfa == NULL || A == NULL || f == NULL || s_t == NULL || e_t == NULL || p == NULL)
		return ERROR_NULL_POINTER;

	if(argc != MAX_ARGS)
		return ERROR_INVALID_INVOCATION;

	for (i = 1, args_to_parse = MAX_ARGS - 1; i < argc - 1; i+= 2)
	{
		/*checkeo para ver si el comando coincide con -alfa*/
		if(!strcmp(argv[i], CMD_ARG_ALFA_TOKEN)) 
		{
			*alfa = (float) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			/*strtol deja el puntero tmp apuntado al proximo elemento despues del numero que esta pasandod de caracteres a long*/
			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			/*Le restamos 2 a los argumentos que hay que parsear, debido que uno es de -alfa y el otro es el numero que tenga alfa.*/
			args_to_parse -= 2;
		}

		/*checkeo para ver si el comando coincide con -amp*/
		if(!strcmp(argv[i], CMD_ARG_AMPLITUDE_TOKEN)) 
		{
			*A = (float) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			args_to_parse -= 2;
		}

		/*checkeo para ver si el comando coincide con -frec*/
		if(!strcmp(argv[i], CMD_ARG_FRECUENCY_TOKEN)) 
		{
			*f = (float) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			args_to_parse -= 2;
		}

		/*checkeo para ver si el comando coincide con -star*/
		if(!strcmp(argv[i], CMD_ARG_START_TIME_TOKEN)) 
		{
			*s_t = (size_t) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			args_to_parse -= 2;
		}

		/*checkeo para ver si el comando coincide con -end*/
		if(!strcmp(argv[i], CMD_ARG_END_TIME_TOKEN)) 
		{
			*e_t = (size_t) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			args_to_parse -= 2;
		}

		/*checkeo para ver si el comando coincide con -points*/
		if(!strcmp(argv[i], CMD_ARG_POINTS_TOKEN)) 
		{
			*p = (size_t) strtol(argv[i + 1], &tmp, DECIMAL_BASE);

			if(*tmp) 
				return ERROR_INVALID_INVOCATION;
			
			args_to_parse -= 2;
		}
	}

	if(args_to_parse != 0)
		return ERROR_INVALID_INVOCATION;

	return OK;
}


double calculate_wave_form(float alfa, float A, float f, double t, double val)
{
	/*Obtiene el angulos en radianes, entonces lo cambio*/
	return  (A * sin ((2 * PI * f *( (double) t * val ) + alfa)));

}