#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo) {
	int i;
	if (modo==GL_LINE) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (modo==GL_FILL) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glBegin( GL_POLYGON );
		for (i=0;i<n;i++) glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
	glEnd();
}

void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0); //Rojo
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0); //Amarillo
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,1.0,1.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_LINES);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

	 //Parte izq
	 glColor3f(1.0,1.0,1.0);
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(-0.35,0.275,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

	 //Parte dcha
	 glColor3f(1.0,1.0,1.0);
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.35,0.275,0.0);
      glVertex3f(0.2,0.55,0.0);
   glEnd(); 

	 //Oreja izq
	 glColor3f(0.0,0.0,0.0);
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.55,0.0);
			glVertex3f(-0.1,0.55,0.0);
			glVertex3f(-0.1,0.63,0.0);
   glEnd(); 

	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.55,0.0);
			glVertex3f(-0.3,0.55,0.0);
			glVertex3f(-0.25,0.455,0.0);
   glEnd();

	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
			glVertex3f(-0.3,0.55,0.0);
			glVertex3f(-0.25,0.65,0.0);
			glVertex3f(-0.1,0.63,0.0);
			glVertex3f(-0.2,0.55,0.0);
   glEnd();  

	 //Oreja dcha
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(0.2,0.55,0.0);
			glVertex3f(0.1,0.55,0.0);
			glVertex3f(0.1,0.63,0.0);
   glEnd(); 

	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
      glVertex3f(0.2,0.55,0.0);
			glVertex3f(0.3,0.55,0.0);
			glVertex3f(0.25,0.455,0.0);
   glEnd();

	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
			glVertex3f(0.3,0.55,0.0);
			glVertex3f(0.25,0.65,0.0);
			glVertex3f(0.1,0.63,0.0);
			glVertex3f(0.2,0.55,0.0);
   glEnd();  
   
	 //Nariz
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
			glVertex3f(-0.1,0.22,0.0);
			glVertex3f(0.1,0.22,0.0);
			glVertex3f(0.0,0.15,0.0);
   glEnd();
   
	 //Ojos
	 Circle(0.07,0.1,0.35,20,GL_FILL);
	 glColor3f(1.0,1.0,1.0);
	 Circle(0.07,0.1,0.35,20,GL_FILL);
}


static void Init( )
{

   glShadeModel( GL_FLAT); // Flat = plano. El color es plano, no hace interpolación (Se queda con el ultimo color que se haya puesto.). Para interpolación --> Smooth.
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0); // x minima, x maxima, y minima, y maxima.
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0); //Color del fondo
  glClear( GL_COLOR_BUFFER_BIT ); // si no lo ponemos el fondo es transparente
    
  
   // los objetos que queremos pintar
   Ejes(6); 
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27) //Si pulsamos esc se cierra
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 ); // 0,0 arriba izquierda
   glutInitWindowSize(500, 500 ); //Tamaño ventana
   glutCreateWindow("Practica 0 IG"); //Titulo de la ventana


   Init(); 

   glutReshapeFunc(Reshape); //event Resizing window
   glutDisplayFunc(Display); //evento display mostrar la ventana cuando se pincha en ella y está dtras de otra. Lo uqe hace es volver a generar la imagen.
   glutKeyboardFunc(Keyboard); //evento pulsar una tecla
  
   glutMainLoop( );

   return 0;
}

