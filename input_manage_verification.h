/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input_manage_verification.h
 * Author: r2d2
 *
 * Created on March 16, 2016, 6:47 PM
 */

#ifndef INPUT_MANAGE_VERIFICATION_H
#define INPUT_MANAGE_VERIFICATION_H

//–type YE –lStart 50 –lConstant 0.88 –lEnd 4 –leftAngle -15 –rightAngle -15
        
  
    typedef struct
    {
            double xcord,ycord;
    }point_t;

    typedef struct
    {
            int type;
            double lstart,lend,lconstant;
            double leftangle,rightangle;
            unsigned int polygonSides;
            int leftangleFlag, rightangleFlag,polygonSidesFlag,lconstantFlag;
            
            point_t drawStart;

    }input_data_t;
    
    
    enum types_fractales{YE=1,UNIFORME,PITAGORAS};
    
    #define D_WIDTH		1024
    #define D_HEIGHT	600
    
    #define IN_USE		1
    #define NOT_IN_USE	0
        
    #define YE_RIGHT_ANGLE_MIN	0
    #define YE_RIGHT_ANGLE_MAX	90

    #define YE_LEFT_ANGLE_MIN	-90
    #define YE_LEFT_ANGLE_MAX	0
  
    #define PITAG_RIGHT_ANGLE_MIN   0
    #define PITAG_RIGHT_ANGLE_MAX   90

    #define PITAG_LEFT_ANGLE_MIN    -90
    #define PITAG_LEFT_ANGLE_MAX    0


    #define L_CONSTANT_MIN 0
    #define L_CONSTANT_MAX 1

    #define L_END_MAX	100
    #define L_END_MIN	0

    #define L_START_MAX	600 
    #define L_START_MIN	0

    #define DEFAULT_XCORD ((D_WIDTH)/2.0)
    #define DEFAULT_YCORD ((D_HEIGHT)/2.0)
    #define DEFAULT_POLY_SIDES  8

    #define NOT_VALID_INPUT -1
    #define VALID_INPUT 0


    int get_input_callback(const char *key_orig, const char *value_orig, void *userData);
    void initialize_input_structure(input_data_t * user_input_data);
    int validate_input(input_data_t * user_input_data);
    void draw_fractal(input_data_t * user_input_data);


#endif /* INPUT_MANAGE_VERIFICATION_H */

