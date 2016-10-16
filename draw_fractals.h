/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   draw_fractals.h
 * Author: r2d2
 *
 * Created on March 18, 2016, 10:41 PM
 */

#ifndef DRAW_FRACTALS_H
#define DRAW_FRACTALS_H

    #define REST_TIME	0.1
    #define LINE_THICKNESS  0.0

    #define RADIAN(a) ( (a)/( 180.0/(double)M_PI) )
    #define ABS(x) ((x)<0?(-(x)):(x))
    #define SQUARE(x) ((x)*(x))
    
    void reqFractalY(double xCenter, double yCenter, double leftAngle, double rightAngle,
                    double lStart,double lConstant,double lEnd,double *saved_leftAngle,double *saved_rightangle);
    void triangle_fractal(double xDrawstart, double yDrawstart, double leftAngle, double rightAngle, double lStart,double lEnd);
    void draw_polygon(double xCenter, double yCenter, double lStart, double lConst, double lEnd, unsigned int polygonType);

#endif /* DRAW_FRACTALS_H */

