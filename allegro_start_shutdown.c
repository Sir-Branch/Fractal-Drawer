/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

#include "allegro_start_shutdown.h"
#include "input_manage_verification.h"




int allegro_startup(void)
{
	if(al_init())
    {
		if(al_init_primitives_addon())
		{
			if(al_init_image_addon())
			{
				if(al_install_audio())
				{
					if(al_init_acodec_addon())
					{
						if(al_reserve_samples(1))
							return AL_STARTUP_SUCCESS;
						else 
							fprintf(stderr,"ERROR: Failed to reserve samples:(\n");
						//al_shutdown_acodec_addon(); Does not exist
					}
					else 
						fprintf(stderr,"ERROR: Failed to install acodec_addon samples:(\n");
					al_uninstall_audio();
				}
				else
					fprintf(stderr,"ERROR: Failed to install audio\n");
				al_shutdown_image_addon();					
			}
			else
				fprintf(stderr,"ERROR: Failed to load primitives addon\n");
			al_shutdown_primitives_addon();
		}
		else
			fprintf(stderr,"ERROR: Failed to install keyboard\n");
		al_uninstall_system();
    }
    else
		fprintf(stderr,"ERROR: Failed to initialize allegro system\n");
    return AL_STARTUP_ERROR;
}

void allegro_shut_down(void)
{
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_audio(); 
	al_uninstall_system();
}


ALLEGRO_DISPLAY * create_display(void)
{
	ALLEGRO_DISPLAY *display;
	
	if(!(display=al_create_display(D_WIDTH,D_HEIGHT)))
	{
		fprintf(stderr,"Unable to create display\n");
		return NULL;
	}
	
	#if	(defined BACKGROUND && defined BACKGROUND_WIDTH && defined BACKGROUND_HEIGHT) 
	ALLEGRO_BITMAP *background;
	if(!(background=al_load_bitmap(BACKGROUND)))
		fprintf(stderr,"Unable to load background");
	else
	{
		al_draw_scaled_bitmap(background,0,0,BACKGROUND_WIDTH,BACKGROUND_HEIGHT
							,0,0,D_WIDTH,D_HEIGHT,0);
		al_destroy_bitmap(background);
	}
		
	#else
	al_clear_to_color(al_map_rgb(255,255,255));
	#endif 

	al_flip_display();


	#ifdef ICON
	ALLEGRO_BITMAP *icon;
	if(!(icon=al_load_bitmap(ICON)))
		fprintf(stderr,"Unable to load Icon");
	else
	{
		al_set_display_icon(display,icon);
		al_destroy_bitmap(icon);
	}
	#endif
	al_set_window_title(display,"TP EDA#2 Dibujador de Fractales");
	
	
	return display;
}

 
//Guarda una captura de pantalla si el usario lo desea
void saveScreenShotOption(ALLEGRO_DISPLAY* display)
{
	const char* path;
	ALLEGRO_FILECHOOSER *fchooser;
	
	al_show_native_file_dialog(NULL,	
			fchooser=al_create_native_file_dialog(NULL,"Save Fractal Screen Shot. SAVE AS .bmp or image extension","*.*",ALLEGRO_FILECHOOSER_SAVE)
				);
	path=al_get_native_file_dialog_path(fchooser, 0);
	if(path)
		if(!al_save_bitmap(path,al_get_backbuffer(display)))
			fprintf(stderr,"Unable to save file path or extension invalid >%s<\n",path);
	al_destroy_native_file_dialog(fchooser);
	//free(path);
	
	
}


ALLEGRO_SAMPLE * loadPlayMusic(void)
{
	ALLEGRO_SAMPLE * music=al_load_sample(BACKGROUND_MUSIC);
	if(music)
		al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL); 
	else
		fprintf(stderr,"Unable to load background music\n");
	
	return music;
}

ALLEGRO_SAMPLE * loadPlayEnd(void)
{
	ALLEGRO_SAMPLE * music=al_load_sample(END_MUSIC);
	if(music){
		al_stop_samples();
		al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else
		fprintf(stderr,"Unable to load background music\n");
	
	return music;
}

void stopMusic(ALLEGRO_SAMPLE *music)
{
	al_stop_samples();
	al_destroy_sample(music);
	
}