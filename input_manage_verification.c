/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "input_manage_verification.h"
#include "main_parsing_eda.h"
#include "draw_fractals.h"


static int validate_ye(input_data_t * user_input_data);
static int validate_uniforme(input_data_t * user_input_data);
static int validate_pitagoras(input_data_t * user_input_data);


/*
 * La funcion inicializa la estructura de user_input_data donde se guardara todo
 * la data ingresada por linea de comando.
 * Inicializa aquellos valores opcionales con valores default y se aseguro de que 
 * demas queden fuera de rango para evitar que los valores basura interfiera en el corrido
 * y produzca un inputo falso-verdadero(osea que la basura que este contenida en la posicion de memoria
 * resulta valida para el programa, algo raro pero que puede suceder)
 */


void initialize_input_structure(input_data_t * user_input_data)
{
		
	user_input_data->drawStart.xcord=DEFAULT_XCORD;
	user_input_data->drawStart.ycord=DEFAULT_YCORD;
	user_input_data->polygonSides=DEFAULT_POLY_SIDES;
	
	user_input_data->lend=L_START_MIN-1;
	user_input_data->lstart=L_START_MIN-1;
	user_input_data->lconstant=L_CONSTANT_MIN-1;
	user_input_data->leftangle=-180;
	user_input_data->rightangle=180;
	user_input_data->type=-1;
	
	user_input_data->rightangleFlag=NOT_IN_USE;
	user_input_data->leftangleFlag=NOT_IN_USE;
	user_input_data->polygonSidesFlag=NOT_IN_USE;
	user_input_data->lconstantFlag=NOT_IN_USE;

	
}

/*
 * En este caso el input no puede contener un parametro ya que todos son opciones permite las siguientes entradas de input
 * 
 * xcord, ycord Punto de inicio de dibujo de fractal
 * type, YE,UNIFORME,PITAGORAS que sera el tipo de fractla
 * lstart largo de inicio de las lineas
 * lend largo en el cual se dejara de dibujar el fractal
 * lconstant: multiplicador que se emplea en algunos fractales por el cual se multiplicara lstart en cada iteracion 
 * left/right angle: angulos que se le pasan al fractal Ye y al de pitagoras para realizar el dibujo
 * Sides: Indica cuanto lados tendran los poligonos que se emplearan en el fractal uniforme
 * 
 * 
 * CRITERIO DE PROGRAMA:
 * Decidimos ignora input repetido tomando solo el ultimo si ambos son validos ej: Input -lconst 1000 -lend 10 -lconst 100 
 * Lconst quedara con un valor de 100
 * 
 * 
 * La funcion va comparando los key con strcmp deja abierta ciertas opciones a input mayuscula o minuscula.
 * De concidir la key convierte el value en float, y contempla el caso de error de atof (quisimos implementar otra funcion
 * que trabaja con punteros para error de conversion, pero no resulto ya que generaba ciertos segmentacion faults y no tenia
 * documentacion muy clara)
 */

int get_input_callback(char *key, char *value, void *userData)
{
	int status=CALLBCK_SUCCESS;
	double num_input;//guardaremos el valor 
	
	if(key){//Opcional para hacer mas entendible los casos errores
		printf("Input recieved %s %s\n",key,value);
	}
	
	if(!key){//De pasarse un parametro seteamos un error, esto es opcional y se podria desactivar 
		status=CALLBCK_ERROR;
		fprintf(stderr,"Why would you pass a Parameter?? Check your input('%s') \n",value);
	}
	else if( !strcmp("Type",key) || !strcmp("type",key))
	{
		if(!strcmp("YE",value) || !strcmp("ye",value ) )
			((input_data_t *)userData)->type=YE;
		
		else if(!strcmp("UNIFORME",value) || !strcmp("uniforme",value ) )
			((input_data_t *)userData)->type=UNIFORME;
		
		else if(!strcmp("PITAGORAS",value) || !strcmp("pitagoras",value ) )
			((input_data_t *)userData)->type=PITAGORAS;
		
		else
		{
			fprintf(stderr,"Unknown fractal type\n");
			status=CALLBCK_ERROR;
		}
			
	}
	else if( !strcmp("lStart",key) || !strcmp("lstart",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for lstart not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
		
		else	
			((input_data_t *)userData)->lstart=num_input;
	}
	
	else if( !strcmp("lEnd",key) || !strcmp("lend",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for lend not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
			
		else
			((input_data_t *)userData)->lend=num_input;
	}
	else if( !strcmp("lConstant",key) || !strcmp("lconstant",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for lconstant not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}

		else{
			((input_data_t *)userData)->lconstant=num_input;
			((input_data_t *)userData)->lconstantFlag=IN_USE;
			
		}
	}
	
	else if( !strcmp("leftAngle",key) || !strcmp("leftangle",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for leftangle not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
			
		else
		{
			((input_data_t *)userData)->leftangle=num_input;
			((input_data_t *)userData)->leftangleFlag=IN_USE;
		}
	}
	
	else if( !strcmp("rightAngle",key) || !strcmp("rightangle",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input not for rightangle not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
			
		else
		{
			((input_data_t *)userData)->rightangle=num_input;
			((input_data_t *)userData)->rightangleFlag=IN_USE;
			
		}
	}
	else if( !strcmp("xcord",key) || !strcmp("xCord",key)   )	
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for xcord not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
			
		else
			((input_data_t *)userData)->drawStart.xcord=num_input;
		
	}
	else if( !strcmp("ycord",key) || !strcmp("yCord",key)   )
	{
		num_input=atof(value);
		if(num_input==0.0)//se puede ya que ambos son double
		{
			fprintf(stderr,"Invalid input for ycord not a number or 0.0\n");
			status=CALLBCK_ERROR;
		}
			
		else
			((input_data_t *)userData)->drawStart.ycord=num_input;
	}
	else if( !strcmp("sides",key) || !strcmp("Sides",key)   )
	{
		int side_input=atoi(value);
		if(!num_input) 
		{
			fprintf(stderr,"Invalid input not a number or 0\n");
			status=CALLBCK_ERROR;
		}
			
		else
		{
			((input_data_t *)userData)->polygonSides=side_input;
			((input_data_t *)userData)->polygonSidesFlag=IN_USE;
			
		}
	}
	else
	{
		fprintf(stderr,"Unknown option: '%s %s'\n",key, value);
		status=CALLBCK_ERROR;
	}
	
	return status;
	
}




/*
 * La funcion recibe input YA VERIFICADO, y revisa el tipo de fractal, deja el caso de que se filtre un type no valido pero eso deberia
 * detectarse en la validacion del input.
 * Segun el tipo de fractal llama al fractal correspondiente con los datos correspondientes.
 * 
 */
void draw_fractal(input_data_t * user_input_data)
{
	switch( user_input_data->type )
	{
		case YE:
			reqFractalY(user_input_data->drawStart.xcord ,user_input_data->drawStart.ycord,user_input_data->leftangle,user_input_data->rightangle, 
					user_input_data->lstart,user_input_data->lconstant,user_input_data->lend, &user_input_data->leftangle , &user_input_data->rightangle);
			break;
			
		case UNIFORME:
			draw_polygon(user_input_data->drawStart.xcord ,user_input_data->drawStart.ycord,user_input_data->lstart,
						user_input_data->lconstant,user_input_data->lend,user_input_data->polygonSides);
			break;
			
		case PITAGORAS:
			triangle_fractal(user_input_data->drawStart.xcord ,user_input_data->drawStart.ycord,user_input_data->leftangle,
					user_input_data->rightangle,user_input_data->lstart,user_input_data->lend);
			break;
			
		default://unknown type
			//shouldn't reach this condition since input type has been DOUBLE verified.
			break;
	}
	
}


/*
 *  La funcion como dice su nombre valida el input, del usuario, detecta que tipo de fractal se paso 
 *	y verifica las condiciones para ese fractal(con la funcion correspondiente, devuelve NOT_VALID_INPUT de producirse un error)
 */

int validate_input(input_data_t * user_input_data)
{
	switch( user_input_data->type )
	{
		case YE:
			if(validate_ye(user_input_data)==NOT_VALID_INPUT)
				return NOT_VALID_INPUT;
			break;
			
		case UNIFORME:
			if(validate_uniforme(user_input_data)==NOT_VALID_INPUT)
				return NOT_VALID_INPUT;
			break;
			
		case PITAGORAS:
			if(validate_pitagoras(user_input_data)==NOT_VALID_INPUT)
				return NOT_VALID_INPUT;
			break;
			
		default://unknown type
			fprintf(stderr,"Unknown fractal type or No fractal input\n");
			return NOT_VALID_INPUT;
			break;
	}
	
}

/*
 * Las tres siguientes funciones realizan el verificado de que el input numerico sea valido.
 * Por ejemplo que no se pase un angulo a un fractal que no lo requiere, que no se le pase lados a ye o pitagoras,etc
 * Emplea fuertemente los defines en el header permitiendo asi una mayor flexibilidad.
 */

int validate_ye(input_data_t * user_input_data)
{
	int status=VALID_INPUT;
	
	if( user_input_data->lstart <L_START_MIN || user_input_data->lstart >L_START_MAX   ){
		fprintf(stderr," Invalid range for lstart or not in use\n");
		status=NOT_VALID_INPUT;
	}
	
	else if( user_input_data->lend <L_END_MIN || user_input_data->lend >L_END_MAX || user_input_data->lend > user_input_data->lstart ){
		fprintf(stderr," Invalid range for lend or not in use\n");
		status=NOT_VALID_INPUT;
	}
	
	else if( user_input_data->lconstant < L_CONSTANT_MIN || user_input_data->lconstant >= L_CONSTANT_MAX ){
		fprintf(stderr," Invalid range for lconstant or not in use \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->leftangleFlag==NOT_IN_USE || user_input_data->rightangleFlag==NOT_IN_USE )
	{
		fprintf(stderr, "One or both angles not in use, unable to draw fractal.\n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->leftangle < YE_LEFT_ANGLE_MIN || user_input_data->leftangle > YE_LEFT_ANGLE_MAX ){
		fprintf(stderr," Invalid range for leftangle \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->rightangle < YE_RIGHT_ANGLE_MIN || user_input_data->rightangle > YE_RIGHT_ANGLE_MAX || user_input_data->rightangle==90.0 && user_input_data->rightangle==user_input_data->leftangle){
		fprintf(stderr," Invalid range for rightangle \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->drawStart.xcord > D_WIDTH || user_input_data->drawStart.ycord > D_HEIGHT || user_input_data->drawStart.xcord <0 || user_input_data->drawStart.ycord <0){
		fprintf(stderr," Invalid draw start cords\n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->polygonSidesFlag==IN_USE )
	{
		fprintf(stderr, "Why would you pass sides to this polygon. WHY DO SOME PEOPLE JUST WANT TO SEE THE WORLD BURN??\n");
		status=NOT_VALID_INPUT;
	}
	return status;
	
}

int validate_uniforme(input_data_t * user_input_data)
{
		int status=VALID_INPUT;
	if( user_input_data->lstart <L_START_MIN || user_input_data->lstart >L_START_MAX   ){
		fprintf(stderr," Invalid range for lstart or not in use\n");
		status=NOT_VALID_INPUT;
	}
	
	else if( user_input_data->lend <L_END_MIN || user_input_data->lend >L_END_MAX || user_input_data->lend > user_input_data->lstart ){
		fprintf(stderr," Invalid range for lend or not in use \n");
		status=NOT_VALID_INPUT;
	}
	
	else if( user_input_data->lconstant < L_CONSTANT_MIN || user_input_data->lconstant >= L_CONSTANT_MAX ){
		fprintf(stderr," Invalid range for lconstant or not in use \n");
		status=NOT_VALID_INPUT;
	}
		
	else if( user_input_data->leftangleFlag==IN_USE || user_input_data->rightangleFlag==IN_USE )
	{
		fprintf(stderr, "Why did you pass angles to this fractal? It needn't use any.\n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->drawStart.xcord > D_WIDTH || user_input_data->drawStart.ycord > D_HEIGHT || user_input_data->drawStart.xcord <0 || user_input_data->drawStart.ycord <0){
		fprintf(stderr," Invalid draw start cords\n");
		status=NOT_VALID_INPUT;
	}
	return status;
	
}

int validate_pitagoras(input_data_t * user_input_data)
{
	int status=VALID_INPUT;
	if( user_input_data->lstart <L_START_MIN || user_input_data->lstart >L_START_MAX   ){
		fprintf(stderr," Invalid range for lstart or not in use\n");
		status=NOT_VALID_INPUT;
	}
	
	else if( user_input_data->lend <L_END_MIN || user_input_data->lend >L_END_MAX || user_input_data->lend > user_input_data->lstart ){
		fprintf(stderr," Invalid range for lend or not in use \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->lconstantFlag==IN_USE ){
		fprintf(stderr," Why would you pass Lconstant in pitagoras fractal \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->leftangle < PITAG_LEFT_ANGLE_MIN || user_input_data->leftangle > PITAG_LEFT_ANGLE_MAX ){
		fprintf(stderr," Invalid range for leftangle or not in use \n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->rightangle < PITAG_RIGHT_ANGLE_MIN || user_input_data->rightangle > PITAG_RIGHT_ANGLE_MAX 
			|| user_input_data->rightangle==90.0 && user_input_data->rightangle==user_input_data->leftangle){
		fprintf(stderr," Invalid range for rightangle or not in use\n");
		status=NOT_VALID_INPUT;
	}
		
	else if( user_input_data->drawStart.xcord > D_WIDTH || user_input_data->drawStart.ycord > D_HEIGHT || user_input_data->drawStart.xcord <0 || user_input_data->drawStart.ycord <0){
		fprintf(stderr," Invalid draw start cords\n");
		status=NOT_VALID_INPUT;
	}
	else if( user_input_data->polygonSidesFlag==IN_USE )
	{
		fprintf(stderr, "Why would you pass sides to this polygon. WHY DO SOME PEOPLE JUST WANT TO SEE THE WORLD BURN??\n");
		status=NOT_VALID_INPUT;
	}
	return status;
}

