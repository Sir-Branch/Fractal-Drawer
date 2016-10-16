
/* 
 * File:   main.c
 * Authores: Dieguez, Manuel
 *			 Merello, Ramiro
 *			 Santamaria,Rocio
 *			 Silva, Nicolas
 * Created on March 15, 2016, 11:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "allegro_start_shutdown.h"
#include "input_manage_verification.h"
#include "main_parsing_eda.h"

#define TEST_MODE 1 //De estar en 0 ejecuta normalmente de lo contrario ejecuta el banco de prueba.

void bancoPruebas(void);

int main(int argc, char** argv) 
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_SAMPLE *background_music,*end_music;
	input_data_t user_input_data;

	if( allegro_startup()==AL_STARTUP_ERROR){
		fprintf(stderr,"Unable to start allegro\n");
		return -1;//Sabemos que no le gustan varios returns pero resulta mucho mas practico y entendible desde nuestro punto de vista.
	}
	srand(time(NULL)); //seedeamos el main para poder llamar a rand()
	
	background_music=loadPlayMusic();
	
	#if TEST_MODE 
	bancoPruebas();
	#else
	
	initialize_input_structure(&user_input_data);
	
	if( parseCmdLine(argc,argv,&get_input_callback,&user_input_data) == PARSING_ERROR){//validamos el input del usuario via CMD/terminal
		fprintf(stderr,"Parsing error\n");
	}
	
	else if(validate_input(&user_input_data)==NOT_VALID_INPUT){//Validamos el input ya parseado 
		fprintf(stderr,"Not valid user input ¯\\_(ツ)_/¯ (stupid....)\n");
	}
	
	else if( (display=create_display()) ){//Si el input es valido creamos display y dibujamos fractal
		draw_fractal(&user_input_data);//dibujamos el fractal correspondiente
		end_music=loadPlayEnd();//Hacemos play de la musica que avisa que el fractal ha terminado de dibujarse
		saveScreenShotOption(display);//Option de sacar screenshot y de pasada te da todo el tiempo que quieras para ver el fractal
		al_destroy_display(display);
		stopMusic(end_music);

	}
	else
		fprintf(stderr,"Unable to create display :( No fractal for you\n");
	
	#endif
	stopMusic(background_music);

	allegro_shut_down();
	
	return 0;
}


/*
 * El banco de pruebas simula en arreglos input de usuario, resulta necesario calcular el tamanio(no tengo enie, ni tildes), 
 * en un arreglo ya que sino toma el tamanio de un char *.
 * Luego en el for funciona al igual que el main, parsea el CMD/Terminal, luego valido y crea el display y finalmente dibuja el fractal
 * dejando un segundo para ver el fractal.
 * 
 */



void bancoPruebas(void)
{
	char *ye_valido[]={"./program","-type", "YE", "-lStart","100", "-lConstant", "0.60", "-lEnd" ,"4" ,"-rightangle" ,"15" ,"-leftangle", "-15"};
    char *triangulo_valido[]={"./program","-type","PITAGORAS","-lStart","300","-lEnd" ,"10" ,"-rightangle" ,"60" ,"-leftangle", "-60"};
    char *uniforme_valido[]={"./program","-type","UNIFORME","-lStart","100", "-lEnd" ,"10","-lConstant", "0.50","-xcord","300","-ycord","300","-sides","8"};
	char *type_invalido[]={"./program","-type","LAMACARENA","-lStart","200", "-lEnd" ,"10","-lConstant", "0.50","-xcord","300","-ycord","300","-sides","5"};
    char *ye_invalido_sides[]={"./program","-type", "YE", "-lStart","10", "-lConstant", "0.70", "-lEnd" ,"4" ,"-rightangle" ,"15" ,"-leftangle", "-15","-sides","5"};
    char *ye_invalido_angulos_invertidos[]={"./program","-type", "YE", "-lStart","10", "-lConstant", "0.70", "-lEnd" ,"4" ,"-rightangle" ,"-15" ,"-leftangle", "15"};
	char *triangulo_invalido_lconstant[]={"./program","-type","PITAGORAS","-lStart","300", "-lConstant", "0.70","-lEnd" ,"50" ,"-rightangle" ,"60" ,"-leftangle", "-60"};
	char *uniforme_invalido_lcons_negat[]={"./program","-type","UNIFORME","-lStart","50", "-lEnd" ,"10","-lConstant", "0.50","-lconstant","-10","-sides","5"};
	char *uniforme_invalido_parametro[]={"./program","UNIFORME","-lStart","50", "-lEnd" ,"10","-lConstant", "0.50","-lconstant","-10","-sides","5"};
	char *uniforme_invalido_lstartVSlend[]={"./program","-type","UNIFORME","-lStart","50", "-lEnd" ,"100","-lConstant", "0.50","-lconstant","-10","-sides","5"};

	   
	char **pruebas[]={ye_valido,triangulo_valido,uniforme_valido,type_invalido,ye_invalido_sides,ye_invalido_angulos_invertidos,
					triangulo_invalido_lconstant,uniforme_invalido_lcons_negat,uniforme_invalido_parametro,uniforme_invalido_lstartVSlend};
	
	int num_elements[]={sizeof(ye_valido)/sizeof(char *), sizeof(triangulo_valido)/sizeof(char *),
						sizeof(uniforme_valido)/sizeof(char *), sizeof(type_invalido)/sizeof(char *),
						sizeof(ye_invalido_sides)/sizeof(char *), sizeof(ye_invalido_angulos_invertidos)/sizeof(char *),
						sizeof(triangulo_invalido_lconstant)/sizeof(char *), sizeof(uniforme_invalido_lcons_negat)/sizeof(char *),
						sizeof(uniforme_invalido_parametro)/sizeof(char *),sizeof(uniforme_invalido_lstartVSlend)/sizeof(char *)};
	int count;
	input_data_t user_input_data;
	ALLEGRO_DISPLAY *display;
	
	
	for(count=0;count<(sizeof(pruebas)/sizeof(char**));count++)
	{
		initialize_input_structure(&user_input_data);
		
		if( parseCmdLine(num_elements[count],pruebas[count],&get_input_callback,&user_input_data) == PARSING_ERROR){
			fprintf(stderr,"Parsing error in test %d \n\n",count+1);
		}
		else if(validate_input(&user_input_data)==NOT_VALID_INPUT){
			fprintf(stderr,"Not valid user input int test %d \n\n",count+1);
		}
		else if( (display=create_display()) ){//Si el input es valido creamos display y dibujamos fractal
			draw_fractal(&user_input_data);
			al_rest(1.0);
			al_destroy_display(display);
		}
		else
			fprintf(stderr,"Unable to create display :( No fractal for you\n");
		
	}
    
}