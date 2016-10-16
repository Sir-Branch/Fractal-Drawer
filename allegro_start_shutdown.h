/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   allegro_start_shutdown.h
 * Author: r2d2
 *
 * Created on February 18, 2016, 9:34 PM
 */

#ifndef ALLEGRO_START_SHUTDOWN_H
#define ALLEGRO_START_SHUTDOWN_H

#define AL_STARTUP_ERROR -1
#define AL_STARTUP_SUCCESS 0

#define BACKGROUND	"penguin_background.jpg"
#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 800

#define ICON                    "icon.png"
#define BACKGROUND_MUSIC	"background_music.wav"
#define END_MUSIC               "Fatality.wav"

int allegro_startup(void);
void allegro_shut_down(void);
ALLEGRO_DISPLAY * create_display(void);
void saveScreenShotOption(ALLEGRO_DISPLAY* display);
void stopMusic(ALLEGRO_SAMPLE *music);
ALLEGRO_SAMPLE * loadPlayMusic(void);
ALLEGRO_SAMPLE * loadPlayEnd(void);

#endif /* ALLEGRO_START_SHUTDOWN_H */

