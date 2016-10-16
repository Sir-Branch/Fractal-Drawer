/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>

#include "input_manage_verification.h"//data types
#include "draw_fractals.h"


/*
 * Todas funcionemos que empleamos para el dibujo de los fractales 
 * No nos interesa que otra parte de nuestro porgrama pueda acceder a ellas
 * Razon por la cual las definimos estaticas.
 */

//Tree fractal'Y'
static void 
reqFractalY_(double xCenter, double yCenter, double leftAngle, double rightAngle, 
			double lStart,double lConstant,double lEnd,double *saved_leftAngle,double *saved_rightangle);

//Traingle fractal
static point_t gravityPointTriangle(point_t * point1,point_t * point2,point_t * point3);
static double EuclideanDistance(point_t punto1,point_t punto2);
static void triangle_fractal_recursion(point_t point1, point_t point2, point_t point3,double lEnd);
static ALLEGRO_COLOR allegroRandomColor(void);



//Dibujo primera linea y luego llama a req_fractalY_ que realizara la recursion y el dibujo total del arbol
void reqFractalY(double xCenter, double yCenter, double leftAngle, double rightAngle, 
				double lStart,double lConstant,double lEnd,double *saved_leftAngle,double *saved_rightangle)
{
	al_draw_line(xCenter,yCenter,xCenter,yCenter-lStart,allegroRandomColor(),LINE_THICKNESS);//dibuja la primera linea
	al_flip_display();
	reqFractalY_(xCenter, yCenter-lStart, leftAngle, rightAngle, lStart *lConstant,lConstant,lEnd,saved_leftAngle,saved_rightangle);
}

/*
 * Esta es la funcion que realmente dibuja el fractal la anterior, dibuja la primera linea del fractal
 * para luego llamar a esta.
 * Dibujo el fractal de tipo arbol.
 
 */
void reqFractalY_(double xCenter, double yCenter, double leftAngle, double rightAngle, double lStart,
				double lConstant,double lEnd,double *saved_leftAngle,double *saved_rightangle)
{
	if(lStart <= lEnd)
        return; 
	
    float xFinal = xCenter + lStart*sin( RADIAN(rightAngle));//calculamos el defasaje a el nuevo punto,osea donde termina la nueva rama
	float yFinal = yCenter - lStart*cos( RADIAN(rightAngle));
    
    ALLEGRO_COLOR iterationColor=allegroRandomColor();//se guarda el color de iteracion para que las dos ramas tengan el mismo

    al_draw_line(xCenter,yCenter,xFinal,yFinal,iterationColor, LINE_THICKNESS);
    al_flip_display();
    
	al_rest(REST_TIME);
	//Primero dibujamos toda la parte derecha y luego la izquierda
    reqFractalY_(xFinal,yFinal,leftAngle, rightAngle+ *saved_rightangle, lStart*lConstant,lConstant,lEnd, saved_leftAngle,saved_rightangle);
    xFinal = xCenter + lStart*sin(RADIAN(leftAngle));
	yFinal = yCenter - lStart*cos(RADIAN(leftAngle));
        
    al_draw_line(xCenter,yCenter,xFinal,yFinal, iterationColor , LINE_THICKNESS);
    al_flip_display();
	al_rest(REST_TIME);
	//Llamos la recursion del lado izquierdo
    reqFractalY_(xFinal,yFinal, leftAngle+ *saved_leftAngle,rightAngle, lStart*lConstant,lConstant,lEnd, saved_leftAngle,saved_rightangle);

}

//Color random Rgb 
ALLEGRO_COLOR allegroRandomColor(void){
	return al_map_rgb(rand()%256,rand()%256,rand()%256);	
}


/*
 * Esta funcion dibuja el primer triangulo y luego llama a la funcion que hara la recursion(triangle_fractal_recursion)
 */

void triangle_fractal(double xDrawstart, double yDrawstart, double leftAngle, double rightAngle, double lStart,double lEnd)
{

	double topAngle=180-ABS(leftAngle)-rightAngle;//Calculamos el angulo de arriba que no recibe la funcion
	double lenghtRightSide, lenghtLeftSide;
	point_t leftPoint,topPoint,rightPoint; //estos puntos se emplearan para la recursion

	
	rightPoint.xcord=xDrawstart+lStart;
	rightPoint.ycord=yDrawstart;
	
	leftPoint.xcord=xDrawstart;
	leftPoint.ycord=yDrawstart;

	lenghtLeftSide=sin(RADIAN(rightAngle)) *lStart / sin(RADIAN(topAngle));//Calculamos el largo de un aldo de cualquier triangulo matematica 
	//lenghtRightSide=sin(RADIAN(leftAngle)) *lStart / sin(RADIAN(topAngle));//matematica pura como saben estos pibess 

	if(leftAngle==90.0){
		topPoint.xcord=xDrawstart;
		topPoint.ycord=yDrawstart-lStart * tan(RADIAN(ABS(rightAngle))) ;
	}
	else{
		topPoint.xcord=xDrawstart+lenghtLeftSide*cos(RADIAN(ABS(leftAngle)));
		topPoint.ycord=yDrawstart-lenghtLeftSide*sin(RADIAN(ABS(leftAngle)));
	}
	
	al_draw_triangle(xDrawstart,yDrawstart,rightPoint.xcord,rightPoint.ycord,topPoint.xcord,topPoint.ycord,al_map_rgb(213, 38, 181),LINE_THICKNESS);
	al_flip_display();

	triangle_fractal_recursion(leftPoint,rightPoint,topPoint,lEnd);

}


/*
 * Esta es la funcion que realmente dibuja el fractal del triangulo. La funcion que llama a esta dibuja el triangulo inicial 
 * y luego esta calcula el centro de gravedad/geometrico del triangulo. Una vez calculado el centro se trazan lineas hacia el de cada
 * vertice de triangulo y se repite recursivamente con cada subtriangulo hasta que el largo sea menor que lend.
 */
void triangle_fractal_recursion(point_t point1, point_t point2, point_t point3,double lEnd)
{
	point_t gravityCenter=gravityPointTriangle(&point1, &point2, &point3); 
	ALLEGRO_COLOR iterationColor=allegroRandomColor();
	
	if( EuclideanDistance(point1,gravityCenter) <=lEnd || EuclideanDistance(point2,gravityCenter) <=lEnd || EuclideanDistance(point3,gravityCenter) <=lEnd )
		return;
	
	al_draw_line(point1.xcord,point1.ycord,gravityCenter.xcord,gravityCenter.ycord,iterationColor,LINE_THICKNESS);
	al_draw_line(point2.xcord,point2.ycord,gravityCenter.xcord,gravityCenter.ycord,iterationColor,LINE_THICKNESS);
	al_draw_line(point3.xcord,point3.ycord,gravityCenter.xcord,gravityCenter.ycord,iterationColor,LINE_THICKNESS);
	al_flip_display();
	
	al_rest(REST_TIME);
	
	triangle_fractal_recursion(point1,point2,gravityCenter,lEnd);
	triangle_fractal_recursion(point1,point3,gravityCenter,lEnd);
	triangle_fractal_recursion(point2,point3,gravityCenter,lEnd);

}


//Calcula el centor de grravedad de un triangulo recibiendo los tres puntos de extremo del mismo
point_t gravityPointTriangle(point_t * point1,point_t * point2,point_t * point3)
{
	point_t gravityPoint; 
	gravityPoint.xcord=(point1->xcord + point2->xcord + point3->xcord)/3.0;
	gravityPoint.ycord=(point1->ycord + point2->ycord + point3->ycord)/3.0;
	return gravityPoint;
}

//Tmb conocida como la distancia entre dos puntos
double EuclideanDistance(point_t punto1,point_t punto2){
	return sqrt( SQUARE(punto1.xcord- punto2.xcord)+ SQUARE(punto1.ycord- punto2.ycord));
}


/* Dibuja un fractal de cualquier poligono REGULAR, el fractal consiste en un polygono regular
 * al cual se le dibuja el mismo poligono(en menor escala) en todos los vertices y asi reteiradas veces.
 * Decidimos no implementar varios colores para este fractal ya que no quedaba tan vistoso el resultado y mareaba el patron.
*/
void draw_polygon(double xCenter, double yCenter, double lStart, double lConst, double lEnd, unsigned int polygonType)
{
    if (lStart <= lEnd)
        return;

	double apotema = (lStart * polygonType)/(16*(sqrt(2)-1)); //se calcula la distacia hasta el punto del perimetro mas cercano
	double angle = (180.0 * (polygonType-2.0))/polygonType;//calculo para saber el angulo entre las lineas
	int counter;
	
	point_t *points = malloc ((polygonType+2) * sizeof (point_t)); //arreglo de datos para guardar los puntos donde se empiezan a dibujar los otros poligonos
	if(!points){
		fprintf(stderr,"Unable to allocate space for points in polygon draw function :( \n");
		return;
	}
	points[0].xcord = apotema + xCenter; //hallo el valor en X de la primer coordenada
	points[0].ycord = yCenter - lStart/2; //hallo la primer coordenada en Y
	points[1].xcord = points[0].xcord; //valor de X en la segunda coordenada
	points[1].ycord = yCenter + lStart/2; //valor de Y en la segunda coordenada

	
	for (counter=0 ; counter < polygonType ; counter++)
	{
		al_draw_line (points[counter].xcord, points[counter].ycord, points[counter+1].xcord, points[counter+1].ycord, al_map_rgb (255,0,247), 0.0);	
		points[counter+1].xcord = points[counter].xcord - lStart*sin( RADIAN((180-angle)*(counter+1))); //se reubican los puntos donde se trazan las lineas
		points[counter+1].ycord = points[counter].ycord - lStart*cos( RADIAN((180-angle)*(counter+1)));
                
		points[counter+2].xcord = points[counter+1].xcord + lStart*sin( RADIAN((180-angle)*(counter+1)));
		points[counter+2].ycord = points[counter+1].ycord + lStart*cos( RADIAN((180-angle)*(counter+1)));        
	}
 	al_flip_display();
	al_rest(REST_TIME);
	
	for (counter = 0 ; counter < polygonType ; counter++)//Dibujamos el poligonos mas chichos en todas los vertices del anterior
		draw_polygon (points[counter].xcord, points[counter].ycord, lStart * lConst, lConst, lEnd,polygonType); //recursion
        
	free (points);
}   
	


/* Main de prueba aislada del triangulo 
int main(void)
{

		srand(time(NULL));//seedeamos el main para poder llamar a rand()
		
		al_init();
		al_init_primitives_addon();
		al_init_image_addon();
		
		ALLEGRO_DISPLAY *diplay=al_create_display(1000,600);
		triangle_fractal(0.0,400.0,50,60,300,20.0);

}
*/

/* Main pruebas aislado polygono
 
 
	int main(int argc, char ** argv)
	{
		ALLEGRO_DISPLAY *display = NULL;
		point_t puntoinicial[8];
		double xCenter = DISPLAY_X/2,yCenter = DISPLAY_Y/2;
		int lStart = LENGTH;
		int contador;
		double lConst = 0.6, lEnd = 20;
		int polygonType = POLIGONO;



		if(al_init()) 
		{	
			if(al_init_primitives_addon())
			{
				display = al_create_display(DISPLAY_X, DISPLAY_Y);
				if(display) 
				{
					//Le ponemos el nombre a la ventana.
					al_set_window_title(display,"Poligono regular");
					al_clear_to_color(al_map_rgb (0,0,0));

					draw_polygon (xCenter, yCenter, lStart, polygonType, lConst, lEnd);

					//Esperamos 10.
					al_rest(10.0);

					//Destruimos el display para no generar memory leaks.
					al_destroy_display(display); 

				}
				else
					fprintf(stderr, "failed to create display1!\n");

				//Cerramos apropiadamente el addon de primitives.
				al_shutdown_primitives_addon();
			}
		}
		//The end.
		return 0;
	}
 
 
 */





